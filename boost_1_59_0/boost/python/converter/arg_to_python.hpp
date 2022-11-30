// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ARG_TO_PYTHON_DWA200265_HPP
# define ARG_TO_PYTHON_DWA200265_HPP

# include <boost/python/ptr.hpp>
# include <boost/python/tag.hpp>
# include <boost/python/to_python_indirect.hpp>

# include <boost/python/converter/registered.hpp>
# include <boost/python/converter/registered_pointee.hpp>
# include <boost/python/converter/arg_to_python_base.hpp>
# include <boost/python/converter/shared_ptr_to_python.hpp>
// Bring in specializations
# include <boost/python/converter/builtin_converters.hpp>

# include <boost/python/object/function_handle.hpp>

# include <boost/python/base_type_traits.hpp>

# include <boost/python/detail/indirect_traits.hpp>
# include <boost/python/detail/convertible.hpp>
# include <boost/python/detail/string_literal.hpp>
# include <boost/python/detail/value_is_shared_ptr.hpp>
# include <boost/python/detail/type_traits.hpp>

# include <boost/mpl/or.hpp>

namespace boost { namespace python { namespace converter { 

template <class T> struct is_object_manager;

namespace detail
{
  template <class T>
  struct function_arg_to_python : handle<>
  {
      function_arg_to_python(T const& x);
  };

  template <class T>
  struct reference_arg_to_python : handle<>
  {
      reference_arg_to_python(T& x);
   private:
      static PyObject* get_object(T& x);
  };

  template <class T>
  struct shared_ptr_arg_to_python : handle<>
  {
      shared_ptr_arg_to_python(T const& x);
   private:
      static PyObject* get_object(T& x);
  };

  template <class T>
  struct value_arg_to_python : arg_to_python_base
  {
      // Throw an exception if the conversion can't succeed
      value_arg_to_python(T const&);
  };

  template <class Ptr>
  struct pointer_deep_arg_to_python : arg_to_python_base
  {
      // Throw an exception if the conversion can't succeed
      pointer_deep_arg_to_python(Ptr);
  };

  template <class Ptr>
  struct pointer_shallow_arg_to_python : handle<>
  {
      // Throw an exception if the conversion can't succeed
      pointer_shallow_arg_to_python(Ptr);
   private:
      static PyObject* get_object(Ptr p);
  };

  // Convert types that manage a Python object to_python
  template <class T>
  struct object_manager_arg_to_python
  {
      object_manager_arg_to_python(T const& x) : m_src(x) {}
      
      PyObject* get() const
      {
          return python::upcast<PyObject>(get_managed_object(m_src, tag));
      }
      
   private:
      T const& m_src;
  };

  template <class T>
  struct select_arg_to_python
  {
      typedef typename unwrap_reference<T>::type unwrapped_referent;
      typedef typename unwrap_pointer<T>::type unwrapped_ptr;

      typedef typename mpl::if_<
          // Special handling for char const[N]; interpret them as char
          // const* for the sake of conversion
          python::detail::is_string_literal<T const>
        , arg_to_python<char const*>

        , typename mpl::if_<
              python::detail::value_is_shared_ptr<T>
            , shared_ptr_arg_to_python<T>
      
            , typename mpl::if_<
                mpl::or_<
                    boost::python::detail::is_function<T>
                  , indirect_traits::is_pointer_to_function<T>
                  , boost::python::detail::is_member_function_pointer<T>
                >
                , function_arg_to_python<T>

                , typename mpl::if_<
                      is_object_manager<T>
                    , object_manager_arg_to_python<T>

                    , typename mpl::if_<
                          boost::python::detail::is_pointer<T>
                        , pointer_deep_arg_to_python<T>

                        , typename mpl::if_<
                              is_pointer_wrapper<T>
                            , pointer_shallow_arg_to_python<unwrapped_ptr>

                            , typename mpl::if_<
                                  is_reference_wrapper<T>
                                , reference_arg_to_python<unwrapped_referent>
                                , value_arg_to_python<T>
                              >::type
                          >::type
                      >::type
                  >::type
              >::type
          >::type
      >::type
      
      type;
  };
}

template <class T>
struct arg_to_python
    : detail::select_arg_to_python<T>::type
{
    typedef typename detail::select_arg_to_python<T>::type base;
 public: // member functions
    // Throw an exception if the conversion can't succeed
    arg_to_python(T const& x);
};

//
// implementations
//
namespace detail
{
  // reject_raw_object_ptr -- cause a compile-time error if the user
  // should pass a raw Python object pointer
  using python::detail::yes_convertible;
  using python::detail::no_convertible;
  using python::detail::unspecialized;
  
  template <class T> struct cannot_convert_raw_PyObject;

  template <class T, class Convertibility>
  struct reject_raw_object_helper
  {
      static void error(Convertibility)
      {
          cannot_convert_raw_PyObject<T*>::to_python_use_handle_instead();
      }
      static void error(...) {}
  };
  
  template <class T>
  inline void reject_raw_object_ptr(T*)
  {
      reject_raw_object_helper<T,yes_convertible>::error(
          python::detail::convertible<PyObject const volatile*>::check((T*)0));
      
      typedef typename remove_cv<T>::type value_type;
      
      reject_raw_object_helper<T,no_convertible>::error(
          python::detail::convertible<unspecialized*>::check(
              (base_type_traits<value_type>*)0
              ));
  }
  // ---------
      
  template <class T>
  inline function_arg_to_python<T>::function_arg_to_python(T const& x)
      : handle<>(python::objects::make_function_handle(x))
  {
  }

  template <class T>
  inline value_arg_to_python<T>::value_arg_to_python(T const& x)
      : arg_to_python_base(&x, registered<T>::converters)
  {
  }

  template <class Ptr>
  inline pointer_deep_arg_to_python<Ptr>::pointer_deep_arg_to_python(Ptr x)
      : arg_to_python_base(x, registered_pointee<Ptr>::converters)
  {
      detail::reject_raw_object_ptr((Ptr)0);
  }

  template <class T>
  inline PyObject* reference_arg_to_python<T>::get_object(T& x)
  {
      to_python_indirect<T&,python::detail::make_reference_holder> convert;
      return convert(x);
  }

  template <class T>
  inline reference_arg_to_python<T>::reference_arg_to_python(T& x)
      : handle<>(reference_arg_to_python<T>::get_object(x))
  {
  }

  template <class T>
  inline shared_ptr_arg_to_python<T>::shared_ptr_arg_to_python(T const& x)
      : handle<>(shared_ptr_to_python(x))
  {
  }

  template <class Ptr>
  inline pointer_shallow_arg_to_python<Ptr>::pointer_shallow_arg_to_python(Ptr x)
      : handle<>(pointer_shallow_arg_to_python<Ptr>::get_object(x))
  {
      detail::reject_raw_object_ptr((Ptr)0);
  }

  template <class Ptr>
  inline PyObject* pointer_shallow_arg_to_python<Ptr>::get_object(Ptr x)
  {
      to_python_indirect<Ptr,python::detail::make_reference_holder> convert;
      return convert(x);
  }
}

template <class T>
inline arg_to_python<T>::arg_to_python(T const& x)
    : base(x)
{}

}}} // namespace boost::python::converter

#endif // ARG_TO_PYTHON_DWA200265_HPP

/* arg_to_python.hpp
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
*/