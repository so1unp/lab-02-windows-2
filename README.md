[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Y1zgDfeF)
# Laboratorio 2 - Llamadas al Sistema

En este laboratorio vamos a trabajar con llamadas al sistema relacionadas con el manejo de archivos y creación de procesos. Además, se verá la implementación de las llamadas al sistema operativo _xv6_.

Las respuestas a las preguntas planteadas en los ejercicios deben ser entregadas en un archivo PDF en el campus virtual (máximo de dos carillas, respetando el template).

## Ejercicio 1: Interprete de comandos

El programa `sh.c` es un interprete de comandos (en inglés generalmente denominado _shell_). Sin embargo, no tiene implementada la funcionalidad de ejecución de programas o de redirección de entrada/salida. Cuando se ejecuta imprime un símbolo de sistema (`$`) y queda a la espera de que el usuario ingrese un comando. Se puede terminar su ejecución con `^C`.

### 2.1: Ejecución de comandos

Implementar la ejecución de comandos. El programa genera una estructura `execcmd` que contiene el comando a ejecutar y sus parámetros (si los hubiera). 

- Implementar la ejecución de comandos completando el caso `EXEC` en la función `runcmd()`. Usar la llamada a sistema [`exec()`](http://man7.org/linux/man-pages/man3/exec.3.html).
- Se debe imprimir un mensaje de error si `exec()` falla utilizando la función [`perror()`](http://man7.org/linux/man-pages/man3/perror.3.html).

### 2.2: Redirección de E/S

Implementar redirección de E/S mediante los operadores `<` y `>`, de manera que el _shell_ permita ejecutar comandos como:

```console
$ echo "sistemas operativos" > so.txt
$ cat < so.txt
sistemas operativos
$
```

El parser implementado en el _shell_ ya reconoce estos operadores y genera una estructura `redircmd` con los datos necesarios para implementar la redirección.

- Completar el código necesario en el caso `REDIR` de la función `runcmd()`.
- Consultar las llamadas al sistema [`open()`](http://man7.org/linux/man-pages/man2/open.2.html) y [`close()`](http://man7.org/linux/man-pages/man2/close.2.html).
- Imprimir un mensaje de error si alguna de las llamadas al sistema falla, utilizando [`perror()`](http://man7.org/linux/man-pages/man3/perror.3.html).
- Verificar los permisos con los que se crea el archivo en caso de la redirección de salida (`>`).

### 2.3: Shell de xv6
El repositorio `xv6` contiene el código de _xv6_, un sistema operativo muy sencillo basado en UNIX. Parados en dicho repositorio pueden ejecutarlo utilizando la maquina virtual *QEMU* mediante el comando `make qemu`. Debe aparecer una ventana con algo similar a lo siguiente: 

```console
Booting from Hard Disk..xv6...
cpu0: starting 0
sb: size 1000 nblocks 941 ninodes 200 nlog 30 logstart 2 inodestart 32 bmap start 58
init: starting sh
$
```

Si ejecutamos un comando como `ls` veremos un error, ya que no está implementada la ejecución de comandos:
```console
$ ls
exec not implemented
$
```

Para terminar la ejecución de QEMU, presionar `C^A x` (esto es, `Ctrl+A` y luego la tecla `x`).

Implementar la ejecución de comandos y la redirección de entrada/salida, usando el código del ejercicio anterior.

## Ejercicio 2: Traza de llamadas al sistema

### Traza de llamadas al sistema en Linux
Ejecutar el programa `sum.c` del Laboratorio 1 mediante el comando `strace` como se indica a continuación, para obtener las llamadas al sistema que invoca durante su ejecución:

**Caso 1**: usando argumentos
```console
$ strace bin/sum 1 2 3 > /dev/null
```

**Caso 2**: leyendo desde la entrada estándar
```console
$ echo "1 2 3" | strace bin/sum > /dev/null
```

**Nota**: `> /dev/null` redirije la _salida estándar_ de `bin/sum` al archivo especial del sistema `/dev/null`, que descarta todo lo que se escriba en el mismo. De esta manera evitamos que la salida del comando `sum` se mezcle con la de `strace`.

Responder:

1. ¿Cuantas llamadas al sistema invoca el programa en cada caso?
2. Identificar las funciones en el código de `sum.c` que invocan llamadas al sistema.
3. Describir los parámetros que utiliza la llamadas al sistema identificadas.

### Traza de llamadas al sistema en xv6
El programa `trace.c` en _xv6_ activa o desactiva la traza de llamadas al sistema: imprime por la salida estándar las llamadas al sistema que son invocadas por los programas en ejecución. Al pasarle `1` como parámetro, activa la traza. Para desactivarla, se utiliza el parámetro `0`.

Por ejemplo, al ejecutar `trace 1` deberían tener una salida similar a la siguiente:
```console
$ trace 1
[27] sys_sctrace: 0
[3] sys_wait: 6
$[16] sys_write: 1
 [16] sys_write: 1
```

Luego, cuando se ejecuta un programa, se imprimiran las llamadas al sistema que este invoque.

Responder:

1. Ejecutar el comando `echo hola`. Explicar por que se invocan las llamadas al sistema que se presentan en la traza.

## Ejercicio 3 - Implementar una nueva llamada al sistema en xv6

En este ejercicio vamos a modificar el _kernel_ de _xv6_ para agregar una **nueva llamada al sistema** que retorne al usuario el número **42** (el sentido de la vida, el universo y todo lo demás).

Como referencia, utilizar la guía de implementación de la llamada al sistema `sys_trace` del ejercicio anterior, que se encuentra en la carpeta `doc` de `xv6`.

Se deben modificar los siguientes archivos de _xv6_:

- `usys.S`: mecanismo de invocación de una llamada al sistema desde el nivel de usuario.
- `user.h`: prototipos de las funciones de biblioteca para el usuario.
- `syscall.h`: identificadores de cada una de las llamadas al sistema.
- `syscall.c`: código que invoca la llamadas al sistema dentro del _kernel_.
- `sysproc.c`: aquí implementaremos la llamada al sistema, aunque podría estar en cualquier otro archivo `.c`.

El programa `answer.c` invoca la llamada al sistema e imprime el resultado (el número `42`). El código donde se invoca la llamada al sistema esta comentado dado que no existe aún dicha llamada.

Una vez que la hayan implementado, descomentar el código correspondiente en el programa, recompilar y ejecutar nuevamente _xv6_ para verificar que se invoque correctamente la nueva llamada al sistema.

---

¡Fin del Laboratorio 2!
