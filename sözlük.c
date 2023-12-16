#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Maksimum kelime sayısı
#define MAX_KELIME_SAYISI 100

// Veritabanında bulunan kelime çiftleri
char kelimeCiftleri[MAX_KELIME_SAYISI][2][100] = {
    {"hello", "merhaba"},
    {"merhaba", "hello"},
    {"gülegüle", "goodbye"},
    {"goodbye", "gülegüle"},
    // Ek çeviriler ekleyebilirsiniz
};

// Her kelimenin kaç defa sorulduğunu tutmak için sayaç dizisi
int sorulmaSayilari[MAX_KELIME_SAYISI] = { 0 };

// Toplam kelime sayısı
int toplamKelimeSayisi = 4; // Başlangıçta dört kelime var

// Kelime çifti ekleme fonksiyonu
void kelimeEkle(const char* ingilizce, const char* turkce) {
    if (toplamKelimeSayisi < MAX_KELIME_SAYISI) {
        strcpy(kelimeCiftleri[toplamKelimeSayisi][0], ingilizce);
        strcpy(kelimeCiftleri[toplamKelimeSayisi][1], turkce);
        toplamKelimeSayisi++;
        printf("Kelime çifti eklendi: %s - %s\n", ingilizce, turkce);
    }
    else {
        printf("Maksimum kelime sayısına ulaşıldı. Daha fazla kelime eklenemez.\n");
    }
}

int karsilastir(const void* a, const void* b) {
    return strcoll(*(const char(*)[100])a, *(const char(*)[100])b);
}


int main() {
    char input[100];
    int indeks = -1;  // indeks'i burada tanımladık

    // Türkçe karakterleri desteklemek için yerel ayarı ayarla
    setlocale(LC_ALL, "Turkish");

    while (1) {
        // Kullanıcıya seçenekleri göster
        printf("\n1. Kelime Çevir\n");
        printf("2. Yeni Kelime Ekle\n");
        printf("3. Çıkış\n");
        printf("Seçiminizi yapın: ");

        int secim;
        scanf("%d", &secim);
        getchar(); // Buffer'ı temizle

        switch (secim) {
        case 1:
            // Kelime çevirme işlemi
            printf("Kelimeyi girin (İngilizce veya Türkçe): ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            indeks = -1;  // indeksi sıfırla

            // Kelimeleri sırala
            qsort(kelimeCiftleri, toplamKelimeSayisi, sizeof(kelimeCiftleri[0]), karsilastir);

            for (int i = 0; i < toplamKelimeSayisi; ++i) {
                if (strcoll(input, kelimeCiftleri[i][0]) == 0) {
                    printf("Çevirisi: %s\n", kelimeCiftleri[i][1]);
                    indeks = i;
                    break;
                }
                else if (strcoll(input, kelimeCiftleri[i][1]) == 0) {
                    printf("Çevirisi: %s\n", kelimeCiftleri[i][0]);
                    indeks = i;
                    break;
                }
            }

            if (indeks != -1) {
                sorulmaSayilari[indeks]++;
                printf("Kelime %d kez soruldu\n", sorulmaSayilari[indeks]);
            }
            else {
                printf("Çeviri bulunamadı\n");
            }
            break;

        case 2:
            // Yeni kelime ekleme işlemi
            printf("İngilizce kelimeyi girin: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            char ingilizce[100];
            strcpy(ingilizce, input);

            printf("Türkçe karşılığını girin: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            char turkce[100];
            strcpy(turkce, input);

            kelimeEkle(ingilizce, turkce);
            break;

        case 3:
            // Çıkış
            printf("Programdan çıkılıyor...\n");
            return 0;

        default:
            printf("Geçersiz seçenek. Lütfen tekrar deneyin.\n");
        }
    }

    return 0;
}
