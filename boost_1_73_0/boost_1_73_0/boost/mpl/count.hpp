
#ifndef BOOST_MPL_COUNT_HPP_INCLUDED
#define BOOST_MPL_COUNT_HPP_INCLUDED

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

#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/count_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct count
    : count_impl< typename sequence_tag<Sequence>::type >
        ::template apply<Sequence,T>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,count,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, count)

}}

#endif // BOOST_MPL_COUNT_HPP_INCLUDED

/* count.hpp
Ln0L+rzNXm/T9TYHzGZ1hEpz5b89Enl/Lw+5m/aoTntpt8nFVZsu0Fvzraxy05l6q97KbtpkruU0ey3z7LUsScxKuxZ/PrDZxTqrrtRmbn0mlpNOsizkc7xRirv23M+V3/EGwsSI1LTpl7ch/XZtCbEurTsvcZwJO3JDyF7inMQU3KCHlHmJ/A9qrD6SlU51pNH3ElLLu5E6OG/RTs/iPSreTLIu0pc1UlucDyTHvbIiORRNXlJIYXeYC8CbOS8=
*/