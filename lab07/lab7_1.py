from PyQt5 import QtWidgets, uic
from PyQt5.QtWidgets import QTableWidgetItem, QMessageBox
from PyQt5.QtGui import QPen, QColor, QImage, QPixmap, QPainter, QTransform
from PyQt5.QtCore import Qt, QTime, QCoreApplication, QEventLoop, QPoint
import time
import math as m

red = Qt.darkGreen
blue = Qt.red
now = None

class Window(QtWidgets.QMainWindow):
    def __init__(self):
        QtWidgets.QWidget.__init__(self)
        uic.loadUi("window.ui", self)
        self.scene = Scene(0, 0, 561, 581)
        self.scene.win = self
        self.view.setScene(self.scene)
        self.image = QImage(561, 581, QImage.Format_ARGB32_Premultiplied)
        self.image.fill(Qt.white)
        self.bars.clicked.connect(lambda : set_bars(self))
        self.erase.clicked.connect(lambda: clean_all(self))
        self.paint.clicked.connect(lambda: clipping(self))
        self.rect.clicked.connect(lambda: set_rect(self))
        self.ect.clicked.connect(lambda: add_bars(self))
        self.lines = []
        self.clip = None
        self.point_now = None
        self.input_bars = False
        self.input_rect = False
        self.pen = QPen(red)


class Scene(QtWidgets.QGraphicsScene):

    def mousePressEvent(self, event):
        add_point(event.scenePos())

    def mouseMoveEvent(self, event):
        global now, w
        if w.input_rect:
            if now is None:
                now = event.scenePos()
            else:
                self.removeItem(self.itemAt(now, QTransform()))
                p = event.scenePos()
                self.addRect(now.x(), now.y(), abs(now.x() - p.x()), abs(now.y() - p.y()), QPen(Qt.blue))



def set_bars(win):
    if win.input_bars:
        win.input_bars = False
        win.rect.setDisabled(False)
        win.erase.setDisabled(False)
        win.paint.setDisabled(False)
        win.ect.setDisabled(False)
    else:
        win.input_bars = True
        win.rect.setDisabled(True)
        win.erase.setDisabled(True)
        win.paint.setDisabled(True)
        win.ect.setDisabled(True)


def set_rect(win):
    if win.input_rect:
        win.input_rect = False
        win.bars.setDisabled(False)
        win.erase.setDisabled(False)
        win.paint.setDisabled(False)
        win.ect.setDisabled(False)
    else:
        win.input_rect = True
        win.bars.setDisabled(True)
        win.erase.setDisabled(True)
        win.paint.setDisabled(True)
        win.ect.setDisabled(True)


def add_row(win):
    win.table.insertRow(win.table.rowCount())


def add_point(point):
    global w
    if w.input_bars:
        if w.point_now is None:
            w.point_now = point
        else:
            w.lines.append([[w.point_now.x(), w.point_now.y()],
                            [point.x(), point.y()]])

            add_row(w)
            i = w.table.rowCount() - 1
            item_b = QTableWidgetItem("[{0}, {1}]".format(w.point_now.x(), w.point_now.y()))
            item_e = QTableWidgetItem("[{0}, {1}]".format(point.x(), point.y()))
            w.table.setItem(i, 0, item_b)
            w.table.setItem(i, 1, item_e)
            w.scene.addLine(w.point_now.x(), w.point_now.y(), point.x(), point.y(), w.pen)
            w.point_now = None


def clean_all(win):
    win.scene.clear()
    win.table.clear()
    win.lines = []
    win.image.fill(Qt.white)
    r = win.table.rowCount()
    for i in range(r, -1, -1):
        win.table.removeRow(i)


