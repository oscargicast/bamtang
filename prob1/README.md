# Decidir si un punto esta dentro o fuera de un triángulo.

Para probar tu implementación usarás el siguiente arreglo de números en los que cada linea tiene los 3 vértices de un triángulo ABC en el plano XY (en este orden: _ax, ay, bx, by, cx, cy_)

``` cpp
int g_triangles[] = {
    -677, 830, 861, 74, -193, 456,
    -747, -413, -302, -8, -482, 678,
    -729, -760, 372, 821, -776, 732,
    // ...
    574, -451, 795, -496, -679, 0,
    717, -74, 996, -340, 332, -715,
    800, -902, -34, 1035, 97, 64,
};
```

Descarga el arreglo completo de: [triangles.cpp](http://www.bamtanggames.com/exams/cpp/triangles.cpp) y cópialo en tu programa. Implementar una función que reciba los 3 vertices del triángulo y devuelva verdadero si el punto P(px, py) está completamente dentro del triángulo. Si el punto está en el borde o fuera devolver falso.

Implementar: **IsPointInsideTriangle(ax, ay, bx, by, cx, cy, px, py)** (4 PUNTOS)

Tu programa debe imprimir en pantalla el numero de triángulos del arreglo g_triangles[] que contienen al punto **P(23, 45)**.


## Solución

Compilar y ejecutar **main.cpp**. El resultado es el siguiente:

``` shell
>> ./main
>> 228
```