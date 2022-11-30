#ifndef BOOST_EXTENDED_TYPE_INFO_NO_RTTI_HPP
#define BOOST_EXTENDED_TYPE_INFO_NO_RTTI_HPP

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

// extended_type_info_no_rtti.hpp: implementation for version that depends
// on runtime typing (rtti - typeid) but uses a user specified string
// as the portable class identifier.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.
#include <boost/assert.hpp>

#include <boost/config.hpp>
#include <boost/static_assert.hpp>

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_polymorphic.hpp>
#include <boost/type_traits/remove_const.hpp>

#include <boost/serialization/static_warning.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/serialization/factory.hpp>
#include <boost/serialization/throw_exception.hpp>

#include <boost/serialization/config.hpp>
// hijack serialization access
#include <boost/serialization/access.hpp>

#include <boost/config/abi_prefix.hpp> // must be the last header
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4251 4231 4660 4275 4511 4512)
#endif

namespace boost {
namespace serialization {
///////////////////////////////////////////////////////////////////////
// define a special type_info that doesn't depend on rtti which is not
// available in all situations.

namespace no_rtti_system {

// common base class to share type_info_key.  This is used to
// identify the method used to keep track of the extended type
class BOOST_SYMBOL_VISIBLE extended_type_info_no_rtti_0 :
    public extended_type_info
{
protected:
    BOOST_SERIALIZATION_DECL extended_type_info_no_rtti_0(const char * key);
    BOOST_SERIALIZATION_DECL ~extended_type_info_no_rtti_0() BOOST_OVERRIDE;
public:
    BOOST_SERIALIZATION_DECL bool
    is_less_than(const boost::serialization::extended_type_info &rhs) const BOOST_OVERRIDE;
    BOOST_SERIALIZATION_DECL bool
    is_equal(const boost::serialization::extended_type_info &rhs) const BOOST_OVERRIDE;
};

} // no_rtti_system

template<class T>
class extended_type_info_no_rtti :
    public no_rtti_system::extended_type_info_no_rtti_0,
    public singleton<extended_type_info_no_rtti< T > >
{
    template<bool tf>
    struct action {
        struct defined {
            static const char * invoke(){
                return guid< T >();
            }
        };
        struct undefined {
            // if your program traps here - you failed to
            // export a guid for this type.  the no_rtti
            // system requires export for types serialized
            // as pointers.
            BOOST_STATIC_ASSERT(0 == sizeof(T));
            static const char * invoke();
        };
        static const char * invoke(){
            typedef
                typename boost::mpl::if_c<
                    tf,
                    defined,
                    undefined
                >::type type;
            return type::invoke();
        }
    };
public:
    extended_type_info_no_rtti() :
        no_rtti_system::extended_type_info_no_rtti_0(get_key())
    {
        key_register();
    }
    ~extended_type_info_no_rtti() BOOST_OVERRIDE {
        key_unregister();
    }
    const extended_type_info *
    get_derived_extended_type_info(const T & t) const {
        // find the type that corresponds to the most derived type.
        // this implementation doesn't depend on typeid() but assumes
        // that the specified type has a function of the following signature.
        // A common implemention of such a function is to define as a virtual
        // function. So if the is not a polymorphic type it's likely an error
        BOOST_STATIC_WARNING(boost::is_polymorphic< T >::value);
        const char * derived_key = t.get_key();
        BOOST_ASSERT(NULL != derived_key);
        return boost::serialization::extended_type_info::find(derived_key);
    }
    const char * get_key() const{
        return action<guid_defined< T >::value >::invoke();
    }
    const char * get_debug_info() const BOOST_OVERRIDE {
        return action<guid_defined< T >::value >::invoke();
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
        //delete static_cast<T const * const>(p) ;
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
            boost::serialization::extended_type_info_no_rtti< T > type;
    };
    } // namespace serialization
    } // namespace boost
#endif

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif
#include <boost/config/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_EXTENDED_TYPE_INFO_NO_RTTI_HPP

/* extended_type_info_no_rtti.hpp
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
*/