def add_bars(win):
    global now
    if now is None:
        QMessageBox.warning(win, "Ошибка", "Не введен отсекатель!")
        return
    buf = win.scene.itemAt(now, QTransform())
    if buf is None:
        QMessageBox.warning(win, "Ошибка", "Не введен отсекатель!")
    else:
        buf = buf.rect()
        win.clip = [buf.left(), buf.right(), buf.top(),  buf.bottom()]

        t = abs(win.clip[2] - win.clip[3]) * 0.8
        k = abs(win.clip[0] - win.clip[1]) * 0.8
        # задаем граничные отрезки
        win.pen.setColor(red)
        w.lines.append([[win.clip[0], win.clip[2] + t],  [win.clip[0], win.clip[3] - t]])
        add_row(w)
        i = w.table.rowCount() - 1
        item_b = QTableWidgetItem("[{0}, {1}]".format(win.clip[0], win.clip[2] + t))
        item_e = QTableWidgetItem("[{0}, {1}]".format(win.clip[0], win.clip[3] - t))
        w.table.setItem(i, 0, item_b)
        w.table.setItem(i, 1, item_e)
        win.scene.addLine(win.clip[0], win.clip[2] + t,  win.clip[0], win.clip[3] - t, win.pen)

        w.lines.append([[win.clip[1], win.clip[2] + t],  [win.clip[1], win.clip[3] - t]])
        add_row(w)
        i = w.table.rowCount() - 1
        item_b = QTableWidgetItem("[{0}, {1}]".format(win.clip[1], win.clip[2] + t))
        item_e = QTableWidgetItem("[{0}, {1}]".format(win.clip[1], win.clip[3] - t))
        w.table.setItem(i, 0, item_b)
        w.table.setItem(i, 1, item_e)
        win.scene.addLine(win.clip[1], win.clip[3] - t,  win.clip[1], win.clip[2] + t, win.pen)

        w.lines.append([[win.clip[0] + k, win.clip[2]], [win.clip[1] - k, win.clip[2]]])
        add_row(w)
        i = w.table.rowCount() - 1
        item_b = QTableWidgetItem("[{0}, {1}]".format(win.clip[0] + k, win.clip[2]))
        item_e = QTableWidgetItem("[{0}, {1}]".format(win.clip[1] - k, win.clip[2]))
        w.table.setItem(i, 0, item_b)
        w.table.setItem(i, 1, item_e)
        win.scene.addLine(win.clip[0] + k, win.clip[2], win.clip[1] - k, win.clip[2], win.pen)

        w.lines.append([[win.clip[0] + k, win.clip[3]], [win.clip[1] - k, win.clip[3]]])
        add_row(w)
        i = w.table.rowCount() - 1
        item_b = QTableWidgetItem("[{0}, {1}]".format(win.clip[0] + k, win.clip[3]))
        item_e = QTableWidgetItem("[{0}, {1}]".format(win.clip[1] - k, win.clip[3]))
        w.table.setItem(i, 0, item_b)
        w.table.setItem(i, 1, item_e)
        win.scene.addLine(win.clip[0] + k, win.clip[3], win.clip[1] - k, win.clip[3], win.pen)

def clipping(win):
    buf = win.scene.itemAt(now, QTransform()).rect()
    win.clip = [buf.left(), buf.right(), buf.top(),  buf.bottom()]
    for b in win.lines:
        pass
        win.pen.setColor(blue)
        modPoint(b, win.clip, win)
        win.pen.setColor(red)

def getCode(a, rect):
    code = [0, 0, 0, 0]
    if a[0] < rect[0]:
        code[0] = 1
    if a[0] > rect[1]:
        code[1] = 1
    if a[1] < rect[2]:
        code[2] = 1
    if a[1] > rect[3]:
        code[3] = 1

    return code

def codeSum(CODE):
    Sum = 0
    for i in range(0, 4):
        Sum += CODE[i]
    return Sum

def codesMult(code1, code2):
    Comp = 0
    for i in range(0, 4):
        Comp += int((code1[i] + code2[i])/2)
    return Comp

def cutDouble(R, i, epsilon, rect) :
    global point1
    global point2
    global Pcp
    global Pm
    global code1
    global code2
    
    while True:
        if((abs(point1[0] - point2[0]) < epsilon) and (abs(point1[1] - point2[1]) < epsilon)):
            return 

        xcp = round((point1[0] + point2[0]) / 2)
        ycp = round((point1[1] + point2[1]) / 2)       
        Pcp = [xcp, ycp]                 
        
        Pm = point1                            
        point1 = Pcp

        code1 = getCode(point1, rect)
        Comp = codesMult(code1, code2) 
            
        if(Comp == 0):
            continue

        point1 = Pm
        point2 = Pcp
        continue

def modPoint(bar, rect, win):
    global point1
    global point2

    global Pcp
    global Pm
    global code1
    global code2

    i = 1

    Pcp = 0
    Pm = 0

    epsilon = m.sqrt(2)

    point1 = bar[0]
    point2 = bar[1]

    while True:

        code1 = getCode(point1, rect)
        code2 = getCode(point2, rect)

        S1 = codeSum(code1)
        S2 = codeSum(code2)

        if(S1 == S2 == 0):
            win.scene.addLine(point1[0], point1[1], point2[0], point2[1], win.pen)
            return

        if(codesMult(code1, code2) != 0):
            return

        R = point1

        if(i > 2):
            if(codesMult(code1, code2) == 0):
                win.scene.addLine(point1[0], point1[1], point2[0], point2[1], win.pen)
            return

        if(S2 == 0):
            point1 = point2
            point2 = R
            i += 1                       
            continue 


        cutDouble(R, i, epsilon, rect)

        #point1 = point1
        point2 = R
        i += 1
        continue




    print(S1, S2)

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    w = Window()
    w.show()
    sys.exit(app.exec_())
