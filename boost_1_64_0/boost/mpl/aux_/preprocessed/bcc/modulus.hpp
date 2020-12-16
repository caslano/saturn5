
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "modulus.hpp" header
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
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

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
jMEz5KEM9ehAf8azgA0c4BK3veqYZOJ5cpKf0lThbRrSgi70oj/DGM8MvuMwV7jtNeudzLxKMSpSm/foylC+ZjYr2cpeLnNHLucD8lKGunTiMyaxkh38wh/cmVvd4FWKUYG6tOAjBjGJeaxmN8e5TJDHOYH/8QzZKEJp6tCeHgxmJJOZywo2sYejXOBvUuWVy7xEMerQhsFMZh3HSMlnvZCT4lSlKR3ozWhm8x27+YWL3J5frOSkGLVpzUC+YRPHuERYQD7xFDkpSwO6MJApLGc/V7m/oP5TiLdoyIcMZirL2MrPXCWlkHpBVgpTiSZ0pB+jmMZytnKcf7izsPVBdopRg5b0YAQzWM0efuU6D7xuTClJbdozlOls5gzpiqgfFKACzenBCGazgb2c5jp3FpX3ZKUIFalPe7rxOVNYxmaO8Cd3FpMrFKQaLenKF0xiQTHbc4DfCd4wTuSkJPXpwBC+Yj7r+IXrpCtujnmJQrzF+3Tnc6aylM0c5w+SEj5HkJPytKInI5jHd+znHP+QpqRjkIX8vEk1mtCZQUzgW9ayl9P8zYOl1AryUoYGtKYbXzCJRWzlJy5wk3SlrVOyU4hqvEMnBjCGmaxgG4e5RPimNcVTZKcQZahBMz5mEKOYyiK+Yye/cJGgjHnjSbLyOuWpRXM+ZhizWMMujnCelLLWEY/xHHmpQGM68SlTWMpBznCN+8vJE3JTnsZ0pg8jmcFKtnCIy6Qrbx/yUY3W9GUmq9nNVVK/pS/koiIt6Mnwt2zLdxzgOJdIKvi8TTaKUZ3W9GUMK9nOz1zjgYpyiWK8TeuKtmVsRe2zmt38yr+krSRuXqM8TfiYUSxgK2dIKhtHClOZVvRgAuv4lX+4r4rcpALv0ZcJfMtWjvM391c1J+ShJNV5j658wdcsZgunSalm3MhDbVrTn0ms4gBXuKO6/pCfarSkK58znWXs4wp3v62e8QrFqEJDOtKDoUxkPhs5wjn+IF0Nx6EAb9GQjvRnGJNYxnZOcImopnM8GclDOZrQiR58xiQWsZ3DXCClljwmM7kpR1O6MIQJzOM79nKK69xdW4zkpRz1aMtQ5rCFU/zLg3XUYApRmSZ0oA/jWMZOfuUG99Z1fUURatCZocxlC0f4g7ietslGUerQigGMZSpL2cwBznKN++ubG7KQm6JUpRm9mcBitrCHn/mdpIFrZ54nH2V4h450ZwSzWc8uTnGVdA1dr5OPctSiGZ0ZxmSWs5WfuMxtjdRispCXUtSmFd0ZxVw2NbIPFwgbWyPkoDzv8QlD+IpZLGIt2zjEJYImaj+PkZmXKU5NmtKRPoxkMgtZyx6OcoKL3CBVU3WCZ8hNKWrSgo8YxEQWsplDXCR6x7yQmcJUoAbN+YB+jGI637KSHRznL257Vy3jGfLxJjVoSnsGMp7FbOUIl0hp5hxJNt6gBq3oxjAmspRtnOQ6dzR3jcDLFKcWbejDGGbzHVs4yFlSWoiNgtSmC18ym3Uc4E8eek+9pAot6cUYprCATRziAlFL801mcvMGtWhBF/oxhsmsYTMHOMEF7mjl3EteSlKNd2lDb4YzjTXs41eucc/76gzPU4AS1KQ5HzOUiSxkG8e5TNJavGSgAOVoQCu6MogJzGYBq/ie/ZzgHNdI2oiBh8nEyxThLarRiPf5mF4MZRxzWMl2fuY8N7m9rRzgefJRnAo0pjM9GcI4FrKVnzjDDe5qZw7IR0Ua05GeDGE0c1nLjxzlD1K11wcy8iL5KUMt3qMno1nAOn7iMmk6qCfkoyz1aE1vRrCcvZwndUfrmjyUoyEdGMxUVvMjp7nBfZ3UagpQlZb0YjiTWcx37OYIV4g6y1teoiS1eZ8=
*/