// Copyright David Abrahams 2002.
// Copyright Stefan Seefeld 2016.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_python_converter_registered_hpp_
#define boost_python_converter_registered_hpp_

#include <boost/python/type_id.hpp>
#include <boost/python/converter/registry.hpp>
#include <boost/python/converter/registrations.hpp>
#include <boost/python/detail/type_traits.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/type.hpp>
#include <memory>
#if defined(BOOST_PYTHON_TRACE_REGISTRY) \
 || defined(BOOST_PYTHON_CONVERTER_REGISTRY_APPLE_MACH_WORKAROUND)
# include <iostream>
#endif

namespace boost {

// You'll see shared_ptr mentioned in this header because we need to
// note which types are shared_ptrs in their registrations, to
// implement special shared_ptr handling for rvalue conversions.
template <class T> class shared_ptr;

namespace python { namespace converter { 

struct registration;

namespace detail
{
  template <class T>
  struct registered_base
  {
      static registration const& converters;
  };
}

template <class T>
struct registered
  : detail::registered_base<
        typename boost::python::detail::add_lvalue_reference<
            typename boost::python::detail::add_cv<T>::type
        >::type
    >
{
};

# if !BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1310))
// collapses a few more types to the same static instance.  MSVC7.1
// fails to strip cv-qualification from array types in typeid.  For
// some reason we can't use this collapse there or array converters
// will not be found.
template <class T>
struct registered<T&>
  : registered<T> {};
# endif

//
// implementations
//
namespace detail
{
  inline void
  register_shared_ptr0(...)
  {
  }
  
  template <class T>
  inline void
  register_shared_ptr0(shared_ptr<T>*)
  {
      registry::lookup_shared_ptr(type_id<shared_ptr<T> >());
  }

#if !defined(BOOST_NO_CXX11_SMART_PTR)
  template <class T>
  inline void
  register_shared_ptr0(std::shared_ptr<T>*)
  {
      registry::lookup_shared_ptr(type_id<std::shared_ptr<T> >());
  }
#endif

  template <class T>
  inline void
  register_shared_ptr1(T const volatile*)
  {
      detail::register_shared_ptr0((T*)0);
  }
  
  template <class T>
  inline registration const& 
  registry_lookup2(T&(*)())
  {
      detail::register_shared_ptr1((T*)0);
      return registry::lookup(type_id<T&>());
  }

  template <class T>
  inline registration const& 
  registry_lookup1(type<T>)
  {
      return registry_lookup2((T(*)())0);
  }

  inline registration const& 
  registry_lookup1(type<const volatile void>)
  {
      detail::register_shared_ptr1((void*)0);
      return registry::lookup(type_id<void>());
  }

  template <class T>
  registration const& registered_base<T>::converters = detail::registry_lookup1(type<T>());

}

}}} // namespace boost::python::converter

#endif

/* registered.hpp
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
*/