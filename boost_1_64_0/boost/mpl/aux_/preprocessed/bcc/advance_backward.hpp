
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "advance_backward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_backward;
template<>
struct advance_backward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_backward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_backward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_backward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_backward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename prior<iter0>::type iter1;
        typedef typename prior<iter1>::type iter2;
        typedef typename prior<iter2>::type iter3;
        typedef typename prior<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_backward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_backward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_backward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_backward.hpp
H4HJiZjjaMdxcyLuO25TzFQKT2yu4GHl8RBb3u+NJ1Zw5pTHw4iH04l1zLs/x3hyKrGeeffnGI+DMuZNesYh/d6c50NOL9/77sZXguiPgyjWv3p/5j29iERif9yrmw39s9+tP1tp+jf73Xr9begTmZCoPIbiVR57DQR4rGkqxxFehpJ2SfxnStWPGRTYkBvjL7d9k0uH3EeJ8akocyxj2lRg42MoBcbDx7jsfBo2ZjjiMN+Y8YtFN/aaNrgTZPpQmTTtlK/ICo6O9HCUnvKTYg01w734rKV6eGdHmxefNdUI19NfVxe/u8uLzxprhGvxh+ri49aZF5811Ahn/McP9Fcjx+KxaKR/XX+UX+d6Si47avGmq5rpKRl3Oe36xgh1JS5v8Fan9vDFrHRvX7VKbUuPhZxUxjb6No2bo+Z+cNx0T1zwEaHNzePgWBlx2P5uKzWNg/JtEMepDiv48krTuCjbBnETA3HrsfaoGpqEfd9rarTPqeJYUm7aNyxAtj+5LN+Iv258s+Dq8hWp+vq381VfuFzkKwNxd665uY+mhc12GD4sOmnqo3mhe3P68uFCO8U9Ej9ytEKI4NpEQ2Jk+axop1KpGcvHqbzvUDW+jqh7zL6PVjW5lijbvCN7i6Fpk2sJ7bT5GxnGTmbTExirmwXlXVdmSAuDWO+6cp20YCsvO2Wbp4U4zdJCFYO51InKCJoT6fWPOKmKY6ThfnFKBhCee9aDhBVDPH1AHEm40eXdiPUR3Td+i1l+1cPnn2feesRPcx6uqf8YXag0ouviRv7lIYZyXRq83CGBdZguUZ/jnGE/6IbzEN6+eIWkzQk02wX6jtQXEMdnnKB7Mh7qcjD3UR2oeW1wr5hUe4/6zIhprz9LwwVRhu0kCsqwxXM2Zr9U7LyP3Jj2jZ/JYd97EummkTIm/xvElfLqr9lYNDJsjOeK4ptRovyeW+37RbyGx+WrCONyXSrLVy0smnnfNeK1XJuH7UKA/v4KfZnzsDDqyVZgrp+fDfxx0OSdm038dbXRnX4O1vvrxN0A/XlHDmnr/XXKrfgE+k0523juTA1U1ADY57+jgf9II/8dN+afg0R9npvl66XBwWHTMuaMd2P/lbLpn+Vt+OczHE3KnUnU++dEA+fH8FkH3S+H9bwv3R3P4KNG0oGioc8XB/ucJ2G43xfKmWNGBPvjshz53RsEm3FZfk5yzK7OQWKk2DAPLC9+F4YnkenLK6sc70XwvDF8eWUzhbZBa7DqnwlmOTl4Ota0Uz69yQj6K+fq/aCMeLzjHUZcr64h/+3+eCwf/Xk0WJjxK2osvx23hEqOkbZeLpz3rn2gxYrE4sD1+8My8vxOFPj5Z9l2qteXRv42OTLjTdNa/EqqY2XA/xwTainnVFZ2cWijPdeEULcdlA/ZhCJh5lL5Cpmfc4w/RAwt4yVhz14ulNpzs/ptK96XbO8YwX7XPT9rnMT+23eI5N7VQ0xL3lXAt74nchPMk5feisbpobfoH5ffcHqI2Sw9tido27T951OLjdoRfyPIZ+xUYUifY4pfNfbfz6zfd3llPRAw+yLeTXrL+9yukRYLwmZKTdKBUX06zbzrx11i6/vPCbYmNiHJU2cXizvEOqGWtPdto5mOT/0uLGUxPZCOvHyW7BvNC+uLPjec/rfywCJkHurmq42vbao8qZbAm6xu8vVNL47b/66ezHIn3SxK93uxdc9j0lDVKK9dcm89ONfxrxcPbvF5kZqlw+LQ88Quv29f8I5yxta/c0sjX3vkf1w3gLey68OY4UZ1C/3869tzB717b/Llrml/XuX2SdKdbmU+LPeOjNVDW19d0yPQPrQp7tnU58CIwTQ2xc1kZvQ=
*/