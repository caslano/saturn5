// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BUILTIN_CONVERTERS_DWA2002124_HPP
# define BUILTIN_CONVERTERS_DWA2002124_HPP
# include <boost/python/detail/prefix.hpp>
# include <boost/python/detail/none.hpp>
# include <boost/python/handle.hpp>
# include <boost/python/ssize_t.hpp>
# include <boost/implicit_cast.hpp>
# include <string>
# include <complex>
# include <boost/limits.hpp>

// Since all we can use to decide how to convert an object to_python
// is its C++ type, there can be only one such converter for each
// type. Therefore, for built-in conversions we can bypass registry
// lookups using explicit specializations of arg_to_python and
// result_to_python.

namespace boost { namespace python {

namespace converter
{
  template <class T> struct arg_to_python;
  BOOST_PYTHON_DECL PyObject* do_return_to_python(char);
  BOOST_PYTHON_DECL PyObject* do_return_to_python(char const*);
  BOOST_PYTHON_DECL PyObject* do_return_to_python(PyObject*);
  BOOST_PYTHON_DECL PyObject* do_arg_to_python(PyObject*);
}

// Provide specializations of to_python_value
template <class T> struct to_python_value;

namespace detail
{
  // Since there's no registry lookup, always report the existence of
  // a converter.
  struct builtin_to_python
  {
      // This information helps make_getter() decide whether to try to
      // return an internal reference or not. I don't like it much,
      // but it will have to serve for now.
      BOOST_STATIC_CONSTANT(bool, uses_registry = false);
  };
}

// Use expr to create the PyObject corresponding to x
# define BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T, expr, pytype)\
    template <> struct to_python_value<T&>                      \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };                                                          \
    template <> struct to_python_value<T const&>                \
        : detail::builtin_to_python                             \
    {                                                           \
        inline PyObject* operator()(T const& x) const           \
        {                                                       \
            return (expr);                                      \
        }                                                       \
        inline PyTypeObject const* get_pytype() const           \
        {                                                       \
            return (pytype);                                    \
        }                                                       \
    };

# define BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T, expr)   \
    namespace converter                                 \
    {                                                   \
      template <> struct arg_to_python< T >             \
        : handle<>                                      \
      {                                                 \
          arg_to_python(T const& x)                     \
            : python::handle<>(expr) {}                 \
      };                                                \
    } 

// Specialize argument and return value converters for T using expr
# define BOOST_PYTHON_TO_PYTHON_BY_VALUE(T, expr, pytype)  \
        BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(T,expr, pytype)  \
        BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE(T,expr)

// Specialize converters for signed and unsigned T to Python Int
#if PY_VERSION_HEX >= 0x03000000

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyLong_FromLong(x), &PyLong_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned T, ::PyLong_FromUnsignedLong(x), &PyLong_Type)

#else

# define BOOST_PYTHON_TO_INT(T)                                         \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed T, ::PyInt_FromLong(x), &PyInt_Type)      \
    BOOST_PYTHON_TO_PYTHON_BY_VALUE(                                    \
        unsigned T                                                      \
        , static_cast<unsigned long>(x) > static_cast<unsigned long>(   \
                (std::numeric_limits<long>::max)())                     \
        ? ::PyLong_FromUnsignedLong(x)                                  \
        : ::PyInt_FromLong(x), &PyInt_Type)
#endif

// Bool is not signed.
#if PY_VERSION_HEX >= 0x02030000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyBool_FromLong(x), &PyBool_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(bool, ::PyInt_FromLong(x), &PyInt_Type)
#endif
  
// note: handles signed char and unsigned char, but not char (see below)
BOOST_PYTHON_TO_INT(char)

BOOST_PYTHON_TO_INT(short)
BOOST_PYTHON_TO_INT(int)
BOOST_PYTHON_TO_INT(long)

# if defined(_MSC_VER) && defined(_WIN64) && PY_VERSION_HEX < 0x03000000
/* Under 64-bit Windows std::size_t is "unsigned long long". To avoid
   getting a Python long for each std::size_t the value is checked before
   the conversion. A std::size_t is converted to a simple Python int
   if possible; a Python long appears only if the value is too small or
   too large to fit into a simple int. */
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    signed BOOST_PYTHON_LONG_LONG,
    (   x < static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::min)())
     || x > static_cast<signed BOOST_PYTHON_LONG_LONG>(
            (std::numeric_limits<long>::max)()))
    ? ::PyLong_FromLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(
    unsigned BOOST_PYTHON_LONG_LONG,
    x > static_cast<unsigned BOOST_PYTHON_LONG_LONG>(
      (std::numeric_limits<long>::max)())
    ? ::PyLong_FromUnsignedLongLong(x)
    : ::PyInt_FromLong(static_cast<long>(x)), &PyInt_Type)
//
# elif defined(HAVE_LONG_LONG) // using Python's macro instead of Boost's
                               // - we don't seem to get the config right
                               // all the time.
BOOST_PYTHON_TO_PYTHON_BY_VALUE(signed BOOST_PYTHON_LONG_LONG, ::PyLong_FromLongLong(x), &PyLong_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(unsigned BOOST_PYTHON_LONG_LONG, ::PyLong_FromUnsignedLongLong(x), &PyLong_Type)
# endif
    
# undef BOOST_TO_PYTHON_INT

#if PY_VERSION_HEX >= 0x03000000
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyUnicode_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyUnicode_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
#else
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(char const*, converter::do_return_to_python(x), &PyString_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::string, ::PyString_FromStringAndSize(x.data(),implicit_cast<ssize_t>(x.size())), &PyString_Type)
#endif

#if defined(Py_USING_UNICODE) && !defined(BOOST_NO_STD_WSTRING)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::wstring, ::PyUnicode_FromWideChar(x.data(),implicit_cast<ssize_t>(x.size())), &PyUnicode_Type)
# endif 
BOOST_PYTHON_TO_PYTHON_BY_VALUE(float, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(double, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(long double, ::PyFloat_FromDouble(x), &PyFloat_Type)
BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE(PyObject*, converter::do_return_to_python(x), 0)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::complex<float>, ::PyComplex_FromDoubles(x.real(), x.imag()), &PyComplex_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::complex<double>, ::PyComplex_FromDoubles(x.real(), x.imag()), &PyComplex_Type)
BOOST_PYTHON_TO_PYTHON_BY_VALUE(std::complex<long double>, ::PyComplex_FromDoubles(x.real(), x.imag()), &PyComplex_Type)

# undef BOOST_PYTHON_RETURN_TO_PYTHON_BY_VALUE
# undef BOOST_PYTHON_ARG_TO_PYTHON_BY_VALUE
# undef BOOST_PYTHON_TO_PYTHON_BY_VALUE
# undef BOOST_PYTHON_TO_INT
    
namespace converter
{ 

  void initialize_builtin_converters();

}

}} // namespace boost::python::converter

#endif // BUILTIN_CONVERTERS_DWA2002124_HPP

/* builtin_converters.hpp
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
*/