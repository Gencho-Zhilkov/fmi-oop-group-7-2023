# Упражнение 8


### [`std::vector<T>`](https://cplusplus.com/reference/vector/vector/)

`std::vector` е динамичен масив  от стандартната библиотека на C++, състоящ се от елементи от произволен тип. Използва се за ефективна работа с последователности от елементи като списъци, масиви или стекове.

`std::vector` позволява добавяне и премахване на елементи, вмъкване и изтриване на елементи на определена позиция, достъпване на елементите му чрез индекс и др. Едно от основните му предимства е, че векторът автоматично разширява или свива размера си според нуждите на програмата. По този начин се избягва необходимостта от експлицитна алокация и деалокация на памет и грешките, идващи от това.

_**N.B.**_ В професионалния C++ `std::vector<T>` използва много по-често, отколкото `Т[]`!

##### _Полезни методи_:

1. Създаване на нов, _празен_ `std::vector`:
    ```cpp
    std::vector<int> vInt;
    std::vector<Rational> vRat;
    std::vector<std::vector<std::string>> vtf;
    ```

2. Създаване на вектор по дадени елементи:
    ```cpp
    std::vector<int> v{1, 2, 3, 4};
    std::vector<int> v2 = {10, 20, 30, 40};
    ```

3. Провекра дали векторът е празен:
    ```cpp
    const bool isEmpty = v.empty();
    ```

4. Брой елементи:
    ```cpp
    const size_t size = v.size();
    ```

5. Достъп до даден елемент:
    ```cpp
    std::cout << v[3];         // връща елемента с индекс 3. Ако има по-малко от 4 елемента, то поведението е "недефинирано".
    std::cout << v.at(3);      // същото като v[3], но хвърля std::out_of_range ако 3 не е валидна позиция!

    std::cout << v.front();     // същото като v[0]
    std::cout << v.back();      // същото като v[v.size() - 1]
    ```

6. Промяна на стойността на дадена позиция:
    ```cpp
    std::vector<int> v = {1, 2, 3, 4};
    v[2] = 7;
    v.at(2) = 7;
    ```

7. Обхождане на вектор елемент по елемент:
    ```cpp
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i] << std::endl;
    }
    ```
    или
    ```cpp
    for (const auto& elem: v) {
        std::cout << elem << std::endl;
    }
    ```
    _**N.B.**_ Двата начина на обхождане водят до един и същ резултат. Вторият се базира на т.нар. _итератори_, за които ще говорите повече в курса по СДП.

8. Добавяне на елемент в края:
    ```cpp
    v.push_back(7);
    ```

9. Премахване на последния елемент:
    ```cpp
    v.pop_back();
    ```

10. Изчистване на съдържанието (премахване на всички елементи):
    ```cpp
    v.clear();    // същото като v = {}; но по-ефикасно
    ```

#### Примери:

1. Сбор на елементите на даден вектор:
    ```cpp
    template <typename T>
    T sum(const std::vector<T>& v) {
        T res = 0;
        for (size_t i = 0; i < v.size(); i ++) {
            res += v[i];
        }
        return res;
    }
    ```

2. Брой повторения на даден елемент в даден вектор:
    ```cpp
    template <typename T>
    size_t countOccurences(const std::vector<T>& v, const T val) {
        size_t res = 0;
        for (size_t i = 0; i < v.size(); i ++) {
            if (v[i] == val) {
                res++;
            }
        }
        return res;
    }
    ```

    **N.B.** Написани по този начин, функциите `sum` и `countOccurences` ще работят за всякакви съответно числени (`int`, `long`, `float`, ...) или сравними (имащи дефиниран оператор `==`) типове.


### [`std::string`](https://cplusplus.com/reference/string/string/)

`std::string` е клас от стандартната библиотека на C++, който се използва за работа със символни низове (текст). Можете да мислите за него като ООП еквивалента на базовия символен низ (`char *`) или като за `std::vector<char>`.

