
#ifndef BOOST_MPL_FRONT_HPP_INCLUDED
#define BOOST_MPL_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/aux_/front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct front
    : front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, front)

}}

#endif // BOOST_MPL_FRONT_HPP_INCLUDED

/* front.hpp
cFMvpwClxx1401mqBLS0i8vDEuPAMQ/MoXXVOVDuORmpZOOAKSIm+3syphy5CO37SyfQ6Tsiwy5X8Ovn8LjVvq7l6FiIQbyGtJM0zho/z2RgwHGpjYpMq1P7qQhkXzhjbBeJ7D/EDHgsabFcsUJQi+kbaTMhAHlkGlX5ppqRpYrM+6q98xXVcvhGVhQeKxRvEnG4uwO/+NWwSHM3BdsMI8U2ABuP93Y28E5sdRzPnF8SG8MI/4M4TpSxbVld/tqKt6CoWaW2vaND0ZU43HNeC6xEr6qKzHJFww0enDmeHSbaaloAnPB1nIHHMBil4vSjuQYs0DCk4IiqtSY+/R2grx3RnPappVbVRG88iOe3MF8gOozIHOkw8QZXMRouyQhlCQ7q6pi/pOQ7eV9w8u0amLqK6Jys135wDIkyfEQmCwIIaHR3aYGD3lqTqDT0IE9w07rNK52mK046bf6GdnjNGuTFfjcJcPVhVXYOuIaTBrMpBQgxZziPHu8au90KwyXoGzhN94uzw/3Gr4dMRKuzLAuubmNggwhVp/Tu3aPUPmqqVE6LrNkCJNs/sg==
*/