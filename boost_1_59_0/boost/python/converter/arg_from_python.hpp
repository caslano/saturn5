// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ARG_FROM_PYTHON_DWA2002127_HPP
# define ARG_FROM_PYTHON_DWA2002127_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/python/converter/from_python.hpp>
# include <boost/python/detail/indirect_traits.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <boost/python/converter/rvalue_from_python_data.hpp>
# include <boost/mpl/eval_if.hpp>
# include <boost/mpl/if.hpp>
# include <boost/mpl/identity.hpp>
# include <boost/mpl/and.hpp>
# include <boost/mpl/or.hpp>
# include <boost/mpl/not.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/python/converter/registered.hpp>
# include <boost/python/converter/registered_pointee.hpp>
# include <boost/python/detail/void_ptr.hpp>
# include <boost/python/back_reference.hpp>
# include <boost/python/detail/referent_storage.hpp>
# include <boost/python/converter/obj_mgr_arg_from_python.hpp>

namespace boost { namespace python
{
  template <class T> struct arg_from_python;
}}

// This header defines Python->C++ function argument converters,
// parametrized on the argument type.

namespace boost { namespace python { namespace converter {

//
// lvalue converters
//
//   These require that an lvalue of the type U is stored somewhere in
//   the Python object being converted.

// Used when T == U*const&
template <class T>
struct pointer_cref_arg_from_python
{
    typedef T result_type;
    
    pointer_cref_arg_from_python(PyObject*);
    T operator()() const;
    bool convertible() const;
    
 private: // storage for a U*
    // needed because not all compilers will let us declare U* as the
    // return type of operator() -- we return U*const& instead
    typename python::detail::referent_storage<T>::type m_result;
};

// Base class for pointer and reference converters
struct arg_lvalue_from_python_base
{
 public: // member functions
    arg_lvalue_from_python_base(void* result);
    bool convertible() const;
    
 protected: // member functions
    void*const& result() const;
    
 private: // data members
    void* m_result;
};

// Used when T == U* 
template <class T>
struct pointer_arg_from_python : arg_lvalue_from_python_base
{
    typedef T result_type;
    
    pointer_arg_from_python(PyObject*);
    T operator()() const;
};

// Used when T == U& and (T != V const& or T == W volatile&)
template <class T>
struct reference_arg_from_python : arg_lvalue_from_python_base
{
    typedef T result_type;
    
    reference_arg_from_python(PyObject*);
    T operator()() const;
};

// ===================

//
// rvalue converters
//
//   These require only that an object of type T can be created from
//   the given Python object, but not that the T object exist
//   somewhere in storage.
//

// Used when T is a plain value (non-pointer, non-reference) type or
// a (non-volatile) const reference to a plain value type.
template <class T>
struct arg_rvalue_from_python
{
    typedef typename boost::python::detail::add_lvalue_reference<
        T
        // We can't add_const here, or it would be impossible to pass
        // auto_ptr<U> args from Python to C++
    >::type result_type;
    
    arg_rvalue_from_python(PyObject*);
    bool convertible() const;

# if _MSC_FULL_VER > 13102196
    typename arg_rvalue_from_python<T>::
# endif
    result_type operator()();
    
 private:
    rvalue_from_python_data<result_type> m_data;
    PyObject* m_source;
};


// ==================

// Converts to a (PyObject*,T) bundle, for when you need a reference
// back to the Python object
template <class T>
struct back_reference_arg_from_python
    : boost::python::arg_from_python<typename T::type>
{
    typedef T result_type;
    
    back_reference_arg_from_python(PyObject*);
    T operator()();
 private:
    typedef boost::python::arg_from_python<typename T::type> base;
    PyObject* m_source;
};


// ==================

template <class C, class T, class F>
struct if_2
{
    typedef typename mpl::eval_if<C, mpl::identity<T>, F>::type type;
};

// This metafunction selects the appropriate arg_from_python converter
// type for an argument of type T.
template <class T>
struct select_arg_from_python
{
    typedef typename if_2<
        is_object_manager<T>
      , object_manager_value_arg_from_python<T>
      , if_2<
            is_reference_to_object_manager<T>
          , object_manager_ref_arg_from_python<T>
          , if_2<
                is_pointer<T>
              , pointer_arg_from_python<T>
              , if_2<
                    mpl::and_<
                        indirect_traits::is_reference_to_pointer<T>
                      , indirect_traits::is_reference_to_const<T>
                      , mpl::not_<indirect_traits::is_reference_to_volatile<T> >
                        >
                  , pointer_cref_arg_from_python<T>
                  , if_2<
                        mpl::or_<
                            indirect_traits::is_reference_to_non_const<T>
                          , indirect_traits::is_reference_to_volatile<T>
                        >
                      , reference_arg_from_python<T>
                      , mpl::if_<
                            boost::python::is_back_reference<T>
                          , back_reference_arg_from_python<T>
                          , arg_rvalue_from_python<T>
                        >
                    >
                >
            >
        >
    >::type type;
};

// ==================

//
// implementations
//

// arg_lvalue_from_python_base
//
inline arg_lvalue_from_python_base::arg_lvalue_from_python_base(void* result)
    : m_result(result)
{
}

inline bool arg_lvalue_from_python_base::convertible() const
{
    return m_result != 0;
}

inline void*const& arg_lvalue_from_python_base::result() const
{
    return m_result;
}

// pointer_cref_arg_from_python
//
namespace detail
{
  // null_ptr_reference -- a function returning a reference to a null
  // pointer of type U. Needed so that extractors for T*const& can
  // convert Python's None.
  template <class T>
  struct null_ptr_owner
  {
      static T value;
  };
  template <class T> T null_ptr_owner<T>::value = 0;
  
