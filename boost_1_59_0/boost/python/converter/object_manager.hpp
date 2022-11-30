// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef OBJECT_MANAGER_DWA2002614_HPP
# define OBJECT_MANAGER_DWA2002614_HPP

# include <boost/python/handle.hpp>
# include <boost/python/cast.hpp>
# include <boost/python/converter/pyobject_traits.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <boost/mpl/if.hpp>
# include <boost/python/detail/indirect_traits.hpp>
# include <boost/mpl/bool.hpp>

// Facilities for dealing with types which always manage Python
// objects. Some examples are object, list, str, et. al. Different
// to_python/from_python conversion rules apply here because in
// contrast to other types which are typically embedded inside a
// Python object, these are wrapped around a Python object. For most
// object managers T, a C++ non-const T reference argument does not
// imply the existence of a T lvalue embedded in the corresponding
// Python argument, since mutating member functions on T actually only
// modify the held Python object.
//
// handle<T> is an object manager, though strictly speaking it should
// not be. In other words, even though mutating member functions of
// hanlde<T> actually modify the handle<T> and not the T object,
// handle<T>& arguments of wrapped functions will bind to "rvalues"
// wrapping the actual Python argument, just as with other object
// manager classes. Making an exception for handle<T> is simply not
// worth the trouble.
//
// borrowed<T> cv* is an object manager so that we can use the general
// to_python mechanisms to convert raw Python object pointers to
// python, without the usual semantic problems of using raw pointers.


// Object Manager Concept requirements:
//
//    T is an Object Manager
//    p is a PyObject*
//    x is a T
//
//    * object_manager_traits<T>::is_specialized == true
//
//    * T(detail::borrowed_reference(p))
//        Manages p without checking its type
//
//    * get_managed_object(x, boost::python::tag)
//        Convertible to PyObject*
//
// Additional requirements if T can be converted from_python:
//
//    * T(object_manager_traits<T>::adopt(p))
//        steals a reference to p, or throws a TypeError exception if
//        p doesn't have an appropriate type. May assume p is non-null
//
//    * X::check(p)
//        convertible to bool. True iff T(X::construct(p)) will not
//        throw.

// Forward declarations
//
namespace boost { namespace python
{
  namespace api
  {
    class object; 
  }
}}

namespace boost { namespace python { namespace converter { 


// Specializations for handle<T>
template <class T>
struct handle_object_manager_traits
    : pyobject_traits<typename T::element_type>
{
 private:
  typedef pyobject_traits<typename T::element_type> base;
  
 public:
  BOOST_STATIC_CONSTANT(bool, is_specialized = true);

  // Initialize with a null_ok pointer for efficiency, bypassing the
  // null check since the source is always non-null.
  static null_ok<typename T::element_type>* adopt(PyObject* p)
  {
      return python::allow_null(base::checked_downcast(p));
  }
};

template <class T>
struct default_object_manager_traits
{
    BOOST_STATIC_CONSTANT(
        bool, is_specialized = python::detail::is_borrowed_ptr<T>::value
        );
};

template <class T>
struct object_manager_traits
    : mpl::if_c<
         is_handle<T>::value
       , handle_object_manager_traits<T>
       , default_object_manager_traits<T>
    >::type
{
};

//
// Traits for detecting whether a type is an object manager or a
// (cv-qualified) reference to an object manager.
// 

template <class T>
struct is_object_manager
    : mpl::bool_<object_manager_traits<T>::is_specialized>
{
};

template <class T>
struct is_reference_to_object_manager
    : mpl::false_
{
};

template <class T>
struct is_reference_to_object_manager<T&>
    : is_object_manager<T>
{
};

template <class T>
struct is_reference_to_object_manager<T const&>
    : is_object_manager<T>
{
};

template <class T>
struct is_reference_to_object_manager<T volatile&>
    : is_object_manager<T>
{
};

template <class T>
struct is_reference_to_object_manager<T const volatile&>
    : is_object_manager<T>
{
};

}}} // namespace boost::python::converter

#endif // OBJECT_MANAGER_DWA2002614_HPP

/* object_manager.hpp
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
*/