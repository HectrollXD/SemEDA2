# Sistema de administración de productos.
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
    ./bin/admin_system < ./files/registros.txt
```

# Nota importante:
Esta rama está destinada unicamente para prueba de ejecución con redireccionamiento de datos de un archivo de texto hacia un ejecutable.
Por ende, cuando el buffer de redireccionamiento de datos termine de leer el archivo este mustra el menú, pero, como el programa fue
abierto de esta manera, el programa querrá seguir leyendo datos del buffer del archivo; este al terminar, solo se cicla y no se es
posible utilizar el programa.

Así que no se espera que este prototipo funcione.
