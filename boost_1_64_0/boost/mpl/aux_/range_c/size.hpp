
#ifndef BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
        : minus<
              typename Range::finish
            , typename Range::start
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED

/* size.hpp
N/AyptXTMEaBZ2dST9fLz+x8jMdxA0vzcVbkEzyLT4ZyGhgXxiNwTFjfcUwM69sa0vc8C3A7C/NFns6XQjp3sBFfZjO+ymTu5BC+xpF8PaRjuLA7bPfGsN087Be2+0C4d3QNC/BhFuRansp1rMn1bMZHeQE3MJGPM4VPcDif5PXcePBZoWHMQRiLsD/mWaGTQrqv5cmcyuK8juV4PSvzBp7D6WzIWWzPW9iFt7InZ/My3h7KfS6v4B2cwHmcxPmhPtzJGVzIO3k37+E9fICL+AgX81Uu4fu8l3/hUv7IZYwkcjmP4Qrm5UqewFU8kasZ5ksP4xjSxjXsj5kvvX52+wmbshKbsQNbshtbM4VtOJ5tOY0XcgW7cAsv4qnWfQmvYwL/yu5U1+N68k0m0brienM9k1kxh/2Ds3gZjxbPARzGFIZ74kNfflof//6Ye+L7HiUdTGEhDmIxDmZNDuG5HM7GHMHWHMmxHM1pvILzOYarOJZPcBxf4nju4ZXcx6uYU1wmMDcn8UxOYWNew26cytG8iVM4gzM4k7MohP039NlzaCb7b+dwvriYBdiVhZnABuzGZuzOVuzBBPZkXyZyAHszhX34dURhQ9hun7Dd3Owatrsp3FO+mcdyC4/jVp7KbSzHZ1mDz7E1X+AlfIm9+DLTzgOhD5/HZ3IeeCNcd+xiHr7JtPwRwnKNMsmfhiGejUI8GzM/m/AkNmVJNuMZbM4qbMFabMn6bM0GbPPzvfGhLz5cT8TcG/90OE5vYh5uDuWzhUX5DCtxG6vw2YPP3Qh977xU2B/z3I03w3HrHRbguyzM93g697A232cjfsBm/JAX8aOo8+60sJ2KmeT3snD9spzluIJhudAnLm8zWW5RWG4x63HJweVCHzfrZ7Lc3LDcHTyH86KWGxeWa5bJcneF5RawERdGLbc7x6HTd2tY7raQvtlhuZOOCn3IoW95f+S9f+dh5FUx5H9VxrM6T2ENlmVNVmIt1mRt1mMd9uU5HMBzOYR1OYr1OJH1eR0bcA4bcjkb8Qk25nNswpfZjG+xOT9iC37Jloyc61oxL1uzGNuwOtuyJduxA9uzM8/nRbyQvdiZyexy8Hop9EXz1kyulz4N+fNlqJ97WZhfh/r5F9bmvlA/vwn181u24XfszO+ZyB84gQc4jX/lzfwbw34Y+qDFOZP9cHdcuK7nmdzDhnyfTfkh2/NjXsBPGK7DQr+zPMrkOuzOMETnLp7Cu8P672ElLmJLLmb68XRaWF/fTI6nF4Xj1A0hvtN4EqezAm9iPc7gebyFrXgrEziHybwjOv7H2h6rZhL/z8N2vmBBfski3BvS8RUr8uuwvpVCt7C+RWF9BbggrG9Y2J9GsBBHsjhHsSxHsyqvYB2OYSOOZWuOYyeO56W8kr05gX05kZdzEodyMsdzCifzal7La7iA1zLU19Bv7JicSX19INTXNUy9DuUpXMtyXMdzuJ5N+Sgv4WPszg0cx8c5nU/wdj7F9dwU9tvNB4+7oX+Y8Zkcl14J57lXmZ87mf57p1tYrmomv3eOCstl48nMztOYk5WZK6xnszAvrGdVWE8hrgvrOT3UwzN4LMvyBJZjIZ7JYiwf6nlF1mAl1mFlNmAVtmBVdmF1JrAGk1iT/ViLg3kWJ/BsXsM6nMZzOIvn8g7W5QrWj3p+1Lg8UdcpMc/N2R6uj15kcb7E0tzBinyZ5/EVJnAnE/kaw/NWQt+tMhf2xzxv5baw/jtZiHeF7SzkGbybVXgPz+YiNuQStua97MylYbvLOJArOJwrOZ6reA1X8ybez3v4INfyEYb6Ffpc1alM6td9oZ7cz1J8IGo/qRKWuzmT/WRg2E+GsSiHsxg=
*/