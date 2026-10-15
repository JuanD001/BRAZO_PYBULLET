<div align="center">

# 🤖 BRAZO_PYBULLET

### Control de un brazo robótico simulado en PyBullet mediante un ESP32-S3

Firmware de adquisición de datos analógicos en tiempo real (ESP32-S3) más simulación del brazo robótico en PyBullet a partir de un modelo URDF.

![ESP32-S3](https://img.shields.io/badge/Board-ESP32--S3-blue?style=for-the-badge&logo=espressif)
![PlatformIO](https://img.shields.io/badge/IDE-PlatformIO-orange?style=for-the-badge&logo=platformio)
![Framework](https://img.shields.io/badge/Framework-Arduino-00979D?style=for-the-badge&logo=arduino)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Activo-success?style=for-the-badge)

</div>

---

## 📑 Tabla de Contenidos

- [Descripción](#-descripción)
- [Demostración](#-demostración)
- [Características](#-características)
- [Arquitectura del sistema](#️-arquitectura-del-sistema)
- [Hardware requerido](#️-hardware-requerido)
- [Conexiones](#-conexiones-pinout)
- [Estructura del proyecto](#-estructura-del-proyecto)
- [Instalación y puesta en marcha](#-instalación-y-puesta-en-marcha)
- [Configuración](#️-configuración)
- [Formato de salida](#-formato-de-salida)
- [Simulación en PyBullet](#-simulación-en-pybullet)
- [Solución de problemas](#-solución-de-problemas)
- [Hoja de ruta](#-hoja-de-ruta)
- [Contribuir](#-contribuir)
- [Licencia](#-licencia)
- [Autor](#-autor)

---

## 📖 Descripción

**BRAZO_PYBULLET** es un sistema de control de un brazo robótico simulado. Un **ESP32-S3** lee dos potenciómetros que actúan como controladores de las articulaciones y envía las lecturas por puerto serial en formato CSV. Un script en Python recibe esos datos y mueve las articulaciones del modelo **URDF** dentro de **PyBullet**, de forma que girar un potenciómetro físico mueve el brazo virtual en tiempo real.

El repositorio se divide en dos partes:

| Módulo | Carpeta | Tecnología |
| :--- | :--- | :--- |
| **Firmware** | [`firmware/`](firmware) | ESP32-S3, Arduino, PlatformIO |
| **Simulación** | [`simulation/`](simulation) | Python, PyBullet, URDF |

## 🏗️ Arquitectura del sistema

```text
 ┌─────────────┐   ADC    ┌───────────┐  Serial CSV   ┌──────────────────┐
 │ Potenciómetros ├────────► ESP32-S3  ├──────────────► Script Python    │
 │  (POT1, POT2)│          │ (firmware)│  pot1,pot2    │ (pyserial)       │
 └─────────────┘          └───────────┘               └────────┬─────────┘
                                                               │ ángulos
                                                      ┌────────▼─────────┐
                                                      │ PyBullet + URDF  │
                                                      │ (brazo simulado) │
                                                      └──────────────────┘
```

## 📹 Demostración

<!-- Reemplaza TU_ID_DE_VIDEO por el ID de tu video de YouTube, o sustituye este bloque por un GIF: ![Demo](docs/demo.gif) -->

[![Demostración del proyecto](https://img.youtube.com/vi/TU_ID_DE_VIDEO/maxresdefault.jpg)](https://www.youtube.com/watch?v=TU_ID_DE_VIDEO)

> 💡 Haz clic en la imagen para ver el sistema en funcionamiento.

## ✨ Características

- ⏱️ **Lectura en tiempo real:** muestreo de los sensores cada 50 ms (≈ 20 Hz).
- 📊 **Resolución de 12 bits:** valores de 0 a 4095 por canal.
- 📡 **Salida CSV simple:** formato `pot1,pot2`, fácil de parsear desde cualquier lenguaje.
- 🔌 **Compatible con PlatformIO:** compilación y carga con un solo clic.
- 🧩 **Fácil de extender:** pensado para añadir más articulaciones o sensores.

## 🛠️ Hardware requerido

| Componente | Especificación |
| :--- | :--- |
| **Microcontrolador** | ESP32-S3 DevKitC-1 |
| **Sensores** | 2 × potenciómetros lineales (10 kΩ recomendado) |
| **Conexión** | Cable USB con soporte de datos |

## 🔌 Conexiones (Pinout)

| Componente | Pin ESP32-S3 | Descripción |
| :--- | :--- | :--- |
| **Potenciómetro 1** | `GPIO 4` | Lectura analógica de la articulación 1 |
| **Potenciómetro 2** | `GPIO 5` | Lectura analógica de la articulación 2 |
| **Alimentación** | `3V3` / `GND` | Extremos de cada potenciómetro |

```text
        3V3 ──────┬──────────────┐
                  │              │
              ┌───┴───┐      ┌───┴───┐
              │  POT1 ├─GPIO4│  POT2 ├─GPIO5
              └───┬───┘      └───┬───┘
                  │              │
        GND ──────┴──────────────┘
```

> ⚠️ **Importante:** alimenta los potenciómetros con **3.3 V**, nunca con 5 V. Los pines ADC del ESP32-S3 no toleran más de 3.3 V.

## 📁 Estructura del proyecto

```text
BRAZO_PYBULLET/
├── firmware/                     # Código del ESP32-S3
│   ├── src/
│   │   └── main.cpp              # Lectura ADC y envío serial
│   └── platformio.ini            # Configuración de PlatformIO
├── simulation/                   # Simulación en PyBullet
│   ├── urdf/                     # Modelo URDF y mallas del brazo
│   ├── requirements.txt          # Dependencias de Python
│   └── main.py                   # Script que une serial y PyBullet
├── docs/                         # Imágenes, esquemas y GIFs
├── BRAZO_URDF.code-workspace     # Espacio de trabajo de VS Code
├── .gitignore
├── LICENSE
└── README.md
```

> 📝 Ajusta los nombres de la carpeta `simulation/` a los archivos reales de tu proyecto.

## 🚀 Instalación y puesta en marcha

### Requisitos previos

- [Visual Studio Code](https://code.visualstudio.com/)
- Extensión [PlatformIO IDE](https://platformio.org/install/ide?install=vscode)
- [Git](https://git-scm.com/)

### Pasos

1. **Clonar el repositorio**

   ```bash
   git clone https://github.com/JuanD001/BRAZO_PYBULLET.git
   cd BRAZO_PYBULLET
   ```

2. **Abrir el proyecto** en VS Code (`BRAZO_URDF.code-workspace` o la carpeta completa). PlatformIO descargará automáticamente la plataforma y las dependencias.

3. **Ajustar el puerto COM** en `firmware/platformio.ini` (ver [Configuración](#️-configuración)).

4. **Compilar y cargar**

   ```bash
   cd firmware
   pio run --target upload
   ```

   O usa el botón **Upload** (➡️) de la barra inferior de PlatformIO.

5. **Abrir el monitor serial**

   ```bash
   pio device monitor
   ```

   O usa el botón **Serial Monitor** (🔌) de la barra inferior de PlatformIO.

## ⚙️ Configuración

### `firmware/platformio.ini`

```ini
[env:esp32-s3-devkitc-1]
platform = espressif32
board = esp32-s3-devkitc-1
framework = arduino
build_flags =
    -DARDUINO_USB_CDC_ON_BOOT=1
    -DARDUINO_USB_MODE=1

monitor_speed = 115200
monitor_port = COM6
upload_port = COM6
```

> **Atención:** cambia `COM6` por el puerto de tu placa (en Linux/macOS será algo como `/dev/ttyUSB0` o `/dev/ttyACM0`). Si omites ambas líneas, PlatformIO intentará detectar el puerto automáticamente.

### Parámetros del firmware (`firmware/src/main.cpp`)

| Parámetro | Valor | Descripción |
| :--- | :--- | :--- |
| `POT1_PIN` | `4` | Pin del potenciómetro 1 |
| `POT2_PIN` | `5` | Pin del potenciómetro 2 |
| Baudrate | `115200` | Velocidad del puerto serial |
| `delay(50)` | 50 ms | Periodo de muestreo |

### 🔀 Nota sobre el puerto serial

El ESP32-S3 DevKitC-1 tiene **dos conectores USB-C**:

| Puerto | Objeto en código | Descripción |
| :--- | :--- | :--- |
| **UART** (chip puente USB-UART) | `Serial0` | Es el que usa actualmente `main.cpp` |
| **USB** (USB nativo) | `Serial` | Con `ARDUINO_USB_CDC_ON_BOOT=1`, `Serial` apunta al USB nativo |

Asegúrate de conectar el cable al puerto que corresponda con el objeto serial usado en el código. Para usar el **USB nativo**, reemplaza `Serial0` por `Serial` en `firmware/src/main.cpp`.

## 📊 Formato de salida

Tras el mensaje de inicio, el firmware envía una línea por muestra con el formato `pot1,pot2`:

```text
ESP32 INICIADO
Lectura de potenciometros:
2048,1024
2050,1022
2045,1025
```

| Campo | Rango | Descripción |
| :--- | :--- | :--- |
| `pot1` | 0 – 4095 | Valor ADC de la articulación 1 |
| `pot2` | 0 – 4095 | Valor ADC de la articulación 2 |

> Las dos primeras líneas son de texto informativo. Al procesar los datos, ignora las líneas que no tengan formato numérico.

## 🎮 Simulación en PyBullet

### Instalación

```bash
cd simulation
python -m venv .venv
.venv\Scripts\activate        # Windows  (Linux/macOS: source .venv/bin/activate)
pip install pybullet pyserial
```

### Ejecución

1. Conecta el ESP32-S3 y cierra el monitor serial de PlatformIO (el puerto solo puede usarlo un programa a la vez).
2. Ajusta `PORT` en el script con tu puerto COM.
3. Ejecuta:

```bash
python main.py
```

### Ejemplo de integración

Esquema básico que lee el puerto serial y mueve dos articulaciones del URDF. Adapta `URDF_PATH` y los índices de articulación (`JOINTS`) a tu modelo:

```python
import time
import math
import serial
import pybullet as p
import pybullet_data

PORT = "COM6"
BAUD = 115200
URDF_PATH = "urdf/brazo.urdf"   # Ruta de tu modelo
JOINTS = [0, 1]                 # Índices de las articulaciones a controlar
ADC_MAX = 4095
ANGLE_RANGE = math.pi           # 0 - 180° en radianes

p.connect(p.GUI)
p.setAdditionalSearchPath(pybullet_data.getDataPath())
p.setGravity(0, 0, -9.81)
p.loadURDF("plane.urdf")
robot = p.loadURDF(URDF_PATH, useFixedBase=True)

with serial.Serial(PORT, BAUD, timeout=1) as ser:
    while p.isConnected():
        line = ser.readline().decode(errors="ignore").strip()
        try:
            values = list(map(int, line.split(",")))
        except ValueError:
            continue  # Ignora líneas de texto o incompletas
        if len(values) != 2:
            continue

        for joint, adc in zip(JOINTS, values):
            angle = adc / ADC_MAX * ANGLE_RANGE
            p.setJointMotorControl2(robot, joint, p.POSITION_CONTROL, targetPosition=angle)

        p.stepSimulation()
        time.sleep(1 / 240)
```

## 🩺 Solución de problemas

| Problema | Posible causa / solución |
| :--- | :--- |
| No aparece el puerto COM | Usa un cable con soporte de datos y revisa el administrador de dispositivos. Instala el driver CP210x si es necesario. |
| No se ve ninguna salida en el monitor | Verifica que el cable esté en el puerto correcto (UART vs USB, ver [nota](#-nota-sobre-el-puerto-serial)) y que el baudrate sea 115200. |
| Error al cargar el firmware | Mantén presionado **BOOT**, pulsa **RESET** y suelta **BOOT** para entrar en modo de descarga. |
| Lecturas inestables o con ruido | Añade un condensador de 100 nF entre el pin del ADC y GND, o promedia varias muestras por software. |
| Valores siempre en 0 o 4095 | Revisa el cableado: el pin central del potenciómetro debe ir al GPIO. |

## 🗺️ Hoja de ruta

- [ ] Filtro de media móvil para suavizar las lecturas
- [ ] Soporte para más articulaciones (hasta 6 GDL)
- [ ] Salida en ángulos o radianes directamente desde el firmware
- [ ] Calibración de los límites de cada articulación
- [ ] Nodo ROS 2 para publicar el estado de las articulaciones
- [ ] Control de servomotores en el brazo físico

## 🤝 Contribuir

Las contribuciones son bienvenidas:

1. Haz un *fork* del repositorio
2. Crea una rama para tu mejora: `git checkout -b feature/mi-mejora`
3. Haz *commit* de tus cambios: `git commit -m "feat: descripción de la mejora"`
4. Sube la rama: `git push origin feature/mi-mejora`
5. Abre un *Pull Request*

## 📄 Licencia

Distribuido bajo la licencia **MIT**. Consulta el archivo [`LICENSE`](LICENSE) para más información.

## 👤 Autor

**JuanD001**

- GitHub: [@JuanD001](https://github.com/JuanD001)

---

<div align="center">

⭐ Si este proyecto te resultó útil, ¡considera darle una estrella en GitHub!

</div>
