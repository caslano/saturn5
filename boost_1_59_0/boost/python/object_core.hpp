// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef OBJECT_CORE_DWA2002615_HPP
# define OBJECT_CORE_DWA2002615_HPP

# define BOOST_PYTHON_OBJECT_HAS_IS_NONE // added 2010-03-15 by rwgk

# include <boost/python/detail/prefix.hpp>

# include <boost/type.hpp>

# include <boost/python/call.hpp>
# include <boost/python/handle_fwd.hpp>
# include <boost/python/errors.hpp>
# include <boost/python/refcount.hpp>
# include <boost/python/detail/preprocessor.hpp>
# include <boost/python/tag.hpp>
# include <boost/python/def_visitor.hpp>

# include <boost/python/detail/raw_pyobject.hpp>
# include <boost/python/detail/dependent.hpp>

# include <boost/python/object/forward.hpp>
# include <boost/python/object/add_to_namespace.hpp>

# include <boost/preprocessor/iterate.hpp>
# include <boost/preprocessor/debug/line.hpp>

# include <boost/python/detail/is_xxx.hpp>
# include <boost/python/detail/string_literal.hpp>
# include <boost/python/detail/def_helper_fwd.hpp>
# include <boost/python/detail/type_traits.hpp>

namespace boost { namespace python { 

namespace detail
{
  class kwds_proxy; 
  class args_proxy; 
} 

namespace converter
{
  template <class T> struct arg_to_python;
}

// Put this in an inner namespace so that the generalized operators won't take over
namespace api
{
  
// This file contains the definition of the object class and enough to
// construct/copy it, but not enough to do operations like
// attribute/item access or addition.

  template <class Policies> class proxy;
  
  struct const_attribute_policies;
  struct attribute_policies;
  struct const_objattribute_policies;
  struct objattribute_policies;
  struct const_item_policies;
  struct item_policies;
  struct const_slice_policies;
  struct slice_policies;
  class slice_nil;

  typedef proxy<const_attribute_policies> const_object_attribute;
  typedef proxy<attribute_policies> object_attribute;
  typedef proxy<const_objattribute_policies> const_object_objattribute;
  typedef proxy<objattribute_policies> object_objattribute;
  typedef proxy<const_item_policies> const_object_item;
  typedef proxy<item_policies> object_item;
  typedef proxy<const_slice_policies> const_object_slice;
  typedef proxy<slice_policies> object_slice;

  //
  // is_proxy -- proxy type detection
  //
  BOOST_PYTHON_IS_XXX_DEF(proxy, boost::python::api::proxy, 1)

  template <class T> struct object_initializer;
  
  class object;
  typedef PyObject* (object::*bool_type)() const;
  
  template <class U>
  class object_operators : public def_visitor<U>
  {
   protected:
      typedef object const& object_cref;
   public:
      // function call
      //
      object operator()() const;

# define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PYTHON_MAX_ARITY, <boost/python/object_call.hpp>))
# include BOOST_PP_ITERATE()
    
      detail::args_proxy operator* () const; 
      object operator()(detail::args_proxy const &args) const; 
      object operator()(detail::args_proxy const &args, 
                        detail::kwds_proxy const &kwds) const; 

      // truth value testing
      //
      operator bool_type() const;
      bool operator!() const; // needed for vc6

      // Attribute access
      //
      const_object_attribute attr(char const*) const;
      object_attribute attr(char const*);
      const_object_objattribute attr(object const&) const;
      object_objattribute attr(object const&);

      // Wrap 'in' operator (aka. __contains__)
      template <class T>
      object contains(T const& key) const;
      
      // item access
      //
      const_object_item operator[](object_cref) const;
      object_item operator[](object_cref);
    
      template <class T>
      const_object_item
      operator[](T const& key) const;
    
      template <class T>
      object_item
      operator[](T const& key);

      // slicing
      //
      const_object_slice slice(object_cref, object_cref) const;
      object_slice slice(object_cref, object_cref);

      const_object_slice slice(slice_nil, object_cref) const;
      object_slice slice(slice_nil, object_cref);
                             
      const_object_slice slice(object_cref, slice_nil) const;
      object_slice slice(object_cref, slice_nil);

      const_object_slice slice(slice_nil, slice_nil) const;
      object_slice slice(slice_nil, slice_nil);

