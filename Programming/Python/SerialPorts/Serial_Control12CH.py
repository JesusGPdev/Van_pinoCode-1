import tkinter as tk
from PIL import Image, ImageTk
import time, os, serial, threading

class Communication_App(tk.Tk):
  def __init__(self, puerto_serial, velocidad_serial):
    super().__init__()

    self.puerto_serial = puerto_serial
    self.velocidad_serial = velocidad_serial
    self.read_serial_time = 100
    self.images_cases = ["pg_CL.png", "pch_CL.png",
                         "pg_OpG.png","pg_OpD.png",
                         "pch_OpG.png","pch_OpD.png",
                         "r_D.png","r_Moving.png","r_I.png",
                         "Puertas_cases"]
    self.sensor_state = [False]*6
    self.inicializar_interface()

  def inicializar_interface(self):
    self.title("SENSORS")
    self.geometry("620x600")

    self.bind("<Key>", self.handle_key_event)
    self.serial_socket = serial.Serial(self.puerto_serial, self.velocidad_serial, timeout=2)
    # self.after(self.read_serial_time, self.read_serial)
    self.images_dir = os.path.dirname(os.path.realpath(__file__)) + "\\..\\Images_cases\\"

    # --------------------------------------------------------------------------------- Buttons
    self.turn_on_OUT13 = tk.Button(self, text="Turn ON OUT 13",
                                  command=lambda: self.Turn_on_led("ON_13"),
                                  bg="#FE8282", width=16)
    self.turn_on_OUT13.pack(pady=10)
    self.turn_on_OUT13.place(x=5, y=5)
    self.turn_off_OUT13 = tk.Button(self, text="Turn OFF OUT 13",
                                  command=lambda: self.Turn_off_led("OFF_13"),
                                  bg="#D66C6C", width=16)
    self.turn_off_OUT13.pack(pady=10)
    self.turn_off_OUT13.place(x=140, y=5)
    self.turn_on_OUT12 = tk.Button(self, text="Turn ON OUT 12",
                                    command=lambda: self.Turn_on_led("ON_12"),
                                    bg="#0CEC6B", width=16)
    self.turn_on_OUT12.pack(pady=10)
    self.turn_on_OUT12.place(x=5, y=35)
    self.turn_off_OUT12 = tk.Button(self, text="Turn OFF OUT 12",
                                    command=lambda: self.Turn_off_led("OFF_12"),
                                    bg="#8BD66C", width=16)
    self.turn_off_OUT12.pack(pady=10)
    self.turn_off_OUT12.place(x=140, y=35)
    self.turn_on_OUT11 = tk.Button(self, text="Turn ON OUT 11",
                                  command=lambda: self.Turn_on_led("ON_11"),
                                  bg="#82C0FE", width=16)
    self.turn_on_OUT11.pack(pady=10)
    self.turn_on_OUT11.place(x=5, y=65)
    self.turn_off_OUT11 = tk.Button(self, text="Turn OFF OUT 11",
                                    command=lambda: self.Turn_off_led("OFF_11"),
                                    bg="#6CA1D6", width=16)
    self.turn_off_OUT11.pack(pady=10)
    self.turn_off_OUT11.place(x=140, y=65)
    self.turn_on_OUT10 = tk.Button(self, text="Turn ON OUT 10",
                                  command=lambda: self.Turn_on_led("ON_10"),
                                  bg="#EEE408", width=16)
    self.turn_on_OUT10.pack(pady=10)
    self.turn_on_OUT10.place(x=5, y=95)
    self.turn_off_OUT10 = tk.Button(self, text="Turn OFF OUT 10",
                                  command=lambda: self.Turn_off_led("OFF_10"),
                                  bg="#CFC605", width=16)
    self.turn_off_OUT10.pack(pady=10)
    self.turn_off_OUT10.place(x=140, y=95)
    self.turn_on_OUT9 = tk.Button(self, text="Turn ON OUT 9",
                                    command=lambda: self.Turn_on_led("ON_9"),
                                    bg="#F979F7", width=16)
    self.turn_on_OUT9.pack(pady=10)
    self.turn_on_OUT9.place(x=5, y=125)
    self.turn_off_OUT9 = tk.Button(self, text="Turn OFF OUT 9",
                                    command=lambda: self.Turn_off_led("OFF_9"),
                                    bg="#DF31DC", width=16)
    self.turn_off_OUT9.pack(pady=10)
    self.turn_off_OUT9.place(x=140, y=125)
    self.turn_on_OUT8 = tk.Button(self, text="Turn ON OUT 8",
                                  command=lambda: self.Turn_on_led("ON_8"),
                                  bg="#F8A446", width=16)
    self.turn_on_OUT8.pack(pady=10)
    self.turn_on_OUT8.place(x=5, y=155)
    self.turn_off_OUT8 = tk.Button(self, text="Turn OFF OUT 8",
                                    command=lambda: self.Turn_off_led("OFF_8"),
                                    bg="#E28215", width=16)
    self.turn_off_OUT8.pack(pady=10)
    self.turn_off_OUT8.place(x=140, y=155)
    # --------------------------------------------------------------------------------- Labels
    # Red
    self.label_OUT13_status = tk.Label(self, text="S3_q", bg= "#000000", width=4,
                                       fg="white", font="Arial 12 bold")
    # self.label_OUT13_status.pack(pady=10)
    self.label_OUT13_status.place(x=280, y=5)

    self.label_OUT12_status = tk.Label(self, text="S4_w", bg= "#000000", width=4,
                                       fg="white", font="Arial 12 bold")
    # self.label_OUT12_status.pack(pady=10)
    self.label_OUT12_status.place(x=280, y=35)

    self.label_OUT11_status = tk.Label(self, text="S1_e", bg= "#000000", width=4,
                                       fg="white", font="Arial 12 bold")
    # self.label_OUT11_status.pack(pady=10)
    self.label_OUT11_status.place(x=280, y=65)

    self.label_OUT10_status = tk.Label(self, text="S2_r", bg= "#000000", width=4,
                                       fg="white", font="Arial 12 bold")
    # self.label_OUT10_status.pack(pady=10)
    self.label_OUT10_status.place(x=280, y=95)

    self.label_OUT9_status = tk.Label(self, text="S6_t", bg= "#000000", width=4,
                                       fg="white", font="Arial 12 bold")
    # self.label_OUT9_status.pack(pady=10)
    self.label_OUT9_status.place(x=280, y=125)

    self.label_OUT8_status = tk.Label(self, text="S5_y", bg= "#000000", width=4,
                                       fg="white", font="Arial 12 bold")
    # self.label_OUT8_status.pack(pady=10)
    self.label_OUT8_status.place(x=280, y=155)

    self.label_dat_received = tk.Label(self, text="Received Data: ")
    # self.label_dat_received.pack(pady=10)
    self.label_dat_received.place(x=90, y=195)

    

  def handle_key_event(self, event):
    serial_data=""
    if event.char.lower() == 'w': # <<--- Keyboard Button
      if self.sensor_state[0] == False:
        serial_data = "ON_13"
        self.sensor_state[0] = True
      else:
        serial_data = "OFF_13"
        self.sensor_state[0] = False
    elif event.char.lower() == 'q':# <<--- Keyboard Button
      if self.sensor_state[1] == False:
        serial_data = "ON_12"
        turn_on = True
        self.sensor_state[1] = True
      else:
        serial_data = "OFF_12"
        self.sensor_state[1] = False
    elif event.char.lower() == 's':# <<--- Keyboard Button
      if self.sensor_state[2] == False:
        serial_data = "ON_11"
        self.sensor_state[2] = True
      else:
        serial_data = "OFF_11"
        self.sensor_state[2] = False
    elif event.char.lower() == 'a':# <<--- Keyboard Button
      if self.sensor_state[3] == False:
        serial_data = "ON_10"
        self.sensor_state[3] = True
      else:
        serial_data = "OFF_10"
        self.sensor_state[3] = False
    elif event.char.lower() == 'z':# <<--- Keyboard Button
      if self.sensor_state[4] == False:
        serial_data ="ON_9"
        self.sensor_state[4] = True
      else:
        serial_data ="OFF_9"
        self.sensor_state[4] = False
    elif event.char.lower() == 'x':# <<--- Keyboard Button
      if self.sensor_state[5] == False:
        serial_data ="ON_8"
        self.sensor_state[5] = True
      else:
        serial_data ="OFF_8"
        self.sensor_state[5] = False
    else:
      serial_data = "NONE"

    if serial_data == "NONE":
      print("Button unknown")
    else:
      self.compare_data_received(serial_data)
      self.image_case_simulator(self.sensor_state)
      self.enviar_comando(serial_data)

  def image_case_simulator(self, number_string):
    print(number_string)

  def Turn_on_led(self, communication_num):
    print("ON, Sending: ", communication_num)
    self.enviar_comando(communication_num)
    
  def Turn_off_led(self,communication_num):
    print("OFF, Sending: ", communication_num)
    self.enviar_comando(communication_num)
  

  def enviar_comando(self, comando):
    try:
        self.serial_socket.write(comando.encode('utf-8'))
        # ser.close()
    except Exception as e:
        print(f"Error al enviar el comando: {e}")

  def read_serial(self):
    serial_data = ""
    try:
      serial_data = self.serial_socket.readline().decode('utf-8').strip()
      print("Received Data: ", serial_data)
      self.label_dat_received.config(text=f"Received Data: {serial_data}")
    except:
      print("Exception occurred, something wrong...")
    # self.after(self.read_serial_time, self.read_serial)
    self.compare_data_received(serial_data)

  def compare_data_received(self, serial_data):
     if serial_data == "ON_13":
        self.label_OUT13_status.config(bg="#FF0000", fg="black",
                                       font="Arial 12 bold")
     elif serial_data == "OFF_13":
        self.label_OUT13_status.config(bg="#000000", fg="white",
                                       font="Arial 12 bold")
     elif serial_data == "ON_12":
        self.label_OUT12_status.config(bg="#0CEC6B", fg="black",
                                       font="Arial 12 bold")
     elif serial_data == "OFF_12":
        self.label_OUT12_status.config(bg="#000000", fg="white",
                                       font="Arial 12 bold")
     elif serial_data == "ON_11":
        self.label_OUT11_status.config(bg="#82C0FE", fg="black",
                                       font="Arial 12 bold")
     elif serial_data == "OFF_11":
        self.label_OUT11_status.config(bg="#000000", fg="white",
                                       font="Arial 12 bold")
     elif serial_data == "ON_10":
        self.label_OUT10_status.config(bg="#FFF300", fg="black",
                                       font="Arial 12 bold")
     elif serial_data == "OFF_10":
        self.label_OUT10_status.config(bg="#000000", fg="white",
                                       font="Arial 12 bold")
     elif serial_data == "ON_9":
        self.label_OUT9_status.config(bg="#FF00FB", fg="black",
                                       font="Arial 12 bold")
     elif serial_data == "OFF_9":
        self.label_OUT9_status.config(bg="#000000", fg="white",
                                       font="Arial 12 bold")
     elif serial_data == "ON_8":
        self.label_OUT8_status.config(bg="#FF8700", fg="black",
                                       font="Arial 12 bold")
     elif serial_data =="OFF_8":
        self.label_OUT8_status.config(bg="#000000", fg="white",
                                       font="Arial 12 bold")
     else:
      print("Serial data unknown", serial_data)

