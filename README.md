# Mapeo conformal sobre imágenes PGM

## Descripción general
Este repositorio reúne el código fuente utilizado para experimentar con transformaciones conformes aplicadas sobre imágenes en formato PGM. Las implementaciones están escritas en C++ y forman parte de los trabajos prácticos de la materia Algoritmos II (Cátedra Calvo), donde se analizan funciones de variable compleja para deformar imágenes en escala de grises preservando la continuidad.

## Estructura del repositorio
- `TP0/`: primera iteración del procesador de imágenes. Lee una imagen PGM, aplica una función compleja seleccionada mediante la opción `-f` y genera una nueva imagen como salida.
- `TP1/`: segunda iteración que introduce un analizador de expresiones y un árbol binario de operaciones para describir funciones más complejas.
- `'Clase complejo'/`: biblioteca auxiliar con la implementación de números complejos utilizada por los trabajos prácticos.
- `Test/`: utilidades y experimentos para validar el parser de expresiones y otras piezas del proyecto.
- Archivos como `Lenna.pgm` y `grid.png` sirven como muestras para ejecutar los programas y visualizar los resultados de las transformaciones.

## Requisitos previos
- Compilador C++ compatible con C++03 o posterior (por ejemplo, `g++`).
- Herramientas básicas de línea de comandos disponibles en sistemas tipo Unix.

## Compilación
Ejecutar el `makefile` correspondiente dentro del directorio del trabajo práctico que se desee compilar. Por ejemplo, para compilar la primera versión del procesador:

```bash
cd TP0
make
```

El binario generado (`main.exe`) quedará disponible en el mismo directorio.

## Uso
Los programas aceptan entrada y salida desde archivos o desde los flujos estándar. Las opciones principales son:

- `-i <ruta>`: establece la imagen PGM de entrada. Utilizar `-` para leer desde `stdin`.
- `-o <ruta>`: define el archivo de salida. Utilizar `-` para escribir en `stdout`.
- `-f <función>`: selecciona la función compleja a aplicar. Los valores permitidos incluyen `z`, `Z` y `exp(z)`.
- `-h`: muestra la ayuda incorporada.

### Ejemplo de ejecución

```bash
./main.exe -i imagenOrigen/Lenna.pgm -o imagenDestino/Lenna_exp.pgm -f exp(z)
```

## Pruebas y validación
El repositorio contiene imágenes de referencia (por ejemplo, `grid.pgm` y `greenranger.pgm`) que permiten verificar visualmente los resultados. También se incluyen archivos de ejemplo bajo `Test/` que ejercitan el analizador de expresiones y el algoritmo de shunting-yard empleado en el segundo trabajo práctico.

## Créditos
El trabajo fue desarrollado por Federico Verstraeten y Jeremías Ignacio Zec bajo la dirección de la cátedra Algoritmos II (Calvo), tal como se documenta en los encabezados de los archivos fuente.
