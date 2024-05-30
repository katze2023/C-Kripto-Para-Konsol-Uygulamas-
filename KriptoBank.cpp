// ConsoleApplication15.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//


#include <random>
#include <iostream>
#include <ctime> // Tarih ve saat için kütüphane
#include <chrono>
#include <vector> //Dinamik dizi oluşturabilmek için 
#include <cctype>
//#define _CRT_SECURE_NO_WARNINGS 
using namespace std;

#include <string>


class Hesap
{
public:
    enum /*class*/ HesapTuru { ozelHesap, genelHesap };
    int gecenGunSayisi;
    int hesapNo;

    Hesap(HesapTuru tur) : hesapTuru(tur), bakiye(0), kar(0)
    {
        hesapNoHesapla();
    }

    //Hesap ile ilgili fonksiyonlar
    void hesapNoHesapla();
    void hesapAcilisTarihi();
    void ozelHesapAc();
    void genelHesapAc();
    void hesaplariGoster();
    void al();
    void sat();
    void karBul();
    void bakiyeBul();
    void tarihGuncelle();

private:
    HesapTuru hesapTuru;
    double bakiye;
    string isim;
    string soyisim;
    double kar;
    time_t acilisTarihi;
};

vector<Hesap> hesaplar; // Global hesaplar vektörü


//Hesap numaralarını 4 haneli bir sayı olacak şekilde rastgele oluşturuyor
void Hesap::hesapNoHesapla()
{
    default_random_engine generator;
    uniform_int_distribution<int> distribution(1000, 9999);
    hesapNo = distribution(generator);
}

//Girilen tarihin yaşanmış olup olmadığını kontol eden fonksiyon
bool gercek_tarih_mi(int gun, int ay, int yil)
{
    time_t bugun = time(NULL);
    struct tm* bugunTarih = localtime(&bugun); // Günümüzün tarihini alan yapı

    //if (mktime(hesap::girilenTarih) > mktime(bugunTarih))//Gelecekteki tarihleri kontrol eden yapı
        //return false;

    if (ay < 1 || ay > 12 || gun < 1 || gun > 31) //Genel tarih kontrolü yapan yapı  
        return false;

    if ((ay == 4 || ay == 6 || ay == 9 || ay == 11) && gun > 30) //Gün sayısı 30 olan ayları kontrol eden yapı
        return false;

    if (ay == 2) // Şubat ayı için kontrol yapan yapı 
    {
        if ((yil % 4 == 0 && yil % 100 != 0) || (yil % 400 == 0))
            return gun <= 29;
        else
            return gun <= 28;
    }
    return true;
}
//Kullanıcıdan alınan tarihten itibaren bugüne kadar geçen gün sayısını bulan fonksiyon
void Hesap::hesapAcilisTarihi()
{
    int gun, ay, yil;
    //Kullanıcının girdiği tarihleri "gercek_tarih_mi" fonksiyonuna göre kontrol eden yapı 
    do {
        cout << "\n\n\tLütfen hesabın açılmış olduğu tarihi giriniz (gün, ay, yıl): ";
        cin >> gun >> ay >> yil;

        if (!gercek_tarih_mi(gun, ay, yil)) {
            cout << "\n\n\tGirilen tarih yaşanmamıştır.Lutfen başka bir tarih giriniz (gün, ay, yıl):";
        }
    } while (!gercek_tarih_mi(gun, ay, yil));

    time_t tarih = time(NULL);
    struct tm* tarih_bilgisi = localtime(&tarih);

    /*tarih_bilgisi->tm_hour = 0;
    tarih_bilgisi->tm_min = 0;
    tarih_bilgisi->tm_sec = 0;
    tarih_bilgisi->tm_mon = 0;
    tarih_bilgisi->tm_mday = 1;*/

    struct tm girilenTarih = { 0 };
    girilenTarih.tm_year = yil - 1900;
    girilenTarih.tm_mon = ay - 1;
    girilenTarih.tm_mday = gun;

    time_t bugun = time(NULL);
    struct tm* bugunTarih = localtime(&bugun);

    int gecenGunSayisi = difftime(mktime(bugunTarih), mktime(&girilenTarih)) / (60 * 60 * 24);

    //int gecenGunSayisi = difftime(tarih, mktime(tarih_bilgisi)) / (60 * 60 * 24);
    cout << "\n\n\tHesabınız" << gecenGunSayisi << " gündür açıktır.";
}

