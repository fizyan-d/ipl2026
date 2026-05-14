/*The advantage of storing array of structures as binary files is that we can use fseek to go to specific record and get the record.
Write a program to store n records in binary file.
Write a function to get mth record and display.
Use fseek
Write a function to delete a record.
Deleting a record requires thinking.*/
#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int id;
    char name[50];
    float gpa;
}Student;
void storeRecords(const char* filename,int n);
void getMthRecord(const char* filename,int m);
void deleteRecord(const char* filename,int idToDelete);
int main(){
    const char* filename="students.dat";
    int n,m,idDel;
    printf("Enter number of records to create : ");
    scanf("%d",&n);
    storeRecords(filename,n);
    printf("\nEnter the record index to retrive (0 to n-1): ");
    scanf("%d",&m);
    getMthRecord(filename,m);
    printf("\nEnter the Student ID to delete: ");
    scanf("%d",&idDel);
    deleteRecord(filename,idDel);
    return 0;

    
}
void storeRecords(const char* filename, int n){
    FILE* fp=fopen(filename,"wb");
    if(!fp) return;
    Student s;
    for(int i=0;i<n;i++){
        printf("Enter ID,Name, GPA for student %d:",i+1);
        scanf("%d %s %f",&s.id,s.name,&s.gpa);
        fwrite(&s, sizeof(Student),1,fp);

    }
    fclose(fp);


}
void getMthRecord(const char* filename,int m){
    FILE* fp=fopen(filename,"rb");
    if(!fp) return;
    Student s;
    fseek(fp,m* sizeof(Student),SEEK_SET);
    if(fread(&s,sizeof(Student),1,fp)){
        printf("Record %d: ID=%d.Name=%s,GPA =%f\n",m,s.id,s.name,s.gpa);

    }else{
        printf("Record not found.\n");
    }
    fclose(fp);
}
void deleteRecord(const char* filename,int idToDelete){
    FILE* fp=fopen(filename,"rb");
    FILE* temp=fopen("temp.dat","wb");
    if(!fp || !temp) return;
    Student s;
    int found =0;
    while(fread(&s,sizeof(Student),1,fp)){
        if(s.id != idToDelete){
            fwrite(&s,sizeof(Student),1,temp);
        }else{
            found=1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove(filename);
    rename("temp.dat",filename);
    if(found) printf("Record with ID %d deleted successfully.\n",idToDelete);
    else printf("Record not found.\n");
}
