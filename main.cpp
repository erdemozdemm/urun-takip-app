#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Urun {
    string ad;
    double fiyat;
    int adet;
};

void menuGoster() {
    cout << "\n===== URUN SATIS TAKIP SISTEMI =====\n";
    cout << "1. Urun Ekle\n";
    cout << "2. Urunleri Listele\n";
    cout << "3. Toplam Stok Degerini Hesapla\n";
    cout << "4. Urun Sil\n";
    cout << "5. Urun Guncelle\n";
    cout << "6. Cikis\n";
    cout << "Seciminizi girin: ";
}

void urunEkle(vector<Urun>& urunler) {
    Urun yeniUrun;

    cout << "\nUrun adini girin: ";
    cin.ignore();
    getline(cin, yeniUrun.ad);

    cout << "Urun fiyatini girin: ";
    cin >> yeniUrun.fiyat;

    cout << "Urun adetini girin: ";
    cin >> yeniUrun.adet;

    urunler.push_back(yeniUrun);

    cout << "Urun basariyla eklendi.\n";
}

void urunleriListele(const vector<Urun>& urunler) {
    if (urunler.empty()) {
        cout << "\nHenuz urun eklenmedi.\n";
        return;
    }

    cout << "\n===== URUN LISTESI =====\n";
    cout << left << setw(5) << "No"
         << setw(20) << "Urun Adi"
         << setw(12) << "Fiyat"
         << setw(10) << "Adet"
         << setw(15) << "Toplam" << endl;

    cout << "-----------------------------------------------------------\n";

    for (size_t i = 0; i < urunler.size(); i++) {
        double toplam = urunler[i].fiyat * urunler[i].adet;

        cout << left << setw(5) << (i + 1)
             << setw(20) << urunler[i].ad
             << setw(12) << urunler[i].fiyat
             << setw(10) << urunler[i].adet
             << setw(15) << toplam << endl;
    }
}

void urunSil(vector<Urun>& urunler) {
    if (urunler.empty()) {
        cout << "\nHenuz urun eklenmedi.\n";
        return;
    }

    cout << "\n===== SILINECEK URUNU SECIN =====\n";
    urunleriListele(urunler);

    int secim;
    cout << "\nSilmek istediginiz urunun numarasini girin: ";
    cin >> secim;

    if (secim < 1 || secim > static_cast<int>(urunler.size())) {
        cout << "\nGecersiz urun numarasi!\n";
        return;
    }

    urunler.erase(urunler.begin() + (secim - 1));
    cout << "\nUrun basariyla silindi.\n";
}

void urunGuncelle(vector<Urun>& urunler) {
    if (urunler.empty()) {
        cout << "\nHenuz urun eklenmedi.\n";
        return;
    }

    cout << "\n===== GUNCELLENECEK URUNU SECIN =====\n";
    urunleriListele(urunler);

    int secim;
    cout << "\nGuncellemek istediginiz urunun numarasini girin: ";
    cin >> secim;

    if (secim < 1 || secim > static_cast<int>(urunler.size())) {
        cout << "\nGecersiz urun numarasi!\n";
        return;
    }

    cout << "\nYeni urun adini girin: ";
    cin.ignore();
    getline(cin, urunler[secim - 1].ad);

    cout << "Yeni urun fiyatini girin: ";
    cin >> urunler[secim - 1].fiyat;

    cout << "Yeni urun adetini girin: ";
    cin >> urunler[secim - 1].adet;

    cout << "\nUrun basariyla guncellendi.\n";
}

void toplamStokDegeri(const vector<Urun>& urunler) {
    if (urunler.empty()) {
        cout << "\nHenuz urun eklenmedi.\n";
        return;
    }

    double genelToplam = 0;

    for (const auto& urun : urunler) {
        genelToplam += urun.fiyat * urun.adet;
    }

    cout << "\nToplam stok degeri: " << genelToplam << " TL\n";
}

int main() {
    vector<Urun> urunler;
    int secim;

    do {
        menuGoster();
        cin >> secim;

        switch (secim) {
            case 1:
                urunEkle(urunler);
                break;
            case 2:
                urunleriListele(urunler);
                break;
            case 3:
                toplamStokDegeri(urunler);
                break;
            case 4:
                urunSil(urunler);
                break;
            case 5:
                urunGuncelle(urunler);
                break;
            case 6:
                cout << "\nProgramdan cikiliyor...\n";
                break;
            default:
                cout << "\nGecersiz secim yaptiniz. Tekrar deneyin.\n";
        }

    } while (secim != 6);

    return 0;
}