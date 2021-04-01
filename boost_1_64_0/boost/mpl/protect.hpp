
#ifndef BOOST_MPL_PROTECT_HPP_INCLUDED
#define BOOST_MPL_PROTECT_HPP_INCLUDED

// Copyright Peter Dimov 2001
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/arity.hpp>
#include <boost/mpl/aux_/config/dtp.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    , int not_le_ = 0
    >
struct protect : T
{
#if BOOST_WORKAROUND(__EDG_VERSION__, == 238)
    typedef mpl::protect type;
#else
    typedef protect type;
#endif
};

#if defined(BOOST_MPL_CFG_BROKEN_DEFAULT_PARAMETERS_IN_NESTED_TEMPLATES)
namespace aux { 
template< BOOST_MPL_AUX_NTTP_DECL(int, N), typename T >
struct arity< protect<T>, N > 
    : arity<T,N>
{ 
};
} // namespace aux
#endif

BOOST_MPL_AUX_NA_SPEC_MAIN(1, protect)
#if !defined(BOOST_MPL_CFG_NO_FULL_LAMBDA_SUPPORT)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(1, 1, protect)
#endif

}}

#endif // BOOST_MPL_PROTECT_HPP_INCLUDED

/* protect.hpp
9zsipqToiYWWBZU0FD7GHx0KXlY4PnzkHOtKXj7ojn/VXUHcak8yHuPf0dtjaQ51iALIXDexv9YgINqiiKkL4TnrYfhbalhvV77r/U+GnnE6ERcx7H1kJYBWYTB+DvhUPWHfLwfT1fx5tntpYinWM2BYs2yb0TTJ9BaW9KKNAmjG757ZFYaA9WmyApHoOnJJumHK9r30tfQvMoRxZpYndsnK6R/k1M/f/zILNPvNZ6mUq+kmVg5x4jrLkyxErRz4efGaocRcHKQcE90GGNmtz4BzS35x2hzR6r0vkDofBaplAyQvBNOi+wfMo2A+NUpT8SemQ4WO9Y5eI1BtgIxWcH+p7xzSYu9YORhY7cP/dTYMfevO7Zy4rcQNefEyU0Y5ZP/FXB41HaMfp/m4/321e0PMLjW/PJ4CGdp0y6qCssge3USLRU6ZfQ90Xeyv89MK+xUQ8x8I3b+XR0XT+wEQsGIkqtuJrzVnmL2vNPja3qzc8ceCAP2vNoZaY9zH+g6i46ljTbTiatQyVCGeB+t2nt/8PF1oViMSgwuSVktDAQFPAY/K5ayM3OJPcw==
*/