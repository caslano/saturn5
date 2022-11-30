#ifndef BOOST_CORE_TYPEINFO_HPP_INCLUDED
#define BOOST_CORE_TYPEINFO_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  core::typeinfo, BOOST_CORE_TYPEID
//
//  Copyright 2007, 2014 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined( BOOST_NO_TYPEID )

#include <boost/current_function.hpp>
#include <functional>
#include <cstring>

namespace boost
{

namespace core
{

class typeinfo
{
private:

    typeinfo( typeinfo const& );
    typeinfo& operator=( typeinfo const& );

    char const * name_;
    void (*lib_id_)();

public:

    typeinfo( char const * name, void (*lib_id)() ): name_( name ), lib_id_( lib_id )
    {
    }

    bool operator==( typeinfo const& rhs ) const
    {
#if ( defined(_WIN32) || defined(__CYGWIN__) ) && ( defined(__GNUC__) || defined(__clang__) ) && !defined(BOOST_DISABLE_CURRENT_FUNCTION)

        return lib_id_ == rhs.lib_id_? this == &rhs: std::strcmp( name_, rhs.name_ ) == 0;

#else

        return this == &rhs;

#endif
    }

    bool operator!=( typeinfo const& rhs ) const
    {
        return !( *this == rhs );
    }

    bool before( typeinfo const& rhs ) const
    {
#if ( defined(_WIN32) || defined(__CYGWIN__) ) && ( defined(__GNUC__) || defined(__clang__) ) && !defined(BOOST_DISABLE_CURRENT_FUNCTION)

        return lib_id_ == rhs.lib_id_? std::less< typeinfo const* >()( this, &rhs ): std::strcmp( name_, rhs.name_ ) < 0;

#else

        return std::less< typeinfo const* >()( this, &rhs );

#endif
    }

    char const* name() const
    {
        return name_;
    }
};

inline char const * demangled_name( core::typeinfo const & ti )
{
    return ti.name();
}

} // namespace core

namespace detail
{

template<class T> struct BOOST_SYMBOL_VISIBLE core_typeid_
{
    static boost::core::typeinfo ti_;

    static char const * name()
    {
        return BOOST_CURRENT_FUNCTION;
    }
};

BOOST_SYMBOL_VISIBLE inline void core_typeid_lib_id()
{
}

template<class T> boost::core::typeinfo core_typeid_< T >::ti_( core_typeid_< T >::name(), &core_typeid_lib_id );

template<class T> struct core_typeid_< T & >: core_typeid_< T >
{
};

template<class T> struct core_typeid_< T const >: core_typeid_< T >
{
};

template<class T> struct core_typeid_< T volatile >: core_typeid_< T >
{
};

template<class T> struct core_typeid_< T const volatile >: core_typeid_< T >
{
};

} // namespace detail

} // namespace boost

#define BOOST_CORE_TYPEID(T) (boost::detail::core_typeid_<T>::ti_)

#else

#include <boost/core/demangle.hpp>
#include <typeinfo>

namespace boost
{

namespace core
{

#if defined( BOOST_NO_STD_TYPEINFO )

typedef ::type_info typeinfo;

#else

typedef std::type_info typeinfo;

#endif

inline std::string demangled_name( core::typeinfo const & ti )
{
    return core::demangle( ti.name() );
}

} // namespace core

} // namespace boost

#define BOOST_CORE_TYPEID(T) typeid(T)

#endif

#endif  // #ifndef BOOST_CORE_TYPEINFO_HPP_INCLUDED

/* typeinfo.hpp
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
*/