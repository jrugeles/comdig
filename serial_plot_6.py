import sys
import serial
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import numpy as np
import pyqtgraph as pg


class SerialPlot(QWidget):

    def __init__(self):
        super().__init__()

        # Configuración de la ventana principal
        self.setWindowTitle("Lectura de puerto serial")
        self.setGeometry(0, 0, 800, 600)

        # Configuración del gráfico
        self.graphWidget = pg.PlotWidget(self)
        self.graphWidget.setGeometry(50, 50, 700, 500)
        self.graphWidget.setBackground('w')
        self.graphWidget.showGrid(x=True, y=True)
        self.graphWidget.setLabel('left', 'Magnitud')
        self.graphWidget.setLabel('bottom', 'Muestras')
        self.graphWidget.setXRange(0, 200, padding=0)
        self.graphWidget.setYRange(0, 1023, padding=0)

        # Configuración del puerto serial
        self.ser = serial.Serial('COM7', 9600)
        self.ser.flush()

        # Variables para el almacenamiento de los datos
        self.x = np.linspace(0, 199, 200)
        self.y = np.zeros(200)

        # Configuración de la línea de datos en el gráfico
        self.data_line = self.graphWidget.plot(self.x, self.y, pen=pg.mkPen('r', width=2))

        # Configuración del temporizador para actualizar los datos
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_data)
        self.timer.start(10)

    def update_data(self):
        # Leer los datos del puerto serial
        while self.ser.in_waiting:
            data = self.ser.readline().decode('utf-8').rstrip()
            try:
                value = int(data)
                self.y[:-1] = self.y[1:]
                self.y[-1] = value
            except ValueError:
                print("Valor no válido: ", data)

        # Actualizar la línea de datos en el gráfico
        self.data_line.setData(self.x, self.y)

    def resizeEvent(self, event):
        # Actualizar el tamaño del gráfico al cambiar el tamaño de la ventana
        self.graphWidget.setGeometry(50, 50, self.width() - 100, self.height() - 100)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = SerialPlot()
    ex.show()
    sys.exit(app.exec_())
