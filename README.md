PROGRAMLAMA LABORATUVARI MİNİMUM ÇEVRELEYEN ÇEMBER (MEC-SPLINE)

                           
  Eliz KURTULUŞ
Kocaeli Üniversitesi
Mühendislik Fakültesi
Bilgisayar Mühendisliği(İÖ)
190202015@kocaeli.edu.tr


İrem ÇELİKKANAT
Kocaeli Üniversitesi
Mühendislik Fakültesi
Bilgisayar Mühendisliği(İÖ)
19020202124@kocaeli.edu.tr


Özet: Bu çalışmada Minimum Enclosing Circle Probleminin algoritmasını oluşturulmuştur. Proje oluşturulması için Codeblocks IDE’si ve Allegro kütüphanesi kullanılmıştır. Projede; kullanıcı tarafından N nokta verildiğinde ,tam sayı koordinatlı iki boyutlu düzlemde tüm noktaları içeren ve minimum çevreleyen yarıçaplı çember çizdirilmektedir.

Anahtar kelimeler: Minimum Çevreleyen Çember Problemi, C Programlama Dili, Allegro kütüphanesi

I.	                GİRİŞ

Proje için (bizden istenilen )C programlama Dili ve Codeblocks geliştirme ortamını kullandık.
•	Codeblocks platformu; özgür açık kaynak kodlu bir C++ tümleşik geliştirme ortamıdır. GNU/Linux, Mac, Windows platformlarında çalışır. Genişletilebilir eklenti desteğine sahiptir. Birden fazla derleyiciyi destekler. Başka programlama dillerini de desteklemesiyle birlikte kod yazımı esnasında ihtiyaç duyabileceğiniz birçok yardımcı fonksiyon sunar. Belirttiğimiz bize sağladığı kolaylıklar tercih etme sebeplerimizdir.
•	Projede amacımız; Minimum çevreleyen çemberin merkezini ve yarıçapını bulmaktır. Minimum çevreleyen daire hesaplama problemi, Min-Max optimizasyon  problemleri olarak bilinen problemler sınıfına aittir. Minimum çevreleyen çember, girilen tüm noktaların çemberin içinde veya sınırlarında yer aldığı bir çemberdir. Merkez noktasının hesaplanmasında noktaların merkeze olan uzaklıklarını sorgular. Minimum çevreleyen daire olması durumunda ise çemberin sınırında bulunan noktaları aramaktadır. Merkez noktasının koordinatlarını bulmak önemlidir. Merkez konumu belirlendiğinde yarıçap ve benzeri şeyler de bulunmuş olur.Projemizde, merkez noktalarını bulmak için iki ayrı koşul kullanılmaktadır. Girilen nokta sayısına bağlı olarak merkezi bulma yöntemimiz değişiklik göstermektedir. Girilen noktalar ise kullanıcının yazdığı txt dosyasından okutulur. Okunan değerler, birçok farklı yapıyı içinde tutabildiğinden struct yapısına atanır. Ardından uygun olunan koşul belirlenerek merkez noktaları ve yarıçap hesaplanır. Hesaplama işlemlerine yöntem bölümünde daha detaylıca değinilecektir. Kullandığımız  arayüz ile de çember çizdirilir.


II.	             YÖNTEM

Bu kısımda projeyi oluştururken kullandığımız araçlar ve yöntemler hakkında ayrıntılı bilgi verilecektir.

A.	Arayüz Tasarımı

Allegro, esas olarak video oyunlarına ve multimedya programlamaya yönelik bir çapraz platform kitaplığıdır. Pencereler oluşturma, kullanıcı girişini kabul etme, veri yükleme, resim çizme, ses çalma vb. Gibi yaygın, düşük seviyeli görevleri yerine getirir ve genel olarak temeldeki platformu soyutlar. Ancak, Allegro bir oyun motoru değildir : programı istediğimiz gibi tasarlayabilecek ve yapılandırabileceğimiz bir yapıdır. Allegro da genel olarak çizim, font vs. için kullanabileceğimiz fonksiyonlar barındırır. Bu projede kullanılan fonksiyonlar şunlardır:

a)	al_draw_textf ( )
b)	al_draw_line( )
c)	al_draw_filled_circle( )
d)	al_draw_circle( )

B.	Kullanılan Yapılar

Kullanıcının girdiği koordinatları alabilmek için dosya işlemlerini kullandık. Dosya ile okuma ve ekleme modunda işlemler gerçekleştirdik. Okunan değerleri ise ‘dizi’ kullanarak ‘struct’ yapısına atadık. Karşılaştırma ve koşul durumlarında ‘if’ yapısından faydalandık . Merkez ve yarıçap hesaplamalarında ‘for döngü’lerinden yararlandık.

C.	Proje Hesaplamaları

