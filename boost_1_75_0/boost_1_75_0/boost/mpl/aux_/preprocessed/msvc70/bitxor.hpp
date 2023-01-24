
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitxor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitxor_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< bitxor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitxor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitxor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitxor_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitxor_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitxor_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitxor_

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , bitxor_2< N1,N2 >
        , bitxor_<
              bitxor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitxor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitxor_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitxor_impl<
              typename bitxor_tag<N1>::type
            , typename bitxor_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitxor_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitxor_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitxor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 ^ n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitxor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitxor_wknd<
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

/* bitxor.hpp
AQrhh+rTJ0JMaEo5XaSABrHYiSWm0zp6336dTdaxfPwX1ykuKRe18oOpTjcZEsv1zX4znIE15Gi7d2NDJ9cso01tHnyoRbsh43z0+NlG8xleo/oLmEv8CNB1RbKEUZo58EsbAyRAhDISNP3BjvvN0yxSehIeAs5Pl7srnYKaJHbz8nwguaHXuecfTGZvSay+OqugLLM7+2CtV6bZmL4S85arLt0rB9VUIB+jhnVxVXijnH9BH495lE+JiFlLXClJ/pBN3v1sWUka6w3VbXLv1xq7jI4wCA/3IEVfXGxGV27Glqk3+oV3GIMi0s13/9kdhoS+d470hkR8QLMvyXbZcCQormN0sp70BCAS3Mic0El0iQ2bWJ0Bct19Qz9avbx/unxleyK7ElSb72//DU2oLWtrPYwiXgyPDyQ8I6kz4PAe80lOXZarnDeN4bl1TouutagsTmvcNfyw5wQefrZQ2Do8tqDd8nt9LOi4jYoL6UxBPfPr0w4f9y/SbT7ObQXkxk74juLFEy7y9ACfiOhOSe/oNpIrTtJ2crUOYVHL6ZFn9C5DrrGpNEb1A9EnwmmftUBH5V93da/I3FYt54DZfk6zUHLBctoG3Hk8ewKOmukXjfec36aiqU3fyP2Fs7MKigO6wnAJlgKBEAKEYAGCu7sT3IK7u7u7BHf3ENzdZXF3d4fFHZbdZdm205m2D53pTJ/uy70P9/Gb//zf
*/