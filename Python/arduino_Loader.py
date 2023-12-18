import serial
import time

def cargar_programa(archivo_hex, puerto_serial, velocidad_serial):
    try:
        # Inicializar la conexión serie
        ser = serial.Serial(puerto_serial, velocidad_serial, timeout=5)

        # Esperar a que Arduino se reinicie después de abrir la conexión
        time.sleep(2)

        # Leer el archivo HEX y enviarlo a Arduino
        with open(archivo_hex, 'rb') as f:
            for line in f:
                ser.write(line)

        # Cerrar la conexión
        ser.close()
        print("Programa cargado exitosamente en Arduino.")
    except Exception as e:
        print(f"Error al cargar el programa: {e}")

# Configuración
archivo_hex = 'ruta/al/archivo.hex'  # Ruta al archivo HEX generado por el compilador de Arduino
puerto_serial = 'COM3'  # Cambiar al puerto correcto en tu sistema (puedes encontrarlo en el IDE de Arduino)
velocidad_serial = 115200  # Velocidad de comunicación serial, ajustar según sea necesario

# Llamar a la función para cargar el programa en Arduino
cargar_programa(archivo_hex, puerto_serial, velocidad_serial)
