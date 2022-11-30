// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef EXTRACT_DWA200265_HPP
# define EXTRACT_DWA200265_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/converter/object_manager.hpp>
# include <boost/python/converter/from_python.hpp>
# include <boost/python/converter/rvalue_from_python_data.hpp>
# include <boost/python/converter/registered.hpp>
# include <boost/python/converter/registered_pointee.hpp>

# include <boost/python/object_core.hpp>
# include <boost/python/refcount.hpp>

# include <boost/python/detail/copy_ctor_mutates_rhs.hpp>
# include <boost/python/detail/void_ptr.hpp>
# include <boost/python/detail/void_return.hpp>
# include <boost/call_traits.hpp>

#if BOOST_WORKAROUND(BOOST_INTEL_WIN, <= 900)
# define BOOST_EXTRACT_WORKAROUND ()
#else
# define BOOST_EXTRACT_WORKAROUND
#endif

namespace boost { namespace python {

namespace api
{
  class object;
}

namespace converter
{
  template <class Ptr>
  struct extract_pointer
  {
      typedef Ptr result_type;
      extract_pointer(PyObject*);
      
      bool check() const;
      Ptr operator()() const;
      
   private:
      PyObject* m_source;
      void* m_result;
  };
  
  template <class Ref>
  struct extract_reference
  {
      typedef Ref result_type;
      extract_reference(PyObject*);
      
      bool check() const;
      Ref operator()() const;
      
   private:
      PyObject* m_source;
      void* m_result;
  };
  
  template <class T>
  struct extract_rvalue : private noncopyable
  {
      typedef typename mpl::if_<
          python::detail::copy_ctor_mutates_rhs<T>
        , T&
        , typename call_traits<T>::param_type
      >::type result_type;

      extract_rvalue(PyObject*);

      bool check() const;
      result_type operator()() const;
   private:
      PyObject* m_source;
      mutable rvalue_from_python_data<T> m_data;
  };
  
  template <class T>
  struct extract_object_manager
  {
      typedef T result_type;
      extract_object_manager(PyObject*);

      bool check() const;
      result_type operator()() const;
   private:
      PyObject* m_source;
  };
  
  template <class T>
  struct select_extract
  {
      BOOST_STATIC_CONSTANT(
          bool, obj_mgr = is_object_manager<T>::value);

      BOOST_STATIC_CONSTANT(
          bool, ptr = is_pointer<T>::value);
    
      BOOST_STATIC_CONSTANT(
          bool, ref = is_reference<T>::value);

      typedef typename mpl::if_c<
          obj_mgr
          , extract_object_manager<T>
          , typename mpl::if_c<
              ptr
              , extract_pointer<T>
              , typename mpl::if_c<
                  ref
                  , extract_reference<T>
                  , extract_rvalue<T>
                >::type
            >::type
         >::type type;
  };
}

template <class T>
struct extract
    : converter::select_extract<T>::type
{
 private:
    typedef typename converter::select_extract<T>::type base;
 public:
    typedef typename base::result_type result_type;
    
    operator result_type() const
    {
        return (*this)();
    }
    
    extract(PyObject*);
    extract(api::object const&);
};

//
// Implementations
//
template <class T>
inline extract<T>::extract(PyObject* o)
    : base(o)
{
}

template <class T>
inline extract<T>::extract(api::object const& o)
    : base(o.ptr())
{
}

namespace converter
{
  template <class T>
  inline extract_rvalue<T>::extract_rvalue(PyObject* x)
      : m_source(x)
      , m_data(
          (rvalue_from_python_stage1)(x, registered<T>::converters)
          )
  {
  }
  
  template <class T>
  inline bool
  extract_rvalue<T>::check() const
  {
      return m_data.stage1.convertible;
  }

  template <class T>
  inline typename extract_rvalue<T>::result_type
  extract_rvalue<T>::operator()() const
  {
      return *(T*)(
          // Only do the stage2 conversion once
          m_data.stage1.convertible ==  m_data.storage.bytes
             ? m_data.storage.bytes
             : (rvalue_from_python_stage2)(m_source, m_data.stage1, registered<T>::converters)
          );
  }

  template <class Ref>
  inline extract_reference<Ref>::extract_reference(PyObject* obj)
      : m_source(obj)
      , m_result(
          (get_lvalue_from_python)(obj, registered<Ref>::converters)
          )
  {
  }

  template <class Ref>
  inline bool extract_reference<Ref>::check() const
  {
      return m_result != 0;
  }

  template <class Ref>
  inline Ref extract_reference<Ref>::operator()() const
  {
      if (m_result == 0)
          (throw_no_reference_from_python)(m_source, registered<Ref>::converters);
      
      return python::detail::void_ptr_to_reference(m_result, (Ref(*)())0);
  }

  template <class Ptr>
  inline extract_pointer<Ptr>::extract_pointer(PyObject* obj)
      : m_source(obj)
      , m_result(
          obj == Py_None ? 0 : (get_lvalue_from_python)(obj, registered_pointee<Ptr>::converters)
          )
  {
  }

  template <class Ptr>
  inline bool extract_pointer<Ptr>::check() const
  {
      return m_source == Py_None || m_result != 0;
  }

  template <class Ptr>
  inline Ptr extract_pointer<Ptr>::operator()() const
  {
      if (m_result == 0 && m_source != Py_None)
          (throw_no_pointer_from_python)(m_source, registered_pointee<Ptr>::converters);
      
      return Ptr(m_result);
  }

  template <class T>
  inline extract_object_manager<T>::extract_object_manager(PyObject* obj)
      : m_source(obj)
  {
  }

  template <class T>
  inline bool extract_object_manager<T>::check() const
  {
      return object_manager_traits<T>::check(m_source);
  }

  template <class T>
  inline T extract_object_manager<T>::operator()() const
  {
      return T(
          object_manager_traits<T>::adopt(python::incref(m_source))
          );
  }
}
  
}} // namespace boost::python::converter

#endif // EXTRACT_DWA200265_HPP

/* extract.hpp
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
*/