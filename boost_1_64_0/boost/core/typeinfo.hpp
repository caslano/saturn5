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
lk/HxmXWpFwcDceU9RePBo2Gy5J4mcZP+PwtwLFRbXn3BnTYWKTTffMzDZDwvC+gRcVavf5D0eH8FxULtvQvgU6RYTv+26dh5aJO/uPRuMpN52WUCzbxkECDCk7oHhHoUMHrGuBnFAzlt5zg06OSbbs9iunwo4tqRh0eKNM6OnxMSGNVDeU+NqQLbLk9nadRecLvYJEGVW7LPiSkDex6XWN8jeoT3k8Q6WX7fmJCO5LPF6t182mOvPWGQ4mOfKOuob5OJVy2e9huyiY0hwc0ZkHbvtEn0JCvar41RxDO35rsruG49Y0MrUZWWq0vUQjC/HS9MjbmrCseyTTa+9BmNFWZyqMPuZho1GcfUCPf0Segr84grAe1GZxCATCcYEsMVpvk5SAjezth6PtKZS9LaKbVbaOZvDp+jLG/lrPuuruzQ0O5nuxQN0URH+7t77NNYdr1+DRab598Beubd8KdOEErCZMKw3o93CrR6DZX6+CriUfbEv2W3fuaXgffI9yteOJyyS87AcYaFYNA63cPnc5y38Ps9Oj8Pb6Mh2u3l04L8d2ltpTySNR6FfCNHu5/h0/y8SmX/8mEUxSiqBgzpm29qWInjkenSPnVoAU8nubR+Gt7z/BwPecjAwUeXUxD2FSBIKUGrEe3h/v1yPo4y5DY9BaL1+nI/awZgHgXuvm5gRT779jl0r7kVi6b126U9Zu++CzG4tkVTZ/8ue427Dd85x3HiT4nf71CLOx7RpyXp1TFGt0v6JsujxbhfuEA0qhYLhNFHUa1XjMy4jy0FEXTxZp7XmEwkUEbEo0qLfqsGKU/Z4k+F3JZ032yWgv3plaBfq2Odnrff8rqxKJ9HuHuuoUbJ2l3gIfv+7yQaHDNwS/jRTzWx+1QKjBs+8Co/d7Q55Fqri7tMFVCU2AaO/tlAlgTGGMaUz6k00sPdLO5RO6H6qOKyuJ7CHfWy5hBB+Mrj5PnzPSPc2+sTHwKdFBxhE4tZ/B9OeShdODlbwtoapPqUGtUmVIkTa6bRbWZwDaeItpGDevd20Ndv57fA3id9cmmzz2MbUPIHxVjX4hI90kTryglNDOCv6DUhOPkbEjDWoT3hk6Q1o5CH+kskc71gV7qlqeszvT5lyVYqQCRJCGmN+Pqmh4Nt5oGxp4W3w8pkSnw/ZWOFBrmFfiOL/fosEzU3ytP8GyYTyA1P7bPjO0N7OvZon29ytEhB8ED/NU8LvAyndKA0x9eK+B0aMLENDqfcI5LHn83TNy2E+wZY8IJsnp9Q2LTQ8P9g9nki0ttX6tWoqKle2NAp6cl+T0jJTyPeAHLqH1V/gQA/jNeT2W8XpuOnD3GC/32Yy2ZGGzMX+GunmBNn2XVOPUuXrclmn3Um+UBXvcfi/WJp2zj6tIf8noHfBftiM1Rveako3NmanjQN8dNe73T02EBYoNdzJgenFi/pULjYyIt2Kh/Qx82J/ojp7fq/SiVh6cGNj7b4XpfA7HEFmdbFVYz5y7bvHQ919GTJfxmIK7G/VIhzMvlxdoR8qI8cl5yb2ZK+SLNZcw37b3p85jpMowvl6bRsRtg5mSkRSuHe87jvMMQc88WPJl+R6RvrGOjY1K1WFY/6rCvcN5uCtoX9nLYF1B3RtTzAAP6PQrnjdrLkcYSmPpcSbiKG6FXYqMR7s8i/9zAjs0UCrQlDY+jnEawB4R4tnvg2QM2xH9C82GXBiSEPRqUkXTK9ZPys4h2XeTjiPdlh4e6uwaysYOeG1JeZF931ujik0irHh452fYX1CMXYurwKcQGsR1s/s9gHWpaz6n540iLWgdtIk3YFtcCrr8itAkM+b8Q4OT+Qt/4EuLkVvr21D4HHehDpAHbMOU=
*/