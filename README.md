## Overview
Should be used as a preprocessor for Zip etc.
## Test
HTML-page:
```
$ curl -s https://putinism.wordpress.com/2021/05/18/zaches/ > zaches.txt
$ kek -c zaches.txt zaches.kek
$ gzip -9k zaches.kek
$ gzip -9k zaches.txt
$ bzip2 -9k zaches.kek
$ bzip2 -9k zaches.txt
$ brotli zaches.kek
$ brotli zaches.txt
$ ls -lSr zaches.* # reformatted
       45490 zaches.txt.br
       45907 zaches.txt.bz2
       45923 zaches.kek.br
       48008 zaches.kek.bz2
       50875 zaches.kek.gz
       55039 zaches.txt.gz
      156999 zaches.kek
      199018 zaches.txt
```
Japanese:
```
$ curl -s -o wild.txt https://ja.wikipedia.org/wiki/DEATH_STRANDING
$ kek -c wild.txt wild.kek
...
# Running Brotli, GZip, and BZip2
...
$ ls -lSr wild.* # reformatted
       54290 wild.txt.bz2
       55510 wild.txt.br
       57367 wild.kek.br
       59898 wild.kek.bz2
       65754 wild.kek.gz
       69318 wild.txt.gz
      221071 wild.kek
      271425 wild.txt
```
Small files are almost incompressible and will be stored without conversion with just 1 extra byte:
```
$ cat > short.txt
Кекну, а в ответ - тишина.

Едут троллЯйбусы без габаритных огней.
Нижегородцы ночами делают новых зверей.

- Ду ю спик идиш?
- Ноу, ай эм э рашн джу, энд ай эм э пэтриот.
- ?
- Это значит, что я использую тот лэнгуидж, на котором говорит мой хозяин.
  Инглиш, чайниз, москальска мова...
  Надо будет репатриироваться в Изгаиль - выучу иврит.
  Нахряна мне идиш?

Бешмельдэ-шешмельдэ, нащяа-аальника.
$ kek -c short.txt short.kek
...
# Running Brotli, GZip, and BZip2
...
$ ls -lSr short.* # reformatted
         306 short.txt.br
         338 short.txt.bz2
         347 short.kek.br
         396 short.kek.gz
         401 short.kek.bz2
         405 short.txt.gz
         485 short.kek
         699 short.txt
```
Oops, this input was compressible.
## To-do
https://github.com/powturbo/Turbo-Range-Coder/blob/094f749f12b919241c8d3b10e9c610159001956b/rcutil.c#L214-L231
```
//------------- Integer VLC for symbol dictionary coding ----------
#define VB_B2  4  		// 6: max. 4276351=41407f   5: 2171071=2120bf   4:1118431=1110df  3:592111=908ef
#define VB_BA2 (255 - (1<<VB_B2))  

#define VB_OFS1 (VB_BA2 - (1<<VB_B2))
#define VB_OFS2 (VB_OFS1 + (1 << (8+VB_B2)))

#define vbput24(_op_, _x_) { \
  if(likely((_x_) < VB_OFS1)){ *_op_++ = (_x_); } \
  else if  ((_x_) < VB_OFS2) { ctou16(_op_) = bswap16((VB_OFS1<<8)+((_x_)-VB_OFS1));                _op_  += 2; } \
  else                       { *_op_++ = VB_BA2 + (((_x_) -= VB_OFS2) >> 16); ctou16(_op_) = (_x_); _op_  += 2; } \
}

#define vbget24(_ip_, _x_) do { _x_ = *_ip_++;\
       if(likely(_x_ < VB_OFS1));\
  else if(likely(_x_ < VB_BA2))  { _x_ = ((_x_<<8) + (*_ip_)) + (VB_OFS1 - (VB_OFS1 <<  8)); _ip_++;} \
  else                           { _x_ = ctou16(_ip_) + ((_x_ - VB_BA2 ) << 16) + VB_OFS2; _ip_ += 2;}\
} while(0)
```
