
#ifndef BOOST_MPL_EMPTY_HPP_INCLUDED
#define BOOST_MPL_EMPTY_HPP_INCLUDED

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
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/empty_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct empty
    : empty_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,empty,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, empty)

}}

#endif // BOOST_MPL_EMPTY_HPP_INCLUDED

/* empty.hpp
/YP5Fsp8i2S+JWht20LuaTDSRdsWkwozH07GR3EKBuBUbIJPYTf8B/bH6Whr490oy33VRRvvzYlaCltiBWyF7bE1hmEIJmI7TMbHcTZ2wnnYA61t9sm9BNZy0WbfK7KeZeiPy7EbrsCRuBJjcBUmYBo+javxeVyDK3EtpuF6PIAb8Di+hhfwdfwJN+F13IwlSE86lsMtWAHfQGmDQu4pOIZdtEHxFvFK4tvoh+9gTdyGjfBd
*/