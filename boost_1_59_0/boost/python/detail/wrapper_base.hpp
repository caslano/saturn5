// Copyright David Abrahams 2004. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef WRAPPER_BASE_DWA2004722_HPP
# define WRAPPER_BASE_DWA2004722_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/python/detail/type_traits.hpp>

namespace boost { namespace python {

class override;

namespace detail
{
  class wrapper_base;
  
  namespace wrapper_base_ // ADL disabler
  {
    inline PyObject* get_owner(wrapper_base const volatile& w);

    inline PyObject*
    owner_impl(void const volatile* /*x*/, detail::false_)
    {
        return 0;
    }
    
    template <class T>
    inline PyObject*
    owner_impl(T const volatile* x, detail::true_);
    
    template <class T>
    inline PyObject*
    owner(T const volatile* x)
    {
        return wrapper_base_::owner_impl(x,is_polymorphic<T>());
    }
  }
  
  class BOOST_PYTHON_DECL wrapper_base
  {
      friend void initialize_wrapper(PyObject* self, wrapper_base* w);
      friend PyObject* wrapper_base_::get_owner(wrapper_base const volatile& w);
   protected:
      wrapper_base() : m_self(0) {}
          
      override get_override(
          char const* name, PyTypeObject* class_object) const;

   private:
      void detach();
      
   private:
      PyObject* m_self;
  };

  namespace wrapper_base_ // ADL disabler
  {
    template <class T>
    inline PyObject*
    owner_impl(T const volatile* x, detail::true_)
    {
        if (wrapper_base const volatile* w = dynamic_cast<wrapper_base const volatile*>(x))
        {
            return wrapper_base_::get_owner(*w);
        }
        return 0;
    }
    
    inline PyObject* get_owner(wrapper_base const volatile& w)
    {
        return w.m_self;
    }
  }
  
  inline void initialize_wrapper(PyObject* self, wrapper_base* w)
  {
      w->m_self = self;
  }

  inline void initialize_wrapper(PyObject* /*self*/, ...) {}

  
  
} // namespace detail

}} // namespace boost::python

#endif // WRAPPER_BASE_DWA2004722_HPP

/* wrapper_base.hpp
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
*/