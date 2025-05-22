from BaseNaviWidget import BaseNaviWidget
import PyQt6
import PyQt6.QtGui
import PyQt6.QtWidgets

class Test(BaseNaviWidget):
    def __init__(self):
        super().__init__(0)

    def icon():
        return PyQt6.QtGui.QIcon()

    def name():
        return "TestName"

    def description():
        return "TestDesc"

    def getNavigationData():
        return ["None"]


if __name__ == "__main__":
    app = PyQt6.QtWidgets.QApplication([])

    test = Test()
    test.show()
    app.exec()