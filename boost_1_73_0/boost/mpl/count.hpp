
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
Uod7FP3wEJr4Y2sHh77/jBNa6fi80ai/93eHtm++XqvAcqKs35SvY3wgy32d8FUH5zaBlfrQiTJ+jfESvuSdjN9ivI6fspxWDm0g+zi12V+M4Cn1pMnETe2optuSVx73bn9S219hZYe2IGkKn4aibVvPvzm2bZgYHWWw/pPO1l4hyZe2Sc36JOn70N9D7euwEuNVZV2M6+Rbf3u/cr3IN3lnTPYB+8bFO2NKv25+2A3rYXcM
*/