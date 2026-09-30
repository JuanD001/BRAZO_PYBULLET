# 🤖 Brazo_ESP32 - Interfaz de Control de Brazo Robótico

![ESP32-S3](https://img.shields.io/badge/Board-ESP32--S3-blue?style=for-the-badge&logo=espressif)
![PlatformIO](https://img.shields.io/badge/IDE-PlatformIO-orange?style=for-the-badge&logo=platformio)
![Framework](https://img.shields.io/badge/Framework-Arduino-00979D?style=for-the-badge&logo=arduino)

Este repositorio contiene el firmware desarrollado para un sistema de adquisición de datos en tiempo real mediante un microcontrolador **ESP32-S3**. El proyecto lee señales analógicas de potenciómetros para el control e interacción de articulaciones de un brazo robótico (modelo de simulación URDF).

---

## 📹 Demostración en Video

*(Reemplaza el siguiente enlace con la URL de tu video de YouTube o sube un GIF del funcionamiento)*

[![Demostración del Proyecto](https://img.youtube.com/vi/TU_ID_DE_VIDEO/maxresdefault.jpg)](https://www.youtube.com/watch?v=TU_ID_DE_VIDEO)

> 💡 **Nota:** Haz clic en la imagen superior para ver el video completo del sistema en funcionamiento.

---

## 📌 Características Principales

* **Lectura en tiempo real:** Muestreo de sensores analógicos a intervalos regulares de 50 ms.
* **USB CDC Nativo:** Transmisión de datos serial directa por el puerto USB integrado del ESP32-S3 (`CDC ON BOOT`).
* **Formato Estándar CSV:** Envío continuo de lecturas en formato `pot1,pot2` para facilitar su integración con motores de simulación, ROS (Robot Operating System) o interfaces gráficas.

---

## 🛠️ Hardware Requerido

| Componente | Especificación / Modelo |
| :--- | :--- |
| **Microcontrolador** | ESP32-S3 DevKitC-1 |
| **Sensores** | 2 Potenciómetros lineales (10kΩ recomendado) |
| **Conexión USB** | Cable USB-C a USB-A/C con soporte de datos |

### 🔌 Diagrama de Pines (Pinout)

| Componente | Pin del ESP32-S3 | Descripción |
| :--- | :--- | :--- |
| **Potenciómetro 1 (POT1)** | `GPIO 4` | Lectura analógica articulación 1 |
| **Potenciómetro 2 (POT2)** | `GPIO 5` | Lectura analógica articulación 2 |
| **Alimentación** | `3.3V` / `GND` | VCC y masa compartida para los sensores |

---

## 📁 Estructura del Proyecto

```text
Brazo_ESP32/
├── src/
│   └── main.cpp             # Código fuente principal (lectura ADC y puerto serial)
├── platformio.ini           # Configuración del entorno PlatformIO y compilación
└── BRAZO_URDF.code-workspace# Espacio de trabajo para VS Code
```

---

## 💻 Configuración de Software y Compilación

El proyecto utiliza **PlatformIO** sobre **Visual Studio Code**.

### Archivo `platformio.ini`
Se incluye la configuración para habilitar el puerto USB nativo durante el arranque:

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

> **Atención:** Ajusta los parámetros `upload_port` y `monitor_port` con el puerto COM asignado a tu placa en tu sistema operativo.

---

## 🚀 Instalación y Puesta en Marcha

1. **Clonar el repositorio:**
   ```bash
   git clone https://github.com/TU_USUARIO/Brazo_ESP32.git
   cd Brazo_ESP32
   ```

2. **Abrir en VS Code:**
   Abre la carpeta del proyecto en Visual Studio Code con la extensión de **PlatformIO** instalada.

3. **Compilar y Cargar:**
   * Conecta tu ESP32-S3 vía USB.
   * Presiona el botón de **Upload** (flecha a la derecha en la barra inferior de PlatformIO).

4. **Monitor Serial:**
   * Abre el monitor serial a **115200 baudios**.
   * Verás la salida continua de datos en formato separado por comas:
     ```text
     ESP32 INICIADO
     Lectura de potenciometros:
     2048,1024
     2050,1022
     2045,1025
     ```

---

## 📄 Licencia

Este proyecto se distribuye bajo la licencia MIT. Consulta el archivo `LICENSE` para obtener más información.
