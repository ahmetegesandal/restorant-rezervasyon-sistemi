# Restoran Rezervasyon Sistemi

## Proje Açıklaması
Bu proje, bir restoranın rezervasyon sistemini yönetmek için tasarlanmıştır. Kullanıcılar masalarını rezerve edebilir, mevcut rezervasyonları görebilir ve iptal edebilir. Ayrıca, bir yönetici paneli aracılığıyla yemek menüsü üzerinde değişiklik yapma imkanı sunar.

## Kurulum Adımları
1. **Projeyi Klonlayın**:
   ```bash
   git clone https://github.com/ahmetegesandal/restorant-rezervasyon-sistemi.git
   ```
2. **Derleme**:
   Projeyi bir C++ derleyici ile derleyin:
   ```bash
   g++ -o restoran_sistemi main.cpp
   ```
3. **Uygulamayı Çalıştırın**:
   ```bash
   ./restoran_sistemi
   ```

## Kullanım Kılavuzu
- **Ana Menü**:
  - Rezervasyonları yönet.
  - Yemek menüsünü görüntüle.
  - Yönetici paneline erişim.
- **Yönetici Paneli**:
  - Yemek menüsü ekleme, silme ve güncelleme.
  - Menüdeki mevcut öğeleri görüntüleme.
- **Rezervasyon Yönetimi**:
  - Mevcut rezervasyonları görüntüleyin.
  - Müsait masaları kontrol edin ve rezervasyon yapın.
  - Rezervasyonları iptal edin.

## Teknik Detaylar
- **Dil**: C++
- **Özellikler**:
  - Dinamik bellek yönetimi.
  - Kullanıcı dostu konsol arayüzü.
  - Verilerin kalıcı saklanması (`reservations.txt`).
  - Yönetici girişi (Kullanıcı adı: `admin`, Şifre: `12345`).

## Özellikler
1. **Rezervasyon Sistemi**:
   - Müsait masaların listelenmesi.
   - Rezervasyon yapma ve iptal etme işlemleri.
2. **Yemek Menüsü Yönetimi**:
   - Yeni öğeler ekleme, silme veya mevcutları güncelleme.
3. **Yönetici Paneli**:
   - Yalnızca yetkilendirilmiş kullanıcıların erişebileceği bir arayüz.
4. **Veri Saklama**:
   - Rezervasyonlar ve menü öğeleri dosyada saklanır.

## Ekran Görüntüleri / Demolar
### Ana Menü
```
+----------------------------------------+
| Restoran Yönetim Sistemi               |
+----------------------------------------+
1. Rezervasyonları Yönet
2. Menü Görüntüle
3. Yönetici Paneli
4. Çıkış
Seçiminizi girin: _
```

### Müsait Masalar
```
Müsait Masalar: 1 2 3 5 7 9
Rezerve etmek istediğiniz masa numarasını girin: _
```

### Yönetici Paneli
```
+----------------------------------------+
| Yönetici Paneli                        |
+----------------------------------------+
1. Menü Öğesi Ekle
2. Menü Öğesi Sil
3. Menü Öğesi Güncelle
4. Menü Görüntüle
5. Ana Menüye Dön
Seçiminizi girin: _
```

## Katkıda Bulunanlar
- **Ahmet Ege Sandal** - Geliştirici ve Proje Yöneticisi

Daha fazla bilgi için lütfen [proje deposunu](https://github.com/ahmetegesandal/restorant-rezervasyon-sistemi) ziyaret edin.