`std::string` поддържа разнообразие от операции като конкатенация, извличане на поднизове, сравнение на низове и манипулация на символи, като тези операции могат да се изпълнят лесно и ефективно. Той е предпочитан за работа пред традиционните (_C-style_) символни низове, тъй като автоматично управлява паметта и по този начин предотвратява повечето грешки, свързани с неправилно управление на паметта или [буферни препълвания](https://en.wikipedia.org/wiki/Buffer_overflow).

_**N.B.**_ В професионалния C++, на практика много по-често се ползва `std::string`, отколкото `char*`!

##### _Полезни методи_:

1. Създаване на нов, _празен_ `std::srting`:
    ```cpp
    std::string str;
    ```

2. `std::string` от символен низ (`const char*`):
    ```cpp
    std::string s1 = "Once upon a time in the west";
    std::string s2{"Once upon a time in the west"};
    ```

3. Проверка дали един string е празен:
    ```cpp
    const bool isEmpty = str.empty();
    ```

4. Методи, връщащи броя символи в string-а:
    ```cpp
    const size_t size = str.size();
    const size_t len = str.length();
    ```
    _**N.B.**_ `size` и `length` са напълно еквивалентни.

5. Достъп до отделни символи:
    ```cpp
    std::cout << str[3];        // връща символа с индекс 3. Ако низа има по-малко от 4 символа, то поведението е "недефинирано".
    std::cout << str.at(3);     // същото като str[3], но хвърля std::out_of_range ако 3 не е валидна позиция!

    std::cout << str.front();   // същото като str[0]
    std::cout << str.back();	// същото като str[str.size() - 1]
    ```
    _**Въпрос**_: Какво ще се случи ако string-ът е празен?

6. Промяна на стойността на дадена позиция:
    ```cpp
    str[3] = 'B';
    str.at(3) = 'N';
    ```

7. Обхождане символ по символ:
    ```cpp
    for (size_t i = 0; i < str.size(); i++) {
        const char c = str[i];
        std::cout << c << std::endl;
    }
    ```
    или
    ```cpp
    for (const char c: str) {
        std::cout << c << std::endl;
    }
    ```
    _**N.B.**_ Двата начина на обхождане водят до един и същ резултат. Вторият се базира на т.нар. _итератори_, за които ще говорите повече в курса по СДП.

8. Добавяне на символи към края на даден string:
    ```cpp
    str.push_back('c');     // добавяне на един символ (char)
    str.append("foo");      // добавяне на std::string или const char*
    str += "foo";           // същото като на горния ред
    str3 = str1 + str2;     // конкатенация на str1 и str2
    ```

9. Премахване на символи от даден стринг:
    ```cpp
    str.pop_back();         // Премахва последния символ
    str.erase(5, 3);        // Започва от позиция 5 и премахва 3 символа
    ```
    _**Въпрос**_: Какво ще се случи ако string-ът е празен?

10. Взимане на под-string (substring) от даден string:
    ```cpp
    const std::string str = "Mamma mia!";
    const std::string subs = str.substr(3, 5);  // Започва от позиция 3 и взима следващите 5 символа
    std::cout << subs << std::endl;             // Ще отпечата: ma mi
    ```

11. Изчистване на съдържанието (нулиране) на string:
    ```cpp
    str.clear();    // същото като str = ""; но по-ефикасно
    ```

12. Pавенство между два string-a:
    ```cpp
    const std::string str1 = "Mamma", str2 = "mia";
    std::cout << "Equal: " << (str1 == str2) << std::endl;
    std::cout << "Not equal: " << (str1 != str2) << std::endl;
    ```
    **N.B.** Операторите `==` и `!=` сравняват съдържанието на двата string-а, не дали са един и същ обект (за разлика от `char*`).

13. Лексикографскo сравнение на два string-a:
    ```cpp
    const int cmp = str1.compare(str2); // <0 ако str1 < str2, 0 ако са равни, >0 ако str2 > str1

    const bool lt = str < str2;         // Дали str1 е лексикографски преди str2
    ```
    **N.B.** Освен `<`, можете да използвате и останалите оператори за сравнение: `<=`, `>=`, `>`.

14. Търсене на под-string (_"needle"_) в даден string (_"haystack"_): `find` връща началния индекс на първото срещане на _"needle"_ или `std::string::npos`, ако _"needle_ не се съдържа в _"haystack"_.
    ```cpp
    const std::string needle = "ma";
    const std::string haystack = "Mamma mia!";

    const size_t pos = haystack.find(needle);
    if (pos != std::string::npos) {
        std::cout << pos << std::endl;  // Ще отпечата 3
    } else {
        std::cout << needle << " not found!" << std::endl;
    }
    ```


### Задачи:

1. **Обединение**: Да се напише функция, която приема два целочислени вектора и връща нов вектор, който съдържа всички числа, които се срещат поне в един от двата вектора.

2. **Сечение:** Да се напише функция, която приема два целочислени вектора и връща нов вектор, който съдържа само тези числа, които се срещат и в двата вектора.

3. Имплементирайте функция, която приема два символни низа (`std::string`) и връща най-дългия общ префикс между тях. Например, ако низовете са `"hello"` и `"heaven"`, то най-дългият общ префикс е `"he"`.

4. Да се напише функция, която приема символен низ (`std::string`) и заменя в него всички срещания на даден символ с друг символ. Например, ако низът е `"Hello world"` и се иска да се замени буквата `'o'` с буквата `'a'`, то резултатът ще бъде `"Hella warld"`.

5. Да се напише функция, която приема парче текст (`std::string`) и връща списък с думите в него (`std::vector<std::string>`). Думите се разделят от интервали, табулации или нови редове.

    **Бонус**: Напишете и функция, която да връша списък с уникалните думи в текста.
