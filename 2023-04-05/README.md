Компания за отдаване на автомобили под наем трябва да съхранява информация за направените резервации. Напишете програма, която осъществява това, като всички данни се пазят в текстов файл с разширение `*.db`.

Нека системата да може да обработи всяка една от следните команди:

1. Add - добавя нов автомобил в базата данни. Нека при успешно изпълнение на тази команда базата данни също да се актуализира. Всеки автомобил на компанията се описва от следните полета:
  - `id` - уникален идентификационен номер - цяло число
  - `type` - марка на автомобила - символен низ с до 50 символа дължина
  - `year` - година на производство - цяло четирицифрено число
  - `reservations` - списък от резервации за съответния автомобил, всяка от която описана чрез наредена двойка начална и крайна дата във формат `dd/mm/yyyy` (валидни календарни дати, началната винаги е преди крайната или съвпадат).

2. Search - търси автомобил от наличните в компанията по неговото id. Ако такъв автомобил не съществува, нека се изведе подходящо съобщение.

3. Reserve - опитва да резервира автомобил (зададен с неговото id). Ако такъв автомобил не съществува или вече е зает за дадения период (резервациите не могат да съвпадат напълно или частично), да се изведе подходящо съобщение. Ако автомобилът е наличен и свободен, нека резервацията се осъществи. Нека при успешно изпълнение на тази команда базата данни също да се актуализира.

За всички класове да се реализира подходящо канонично представяне, move
семантика, оператори за вход и изход.