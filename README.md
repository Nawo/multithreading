# Wielowątkowość i współbieżność w C++

## Tematy

01. Teoria Wielowątkowości (multithreading theory)
02. Wątki (threads) - [Test](https://forms.gle/yRATL7rzMfTSnrGa9)
03. Współdzielenie danych (data_sharing) - [Test](https://forms.gle/s517xwB7ZKpMgPTV6)
04. Zmienne warunku (condition_variable) - [Test](https://forms.gle/e9uHQLAcYauHbtPS9)
05. Zmienne atomowe i model pamięci (atomic) - [Test](https://forms.gle/rFtDNbJyiLqe7vef9)
06. Jednokrotne wywołania (call_once) - [Test](https://forms.gle/Vu6bUc5VEtZ69MRr7)
07. Komunikacja jednokierunkowa (future, promise) - [Test](https://forms.gle/v8JvUtaXHNoXe2JGA)
08. Zadania asynchroniczne (async, packaged_task) - [Test](https://forms.gle/AtASJcopK4uFJCSr8)
09. Problemy współbieżności  ----------------┐
10. Współbieżne wzorce projektowe  ---------┼- [Test z 08, 09, 10](https://forms.gle/GctQkxiYmZN4rKGu7)
11. Testowanie programów współbieżnych ---┘

[Ankieta oceniająca trenera - Mateusz Adamski](https://forms.gle/8Nidginm5wURfiFB6)

[Ankieta oceniająca trenera - Łukasz Ziobroń](https://forms.gle/iRmdRgjzp14jdJpu7)

## Prace domowe

### Zadanie 1

- Zagraj w [The Deadlock Empire](https://deadlockempire.github.io) i przejdź wszystkie poziomy :D Screenshot zaliczonych poziomów posłuży za dowód

### Zadanie 2

Napisz równoległą wersję algorytmu std::accumulate, który będzie współbieżnie sumował fragmenty kontenera. Wyniki powinny zostać również zapisane w kontenerze.

- on empty returns init
- calculate number of threads - `hardware_threads = hardware_concurrency()  0 ? hardware_concurrency() : 2`
- divide on blocks according to the number of threads
- create vector of results
- run every thread in parallel
- put results in vector element passed by reference (threads cannot return value)
- join threads
- accumulate results from the result vector
- test on 1M elements and compare with standard std::accumulate
- templatize algorithm on Iterator (depends on container) and type T sually int, double)

<details><summary>Podpowiedź</summary>
<p>
Rozwiązanie znajdziesz w książce *C++ Concurrency in Action, Anthony Williams*, listing 2.8. [Link do mojego rozwiązania opartego na ww](https://github.com/coders-school/multithreading/blob/solutions/homework/02_parallel_accumulate.cpp)
</p>
</details>

### Zadanie 3

Napisz współbieżną wersję algorytmu std::count_if. Zmierz czas działania i napisz testy, pokazujące, że zwraca ona takie same wyniki, jak std::count_if.
Porównaj go dodatkowo z std::count_if z przekazanym dodatkowym parametrem std::execution::par policy z C++17 ;)

### Zadanie 4

Zaimplementuj problem ucztujących filozofów z użyciem wątków i mutexów.

- Każdy filozof ma być kontrolowany przez oddzielny wątek.
- Każdy sztuciec ma być chroniony przez 1 mutex
- Postaraj się o wizualizację problemu na konsoli (np. `F1-  F2  -F3-  F4  |  F5  |` oznacza, że filozof F3 ma oba sztućce, a F1 tylko jeden)
- Strzeż się zakleszczeń
- Pobaw się liczbą filozofów i zobacz czy zmienia się zachowanie programu. Opisz to w komendarzu
- Zadanie dodatkowe: Strzeż się zagłodzenia (starvation). Jest to sytuacja w której przynajmniej 1 wątek z powodu implementacji lub swojego niższego priorytetu nigdy nie dostanie wszystkich wymaganych zasobów. Doimplementuj w tym celu pewien mechanizm, który zapobiegnie zagłodzeniu.

<details><summary>Podpowiedź</summary>
<p>
https://mariusbancila.ro/blog/2017/01/16/dining-philosophers-in-cpp11/
</p><p>
https://mariusbancila.ro/blog/2017/01/20/dining-philosophers-in-c11-chandy-misra-algorithm/
</p>
</details>

### Zadanie 5

- Poszukaj informacji na temat zjawiska nazywanego fałszywym współdzielenim (**false sharing**). Jest to bardzo niemiłe zjawisko, wynikające z architektury współczesnych komputerów, które znacząco spowalnia równoległe wykonywanie programów.
- Napisz/przepisz/skopiuj sobie kawałek kodu, który ma ten problem i zmierz czas działania programu w zależności od wielkości danych wejściowych i liczby wątków
- Napraw problem false sharingu i zmierz czas działania programu również przy różnej wielkości danych wejściowych i liczbie wątków
- Wyciągnij i opisz w komentarzu wnioski jak pisać kod odporny na false sharing :)

<details><summary>Podpowiedź</summary>
<p>
Możesz spróbować zaimplementować algorytm std::fill
</p>
</details>

### Zadanie 6

Zaimplementuj grę w ping-ponga (zadanie `03_ping_pong.cpp` z rozdziału o zmiennych warunku)

- 1 wątek wypisuje "ping" oraz kolejny numer
- 2 wątek wypisuje "pong" oraz kolejny numer
- Zaczyna wątek ping, a kończy zawsze pong. Wątki muszą pracować na przemian. Nie mogą być 2 pingi lub pongi po sobie. Program nie może zakończyć się pingiem, na który nie będzie odpowiedzi – ponga.
- Zakończenie działania programu ma nastąpić albo po wykonanej liczbie odbić albo po limicie czasowym, w zależności które wystąpi pierwsze. Powód zakończenia powinien zostać wyświetlony na ekranie
- Parametry programu:
  - liczba odbić
  - limit czasowy (w sekundach)

### Zadanie 7

Rozwiąż zadania z użyciem `promise` i `future` od Ihora z katalogu [07_future_promise/homework](07_future_promise/homework)

### Zadanie 8

Tak jak w zadaniu 2 - napisz równoległą wersję algorytmu std::accumulate, który będzie współbieżnie sumował fragmenty kontenera, ale użyj w tym celu zadań asynchronicznych

### Zadanie 9 - Przetwarzanie obrazów

Zainstaluj sobie bibliotekę OpenCV - [Instrukcja instalacji](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html)

Przerób algorytmy podane w dokumentacji na ich wielowątkowe wersje:

1. [Wykrywanie wzorców](https://docs.opencv.org/master/de/da9/tutorial_template_matching.html).

    Każdy wątek sprawdza inny wzorzec. Możemy jednocześnie szukać kilku rzeczy na obrazku. Na koniec wyświetl na obrazku miejsca, gdzie wybrane wzorce najbardziej pasowały. Jeden wzorzec może występować w kilku miejscach.

2. [Wykrywanie linii](https://docs.opencv.org/master/dd/dd7/tutorial_morph_lines_detection.html).

    Każdy wątek szuka linii pod innym kątem (0, 30, 45, 60, 90, 120, 135, 150 stopni). Musisz stworzyć odpowiednie maski. Na koniec wyświetl na jednym obrazku znalezione linie - każdy kąt innym kolorem. Możesz też dodać wyszukiwanie okręgów.

---

## Projekt 1: Hardkorowi filozofowie

Zaimplementuj trochę inną wersję [algorytmu ucztujących filozofów](https://pl.wikipedia.org/wiki/Problem_ucztujących_filozofów). Polecam pracę w grupie.

- Chłop zadaje ważne egzystencjalnie pytanie 5 filozofom (wprowadź je z klawiatury)
- Każdy filozof posiada gotowy zestaw 10 odpowiedzi (każdy filozof ma inne odpowiedzi)
- Każdy filozof podczas myślenia ma zaimplementowany inny algorytm obliczający pewne wartości
- Algorytmy filozofów jako parametr wejściowy przyjmują pytanie (`std::string`) oraz odpowiedź (`std::string`) i zwracają liczbę `int`. Jeśli nie masz pomysłu na różne algorytmy oblicz kilkukrotny `std::hash` z zestawu pytanie + odpowiedź.
- Wszyscy filozofowie podczas myślenia korzystają także z bardzo mądrej księgi, która stanowi dla nich inspirację. Wielu filozofów może odczytywać księge jednocześnie. Wartości zapisane w księdze także mogą być brane pod uwagę w algorytmie.
- Każdy filozof musi przemyśleć każdą z 10 swoich odpowiedzi, która stanowi parametr wejściowy do jego algorytmu myślenia.
- Zadania do przemyślenia przez filozofów możesz zaimplementować jako pulę wątków (Thread Pool).
- Każdy filozof, aby przemyśleć pojednynczą odpowiedź musi być najedzony. Nie może więc rozpocząć myślenia bez jedzenia.
- Każdy filozof potrzebuje 2 sztućców, aby móc się najeść. Liczba szućców jest równa liczbie filozofów.
- Każdy filozof po przemyśleniu odpowiedzi zapisuje swoje rozważania w księdze. Tylko 1 filozof na raz może zapisywać rozważania i żaden inny nie może tym momencie korzystać z księgi.
- Przemyślenia w księdze mają następujący format:

    ```cpp
    struct {
        string philosopher,
        string answer,
        int result,
        chrono::duration period,
        bool chosen = false,
    }
    ```

- Żaden filozof nie może się przejeść. Po posiłku musi on poczekać 3 sekundy zanim zacznie kolejny posiłek.
- Jeśli filozof nie jadł przez 20 sekund to umiera śmiercią głodą. Nie dopuść do tego!
- W czasie poszukiwania odpowiedzi, możesz usypiać filozofów. W tym celu musisz z klawiatury podać odpowiednią komendę w czasie działania programu (np. sleep Platon).
- Uśpiony filozof nie może myśleć ani jeść. Umiera on z głodu dopiero po 60 sekundach.
- Uśpionego filozofa można obudzić podając odpowiednią komendę z klawiatury (np. wakeup Platon).
- Na koniec każdy filozof odczytuje odpowiedź która została przez niego wybrana (oblicza max z działań `result * period`). W tym celu musi odczytać księgę, gdyż tam zapisał swoje rozważania. Przy wybranej odpowiedzi ustawia `chosen = true`.

MEGA PODPOWIEDŹ: Pracuj w TDD i używaj Thread Sanitizera :)

## Projekt 2: Wielowątkowy raytracer

[Czym jest ray tracing? - wideo na YT](https://www.youtube.com/watch?v=JdfV2sB-Qcw)
Rozwiń [algorytm śledzenia promieni](https://pl.wikipedia.org/wiki/Śledzenie_promieni), implementując jego współbieżną wersję, która wygeneruje jakąś statyczną scenę i zapisze ją w jako obrazek (najlepiej użyj sceny chessboard).
Możesz wykorzystać [ten kod](http://cosinekitty.com/raytrace/chapter05_cpp_code.html).

- Zaimplementuj współbieżną wersję istniejącego algorytmu
- Podziel obraz na różne sposoby pomiędzy wiele zadań asynchronicznych
  - użyj async, future, promise i/lub packaged_task
- Zbadaj szybkość przetwarzania w zależności od rodzaju podziału (użyj std::chrono)
  - podział na wiersze
  - podział na kolumny
  - podział na prostokąty
- Zbadaj szybkość przetwarzania w zależności od liczby współbieżnych zadań

## Zakończenie

1. [Wypełnij ankietę zadowolenia z kursu](https://forms.gle/6gzPT8PU6cKAY7eg8)
2. [Obserwuj Coders School na LinkedInie](https://www.linkedin.com/company/coders-school/)
3. [Polub Coders School na Facebooku](https://www.facebook.com/szkola.coders.school)
4. Jeśli uważasz, że odwalam dobrą robotę to [skrobnij parę słów na ten temat na FB](https://www.facebook.com/pg/szkola.coders.school/reviews/?ref=page_internal), niech się niesie w świat ;)
5. Zachęcam też do [potwierdzenia moich umiejętności i wystawienia mi rekomendacji na LinkedInie](https://www.linkedin.com/in/lukaszziobron/). Mogę odwdzięczyć się tym samym :)
6. [Zapisz się na newsletter](https://coders.school/#newsletter), jeśli chcesz otrzymywać informacje o przyszłych kursach.
