
#ifndef BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// default implementation, requires at least bi-directional iterators;
// conrete sequences might override it by specializing either the 
// 'back_impl' or the primary 'back' template

template< typename Tag >
struct back_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename end<Sequence>::type end_;
        typedef typename prior<end_>::type last_;
        typedef typename deref<last_>::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, back_impl)

}}

#endif // BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED

/* back_impl.hpp
4Ro2OHZ8GL44Y22upmf25yBEeoOEyqs10MP3EuwrXt/5pmOUQHoi6Rdk5Ptf5uHS13shmCoaV1guZtPDNa89HmTOVk/AStZcsAb6RZwfj+n3qxEj/l68lZqB0vVKb6If/gdb2cg8gu2Wyw2dyOUmTmtlOLbZM2/MpZmnvwG4M2luDVE5eJhqJNcqD/7q3F4AwFMdFG/84dGQr03vWxoTabS64CwRHHl8XEd7LpQ8OK/3bwXcw+OaLvVHoHIB2SFhA0sUub39Uj8JWcPuAFSshJ27fMtbXbWWra1ydUT70Zg66NYk2qQah8NZ+AlRgH8/2xyHF8kB7BsU1nvwwuQFUyDTDcSRJT4dsydCN7zOYirEMcUvmgLZjAlcVXpv5FZZe+p4Ehs/+bcd9zIFRkCIvyjJYL7vEH675jqFhBNnlwz54UUnZjTSlXIbSrGztEhZqnSFUtiJEcg/3wiyaHbvLDeVgyWonTmO7AVhjoYTEKedcGKLBiCC6fPWSF+kLhGk2AQjud3HF2+tVR3RsJhfW7lGC64v2txP4MY8trb+EhQ/oOin3kbnwDRbew==
*/