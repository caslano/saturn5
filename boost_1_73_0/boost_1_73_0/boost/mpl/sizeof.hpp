
#ifndef BOOST_MPL_SIZEOF_HPP_INCLUDED
#define BOOST_MPL_SIZEOF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct sizeof_
    : mpl::size_t< sizeof(T) >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,sizeof_,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, sizeof_)

}}

#endif // BOOST_MPL_SIZEOF_HPP_INCLUDED

/* sizeof.hpp
hxHuIEQHdhP+kfAdwr8KzixWo3PvEn5B+B7hD4TvE54gPEB4GbXzAWE44YeEkYQfE6J/pD7VNxN+QlhCeAjXJ/wn4VLCzwnxYP0vCR8mPEL4FOFXhJjrr5VNS3dpm4ZSmIDOLmLaYlUKE+fMeZBgeV6MS9NiDc1taKl+msUeCos91NYPBZhpqDSuqXUdls1rrKA0QGah8dvFKjZzdVZTkED/tx4UNjP3qoAxSY2emYCXXYitpaqFeL+xgglPHrg=
*/