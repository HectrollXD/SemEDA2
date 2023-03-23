# Sistema de administración de productos.
## Descripción
Esta variación del proyecto está destinada a la lectura y escritura de un archivo de texto mediante
el uso del paso de parámetros por consola al momento de ejecutarse.   
Dicho proyecto está basado a la rama ```feature/modular```, y este funciona mediante la lectura de
un archivo linea por linea.

## Compilar programa desde consola.

**Nota:** Los comandos están pensados para compilar y ejecutar en sistemas posix. Si se requiere compilar en el sistema operativo Windows,
solo es necesario cambiar la síntaxis de las rutas: ```/ruta/del/proyecto``` por ```C:\ruta\del\proyecto```.

Asumiendo que se está posicionado en la ruta raíz del proyecto.

Con gcc:
``` bash
    gcc *.cpp -o ./bin/admin_system -lstdc++
```

Con g++:
``` bash
    g++ *.cpp -o ./bin/admin_system
```

## Ejecutar el programa.
Asumiendo que se está posicionado en la ruta raíz del proyecto.
``` bash
    ./bin/admin_system ./files/registros.txt
```
