/* File: linux_permissions_demo.c
   Compile in Dev-C++ (no special libraries required).

   What it does:
   - Shows short explanation of Linux permission model
   - Converts symbolic permission strings to octal (e.g. u=rwx,g=rx,o=r -> 754)
   - Converts octal permission (e.g. 755) to symbolic (rwxr-xr-x)
   - Lets you simulate chmod changes interactively
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* Convert a single digit (0-7) to rwx symbolic (3 chars) */
void digit_to_rwx(int d, char out[4]) {
    out[0] = (d & 4) ? 'r' : '-';
    out[1] = (d & 2) ? 'w' : '-';
    out[2] = (d & 1) ? 'x' : '-';
    out[3] = '\0';
}

/* Convert full octal (e.g. 754) -> symbolic like rwxr-xr-- */
void octal_to_symbolic(int oct, char out[10]) {
    int u = (oct / 100) % 10;
    int g = (oct / 10) % 10;
    int o = oct % 10;
    char a[4], b[4], c[4];
    digit_to_rwx(u, a);
    digit_to_rwx(g, b);
    digit_to_rwx(o, c);
    /* concat */
    snprintf(out, 10, "%s%s%s", a, b, c);
}

/* Parse a symbolic permission token like "u=rwx" or "ug=rw" and apply to u,g,o bits */
void apply_symbolic_token(const char *token, int *uBits, int *gBits, int *oBits) {
    // token form: <who>=<perms>  (we'll only support '=' assignment, not +/- modifiers)
    const char *eq = strchr(token, '=');
    if (!eq) return;
    int whoMaskU = 0, whoMaskG = 0, whoMaskO = 0;
    const char *who = token;
    size_t whoLen = eq - token;
    if (whoLen == 0) return;

    // set who flags
    for (size_t i = 0; i < whoLen; ++i) {
        char c = who[i];
        if (c == 'u') whoMaskU = 1;
        else if (c == 'g') whoMaskG = 1;
        else if (c == 'o') whoMaskO = 1;
        else if (c == 'a') { whoMaskU = whoMaskG = whoMaskO = 1; } // 'a' = all
    }

    // parse permissions part
    int permVal = 0;
    const char *perms = eq + 1;
    for (size_t i = 0; i < strlen(perms); ++i) {
        char p = perms[i];
        if (p == 'r') permVal |= 4;
        else if (p == 'w') permVal |= 2;
        else if (p == 'x') permVal |= 1;
        // ignore other chars
    }

    // assign (use '=' semantics: replace bits for those categories)
    if (whoMaskU) *uBits = permVal;
    if (whoMaskG) *gBits = permVal;
    if (whoMaskO) *oBits = permVal;
}

/* Convert symbolic string like "u=rwx,g=rx,o=r" to octal int (e.g. 754) */
int symbolic_to_octal(const char *sym) {
    // Start with zeros
    int u = 0, g = 0, o = 0;
    char tmp[256];
    strncpy(tmp, sym, sizeof(tmp)-1);
    tmp[sizeof(tmp)-1] = '\0';

    // tokens separated by ','
    char *tok = strtok(tmp, ",");
    while (tok) {
        // trim spaces
        while (*tok == ' ') tok++;
        // apply token
        apply_symbolic_token(tok, &u, &g, &o);
        tok = strtok(NULL, ",");
    }
    return u*100 + g*10 + o;
}

/* Trim newline from fgets */
void chomp(char *s) {
    size_t n = strlen(s);
    if (n > 0 && s[n-1] == '\n') s[n-1] = '\0';
}

/* Show short help/explanation */
void show_explanation() {
    puts("\nLinux File Permission Model (short):");
    puts(" - Types of permissions: read (r), write (w), execute (x)");
    puts(" - Three user categories per file: owner (u), group (g), others (o)");
    puts(" - Shown in ls -l as: rwxr-xr--  -> owner/group/others");
    puts(" - Numeric (octal) mapping: r=4, w=2, x=1. Combine to form digits 0..7");
    puts("   Example: 7 (4+2+1) -> rwx, 5 (4+1) -> r-x, 4 -> r--");
}

