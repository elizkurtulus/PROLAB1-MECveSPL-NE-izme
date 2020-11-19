#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>//Mesaj kutuları vs pencere gerektiren herhangi bir şey için kullanılır
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#define ScreenWidth 2000
#define ScreenHeight 1000
#define prolab "proje.txt"
#define INF 20000
#define ekran 25 //bir birim 25 piksele eşittir.
struct nokta
{
    double x;
    double y;
};
double nokta_uzaklik (struct nokta n1,struct nokta n2)
{
    return sqrt(pow(n1.x-n2.x,2)+pow(n1.y-n2.y,2));
}
double yeni_uzaklik (double n1,double n2)
{
    return sqrt((n1*n1)+(n2*n2));
}
struct nokta merkez_bul(struct nokta a,struct nokta b)
{
    struct nokta merkez;
    merkez.x=(a.x+b.x)/2;
    merkez.y=(a.y+b.y)/2;

    return merkez;
}
void spline_nokta_ciz ( struct nokta p )
{
    double x = ScreenWidth/ 2.0 + ekran * p.x - 2.0;
    double y = ScreenHeight / 2.0 - ekran * p.y - 2.0;
    al_draw_filled_circle ( x, y, 1.0, al_map_rgb (95,179,225));
}
struct nokta spline_hesaplama (float u ,int sayi,struct nokta *dizi)
{
    int p0, p1, p2, p3;

    p1 = ( int ) u;//ağırlık faktörleri
    p2 = ( p1 + 1 )%sayi;
    p3 = ( p2 + 1 )%sayi ;

    if(p1 >= 1)
    {
        p0 =p1 - 1;
    }
    else
    {
        p0=sayi - 1;
    }
    u = u - ( int ) u;//u değerinin 1in üstüne cıkması engelleniyor.

    double af1, af2, af3, af4;
    af1 = (- pow ( u, 3 ) + 2.0 * pow ( u, 2 ) - u);//Ağırlık faktörlerinin matematiksel fonksiyonları
    af2 = 3.0 * pow ( u, 3 ) - 5.0 * pow ( u, 2 ) + 2.0;
    af3 = - 3.0 * pow ( u, 3 ) + 4.0 * pow ( u, 2 ) + u;
    af4 = pow ( u, 3 ) - pow ( u, 2 );

    struct nokta spline;

    spline.x= 0.5 * ( dizi[ p0 ].x * af1 + dizi[ p1 ].x * af2 + dizi[ p2 ].x * af3 + dizi[ p3 ].x * af4 );
    spline.y= 0.5 * ( dizi[ p0 ].y * af1 + dizi[ p1 ].y * af2 + dizi[ p2 ].y * af3 + dizi[ p3 ].y * af4 );


    return spline;
}


