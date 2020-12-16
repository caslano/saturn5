// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ARG_FROM_PYTHON_DWA2002128_HPP
# define ARG_FROM_PYTHON_DWA2002128_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/python/converter/arg_from_python.hpp>
# if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    || BOOST_WORKAROUND(BOOST_INTEL_WIN, BOOST_TESTED_AT(800))
# include <boost/python/detail/type_traits.hpp>
#endif

namespace boost { namespace python { 

template <class T>
struct arg_from_python
    : converter::select_arg_from_python<
# if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    || BOOST_WORKAROUND(BOOST_INTEL_WIN, BOOST_TESTED_AT(800))
          typename detail::remove_cv<T>::type
# else
          T
# endif 
      >::type
{
    typedef typename converter::select_arg_from_python<
# if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) \
    || BOOST_WORKAROUND(BOOST_INTEL_WIN, BOOST_TESTED_AT(800))
          typename detail::remove_cv<T>::type
# else
          T
# endif 
        >::type base;
    
    arg_from_python(PyObject*);
};

// specialization for PyObject*
template <>
struct arg_from_python<PyObject*>
{
    typedef PyObject* result_type;
    
    arg_from_python(PyObject* p) : m_source(p) {}
    bool convertible() const { return true; }
    PyObject* operator()() const { return m_source; }
 private:
    PyObject* m_source;
};

template <>
struct arg_from_python<PyObject* const&>
{
    typedef PyObject* const& result_type;
    
    arg_from_python(PyObject* p) : m_source(p) {}
    bool convertible() const { return true; }
    PyObject*const& operator()() const { return m_source; }
 private:
    PyObject* m_source;
};

//
// implementations
//
template <class T>
inline arg_from_python<T>::arg_from_python(PyObject* source)
    : base(source)
{
}

}} // namespace boost::python

#endif // ARG_FROM_PYTHON_DWA2002128_HPP

/* arg_from_python.hpp
AAAAAAABABgAAAZOKP/X0gHND9xX+9PWAW2u2Vf709YBUEsBAj8AFAAAAAgAwLG8SjX2rb+zngIAAI4HABIAJAAAAAAAAAAgAAAAbWVRAGJpbjY0L2xpYnNzbE1ELmRsbAoAIAAAAAAAAQAYAADE+LT/19IBLnHeV/vT1gHND9xX+9PWAVBLAQI/ABQAAAAIAMCxvEp+7t31GIIHAACQHAASACQAAAAAAAAAIAAAAFAEVABiaW42NC9saWJzc2xNRC5wZGIKACAAAAAAAAEAGAAAxPi0/9fSAS5x3lf709YBLnHeV/vT1gFQSwECPwAUAAAACABCsbxKr4m/bcebAgAAkAkAEwAkAAAAAAAAACAAAACYhlsAYmluNjQvbGlic3NsTURkLmRsbAoAIAAAAAAAAQAYAAAGTij/19IBLnHeV/vT1gEucd5X+9PWAVBLAQI/ABQAAAAIAEKxvEojQaLC9dsFAADQFwATACQAAAAAAAAAIAAAAJAiXgBiaW42NC9saWJzc2xNRGQucGRiCgAgAAAAAAABABgAAAZOKP/X0gEucd5X+9PWAS5x3lf709YBUEsBAj8AFAAAAAgAwLG8Sl61Yx2XcAMAAHQHABEAJAAAAAAAAAAgAAAAtv5jAGJpbjY0L29wZW5zc2wuZXhlCgAgAAAAAAABABgAAMT4tP/X0gEucd5X+9PWAS5x3lf709YBUEsBAj8AFAAAAAgAwLG8ShCYyqq1IwkAANAjABEAJAAAAAAAAAAgAAAAfG9nAGJpbjY0L29wZW5zc2wucGRiCgAgAAAAAAABABgAAMT4tP/X0gGO0uBX+9PWAY7S4Ff709YBUEsBAj8AFAAAAAgA4q68Ste2GiQ22goAACwcABMAJAAAAAAAAAAgAAAAYJNwAGJpbi9saWJjcnlwdG9NRC5kbGwKACAAAAAAAAEAGAAA7NwP/dfSAY7S4Ff709YBjtLgV/vT1gFQSwECPwAUAAAACADjrrxKequA/+JdHwAA0IoAEwAkAAAAAAAAACAAAADHbXsAYmluL2xpYmNyeXB0b01ELnBkYgoAIAAAAAAAAQAYAAAZDhH919IBT5XlV/vT1gGO0uBX+9PWAVBLAQI/ABQAAAAIAFauvEpO0kpV/34LAAByJAAUACQAAAAAAAAAIAAAANrLmgBiaW4vbGliY3J5cHRvTURkLmRsbAoAIAAAAAAAAQAYAAAS5HT819IBT5XlV/vT1gFPleVX+9PWAVBLAQI/ABQAAAAIAFauvEqAE6G6NOoWAAAQbQAUACQAAAAAAAAAIAAAAAtLpgBiaW4vbGliY3J5cHRvTURkLnBkYgoAIAAAAAAAAQAYAAAS5HT819IBr/bnV/vT1gFPleVX+9PWAVBLAQI/ABQAAAAIAOKuvEoDuKLB+S4CAADYBQAQACQAAAAAAAAAIAAAAHE1vQBiaW4vbGlic3NsTUQuZGxsCgAgAAAAAAABABgAAOzcD/3X0gGv9udX+9PWAa/251f709YBUEsBAj8AFAAAAAgA4668SnVptG8zhAcAALAdABAAJAAAAAAAAAAgAAAAmGS/AGJpbi9saWJzc2xNRC5wZGIKACAAAAAAAAEAGAAAGQ4R/dfSAQ9Y6lf709YBr/bnV/vT1gFQSwECPwAUAAAACABWrrxKzNe0ng5hAgAAVAcAEQAkAAAAAAAAACAAAAD56MYAYmluL2xpYnNzbE1EZC5kbGwKACAAAAAAAAEAGAAAEuR0/NfSAQ9Y6lf709YBD1jqV/vT1gFQSwECPwAUAAAACABWrrxKUIUEGSSTBQAAUBcAEQAkAAAAAAAAACAAAAA2SskAYmluL2xpYnNzbE0=
*/