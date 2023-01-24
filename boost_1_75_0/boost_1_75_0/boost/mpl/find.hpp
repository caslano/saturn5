
#ifndef BOOST_MPL_FIND_HPP_INCLUDED
#define BOOST_MPL_FIND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/find_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct find
    : find_if< Sequence,same_as<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,find,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, find)

}}

#endif // BOOST_MPL_FIND_HPP_INCLUDED

/* find.hpp
16r0+JhZrOtVv9fpe3qxHHxQKlZSP8fum9An4bwDf3/lt6zDcOy51ye5tNNL6G85oCPo8xV4hdYDx3gWQK0XbcAKoHuR8mcNZHshUKX396p8ceR8/GQ+MKk7AlD3WwvIMuwWuAVXc1MhDva+nFNtVbx/8no93roF7pskA/j373WQxJQ1zj092+B1ataVWx9OlO7rwwDpiFQ16+aew5u1/W/q1i2u729WajVEMz1B1g0t/nPwNv8ueKZ/Elz6+V3l7SpVIqAcEZzyvLbvL/ppz/3ouSUDwdvXeX/beeXZ6PsEi4FRqB9ObtF79j1TV3IfrK1e5Nt3B8mcGMI14hHnHYt97XX3o683xHt/tuodBc0ZI9QhJFJU5nr+2hOO/n3r1tZNVr+OXJukvCZ+6ptHzr+lkiD1TfJDk6v5qnHNwfNw81g7Vvr4ePbUIZKhYqlOTEGbpBBfOn+d4eSNEnbrP7Keq2LUFFETMxhk+mOfSnfq5/FfoVZzfzXESMCIsxBFvBYCTOZqiGF0HFDDQnDJGYoC5ZOHxzp5k7C5/7iI+tq0nN0T7IujGFXl+ZKc3cUD+ilNO63Y3zjaVy+UnhGo+bS3PbXQp9CSq8BXF777rx50i88+x12C1w/85Jgv76HxGB+GFF6zZ01GAjuqnE1aXpL6+zv+1iN3C20vK+6m/ZPo0cKDMOAMNJbqYdeuyoeYvzz2b62+f9ln7pPY
*/