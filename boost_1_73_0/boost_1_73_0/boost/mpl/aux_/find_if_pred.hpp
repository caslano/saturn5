
#ifndef BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED
#define BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Eric Friedman 2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include <boost/mpl/aux_/iter_apply.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename Predicate >
struct find_if_pred
{
    template< typename Iterator >
    struct apply
    {
        typedef not_< aux::iter_apply1<Predicate,Iterator> > type;
    };
};

}}}

#endif // BOOST_MPL_AUX_FIND_IF_PRED_HPP_INCLUDED

/* find_if_pred.hpp
VB82ZNoR7fZJpzs8ltmJSHk36560O62Tbr0rWie8kw6H7dZRuyM28BP2gniyLDILE/4kVs2KejXCBalpmS84kYQhFKXMsIm0QEsXJVkIu3txcz+4vI13qXhvb+4GjBRLGB5fRF/F8jIz0pmUZwvpE7bMC/2udhMcBc5r2A8KiUR27+9Ozy7vWK6GVCpMG5wgyjpbK3JfnL5Q6cdyYjyvYsTeAMUKXnS07/VPJNAc/KTkmZMlYOqqskUZsYyxljE1xoVBVQU0VzGVzgiD18TBDBWD5VzdCS4wWAwv1NkJfsZxEL0fYXAcjagS2/10fnd/efPTTvBeCFmg+YAd7AQ7xHgVwpdn46/r8x8MO49EnTvAO27PbqAByIWEMSKAsuAMCqBTammF2y3WhlSNlIPClA70dDJErZRGMBJMVGA4AF2pCq98P7DsimP1X2PfZkqmce2AMTS+eDS6nzvHX16Y57KwjGboBqLXormhxWoyrYXYAlgqG/nHwsYwnGNudwLU+P/wEFYpXwp3tCGcdSm2yEK5yu1o4dbadpNl6d1gYlK0Eu1w/ZLFUCApeq32/vaF2V+9FQxfvlqt9i9RMFnrg5nEzvYnn/fGftUHe98cV/vbNP4r2ja3R/zGyfJ1vO3A33SFz/g4RPg6fCH8
*/