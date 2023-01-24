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
nVD7sRH9DM6e1fgysk71sV1cW4NIaoZnXb6PAxXHaqOLNEJQyAKU4zRKTVr2Su/1A8gds5qPtMt/cQs+j1xPZAqmHm+cNHRqrmzZuJVCSu+YlfI1GZBc5//g/S5v/DouIBibi0W1o38XFPaCs09lVqLQS5LotkvwWPNWcI7epdrkhli9XGjCq4yrOLRaso4qYk0juN2+go1JxA8mMfa+bU1a6flBxxPOZDKJncAnOxAiuZ33qX0BGupxMe2cyQ1cGfhl8G/FoB/oqaQXYSrSWQNpGiwYFsAquGmINrOwu37z6EUyesmAbA2+eVQ0QtfXyhq4RYi82b5EMsbDReh/2Quktzu+vmCZxqXlbVtIGqzLCIePpCH9nz2Z23uffL5L1S5QAoSsuEgB5SiZP9hqqSNwyrurAejWU0qqs+FEWfIfrtwD3MELDVCZAJlRZNueZMSYYJrpqKez3rSQyJLxB6EDJtW6R7hT/hLz1DVfGPeQkE6A3TpDSMuvJ8eBcdg2nqeRj7J6Tc59F0oETv01KzaBu9phDeK+4WsvdQIMCqbz+JHfLrisaPpELMGpkhVyQ8ab2rjl6Rh76ypj8w4myrE3DxDVv4htTs1E0wTXF2Nqhf/wjk4Tzd1BGDwa4QdNxs9fJbT+7SjQ9XLANFdwSzqn6CHOwvnXSt3EZT83lDJH3Ce6+y2JU+Ro288XhJMdHmnEscLGI4/4aN+1
*/