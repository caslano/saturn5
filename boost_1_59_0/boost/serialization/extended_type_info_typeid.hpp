#ifndef BOOST_SERIALIZATION_EXTENDED_TYPE_INFO_TYPEID_HPP
#define BOOST_SERIALIZATION_EXTENDED_TYPE_INFO_TYPEID_HPP

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

// extended_type_info_typeid.hpp: implementation for version that depends
// on runtime typing (rtti - typeid) but uses a user specified string
// as the portable class identifier.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <typeinfo>
#include <cstdarg>
#include <boost/assert.hpp>
#include <boost/config.hpp>

#include <boost/static_assert.hpp>
#include <boost/serialization/static_warning.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/serialization/config.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/serialization/factory.hpp>

// hijack serialization access
#include <boost/serialization/access.hpp>

#include <boost/mpl/if.hpp>

#include <boost/config/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4251 4231 4660 4275 4511 4512)
#endif

namespace boost {
namespace serialization {
namespace typeid_system {

class BOOST_SYMBOL_VISIBLE extended_type_info_typeid_0 :
    public extended_type_info
{
    const char * get_debug_info() const BOOST_OVERRIDE {
        if(static_cast<const std::type_info *>(0) == m_ti)
            return static_cast<const char *>(0);
        return m_ti->name();
    }
protected:
    const std::type_info * m_ti;
    BOOST_SERIALIZATION_DECL extended_type_info_typeid_0(const char * key);
    BOOST_SERIALIZATION_DECL ~extended_type_info_typeid_0() BOOST_OVERRIDE;
    BOOST_SERIALIZATION_DECL void type_register(const std::type_info & ti);
    BOOST_SERIALIZATION_DECL void type_unregister();
    BOOST_SERIALIZATION_DECL const extended_type_info *
    get_extended_type_info(const std::type_info & ti) const;
public:
    BOOST_SERIALIZATION_DECL bool
    is_less_than(const extended_type_info &rhs) const BOOST_OVERRIDE;
    BOOST_SERIALIZATION_DECL bool
    is_equal(const extended_type_info &rhs) const BOOST_OVERRIDE;
    const std::type_info & get_typeid() const {
        return *m_ti;
    }
};

} // typeid_system

template<class T>
class extended_type_info_typeid :
    public typeid_system::extended_type_info_typeid_0,
    public singleton<extended_type_info_typeid< T > >
{
public:
    extended_type_info_typeid() :
        typeid_system::extended_type_info_typeid_0(
            boost::serialization::guid< T >()
        )
    {
        type_register(typeid(T));
        key_register();
    }
    ~extended_type_info_typeid() BOOST_OVERRIDE {
        key_unregister();
        type_unregister();
    }
    // get the eti record for the true type of this record
    // relying upon standard type info implemenation (rtti)
    const extended_type_info *
    get_derived_extended_type_info(const T & t) const {
        // note: this implementation - based on usage of typeid (rtti)
        // only does something if the class has at least one virtual function.
        BOOST_STATIC_WARNING(boost::is_polymorphic< T >::value);
        return
            typeid_system::extended_type_info_typeid_0::get_extended_type_info(
                typeid(t)
            );
    }
    const char * get_key() const {
        return boost::serialization::guid< T >();
    }
    void * construct(unsigned int count, ...) const BOOST_OVERRIDE {
        // count up the arguments
        std::va_list ap;
        va_start(ap, count);
        switch(count){
        case 0:
            return factory<typename boost::remove_const< T >::type, 0>(ap);
        case 1:
            return factory<typename boost::remove_const< T >::type, 1>(ap);
        case 2:
            return factory<typename boost::remove_const< T >::type, 2>(ap);
        case 3:
            return factory<typename boost::remove_const< T >::type, 3>(ap);
        case 4:
            return factory<typename boost::remove_const< T >::type, 4>(ap);
        default:
            BOOST_ASSERT(false); // too many arguments
            // throw exception here?
            return NULL;
        }
    }
    void destroy(void const * const p) const BOOST_OVERRIDE {
        boost::serialization::access::destroy(
            static_cast<T const *>(p)
        );
        //delete static_cast<T const * const>(p);
    }
};

} // namespace serialization
} // namespace boost

///////////////////////////////////////////////////////////////////////////////
// If no other implementation has been designated as default,
// use this one.  To use this implementation as the default, specify it
// before any of the other headers.
#ifndef BOOST_SERIALIZATION_DEFAULT_TYPE_INFO
    #define BOOST_SERIALIZATION_DEFAULT_TYPE_INFO
    namespace boost {
    namespace serialization {
    template<class T>
    struct extended_type_info_impl {
        typedef typename
            boost::serialization::extended_type_info_typeid< T > type;
    };
    } // namespace serialization
    } // namespace boost
#endif

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
#include <boost/config/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_SERIALIZATION_EXTENDED_TYPE_INFO_TYPEID_HPP

/* extended_type_info_typeid.hpp
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
*/