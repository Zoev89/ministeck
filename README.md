ministeck

part
0

00      0
        0
        
000     0
        0
        0

00
00

0   00      00        0 
00  0        0       00 

10 mogelijkheden

string

         0 0 0                 0 0 0
00 00 00 0 0 0 0 0 0 0 0 0 0 0 0 0 0 00 00 00
00 00  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  0 00 00 0
-----------------------------------------------
00 00 00 0 0 0 0 0 0 0 0 0 0 0 0 0 0 00 00 00 0
00 00  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  0 00 00 
         0 0 0                 0 0 0


per strip
totaal 42 vromen
          aantal	kans
enkeltje  2		1/21
tweeje   16             8/21
drietje  12		6/21
vierkant  8		4/21
hoekje    4		2/21

Per kleur en per vorm de overall match bijhouden
24 kleuren
5 vormen
Maar elke vorm heeft meerder orientaties dat zijn totaal
10 orientaties
per pin word een 8x8 data array bijgehouden. Dat zijn
1 + 2*2 + 2*3 + 4 + 4*3 = 27 8x8 arrays
Dus 24 * 27 = 648 arrays
Ik had ook een shape beschrijving los kunnen maken en dan had ik maar
24 * 16 = 384 maar dan kan ik weer moeilijker de statistiek bijhouden
zou eventueel de cv::Mat er alleen uit halen en die 384 keer neerleggen


enkeltje
(0,0) v1
11111111
10000001
10000001
10000001
10000001
10000001
10000001
11111111

tweetje                 tweetje
(0,0) v2    (1,0) v3    (0,0) v4    (0,1) v5
11111111    11111111    11111111    10000001
10000000    00000001    10000001    10000001
10000000    00000001    10000001    10000001
10000000    00000001    10000001    10000001
10000000    00000001    10000001    10000001
10000000    00000001    10000001    10000001
10000000    00000001    10000001    10000001
11111111    11111111    10000001    11111111
                    
drietje                             drietje
(0,0) v2    (1,0) v6    (2,0) v3    (0,0) v4    (0,1) v7    (0,2) v5
11111111    11111111    11111111    11111111    10000001    10000001
10000000    00000000    00000001    10000001    10000001    10000001
10000000    00000000    00000001    10000001    10000001    10000001
10000000    00000000    00000001    10000001    10000001    10000001
10000000    00000000    00000001    10000001    10000001    10000001
10000000    00000000    00000001    10000001    10000001    10000001
10000000    00000000    00000001    10000001    10000001    10000001
11111111    11111111    11111111    10000001    10000001    11111111

vierkant
(0,0) v8    (1,0) v9    (0,1)v10    (1,1)v11
11111111    11111111    10000000    00000001
10000000    00000001    10000000    00000001
10000000    00000001    10000000    00000001
10000000    00000001    10000000    00000001
10000000    00000001    10000000    00000001
10000000    00000001    10000000    00000001
10000000    00000001    10000000    00000001
10000000    00000001    11111111    11111111

0   00      00        0 
00  0        0       00 

hoekje
(0,0) v4    (0,1)v12    (1,1) v3
11111111    10000001    11111111
10000001    10000000    00000001
10000001    10000000    00000001
10000001    10000000    00000001
10000001    10000000    00000001
10000001    10000000    00000001
10000001    10000000    00000001
10000001    11111111    11111111

hoekje
(0,0)v13    (1,0) v3    (0,1) v5
11111111    11111111    10000001
10000000    00000001    10000001
10000000    00000001    10000001
10000000    00000001    10000001
10000000    00000001    10000001
10000000    00000001    10000001
10000000    00000001    10000001
10000001    11111111    11111111

hoekje
(0,0) v2    (1,0)v14    (1,1) v5
11111111    11111111    10000001
10000000    00000001    10000001
10000000    00000001    10000001
10000000    00000001    10000001
10000000    00000001    10000001
10000000    00000001    10000001
10000000    00000001    10000001
11111111    10000001    11111111

hoekje
(0,0) v4    (0,1)v15    (-1,1)v2
11111111    10000001    11111111
10000001    00000001    10000000
10000001    00000001    10000000
10000001    00000001    10000000
10000001    00000001    10000000
10000001    00000001    10000000
10000001    00000001    10000000
10000001    11111111    11111111


v0 is een niet gebruikte variant dus die kunnen we gebruiken om te checken of een plek vrij is
v0    v1    v2    v3    v4    v5    v6    v7    v8    v9    v10   v11   v12   v13   v14   v15
000   111   111   111   111   101   111   101   111   111   100   001   101   111   111   101
000   101   100   001   101   101   000   101   100   001   100   001   100   100   001   001
000   111   111   111   101   111   111   101   100   001   111   111   111   101   101   111

 (x,y) (x,y,width,height)
 
 enkeltje (0,0) vx
 tweetje  (0,0) vx (1,0) vx
 tweetje  (0,0) vx (0,1) vx
 
 x=currentform .=empty c=othercolor or border or al belegt maakt niet uit welke kleur

    c
   c.c 
  c.x.c
   c.c
    c
    
 xx.c
   c
 
 xx
 c.c
  c
   
 x.c
 xc
 
 xc
 x.c
  c
  
  x
c.x
 c

  x
  x
 c.c
  c
  
 xxx
 c.c
  c
    
 x.c
 xc
 x
 
 xc
 x.c
 xc
 
 x
 xc
 x.c
  c
  
 xx.c
 x c
 
 xx
 x.c
  c
  
 xx
 c.c
  c
 
 
  xx.c
  c.c
   c
   
