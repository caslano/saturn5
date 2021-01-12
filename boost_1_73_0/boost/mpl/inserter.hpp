
#ifndef BOOST_MPL_INSERTER_HPP_INCLUDED
#define BOOST_MPL_INSERTER_HPP_INCLUDED

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

namespace boost { namespace mpl {

template<
      typename Sequence
    , typename Operation
    >
struct inserter
{
    typedef Sequence    state;
    typedef Operation   operation;
};

}}

#endif // BOOST_MPL_INSERTER_HPP_INCLUDED

/* inserter.hpp
revhwhb1+M1zkTe2+EHE70a8om+q8XP/IH6kr/VcWu0Q/7w2vpwfNd7wdPk9S0RFa0bGe3KNQh0q14TwtzxdtHfAlasA9Wuu94frPL1p+72Pix7neL9zw2G67D+Xv/WVZP/V8rDuv/goE5cF534dZlaxJq44L+E/Kl5lGRnbNNuoXJAtnWc7l+uCCt27Hmf7Yed70PWa8WWa8VTN+LOa8RTNuEEz7q8Z95FxF+1LuKorknMB
*/