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
tkgkYFBLAQIAAAoAAAAIAC1nSlIlMy1SJgMAAPMGAAAhAAkAAAAAAAEAAAAAAE0USABjdXJsLW1hc3Rlci90ZXN0cy91bml0L3VuaXQxNjAxLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSFSL9zYYDAACDCAAAIQAJAAAAAAABAAAAAAC7F0gAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC91bml0MTYwMi5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUudIFgJ9BQAAkhcAACEACQAAAAAAAQAAAAAAiRtIAGN1cmwtbWFzdGVyL3Rlc3RzL3VuaXQvdW5pdDE2MDMuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJdM8cHSggAAHEtAAAhAAkAAAAAAAEAAAAAAE4hSABjdXJsLW1hc3Rlci90ZXN0cy91bml0L3VuaXQxNjA0LmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSHQMo9OICAACDBgAAIQAJAAAAAAABAAAAAADgKUgAY3VybC1tYXN0ZXIvdGVzdHMvdW5pdC91bml0MTYwNS5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUkKfFvcfBAAAXgoAACEACQAAAAAAAQAAAAAACi1IAGN1
*/