Dosya tanımlayarak dosyamızı read modunda açtık. Bize gönderilen dosyadan verilen noktaların koordinatlarını Struct nokta olarak adlandırdığımız içinde double x ve double y değişkenlerini tanımladığımız yapıya dizi yardımıyla atadık.Aynı zamanda bir struct dizisi oluşturduk ve noktaları bu dizide tuttuk. İlk başta genel çember çizme mantığından ilerledik. Ancak üçten fazla nokta girildiğinde çemberin içine dahil olmayan noktalar olduğunu fark ettik. Bu durumu düzeltmek için yeni bir algoritma oluşturduk. Böylece Nokta sayısına bağlı koşul ortaya çıktı. Eğer üç ve üçten az sayıda nokta varsa;  iç içe for döngüleri içinde dizinin indislerini nokta_uzaklik() fonksiyonuna yolladık.

•	nokta_uzaklik() Fonksiyonu
 Noktaların yerini belirten sıralı ikililerin   apsislerinin büyük olanından küçük olanı çıkartılıp, ordinatlarının da büyük olanından küçük olanı çıkartılır. Apsislerin farkının karesi ile ordinatların farkının karesinin toplamı bize iki nokta arasındaki uzunluğun karesini verir.Bu toplamın karekökü ise iki nokta arasındaki uzaklığı verir. Bu yöntem sonucunda noktalar arası uzaklık bulunmuş olur. Uzaklık bulma formülü kısaca şu şekilde gösterilebilir:

IABI = sqrt(pow(x1-x2,2)+pow(y1-y2,2))

Uzaklıklar hesaplandıktan sonra sıralanması gerekir. Amaç en uzak iki noktayı bulabilmektir. Sıralama algoritması kullanmak gerekiyordu. Biz prototip aşamasında basit uygulanabilir olmasından dolayı Selection Sort algoritmasını kullanmaya karar verdik Algoritmanın çalışma ilkesi basittir.

Bu algoritma bizim noktalar arasındaki uzaklığı bulduktan sonra uzaklıkları karşılaştırma aşamasında kullanmak için  fazlasıyla yeterliydi. Daha sonraki aşamalarda da değiştirme gereği duymadık. Bulunan en uzak iki noktanın aralarındaki mesafenin ikiye bölünmesiyle yarıçapı hesaplamış olduk. Bulduğumuz iki noktanın x ve y değişkenlerini, ayrı ayrı tanımladığımız Struct yapılarına atadık. Merkez_bul() fonksiyonuna göndererek merkezin koordinatlarını belirledik. Bu fonksiyonda merkez bulma formülü olan x0= (x1+x2)/2 ve y0= (y1+y2)/2 kullanıldı. Sonuç, merkez için tanımladığımız m Structına gönderilir.



Spline Kaba Kodu

►Başla
► i yi 0.000 dan başlayarak girilen sayı kadar 0.001 arttır
►spline_hesaplama() fonksiyonuna artış miktarı ve dizideki noktaları ve nokta sayısını yolla
►Po P1 P2 P3 ağırlık faktörlerini hesapla
►u değerini 1’in üstüne çıkmaması için int olarak kendinden çıkar ve hep 1 in altında kalmasını sağla
►af1,af2,af3 ve af4 de ağırlık faktörlerinin matematiksel fonksiyonlarını hesapla
►Dizideki her bir noktayı kendi ağırlık faktörü ile carp
►Bunu her x ve y noktası için yap ve struct Spline.x ve Spline.y’ye ata
►Fonksiyonda spline structını döndür
►Gelen fonksiyon değerini spline_nokta_ciz()fonksiyonuna yolla
►Gelen değerleri koordinat sistemine uyarla
► al_draw_filled_circle() fonksiyonu ile spline noktalarını çizdir
►Bitir


D.	PERFORMANS

Programda kullanılan en yüksek dereceli fonsiyon üzerinden hesaplanma yapılmıştır.B-Spline ağırlık faktörlerinden biri baz alınmıştır.
Q1=-t3+2t2-t+0 için k=0
t>0 için (bu aynı zamanda t>k)
t3+2t2-t+0≤-t3+2t3-t3+-t3
+t3 ≤ t3
Öyleyse C=1 ve k=0
F(x) ≤ 1t2+0, x>k durumu sağlanır.
Sonuç olarak O(t3) olur.

III.	DENEYSEL SONUÇLAR

Bu projede sıklıkla Geometri ve Matematik uygulamaları kullanıldı ve bir çok sonuç elde edildi.Elde edilen sonuçların doğruluğunu test etmek amacıyla veriler görselleştirerek, kontrol edilip bu modellerin çıktılarıyla kıyaslanarak kendi test yöntemlerimizi oluşturduk. Test edilen sonuçlar ekran çıktılarıyla kesinleşti.





IV.	SONUÇ

Bu projede arayüz tasarım kütüphaneleriyle tanıştık.Ekip çalışması ile proje yönetimi yeteneğimizi geliştirdik. Projede, algoritma oluşturmaya ve kod yazmaya dair tecrübeye sahip olduk. Teşekkür ederiz.

V.	KAYNAKÇA

(1)https://tr.wikipedia.org/wiki/Code::Blocks 
(2)http://cs.rkmvu.ac.in/~shreesh/media/mec.pdf 
(3)https://en.wikipedia.org/wiki/Smallest-circle_problem
