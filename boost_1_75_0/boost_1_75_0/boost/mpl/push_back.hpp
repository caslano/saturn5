
#ifndef BOOST_MPL_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/aux_/push_back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct push_back
    : push_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,push_back,(Sequence,T))
};


template< 
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct has_push_back
    : has_push_back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,has_push_back,(Sequence))
};


BOOST_MPL_AUX_NA_SPEC(2, push_back)
BOOST_MPL_AUX_NA_SPEC(1, has_push_back)

}}

#endif // BOOST_MPL_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
hcnjAOD8RusUJfU+Arlx50IpC87i2DumVM0tXPGG6oDBpMTaYXVAC/fvXGEhN1+U261Hl2pNLPX7QwEAQBy5iEteQ5u3VH/v0RFQgZ2Tf83sV9l7SfIvrFmX8iSXub2MtQ1NVd32AKLOKcsDBUwix5LFouoSzkUZSzvmYufxGIpoLOlGeCEkf9T+pcPopDqnzwvkAihYc3YQII40u3S/uaKTqD3q6hJjRkHkvGVsfmXxzb3P0ATmd7v+KZdxVNfK9UYpTr7oWhWNBi5Hw+IacYRlLvYqH4HHd+Id6wiQXief3wWkCXs1d1OtbG2R22FdoIYImHaY+nQgVtm/v2Qi6fcqrbVLXBXLxPCnSSZhm6N9CHTgQAqwBJK/tz1pdAiVlhJiRWtsgunqK8emLlYiOfzkWmFbnCpYZku6HRhsMks/5euvb9C1MdJfTnQ6qb9HLURCXm2hx7ZCt/vDa0jGyMr8/WSzUl22suNlwcXK5o3rV7YoLRCVgYkV6ZjGKQ4GSx47mmFE6NsYutaQry2/cyuPRwmTGJPm/e+KrMtAnIvgL/LZbCjlORbg8afUCUyC4DmMRTa/PE0DrZbKaukGufbC4LhTBXF3HeK5hd5ktpGrTEiktYOm5b1SxptwZs6mkHXWIvNlreJhxOspXATF3W8t/vDvqQ1sezSJnJny17t+cRWtkyDgFK7prLmPES5dKr/PNPMjGTT/ybey
*/