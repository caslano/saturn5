
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
w2EwpEImFEEN1EIDtLjQB4fgmAuNYCpDI5ghvgydYCtDaxlawVOG3jK0lqG1DK1laC1Daxl2LENvOXYsRytkg7scjeWMdTk6oRlay9FbjtZyNM7FhmCBTLCDC6qgAVrmog165qIPTG70gdmNPkh3o82NNvC40ebGlm70QZMbjW70udHnxkchYh76IA6SwArZkAfF4IZF89AM9dAIHfPQCqchfD42nY9msEDqfHTPRzcUzUc3
*/