
#ifndef BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/multiset/aux_/item.hpp>
#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/insert_fwd.hpp>

namespace boost { namespace mpl {

template<>
struct insert_impl< aux::multiset_tag >
{
    template< typename Set, typename Key, typename unused_ > struct apply
    {
        typedef ms_item<Key,Set> type;
    };
};

}}

#endif // BOOST_MPL_MULTISET_AUX_INSERT_IMPL_HPP_INCLUDED

/* insert_impl.hpp
jnk0gS48pc/rX789+AWm6ff0lTcruTRl9KyEXh71P1BLAwQKAAAACAAtZ0pSbCQvmd8BAAA9AwAAHQAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDg0VVQFAAG2SCRglVPBbptAEL2vxD+MEvkSla4duVKDiCU3TeIoarBi6kq9bdeDWQVYxA626dd3YO34kFMlBMzum8d7b4eY0JFWDmciNlVm+fGG3d42GzcTizRdDjd4vE/9yzfljAbVUu7rurGHTsTy3BRLz3MpLmGFzQ6b0JkNirjBuuh4f6NIeW45+TyG6/EYkmfxXRFGkLb4CcY38GJ3vDEZw2QaTW8ihjz+SIWni6DXHLqhkJl6Q3B7pwvrUNzZirCiMO1q7HEHkjmVhXhoq6oLc1SbCDp0fAmhPdaxYi8plkeJg/a7wvRMXrseCob4r85ETlRzw6mEuFIleldgeckHA3tDOThDOETGFEYrMrbiBuk7INa2LFW18ZyRlKNFskqfltGoJ1smr6nco9yriiTlimSttii/TiE8wAckhGHLksCoMio7h0XGGt/54wwVtQ3yIZ2O7bzCuKPHwf0aG5N10AcDKiPmZPlD8JArB38QK7hwuaULEe8GLFMwK1lti5ngeYH/s3Och0kgFtZR9NFb
*/