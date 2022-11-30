// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef MAKE_INSTANCE_DWA200296_HPP
# define MAKE_INSTANCE_DWA200296_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/python/object/instance.hpp>
# include <boost/python/converter/registered.hpp>
# include <boost/python/detail/decref_guard.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <boost/python/detail/none.hpp>
# include <boost/mpl/assert.hpp>
# include <boost/mpl/or.hpp>

namespace boost { namespace python { namespace objects { 

template <class T, class Holder, class Derived>
struct make_instance_impl
{
    typedef objects::instance<Holder> instance_t;
        
    template <class Arg>
    static inline PyObject* execute(Arg& x)
    {
        BOOST_MPL_ASSERT((mpl::or_<boost::python::detail::is_class<T>,
                boost::python::detail::is_union<T> >));

        PyTypeObject* type = Derived::get_class_object(x);

        if (type == 0)
            return python::detail::none();

        PyObject* raw_result = type->tp_alloc(
            type, objects::additional_instance_size<Holder>::value);
          
        if (raw_result != 0)
        {
            python::detail::decref_guard protect(raw_result);
            
            instance_t* instance = (instance_t*)raw_result;
            
            // construct the new C++ object and install the pointer
            // in the Python object.
            Holder *holder =Derived::construct(instance->storage.bytes, (PyObject*)instance, x);
            holder->install(raw_result);
              
            // Note the position of the internally-stored Holder,
            // for the sake of destruction
            const size_t offset = reinterpret_cast<size_t>(holder) -
              reinterpret_cast<size_t>(instance->storage.bytes) + offsetof(instance_t, storage);
            Py_SET_SIZE(instance, offset);

            // Release ownership of the python object
            protect.cancel();
        }
        return raw_result;
    }
};
    

template <class T, class Holder>
struct make_instance
    : make_instance_impl<T, Holder, make_instance<T,Holder> >
{
    template <class U>
    static inline PyTypeObject* get_class_object(U&)
    {
        return converter::registered<T>::converters.get_class_object();
    }
    
    static inline Holder* construct(void* storage, PyObject* instance, reference_wrapper<T const> x)
    {
        size_t allocated = objects::additional_instance_size<Holder>::value;
        void* aligned_storage = ::boost::alignment::align(boost::python::detail::alignment_of<Holder>::value,
                                                          sizeof(Holder), storage, allocated);
        return new (aligned_storage) Holder(instance, x);
    }
};
  

}}} // namespace boost::python::object

#endif // MAKE_INSTANCE_DWA200296_HPP

/* make_instance.hpp
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
*/