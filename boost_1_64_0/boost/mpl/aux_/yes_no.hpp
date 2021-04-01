
#ifndef BOOST_MPL_AUX_YES_NO_HPP_INCLUDED
#define BOOST_MPL_AUX_YES_NO_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>


namespace boost { namespace mpl { namespace aux {

typedef char (&no_tag)[1];
typedef char (&yes_tag)[2];

template< bool C_ > struct yes_no_tag
{
    typedef no_tag type;
};

template<> struct yes_no_tag<true>
{
    typedef yes_tag type;
};


template< BOOST_MPL_AUX_NTTP_DECL(long, n) > struct weighted_tag
{
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    typedef char (&type)[n];
#else
    char buf[n];
    typedef weighted_tag type;
#endif
};

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
template<> struct weighted_tag<0>
{
    typedef char (&type)[1];
};
#endif

}}}

#endif // BOOST_MPL_AUX_YES_NO_HPP_INCLUDED

/* yes_no.hpp
Zq52IdGNnbDj3BxR+/6eXpZ8E/rE2dt3fHpVpsT3F+XqShPPo/sHx3alUnpH5qYhFbjrebuKgRVEbI3DvvcVxig4JFrI+Xal4mSJyWqbYbacZnDeUY5V5B6o0oOFK4nPvyvFjlLKKKrBEH+At2NiIOEXzU18CVom6uxgzyqpquTHoPmxHCjIhMH242h9+UpNdZh7rHt5mcQp5sQZIgHDQ+IpJFUmJAeRZFf64AcMgBjeqp4Tu96U24y0tG3tezY6BBb+f5l8xhKmb8JLR1RhHm5lPEWqH3w9lQyrmPFloFIDVM9FCeI/ogAiZdS0rOsF6Zev2L4Zry8yjQC6AVdbQQSijE7O09ezPm+e1QriFzByrAUL899fNt58yza6h9Z9TqrE3CKcZnZAqQBYU4gMqLwvsmIpnh9rzQpSRHPYFKor8FQkDNX1Z3ev+CiawF8Z2/kA+p/aO6jPGhl+rUc6GWN5c7GW9RCKg6lXX+8ZzAzLMMCedmADDcc1mL1MXV2z3XUKBCXRbdZJR6Y7CyGaYw+4qHo9/RcyCpnVCslQ8VlQjIPKA8drieg9Zg==
*/