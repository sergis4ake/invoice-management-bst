# invoice-management-bst
Invoice management practice with binary search tree data structure using C++ language.


## Objetivo
El objetivo de esta práctica es implementar un programa en C++ que permita gestionar las facturas de un taller mecánico.

## Implementación
En la presente práctica se debe modelar el comportamiento del sistema de gestión de facturas teniendo en cuenta las siguientes consideraciones:

* Cada una de las fichas personales de modelará como un nodo de un Árbol Binario de Búsqueda.
* Las búsquedas se realizarán por el número de DNI del cliente.
* El historial de reparaciones será dinámico, pudiendo haber clientes con una sola reparación o clientes con múltiples reparaciones.
* Para ello, cada una de las reparaciones se modelará como una lista dinámica, donde cada uno de los nodos será una reparación concreta.
* Respecto a los datos de cada ficha:
   * El Número de Historial se generará de forma correlativa.
   * El Nombre y apellidos se generará de forma aleatoria como una única cadena de texto.
   * El Número de DNI será de 8 dígitos y se generará de forma aleatoria.
   * El número de reparaciones se elegirá aleatoriamente, siendo un número entre 1 y 5, ambos incluidos.
   * Del mismo modo, los datos de cada una de las reparaciones se generarán de forma aleatoria.
* El número inicial mínimo de clientes será de 7.
* El sistema debe permitir la visualización de las fichas de los clientes de forma similar a lo mostrado en el ejemplo.
