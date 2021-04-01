
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
6WBHhodfcj/5iSRior/+FyAEh2fZysYuEI1WfIQ9Dd6s5hx0we302dQY6pYyPRp848TnOu7ZceU4/CiR522FuDDjGQ+3wLa7mtGf3y53Yiyj3IGILSX9qnY/XxXdcfxrP/98OlPE9CHXw+OvEYYfLQkcQi9vh1hKf6WnV0LdtoKYGbj81l9Pr1u8XR78B9HMkqt38QpgPiN5hsj/BLkBvnd8OaUVYYZSAbS3Fe0FVj5ljZtdo+F8p5dZfzNUHlzPPB4YfpHB5umwB2Y0/3idE7VNu/FTl69dNmQLZq0WlIi4ehsCden5U9nCu6MA6FLsIUfO9doIr+EOOdPU64fzcByW5uGbaRTFJMTmrRFLfHJpxIlL67TBPZ0DlsWhoc5gmEmc5AZooedmlSeJU/Ad6Qmo5N5QGiTp5gK3bs0jjhf6W4a/VfU5I9HQnrybeP7FKxxHjw6u+4mcJ9t3S21A/WTREhsnCwWufhIAJR0w8lPgpNoX7FPyWbJLIwSjARiTfctKCZKcoOONyae539wGEyql+46CQgas0/A4Rubi0OjRhoJQMqjFxJ3VlQ==
*/