int main()
{
    FILE *dosya;

    int sayi=0;
    double f[500];
    double g[500];
    struct nokta listep[500];


    if((dosya=fopen(prolab,"r"))!=NULL)
    {
        while(!feof(dosya))
        {

            fscanf(dosya,"%lf",&f[sayi]);
            listep[sayi].x=f[sayi];
            fscanf(dosya,"%lf",&g[sayi]);
            listep[sayi].y=g[sayi];
            sayi++;
        }

    }

    else
    {
        printf("dosya bulunamadi");
        exit(1);
    }
    fclose(dosya);

    dosya=fopen(prolab,"a");
    if(dosya== NULL)
    {
        printf("Dosya acilmadi!");
        exit(1);
    }


    sayi=sayi-1;
    double r;
    struct nokta m;
    int i,j;

    if(sayi<=3)
    {
        double en_buyuk=0,b;
        struct nokta e1;
        struct nokta e2;

        for(i=0; i<sayi; i++)
        {

            for(j=i+1; j<sayi; j++)
            {
                b=nokta_uzaklik(listep[i],listep[j]);
                if(en_buyuk<b)
                {
                    en_buyuk=b;
                    e1.x=listep[i].x;
                    e1.y=listep[i].y;

                    e2.x=listep[j].x;
                    e2.y=listep[j].y;
                }
            }
        }
        m=merkez_bul(e1,e2);
        r=en_buyuk/2.0;
        fprintf(dosya,"\n");
        fprintf(dosya,"Merkez: {%.2lf,%.2lf}",m.x,m.y);
        fprintf(dosya,"\n");
        fprintf(dosya,"Yaricap: %lf\n",r);

    }
    else if(sayi>3)
    {
        double t,n;
        double merkezx=0,merkezy=0;
        double p=0.1;

        for(i=0; i<sayi; i++)
        {
            merkezx=merkezx+f[i];
            merkezy=merkezy+g[i];
        }
        merkezx=merkezx/sayi;
        merkezy=merkezy/sayi;

        for(i=0; i<INF; i++)
        {
            int k=0;
            t= yeni_uzaklik(merkezx-listep[0].x,merkezy-listep[0].y);

            for(j=1; j<sayi; j++)
            {
                n=yeni_uzaklik(merkezx-listep[j].x,merkezy-listep[j].y);

                if(t<n)
                {
                    t=n;
                    k=j;
                }
            }

            merkezx=merkezx+((listep[k].x-merkezx)*p);
            merkezy=merkezy+((listep[k].y-merkezy)*p);
            p=p*0.9;
        }
        m.x=merkezx;
        m.y=merkezy;
        r=t;
        fprintf(dosya,"\n");
        fprintf(dosya,"Merkez: {%.2lf,%.2lf}",m.x,m.y);
        fprintf(dosya,"\n");
        fprintf(dosya,"Yaricap: %lf\n",r);
    }

    fclose(dosya);


    ALLEGRO_DISPLAY * display;
    ALLEGRO_EVENT_QUEUE *queue;
    al_init();//Bu kodla derleyiciye allegro kütüphanesini kullanacağımız bildirmiş oluyoruz.



    display =al_create_display(ScreenWidth, ScreenHeight);

    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    queue = al_create_event_queue();
    al_install_keyboard();//Bu kodu kullanarak klavyeyi yazılımda kullanılabilir hale getiririz.
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));


    al_init_primitives_addon();

    al_init_font_addon();
    al_init_ttf_addon();
    ALLEGRO_FONT *font=al_load_font("arial.ttf",12,NULL);


    for ( float i = 0.000; i < ( float )sayi; i += 0.001 )
    {
        spline_nokta_ciz( spline_hesaplama(i,sayi,listep));
    }


    for(int i=0; i<40; i++)
    {
        al_draw_textf (font, al_map_rgb (255, 255, 255),(ScreenWidth/2)+(((ScreenWidth/2)/40)*i),(ScreenHeight/2)+2, ALLEGRO_ALIGN_CENTER, "%d",i);//+x ekseni sayıları
    }
    for(int i=0; i<40; i++)
    {
        al_draw_textf (font, al_map_rgb (255, 255, 255),(ScreenWidth/2)+4,(ScreenHeight/2)+(25*i)-2, ALLEGRO_ALIGN_LEFT, "-%d",i);//-y ekseni sayıları
    }
    for(int i=0; i<40; i++)
    {
        al_draw_textf (font, al_map_rgb (255, 255, 255),(ScreenWidth/2)+4,(ScreenHeight/2)+(-25*i), ALLEGRO_ALIGN_LEFT, "%d",i);//+y ekseni sayıları
    }

    for(int i=0; i<40; i++)
    {
        al_draw_textf (font, al_map_rgb (255, 255, 255),(ScreenWidth/2)+(-25*i),(ScreenHeight/2)+2, ALLEGRO_ALIGN_CENTER, "-%d",i);//-x ekseni sayıları
    }

    for(int i=0; i<ScreenWidth; i+=5)
    {
        al_draw_line((0+(5*i)),0,(0+(5*i)),ScreenHeight, al_map_rgb(42,42,42), 1.0);//y ekseni arkaplan cizgisi
    }
    for(int i=0; i<ScreenHeight; i+=5)
    {
        al_draw_line(0,(0+(5*i)), ScreenWidth,(0+(5*i)), al_map_rgb(42,42,42), 1.0);//x ekseni arkaplan cizgisi
    }

    ALLEGRO_FONT *a=al_load_font("arial.ttf",20,NULL);

    al_draw_textf(a, al_map_rgb(255, 255, 255), ScreenWidth-20,(ScreenHeight/2)-500, ALLEGRO_ALIGN_RIGHT, "Yaricap: %f", r );        //ekrana yarıcap yazdırma
    al_draw_textf(a, al_map_rgb(255, 255, 255), ScreenWidth-20,(ScreenHeight/2)-480, ALLEGRO_ALIGN_RIGHT, "X: %f", m.x );         //Merkez x noktası
    al_draw_textf(a, al_map_rgb(255, 255, 255), ScreenWidth-20,(ScreenHeight/2)-460, ALLEGRO_ALIGN_RIGHT, "Y: %f", m.y );         //Merkez y noktası






    al_draw_circle(((ScreenWidth / 2)+(m.x*25)), ((ScreenHeight / 2)+(-m.y*(25))), r*25, al_map_rgb(172,16,224), 4);//daire

    al_draw_line(0, (ScreenHeight / 2)+2, ScreenWidth, (ScreenHeight / 2)+2, al_map_rgb(184,171,179), 3.0);//x ekseni
    al_draw_line((ScreenWidth / 2)+1,0,(ScreenWidth / 2)+1, ScreenHeight, al_map_rgb(184,171,179), 3.0);//y ekseni

    for(int i=0; i<sayi; i++)
    {
        al_draw_filled_circle((ScreenWidth/2)+(listep[i].x*25),(ScreenHeight/2)+(listep[i].y*-25),6,al_map_rgb(255,100, 177));//Klavyeden girilen noktalar

    }


    al_draw_line((ScreenWidth/2)+(m.x*25),(ScreenHeight/2)+(m.y*-25),(ScreenWidth/2)+(m.x*25)+(r*25),(ScreenHeight/2)+(m.y*-25)+(r-1*25),al_map_rgb(69,55,238), 3.0);
    al_draw_filled_circle((ScreenWidth/2)+(m.x*25),(ScreenHeight/2)+(m.y*-25),8,al_map_rgb(172,16,224));//Çember merkezi

    for (int i = 0; i < ScreenWidth; i+=25)
    {
        al_draw_line(i,(ScreenHeight/2)-4, i, (ScreenHeight/2)+4, al_map_rgb(192,192,192), 1.0);//X ekseni sayı çubukları
    }
    for (int j = 0; j < ScreenHeight; j +=25)
    {
        al_draw_line((ScreenWidth/2)-4, j, (ScreenWidth/2)+4, j, al_map_rgb(184,171,179), 1.0);//Y ekseni sayı çubukları
    }



    dosya =fopen(prolab,"r");

    if(dosya== NULL)
    {
        printf("Dosya acilmadi!");
        exit(1);
    }
    char c;

    while(!feof(dosya))
    {
        c=fgetc(dosya);
        printf("%c",c);
    }

    fclose(dosya);





    bool running = true;
    while (running)
    {
        al_flip_display();
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_KEY_UP || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            running = false;
    }
    al_destroy_display(display);
    al_uninstall_keyboard();
    return 0;
}
