# Dibuja un tablero de ajedrez

Implementar una función que dibuje un tablero de ajedrez con la posición de las piezas pasada como parámetro. El parámetro a pasar será una cadena compuesta solamente de los siguientes caracteres: *"p, r, b, n, q, k, /, 1, 2, 3, 4, 5, 6, 7, 8"*.

Donde cada pieza es representada por una carácter, siendo las negras caracteres en minúscula y las blancas caracteres en mayúsculas. Los caracteres son:

``` txt
p = peón
r = torre
b = alfil
n = caballo
q = reina
k = rey
```

Para separar las filas dentro de la cadena se emplea el carácter *"/"*, existen exactamente 8 filas en la cadena.

Para indicar espacios vacíos en la fila se colocan los números del 1 al 8. Por ejemplo la fila *"4p3"* esta compuesta por 4 celdas vacías, un peón y finalmente tres celdas vacías El numero de celdas por fila debe ser siempre 8.

Así por ejemplo la posición inicial de ajedrez se representa por:

``` txt
"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"
```

Implementar la función: **DrawChessBoard(initPosition)**

![Chess Board](http://www.bamtanggames.com/exams/cpp/14869.PNG "Chess Board")

Usa cualquier imagen para las piezas así como la librería gráfica que prefieras. Verifica que las imagenes estén ubicadas correctamente para que no hayan problemas al ejecutar tu proyecto. (7 PUNTOS)

## Solución

Dependencias empleadas [GLUT](https://www.opengl.org/resources/libraries/glut/glut_downloads.php), [OpenGL](https://www.opengl.org/) y [SOIL](http://www.lonesock.net/soil.html). En sistemas basados en debian instalarlas del siguiente modo:

``` bash
>> sudo apt-get install freeglut3 freeglut3-dev mesa-common-dev libsoil-dev
```

Compilar y ejecutar **main.cpp** manualmente:

``` bash
>> g++ main.cpp -lGL -lGLU -lglut -lm -lSOIL -o main
```

O usando el archivo Makefile:

``` bash
>> make
```

Finalmente ejecutar el archivo generado el resultado es el siguiente:

``` bash
>> ./main
```

``` bash 
kInitPosition:
rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
Your position is acceptable :)
```

![Output 1](https://raw.githubusercontent.com/oskargicast/bamtang/master/prob4/images/output1.png "Chess Board")

### Modificando la posicion inicial (**kInitPosition**)

[Modificar la constante kInitPosition](https://github.com/oskargicast/bamtang/blob/master/prob4/main.cpp#L19) por alguna entrada valida como la que se aprecia en esta [linea](https://github.com/oskargicast/bamtang/blob/master/prob4/main.cpp#L18). 

Por ejemplo. Si descomentamos la [linea 18](https://github.com/oskargicast/bamtang/blob/master/prob4/main.cpp#L18) obtenemos lo siguiente:

``` bash 
kInitPosition:
7Q/2Rp4/2pN4/p2rp3/P2N4/B1k5/2PpRb2/3K2n1
Your position is acceptable :)
```

![Output 2](https://raw.githubusercontent.com/oskargicast/bamtang/master/prob4/images/output2.png "Chess Board")