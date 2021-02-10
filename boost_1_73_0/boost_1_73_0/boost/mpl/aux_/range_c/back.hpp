
#ifndef BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED

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

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct back_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename prior< typename Range::finish >::type type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_BACK_HPP_INCLUDED

/* back.hpp
Om4pGmLscXnwR3x9fHzuuc4cWieFxVOWqbbU1M1wudCmsKdsPJ1O+gYm1zfTMLq6vLoI04xvIjMeNrMBG8ANmjs0sVUFssxgVy8poBBOBEQ+fDOE/SSB648ROxcOU5jOcQ+SE/ik72hlmMDwID04SSnmw9U0YgEwBc81tv2El2KGYBdW1tpixM5026J0SrcpbH45bF08XXbo9947XrmmjljEKqxrTaQDqZ6brFDO/kuCK2YZX0lJCp/Vym8MCst+QgHh4FNWOddR+Ho6AKd1DcrCohKOJjC3CKq1DkUBuoQdOTf1Dst82CmrVX50dEz7w5RB1ooGgzIgq3k7wwIa1WCnrSMo1f4E39QY50uHYDyqFHWdCzmDhXIVYCt1gYageMCCTOqmEW0RyKacb4/JUpeTdNsfM7n+POWBxEMcDVf37D12i0aVS/D6gCgdGnAV9vpDJSzkiC1s2Uq7LZbd9bFeIGdU1wlDIJb/iJ/9von4VxKffN/lz8f4jxNMrudtIcxy9DLYi6EBkzK34Tkgy5Gors8c3TAsec1Fru+82g11Fob74NW3UBrdANKVl6AlJdaQ+OizTLsJbc2hB/IobeGzRyGHq6AGhPH26I/LdbEEGXxq92BBBNDDvDrcHe6/htEIjpLVwTVay7LO
*/