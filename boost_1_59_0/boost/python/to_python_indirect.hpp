// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef TO_PYTHON_INDIRECT_DWA200221_HPP
# define TO_PYTHON_INDIRECT_DWA200221_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/object/pointer_holder.hpp>
# include <boost/python/object/make_ptr_instance.hpp>

# include <boost/python/detail/none.hpp>

#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
# include <boost/python/converter/pytype_function.hpp>
#endif

# include <boost/python/refcount.hpp>

# include <boost/python/detail/type_traits.hpp>

# if defined(__ICL) && __ICL < 600 
#  include <boost/shared_ptr.hpp>
# else 
#  include <memory>
# endif

namespace boost { namespace python {

template <class T, class MakeHolder>
struct to_python_indirect
{
    template <class U>
    inline PyObject*
    operator()(U const& ref) const
    {
        return this->execute(const_cast<U&>(ref), detail::is_pointer<U>());
    }
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
    inline PyTypeObject const*
    get_pytype()const
    {
        return converter::registered_pytype<T>::get_pytype();
    }
#endif
 private:
    template <class U>
    inline PyObject* execute(U* ptr, detail::true_) const
    {
        // No special NULL treatment for references
        if (ptr == 0)
            return python::detail::none();
        else
            return this->execute(*ptr, detail::false_());
    }
    
    template <class U>
    inline PyObject* execute(U const& x, detail::false_) const
    {
        U* const p = &const_cast<U&>(x);
        if (detail::is_polymorphic<U>::value)
        {
            if (PyObject* o = detail::wrapper_base_::owner(p))
                return incref(o);
        }
        return MakeHolder::execute(p);
    }
};

//
// implementations
//
namespace detail
{
  struct make_owning_holder
  {
      template <class T>
      static PyObject* execute(T* p)
      {
          // can't use auto_ptr with Intel 5 and VC6 Dinkum library
          // for some reason. We get link errors against the auto_ptr
          // copy constructor.
# if defined(__ICL) && __ICL < 600 
          typedef boost::shared_ptr<T> smart_pointer;
# elif defined(BOOST_NO_CXX11_SMART_PTR)
          typedef std::auto_ptr<T> smart_pointer;
# else
          typedef std::unique_ptr<T> smart_pointer;
# endif
          typedef objects::pointer_holder<smart_pointer, T> holder_t;

          smart_pointer ptr(const_cast<T*>(p));
          return objects::make_ptr_instance<T, holder_t>::execute(ptr);
      }
  };

  struct make_reference_holder
  {
      template <class T>
      static PyObject* execute(T* p)
      {
          typedef objects::pointer_holder<T*, T> holder_t;
          T* q = const_cast<T*>(p);
          return objects::make_ptr_instance<T, holder_t>::execute(q);
      }
  };
}

}} // namespace boost::python

#endif // TO_PYTHON_INDIRECT_DWA200221_HPP

/* to_python_indirect.hpp
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
*/