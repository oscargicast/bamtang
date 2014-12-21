# Ray Tracing

Sea P un plano (infinito) en el espacio 3D definido por los puntos **P1, P2, P3**.
Sea F una fuente de luz ubicada en el infinito con vector direccion **V**.
Se pide encontrar la sombra **S** sobre el plano P que proyecta el punto **Q** debido a la fuente luminosa F.

![Ray Tracing](http://www.bamtanggames.com/exams/cpp/01.PNG "Ray Tracing")

Implementar la función: **GetShadowPoint(Q, P1, P2, P3, V)**.

Considera crear una clase Vector simplificada para efectuar las operaciones necesarias, ten en cuenta que dependiendo de la direccion de la luz puede no haber sombra. No uses archivos, pedir valores en pantalla e imprimir la respuesta ahi mismo. (5 PUNTOS)