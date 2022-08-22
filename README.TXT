Para poder compilar el documento, poner en la terminal 
g++ grafica.cpp $(pkg-config --libs gtk+-3.0 --cflags cairo) fparser/fparser.cc
Para esto es necesario instalar la libreria cairo y gtk. Desde la terminal se puede hacercon las siguientes lineas: 
sudo apt-get install libcairo2-dev
sudo apt-get install libgtk-3-dev
Luego, para correr el archivo, el código recibe 3 cosas desde argumentos, 
a, b y func
a y b es el intervalo donde se evaluara la función y func es la función que evaluara en ese intervalo. 
Para evitar problemas de división entre 0, el programa calcula el valor máximo y mínimo de la función en [a,b] y si la diferencia entre esos valores es mayor que 10^{-8}, solo dibujara una linea horizontal. 
Por otro lado, si se desea incluir multiplicación o paréntesis en la función a evualar, como por ejemplo: 
sin(10x) ó 1/(x+1)
se deberan poner de la siguiente forma sin\(10*x\) y 1/\(x+1\)
Cuando cheque en la documentación, no parecia que habia problemas con los paréntesis, por lo que desconozco si es algo de mi computadora ó si es necesario escribirlo de esa forma. 
