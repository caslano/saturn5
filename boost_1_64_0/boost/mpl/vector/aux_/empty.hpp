
#ifndef BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct empty_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : is_same<
              typename Vector::lower_bound_
            , typename Vector::upper_bound_
            >
    {
    };
};

#else

template<>
struct empty_impl< aux::vector_tag<0> >
{
    template< typename Vector > struct apply
        : true_
    {
    };
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct empty_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
FjElW7kuficzgNEiyaNb6ZTXbiw1dHBZwAI1WO1K42bOXJtWDda+mAaC8NbwBmOQlISI8VlikqTDVZzzmKG8ovN1bJYwp68G/7kmN3W7l+cghOPMYc4M4bWXqYqmyKwow1JiwW4bYr8J7LADDwzo9KVXCnVC9L2gAv0s2N9CM1HXPzVQoZyBHUIMqGWgGfO9VruZkhs6oksS30Sx90NAi6rZZQ6BiZrQwM4mPYRl6bXqAC3CtUIiPpNQOauBIlzrKonXeXDlI+DJzUgaO2TOHfVYJvb/dszBgI4JcBWL4UVBNhxo8ZR+brUwYNf5xc+DOh7D7H40MpATJwbjSG/9x7vIIFZwotL3C5sF9OoVORHlcEg+62+MfLN5Nk4H1yQSz0TVLePO/lln1Zpp6rYmk954wb93hvWHBStkHNmxjJc51u4zikmIcnRXam7a8lbpNkbz8y6XW6xuN9K9aYkkH6GaKNkbUUuXI7gFX01cNK3/nh+xXbVpmbyqfw9gVE27p/rarf9tZft+tCzm1kggG1rsKwfHwOSAXImwFUk8DQUslK97jqnxjoFITA==
*/