//Özel hesap açan fonksiyon
void Hesap::ozelHesapAc()
{
    this->hesapTuru = HesapTuru::ozelHesap;

    // Diğer özel hesap işlemleri

    system("cls");
    cout << "\n\n\tÖzel hesap ile ilgili bilgiler:" << "\n\t1)Özel hesap günlük %5 oranında artış sağlar." << "\n\t2)Ayda üç defa %10'luk düşüş olur.";
    //Hesabın açılmış olduğu tarihi alan fonksiyon
    void hesapAcilisTarihi();
    void hesapNoHesapla();

    cout << "\n\t\tHesap numaranız:" << hesapNo;
    cout << "\n\tHesap sahibi ismini giriniz:";
    cin >> isim >> soyisim;
    cout << "\n\tHesaba para yükleyiniz. (1TL=1KritoPara):";
    cin >> bakiye;
    cout << "\n\n\tÖzel hesabınız açılmıştır.";

    // Oluşturulan hesabı hesaplar vektörüne ekleme
    hesaplar.push_back(*this);
}

//Genel hesap açan fonksiyon 
void Hesap::genelHesapAc()
{
    this->hesapTuru = HesapTuru::genelHesap;

    cout << "\n\n\tGenel hesap ile ilgili bilgiler:" << "\n\t1)Genel hesap günlük %1 oranında artış sağlar." << "\n\t2)On beş günde bir defa %5'lik düşüş olur.";
    //Hesabın açılmış olduğu tarihi alan fonksiyon
    void hesapAcilisTarihi();
    void hesapNoHesapla();

    cout << "\n\t\tHesap numaranız:" << hesapNo;
    cout << "\n\tHesap sahibi ismini giriniz:";
    cin >> isim >> soyisim;
    cout << "\n\tHesaba para yükleyiniz. (1TL=1KritoPara):";
    cin >> bakiye;
    cout << "\n\n\nGenel hesabınız açılmıştır.";

    // Oluşturulan hesabı hesaplar vektörüne ekleme
    hesaplar.push_back(*this);
}

//Karı hesap tiplerine göre hesaplayan fonksiyon 
void Hesap::karBul()
{

    srand(time(NULL)); // Her program başında rastgele günleri seçecek 
    double yeniBakiye{};
    int gecenAySayisi = gecenGunSayisi / 30;
    int dususOlanGunSayisi;
    if (Hesap::ozelHesap)  // özel hesap için kar hesaplar
    {
        dususOlanGunSayisi = 3 * gecenAySayisi;//Özel hesap için
        //%5'lik artışın olduğu günler yeni bakiye hesaplanması 
        for (int gun = 0; gun <= gecenGunSayisi - dususOlanGunSayisi; gun++)
            yeniBakiye = bakiye * (1 + 0.05);
        // Her ay farklı olacak şekilde rasgele seçilen 3 günde %10 düşüşün hesaplanması  
        for (int gecenAylar = 0; gecenAylar <= gecenAySayisi; gecenAylar++)
        {
            int dususOlacakGunler = rand() % 31;
            yeniBakiye = bakiye * (1 - 0.10);
        }


        //Karın hesaplanıp ekrana yazdırılma işlemi
        kar = yeniBakiye - bakiye;
        cout << "\n\n\tAçmış olduğunuz özel hesabınızın açılmış olduğu vakitten itibaren net kazancı : " << kar;
    }
    else // genel hesap için kar hesaplar 
    {
        dususOlanGunSayisi = 2 * gecenAySayisi;
        //%1'lik artışın olduğu günler yeni bakiye hesaplanması 
        for (int gun = 0; gun <= gecenGunSayisi - dususOlanGunSayisi; gun++)
            yeniBakiye = bakiye * (1 + 0.01);
        // Her 15 günde 1 defa %5'lik düşüşün hesaplanması
        for (int gun = 0; gun <= dususOlanGunSayisi; gun++)
            yeniBakiye *= 0.95;

        //Karın hesaplanıp ekrana yazılma işlemi 
        kar = yeniBakiye - bakiye;
        cout << "\n\n\tAçmış olduğunuz genel hesabınızın açılmış olduğu vakitten itibaren net kazancı : " << kar;

    }
}


