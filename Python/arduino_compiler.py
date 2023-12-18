import subprocess, os

current_dir = os.path.dirname(__file__)

# Ruta al ejecutable del IDE de Arduino (cambia esto según tu instalación)
arduino_ide_path = r"E:\\Users\\Administrador\\Documents\\arduino_Versiones_comprimidas\\arduino-1.8.13\\arduino_debug.exe"

# Ruta al archivo .ino que deseas compilar
ino_file_path = current_dir + r"\\..\\Proyecto_PINO_V2.4.ino"

# Comando para compilar utilizando el IDE de Arduino
compile_command = [
    arduino_ide_path,
    "--verify",  # Indica al IDE que compile el archivo
    ino_file_path
]
print(compile_command)
print("OUTPUT: ", ino_file_path)
try:
    # Ejecuta el comando de compilación
    subprocess.run(compile_command, check=True, shell=True)
    print("Compilación exitosa.")
except subprocess.CalledProcessError as e:
    print("Error durante la compilación:", e)
