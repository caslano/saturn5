
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
2+li8xPzITDzlB3pmE6is9pZ7G1E9dyBtf9n5FP8TsGWGPLUCqj3vekUuoAy1or1AUPuZsTLTjLMHGTOtrjd2e4GJpxo97cH28PtUXYeuE4j95h7zc3yuSXuEUM0S2NxWmeehNmpCrariYlinXgk6kBvTZKfgvnek2VNgWox3vwRuybYCrXCsAZRVjmrEpRYDGYqFlX1J/u2/dzu5+wJrE1mkEIwtAajvELPaTYq4FHjutEZSHeO2+YSc6Z12zJdD+vvY0d2kDIBQ10icMo7kKXkEyiyw+QKdoMBhsqYZOPYSH20/kBvYowAs7kJLXFfPBbPhCKDZagMk5EySpaTlWS0jJF3gCaxdhM8f5I9z86zNzrXsVqvu3Pcte4W93v3vlvWM70szGgA74KUbB9f1pIvyEGosBtkB9vNcqC8D0GxJuj79SNQ1Xf1UGOekWEshaL+0thunADOXASOPTFeGIv5Mr6Sf8Vz+AEeKUqLimDhk8VUsVN8I/aJu/KR/JMsaZY1K5sMM+mavXEi5poLUEWemC/MylZ1zOFGays0+Mf2SjCLE3ZgNss4LZ0WXrzXESjwOtTDHC8dylo5GqTswP0GtEM5UolEkxhSB/uMEA2zZ5PGJI60BGNMIJ3BCnqSRNITWDVTjwWPfgSdUJCX51V4DOpbR96Nf8AXofbUFQ2x7i1EvOgopojVUJDFpS73gDUfMVOsqdZ7Vqa13PrU2o8qdBzq8Tb0bDe7l93Pbo4T0cF5ExV+GryA0m5Fl7i6a7kdoJd7gqmsgTPwpdvV6+m9GpjrC1hnDNGEk99QnwrT4rQfy2bfs+vsH7lknq83nuHkBhuhRpgRafSV4+XH8rLMgo5Nst4BY822ituu/b4d4ZQGMzKBYAm45kj3TazyJfe5W9Sr4mVijVd5a6EpN4LDBvl8+ndSQe2izlVvqTXoOHqS3mB3WS9joDHcWAfmuRPaO4635jMxMx/yeWIZ1NQBcQrVI0bWkbGozJoU0paNZRwqdLxMkJ1lN9lTJsr+qNbD5SiZDI9igkwBE5ouZ8o0ucGqZz+1052HzgunkFvICwdrDaQHGbiXj8gqsg4s6E+kmPq5ekRtR4fRWvAP2sPjqaRHo67VgSdCdE0Xuq031rONirw6cEzwitBaYbKBzJG/yFJmPbOx2dzsBf0702pkG3Yfe5ydZW+Bc/PE5nBtujrrnd3wa+6A3TtQO2+5H7mb3fPuHVTYWkCul7zWXm/vqadEBivJPp9siN3UnLxCZpI0sMoMshjMOgt3u5Zk42SWZfXZepyNE2BMd+DoFNUCno4F9tVfXwhG2F52kf8RJaAGr9j3nWBwss/cPkC356ibwX5dKwecnAxlkQVVE+dr2+e0NAvSisJLyQQ3XKWt1bK1ZGMjzt5NOBDb+S3xhbnZ3In9kG4ttD6yujj9nIlgZJ842c4B5yS4eUGXurY7HM7CCjfbLQCOHqzE4Fo1SLyaRBewTdp5XeH1RLwcbWaAkV9wQsHH8z9Tj/RUJ9GVbL92Vy/Bpeghp5orre/tew4UR0L+ZyzST51KN7GT2gs9mrcUA+Usc5110n7sVAOPzv9MEzhE0ylmSyto4NSJkTLD3Gz9bBdw66NO5H+mLRmjLqTfsItaEaM+7yUmy1XmAeueXTJQHVPyP9OTTFNX0R/Yfa2yYfP+YprcYp6xgpyaLvRZWv5nRpAP1M30IgvSGxjt+VixQH4Fl6WUo7u9ofvzP5NCVqv7aB4rqdtwcaaLNfKYedeq4Nhukqdk538mjWxVz9JgrYbexhjBF4it8rJZCE5NWxfsYHf+ZxaQ/eoNGgVfqI8xia8Q++RdM8p2nUR3BjAq/zOryFH1Lo0=
*/