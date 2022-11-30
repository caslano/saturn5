// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef MODULE_INIT_DWA20020722_HPP
# define MODULE_INIT_DWA20020722_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/stringize.hpp>

# ifndef BOOST_PYTHON_MODULE_INIT

namespace boost { namespace python { namespace detail {

#  if PY_VERSION_HEX >= 0x03000000

BOOST_PYTHON_DECL PyObject* init_module(PyModuleDef&, void(*)());

#else

BOOST_PYTHON_DECL PyObject* init_module(char const* name, void(*)());

#endif

}}}

#  if PY_VERSION_HEX >= 0x03000000

#   define _BOOST_PYTHON_MODULE_INIT(name) \
  PyObject* BOOST_PP_CAT(PyInit_, name)()  \
  { \
    static PyModuleDef_Base initial_m_base = { \
        PyObject_HEAD_INIT(NULL) \
        0, /* m_init */ \
        0, /* m_index */ \
        0 /* m_copy */ };  \
    static PyMethodDef initial_methods[] = { { 0, 0, 0, 0 } }; \
 \
    static struct PyModuleDef moduledef = { \
        initial_m_base, \
        BOOST_PP_STRINGIZE(name), \
        0, /* m_doc */ \
        -1, /* m_size */ \
        initial_methods, \
        0,  /* m_reload */ \
        0, /* m_traverse */ \
        0, /* m_clear */ \
        0,  /* m_free */ \
    }; \
 \
    return boost::python::detail::init_module( \
        moduledef, BOOST_PP_CAT(init_module_, name) ); \
  } \
  void BOOST_PP_CAT(init_module_, name)()

#  else

#   define _BOOST_PYTHON_MODULE_INIT(name)              \
  void BOOST_PP_CAT(init,name)()                        \
{                                                       \
    boost::python::detail::init_module(                 \
        BOOST_PP_STRINGIZE(name),&BOOST_PP_CAT(init_module_,name)); \
}                                                       \
  void BOOST_PP_CAT(init_module_,name)()

#  endif

#  define BOOST_PYTHON_MODULE_INIT(name)                       \
  void BOOST_PP_CAT(init_module_,name)();                      \
extern "C" BOOST_SYMBOL_EXPORT _BOOST_PYTHON_MODULE_INIT(name)

# endif

#endif // MODULE_INIT_DWA20020722_HPP

/* module_init.hpp
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
*/