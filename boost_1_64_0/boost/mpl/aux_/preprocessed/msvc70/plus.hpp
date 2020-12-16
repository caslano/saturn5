
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
    : tag< T,na >
{
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

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , plus2< N1,N2 >
        , plus<
              plus2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

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
PecjneerPOdpnvIuPnl0961avtUr5L6VwXbct/rdvveN8phKCbMF6SdGqV9dIl3lUfXzmV9a4jz/3u0zqJhwis8XFGtKZS2GtBFKWUxqoawec8dZqvNZiY4SXfuSJq+350u9nIN0IA9q3tblAQ26NmvP/5ofdY78suFSH93nqd7+iipp08zXT4iPGwl/1H1OfKrtu8T2C8T2uUi01qbs0dnObSjNzwuoznn9XhVUOvT+FCvyPW2jt60W++TelPq03Q5piKvEvgvFvhoT++zLf3r7ImXO/Zli3xSkE/alvONrXxlFN/hni/uZaHxGiD9Un/q4Wew5TewZi8Ro+eWyR158NHuc09xzK4J4v3Ag/Eqb7Sj5pvg3U/KNc7FzbOz90r/TdbC3Hyz5hOD3sg92z/Rg97g331P+x+uXO9576JvvZW+1Z71VP6TVnEXrvfU7TNKuH14zIXbxus3X3PHuxLlXnLr/guD7FS18Hkg/obwbS3u3w2cM/zTpN0mHiXAiTIKT4WiYAU+DU2SsfSo8F06TMf0zoUuPvMuCPBM9J4qePrAr7Au7w35wEOwP0+EAOBX+DM6FA+H5MFnZI413TyU9+j3ShoieU0RPiuhJhYNhGsyAI+F0OApeAEfDRXCspOtUz5wleUeE34s+dc7S86LvT6LvZThU5kJmwtdgAWyAS+Ab8EL4JrwV7oJPwt3wbfgW/Bd7dwIXRdkHcHwVFO9IEY88UDEVLzzyPhCPwBMV7wM5BeVSVkXz1pQUDc2DPMn7yvDKTC1SMg9USkssKzxKMytS094ye3+z+wdml91X8EWr953n09PXWWZnnueZZ2ZnnnnmmW/xAt7ANLwvfSZ/w6+yxm6U8zs53ztuNnZjiKQrHJtiJLbAsdLeq5dyHo89MBq9cRIOwcnoh1MxBKdLu99MaR+djVNxjrSjxWAszsPXMFbytxDfwDjcgItQxvqX8xzSJOlXj/W/XNK/RurlWqmHCdgP38ChuB7H4wacK+2JcbhJ3qmwWdprt+B2aVc8itvxIu7AdOmDmIFvoZKoRCyBu7A67sZWuAfb4T7sh2/jYHwHR+ABHI3vYjgelPx66eScBodJPbLDTpLf0pLfMlgBHWQ/dMSWWE72uwo4CCtmjSEp5xs4XJar7vPjK8v1Qwf0l3oQgB0xUPazINX+FSfLG2dh/+ony+svyxuADXEgdsNBUo8GS3qHyHYiUp/Iu9R/0ip97+T3Hj1lfeq+d91lfb2k3vbGzthH1T4eJ99vK99Xt49flu9flXL8HZOZh7EF/+OYgm1aWu5Ts5eYSpQxA3OMFyjjBFocI9D62IDMR9S1Mx0HUMYAlPH/1GP/mbYxxxI3EGWMv8ce368SMXMMv4HE2UQZsy/HeH05x+izND6f5XH5co7Jlz0eXzLt3enEB8RKAfSlIQYQY4hbiMeJN4hFArV2cS1oQQta0IIWtKAFLWhBC1rIbXjC9/+Vobbypf//GtUYfA4FzN77Lu8s9vpYfc/AsO5HjiVRWsb985rIshiRJzwwu53dvqC19nRr7dHW2s3/umfc86v9/Um3p1u+r2Ctnd16e3pzQ3v62NoepT48+dUk9+puW9K+r9ct7+8Etna/xPisp9Q1qYOJZs96lpN3YVTAElgRS+FzWB6rY9w/qP3p79L2lN/tTuo2p3paW5IWtKAFLWhBC1rQghb+D4ItMejJXf8HKXPmx7j/ShtAQmldjvHqJ8i4ZkF4hoFwIs+q++kZ15/Zl74e5gwFZrFY0tHK0CfQUVdQxuXO7n9uMla1fB4WEZD1WbqMuxgU6jsySj67JP1J+baPq3x2jc82OmT3aVf3w42apGO9Ns8m8u9U8rI=
*/