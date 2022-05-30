##Overview
Should be used as a preprocessor for Zip etc.
##Test
HTML-page:
```
$ curl -s https://putinism.wordpress.com/2021/05/18/zaches/ > zaches.txt
$ kek -c zaches.txt zaches.kek
$ gzip -9k zaches.kek
$ gzip -9k zaches.txt
$ ls -lSr zaches.* # reformatted
       50876 zaches.kek.gz
       55039 zaches.txt.gz
      157000 zaches.kek
      199018 zaches.txt
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
$ gzip -9k short.kek
$ gzip -9k short.txt
$ ls -lSr short.* # reformatted
        396 short.kek.gz
        405 short.txt.gz
        486 short.kek
        699 short.txt
```
Oops, this input was compressible.