void Hesap::al()
{
    int yuklenecekParaTL;
    double yuklenecekParaKripto;
    static double yeniKriptoKuru;

    //Kullanıcıdan para miktarının alınması
    cout << "\n\n\tHesabınıza aktarmak istediğiniz para miktarını giriniz:";
    cin >> yuklenecekParaTL;

    if (HesapTuru::ozelHesap) //Özel hesap için alış işlemleri
    {
        int gecenAySayisi = gecenGunSayisi / 30;
        int dususOlanGunSayisi = 3 * gecenAySayisi;

        // Yeni kur değerinin hesaplanması 
        for (int gun = 0; gun <= gecenGunSayisi - dususOlanGunSayisi; ++gun) // %5'lik artış
            yeniKriptoKuru = 1 + (1 * 0.05);
        for (int gun = 0; gun <= dususOlanGunSayisi; ++gun) // %10'luk düşüş
            yeniKriptoKuru = yeniKriptoKuru * 0.10;
        // Türk Lirasının kripto paraya çevrilmesi


        yuklenecekParaKripto = yuklenecekParaTL * yeniKriptoKuru;

    }
    else //Genel hesap için satış işlemleri 
    {
        int gecenAySayisi = gecenGunSayisi / 30;
        int dususOlanGunSayisi = 2 * gecenAySayisi;

        // Yeni kur değerinin hesaplanması 
        for (int gun = 0; gun <= gecenGunSayisi - dususOlanGunSayisi; ++gun) // %1'lik artış
            yeniKriptoKuru = 1 + (1 * 0.01);
        for (int gun = 0; gun <= dususOlanGunSayisi; ++gun) // %5'lik düşüş
            yeniKriptoKuru = yeniKriptoKuru * 0.5;
        // Türk Lirasının kripto paraya çevrilmesi
        yuklenecekParaKripto = yuklenecekParaTL * yeniKriptoKuru;

    }
    cout << "\n\n\tGüncel kur değeri:" << yeniKriptoKuru;
    cout << "\n\n\tHesabınızın yeni bakiyesi:" << bakiye + yuklenecekParaKripto;

}

void Hesap::sat()
{
    double cekilecekParaTL;
    double cekilecekParaKripto;
    static double yeniKriptoKuru;

    //Kullanıcıdan para miktarının alınması
    cout << "\n\n\tHesabınızdan çekmek istediğiniz kripto miktarını giriniz:";
    cin >> cekilecekParaKripto;
    // Çekilecek kripto para miktarı bakiyeyi geçmemeli
    if (cekilecekParaKripto <= bakiye)
    {

        if (Hesap::ozelHesap) //Özel hesap için satış işlemleri
        {

            int gecenAySayisi = gecenGunSayisi / 30;
            int dususOlanGunSayisi = 3 * gecenAySayisi;

            // Yeni kur değerinin hesaplanması 
            for (int gun = 0; gun <= gecenGunSayisi - dususOlanGunSayisi; ++gun) // %5'lik artış
                yeniKriptoKuru = 1 + (1 * 0.05);
            for (int gun = 0; gun <= dususOlanGunSayisi; ++gun) // %10'luk düşüş
                yeniKriptoKuru = yeniKriptoKuru * 0.10;
            // Çekilecek kripto paranın 
            cekilecekParaTL = cekilecekParaKripto * yeniKriptoKuru;

        }
        else //Genel hesap için satış işlemleri 
        {
            int gecenAySayisi = gecenGunSayisi / 30;
            int dususOlanGunSayisi = 2 * gecenAySayisi;

            // Yeni kur değerinin hesaplanması 
            for (int gun = 0; gun <= gecenGunSayisi - dususOlanGunSayisi; ++gun) // %1'lik artış
                yeniKriptoKuru = 1 + (1 * 0.01);
            for (int gun = 0; gun <= dususOlanGunSayisi; ++gun) // %5'lik düşüş
                yeniKriptoKuru = yeniKriptoKuru * 0.5;
            // Türk Lirasının kripto paraya çevrilmesi
            cekilecekParaTL = cekilecekParaKripto * yeniKriptoKuru;

        }
        cout << "\n\n\tHesabınızdan" << cekilecekParaTL << " tutarında TL çekilmiştir.";
        cout << "\n\n\tHesabınızın yeni bakiyesi:" << bakiye - cekilecekParaKripto;

    }
    else
        cout << "\n\n\tHesabınızda bulunan miktardan daha fazlasını çekemezsiniz. Hezabınızda" << bakiye << " miktarında kripto para vardır.";

}

