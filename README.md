# PROJE-3
Bu proje, Tiva C serisi mikrodenetleyici (TM4C123GH6PM) kullanarak ADC (Analog-Dijital Çevirici) ve Timer (Zamanlayıcı) yapılandırması ile analog bir sinyalin okunmasını sağlar. Timer0 kullanılarak ADC0 tetiklenir ve ADC0'dan alınan veriler kesme servis rutini üzerinden işlenir.

Özellikler
ADC0: 12-bit çözünürlükle analog veriyi dijitale çevirir.
Timer0: ADC tetikleme işlemi için periyodik zamanlayıcı olarak kullanılır.
Kesme Servis Rutini: ADC verisi okunduğunda kesme tetiklenir, veriler işlenir.
Kullanılan Donanım
GPIOF: Kullanıcı tarafından belirlenen GPIO portu (başka portlar da seçilebilir).
ADC0: Analog girişleri dijitale çeviren ADC modülü.
Timer0: Zamanlayıcı modülü, periyodik tetiklemeler için kullanılır.
Yapılandırma ve Başlatma
Saat Ayarı: Sistemin saat hızı 50 MHz olarak ayarlanır.
Periferik Aktivasyonu:
GPIOF ve ADC0 periferikleri etkinleştirilir.
Timer0, periyodik modda çalışacak şekilde yapılandırılır.
Timer0 Yapılandırması:
Timer0, her saniyede bir tetiklenecek şekilde ayarlanır.
ADC Yapılandırması:
ADC0, Timer0 tarafından tetiklenecek şekilde yapılandırılır.
ADC kanal 0 üzerinden bir örnekleme yapılır.
Kesme Servis Rutini:
ADC0'dan alınan veri, kesme servis rutininde işlenir.
Çalışma Prensibi
Timer0 her saniyede bir tetiklenir.
ADC0, Timer0 tetiklendiğinde çalışmaya başlar ve analog bir değeri dijitale dönüştürür.
ADC0Handler() fonksiyonu, ADC dönüşümünü tamamladıktan sonra çağrılır ve burada okunan değer value[] dizisine kaydedilir.
