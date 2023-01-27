#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define NORMAL  "\x1B[0m"
#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE  "\x1B[34m"
#define CYAN  "\x1B[36m"

struct data{
    char nama[15];
    char usia[5];
    char alamat[20];
};

typedef struct data maba;

int banyakData()
{
    FILE *fptr;

    fptr = fopen("dataMaba", "r");
    fseek(fptr, 0, SEEK_END);

    if(fptr==NULL)return 0;

    return ftell(fptr)/sizeof(maba);
}

void display()
{
    system("cls");
    int count=1, banyakDataMaba;
    FILE *fptr;
    maba mb;
    fptr = fopen("dataMaba", "r");

    banyakDataMaba = banyakData();

    printf(NORMAL);
    printf(YELLOW"\n\t\t\tData mahasiswa\n"NORMAL);
    printf("\t\t\t+---------------------------------------------------+\n");
    printf("\t\t\t|"YELLOW"%-4s"NORMAL"| "YELLOW"%-15s%-10s%-20s"NORMAL"|\n", " No", "Nama", "Usia", "Alamat");
    printf("\t\t\t-----------------------------------------------------\n");


    while(fread(&mb, sizeof(maba), 1, fptr))
    {
        printf("\t\t\t| "YELLOW"%-3d"NORMAL"| "YELLOW"%-15s%-10s%-20s"NORMAL"|\n", count++, mb.nama, mb.usia, mb.alamat);
    }

    printf("\t\t\t+---------------------------------------------------+\n");
    printf(NORMAL);
    fclose(fptr);
}

void editData()
{
    system("cls");
    FILE *fptr, *fptr1;
    maba mb;
    char nama[15];
    int found=0;

    fptr = fopen("dataMaba", "r");
    fptr1 = fopen("helper", "w");

    printf(NORMAL);
    printf("\n\t\t\tMasukan Nama data yang akan diubah : ");
    fflush(stdin);
    gets(nama);

    while(fread(&mb, sizeof(maba), 1, fptr))
    {
        if(strcmp(strlwr(mb.nama), strlwr(nama))==0)
        {
            found=1;

            printf(GREEN"\t\t\tMasukan Nama baru : ");
            scanf("%s", &mb.nama);
            fflush(stdin);

            printf(GREEN"\t\t\tMasukan Usia baru : ");
            scanf("%s", &mb.usia);
            fflush(stdin);

            printf(GREEN"\t\t\tMasukan Alamat baru : ");
            scanf("%s", &mb.alamat);
            fflush(stdin);
        }
        fwrite(&mb, sizeof(maba), 1, fptr1);
    }
    fclose(fptr);
    fclose(fptr1);

    if(found==1)
    {
        fptr = fopen("dataMaba", "w");
        fptr1 = fopen("helper", "r");

        while(fread(&mb, sizeof(maba), 1, fptr1)) fwrite(&mb, sizeof(maba), 1, fptr);
        printf("\n\t\t\t"CYAN"Data berhasil diubah"NORMAL);
    }else
    {
        printf("\n\t\t\t"RED"Data tidak ditemukan"NORMAL);
    }

    fclose(fptr);
    fclose(fptr1);
}

void deleteData()
{
    system("cls");
    FILE *fptr, *fptr1;
    maba mb;
    char nama[15];
    bool isDeleted=false;

    fptr = fopen("dataMaba", "r");
    fptr1 = fopen("helper", "w+");

    printf(YELLOW"\n\t\t\tHapus Data"NORMAL);
    printf(GREEN"\n\t\t\tMasukan Nama Maba yang akan dihapus : ");
    scanf("%s", &nama);
    fflush(stdin);

    while(fread(&mb, sizeof(maba), 1, fptr)){
        if(strcmp(mb.nama, nama)!=0){
            fwrite(&mb, sizeof(maba), 1, fptr1);
        }
        if(strcmp(mb.nama, nama)==0){
            isDeleted = true;
        }
    }
    fclose(fptr);
    fclose(fptr1);

    if(isDeleted){
        fptr1 = fopen("helper", "r");
        fptr = fopen("dataMaba", "w");
        while(fread(&mb, sizeof(maba), 1, fptr1)){
            fwrite(&mb, sizeof(maba), 1, fptr);
        }
        printf(CYAN"\n\t\t\tData berhasil dihapus"NORMAL);
    }else
    {
        printf(RED"\n\t\t\tData tidak ditemukan"NORMAL);
    }
    fclose(fptr);
    fclose(fptr1);
}

void tambahData()
{
    system("cls");
    FILE *fptr;
    maba mb;
    fptr = fopen("dataMaba","a");
    printf(YELLOW"\n\t\t\tMasukan data\n"NORMAL);

    printf("\t\t\tMasukan nama : ");
    fflush(stdin);
    gets(mb.nama);

    printf("\t\t\tMasukan usia : ");
    scanf("%s", &mb.usia);
    fflush(stdin);

    printf("\t\t\tMasukan alamat : ");
    scanf("%s", &mb.alamat);

    printf("\n\n\t\t\t"CYAN"Data berhasil ditambahkan"NORMAL);
    fwrite(&mb, sizeof(maba), 1, fptr);
    fclose(fptr);
}

