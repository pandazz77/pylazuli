from BaseNaviWidget import BaseNaviWidget
import PyQt6
import PyQt6.QtCore
import PyQt6.QtGui
import PyQt6.QtWidgets
import PyQt6.sip

class Test(BaseNaviWidget):
    def __init__(self):
        super().__init__(0)
        self.setLayout(PyQt6.QtWidgets.QHBoxLayout()) # type: ignore  # noqa: F821
        self.layout().addWidget(PyQt6.QtWidgets.QLabel("Hello from python widget!"))

    def __del__(self):
        print("Python widget DESTRUCTED")
        

    def icon(self):
        return PyQt6.QtGui.QIcon()

    def name(self):
        return "TestName"

    def description(self):
        return "TestDesc"

    def getNavigationData(self):
        print(123)
        return ["None"]

def unwrap(obj) -> int:
    result = PyQt6.sip.unwrapinstance(obj)
    print("FROM PYTHON:",result)
    return result

def create_instance() -> Test:
    return Test()

if __name__ == "__main__":
    app = PyQt6.QtWidgets.QApplication([])

    test = Test()
    test.show()

    print(unwrap(test))

    # test.startSend()
    app.exec()