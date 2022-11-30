// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef MAKE_PTR_INSTANCE_DWA200296_HPP
# define MAKE_PTR_INSTANCE_DWA200296_HPP

# include <boost/python/object/make_instance.hpp>
# include <boost/python/converter/registry.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <boost/get_pointer.hpp>
# include <boost/detail/workaround.hpp>
# include <typeinfo>

namespace boost { namespace python { namespace objects { 

template <class T, class Holder>
struct make_ptr_instance
    : make_instance_impl<T, Holder, make_ptr_instance<T,Holder> >
{
    template <class Arg>
    static inline Holder* construct(void* storage, PyObject*, Arg& x)
    {
#if defined(BOOST_NO_CXX11_SMART_PTR)
      return new (storage) Holder(x);
#else
      return new (storage) Holder(std::move(x));
#endif
    }
    
    template <class Ptr>
    static inline PyTypeObject* get_class_object(Ptr const& x)
    {
        return get_class_object_impl(get_pointer(x));
    }
#ifndef BOOST_PYTHON_NO_PY_SIGNATURES
    static inline PyTypeObject const* get_pytype()
    {
        return converter::registered<T>::converters.get_class_object();
    }
#endif
 private:
    template <class U>
    static inline PyTypeObject* get_class_object_impl(U const volatile* p)
    {
        if (p == 0)
            return 0; // means "return None".

        PyTypeObject* derived = get_derived_class_object(
            BOOST_DEDUCED_TYPENAME boost::python::detail::is_polymorphic<U>::type(), p);
        
        if (derived)
            return derived;
        return converter::registered<T>::converters.get_class_object();
    }
    
    template <class U>
    static inline PyTypeObject* get_derived_class_object(boost::python::detail::true_, U const volatile* x)
    {
        converter::registration const* r = converter::registry::query(
            type_info(typeid(*x))
        );
        return r ? r->m_class_object : 0;
    }
    
    template <class U>
    static inline PyTypeObject* get_derived_class_object(boost::python::detail::false_, U*)
    {
        return 0;
    }
};
  

}}} // namespace boost::python::object

#endif // MAKE_PTR_INSTANCE_DWA200296_HPP

/* make_ptr_instance.hpp
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
*/