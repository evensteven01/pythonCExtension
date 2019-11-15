from distutils.core import setup, Extension
setup(name='superfastcode', version='1.0',
      ext_modules=[Extension('superfastcode', ['module.cpp'])])
