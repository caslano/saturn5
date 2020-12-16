
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template< typename T, bool has_type_ >
struct quote_impl
    : T
{
};

template< typename T >
struct quote_impl< T,false >
{
    typedef T type;
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl<
              F<U1>
            , aux::has_type< F<U1> >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl<
              F< U1,U2 >
            , aux::has_type< F< U1,U2 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl<
              F< U1,U2,U3 >
            , aux::has_type< F< U1,U2,U3 > >::value
            >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4 >
            , aux::has_type< F< U1,U2,U3,U4 > >::value
            >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl<
              F< U1,U2,U3,U4,U5 >
            , aux::has_type< F< U1,U2,U3,U4,U5 > >::value
            >

    {
    };
};

}}


/* quote.hpp
3BJDwRgPx1AOjVIOK2R8/zKkVruXv6kqB3oDbMSZCfiqquOH+gbHWfjtzYafxJ7jLZU9mXEeCHwUQawZsW2Iz0CwooBGKXfDvHYpd918bkVsP63cD5OTBoztZd8wzW9IWil3iQuo6F/I6Mc/IXEOtpH3PW+r8u7lnUBrVeyvIRV6P3vc31djjPFzRHzQz5Pajg+N1j4U5Zfbn7sSWteT6d/wK2AzxDuLN8+NruNHs9qPTr2Pii/6eRyGe/yJePM8/fvxJfakpS/S5Dq9vvzCdR3xKXCO6uUc6a8Rd/+QeiL+ZKj96fS7o8IXKRu2BHXZ5Fn74m+gSykcf9vVRf4E6m9NgrlsdmjtlYU/HX32Fh9ol83rk8Umqn2oV/vQ6fcAlS/Bfh3xZYa031OQnfjSZOmLhGyz2Y7r/VDHlZJ5WhYxxSYnmZ/jH8C/tN9Z+8fbQ8RlZI55Y/TjUFLIORM/MtR+dPj9Sf8ugQZDvckaoPYhT+1Dp9+n2osDdFL8SRF/BiIP4k+12p8ufccK3H+1WCCi0rjW60Bzvfmcdo2pfZMARZHfK82xiYxldFYR62C3dn1Z+SFPGHbi24Q7X6LFUCY7ks3n6/P40mLpi6/UTtwwO2Ui8V2CcXf0fqWkqMso7R1Lv7hZRf4N4V/s3QtcFVUewHF8v7BQER+g4vuFim98g6KioqJimukCAoqKQICKhYpKiekalaWWKZkamhmpGZoPNE1XMdHI1MwoLR+ZUZJRa+3+5t7/nTtz74BgfXY/u5/87Nkv9zRnzjnzOHfmzNxz7Mfb0e+rdDf78ytNOceNy/GH7mFMZZFKy1p0ZfFqYF+WDcQFG5flD93XuEhZylEWdS02+2iblEc7ntXrxCVpysPPeNVvKo6cEo0ZZSkLc+lSlpm6OVsT5LfoM8pzTOAk3ESeafo8dXlF2mVjOEafXb6WbVCLPNR1SvmOy5g9/BDb9Hmlsg7ShZBO2Y9X+byZck2eNWVKJ0mzz2Ycul3yebp8PiLrjJGxSLLUe7OZXPTwSFi+GzOJV8oePWUKO9kcl63Jr6MpfbkaGXxuxfYazedPle0j682Q9fIkOYgxiKbGR5jjt1niQxLUeLa9uq54WVfbb63rSi9iXRuN16Uft9BdxoyT+7aOmE4+nvnWfTnV1PpNnhEuv7NmkItY2o77jtFkegYtz5ZjSK0+gza4By60Gx9Q9ovm2bKynhncg3WSuHuaOKJ0x2i21KuOnBe1CVupV9YPmnrNVI4mRmafXvLzwTRfq3y2zLHMCnR5h/GARjcuqJyneZq8LTmX5lyUvNVzwnr80dCESp+DnCscCpwF+m3STH5Pv51QXX53u51yOf1oXy4uCUp8T25brnhrucJC5sqYPkWU11lbXs2xIN9HuvLvaiKZy7E6H5V+tHxN+S3tJBfkJejX0bW3dn0xlncLNPe6urEbwuTl5gFVKA/2Q6U8eQWm8pheXpGbJVNZwh6wLPQGmrZhpno+z5UbVcbOlDZDuYcwVVrGec7SLBsSyQnLDPbhks8l+W9xceZ9kMNn9VpSlrmqOR/ttoPE5RFnvpfjBJR05yVd9AzrOKrq97qULVfiKJfmBlf6WmTcVfMcGOY2NJP9Hsy2/pHjZOHP1v6wfKl3gjo+q3zWtAe68Txkfz0tx/8iJR11SnIwjSdheWhZ6vsnaQs08yhr+v7UviZ5RyV8thzTcgw1l9+lSFvhQUhxof0tYy1TXHjklKC4aVOjStEXLHnr8nJvYV7wltT/uvRDx0heysM8zbipD3T+FGiOWV0fm3wfRlBfN8qxjM8fmPKV/W5zDFNu3bmW0FL6k2VM9UqolD2trKbsSuISvC+l9OcuKm8=
*/