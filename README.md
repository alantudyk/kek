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
