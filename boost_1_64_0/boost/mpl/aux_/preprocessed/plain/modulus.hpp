
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct modulus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct modulus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus

    : modulus_impl<
          typename modulus_tag<N1>::type
        , typename modulus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {
template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  % BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* modulus.hpp
Cd++I0QTjE08dUs8g2fwDJ7BM/yTvfuAj6JM4zgemnQJkIRAgoQqndA7BkLoXRBENAkkhEBIYgpNREQshw0EBTsqdk8jeoqKGk9UFJSgHIeAmlNEzkONgoqKer+Z/Hd3dnY3u6uoV3Y+vn7ZzezM877zzmyZt4SW0BJa/ujld7n/n5U507z9fwru/8+1zAEY5+i7TKqi7/yrzQG9nPfRExlsX7eTzHETgxpfOBWtc10s1/4aan/Gk2tYb6P3/TF+ov/xs633nuMrq++Ytt+ctJbtF3vffm5eJk0DuFEXzFwM88PNe4Lm4zrK5yK03mvOzE5jH657hC1iNA+ALd6divcGUl31S1zH9sqquLdj8Bz1OCzgsb51b9x5L/JGHudqYhONje0cO9s6t0VWFc/YbmK9oqpusXkdiTgs7JfHt96MLy/LOq+UxvJ2mwsnTje09yu+vaSbjddWc4tPs9r5n3vJFo/P8bqPeytD+1wwtjLtppgfUMyDFfNA0q3G+Xaae8xkP+C2Nfa2DzewJ16vOLyXXR+1JeirOHqq7Erd4uhqll0wY537LjvPuems5VJsj0flEl/dLZ5TWi7WOHq5zdunuYpkmnF8nHGYA60PMybhCWy+vjrmdstq8Ho02lw8U/7vVmPG9TUf3+983Md8vNH5uHeF8/jwmAlrXOVqzKuSm5NvznGwrVp5e4HbWPfV6u5z3RhxGTOoONoRHXfMf2NuzTX/GeeXuZ6uWW7H63h1/qc+6HXlbcY5UdOtnEYyHn0A5115GS2vpTgpg+a1HGXQtWuYngt3PRcfprL8uaZ7WX5e070sD9cMrCwzlVHHNchavmrrw3MqD1udKdZFroZRFvJ29lFmxGuZk0uz1gRQf+tonjNXnVlc2z1f85yPe5uPz3c+7mU+Hu983NN8PNT5uEeFc/SO0HyEXXQediDdwXoJddzzkq530cnMWfBLrw9GOVdrRJ1JL2Ar7mX6ZE3P8ZXvNs5DWxy8Mqg5Xjdq/9Z9zdFParuV5zdJKay32m1fXTUvWeDzVSivXt8zrPOq6Smv7yNllvcRa8yxtT1jvof1Nta1xWy8jf6KmC3vxT7nBtlMRFpFMXt/z9mgmAco5j5hmm/6dGfMmfk00StInTUnPYi2pYrZdh10r9dDdQGap31nkO7ldWH1tG/NQWep17/oM4zjvWY4e2WqSS/1XNcTzfekp9zKaZ9ivVOx3kq636iPbrE6CyrocoqytFF1lbbn+4g1pqF1NYevYuqvz+0p4c42ncYsb9S3dD6iBnbsjH0pJrfPxAM0H94B7evvpAeNemLZl/u0bMakeOYM137faxqoLOxzddnnxtNnecbS5/k0mmdaPvsNN5/j6NrOCdrvmu+9Iwi6D3m4m+dKjZgt54q5Xxoy6j3ELd/hmk9vp/K9nfQQ+S6p7yvfzkn1/ObbeA9Y1cDV1rOJysHLHHeK1TonnqvOTo11rM/9eld56DnKxFaXr1GelilPS0jpRp4aOPKkt0UzG4HVGz/nvLO9ZFVd8BZo33mkh3ldbkP3eZpmub5bJc8yv70EP2endd6J7dpvibFf+QjrhUe47zddOTffxAJ6Dy3/XLAzwvW54PII988BSyLcPwfkRLh/DkiL8P05wFp2CZpHcLHyUEj6M+vFRbrnIc/53c9RdIHkQ/v18l5cov2eo/1OIj3GesWu/Wam5junUAx4X1f35D0rNYDvJekFbr9X5LIRY+mveHqTHiee+ChnPOaUh86IAjiOjmuQ5uk1zhmvcUUpri/0XPme3L83hWs+vecV3zOkJ4lveZTb/FUUWiB1ulr9Wo0c1whXnJuNc4YN8M8Ky09l7P7ZWPHdofhuIT0=
*/