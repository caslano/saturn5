#ifndef BOOST_BIND_ARG_HPP_INCLUDED
#define BOOST_BIND_ARG_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  bind/arg.hpp
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

#include <boost/config.hpp>
#include <boost/is_placeholder.hpp>

namespace boost
{

template<bool Eq> struct _arg_eq
{
};

template<> struct _arg_eq<true>
{
    typedef void type;
};

template< int I > struct arg
{
    BOOST_CONSTEXPR arg()
    {
    }

    template< class T > BOOST_CONSTEXPR arg( T const & /* t */, typename _arg_eq< I == is_placeholder<T>::value >::type * = 0 )
    {
    }
};

template< int I > BOOST_CONSTEXPR bool operator==( arg<I> const &, arg<I> const & )
{
    return true;
}

#if !defined( BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION )

template< int I > struct is_placeholder< arg<I> >
{
    enum _vt { value = I };
};

template< int I > struct is_placeholder< arg<I> (*) () >
{
    enum _vt { value = I };
};

#endif

} // namespace boost

#endif // #ifndef BOOST_BIND_ARG_HPP_INCLUDED

/* arg.hpp
/ixPW783UNIOepkd9MkxqECS+v3hAD+7drPxHH5m8WcqS3flt/WlTs06isdqo9FwdaWseFV9Y0T1I67fr4l/vJFQNzd96fbObCN5/NrWB5B/ONnNIehTydhozBLf0v3MWQ6hn5sMo7Rl2k7mkL+d6jcOWQvdbF+X6VPiy00cU2z10NXXz2X+Rjw/U36dZpJwGXd0msuofD9ItC/6bWYs2hDJqO0OctutBz1If+u2xd+KNoGm
*/