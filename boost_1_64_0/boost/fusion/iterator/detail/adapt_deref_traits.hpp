/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ADAPT_DEREF_TRAITS_05062005_0900)
#define FUSION_ADAPT_DEREF_TRAITS_05062005_0900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref.hpp>

namespace boost { namespace fusion { namespace detail
{
    struct adapt_deref_traits
    {
        template <typename Iterator>
        struct apply
        {
            typedef typename
                result_of::deref<typename Iterator::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return *i.first;
            }
        };
    };
}}}

#endif



/* adapt_deref_traits.hpp
Kja2jpiCX46ht74m/OROdLfMw7kp127i3OFqeIlNeh9CV7B3/yXQ+Wfo/Au573+IhwP647ewTXQydDN1G7Va4pcjyB2x2TZyziPpA9NfSy0ZQ35hsT52sdqihoVG9uQ5iHqqmc/IPpnEl+xPn/Cv+FX62/FX0CVyU7EW+RxG3nAXPu0xfuFhtDexaxX+6ntkTO8hcTS+YPcY5kUnP8cu9uCbPiD3vhJbvWMo+jqW2hyeUj97qRUz6/j7+XHoDXpUgs89Ap7egA6D4zmNdTm/iF48gHU55wAuxqMzS+Hvenx0J/KdP3UhX8cfP42/gH7/slHo1UDkjV/dF57U9aXWZo/QZaHTYjixYC4+iL996JX32rHcR05xNfZMjpR6FN0A5s3gDzk3s5rIU3bCs27Y7nPsE1iaX8/nrEten+R6FZ8zrJlIE8M+xkd/By/JwWP2tRnk58BTh8IXarjYnfARvie+597foK82DvlBfDrXwcsksNfbyd/4O8lvlM+Z26ETXsePIeefih0+Q5wcBq8uIv/5YVhW/yqJJ/fis/7B/bY8plv4QniwhjyeGCbIy7yTsINdrFVn+yTkeAt+nZpR/BuePw7P/43NUOPEZgELE5ffIT6fTVy/gbr8WOL2MdjjC5x58Jus7YefGMWc5D0fFpHPo/fQlLLtIs15FTwWSXQwii1il6EDkeMP+LD9ySum9OGsFbu/hDhzFrz4Al90K+t1Gs47+0by3iZqvlvJG2LcZ/uTj6H7AXRvMfn6z/E7h5JvbmDe07HJy6G7uAsxDXlUkvO+B482oguLmf8PrEVPMcq/SZX5D752Hfkd+XfVvthxKX7leOzmCubZj77MBdgrOFVxYsXX0PGgXe9Dy0b8GrlrDJzoXuwXf+bb365hWOMd9PppeI2u+x6k9iRnDX1EDE7Ti6wCvp57viW/CkMLOZqXvD2K3luPoY972dc+Fj6ZeP4G9BA7BPWRr6Qn+Rv8HYL93NmF/A+d3MX+u5G7cC21aAhni7ZvxD8RI6tOwRZGYr8PkZvYOjeKOnQhtRFzpRcUIwLq9VXobl0n/Ar+7WboCBKLOO+If0UudxLr3FjCPcX0arHHk1nrMXKQYmrtd9GD7+hn7IdOX0Euel0x/UDygk34s7nMtwl5TMDuXydung9trdgxvd3oCfBxzQh6SPixY+BZGj4lh9EzRAeBxciDxVj4eww+931iJnyM/ZW4jb8Wh6DD5IRx+m8x9NeCzqrh6N8k7Ixc3bOdOOanRqQmyFDX+6Hd+yfsaF94gJ/2bSzhe/3MsQEfdCsxPc5eee4mxZpRzm+sr9B5+hbR3chwQwmxtZh18QnbwEUHU+kS+mf4G3L+ED40Rb1R9W9ymzJyuGuhC34luMfzMvkyfc/US/DiGmSzcjwyIfbM6we/8Y3U0ZnD4I/Av12G/PHZ6XnYCjVo9HVkv7E/59vE5Ti8x8bEUD4TF/0v4CM5yxLUuaFPsa+TqEHp8cbvsvvIFu9CpW6h3k9zLTp0NDVpD8ELish30dNb0ZffDEJ3iYt34Qfu4CxufGfmIz5PL+I9Xdgn9yZf74IPgdZbmLsLOd4Ho8mPsLUy6CY3raKm8nahxzKYHAn86Mvo2nPskxotzdxiFfn+ieT+6HCaOOAnr09Ra6Rfge/0q9Ix/PKj8P9eaOIMJk2PO74TuSzGBqnLqnawx1XEjoox7B0dOQBZ8rfn+07wkpj1MLZ+Hzr8Zm94iL9fDZ95PiTKuyLETdg57+f0vYxPZG/eiejoIGxnM/FyPGcOYzpT39GTWFqMjcOvdeiHXf+2kW+wVjyEXX5B3HwBXe3MWidgJwn0I4Sft/3UKujfjd8aTc5G/yg=
*/