void Hesap::bakiyeBul()
{
    cout << "\n\n\tMevcut durumunu görüntülemek istediğiniz hesabın numarasını giriniz:";
    cin >> hesapNo;
    // Girilen hesap numarasının var olan bir hesaba ait olması gerekir


    cout << "\n\n\tHesap numaranız:" << hesapNo;
    cout << "\n\n\tHesap sahibi:" << isim, soyisim;
    cout << "\n\n\tHesabınızın güncel bakiyesi" << bakiye;

}

//Tarih bilgilerinin güncellendiği fonksiyon
void Hesap::tarihGuncelle()
{
    int gun, ay, yil;
    //Kullanıcının girdiği tarihleri "gercek_tarih_mi" fonksiyonuna göre kontrol eden yapı 
    do {
        cout << "\n\n\tLütfen hesabınız için yeni bir açılış tarihi giriniz (gün, ay, yıl): ";
        cin >> gun >> ay >> yil;
        cout << "\n\n\tHesanızın açılış tarihi güncellenmiştir.";

        if (!gercek_tarih_mi(gun, ay, yil)) {
            cout << "\n\n\tGirilen tarih yaşanmamıştır.Lutfen başka bir tarih giriniz (gün, ay, yıl):";
        }
    } while (!gercek_tarih_mi(gun, ay, yil));

}

void Hesap::hesaplariGoster()
{
    system("cls");
    if (Hesap::ozelHesap) //Özel hesapların görüntülenmesi 
    {
        cout << "\n\n\n\tAçılmış olan özel hesapları görüntülemektesiniz.";
        cout << "\n\n\tHesap numarası:" << hesapNo;
        cout << "\n\n\tHesap sahibinin adı:" << isim + " " + soyisim;
        cout << "\n\n\tHesap bakiyeniz:" << bakiye;
    }
    else //Genel hesapların görüntülenmesi
    {
        cout << "\n\n\n\t\t\tAçılmış olan genel hesapları görüntülemektesiniz.";
        cout << "\n\n\tHesap numarası:" << hesapNo;
        cout << "\n\n\tHesap sahibinin adı:" << isim + " " + soyisim;
        cout << "\n\n\tHesap bakiyeniz:" << bakiye;
    }

}

//Ekrana introyu yazdıran fonksiyon 
void intro()
{
    cout << "===================================================" << endl;
    cout << "      PROGRAMLAMAYA GİRİŞ DERSİ 2. ÖDEV" << endl;
    cout << "         KRİPTO BANKACILIK SİSTEMİ" << endl << endl;
    cout << "          HAZIRLAYAN : FATİH KAYA " << endl;
    cout << "          OKUL: SAKARYA ÜNİVERSİTESİ" << endl;
    cout << "===================================================" << endl;

    cout << "Programa başlamak için enter tuşuna basınız";
    cin.get();
}


