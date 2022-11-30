// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef OBJECT_ATTRIBUTES_DWA2002615_HPP
# define OBJECT_ATTRIBUTES_DWA2002615_HPP

# include <boost/python/detail/prefix.hpp>

# include <boost/python/proxy.hpp>
# include <boost/python/object_core.hpp>
# include <boost/python/object_protocol.hpp>

namespace boost { namespace python { namespace api {

struct const_attribute_policies
{
    typedef char const* key_type;
    static object get(object const& target, char const* key);
    static object get(object const& target, object const& key);
};
  
struct attribute_policies : const_attribute_policies
{
    static object const& set(object const& target, char const* key, object const& value);
    static void del(object const&target, char const* key);
};

struct const_objattribute_policies
{
    typedef object const key_type;
    static object get(object const& target, object const& key);
};
  
struct objattribute_policies : const_objattribute_policies
{
    static object const& set(object const& target, object const& key, object const& value);
    static void del(object const&target, object const& key);
};

//
// implementation
//
template <class U>
inline object_attribute object_operators<U>::attr(char const* name)
{
    object_cref2 x = *static_cast<U*>(this);
    return object_attribute(x, name);
}

template <class U>
inline const_object_attribute object_operators<U>::attr(char const* name) const
{
    object_cref2 x = *static_cast<U const*>(this);
    return const_object_attribute(x, name);
}

template <class U>
inline object_objattribute object_operators<U>::attr(object const& name)
{
    object_cref2 x = *static_cast<U*>(this);
    return object_objattribute(x, name);
}

template <class U>
inline const_object_objattribute object_operators<U>::attr(object const& name) const
{
    object_cref2 x = *static_cast<U const*>(this);
    return const_object_objattribute(x, name);
}

inline object const_attribute_policies::get(object const& target, char const* key)
{
    return python::getattr(target, key);
}

inline object const_objattribute_policies::get(object const& target, object const& key)
{
    return python::getattr(target, key);
}

inline object const& attribute_policies::set(
    object const& target
    , char const* key
    , object const& value)
{
    python::setattr(target, key, value);
    return value;
}

inline object const& objattribute_policies::set(
    object const& target
    , object const& key
    , object const& value)
{
    python::setattr(target, key, value);
    return value;
}

inline void attribute_policies::del(
    object const& target
    , char const* key)
{
    python::delattr(target, key);
}

inline void objattribute_policies::del(
    object const& target
    , object const& key)
{
    python::delattr(target, key);
}

}}} // namespace boost::python::api

#endif // OBJECT_ATTRIBUTES_DWA2002615_HPP

/* object_attributes.hpp
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
*/