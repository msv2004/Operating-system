#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "employee.dat"
#define RECORD_SIZE sizeof(struct Employee)
struct Employee {
  int id;
  char name[30];
  int age;
  float salary;
};
void addEmployee(struct Employee e) {
  FILE *fp;
  fp = fopen(FILE_NAME, "ab");
  if (fp == NULL) {
    printf("Could not open file %s", FILE_NAME);
    return;
  }
  fwrite(&e, RECORD_SIZE, 1, fp);
  fclose(fp);
}
void readEmployee(int id) {
  struct Employee e;
  FILE *fp;
  fp = fopen(FILE_NAME, "rb");
  if (fp == NULL) {
    printf("Could not open file %s", FILE_NAME);
    return;
  }
  fseek(fp, (id - 1) * RECORD_SIZE, SEEK_SET);
  fread(&e, RECORD_SIZE, 1, fp);
  printf("Employee with ID %d:\n", id);
  printf("Name: %s\n", e.name);
  printf("Age: %d\n", e.age);
  printf("Salary: %.2f\n", e.salary);
  fclose(fp);
}
int main() {
  struct Employee e1 = {1, "John Doe", 25, 50000.0};
  struct Employee e2 = {2, "Jane Doe", 30, 60000.0};
  addEmployee(e1);
  addEmployee(e2);
  readEmployee(1);
  readEmployee(2);
}
