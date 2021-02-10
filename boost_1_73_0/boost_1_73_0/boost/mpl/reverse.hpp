
#ifndef BOOST_MPL_REVERSE_HPP_INCLUDED
#define BOOST_MPL_REVERSE_HPP_INCLUDED

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

#include <boost/mpl/copy.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Inserter)
    >
struct reverse
    : reverse_copy<
          Sequence
        , Inserter
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, reverse)

}}

#endif // BOOST_MPL_REVERSE_HPP_INCLUDED

/* reverse.hpp
MTlVVAUAAbZIJGBtkcFqwzAMhu9+CtHSY/FxMExgjI4GShOabHfPURrTxA622pG3n5KmzQ47yZI+/79kK8JIRkdMhLKu9hwuOPz4UMVE7MsyF8Y7h4aAPDjvtq2NhE58vKWHz9NOKLngSt4V1lBguGHYRluhUAH7duBupUmP0CPOdcbfW4uOZtxMCQNxEkkEu3JZPlJVo6ZrQDZsiHruLAVQTne8iibCrif4d3brzhC9uSAxL+8XQBnfddpVidjss6JM89fNMTukRbk75tmpZJcnwMd5RB79C4OtBxh3Al0TBqAGYXxUaHSEb0QHq9h4Wgl1m1gWwBB8ML5i4xeW+5Mq+YTk8jO/UEsDBAoAAAAIAC1nSlL3sXsGZAEAAD8CAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTkwVVQFAAG2SCRgVVLLbsIwELxb4h9WVBxbA4eKIjcqglRFok1EQlFPyE02ilUnjmwD5e9rh2dP1u7szM5ozSwam3GDAWGiLpR7fvCwVzo3AXlNY8LotWb0OELuIEG9Q31vRI6EaWzkwcGmbWZVHpBZuJh8wXQ9g8e+490gjJ7GncpUCqztSSVri4tMQArbXKjel5DyP3TbAVbzClvPkKt9LRXPYS9sCcZq
*/