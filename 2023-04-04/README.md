# Упражнение 7

### Двоични файлове и указатели (динамино заделена памет)

Нека имаме следния тип:

```cpp
struct Book {
    int serialNumber;
    char *title;

    // Евентуално други полета, конструктори и т.н ...
};
```

Какъв е проблемът със следните фрагменти код? Как да го коригираме?

```cpp
std::ofstream fout("my_books.bin", std::ios::out | std::ios::binary);
if (!fout) {
    std::cerr << "Could not open file for writing!" << std::endl;
    return 1;
}

Book b{1234, "The Sun Also Rises"};
fout.write((char *)&b, sizeof(b));
```

```cpp
std::ifstream fin("my_books.bin", std::ios::in | std::ios::binary);
if (!fin) {
    std::cerr << "Could not open file for reading!" << std::endl;
    return 1;
}

Book b;
fin.read((char *)&b, sizeof(b));
```


### Масиви от указатели. _"Плитко"_ и _"Дълбоко"_ копиране

Разгледайте следните фрагменти код. Какво ще се случи във всеки от тях? Кои методи/конструктори ще се извикат?

```cpp
Book myBook{1234, "The Sun Also Rises"};
Book yourBook = myBook;
```

```cpp
Book *myBook = new Book{1234, "The Sun Also Rises"};
Book *yourBook = myBook;
```

```cpp
Book *myBook = new Book{1234, "The Sun Also Rises"};
Book yourBook = *myBook;
```

```cpp
Book *myBooks = new Book[10];
Book *yourBooks = myBooks;
```

```cpp
Book myBooks[10];
Book yourBooks[10] = myBooks;
```

```cpp
Book *myBooks[10];
Book *yourBooks[10] = myBooks;
```

```cpp
Book *myBooks[10];
Book *yourBooks[10];

for(size_t i = 0; i < 10; i++) {
    yourBooks[i] = myBooks[i];
}
```

```cpp
Book *myBooks[10];
Book *yourBooks[10];

for(size_t i = 0; i < 10; i++) {
    yourBooks[i] = new Book{*myBooks[i]};
}
```

1. _"Плитко"_ копиране: Копираме първия _указател_ във втория. Извиква се _copy конструктора_ на типа `Т*`. Накрая и двата указателя сочат към _**един и същ**_ обект (памет). Ако имаме два масива от указатели, това се случва за всеки от елементите на масивите.

_**Пример**_:
```cpp
Book *myBooks[10];
Book *yourBooks[10];

for(size_t i = 0; i < 10; i++) {
    yourBooks[i] = myBooks[i];
}
```

2. _"Дълбоко"_ копиране: копираме _**обекта**_, към който сочи първия указател във втория. Извиква се _copy конструктора_ на типа `T`. Накрая двата указателян сочат към два _**различни**_ обекта, всеки от който е копие на другия. Отново, когато имаме два масива от указатели, това се случва за всеки от елементите на масивите.

_**Пример**_:
```cpp
Book *myBooks[10];
Book *yourBooks[10];

for(size_t i = 0; i < 10; i++) {
    yourBooks[i] = new Book{*myBooks[i]};
}
```


### Задачи:

1. Искаме да имплементираме сериализация (писане) и десериализация (четене) за типа `Book`, дефиниран по-горе. За целта:

1.1. Отворете файла `book.hpp`, и имплементирайте следните методи:
  - `Book(std::istream& in)`: конструктор, който прочита една книга от входния поток `in`.
  - `void save(std::ostream& out) const`: метод, който записва една книга на изходния поток `out` в двоичен формат.

1.2. [Домашно]: Довършете каноничното представяне на класа `Book`.

1.3. Тествайте вашето решение, като довършите файловете:
  - `save_books.cpp`: който записва 5 книги във файла `my_books.bin`
  - `read_books.cpp`: който прочита книгите то файла `my_books.bin` и ги отпечатва на конзолата.


2. Довършете зад. 2 от предното упражнение.
