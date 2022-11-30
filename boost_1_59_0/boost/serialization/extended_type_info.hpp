#ifndef BOOST_SERIALIZATION_EXTENDED_TYPE_INFO_HPP
#define BOOST_SERIALIZATION_EXTENDED_TYPE_INFO_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// extended_type_info.hpp: interface for portable version of type_info

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// for now, extended type info is part of the serialization libraries
// this could change in the future.
#include <cstdarg>
#include <boost/assert.hpp>
#include <cstddef> // NULL
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/serialization/config.hpp>
#include <boost/config/abi_prefix.hpp> // must be the last header
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4251 4231 4660 4275)
#endif

#define BOOST_SERIALIZATION_MAX_KEY_SIZE 128

namespace boost {
namespace serialization {

namespace void_cast_detail{
    class void_caster;
}

class BOOST_SYMBOL_VISIBLE extended_type_info :
    private boost::noncopyable
{
private:
    friend class boost::serialization::void_cast_detail::void_caster;

    // used to uniquely identify the type of class derived from this one
    // so that different derivations of this class can be simultaneously
    // included in implementation of sets and maps.
    const unsigned int m_type_info_key;
    virtual bool is_less_than(const extended_type_info & /*rhs*/) const = 0;
    virtual bool is_equal(const extended_type_info & /*rhs*/) const = 0;
    const char * m_key;

protected:
    BOOST_SERIALIZATION_DECL void key_unregister() const;
    BOOST_SERIALIZATION_DECL void key_register() const;
    // this class can't be used as is. It's just the
    // common functionality for all type_info replacement
    // systems.  Hence, make these protected
    BOOST_SERIALIZATION_DECL extended_type_info(
        const unsigned int type_info_key,
        const char * key
    );
    virtual BOOST_SERIALIZATION_DECL ~extended_type_info();
public:
    const char * get_key() const {
        return m_key;
    }
    virtual const char * get_debug_info() const = 0;
    BOOST_SERIALIZATION_DECL bool operator<(const extended_type_info &rhs) const;
    BOOST_SERIALIZATION_DECL bool operator==(const extended_type_info &rhs) const;
    bool operator!=(const extended_type_info &rhs) const {
        return !(operator==(rhs));
    }
    // note explicit "export" of static function to work around
    // gcc 4.5 mingw error
    static BOOST_SERIALIZATION_DECL const extended_type_info *
    find(const char *key);
    // for plugins
    virtual void * construct(unsigned int /*count*/ = 0, ...) const = 0;
    virtual void destroy(void const * const /*p*/) const = 0;
};

template<class T>
struct guid_defined : boost::mpl::false_ {};

namespace ext {
    template <typename T>
    struct guid_impl
    {
        static inline const char * call()
        {
            return NULL;
        }
    };
}

template<class T>
inline const char * guid(){
    return ext::guid_impl<T>::call();
}

} // namespace serialization
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/config/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_SERIALIZATION_EXTENDED_TYPE_INFO_HPP

/* extended_type_info.hpp
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
*/