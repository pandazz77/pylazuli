## How to run plugin_loader example
*root dir*
1) Create py virtual env: `python3 -m venv .venv`
2) activate env: `source .venv/bin/activate`
3) install build requirements: `pip install -r requirements.txt`
4) install BaseNaviWidget python bindings: `sip-install`

5) build Test via cmake
6) run `./plugin_loader /..../build/PyLazuliLoader/libPyLazuliLoader.so`


## How to run python module with BaseNaviWidget
1) add BaseNaviWidgets shared lib to LD_LIBRARY_PATH: `export LD_LIBRARY_PATH=<libBaseNaviWidgetLib.so_path>:$LD_LIBRARY_PATH`
2) `python3 test.py`