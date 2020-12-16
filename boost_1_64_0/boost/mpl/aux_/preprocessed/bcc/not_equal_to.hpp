
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
rnzJVFbyA4c4T9jFPjxHAd7iHXoxmtlsYB8XSP2B7clOcd6jL5NZzSH+5v4PbUMF3qUbgxjFfNZzkF+5xt0fWZfkpwrN+IjPmM92TvE3936sHlOYajTlQwYxhWXs5RLpPzGOFKEabenHRFawhzP8y/1dxUBeKtGKXoxjCTs5yXXSdzNmFKYq7/Ihg5nMSvZzkdTd5RdZyE0ZatCEtnxEH4YykaVs5xf+JE0Pn1HIRlEqU4uWdGcY01nFHg5xmdQ9nZfJQmEq8g4d6c8IZrOe/Zwn7mV+yU1ZGtCRQUxkHQf4nT+Ie7t252lyUJhy1KEFH9CLIYxkFivZxs/8yV19/E6BQpSjIR0ZwFcsYSuHuMgt7uyrfpGNwlShCV0YxBQWsZdT/MsD/eQCr1ORZnRmIOP4ls0c4iKp+ssJMpGbElSlMe3pxedMZD7rOchF0g1QxyjO27xHbyawjG0c5Tr3DdR/clGK6jSmLb35kmmsYjdnuMXdg8RGDopTmUa05hOGMYuNHOU66Qfbh9coRxN6MIo5rOMQV0g7xLbkpSxv8w7t6clw5vA9J7nJ/Z/qN7koRTWa0pH+fMN69vMbqT9zzU8e3qQOXRjKTJazmSP8zYND1TcKUp56tKc3w5nBZk6T6nPnE7JSgga0px9jWcQufiX8Qn3mNYpRkxZ04VPGM5+NHONfHhymxlGIitTlPT5hCBNZwkb28zuph7ueJBclaEp3RjOdJezkFy4Rfal2kJlclKAOrejJcGaxgcP8xZ0jnMvITSlq8R6fMJSZbOQXrnP/SOuIYlSmPp3ozWgWsIlfuMIdo9RJ8lOd9+nJeJayg584zV/cPlr94jVK04jO9GEk01nGj5wlGqPG8wyv04BuDGc+O7hI2rHqDjkpRiO68ynjmMkSNnCYS6QZZx+K0oSujGc1B7nGPeNdB1CMunzESBaxj7949Cu/06QKLRnEVLZyipQJ4qcojejNV6xkFydJJsoFXqU8rRnCfLZwjlRf+4xELqrSmv5MZiX7uMSdk8w5r1CaGrShL1+xlL1c5p7Jzl0UoirvM5BvWMk+LhFOUWPIRAGq0obBzGYDx7nGXd8YV/JSmfcZwEQWs51TXCftVOuSLOSnAk34gE+ZzLds5SC/coX006x9StGUjxnGPHZxhbumq/EUpwndGM23/Mg5ohnGlLxUpg2Dmc1OfiP1TGuOEjSmK2NYwQ5OcZO0s+QCL5CH8jSlM/34kqksYSMHOEc027ojE1kpRkUa0JKO9GEKy9nAT/xONMf64AWKUoOW9GEM37KOPRzn2n/bzzXelKYxPZnAfFazh9OE85yPeIbCvE1LujGUaSzlR84RzTeXZKMwlWhKR3ozgZXs5gzxAmPGo7xAEaryLm3oyXDms5PzpPnWthSmFh8wnhVsYi+n+IPUC8VDFgpTgSZ04TMmsJjtHOEMf5F2kfMQr1KGpnRlMOOZy1p28BOnuMYDi527KUhVWtKNkUxjDfv5nX+5f4nawutUpRldGcZs1nKImzyy1GcqilOTdvRhAuvYy0n+If0y7VKY0lSmNu/Qln6MZBar2MFRfucWaZc7HlnISxka0pb+jGEu69jPJVKvMI+8SB5KUZc2DGAC89nAHo5xlXQrfW7nZUpSmZZ0ZxgzWMd+LvAPd61yfuZ5ClCWWrxPd0Ywi1Vs5xeucIt0q8XJSxSkPI3oRG9GMI1lbOEX/iTdGnGSjaJUowWfMJx5rGcfJ7lG6rXi5AXy8ia1aEU3PuNrlrCNo1wl+k6t5X9kIRclqElLPmIAw5jCEnZwjJvcu079JQ8VqEsLejKaBezkHNdJtV6cvEABatKCjvTmC75mEd+zjzPc4r4N6gM=
*/