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
7TjdHPQ8WLayMXllaMUedKwyYFKNaX54Ta6tQWWnwvwdf27hoNmup/jjIC3cgguaqRPBVYo1Zn5zgRsSJEMFMVaBUbRMWmD/MEMMkbnAIBQB6H5NXGT3YY67WnL0sJRu4Gx8pPf4piomo013Y1z3Oc6Ufm8xDfP4eBCL2477ymH7Dya3RI5puvqwmcM3SgAZ8OYOkXX/ANl+GtSqEA2g/TiMg7dNEbZC84QmR4B2CkFsgYGCFxdAXtg8orJRV2TnkMJaezX7jMKQRnqVDHwWP+NhfzpU4ML5mtyJG9ka+FXUPXstqXMtL3c9tyPzpJ/fNxhYEjLtZAq/k5q6N2P05rqnI967xdBnJkSgX69EKR/6D7FE5BJFVHC97be7jl8bGfiy0XdWC9TBNmD7V3iTpzg+1n+xYOfKo7UfwpCrlBoeYdkFH7icYyX/ZdqwKJsiUkHNPwIAvVgOkWaYVsWTtHD/nq7AJBIsrEHNRdcQfousaaca2GeYOO9JAAm3K0woEiBABD2Ab/+9pJ1WAe1uG/xWvDrg0wdboADbax6GouF4CSwRo9B0sDudPg==
*/