// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef ENUM_DWA200298_HPP
# define ENUM_DWA200298_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/object/enum_base.hpp>
# include <boost/python/converter/rvalue_from_python_data.hpp>
# include <boost/python/converter/registered.hpp>

namespace boost { namespace python { 

template <class T>
struct enum_ : public objects::enum_base
{
    typedef objects::enum_base base;

    // Declare a new enumeration type in the current scope()
    enum_(char const* name, char const* doc = 0);

    // Add a new enumeration value with the given name and value.
    inline enum_<T>& value(char const* name, T);

    // Add all of the defined enumeration values to the current scope with the
    // same names used here.
    inline enum_<T>& export_values();
 private:
    static PyObject* to_python(void const* x);
    static void* convertible_from_python(PyObject* obj);
    static void construct(PyObject* obj, converter::rvalue_from_python_stage1_data* data);
};

template <class T>
inline enum_<T>::enum_(char const* name, char const* doc )
    : base(
        name
        , &enum_<T>::to_python
        , &enum_<T>::convertible_from_python
        , &enum_<T>::construct
        , type_id<T>()
        , doc
        )
{
}

// This is the conversion function that gets registered for converting
// these enums to Python.
template <class T>
PyObject* enum_<T>::to_python(void const* x)
{
    return base::to_python(
        converter::registered<T>::converters.m_class_object
        , static_cast<long>(*(T const*)x));
}

//
// The following two static functions serve as the elements of an
// rvalue from_python converter for the enumeration type.
//

// This checks that a given Python object can be converted to the
// enumeration type.
template <class T>
void* enum_<T>::convertible_from_python(PyObject* obj)
{
    return PyObject_IsInstance(
        obj
        , upcast<PyObject>(
            converter::registered<T>::converters.m_class_object))
        
        ? obj : 0;
}

// Constructs an instance of the enumeration type in the from_python
// data.
template <class T>
void enum_<T>::construct(PyObject* obj, converter::rvalue_from_python_stage1_data* data)
{
#if PY_VERSION_HEX >= 0x03000000
    T x = static_cast<T>(PyLong_AS_LONG(obj));
#else
    T x = static_cast<T>(PyInt_AS_LONG(obj));
#endif
    void* const storage = ((converter::rvalue_from_python_storage<T>*)data)->storage.bytes;
    new (storage) T(x);
    data->convertible = storage;
}

template <class T>
inline enum_<T>& enum_<T>::value(char const* name, T x)
{
    this->add_value(name, static_cast<long>(x));
    return *this;
}

template <class T>
inline enum_<T>& enum_<T>::export_values()
{
    this->base::export_values();
    return *this;
}

}} // namespace boost::python

#endif // ENUM_DWA200298_HPP

/* enum.hpp
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
*/