void cariData()
{
    system("cls");
    FILE *fptr;
    maba mb;
    char nama[15];
    bool isFound=false;

    fptr = fopen("dataMaba", "r");

    printf(YELLOW"\n\t\t\tCari Maba"NORMAL);
    printf(GREEN"\n\t\t\tMasukan nama maba : ");
    scanf("%s", &nama);
    fflush(stdin);

    system("cls");
    while(fread(&mb, sizeof(maba), 1, fptr)){
        if(strcmp(mb.nama, nama)==0){
            isFound = true;
            printf(NORMAL);
            printf("\t\t\t------------------------------------------------\n");
            printf("\t\t\t| Searching by nama                            |\n");
            printf("\t\t\t------------------------------------------------\n");
            printf("\t\t\t| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", "Nama", "Usia", "Alamat");
            printf("\t\t\t------------------------------------------------\n");
            printf("\t\t\t| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", mb.nama, mb.usia, mb.alamat);
            printf("\t\t\t------------------------------------------------\n");
        }
    }
    if(!isFound) printf(RED"\n\t\t\tData tidak ditemukan!"NORMAL);
    fclose(fptr);
}

void sortingData()
{
    system("cls");
    int pilihMenu, count=1;
    int banyakDataMaba=banyakData();
    FILE *fptr;
    maba mb;
    maba mb2[banyakDataMaba];
    maba temp[1];
    fptr = fopen("dataMaba", "r");

    while(fread(&mb, sizeof(maba), 1, fptr))
    {
        mb2[count] = mb;
        count++;
    }

    for(int x=1; x<=banyakDataMaba; x++){
        for(int y=1; y<=banyakDataMaba-x; y++){
            if(atoi(mb2[y].usia) > atoi(mb2[y+1].usia)){
                temp[1] = mb2[y];
                mb2[y] = mb2[y+1];
                mb2[y+1] = temp[1];
            }
        }
    }

    printf(NORMAL);

    printf("\n\t\t\tPengurutan dari maba usia terendah\n");
    printf("\t\t\t+---------------------------------------------------+\n");
    printf("\t\t\t|"YELLOW"%-4s"NORMAL"| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", " No", "Nama", "Usia", "Alamat");
    printf("\t\t\t-----------------------------------------------------\n");
    for(int x=1; x<=banyakDataMaba; x++){
        printf("\t\t\t| "YELLOW"%-3d"NORMAL"| "YELLOW"%-15s%-20s%-10s"NORMAL"|\n", x, mb2[x].nama, mb2[x].usia, mb2[x].alamat);
    }
    printf("\t\t\t+---------------------------------------------------+\n");
}

int main()
{
    int pilihMenu;
    while(true){
        system("cls");
        printf("\n\t\t\t-----------------------------");
        printf("\n\t\t\t|| "YELLOW"  Data Mahasiswa baru  "NORMAL" ||");
        printf("\n\t\t\t-----------------------------\n");
        printf("\n\t\t\t1) Data Mahasiswa");
        printf("\n\t\t\t2) Urutkan dari usia");
        printf(RED"\n\t\t\t3) Keluar"NORMAL);

        printf(GREEN);
        printf("\n\t\t\tMasukan pilihan ");
        scanf("%d", &pilihMenu);

        printf(NORMAL);
        if(pilihMenu==1){
            system("cls");
            printf("\n\t\t\t------------------------------");
            printf(YELLOW"\n\t\t\t| Data Mahasiswa Informatika |"NORMAL);
            printf("\n\t\t\t------------------------------");

            display();
            printf("\n\t\t\t1) Tambahkan Maba");
            printf("\n\t\t\t2) Edit Maba");
            printf("\n\t\t\t3) Hapus Maba");
            printf("\n\t\t\t4) Pencarian Maba");
            printf(RED"\n\t\t\t5) Kembali"NORMAL);

            printf(GREEN);
            printf("\n\t\t\tMasukan pilihan ");
            scanf("%d", &pilihMenu);
            printf(NORMAL);

            if(pilihMenu==1){
                tambahData();
                printf("\n\t\t\t");
                system("pause");
            }else
            if(pilihMenu==2){
                editData();
                printf("\n\t\t\t");
                system("pause");
            }else
            if(pilihMenu==3){
                deleteData();
                printf("\n\t\t\t");
                system("pause");
            }else
            if(pilihMenu==4){
                cariData();
                printf("\n\t\t\t");
                system("pause");
            }else{

            }

        }else
        if(pilihMenu==2){
            sortingData();
            printf("\n\t\t\t");
            system("pause");

        }else
        {
            exit(0);
        }
    }

    return 0;
}
