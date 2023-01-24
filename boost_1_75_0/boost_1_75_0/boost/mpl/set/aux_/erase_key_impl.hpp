
#ifndef BOOST_MPL_SET_AUX_ERASE_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2007
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

#include <boost/mpl/erase_key_fwd.hpp>
#include <boost/mpl/set/aux_/has_key_impl.hpp>
#include <boost/mpl/set/aux_/item.hpp>
#include <boost/mpl/set/aux_/tag.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/base.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct erase_key_impl< aux::set_tag >
{
    template< 
          typename Set
        , typename T
        > 
    struct apply
        : eval_if< 
              has_key_impl<aux::set_tag>::apply<Set,T>
            , eval_if< 
                  is_same< T,typename Set::item_type_ > 
                , base<Set>
                , identity< s_mask<T,typename Set::item_> >
                >
            , identity<Set>
            >
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_ERASE_KEY_IMPL_HPP_INCLUDED

/* erase_key_impl.hpp
3T+dnFilVot46WYRGax+m39cWXWJKD0Rzyw8akG/CmAuGsbSBEUZlGeKl5fxf/HfffWnzjRbW7XDwlLPJokQxXFFPmCF8SQbZdlsni7GkHxWI8WGOtaGtMb03B2+Zf0y0epkrYjOh6YTSIq3KK3tZffjKFxGP0f1K+cnM7XNLMtR4eSP7V7MB5RgH4wLE7+wNmPtzcahQWNjuwsdXYlndavX2OT6DmzPsZ51Dowol51qIrZj3qC9AlWXbDhQsd+aZBDn2d2dff8+A2hRKrXUMx4Ouv46N+Lhx9rKpob1LG+xhNAfqlEWvi5ZaLR8lrfA1zVIIt2NCE/bSu44VL39lFtLYic6/JaaNIvnr2mismhTMGgdbWh1jsbIJYJ5GESIhBCtA5co6sP3Xjo3p5x8X2mutf91/Ut7fjzMev8pFPqMa31i06/KDKyWXlex7m7hBD00lu5pLYE0bAeWbRL+UK7vXhiv0B+15UsIbcZUD/vFGgLGeVGPUyWBw4uBlLezRAtDKzwbcQKCXRpW5K54idR1SRZAyCLbz7ptu0/JAhcCQDAYElQeuyTmtUZd2KUumQTPqYVPHT7jW4NlWLWXu3cI0D1ZsVHrWyrPFKGfl1Z4WYa7dhb+9okuFnTUmhh+ZHWO/IrU9n2B/CZg+bsH/N2snA7igKrdi4X+PMh6yG0ZbhYDzv0qXSN1q/9lkSdEKcsn+8qZ6guTTlLV
*/