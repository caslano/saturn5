// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef FROM_PYTHON_AUX_DATA_DWA2002128_HPP
# define FROM_PYTHON_AUX_DATA_DWA2002128_HPP

# include <boost/python/converter/constructor_function.hpp>
# include <boost/python/detail/referent_storage.hpp>
# include <boost/python/detail/destroy.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <boost/align/align.hpp>
# include <boost/static_assert.hpp>
# include <cstddef>

// Data management for potential rvalue conversions from Python to C++
// types. When a client requests a conversion to T* or T&, we
// generally require that an object of type T exists in the source
// Python object, and the code here does not apply**. This implements
// conversions which may create new temporaries of type T. The classic
// example is a conversion which converts a Python tuple to a
// std::vector. Since no std::vector lvalue exists in the Python
// object -- it must be created "on-the-fly" by the converter, and
// which must manage the lifetime of the created object.
//
// Note that the client is not precluded from using a registered
// lvalue conversion to T in this case. In other words, we will
// happily accept a Python object which /does/ contain a std::vector
// lvalue, provided an appropriate converter is registered. So, while
// this is an rvalue conversion from the client's point-of-view, the
// converter registry may serve up lvalue or rvalue conversions for
// the target type.
//
// ** C++ argument from_python conversions to T const& are an
// exception to the rule for references: since in C++, const
// references can bind to temporary rvalues, we allow rvalue
// converters to be chosen when the target type is T const& for some
// T.
namespace boost { namespace python { namespace converter { 

// Conversions begin by filling in and returning a copy of this
// structure. The process looks up a converter in the rvalue converter
// registry for the target type. It calls the convertible() function
// of each registered converter, passing the source PyObject* as an
// argument, until a non-null result is returned. This result goes in
// the convertible field, and the converter's construct() function is
// stored in the construct field.
//
// If no appropriate converter is found, conversion fails and the
// convertible field is null. When used in argument conversion for
// wrapped C++ functions, it causes overload resolution to reject the
// current function but not to fail completely. If an exception is
// thrown, overload resolution stops and the exception propagates back
// through the caller.
//
// If an lvalue converter is matched, its convertible() function is
// expected to return a pointer to the stored T object; its
// construct() function will be NULL. The convertible() function of
// rvalue converters may return any non-singular pointer; the actual
// target object will only be available once the converter's
// construct() function is called.
struct rvalue_from_python_stage1_data
{
    void* convertible;
    constructor_function construct;
};

// Augments rvalue_from_python_stage1_data by adding storage for
// constructing an object of remove_reference<T>::type. The
// construct() function of rvalue converters (stored in m_construct
// above) will cast the rvalue_from_python_stage1_data to an
// appropriate instantiation of this template in order to access that
// storage.
template <class T>
struct rvalue_from_python_storage
{
    rvalue_from_python_stage1_data stage1;

    // Storage for the result, in case an rvalue must be constructed
    typename python::detail::referent_storage<
        typename boost::python::detail::add_lvalue_reference<T>::type
    >::type storage;
};

// Augments rvalue_from_python_storage<T> with a destructor. If
// stage1.convertible == storage.bytes, it indicates that an object of
// remove_reference<T>::type has been constructed in storage and
// should will be destroyed in ~rvalue_from_python_data(). It is
// crucial that successful rvalue conversions establish this equality
// and that unsuccessful ones do not.
template <class T>
struct rvalue_from_python_data : rvalue_from_python_storage<T>
{
# if (!defined(__MWERKS__) || __MWERKS__ >= 0x3000) \
        && (!defined(__EDG_VERSION__) || __EDG_VERSION__ >= 245) \
        && (!defined(__DECCXX_VER) || __DECCXX_VER > 60590014) \
        && !defined(BOOST_PYTHON_SYNOPSIS) /* Synopsis' OpenCXX has trouble parsing this */
    // This must always be a POD struct with m_data its first member.
    BOOST_STATIC_ASSERT(BOOST_PYTHON_OFFSETOF(rvalue_from_python_storage<T>,stage1) == 0);
# endif
    
    // The usual constructor 
    rvalue_from_python_data(rvalue_from_python_stage1_data const&);

    // This constructor just sets m_convertible -- used by
    // implicitly_convertible<> to perform the final step of the
    // conversion, where the construct() function is already known.
    rvalue_from_python_data(void* convertible);

    // Destroys any object constructed in the storage.
    ~rvalue_from_python_data();
 private:
    typedef typename boost::python::detail::add_lvalue_reference<
                typename boost::python::detail::add_cv<T>::type>::type ref_type;
};

//
// Implementataions
//
template <class T>
inline rvalue_from_python_data<T>::rvalue_from_python_data(rvalue_from_python_stage1_data const& _stage1)
{
    this->stage1 = _stage1;
}

template <class T>
inline rvalue_from_python_data<T>::rvalue_from_python_data(void* convertible)
{
    this->stage1.convertible = convertible;
}

template <class T>
inline rvalue_from_python_data<T>::~rvalue_from_python_data()
{
    if (this->stage1.convertible == this->storage.bytes)
    {
        size_t allocated = sizeof(this->storage);
        void *ptr = this->storage.bytes;
        void *aligned_storage =
            ::boost::alignment::align(boost::python::detail::alignment_of<T>::value, 0, ptr, allocated);
        python::detail::destroy_referent<ref_type>(aligned_storage);
    }
}

}}} // namespace boost::python::converter

#endif // FROM_PYTHON_AUX_DATA_DWA2002128_HPP

/* rvalue_from_python_data.hpp
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
*/