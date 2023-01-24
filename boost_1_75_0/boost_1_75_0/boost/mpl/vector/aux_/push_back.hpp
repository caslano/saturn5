
#ifndef BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

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
#include <boost/mpl/aux_/config/typeof.hpp>

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

#   include <boost/mpl/vector/aux_/item.hpp>
#   include <boost/mpl/vector/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_back_impl< aux::vector_tag >
{
    template< typename Vector, typename T > struct apply
    {
        typedef v_item<T,Vector,0> type;
    };
};

}}

#endif 

#endif // BOOST_MPL_VECTOR_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
K+E+W4xdYfVL2T4wYEtabLW4sOSTPHa3qyLPVvMaTW59UN27YR8Wkd4Vox473MH7AeEMMSoCcOm+KMJoEUtEazjTD88SvVBZlljDZn/UmsiAR3ZftIdfOuiPZifS/dIOz3ZPnsmHClW0uutuyOO3fqkHNi5GTRwGrQ2PtX0jffAx/LbTbztUHIVSPnsruuKxA+Eh2AziJ7WpoLX1z8yvIpbsDQewX8iubmg6TTQ0jcvn6aLachBaRnBwrwt0L2inn9CwGIURm2KHDorR7M665kO8dYC+jrrWm3UtFYFRH5Qba2WDU4LBYPAL+4cUCKMZxymqHZkzr4nxDdu+m0Vr9fLin3HrPHANl4MhdABggHpsor3oKI3vh7Qutg/hCw3EtsBmw44Oo4Agt5VefJUA+gccLRsQtolSlihtAwS6XTcMCMFcNyuA3bthQDjPg2XNfqkxkeuXkCa32WpZqORUq4cQ4GMI9hcHqeNua6Knv7g3djoNOz0WMDowUNwnPFyt6u3EQJ9kDUgt1IKN5hUwu2ohsL4NRLOBlAPFU+zhM9gXAFqin08C7EnxhIXEiM9OkB4BpNtL75icl7gWxxfghkH0lZjC8M3exBAkER1GP7JODxxruuBoZfuLpxA5eGC0fNJEq7+4F3wbNSUy2BhPtJbeIebhEHvumJhXJ+Z56ybmuTebSi/eY6vdQpPRdH+J22qr2UB7ST7yuCrz
*/