class Control_app(tk.Tk):
  def __init__(self, puerto_serial_control, velocidad_serial_control):
    super().__init__()
    self.puerto_serial_control = puerto_serial_control
    self.velocidad_serial_control = velocidad_serial_control
    self.ctrl_switch = [False]*13
    self.init_control_interface()
  
  def init_control_interface(self):
    self.title("CONTROL")
    self.geometry("620x600")
    self.serial_control_socket = serial.Serial(self.puerto_serial_control, 
                                               self.velocidad_serial_control, timeout=2)
    # self.bind("<key>", self.handle_key_event_control)
    #------------------------------Buttons------------------------------------
    self.cntrl_bttn_1 = tk.Button(self, text="B_1", # -------------------------- BTN_1
                                  command=lambda: self.create_send_command(1),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=5, y=5)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_2", # -------------------------- BTN_2
                                  command=lambda: self.create_send_command(2),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=85, y=5)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_3", # -------------------------- BTN_3
                                  command=lambda: self.create_send_command(3),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=5, y=65)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_4", # -------------------------- BTN_4
                                  command=lambda: self.create_send_command(4),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=85, y=65)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_5", # -------------------------- BTN_5
                                  command=lambda: self.create_send_command(5),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=5, y=125)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_6", # -------------------------- BTN_6
                                  command=lambda: self.create_send_command(6),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=85, y=125)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_7", # -------------------------- BTN_7
                                  command=lambda: self.create_send_command(7),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=5, y=185)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_8", # -------------------------- BTN_8
                                  command=lambda: self.create_send_command(8),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=85, y=185)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_9", # -------------------------- BTN_9
                                  command=lambda: self.create_send_command(9),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=5, y=245)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_10", # -------------------------- BTN_10
                                  command=lambda: self.create_send_command(10),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=85, y=245)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_11", # -------------------------- BTN_11
                                  command=lambda: self.create_send_command(11),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=5, y=305)
  
    self.cntrl_bttn_1 = tk.Button(self, text="B_12", # -------------------------- BTN_12
                                  command=lambda: self.create_send_command(12),
                                  bg="#9FE3EF", width=5, font="bold 10 bold")
    self.cntrl_bttn_1.pack(pady=10)
    self.cntrl_bttn_1.place(x=85, y=305)
  
  # This function is to handle events through keyboard
  # def handle_key_event_control(self, event_control):

  def create_send_command(self, command_case):
    command_string = "BTN"
    # --------------------------------------------------------- BTN_OFF
    # self.ctrl_switch[command_case] = False
    command_string = command_string + "_" + str(command_case)
    self.send_command(command_string)
    print(command_string)
    # time.sleep(1)
    command_string = "BTN"
    # --------------------------------------------------------- BTN_ON
    # self.ctrl_switch[command_case] = True
    # command_string = command_string + "_OFF_" + str(command_case)
    # print(command_string)
    # self.send_command(command_string)

  def send_command(self, command_to_send):
    try:
      self.serial_control_socket.write(command_to_send.encode('utf-8'))
    except Exception as e:
      print(f"Error sending command {e}")

if __name__ == "__main__":
  puerto_serial = 'COM4'  # COM system device
  puerto_serial_control = 'COM8'  # COM system device
  velocidad_serial = 115200  # Data rate to communicate with Arduino

  # app = Communication_App(puerto_serial, velocidad_serial)
  # app.mainloop()
  app_control= Control_app(puerto_serial_control, velocidad_serial)
  app_control.mainloop()

