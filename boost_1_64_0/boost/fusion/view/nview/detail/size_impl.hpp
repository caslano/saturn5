/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NVIEW_SIZE_IMPL_OCT_06_2009_0525PM)
#define FUSION_NVIEW_SIZE_IMPL_OCT_06_2009_0525PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>

namespace boost { namespace fusion
{
    struct nview_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<nview_tag>
        {
            template <typename Sequence>
            struct apply
                : result_of::distance<
                    typename result_of::begin<Sequence>::type
                  , typename result_of::end<Sequence>::type>
            {};
        };
    }
}}

#endif



/* size_impl.hpp
ZbUsZWAomBz+cS8N6OUu12l9UNGjwyISzbesCmgcBZcDjw2AiA0AVOoLSQ7z4hTqQ6NkZWhkduEfYxwAJ+sLEyknPkmdXcBCQxFJFa5aYNhbjATgJN0RTzKIV6cDvn4e2TaBUPC5wGM3IGI3AE492NXqU6JOF6QV8OHvt3M7z9RED/FO+Bx8v/6kyeE0PSeF/MWUttWDbsZ56/7DV1nxT6NwbW+iwYD5/uLrrsObyLYAgJ9Y26QJFHcIFCsaKE6B4IunLK7FvQSKa1lKcShSXIrbAsUdiutCeYstGvwtWmBxe6evd8490/cy3/7Rb/e3V861mXsnmQy5UFmxOA3zoOWVlnKeJSygmh6CmOU79LAgzX+0jsJy49+c8yxPaR+FFs0spmm/dnR279RDLDP3pg0N6Hywuh7SMpu8fURz+lxwdXV5td6dDqTPkqFVYhbiylyZ1uka3vN0odmY1R0UdZTKQ8vE7FHY/N8oBrSczP58vKoh3TejFdFJa9/I+IXqUksPWDjZ0cDONlpL0NIwM6Ytm5v2ZGgRzMbN9G9LMdTGPiJT91GMhiWijdOzNrO+OqBY8oH/EZB2pOcRKi8JrRWzP7KvGkBtVl8PS3XMzp5dTfdPDfXgBmn3H3Sl8QKN9BAqTZxRi3Ros1ietvO175I10cMHHp/f3trUDy499GM2+lyLLnTmHyr7Ic9/7+CeHqXz8lRm+rNQOzovb6qHhszSVw/IrlgkWs400vwmrVpB5/pd9bBDJ+36ic4H6VlBdz0kijzt+DfNlp91FQvroYfRzBpPPHVfMeipBwyfzBVdNhM97+itB3+TtNxvRvtR7AP0sEsnbcg/P08o5o7QQ3mWrumWsMZU3gjZR/ZUzxHcaKNZnpVeznFQfKP0UJDVs2y3K2coT/xwwhOQVmrB0GBq60g9vGM293s1A+WJA/c6sxdt4kMUS34ovpLV5eqG6mWpnlF6WAHSxv2z/xG1Cz507crsmy5dL3r2gjaD2e3Daz9Tv+NHO9Ox+E4OPbuIYpjsvbwktC7Mnus61aJ6TlFbli1RHSkd2ieDtO63fslDNlMPZVhdKkalnU8xzJbrvF2s85QOLQuZuK4IC5jjPZ0Trag0cV0R7aJhCWhBZGJdEgZzvadzzvVeF7dGungNS5rrvS6OWO/p3LHe6xKnkc6jYfZ53usSNs97eTEa6RLR9jO7u7ypgfphvjpdt/qVmykGC9Rz7O2dO7doTCzUw0xmJ/I2Ka88F01EKyYsL+ghd+/2xRQLWKSHezpp3/6scFwx9xI9+ABZymeMhUWivWPWo0XzAorFLxXtIozaBf/xoAVJU13/7MtkPfOBQdRTXMfQ7AZpcUPN8+l6u1KUJ0yWBxCJVlSa6FtxDUcLkqaqC6wS9xPCSh5vSnk6VonYhdWImSHruVoPQ0V7BmJ8Y+uuPyjffaSH4SBt2tyoe3TPhzZYxJf8CUuLc/0QxZybcH0FabPuj8tLz9/RKjBrOLvoB8Xgd+/p3Gj5WXltZowqRPet8Th+QdrMt7//pZh9mx6mMzOUunFSsUS0xsDyPFpvG8WwXdwPCvu9sCdSsZhUVqnq0ozULqnMtGV3oGKOHWr7Z72+JX32AM1PmjgvFuWhBeikdU3a+UqxpJ3imiOs5cXgbNRmu/TwG7N7K26uo3bZjdd+Zq3CRz2g8tDm8/i+PH1GY3ePHu6LuiRPoK1H9xWn+6V9evgM0sbl01vonm+/HsYzG1Z/GVncARxbLM+W3cb60f3nIT2MAmljbi+30bg+jNcIkS55Ivw1PBd9LiggQQ++ejI8j/9Rk8o7ljL/hKnmXyJaUWmq+RdwHK8fIs/kwXco9wa6V/ScxLU=
*/