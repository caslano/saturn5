
#ifndef BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost {  namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct iterator_category
{
    typedef typename Iterator::category type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,iterator_category,(Iterator))
};

BOOST_MPL_AUX_NA_SPEC(1, iterator_category)

}}

#endif // BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

/* iterator_category.hpp
V/t2JU5b4b5+e6F9axr3fLZsjNqfKzsavLVHo4YL3MChNtm9MWY/Ckss6YHaivojsYGtZn443LFnljlgoD0Q3TwEm2KIVPaloPxV4+yu3mWcH2BN4lo94fgW1AFj7f624ONUuNM2+jUqvMv0SD9oAIIAuGtw6p8wX30oUV9BS3GwuH4iVf70byRa0/i9ro/jvdwHCUwzzexAD3Xso/WLn0aH2/dbSvjQsKFB6A6kGdAZFEz66FjxliMzKyXjhlcA00ze38f36umD6aKVTrMH8ZIo0TxIIDhXwoWDigm+IoxWsrg7t3twTf06AVE+ihZzjmp5dag/+/Mc5SjtJk7jLgj14aLqPM/sh4Ke0ElcapZbFjs6NJCLzXbrcgNDWajSLap0F5rmW6KkJtUzaLxHnfVl5Diu79nTt5b+/w39fwi1aOvP+NHnoUHSi0/DgFcMhqaNV0QlX28BS4ivwUWZxFeidDzFO8wUvmnQMxqVHbCb7Z4BbhgUecsOgAWyJeO5oZeScnvXqizhPLXl7b8fXtoWKG0LvR46gpAyL+/NUVMpdCBw06tMASstAwz0sDcwj/n92IvtE1rZj5VebJ71O/bvXtBG+aREnsNcvPkD4tuhRPV4+v9pmT8fD4l/glubxuGlZBGwhC3hr6WL74EJZAaMhqezJVpNxXc6EI+6v/MTHe9YkHDKFD+psQQPuZMhUorMlzFj3cbtarcBy9ZXByT2U7H2v1QfyXi7f8bhxlAaccb9xDpzuUN4ZTAAgXXaF8N+/lNxbPzzy9rBic+fRnrbP19yjms//4fCdvPpOClePm81buGdujhHxPjs94bHAeg495+OjDo/F3edHqOBS+Xi+1ernaErNMXveIC/F5rFopBRR0NZr7+7RJqvN6XJTVVQpg2lNFl0tkhSpSrw072pCypJIiJvHH+wAjosBjOEXKa1HHt5SABKaFECuJWjVbeGBkJKyt3hftpNooXEiPCTINJmbPUkvGhmrf8j4vD3rPj8De/Pdao/cRn9t1tVd8aub/KIzvanjpFzS+vV3EcjU5XJf3+DU2gFvkmMXGNkCX5eJ34mEzDZuv83XK+fhRQl10vyQ8QJ308EURLP1/nk2zQUGvf1xMwO2/8Pt+3/B4vTVhwAOks99LWBDV0UnJ13c23Si2k/o443BOlklvCYGwaow4uvlNjMLN+cjmOHTGk6mDvc3x9lJMmA4qCgI5X2JFbMQJEPimQXrNrUSOmvXOhV38k3n6nCOepA/xAgRYab+D9KaVGAbqHjT6hTrtAIqpBW/JIB/qGaDJILXVWBZhyPNAdctD4yPPh7IJTOob8W3l1HiDaPQ5ur+v98hpiE/X8Yy3MDkqOnUZdDMnwsPOvcf+JEmYXeewuH6NMkqCOXQHtLUE6kLA36MCupfmPoG9Qmr/nACPsVSQAs1B0Q8GjnL8vtC16oBgTP1271vNLe/quAEQrzUX2Vr9kYAT0N0BsUNARGv4rejITuoiLZ/cA0iLaXxK+f07+Xz/fuJ+b5vWHne5/v3c55YGFu1Hng8/Hhlf//sBj+DsIhVvZVyWFsLlMtPzwFDBGH+uzun29q1r6n8hr54lppH/9AI+v1HB/7yJqDIJ68Mg/c7K+uonGkRJoSAb4GhQQfEvQ9FmyWHzl8TzbLlv/rUHt76boOtUS2GgK1BQ7FrXLwlRxJEHowHOmS7RMR3vtW0L5FDoFalWUG+RxZMoDEiG8bMYBvLZy1K4oBe8MO4eXIDIhr4Qy4bA1+7rA9aDDGQw4tvgbI+9ApfbTRo/RRTVpAGViGp8VfhhW++ZSNCQNNqVtWAv8ruQo4BjkJJu76GfxVnPVs9e6E6ydJRV5NXBU=
*/