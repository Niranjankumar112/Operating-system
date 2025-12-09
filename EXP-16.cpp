// 16. Random access file for employee details //
#include <stdio.h>
#include <stdlib.h>

struct emp {
    int id;
    char name[20];
    float salary;
};

int main() {
    FILE *fp;
    struct emp e;
    int n, i, rec;

    fp = fopen("emp.dat", "wb");
    printf("Enter number of employees: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter id name salary: ");
        scanf("%d %s %f", &e.id, e.name, &e.salary);
        fwrite(&e, sizeof(e), 1, fp);
    }
    fclose(fp);

    fp = fopen("emp.dat", "rb");
    printf("Enter record number to read (1 to %d): ", n);
    scanf("%d", &rec);
    if (rec < 1 || rec > n) {
        printf("Invalid record\n");
        fclose(fp);
        return 0;
    }

    fseek(fp, (rec - 1) * sizeof(e), SEEK_SET);
    fread(&e, sizeof(e), 1, fp);
    printf("Record %d: %d %s %.2f\n", rec, e.id, e.name, e.salary);
    fclose(fp);

    return 0;
}

