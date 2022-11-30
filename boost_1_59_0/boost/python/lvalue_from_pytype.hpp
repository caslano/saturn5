// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef LVALUE_FROM_PYTYPE_DWA2002130_HPP
# define LVALUE_FROM_PYTYPE_DWA2002130_HPP

# include <boost/python/detail/prefix.hpp>
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
# include <boost/python/converter/pytype_function.hpp>
#endif

# include <boost/python/type_id.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/python/detail/void_ptr.hpp>
# include <boost/python/detail/type_traits.hpp>

namespace boost { namespace python {

namespace detail
{
  // Given a pointer-to-function of 1 parameter returning a reference
  // type, return the type_id of the function's return type.
  template <class T, class U>
  inline type_info extractor_type_id(T&(*)(U))
  {
      return type_id<T>();
  }

  // A function generator whose static execute() function is an lvalue
  // from_python converter using the given Extractor. U is expected to
  // be the actual type of the PyObject instance from which the result
  // is being extracted.
  template <class Extractor, class U>
  struct normalized_extractor
  {
      static inline void* execute(PyObject* op)
      {
          typedef typename add_lvalue_reference<U>::type param;
          return &Extractor::execute(
              boost::python::detail::void_ptr_to_reference(
                  op, (param(*)())0 )
              );
      }
  };

  // Given an Extractor type and a pointer to its execute function,
  // return a new object whose static execute function does the same
  // job but is a conforming lvalue from_python conversion function.
  //
  // usage: normalize<Extractor>(&Extractor::execute)
  template <class Extractor, class T, class U>
  inline normalized_extractor<Extractor,U>
  normalize(T(*)(U), Extractor* = 0)
  {
      return normalized_extractor<Extractor, U>();
  }
}

// An Extractor which extracts the given member from a Python object
// whose instances are stored as InstanceType.
template <class InstanceType, class MemberType, MemberType (InstanceType::*member)>
struct extract_member
{
    static MemberType& execute(InstanceType& c)
    {
        (void)Py_TYPE(&c); // static assertion
        return c.*member;
    }
};

// An Extractor which simply extracts the entire python object
// instance of InstanceType.
template <class InstanceType>
struct extract_identity
{
    static InstanceType& execute(InstanceType& c)
    {
        (void)Py_TYPE(&c); // static assertion
        return c;
    }
};

// Registers a from_python conversion which extracts lvalues using
// Extractor's static execute function from Python objects whose type
// object is python_type.
template <class Extractor, PyTypeObject const* python_type>
struct lvalue_from_pytype 
{
    lvalue_from_pytype()
    {
        converter::registry::insert
            ( &extract
            , detail::extractor_type_id(&Extractor::execute)
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
            , &get_pytype
#endif
            );
    }
 private:
    static void* extract(PyObject* op)
    {
        return PyObject_TypeCheck(op, const_cast<PyTypeObject*>(python_type))
            ? const_cast<void*>(
                static_cast<void const volatile*>(
                    detail::normalize<Extractor>(&Extractor::execute).execute(op)))
            : 0
            ;
    }
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
    static PyTypeObject const*get_pytype() { return python_type; }
#endif
};

}} // namespace boost::python

#endif // LVALUE_FROM_PYTYPE_DWA2002130_HPP

/* lvalue_from_pytype.hpp
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
*/