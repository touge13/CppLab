*до разбиения на хедеры и адаптацию проекта под cmake все запускалось с командой*

cd "/Users/admin/Desktop/work/С++/graf_laboratory4_cpp/src/" && g++ -std=c++11 main.cpp -o main && "/Users/admin/Desktop/work/С++/graf_laboratory4_cpp/src/"main

*на данный момент под macOS Monterey 12.6.7 в Visual Studio Code при попытке запуска main.cpp командой выше выдает ошибку (под виндой все запускается кстати):*

admin@MacBook-ProMisa graf_laboratory4_cpp % cd "/Users/admin/Desktop/work/С++/graf_laborato
ry4_cpp/src/" && g++ main.cpp -o main && "/Users/admin/Desktop/work/С++/graf_laboratory4_cpp
/src/"main
Undefined symbols for architecture x86_64:
  "createImage(int, std::__1::vector<Edge, std::__1::allocator<Edge> >)", referenced from:
      _main in main-e58e77.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)

*но зато проект запускается при помощи cmake. шило на мыло. видимо вся беда в операционке/ide/стандарте языка/прочих тонкостях железа*

при запуске надо указать путь на файл с входными данными ../conversion/input.txt

во входных данных, где лежит ребро между первой и второй вершиной:
/количество вершин\ /количество ребер\
/номер первой вершины\ /номер второй вершины\

пример input файла можно посмотреть перейдя по следующему пути:
../conversion/input.txt

 
