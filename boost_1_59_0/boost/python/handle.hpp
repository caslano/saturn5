// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef HANDLE_DWA200269_HPP
# define HANDLE_DWA200269_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/cast.hpp>
# include <boost/python/errors.hpp>
# include <boost/python/borrowed.hpp>
# include <boost/python/handle_fwd.hpp>
# include <boost/python/refcount.hpp>
# include <boost/python/tag.hpp>
# include <boost/python/detail/raw_pyobject.hpp>

namespace boost { namespace python { 

template <class T> struct null_ok;

template <class T>
inline null_ok<T>* allow_null(T* p)
{
    return (null_ok<T>*)p;
}

namespace detail
{
  template <class T>
  inline T* manage_ptr(detail::borrowed<null_ok<T> >* p, int)
  {
      return python::xincref((T*)p);
  }
  
  template <class T>
  inline T* manage_ptr(null_ok<detail::borrowed<T> >* p, int)
  {
      return python::xincref((T*)p);
  }
  
  template <class T>
  inline T* manage_ptr(detail::borrowed<T>* p, long)
  {
      return python::incref(expect_non_null((T*)p));
  }
  
  template <class T>
  inline T* manage_ptr(null_ok<T>* p, long)
  {
      return (T*)p;
  }
  
  template <class T>
  inline T* manage_ptr(T* p, ...)
  {
      return expect_non_null(p);
  }
}

template <class T>
class handle
{
    typedef T* (handle::* bool_type )() const;

 public: // types
    typedef T element_type;
    
 public: // member functions
    handle();
    ~handle();

    template <class Y>
    explicit handle(Y* p)
        : m_p(
            python::upcast<T>(
                detail::manage_ptr(p, 0)
                )
            )
    {
    }

    handle& operator=(handle const& r)
    {
        python::xdecref(m_p);
        m_p = python::xincref(r.m_p);
        return *this;
    }

    template<typename Y>
    handle& operator=(handle<Y> const & r) // never throws
    {
        python::xdecref(m_p);
        m_p = python::xincref(python::upcast<T>(r.get()));
        return *this;
    }

    template <typename Y>
    handle(handle<Y> const& r)
        : m_p(python::xincref(python::upcast<T>(r.get())))
    {
    }
    
    handle(handle const& r)
        : m_p(python::xincref(r.m_p))
    {
    }
    
    T* operator-> () const;
    T& operator* () const;
    T* get() const;
    T* release();
    void reset();
    
    operator bool_type() const // never throws
    {
        return m_p ? &handle<T>::get : 0;
    }
    bool operator! () const; // never throws

 public: // implementation details -- do not touch
    // Defining this in the class body suppresses a VC7 link failure
    inline handle(detail::borrowed_reference x)
        : m_p(
            python::incref(
                downcast<T>((PyObject*)x)
                ))
    {
    }
    
 private: // data members
    T* m_p;
};

#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
} // namespace python
#endif

template<class T> inline T * get_pointer(python::handle<T> const & p)
{
    return p.get();
}

#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
namespace python {
#else

// We don't want get_pointer above to hide the others
using boost::get_pointer;

#endif

typedef handle<PyTypeObject> type_handle;

//
// Compile-time introspection
//
template<typename T>
class is_handle
{
 public:
    BOOST_STATIC_CONSTANT(bool, value = false); 
};

template<typename T>
class is_handle<handle<T> >
{
 public:
    BOOST_STATIC_CONSTANT(bool, value = true);
};

//
// implementations
//
template <class T>
inline handle<T>::handle()
    : m_p(0)
{
}

template <class T>
inline handle<T>::~handle()
{
    python::xdecref(m_p);
}

template <class T>
inline T* handle<T>::operator->() const
{
    return m_p;
}

template <class T>
inline T& handle<T>::operator*() const
{
    return *m_p;
}

template <class T>
inline T* handle<T>::get() const
{
    return m_p;
}
    
template <class T>
inline bool handle<T>::operator!() const
{
    return m_p == 0;
}

template <class T>
inline T* handle<T>::release()
{
    T* result = m_p;
    m_p = 0;
    return result;
}

template <class T>
inline void handle<T>::reset()
{
    python::xdecref(m_p);
    m_p = 0;
}

// Because get_managed_object must return a non-null PyObject*, we
// return Py_None if the handle is null.
template <class T>
inline PyObject* get_managed_object(handle<T> const& h, tag_t)
{
    return h.get() ? python::upcast<PyObject>(h.get()) : Py_None;
}

}} // namespace boost::python


#endif // HANDLE_DWA200269_HPP

/* handle.hpp
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
*/