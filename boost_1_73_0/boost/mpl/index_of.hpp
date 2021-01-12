
#ifndef BOOST_MPL_INDEX_OF_HPP_INCLUDED
#define BOOST_MPL_INDEX_OF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright Eric Friedman 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/index_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct index_of
    : index_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,index_of,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, index_of)

}}

#endif // BOOST_MPL_INDEX_OF_HPP_INCLUDED

/* index_of.hpp
x327dRkzJT6/XXxiGePcPpZ891lZzsWeHHujOayVLiPVd2DVb0fNemvcrYxX0N4/SNw9EleOL5fX5nzH33iZb5FD/6LVGP/O1p9klInuVpVUyYejDt9vDi1nXQbzuGzbW75dJT3q97FKXs2W9BsTTdYfdLlOzVf6BOXZyyuMvzVDvU+Ybjtnxss1R+JmE7cikSY+q15zptquL5prFPEtz3RuM63mbDV+iu33zBwbk6SJv5P4
*/