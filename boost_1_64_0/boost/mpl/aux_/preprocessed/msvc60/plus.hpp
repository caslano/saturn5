
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct plus_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct plus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct plus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct plus2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus

    : if_<

          is_na<N3>
        , plus2< N1,N2 >
        , plus<
              plus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct plus2
    : aux::msvc_eti_base< typename apply_wrap2<
          plus_impl<
              typename plus_tag<N1>::type
            , typename plus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, plus2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct plus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 + n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::plus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* plus.hpp
GT6GXfGAnM/jOBLzcTQexAn4JN6KBRiFh+S4Sw1SDolZctxaaJbjFspxj0i6PSfHeV7S7aik24uSbsck3V6SdHtZ0u1VXIKv4Qo8gWvwpMSD50Mpa+RvEo96uFviESPxiMVAjMPGaMTOOEviNRvHYgJOQhOm4Bych8kSjxRchqmSb/NwJ6bhk5iOh9CMz+AC/DsuxCLMkHi3rCLlhFJ+qMS7lfU6s0zPyufmBWyBL2J3PI6D8CUci3/H8ViEt+AraMRXcTaewCV4Eu/CYtyCb+MuLMHj+A6+h+/iF/gefo2n8Bv8AL/FD/FX/Ae2Ja4fYSh+jKPwDI7DT/A2PIcmLMU78FNci5/hPfgF7sIv8WEsw/14wd6XgZQz4jBCiK4vgytyH/4ZG+IvGI5K309D0BdlzD0pJyRvZT/qMffCJb0HYyAOxdY4DNvicOyNI7AvjsQJOAojcAzejOMwDsejESfgRTxvkDJADJP8biz3HGUKkOM3kPwOkuM0wXBsihOxGaZgC7wTW+I6bCX52ga3YVs8iO2wEEPwGeyIR/FGPIWd8Cx2xvMYKvneVfK9G1YnvmFYB3thXeyD7bAv3oT9MRQHyPkmGKQcEKMkva+XfyvT3ZJvWRiA92ADXI8d8a/YC7NxLG7AabgRp+O9eCvm2PvOkDJADHZynRRIvb9DWB+fwub4NLbBQon3JkKM7Oeg7Mcfs2Q/1WRM2huwBdbE7lgbB2EdHIx1cTwG4EQMxNlYH+diI1yMjXEpNsGt2Ax3Ykvci63wMWyN0leWlNdZy/FCdH1lTZLrKBJb4FTsjjfjcJyOk/AWnIIz0IhROA9vw3SMwzUYj+twFm7ABLwXTSjfP1I2p6Rxxe+fv8j9NxNb4R04EO+U/Fwi+bgME3E5ZuEKvBfvwkdxNebjGpQ+66RczlpOF6Lrsy5R0iENm6IZB+ECHIULMRozMB4X4V9wsZzvXzAHM3Ez3ok7cCn/7cFl+DdcjsdwBRbhKnwTV+N5XIMXcC0qkV2HDfFubIr3YFdcjz0xGwfhRpyG9+IMzME0vA8X4v2YhQ/gBtyMW3ArHsRt+BRux5O4A9/AnViKufgZPoRf4cN4HWn4CFbHPdgC92Ir3Idt8FHsh3k4AA/gMMzHEXgQpc86KRtkkvudus+6YPkctcNADMGh2BHH4Y04ATvjbdgF4zAU52JXXIzdMRN74t3YCzdgb9yMfXAv9sP9OBAP4yB8FofgizgCi3AknsDR+CGOwc9wHH6J41H6QKFs0NEHSnVdHzJ9DY71IjTrue5rJlXW4zGf68B1HzLZtv1Vsl6+m+sVy3rXS/sE9XqfqNY7o9qf6/WYcl3vz9GHjJTTYH0X6526xvWyzeX/ubrZBX/1MRQRXNXRzi2/NvW0T5Rr62rXpLCqjOPq6mxzQfhc03rbl8utdbfbsl9X9bf7Z/v8YXW4Q77W1uM2Z/tcs7rco752rz533uFrV6c7K9vnT6vX7X8bYzsToghrCHmEYkIZwf92/kaIImQS9hKKCKWE6tF+hk6EcYREQhYhj1BEKCcExbAtIYqwlLCbcJxQGuOtO+6dvJN38k7eyTv9t01/Uv3/+BST+Zq0/2+qGr9/rzz/d5Dy6GBMVt7l31rP4LzutzLWlzvjnPnVPRjlvO53uskxZs18lrFLhiNy1CENp2AyScZsstW9b0kixzJokrp+vnr8qzLmtyj12+3bOcYAjGXvoG33XlXeZhN8CM0JqcGE2+pp66LGms1pppnzzcbK68QFaOq3K2dZYZwhzdhuseY0pSqRvQ6iD+co1SU09Umr+ziPay5xrVhvVhVlN+rxXes42+poHPWpOGZSGnEuljjb+xRwjOQ=
*/