
#ifndef BOOST_MPL_VALUE_TYPE_HPP_INCLUDED
#define BOOST_MPL_VALUE_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/value_type_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct value_type
    : apply_wrap2<
          value_type_impl< typename sequence_tag<AssociativeSequence>::type >
        , AssociativeSequence, T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,value_type,(AssociativeSequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, value_type)
    
}}

#endif // BOOST_MPL_VALUE_TYPE_HPP_INCLUDED

/* value_type.hpp
Wb/MTDh4o5ixIk4SPBCV0arzgKyp19UqXqtLO+5lHdVweXQnBxeTiz0snkaDoRN4GH2j+0arx9n+3ewQmHuj1HGr7tNobThzfSiYVW6DOJOHU6PJNpXlZGpa+o/ZXwRWVmA+WRHt437AjAQNUQ7HY3tHM3qkc9nrcE+CsTsFJQnNx1pKgatWRN9P7+2HCP7q5pDBjAdKobctSTyOEmuy5GBirmOvqlYkjz83vpBomTRSGQLPRVLKFpyLAecmhO85IKlea7Sr9J4ckxuyxz3gWlBxoyfLXmdGCOiqC1c4uqHV/zutS2YuVMKI+D471xM5k6MVIaufQQAtuaid8aIObmgZK4QpUcnNHMzta7n+mHg1CxN8eerqs69lj55KCY6Gl/mD9JVtEyy/DbJa+PVt0QMzMsJO2RPRsu4MRsGG9O0pu+t09QexFmrK2RFWnBWaVor78QvetdVtkqavRcHz6mBSb7AK13L3YHa9fP+c+8eKKVbcliyMhg/ddwfM7JV5S3pwAwm6qoCW4IgthRIWmLn9p9p4xOfon85DY8v08KwlwuRmH2i6AhMewg==
*/