/* Simple interactive menu */
int main() {
    char choice[8];
    show_explanation();

    while (1) {
        puts("\nMenu:");
        puts(" 1) Convert symbolic -> octal (e.g. u=rwx,g=rx,o=r)");
        puts(" 2) Convert octal -> symbolic (e.g. 755)");
        puts(" 3) Simulate chmod on example permission (start 644)");
        puts(" 4) Short examples");
        puts(" 0) Exit");
        printf("Enter choice: ");
        if (!fgets(choice, sizeof(choice), stdin)) break;
        int c = atoi(choice);

        if (c == 0) {
            puts("Exiting. Good luck!");
            break;
        } else if (c == 1) {
            char input[256];
            printf("Enter symbolic permission (comma-separated), e.g. u=rwx,g=rx,o=r : ");
            if (!fgets(input, sizeof(input), stdin)) break;
            chomp(input);
            int oct = symbolic_to_octal(input);
            printf("Symbolic: %s  =>  Octal: %03d\n", input, oct);
            char sym[10];
            octal_to_symbolic(oct, sym);
            printf("Which is: %s\n", sym);
        } else if (c == 2) {
            char input[32];
            printf("Enter octal (3 digits) e.g. 755: ");
            if (!fgets(input, sizeof(input), stdin)) break;
            chomp(input);
            // validate digits
            int ok = 1;
            if (strlen(input) != 3) ok = 0;
            for (size_t i = 0; i < strlen(input); ++i) if (!isdigit((unsigned char)input[i])) ok = 0;
            if (!ok) { puts("Invalid octal input. Enter exactly 3 digits like 644 or 755."); continue; }
            int oct = atoi(input);
            char sym[10];
            octal_to_symbolic(oct, sym);
            printf("Octal: %03d  =>  Symbolic: %s\n", oct, sym);
        } else if (c == 3) {
            int oct = 644; // starting sample permission
            printf("Starting sample permission: %03d  ", oct);
            char sym[10];
            octal_to_symbolic(oct, sym);
            printf("(%s)\n", sym);
            while (1) {
                char cmd[256];
                printf("Enter chmod symbolic (like u=rwx,g=rx,o=r) to change, or 'done' to stop: ");
                if (!fgets(cmd, sizeof(cmd), stdin)) { return 0; }
                chomp(cmd);
                if (strcmp(cmd, "done") == 0) break;
                int change = symbolic_to_octal(cmd);
                // If user used only some fields (like g=rw) our parser assigns exactly those fields;
                // we must merge: extract digits from change and replace only non-zero specified fields.
                int cu = change / 100;
                int cg = (change / 10) % 10;
                int co = change % 10;
                // but symbolic_to_octal returns 0 for an unspecified field; to detect what was set,
                // we re-parse tokens quickly: if token includes 'u=' then replace u, etc.
                // We'll check presence of 'u=' 'g=' 'o=' 'a=' in cmd
                if (strstr(cmd, "u=") || strstr(cmd, "a=")) oct = (cu*100) + ( (oct/10)%10 )*10 + (oct%10);
                if (strstr(cmd, "g=") || strstr(cmd, "a=")) oct = ( (oct/100)*100 ) + (cg*10) + (oct%10);
                if (strstr(cmd, "o=") || strstr(cmd, "a=")) oct = ( (oct/100)*100 ) + ( ((oct/10)%10)*10 ) + co;
                // Better: recompute from more robust method: start from current digits then replace:
                int curu = oct / 100;
                int curg = (oct / 10) % 10;
                int cu_new = curu, cg_new = curg, co_new = oct % 10;
                if (strstr(cmd, "u=") || strstr(cmd, "a=")) cu_new = cu;
                if (strstr(cmd, "g=") || strstr(cmd, "a=")) cg_new = cg;
                if (strstr(cmd, "o=") || strstr(cmd, "a=")) co_new = co;
                oct = cu_new*100 + cg_new*10 + co_new;

                octal_to_symbolic(oct, sym);
                printf("New permission: %03d  (%s)\n", oct, sym);
            }
        } else if (c == 4) {
            puts("\nExamples:");
            puts(" - ls -l shows permissions like: -rwxr-xr--");
            puts(" - rwxr-xr--  -> owner=rwx (7), group=r-x (5), others=r-- (4) -> octal 754");
            puts(" - chmod 644 file  -> owner rw-, group r--, others r--  -> -rw-r--r--");
            puts(" - chmod u+x,g-w,o= file -> assign execute to owner, remove write from group, set others none");
            puts("Try options 1 and 2 to convert examples yourself.");
        } else {
            puts("Invalid choice. Try again.");
        }
    }

    return 0;
}

