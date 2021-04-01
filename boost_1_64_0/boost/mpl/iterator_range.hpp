
#ifndef BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

struct iterator_range_tag;

template<
      typename BOOST_MPL_AUX_NA_PARAM(First)
    , typename BOOST_MPL_AUX_NA_PARAM(Last)
    >
struct iterator_range
{
    typedef iterator_range_tag tag;
    typedef iterator_range type;
    typedef First begin;
    typedef Last end;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,iterator_range,(First,Last))
};

BOOST_MPL_AUX_NA_SPEC(2, iterator_range)

}}

#endif // BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED

/* iterator_range.hpp
xYns/NrgcCGIGySYRk93iXlreNzCy0LJWI0Prtij/O7lR00oMO13pTMcwhRAuCJmftbrQR+7HoF+GA/6rho1xtuEhfz51Oit55q6jdyyTNG+LHowPf2gbq7MUSQK9NmZM6O5SVRSjMkAKTm+QN/5irm9FMvqonmjlKEIe2r0h6ybgPe7I1lvj++k0oc47DP7kNyY5pdbEn2NpUW1iLPydR1TDQvuxFnoF8RnDF3nUh6h0u4MUVq9+ZpXsVQ3S1XYXvs/IFT2MbFPRMlhraA0OwhqL0S+faL3b2y5PngfO5VNUYgEggB7ePVmg5JP2WHUur5Q1u+iyCn4zaWcrmyRF5JE1Cj8Vi/aruHXlh5npKqnZU6fGeYLdoYHGxL9CLc7eZOS/cuKUC6LN140USQizr2CNxYcEyp3EsYBxq6y1gzcSb7A/mS11RFPATmlAcRC8LdICTKDEcW/uNXntNxGvryLRgmVMdxaK7ch1kXwmVXkYGin0kVl2GDFrUn0HjrJwD4wu7Q9uYoPG83R7IRdZqqhC1aYZJgYLezmQwFTEYcdZbO13ioXOYHprg==
*/