int main()
{
    setlocale(LC_ALL, "Turkish"); //Türkçe karakter
    srand(time(NULL)); // Her defasında farklı bir parametre alır

    //vector<hesap> hesap::hesaplar; //Hesaplarla ilgili vektör 

    //Günümüz tarihini gösteren yapı
    time_t tarih = time(NULL);
    struct tm* tarih_bilgisi = localtime(&tarih);
    char mTarih[50];
    strftime(mTarih, sizeof(mTarih), "%d-%m-%Y %H:%M:%S", tarih_bilgisi); //Tarih bilgilerini ayırır 

    /*clock_t baslangic = clock(), bitis;
    int sayi;
    bitis = clock();
    cout << (float)(bitis - baslangic) / CLOCKS_PER_SEC;*/

    Hesap hesapNesnesi(Hesap::HesapTuru::ozelHesap); //Özel hesap nesnesi oluşturuldu
    //Hesap hesapNesnesi(Hesap::HesapTuru::genelHesap);

    intro(); // İntroyu ekrana yazdırır.
    int choice;
    do
    {
        //Kullanıcıdan veri girişinin alınması
        system("cls");
        cout << "=================================================";
        cout << "\n\n\n\t*ANA MENÜ*";
        cout << "\n\n\t01. ÖZEL HESAP AÇ";
        cout << "\n\n\t02. GENEL HESAP AÇ";
        cout << "\n\n\t03. HESABA PARA YÜKLE";
        cout << "\n\n\t04. HESAPTAN PARA ÇEK";
        cout << "\n\n\t05. TARİHİ DÜZENLE";
        cout << "\n\n\t06. HESAPLARI LİSTELE";
        cout << "\n\n\t07. ÇIKIŞ";
        cout << "\n\n\tGüncel Tarih:" << ctime(&tarih); //Ekrana tarih bilgisini yazar 
        cout << "\n\n=================================================";
        cout << "\n\n\tİŞLEMİNİZİ SEÇİNİZ. (1-7): ";
        cin >> choice;
        system("cls");
        //Girilen veriye göre fonksiyonların çalıştırılması 
        switch (choice)
        {
        case 1:
            hesapNesnesi.ozelHesapAc();
            break;
        case 2:
            hesapNesnesi.genelHesapAc();
            break;
        case 3:
            system("cls");
            cout << "\n\n\tLütfen üzerinde işlem yapmak istediğiniz hesabınızın numarasını giriniz:";
            cin >> hesapNesnesi.hesapNo;
            break;
        case 4:
            system("cls");
            cout << "\n\n\tLütfen üzerinde işlem yapmak istediğiniz hesabınızın numarasını giriniz:";
            cin >> hesapNesnesi.hesapNo;
            break;
        case 5:
            system("cls");
            cout << "\n\n\tLütfen üzerinde işlem yapmak istediğiniz hesabınızın numarasını giriniz:";
            cin >> hesapNesnesi.hesapNo;
            break;
        case 6:
            hesapNesnesi.hesaplariGoster();
            break;
        case 7: //Çıkış yapar
            cout << "\n\n\t Bankacılık sistemimizi kullandığınız için teşekkür ederiz.";
            break;
        default:cout << "\a"; //Bip sesi çıkaracak mı?
        }
    } while (choice != 7);

    system("pause");
    return 0;
}


// Programı çalıştır: Ctrl + F5 veya Hata Ayıkla > Hata Ayıklamadan Başlat menüsü
// Programda hata ayıkla: F5 veya Hata Ayıkla > Hata Ayıklamayı Başlat menüsü

// Kullanmaya Başlama İpuçları: 
//   1. Dosyaları eklemek/yönetmek için Çözüm Gezgini penceresini kullanın
//   2. Kaynak denetimine bağlanmak için Takım Gezgini penceresini kullanın
//   3. Derleme çıktısını ve diğer iletileri görmek için Çıktı penceresini kullanın
//   4. Hataları görüntülemek için Hata Listesi penceresini kullanın
//   5. Yeni kod dosyaları oluşturmak için Projeye Git > Yeni Öğe ekle veya varolan kod dosyalarını projeye eklemek için Proje > Var Olan Öğeyi Ekle adımlarını izleyin
//   6. Bu projeyi daha sonra yeniden açmak için Dosya > Aç > Proje'ye gidip .sln uzantılı dosyayı seçin
