#ifndef BOOST_CORE_IS_SAME_HPP_INCLUDED
#define BOOST_CORE_IS_SAME_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// is_same<T1,T2>::value is true when T1 == T2
//
// Copyright 2014 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/config.hpp>

namespace boost
{

namespace core
{

template< class T1, class T2 > struct is_same
{
    BOOST_STATIC_CONSTANT( bool, value = false );
};

template< class T > struct is_same< T, T >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

} // namespace core

} // namespace boost

#endif // #ifndef BOOST_CORE_IS_SAME_HPP_INCLUDED

/* is_same.hpp
0BxVaytYfbq3w7XFXw1QZsb3WUe0cU//kysrbzO0x2FJ6srzyeLN8UVZSnoe7bqmRWT6AtuOjFkAeNYMCFN64NjQqS/SUptKcRqbtfNBNl/ynVzckAh3YPEr3cU6DOF4d5Yr6VzODXhc37vD16mr9MLXTF74OVyEr/fBecQ7dzEmfr/YDttzuSRKU6WYbuR6MsJxH4cLUW2H+lGqeXlC+EMXpJexPsOg0BoBUcnTG+WN9WLcztEyMpjEH8v9y8fCpBXCSjugnPSI5cohjH5cHnjnQDsS8ixXFgsOy4l3HjiSlyYKZWF9gqBsj96UpTaxuWuE+eLCKZlyPUGtVKr4usO6cCSKTZxhw8EW+GP5lpemqQzlCi03F4hwDauP2HdkpQqDSpmkKlEUTcc9UYec0F9YdBFsDn6xJsoo7JVyl3zUCeB6BT/cIhznRFwlH0xg8CQdm0DD/AsY3Qvh5kyALu6tavRH31lVC/HTVSWgxVTM42M4JciPt+STnwFnKGZOhRCFS4uL1M6Sa3sYPiY1GWFJ0M6+koAFAixdBfoHWgtrVNjL5Sn5MlrAy1SaYsiV5TcHdJGLZEkFw8XrzHXj7InteewTgTrCrrH+MKKe2ZRKTldlszo89QHoPxXoU20RjBcIr+2I/avn+QxFCYt3py3WxYluiUYdKscMHU9H74v2roPeDM9SGNQKrQlxuG/Tndzrl2g05z4ddWdt
*/