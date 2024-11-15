# ExpoFinder

## Описание задачи

**ExpoFinder** — программа для нахождения показателя экспоненты \(x\) из файла, содержащего 100 тысяч строк, каждая из которых рассчитана с погрешностью по формуле:

i * e^x, (0 < i < 100000)

### Проблема
В ходе вычислений значения были записаны с погрешностями, и требуется восстановить значение \(x\).

### Задачи программы
1. Определить показатель экспоненты \(x\) из большого файла с ошибочными данными.
2. Протестировать алгоритм на нескольких (не менее 3) примерах небольших файлов с точными данными.
3. Реализовать многопоточную обработку с использованием OpenMP.
4. Максимально использовать доступные ресурсы параллелизма и оптимизации компилятора.
5. Построить график зависимости ускорения многопоточной программы от числа потоков


# Документация: Exponent Finder API

## Описание

**Exponent Finder API** — это высокопроизводительное веб-приложение, созданное на базе фреймворка Drogon. Приложение генерирует набор данных, основанный на экспоненциальной функции с шумом, считывает данные из файла, анализирует их и определяет показатель экспоненты с использованием многопоточности (OpenMP).

## Функционал

- Генерация данных, основанных на экспоненциальной функции с заданным показателем.
- Чтение данных из файла.
- Параллельное вычисление показателя экспоненты.
- REST API для вызова обработки данных.
- Фронтенд-страница для взаимодействия с пользователем.

---

## Основные файлы

### `main.cpp`
Запускает приложение Drogon, которое принимает HTTP-запросы на обработку данных и рендеринг страниц. Приложение слушает порт 8848

### `DataController.h` и `DataController.cpp`
Содержат основной функционал обработки данных:
- Генерация данных с заданным показателем экспоненты и шумом.
- Чтение данных из файла.
- Вычисление показателя экспоненты с использованием OpenMP.
- Обработка HTTP-запроса `/processData` для запуска обработки данных.

### `FrontendController.h`
Обслуживает запросы на фронтенд-страницу `/index`.

### `test.cpp`
Содержит тесты для проверки корректности генерации данных и вычисления показателя экспоненты.

---

## API

### Эндпоинты

#### **`GET /processData`**
- **Описание**: Генерирует данные, выполняет их обработку и возвращает результат вычисления экспоненты.
- **Ответ**: JSON-массив с информацией о числе потоков, рассчитанном показателе экспоненты и времени обработки.
- **Пример ответа**:
  ```json
  [
    {
      "threads": 1,
      "exponent": 0.0499,
      "duration": 0.12
    },
    {
      "threads": 2,
      "exponent": 0.0499,
      "duration": 0.08
    }
  ]
  ```
#### **`GET /index`**
- **Описание**: Возвращает HTML-страницу для взаимодействия с пользователем.