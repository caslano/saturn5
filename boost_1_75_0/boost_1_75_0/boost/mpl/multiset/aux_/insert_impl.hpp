
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
hXO+AY+cS7CCmY/HtLW7Vk1uvfLNeugiXH+TNORpE9H33D5gja8IudTuUyt58MdKEuHz5AqeXWapa/cLwAMCFOslsPxRcecRySR2JnqqDNeD9DQH77NyLmiUOsVfxaKMnlSGPrn2UEmAazfVqrt1ODHaaybmskCY0OpezrT4hOMpw4maK7GvjiMLF1yo2t99V75WehZRElachl1xF3r2blpFmUtN6e2ftLVCK61XFXl+3NV4v1JPjZrqIEKs4FQuOa0COdNybxbz8iWnxkxPDdqk499C3nZGtyf2F+60XeAd9cyMIC03NO1BlYX+xlr8xnS/r6maBvzcWSrmitZJu98bo9YGG9l5jw3QNNE/I2iDeJwETutPNXnoPF2J3/e0JqrWvbFB1e7jqWa2obU2ZtTEKzcO/221MMxTR/orMbERHH/CbBOTaVDMtmgku+YiovOS+iubKfNG7jaSrqVb3zAzQ4i/ZVjL5NT4CbKnO/r4pzLEgg6hufZHOUYq0VCV2VXCqtxD/BMkUkQ7wzwXyAEaEEoakpGrTO93TlYdYWBjlNvEn0lhifVwZo/FE5kZiqqjOBZvTl7ri6r9Y6Ire20cOtYY2iscOvjIFrIE54YMxlvhLJMZA+1lgz6iak7pLUS6YNaKj4WnnviwLqcmrwV5Pu1wh6sBat7YHIpHrI3c78B1Hv/suPvamd2JRKYD2ilYlAE7s4PtGxa0
*/