import os, sys
import subprocess

from sipbuild import Project, Bindings
from pyqtbuild import PyQtProject, PyQtBindings


class BaseNaviWidget(PyQtProject):
    def __init__(self):
        super().__init__()
        self.bindings_factories = [BaseNaviWidgetsBindings]

    def _build_foo(self):
        cwd = os.path.abspath('BaseNaviWidget')
        build_dir = os.path.join(cwd,"build")
        os.makedirs(build_dir,exist_ok=True)
        subprocess.run(['cmake','..'], cwd=build_dir, capture_output=True, check=True)              # configure
        subprocess.run(['cmake','--build',build_dir], cwd=cwd, capture_output=True, check=True)     # build

    def build(self):        # sip-build
        self._build_foo()
        super().build()

    def build_sdist(self, sdist_directory): # sip-sdist
        self._build_foo()
        return super().build_sdist(sdist_directory)

    def build_wheel(self, wheel_directory): # sip-wheel
        self._build_foo()
        return super().build_wheel(wheel_directory)

    def install(self): # sip-install
        self._build_foo()
        super().install()


class BaseNaviWidgetsBindings(PyQtBindings):
    def __init__(self, project):
        super().__init__(project, 
            name='BaseNaviWidget', 
            sip_file='BaseNaviWidget.sip', 

            libraries=["BaseNaviWidgetLib"],
            library_dirs=["BaseNaviWidget/build"],
            headers=["BaseNaviWidget.h"],
            include_dirs=["BaseNaviWidget/include"],

            qmake_QT=['widgets']
        )
        self._project = project