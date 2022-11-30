#if !defined(BOOST_PP_IS_ITERATING)

// Copyright David Abrahams 2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef OVERRIDE_DWA2004721_HPP
# define OVERRIDE_DWA2004721_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/converter/return_from_python.hpp>

# include <boost/python/extract.hpp>
# include <boost/python/handle.hpp>

#  include <boost/preprocessor/iterate.hpp>
#  include <boost/preprocessor/repeat.hpp>
#  include <boost/preprocessor/debug/line.hpp>
#  include <boost/preprocessor/repetition/enum_params.hpp>
#  include <boost/preprocessor/repetition/enum_binary_params.hpp>

#  include <boost/type.hpp>

namespace boost { namespace python {

class override;

namespace detail
{
  class wrapper_base;
  
  // The result of calling a method.
  class method_result
  {
   private:
      friend class boost::python::override;
      explicit method_result(PyObject* x)
        : m_obj(x)
      {}

   public:
      template <class T>
      operator T()
      {
          converter::return_from_python<T> converter;
          return converter(m_obj.release());
      }

#  if BOOST_WORKAROUND(_MSC_FULL_VER, BOOST_TESTED_AT(140050215))
      template <class T>
      operator T*()
      {
          converter::return_from_python<T*> converter;
          return converter(m_obj.release());
      }
#  endif 
      
#  if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400)) || BOOST_WORKAROUND(BOOST_INTEL_WIN, >= 900)
      // No operator T&
#  else
      
      template <class T>
      operator T&() const
      {
          converter::return_from_python<T&> converter;
          return converter(const_cast<handle<>&>(m_obj).release());
      }
#  endif 

      template <class T>
      T as(type<T>* = 0)
      {
          converter::return_from_python<T> converter;
          return converter(m_obj.release());
      }

      template <class T>
      T unchecked(type<T>* = 0)
      {
          return extract<T>(m_obj.get())();
      }
   private:
      mutable handle<> m_obj;
  };
}

class override : public object
{
 private:
    friend class detail::wrapper_base;
    override(handle<> x)
      : object(x)
    {}
    
 public:
    detail::method_result
    operator()() const
    {
        detail::method_result x(
            PyObject_CallFunction(
                this->ptr()
              , const_cast<char*>("()")
            ));
        return x;
    }

# define BOOST_PYTHON_fast_arg_to_python_get(z, n, _)   \
    , converter::arg_to_python<A##n>(a##n).get()

# define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PYTHON_MAX_ARITY, <boost/python/override.hpp>))
# include BOOST_PP_ITERATE()

# undef BOOST_PYTHON_fast_arg_to_python_get
};

}} // namespace boost::python

#endif // OVERRIDE_DWA2004721_HPP

#else
# if !(BOOST_WORKAROUND(__MWERKS__, > 0x3100)                      \
        && BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3201)))
#  line BOOST_PP_LINE(__LINE__, override.hpp)
# endif 

# define N BOOST_PP_ITERATION()

template <
    BOOST_PP_ENUM_PARAMS_Z(1, N, class A)
    >
detail::method_result
operator()( BOOST_PP_ENUM_BINARY_PARAMS_Z(1, N, A, const& a) ) const
{
    detail::method_result x(
        PyObject_CallFunction(
            this->ptr()
          , const_cast<char*>("(" BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_FIXED, "O") ")")
            BOOST_PP_REPEAT_1ST(N, BOOST_PYTHON_fast_arg_to_python_get, nil)
        ));
    return x;
}

# undef N
#endif 

/* override.hpp
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
*/