      template <class T, class V>
      const_object_slice
      slice(T const& start, V const& end) const;
    
      template <class T, class V>
      object_slice
      slice(T const& start, V const& end);
      
   private: // def visitation for adding callable objects as class methods
      
      template <class ClassT, class DocStringT>
      void visit(ClassT& cl, char const* name, python::detail::def_helper<DocStringT> const& helper) const
      {
          // It's too late to specify anything other than docstrings if
          // the callable object is already wrapped.
          BOOST_STATIC_ASSERT(
              (detail::is_same<char const*,DocStringT>::value
               || detail::is_string_literal<DocStringT const>::value));
        
          objects::add_to_namespace(cl, name, this->derived_visitor(), helper.doc());
      }

      friend class python::def_visitor_access;
      
   private:
     // there is a confirmed CWPro8 codegen bug here. We prevent the
     // early destruction of a temporary by binding a named object
     // instead.
# if __MWERKS__ < 0x3000 || __MWERKS__ > 0x3003
    typedef object const& object_cref2;
# else
    typedef object const object_cref2;
# endif
  };

  
  // VC6 and VC7 require this base class in order to generate the
  // correct copy constructor for object. We can't define it there
  // explicitly or it will complain of ambiguity.
  struct object_base : object_operators<object>
  {
      // copy constructor without NULL checking, for efficiency. 
      inline object_base(object_base const&);
      inline object_base(PyObject* ptr);
      
      inline object_base& operator=(object_base const& rhs);
      inline ~object_base();
        
      // Underlying object access -- returns a borrowed reference
      inline PyObject* ptr() const;

      inline bool is_none() const;

   private:
      PyObject* m_ptr;
  };

  template <class T, class U>
  struct is_derived
    : boost::python::detail::is_convertible<
          typename detail::remove_reference<T>::type*
        , U const*
      >
  {};

  template <class T>
  typename objects::unforward_cref<T>::type do_unforward_cref(T const& x)
  {
      return x;
  }

  class object;
  
  template <class T>
  PyObject* object_base_initializer(T const& x)
  {
      typedef typename is_derived<
          BOOST_DEDUCED_TYPENAME objects::unforward_cref<T>::type
        , object
      >::type is_obj;

      return object_initializer<
          BOOST_DEDUCED_TYPENAME unwrap_reference<T>::type
      >::get(
            x
          , is_obj()
      );
  }
  
  class object : public object_base
  {
   public:
      // default constructor creates a None object
      object();
      
      // explicit conversion from any C++ object to Python
      template <class T>
      explicit object(T const& x)
        : object_base(object_base_initializer(x))
      {
      }

      // Throw error_already_set() if the handle is null.
      BOOST_PYTHON_DECL explicit object(handle<> const&);
   private:
      
   public: // implementation detail -- for internal use only
      explicit object(detail::borrowed_reference);
      explicit object(detail::new_reference);
      explicit object(detail::new_non_null_reference);
  };

  // Macros for forwarding constructors in classes derived from
  // object. Derived classes will usually want these as an
  // implementation detail
# define BOOST_PYTHON_FORWARD_OBJECT_CONSTRUCTORS(derived, base)               \
    inline explicit derived(::boost::python::detail::borrowed_reference p)     \
        : base(p) {}                                                           \
    inline explicit derived(::boost::python::detail::new_reference p)          \
        : base(p) {}                                                           \
    inline explicit derived(::boost::python::detail::new_non_null_reference p) \
        : base(p) {}

  //
  // object_initializer -- get the handle to construct the object with,
  // based on whether T is a proxy or derived from object
  //
  template <bool is_proxy = false, bool is_object_manager = false>
  struct object_initializer_impl
  {
      static PyObject*
      get(object const& x, detail::true_)
      {
          return python::incref(x.ptr());
      }
      
      template <class T>
      static PyObject*
      get(T const& x, detail::false_)
      {
          return python::incref(converter::arg_to_python<T>(x).get());
      }
  };
      
  template <>
  struct object_initializer_impl<true, false>
  {
      template <class Policies>
      static PyObject* 
      get(proxy<Policies> const& x, detail::false_)
      {
          return python::incref(x.operator object().ptr());
      }
  };

