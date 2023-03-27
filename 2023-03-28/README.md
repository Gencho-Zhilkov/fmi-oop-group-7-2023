# Упражнение 6


### Преговор за контролно 1.

1. `class`/`struct`.

2. Спецификатори за достъп: `public`/`private`.

3. Деклариране на полета (член-данни) и методи (член-функции).

4. Канонично представяне (Голяма 4-ка).
  - Конструктори: `Complex(double real=0, double imag=0)`, ...
  - _Copy_ конструктор: `Complex(const Complex& that)`
  - Оператор за присвояване: `Complex& operator =(const Complex& that)`
  - Деструктор: `~Complex()`

5. Дефиниция на методи (член-функции) вън от класа:
```cpp
Complex Complex::conjugate() const {
	return Complex{this->real, - this->imag};
}
```

6. Деклариране на `friend` функции и класове:
  - `friend void print(const Rational& r);`
  - `friend class PrettyPrinter;`
  - `friend operator <<(std::ostream& os, const Rational& r);`

7. [Предефиниране на оператори](https://en.cppreference.com/w/cpp/language/operators):
  - Като медоти на класа:
  ```cpp
  	  Complex& operator += (const Complex& c) {
  	  	  real += c.real;
  	  	  imag += c.imag;
  	  	  return *this;
  	  }
  ```
  - Като външна (приятелска) функция:
  ```cpp
  Complex operator +(const Complex& a, const Complex& b) {
  	  return Complex{
  	  	  a.real + b.real,
  	  	  a.imag + b.imag
  	  };
  }
  ```

8. Работа с потоци и файлове (днес и следващия път!):
  - Текстови файлове
  - Бинарни файлове

9. _Move_ семантика:
  - _Move copy_ конструктор: `Complex(Complex&& rval)`
  - _Move_ оператор за присвояване: `Complex& operator =(Complex&& rval)`
  - `std::move`: превръщане нa lvalue в rvalue референция


### Файлове и потоци:

_**Въпроси**_:
1. Каква е разликата между _потоци_ и _файлове_?
2. Каква е разликата между _бинарен_ (_двоичен_) и _текстов_ файл?
3. Какви са предимствата и недостатъците на _бинарните_ спрямо _текстовите_ файлове?

#### Необходими header файлове:
  - [`<iomanip>`](https://cplusplus.com/reference/iomanip/): Манипулатори за форматиране на вход/изход потоци
  - [`<fstream>`](https://cplusplus.com/reference/fstream/): Работа с файлови потоци.
```cpp
#include <iomanip>
#include <fstream>
```

#### Текстови файлове

Съдържанието на файла се интерпретира като последователност от символи (текст). Начинът на работа е доста подобен на този със `std::cin` и `std::cout`: просто заменяте `std::cin`/`std::cout` със съответния файлов поток.

_**Пример 1: Четене от текстов файл**_: Имаме файла `examples/common_words.txt`, който съдържа 1000-та най-често срещани думи в англ. език. Искаме да намерим и отпечатаме най-дългата дума.

- Вариант 1: `const char*`:
```cpp
char currentWord[MAX_LEN], longestWord[MAX_LEN];

// Отваряме файла за четене
std::ifstream fin("common_words.txt");
if (!fin) {
    std::cerr << "Could not open file for reading!" << std::endl;
    return 1;
}

// Четем ред по ред, докато не стигнем до края
while (fin.getline(currentWord, MAX_LEN)) {
	if (strlen(currentWord) > strlen(longestWord)) {
		strcpy(longestWord, currentWord);
	}
}

std::cout << "Longest word = '" << longestWord << std::endl;
```

- Вариант 2: `std::string`
```cpp
std::string currentWord, longestWord;

// Отваряме файла за четене
std::ifstream fin("common_words.txt");
if (!fin) {
    std::cerr << "Could not open file for reading!" << std::endl;
    return 1;
}

// Четем ред по ред, докато не стигнем до края
while (std::getline(fin, currentWord)) {
	if (currentWord.length() > longestWord.length()) {
		longestWord = currentWord;
	}
}

std::cout << "Longest word = '" << longestWord << std::endl;
```

_**Пример 2: Записване в текстов файл**_: Искаме да запишем, с точност 3 знака след десетичната запетая, първите `n` стойности на [хармоничната редица](https://en.wikipedia.org/wiki/Harmonic_series_(mathematics)): $$h(n) = \sum_{i=1}^n {1 \over i}$$
```cpp
// Отваряме файла за писане
std::ofstream fout("harmonic_series.txt");
if (!fout) {
    std::cerr << "Could not open file for writing!" << std::endl;
    return 1;
}

// Слагаме форматирането на 3 знака след десетичната запетая
fout << std::fixed << std::setprecision(3);

double h = 0;
for (int i = 1; i <= n; i++) {
    h += 1. / i;
    fout << h << std::endl;
}
```

### Бинарни (двоични) файлове:

За разлика от текстовите файлове, съдържанието на бинарните файлове **не** се интерпретира по специален начин, а се разглежда просто като поредица от байтове. Обикновено използваме бинарни файлове, когато работим със записи с еднаква големина напр. числа (`int`, `double`, ...), масиви от символи с фиксирана дължина (`char [10]`) или структури.

_**Пример 1: Четене от бинарен файл**_: Имаме файла `examples/numbers.bin`, който съдържа списък от цели числа. Искаме да намерим и отпечатаме средното им аритметично.
```cpp
    std::ifstream fin("ints.bin", std::ios::in | std::ios::binary);
    if (!fin) {
        std::cerr << "Could not open file for reading!" << std::endl;
        return 1;
    }

    int sum = 0, val;
    size_t count = 0;
    while (fin.read((char *)&val, sizeof(val))) {
        sum += val;
        count ++;
    }

    std::cerr << "Count = " << count << std::endl;
    std::cout << "Average = " << (double)sum / count << std::endl;
```

_**Пример 2: Записване в бинарен файл**_: Искаме отново да запишем първите `n` стойности на [хармоничната редица](https://en.wikipedia.org/wiki/Harmonic_series_(mathematics)), но този път в бинарен формат.
```cpp
std::ofstream fout("harmonic_series.bin", std::ios::out | std::ios::binary);
if (!fout) {
    std::cerr << "Could not open file for writing!" << std::endl;
    return 1;
}

double h = 0;
for (int i = 1; i <= n; i++) {
    h += 1. / i;
    fout.write((char *)&h, sizeof(h));
}
```
_**Въпрос**_: Има ли смисъл и възможно ли е вообвще да фиксираме броя на значещите цифри в този случай?


### Читанка:
Няколко статии, който навлизат в повече детайли относно процеса на компилация:

- [C++ Compiler Operation](https://icarus.cs.weber.edu/~dab/cs1410/textbook/1.Basics/compiler_op.html)
- [The C++ Compilation Model](https://subscription.packtpub.com/book/programming/9781789801491/1/ch01lvl1sec03/the-c-compilation-model)
- [Understanding C++ Compilation](https://www.toptal.com/c-plus-plus/c-plus-plus-understanding-compilation)


### Задачи:

1. Имаме текстов файл, който съдържа измерванията на дневната температура на дадено място (напр. НДК или Черни Връх) за период от няколко години. Всеки ред от файла съответства на едно измерване и се състой от две колони, разделени със запетая. Първата от тях е датата на измерването с формат dd/mm/yyyy, а втората измерената температура в градуси Целзий. (Отворете файла `temperature.csv`, за да видите нагледен пример).<br />
За всяка година намерете средно-годишнита температура, минималната и максималната температури, както датите на които са били имерени, а също и броя измервания, който са били направени (може да има липсващи дни). Запишете резултата в CSV файл, т.е. текстов файл състоящ се от разделени със запетая колони, съответно за: година, брой измервания, средна температура, мин. температура, дата на мин. температура (dd/mm/yyyy), макс. температура, дата на макс. температура (dd/mm/yyyy). Всички температури трябва да се запишат с точност два знака след десетичната запетая. (Може да намерите примерен резултат във файла `yearly_stats.csv`).
<br />

2. Нека имаме бинарен файл, който съдържа списък от записи с оценки на различни студенти по различни предмети. Всеки запис се състои от следните 3 полета:
- `studentId`: Факултетен номер на студента.
- `courseId`: Идентификационен номер на курса. Масив от 6 символа.
- `note`: Оценка на дадения студент по дадения предмет. Положително число, 4 байта. <br /><br />
Да се имплементират следните функции:
- `getStudentNotes(studentId)`, която връща всички оценки на даден студент.
- `getCourseNotes(courseId)`, която връща всички оценки по даден предмет.
- `getStudentAverage(studentId)`, която връща средния успех на даден студент.
- `getCourseAverage(courseId)`, която връща средния успех по даден предмет.
