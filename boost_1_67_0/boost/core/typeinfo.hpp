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