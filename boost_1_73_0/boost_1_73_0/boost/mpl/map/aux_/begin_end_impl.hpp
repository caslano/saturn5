
#ifndef BOOST_MPL_MAP_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_BEGIN_END_IMPL_HPP_INCLUDED

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

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/map/aux_/iterator.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef typename next< typename Map::order >::type max_order_;
        typedef m_iter<
              Map
            , next_order<Map,1,max_order_::value>::value
            , max_order_::value
            > type;
    };
};

template<>
struct end_impl< aux::map_tag >
{
    template< typename Map > struct apply
    {
        typedef typename next< typename Map::order >::type max_order_;
        typedef m_iter< Map,max_order_::value,max_order_::value > type;
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_BEGIN_END_IMPL_HPP_INCLUDED

/* begin_end_impl.hpp
JOsYdpRsODy2rMi5WMuOMfD9SfmD+q5fbVLBn4oXWzT2hyNEMhUatnXWtK3KmPEDmjOxZ8KU0ZoZtmBpXJSv/TCSCP5klqZcsjVSHK0YEkxlIgExD1mCVMiQLPVRwJREBG0iIRWoY/DIRfRMVMSTVhVFHCUMpUSCNTNK0EbwXWmBxhFLlGGviSKNer1RJWY1Lhvouv4OjXmOgmi3Y3CYKPBHebKGQD5lAA3iG0QFSWtGlUcLjSIquOQbZXre3Lq5rNeMLk8UeDD9ImUtpNiTskK1i39GNCRCMtWOJDdvb29+Mhvnw0OWBCpsoeZ1zZhoKE2dE3yJKFHskJIfz0b+Yuw/YNzFegXw7OlNtx8ELqY3Dbxc9IJiTPFp9a/xKsCF3k7rI9Cb4mnugJaL3cC5w26O51PHx66Lp1q+m+K5/ugEeJk7j7h7jckUnv0H/Ct2YjxY4mHgZHgAUeRY6vcr7KR4MMLLqRNpeY0drvV+V79c7XbNqBlHBiRcldckGInh+gKGWASyeAUsOl/ZH6VMJesr/XOsuXrBmqt6XQeTBMBIwYCTYAFUD25jAvSRuaQxBPk38uZKg3gXJSSOi7cQcgXOF0i+gBDir3KhIaPb/0vgX1EC/11GHVgE0rmld8uKOXT6qnxgEmwYgfpk
*/