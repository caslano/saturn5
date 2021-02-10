
#ifndef BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct as_sequence
    : if_< is_sequence<T>, T, single_view<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,as_sequence,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, as_sequence)

}}

#endif // BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED

/* as_sequence.hpp
0FnI3ptW+jqoHZnorPFGhclM05iow2nREVsb51O4UhixL0phR6Fbfhuxq660xvkKo/N15mNHtyK7rqHWYdX8JR6GIS6NbePeNhhSQ8LjS0e3kEKyXMaKkmvd0z1EjNgUk+0n276xY8SWASL4RY7gp+HR6s8/0ytQSwMECgAAAAgALWdKUgQ6qCG0AQAAcwMAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTE1VVQFAAG2SCRgvVPBbtswDL3rKwgMu62xnbUrYAgGhnZdi3VL0LgfoMh0LUSWPIlumr8fHTtegJ126cki+R75KD1LwkhaRSyEkMbVvhByh4e9D1UsxH1ZrkXbWzLi7uvD4/PTNxEwevuKQiZ/YTIZmUIG7OyhEB/gxvqIQA2C9s6hJuMdqJowHJO1CZEg4O+exy9gg4yqTjHsjbXQqK7DicMNB9btrw1opflEpkXfE6BVXcQIitltz9TYa41YAb4pTfYA1uzwbKJ3uBCyUqSycbskW2SwTFNY/RC3ijCHsuk/QfoZ7nDLhewSsus8vcwZ8v1nKTYYXjHkMFzbRTwGSa14RtxHPewsbuZ9c5gzhI4uykOHA/ONkoZaO+cf0b1Qk8MXIRq01vN9TgqPSpf/q3T53kqXk1J+
*/