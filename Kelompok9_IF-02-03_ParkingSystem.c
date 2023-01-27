#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH_PARKING_LOT 10
#define WIDTH_PARKING_LOT 100

//v.vc = struct untuk indexing
//untuk tipe kendaraan
enum vehicle_type {
    SCOOTER = 1,
    CAR = 2,
    BUS = 3,
    TRUCK = 4
};

// mendeklarasikan struct dari vehicle_count
struct vehicle_count{
    int scooter ; 
    int car ;
    int bus ;
    int truck ;
    int vehicle ;
};

// mendeklarasikan struct dari vehicle
struct vehicle{  
    char name[20];
    int num;
    int row;
    int col;
    int type;
    struct vehicle_count vc;
};

// untuk membersihkan layar setiap setelah menu
void clear(){
    system("cls");
}

// fungsi main (utama)
int main(){
    // inisialisasi struct vehicle
    struct vehicle *v;
    // mengalokasikan memori untuk struct vehicle
    v = (struct vehicle *)malloc(sizeof(struct vehicle));
    // inisialisasi struct vehicle_count dengan nilai 0
    // v->vc. digunakan untuk struct indexing
    v->vc.scooter = 0;
    v->vc.car = 0;
    v->vc.bus = 0;
    v->vc.truck = 0;
    int noOfRecords = 0;

    // loop untuk menampilkan menu
    while (1){
        clear();
        printf("=================== \n");
        printf("Parking System ITTS \n");
        printf("=================== \n");
        printf("| |   M E N U   | | \n");
        printf("=================== \n");
        printf("1. Tambahkan Kendaraan \n");
        printf("2. Tampilkan Kendaraan \n");
        printf("3. Hapus Kendaraan \n");
        printf("4. Tampilkan Tempat Parkir\n");
        printf("5. Cari Kendaraan \n");
        printf("6. Save \n");
        printf("7. Load \n");
        printf("8. Exit \n");
        printf("=================== \n");
        printf("Masukan Pilihan : ");
        int choice;
        scanf("%d", &choice);
        // untuk memeriksa apakah tempat parkir penuh
        if(noOfRecords > WIDTH_PARKING_LOT * LENGTH_PARKING_LOT){
            printf("!TEMPAT PARKIR PENUH!");
            break;
        }
        switch (choice){
        case 1:
            clear();
            // untuk menambah kendaraan dan menghitung kendaraan
            printf("=================== \n");
            printf("Tambahkan Kendaraan \n");
            printf("Nama Kendaraan : ");
            scanf("%s", (v+noOfRecords)->name);
            printf("Tipe Kendaraan : ");
            int type;
            scanf("%d", &type);
            (v+noOfRecords)->type = type;
            switch (type)
            {   
            case 1:
                v->vc.scooter++;
                break;
            case 2:
                v->vc.car++;
                break; 
            case 3:
                v->vc.bus++;
                break;
            case 4:
                v->vc.truck++;
                break;
            case 5:
                v->vc.vehicle++;
                break;
            default:
                break;
            }
            (v+noOfRecords)->num = noOfRecords;
            noOfRecords++;
            break;
        case 2:
            // ini untuk menampilkan kendaraan dengan nama
            printf("Menampilkan Kendaraan \n");
            printf("Nama Kendaraan : \n");
            for (int i = 0; i < noOfRecords; ++i){
                printf("%s \n", (v+i)->name);
            }
            printf("Jumlah Total Kendaraan :\n");
            printf("Total        : %d \n", noOfRecords);
            printf("Sepeda Motor : %d \n", v->vc.scooter);
            printf("Mobil        : %d \n", v->vc.car);
            printf("Bus          : %d \n", v->vc.bus);
            printf("Truck        : %d \n", v->vc.truck);
            printf("\nPlese Enter any key to continue");
            getchar();
            break;
        case 3:
            // Program untuk menghapus kendaraan dengan nama
            printf("Menghapus Kendaraan \n");
            printf("Nama Kendaraan : ");
            char name[20];
            scanf("%s", name);
            for (int i = 0; i < noOfRecords; ++i) {
                if (strcmp(name, (v+i)->name) == 0) {
                    for (int j = i; j < noOfRecords; ++j) {
                        *(v+j)->name = *(v+j+1)->name;
                        (v+j)->num = (v+j+1)->num;
                        (v+j)->row = (v+j+1)->row;
                        (v+j)->col = (v+j+1)->col;
                        (v+j)->type = (v+j+1)->type;
                    }
                    noOfRecords--;
                    break;
                }
            }
            break;
        case 4:
            // Program untuk menampilkan semua tempat parkir
            printf("Tampilan Tempat Parkir \n");
            printf("Nama \t Nomor \t Row \t Col \n");
            for (int i = 0; i < noOfRecords; ++i) {
                printf("%s \t\t", (v+i)->name);
                printf("%d \t\t", i+1);
                printf("%d \t\t",(noOfRecords- noOfRecords-i) / WIDTH_PARKING_LOT );
                printf("%d \t\t",-(noOfRecords- noOfRecords-i) % WIDTH_PARKING_LOT);
            }
            printf("\nPlese Enter any key to continue");
            getchar();
            break;
        case 5:
            // Program untuk mencari kendaraan berdasarkan nomor kendaraan
            printf("Mencari Kendaraan \n");
            printf("Nomor Kendaraan : ");
            int num_search;
            scanf("%d", &num_search);
            for (int i = 0; i < noOfRecords; ++i) {
                if (num_search < noOfRecords) {
                    printf("Nama Kendaraan  : %s \n", (v+num_search)->name);
                    printf("Nomor Kendaraan : %d \n", num_search);
                    printf("Row : %d \n",(noOfRecords- noOfRecords-num_search) / WIDTH_PARKING_LOT );
                    printf("Col : %d \n",-(noOfRecords- noOfRecords-num_search) % WIDTH_PARKING_LOT);
                }
            }
            printf("\nPlese Enter any key to continue");
            getchar();
            break;
        case 6:
            // this is for save data to file
            printf("Save \n");
            FILE *fp;
            fp = fopen("data.txt", "w");
            for (int i = 0; i < noOfRecords; ++i) {
                fprintf(fp, "%s \n", (v+i)->name);
                fprintf(fp, "%d \n", i+1);
                fprintf(fp, "%d \n", (noOfRecords- noOfRecords-i) / WIDTH_PARKING_LOT );
                fprintf(fp, "%d \n", (-(noOfRecords- noOfRecords-i) % WIDTH_PARKING_LOT));
                fprintf(fp, "%d \n", (v+i)->type);
            }
            fclose(fp);
            printf("Save Complete");
            printf("\nPlese Enter any key to continue");
            getchar();
            break;
        case 7:
            // this is for load data from file
            printf("Load \n");
            FILE *fp1;
            fp1 = fopen("data.txt", "r");
            for (int i = 0; i < noOfRecords; ++i) {
                fscanf(fp1, "%s", (v+i)->name);
                fscanf(fp1, "%d", &(v+i)->num);
                fscanf(fp1, "%d", &(v+i)->row);
                fscanf(fp1, "%d", &(v+i)->col);
                fscanf(fp1, "%d", &(v+i)->type);
            }
            fclose(fp1);
            printf("Load Complete");
            printf("\nPlese Enter any key to continue");
            getchar();
            break;
        }
    }
    free(v);
    return 0;
}
