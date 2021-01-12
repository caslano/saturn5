
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
wl2CCwfd1oRgQhwhmXCJkGtE9mxuBG+ChTCXkExIJ5QdSTohhpBAOEZ4QCjLAbs5IZAwg5BEOE14TCj7PsshBBJmELYQThOeEcpygPcihBLmEnYT0gj5RpMHgjfBTJhLSCZcIhTiwFiL4E0wE5YSDhLuEsqOZX4EM2EuYTfB3qcsbR3bg+CUwHmZ4E0IJMTxt1rfUWRPtT5ntwjNi2b1N8vqb/afG/7Dv/+bwof9u/r/236r
*/