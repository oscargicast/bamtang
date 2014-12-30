# Ray Tracing

Sea P un plano (infinito) en el espacio 3D definido por los puntos **P1, P2, P3**.
Sea F una fuente de luz ubicada en el infinito con vector direccion **V**.
Se pide encontrar la sombra **S** sobre el plano P que proyecta el punto **Q** debido a la fuente luminosa F.

![Ray Tracing](http://www.bamtanggames.com/exams/cpp/01.PNG "Ray Tracing")

Implementar la función: **GetShadowPoint(Q, P1, P2, P3, V)**.

Considera crear una clase Vector simplificada para efectuar las operaciones necesarias, ten en cuenta que dependiendo de la dirección de la luz puede no haber sombra. No uses archivos, pedir valores en pantalla e imprimir la respuesta ahi mismo. (5 PUNTOS)

## Solución

Compilar y ejecutar **main.cpp**. El resultado es el siguiente:

``` bash
>> ./main
```

``` txt
 ========== Enter Q ==========
Qx = -2
Qy = 0
Qz = 4
========== Enter P1 ==========
P1x = 0
P1y = 0
P1z = 11
========== Enter P2 ==========
P2x = 3
P2y = 6
P2z = 35
========== Enter P3 ==========
P3x = 0
P3y = 1
P3z = 14
========== Enter V ==========
Vx = -3
Vy = 1
Vz = -2

========== Summary ==========
Q: (-2, 0, 4)
P1: (0, 0, 11)
P2: (3, 6, 35)
P3: (0, 1, 14)
V: (-3, 1, -2)

++++++++++ I'm exist! :) ++++++++++
S: (-11, 3, -2)

Enter [c] to continue or [q] to quit
c


========== Enter Q ==========
Qx = 1
Qy = 1
Qz = 1
========== Enter P1 ==========
P1x = 0
P1y = 1
P1z = 0
========== Enter P2 ==========
P2x = 1
P2y = 2
P2z = 0
========== Enter P3 ==========
P3x = 4
P3y = 8
P3z = 0
========== Enter V ==========
Vx = 0
Vy = 0
Vz = -1

========== Summary ==========
Q: (1, 1, 1)
P1: (0, 1, 0)
P2: (1, 2, 0)
P3: (4, 8, 0)
V: (0, 0, -1)

++++++++++ I'm exist! :) ++++++++++
S: (1, 1, 0)

Enter [c] to continue or [q] to quit
c

========== Enter Q ==========
Qx = 1
Qy = 1
Qz = 1
========== Enter P1 ==========
P1x = 0
P1y = 1
P1z = 0
========== Enter P2 ==========
P2x = 1
P2y = 2
P2z = 0
========== Enter P3 ==========
P3x = 4
P3y = 8
P3z = 0
========== Enter V ==========
Vx = 0
Vy = 0
Vz = 1

========== Summary ==========
Q: (1, 1, 1)
P1: (0, 1, 0)
P2: (1, 2, 0)
P3: (4, 8, 0)
V: (0, 0, 1)

++++++++++ I don't have shadow :( ++++++++++

Enter [c] to continue or [q] to quit
q

```