  template <>
  struct object_initializer_impl<false, true>
  {
      template <class T, class U>
      static PyObject*
      get(T const& x, U)
      {
          return python::incref(get_managed_object(x, boost::python::tag));
      }
  };

  template <>
  struct object_initializer_impl<true, true>
  {}; // empty implementation should cause an error

  template <class T>
  struct object_initializer : object_initializer_impl<
      is_proxy<T>::value
    , converter::is_object_manager<T>::value
  >
  {};

}
using api::object;
template <class T> struct extract;

//
// implementation
//

namespace detail 
{

class call_proxy 
{ 
public: 
  call_proxy(object target) : m_target(target) {} 
  operator object() const { return m_target;} 
 
 private: 
    object m_target; 
}; 
 
class kwds_proxy : public call_proxy 
{ 
public: 
  kwds_proxy(object o = object()) : call_proxy(o) {} 
}; 
class args_proxy : public call_proxy 
{ 
public: 
  args_proxy(object o) : call_proxy(o) {} 
  kwds_proxy operator* () const { return kwds_proxy(*this);} 
}; 
} 
 
template <typename U> 
detail::args_proxy api::object_operators<U>::operator* () const 
{ 
  object_cref2 x = *static_cast<U const*>(this); 
  return boost::python::detail::args_proxy(x); 
} 
 
template <typename U> 
object api::object_operators<U>::operator()(detail::args_proxy const &args) const 
{ 
  U const& self = *static_cast<U const*>(this); 
  PyObject *result = PyObject_Call(get_managed_object(self, boost::python::tag), 
                                   args.operator object().ptr(), 
                                   0); 
  return object(boost::python::detail::new_reference(result)); 
 
} 
 
template <typename U> 
object api::object_operators<U>::operator()(detail::args_proxy const &args, 
                                            detail::kwds_proxy const &kwds) const 
{ 
  U const& self = *static_cast<U const*>(this); 
  PyObject *result = PyObject_Call(get_managed_object(self, boost::python::tag), 
                                   args.operator object().ptr(), 
                                   kwds.operator object().ptr()); 
  return object(boost::python::detail::new_reference(result)); 
 
}  


template <typename U>
template <class T>
object api::object_operators<U>::contains(T const& key) const
{
    return this->attr("__contains__")(object(key));
}


inline object::object()
    : object_base(python::incref(Py_None))
{}

// copy constructor without NULL checking, for efficiency
inline api::object_base::object_base(object_base const& rhs)
    : m_ptr(python::incref(rhs.m_ptr))
{}

inline api::object_base::object_base(PyObject* p)
    : m_ptr(p)
{}

inline api::object_base& api::object_base::operator=(api::object_base const& rhs)
{
    Py_INCREF(rhs.m_ptr);
    Py_DECREF(this->m_ptr);
    this->m_ptr = rhs.m_ptr;
    return *this;
}

inline api::object_base::~object_base()
{
    assert( Py_REFCNT(m_ptr) > 0 );
    Py_DECREF(m_ptr);
}

inline object::object(detail::borrowed_reference p)
    : object_base(python::incref((PyObject*)p))
{}

inline object::object(detail::new_reference p)
    : object_base(expect_non_null((PyObject*)p))
{}

inline object::object(detail::new_non_null_reference p)
    : object_base((PyObject*)p)
{}

inline PyObject* api::object_base::ptr() const
{
    return m_ptr;
}

inline bool api::object_base::is_none() const
{
    return (m_ptr == Py_None);
}

//
// Converter specialization implementations
//
namespace converter
{
  template <class T> struct object_manager_traits;
  
  template <>
  struct object_manager_traits<object>
  {
      BOOST_STATIC_CONSTANT(bool, is_specialized = true);
      static bool check(PyObject*) { return true; }
      
      static python::detail::new_non_null_reference adopt(PyObject* x)
      {
          return python::detail::new_non_null_reference(x);
      }
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
      static PyTypeObject const *get_pytype() {return 0;}
#endif
  };
}

inline PyObject* get_managed_object(object const& x, tag_t)
{
    return x.ptr();
}

}} // namespace boost::python

# include <boost/python/slice_nil.hpp>

#endif // OBJECT_CORE_DWA2002615_HPP

/* object_core.hpp
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
*/