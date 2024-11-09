# import tkinter as tk
# import serial
# import time

# class Aplicacion(tk.Tk):
#     def __init__(self, puerto_serial, velocidad_serial):
#         super().__init__()

#         self.puerto_serial = puerto_serial
#         self.velocidad_serial = velocidad_serial

#         self.inicializar_interfaz()

#     def inicializar_interfaz(self):
#         self.title("Control de LED")

#         self.boton_encender = tk.Button(self, text="Encender LED", command=self.encender_led)
#         self.boton_encender.pack(pady=10)

#         self.boton_apagar = tk.Button(self, text="Apagar LED", command=self.apagar_led)
#         self.boton_apagar.pack(pady=10)

#     def encender_led(self):
#         self.enviar_comando("ON")

#     def apagar_led(self):
#         self.enviar_comando("OFF")

#     def enviar_comando(self, comando):
#         try:
#             ser = serial.Serial(self.puerto_serial, self.velocidad_serial, timeout=2)
#             ser.write(comando.encode())
#             ser.close()
#             print(comando)
#         except Exception as e:
#             print(f"Error al enviar el comando: {e}")

# if __name__ == "__main__":
#     puerto_serial = "COM4"  # Cambiar al puerto correcto en tu sistema
#     velocidad_serial = 9600  # Ajustar según la velocidad de comunicación en tu código de Arduino

#     app = Aplicacion(puerto_serial, velocidad_serial)
#     app.mainloop()

import time
import sys
from pymata4 import pymata4

"""
Setup a pin for digital input and monitor its changes
Both polling and callback are being used in this example.
"""

# Setup a pin for analog input and monitor its changes
DIGITAL_PIN = 10  # arduino pin number
POLL_TIME = 5  # number of seconds between polls

# Callback data indices
# Callback data indices
CB_PIN_MODE = 0
CB_PIN = 1
CB_VALUE = 2
CB_TIME = 3


def the_callback(data):
    """
    A callback function to report data changes.
    This will print the pin number, its reported value and
    the date and time when the change occurred

    :param data: [pin, current reported value, pin_mode, timestamp]
    """
    date = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(data[CB_TIME]))
    print(f'Pin: {data[CB_PIN]} Value: {data[CB_VALUE]} Time Stamp: {date}')


def digital_in(my_board, pin):
    """
     This function establishes the pin as a
     digital input. Any changes on this pin will
     be reported through the call back function.

     :param my_board: a pymata_express instance
     :param pin: Arduino pin number
     """

    # set the pin mode
    my_board.set_pin_mode_digital_input(pin, callback=the_callback)

    while True:
        try:
            # Do a read of the last value reported every 5 seconds and print it
            # digital_read returns A tuple of last value change and the time that it occurred
            value, time_stamp = my_board.digital_read(pin)
            date = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time_stamp))
            # value
            print(f'Polling - last value: {value} received on {date} ')
            time.sleep(POLL_TIME)
        except KeyboardInterrupt:
            board.shutdown()
            sys.exit(0)

board = pymata4.Pymata4()

try:
    digital_in(board, DIGITAL_PIN)
except KeyboardInterrupt:
    board.shutdown()
    sys.exit(0)
