//
//  module.cpp
//  superfastcode
//
//  Created by Steven Ford on 11/6/19.
//  Copyright © 2019 Steven Ford. All rights reserved.
//

#include <Python.h>
#include <stdio.h>
#include <cmath>

const double e = 2.7182818284590452353602874713527;

// Original functions
double sinh_impl_orig(double x) {
    return (1 - pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double cosh_impl_orig(double x) {
    return (1 + pow(e, (-2 * x))) / (2 * pow(e, -x));
}

double tanh_impl_orig(double x) {
    return sinh_impl_orig(x) / cosh_impl_orig(x);
}

// Python compatible functions. Just wrappers around the other ones
PyObject* sinh_impl(PyObject *, PyObject* o) {
    double x = PyFloat_AsDouble(o);
    double sinh_x = sinh_impl_orig(x);
    return PyFloat_FromDouble(sinh_x);
}

PyObject* cosh_impl(PyObject *, PyObject* o) {
    double x = PyFloat_AsDouble(o);
    double cosh_x = cosh_impl_orig(x);
    return PyFloat_FromDouble(cosh_x);
}

PyObject* tanh_impl(PyObject *, PyObject* o) {
    double x = PyFloat_AsDouble(o);
    double tanh_x = tanh_impl_orig(x);
    return PyFloat_FromDouble(tanh_x);
}

//Lets tell Python what the structure of tanh_impl is
static PyMethodDef superfastcode_methods[] = {
    // The first property is the name exposed to Python, fast_tanh,
    // Second is C++ function name that contains the implementation.
    { "fast_tanh", (PyCFunction)tanh_impl, METH_O, nullptr },

    // Terminate the array with an object containing nulls.
    { nullptr, nullptr, 0, nullptr }
};

//Lets now tell Python how to refer to this module
static struct PyModuleDef superfastcode_module = {
    PyModuleDef_HEAD_INIT,
    "superfastcode",                        // Module name to use with Python import statements
    "Provides some functions, but faster",  // Module description
    0,
    superfastcode_methods                   // Structure that defines the methods of the module
};

//Lets create function that Python calls when module is loaded
PyMODINIT_FUNC PyInit_superfastcode() {
    return PyModule_Create(&superfastcode_module);
}
