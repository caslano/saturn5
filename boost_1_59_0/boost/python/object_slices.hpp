// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef OBJECT_SLICES_DWA2002615_HPP
# define OBJECT_SLICES_DWA2002615_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/proxy.hpp>
# include <boost/python/object_core.hpp>
# include <boost/python/object_protocol.hpp>
# include <boost/python/handle.hpp>
# include <utility>

namespace boost { namespace python { namespace api {

struct const_slice_policies
{
    typedef std::pair<handle<>, handle<> > key_type;
    static object get(object const& target, key_type const& key);
};
  
struct slice_policies : const_slice_policies
{
    static object const& set(object const& target, key_type const& key, object const& value);
    static void del(object const& target, key_type const& key);
};

template <class T, class U>
inline slice_policies::key_type slice_key(T x, U y)
{
    return slice_policies::key_type(handle<>(x), handle<>(y));
}
    
//
// implementation
//
template <class U>
object_slice
object_operators<U>::slice(object_cref start, object_cref finish)
{
    object_cref2 x = *static_cast<U*>(this);
    return object_slice(x, api::slice_key(borrowed(start.ptr()), borrowed(finish.ptr())));
}

template <class U>
const_object_slice
object_operators<U>::slice(object_cref start, object_cref finish) const
{
    object_cref2 x = *static_cast<U const*>(this);
    return const_object_slice(x, api::slice_key(borrowed(start.ptr()), borrowed(finish.ptr())));
}

template <class U>
object_slice
object_operators<U>::slice(slice_nil, object_cref finish)
{
    object_cref2 x = *static_cast<U*>(this);
    return object_slice(x, api::slice_key(allow_null((PyObject*)0), borrowed(finish.ptr())));
}

template <class U>
const_object_slice
object_operators<U>::slice(slice_nil, object_cref finish) const
{
    object_cref2 x = *static_cast<U const*>(this);
    return const_object_slice(x, api::slice_key(allow_null((PyObject*)0), borrowed(finish.ptr())));
}

template <class U>
object_slice
object_operators<U>::slice(slice_nil, slice_nil)
{
    object_cref2 x = *static_cast<U*>(this);
    return object_slice(x, api::slice_key(allow_null((PyObject*)0), allow_null((PyObject*)0)));
}

template <class U>
const_object_slice
object_operators<U>::slice(slice_nil, slice_nil) const
{
    object_cref2 x = *static_cast<U const*>(this);
    return const_object_slice(x, api::slice_key(allow_null((PyObject*)0), allow_null((PyObject*)0)));
}

template <class U>
object_slice
object_operators<U>::slice(object_cref start, slice_nil)
{
    object_cref2 x = *static_cast<U*>(this);
    return object_slice(x, api::slice_key(borrowed(start.ptr()), allow_null((PyObject*)0)));
}

template <class U>
const_object_slice
object_operators<U>::slice(object_cref start, slice_nil) const
{
    object_cref2 x = *static_cast<U const*>(this);
    return const_object_slice(x, api::slice_key(borrowed(start.ptr()), allow_null((PyObject*)0)));
}

template <class U>
template <class T, class V>
inline const_object_slice
object_operators<U>::slice(T const& start, V const& end) const
{
    return this->slice(
        typename slice_bound<T>::type(start)
        , typename slice_bound<V>::type(end));
}

template <class U>
template <class T, class V>
inline object_slice
object_operators<U>::slice(T const& start, V const& end)
{
    return this->slice(
        typename slice_bound<T>::type(start)
        , typename slice_bound<V>::type(end));
}

inline object const_slice_policies::get(object const& target, key_type const& key)
{
    return getslice(target, key.first, key.second);
}

inline object const& slice_policies::set(
    object const& target
    , key_type const& key
    , object const& value)
{
    setslice(target, key.first, key.second, value);
    return value;
}

inline void slice_policies::del(
    object const& target
    , key_type const& key)
{
    delslice(target, key.first, key.second);
}

}}} // namespace boost::python::api

#endif // OBJECT_SLICES_DWA2002615_HPP

/* object_slices.hpp
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
*/