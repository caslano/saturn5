// Copyright David Abrahams 2002.
// Copyright Stefan Seefeld 2016.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_python_to_python_value_hpp_
#define boost_python_to_python_value_hpp_

#include <boost/python/detail/prefix.hpp>

#include <boost/python/refcount.hpp>
#include <boost/python/tag.hpp>
#include <boost/python/handle.hpp>

#include <boost/python/converter/registry.hpp>
#include <boost/python/converter/registered.hpp>
#include <boost/python/converter/builtin_converters.hpp>
#include <boost/python/converter/object_manager.hpp>
#include <boost/python/converter/shared_ptr_to_python.hpp>

#include <boost/python/detail/type_traits.hpp>
#include <boost/python/detail/value_is_shared_ptr.hpp>
#include <boost/python/detail/value_arg.hpp>

#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>

namespace boost { namespace python { 

namespace detail
{
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES

template <bool is_const_ref>
struct object_manager_get_pytype
{
   template <class U>
   static PyTypeObject const* get( U& (*)() =0)
   {
      return converter::object_manager_traits<U>::get_pytype();
   }
};

template <>
struct object_manager_get_pytype<true>
{
   template <class U>
   static PyTypeObject const* get( U const& (*)() =0)
   {
      return converter::object_manager_traits<U>::get_pytype();
   }
};

#endif

  template <class T>
  struct object_manager_to_python_value
  {
      typedef typename value_arg<T>::type argument_type;
    
      PyObject* operator()(argument_type) const;
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
      typedef boost::mpl::bool_<is_handle<T>::value> is_t_handle;
      typedef boost::detail::indirect_traits::is_reference_to_const<T> is_t_const;
      PyTypeObject const* get_pytype() const {
          return get_pytype_aux((is_t_handle*)0);
      }

      inline static PyTypeObject const* get_pytype_aux(mpl::true_*) {return converter::object_manager_traits<T>::get_pytype();}
      
      inline static PyTypeObject const* get_pytype_aux(mpl::false_* ) 
      {
          return object_manager_get_pytype<is_t_const::value>::get((T(*)())0);
      }
      
#endif 

      // This information helps make_getter() decide whether to try to
      // return an internal reference or not. I don't like it much,
      // but it will have to serve for now.
      BOOST_STATIC_CONSTANT(bool, uses_registry = false);
  };

  
  template <class T>
  struct registry_to_python_value
  {
      typedef typename value_arg<T>::type argument_type;
    
      PyObject* operator()(argument_type) const;
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
      PyTypeObject const* get_pytype() const {return converter::registered<T>::converters.to_python_target_type();}
#endif

      // This information helps make_getter() decide whether to try to
      // return an internal reference or not. I don't like it much,
      // but it will have to serve for now.
      BOOST_STATIC_CONSTANT(bool, uses_registry = true);
  };

  template <class T>
  struct shared_ptr_to_python_value
  {
      typedef typename value_arg<T>::type argument_type;
    
      PyObject* operator()(argument_type) const;
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
      PyTypeObject const* get_pytype() const {return get_pytype((boost::type<argument_type>*)0);}
#endif 
      // This information helps make_getter() decide whether to try to
      // return an internal reference or not. I don't like it much,
      // but it will have to serve for now.
      BOOST_STATIC_CONSTANT(bool, uses_registry = false);
  private:
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
    template <class U>
    PyTypeObject const* get_pytype(boost::type<shared_ptr<U> &> *) const {return converter::registered<U>::converters.to_python_target_type();}
    template <class U>
    PyTypeObject const* get_pytype(boost::type<const shared_ptr<U> &> *) const {return converter::registered<U>::converters.to_python_target_type();}
# if !defined(BOOST_NO_CXX11_SMART_PTR)
    template <class U>
    PyTypeObject const* get_pytype(boost::type<std::shared_ptr<U> &> *) const {return converter::registered<U>::converters.to_python_target_type();}
    template <class U>
    PyTypeObject const* get_pytype(boost::type<const std::shared_ptr<U> &> *) const {return converter::registered<U>::converters.to_python_target_type();}
# endif
#endif
  };
}

template <class T>
struct to_python_value
    : mpl::if_<
          detail::value_is_shared_ptr<T>
        , detail::shared_ptr_to_python_value<T>
        , typename mpl::if_<
              mpl::or_<
                  converter::is_object_manager<T>
                , converter::is_reference_to_object_manager<T>
              >
            , detail::object_manager_to_python_value<T>
            , detail::registry_to_python_value<T>
          >::type
      >::type
{
};

//
// implementation 
//
namespace detail
{
  template <class T>
  inline PyObject* registry_to_python_value<T>::operator()(argument_type x) const
  {
      return converter::registered<argument_type>::converters.to_python(&x);
  }

  template <class T>
  inline PyObject* object_manager_to_python_value<T>::operator()(argument_type x) const
  {
      return python::upcast<PyObject>(
          python::xincref(
              get_managed_object(x, tag))
          );
  }

  template <class T>
  inline PyObject* shared_ptr_to_python_value<T>::operator()(argument_type x) const
  {
      return converter::shared_ptr_to_python(x);
  }
}

}} // namespace boost::python

#endif

/* to_python_value.hpp
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
*/