  template <class U>
  inline U& null_ptr_reference(U&(*)())
  {
      return null_ptr_owner<U>::value;
  }
}

template <class T>
inline pointer_cref_arg_from_python<T>::pointer_cref_arg_from_python(PyObject* p)
{
    // T == U*const&: store a U* in the m_result storage. Nonzero
    // indicates success.  If find returns nonzero, it's a pointer to
    // a U object.
    python::detail::write_void_ptr_reference(
        m_result.bytes
        , p == Py_None ? p : converter::get_lvalue_from_python(p, registered_pointee<T>::converters)
        , (T(*)())0);
}

template <class T>
inline bool pointer_cref_arg_from_python<T>::convertible() const
{
    return python::detail::void_ptr_to_reference(m_result.bytes, (T(*)())0) != 0;
}
template <class T>
inline T pointer_cref_arg_from_python<T>::operator()() const
{
    return (*(void**)m_result.bytes == Py_None)  // None ==> 0
        ? detail::null_ptr_reference((T(*)())0)
        // Otherwise, return a U*const& to the m_result storage.
        : python::detail::void_ptr_to_reference(m_result.bytes, (T(*)())0);
}

// pointer_arg_from_python
//
template <class T>
inline pointer_arg_from_python<T>::pointer_arg_from_python(PyObject* p)
    : arg_lvalue_from_python_base(
        p == Py_None ? p : converter::get_lvalue_from_python(p, registered_pointee<T>::converters))
{
}

template <class T>
inline T pointer_arg_from_python<T>::operator()() const
{
    return (result() == Py_None) ? 0 : T(result());
}

// reference_arg_from_python
//
template <class T>
inline reference_arg_from_python<T>::reference_arg_from_python(PyObject* p)
    : arg_lvalue_from_python_base(converter::get_lvalue_from_python(p,registered<T>::converters))
{
}

template <class T>
inline T reference_arg_from_python<T>::operator()() const
{
    return python::detail::void_ptr_to_reference(result(), (T(*)())0);
}


// arg_rvalue_from_python
//
template <class T>
inline arg_rvalue_from_python<T>::arg_rvalue_from_python(PyObject* obj)
    : m_data(converter::rvalue_from_python_stage1(obj, registered<T>::converters))
    , m_source(obj)
{
}

template <class T>
inline bool arg_rvalue_from_python<T>::convertible() const
{
    return m_data.stage1.convertible != 0;
}

template <class T>
inline typename arg_rvalue_from_python<T>::result_type
arg_rvalue_from_python<T>::operator()()
{
    if (m_data.stage1.construct != 0)
        m_data.stage1.construct(m_source, &m_data.stage1);
    
    return python::detail::void_ptr_to_reference(m_data.stage1.convertible, (result_type(*)())0);
}

// back_reference_arg_from_python
//
template <class T>
back_reference_arg_from_python<T>::back_reference_arg_from_python(PyObject* x)
  : base(x), m_source(x)
{
}

template <class T>
inline T
back_reference_arg_from_python<T>::operator()()
{
    return T(m_source, base::operator()());
}

}}} // namespace boost::python::converter

#endif // ARG_FROM_PYTHON_DWA2002127_HPP

/* arg_from_python.hpp
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
*/