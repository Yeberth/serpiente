# Serpiente

Juego de la serpiente desarrollado en C++ usando Qt 5, Qt Widgets y Qt Multimedia.

## Características

- Movimiento automático de la serpiente.
- Control con las teclas de dirección.
- Fruta generada aleatoriamente.
- Puntuación: 1 punto por cada fruta.
- Banner con tiempo de juego y puntos.
- Colisiones contra los bordes y contra el propio cuerpo.
- Pantalla de `Game Over`.
- Efectos de sonido para:
  - cambiar de dirección;
  - comer fruta;
  - perder la partida;
  - música ambiental.

## Requisitos

- CMake 3.16 o superior.
- Compilador compatible con C++17.
- Qt 5 con los módulos:
  - Qt Widgets
  - Qt Multimedia

En Linux Mint/Ubuntu se pueden instalar las dependencias con:

```bash
sudo apt update
sudo apt install cmake g++ qtbase5-dev \
    qtmultimedia5-dev libqt5multimedia5-plugins \
    gstreamer1.0-qt5 gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good gstreamer1.0-libav
```

## Compilar en Linux

Desde la carpeta del proyecto:

```bash
cmake -S . -B build
cmake --build build -j2
```

El ejecutable se genera en:

```text
build/ventana_qt
```

## Ejecutar en Linux

```bash
./build/ventana_qt
```

Los archivos de audio se copian automáticamente a `build/audio/` durante la compilación.

## Compilar en Windows

Instala:

- Qt 5 con Qt Widgets y Qt Multimedia.
- CMake.
- Visual Studio o Visual Studio Build Tools con C++.

Abre un símbolo del sistema de Qt o agrega `windeployqt` al `PATH`. Después define la ruta de Qt:

```bat
set QT_PREFIX_PATH=C:\Qt\5.15.2\msvc2019_64
```

Ejecuta:

```bat
compilar_windows.bat
```

El script configura el proyecto, compila en modo `Release` y ejecuta `windeployqt` para copiar las DLL y plugins de Qt.

El ejecutable se genera en:

```text
build-windows\Release\ventana_qt.exe
```

## Controles

| Tecla | Acción |
| --- | --- |
| Flecha arriba | Mover hacia arriba |
| Flecha derecha | Mover hacia la derecha |
| Flecha abajo | Mover hacia abajo |
| Flecha izquierda | Mover hacia la izquierda |

La serpiente no puede girar directamente en sentido contrario a su movimiento actual.

## Audio

Los archivos de audio se encuentran en la carpeta `audio/`:

```text
audio/
├── ambient.wav
├── buttom.wav
├── eat.wav
└── Gunshot1.wav
```

El programa busca los archivos en la carpeta `audio/` situada junto al ejecutable.

Si los sonidos no se reproducen, comprueba que:

1. La carpeta `audio/` exista junto al ejecutable.
2. Qt Multimedia esté instalado.
3. Los plugins de GStreamer estén disponibles.
4. El sistema tenga un dispositivo de salida de audio activo.

## Estructura del proyecto

```text
.
├── audio/              # Archivos de sonido
├── CMakeLists.txt      # Configuración de CMake
├── compilar_windows.bat
├── main.cpp            # Punto de entrada
├── Serpiente.cpp       # Lógica y dibujo del juego
├── Serpiente.h
├── Ventana.cpp         # Configuración de la ventana
└── Ventana.h
```

## Licencia y créditos

Proyecto educativo de ejemplo desarrollado en C++ y Qt.

Los créditos de los audios corresponden a sus respectivos autores y fuentes originales.
