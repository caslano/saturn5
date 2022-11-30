// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef RETURN_FROM_PYTHON_DWA200265_HPP
# define RETURN_FROM_PYTHON_DWA200265_HPP

# include <boost/python/converter/from_python.hpp>
# include <boost/python/converter/rvalue_from_python_data.hpp>
# include <boost/python/converter/registered.hpp>
# include <boost/python/converter/registered_pointee.hpp>
# include <boost/python/converter/object_manager.hpp>
# include <boost/python/detail/void_ptr.hpp>
# include <boost/python/detail/void_return.hpp>
# include <boost/python/errors.hpp>
# include <boost/python/handle.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <boost/mpl/and.hpp>
# include <boost/mpl/bool.hpp>

namespace boost { namespace python { namespace converter { 

template <class T> struct is_object_manager;

namespace detail
{
  template <class T>
  struct return_pointer_from_python
  {
      typedef T result_type;
      T operator()(PyObject*) const;
  };
  
  template <class T>
  struct return_reference_from_python
  {
      typedef T result_type;
      T operator()(PyObject*) const;
  };
  
  template <class T>
  struct return_rvalue_from_python
  {
      typedef T result_type;

      return_rvalue_from_python();
      result_type operator()(PyObject*);
   private:
      rvalue_from_python_data<T> m_data;
  };
  
  template <class T>
  struct return_object_manager_from_python
  {
      typedef T result_type;
      result_type operator()(PyObject*) const;
  };
  
  template <class T>
  struct select_return_from_python
  {
      BOOST_STATIC_CONSTANT(
          bool, obj_mgr = is_object_manager<T>::value);

      BOOST_STATIC_CONSTANT(
          bool, ptr = is_pointer<T>::value);
    
      BOOST_STATIC_CONSTANT(
          bool, ref = is_reference<T>::value);

      typedef typename mpl::if_c<
          obj_mgr
          , return_object_manager_from_python<T>
          , typename mpl::if_c<
              ptr
              , return_pointer_from_python<T>
              , typename mpl::if_c<
                  ref
                  , return_reference_from_python<T>
                  , return_rvalue_from_python<T>
                >::type
            >::type
         >::type type;
  };
}

template <class T>
struct return_from_python
    : detail::select_return_from_python<T>::type
{
};

// Specialization as a convenience for call and call_method
template <>
struct return_from_python<void>
{
    typedef python::detail::returnable<void>::type result_type;
    
    result_type operator()(PyObject* x) const
    {
        (void_result_from_python)(x);
# ifdef BOOST_NO_VOID_RETURNS
        return result_type();
# endif 
    }
};

//
// Implementations
//
namespace detail
{
  template <class T>
  inline return_rvalue_from_python<T>::return_rvalue_from_python()
      : m_data(
          const_cast<registration*>(&registered<T>::converters)
          )
  {
  }
  
  template <class T>
  inline typename return_rvalue_from_python<T>::result_type
  return_rvalue_from_python<T>::operator()(PyObject* obj)
  {
    // Take possession of the source object here.  If the result is in
    // fact going to be a copy of an lvalue embedded in the object,
    // and we take possession inside rvalue_result_from_python, it
    // will be destroyed too early.
    handle<> holder(obj);

      return *(T*)
          (rvalue_result_from_python)(obj, m_data.stage1);
  }

  template <class T>
  inline T return_reference_from_python<T>::operator()(PyObject* obj) const
  {
      return python::detail::void_ptr_to_reference(
          (reference_result_from_python)(obj, registered<T>::converters)
          , (T(*)())0);
  }

  template <class T>
  inline T return_pointer_from_python<T>::operator()(PyObject* obj) const
  {
      return T(
          (pointer_result_from_python)(obj, registered_pointee<T>::converters)
          );
  }

  template <class T>
  inline T return_object_manager_from_python<T>::operator()(PyObject* obj) const
  {
      return T(
          object_manager_traits<T>::adopt(expect_non_null(obj))
          );
  }
}
  
}}} // namespace boost::python::converter

#endif // RETURN_FROM_PYTHON_DWA200265_HPP

/* return_from_python.hpp
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
*/