
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitor_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_
    : bitor_< bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitor_< N1,N2,N3,N4,na >

    : bitor_< bitor_< bitor_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitor_< N1,N2,N3,na,na >

    : bitor_< bitor_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitor_< N1,N2,na,na,na >
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitor_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitor_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 | n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitor_wknd<
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

/* bitor.hpp
G/EybkKtf+U66Vds4zzhLM9NN8BG2NC4nrRTrjbWuyrr/aQ+f2dYL/sO652X9b6R9S4Y1suV9VxsrPeDrHcJG+KPst5RO/mNFD+S9ergPlnvmvQLvo6OeBPr4y1sjKxIuQN6YTkMRnscipVwLFbGCXg/pmMVzEQHXIpVcTnWxk3oiC9gHXwJ6+JOrIf7sT6eQGf8ABvgVUwluC2wfFffAxgj+/OonNez+a8WPib7MRPdcBb2wtk4AudgAj6O0/AJXIA5uAGfRHkuRn4Lpe7IcWN8LmYRy9njYmyIS7AZLsXuuAz74nKMwBUYjytxDq7C5/FpfAufwbO4Gq/jGqyr1HMMwGcxCNfjNHwOH8XncQFuxLW4CZ/DzWh+Hlp+R0UPyT/j89AZkn+Zkn+TJP8mS/5loTzHK7+JkseyHeNzvB9JvTqJjvgJ1sNP0R1PoRd+jl3wDA7FsxiC+Tgav8KJ+DWm4zc4FS/iDPxO6+8tv2HiQzaOjwLZryv4ILKO1Cf57REn26hPkbJeFFbDaKyLMeiKcVK+8TgIE3AMJmISjsNUTMJMnKDVJ/ndEQfZqE/bJP/+LvmXi21wO7rhDonvFcmnnZiFuyRfXsXV+Bqux334Ab6BH+KbmI8HsBjfRiUxh7ADHkZ3PIL+eBT74XEMxHe156zk90RMkvwz9ntvLOelJtgaXdEdm2N/bIEDsSWOw1aoPWcl23W0UZ7tZbsdsBa6yXoBLLdf1vtI8rU5//ZD5eMr7VtndMQuWB97YAfsib7YG/thHxyOATgW+2McDsAkDMKpOBCzcRDm4BBchkPxeRyGOzAE9+JwfAPH4Oc4FvMxHO+T5yUrYiQ2xihsjtHYD2OwP8ZiDMZhHMbjLEzAOZiIa3EcPovj8SWcgDsxGfdjCp7AVPwAJ0p+kpHyWx3fjyQ/G8gzQ8rnRcnPrZKff5f8fBl9MBd74g4MwFdwBO7EMNyF0bgXU/BVfARfw6fwdVyK+3A5vom78C3cg/vxfTyAefg2fosH8Ts8hMV4GO2U+oxV8CjWxHfxITyBTfE97IDvowd+oNYrO/n9Dv1svPvYV57D6Iy1sAs2Rj90w67YGbvhVUwg5Mn2UmV7VTBMttdHttcXG2A/2V4AdsH+2B0DcRQOwDEYhIk4CJNxMMp5n9/bSj7vu0t8HpL+jhKfp6TfS7aTaye/neH3sp3auFG2M0e+Hz2OjpiDLfFJ7IXzMBAXYDQuxEdwMc7EpZiDy/BZXI4bcAW+jKtwFz6NJ/AZfB9X4xlci+dwPV7ADSjneX4DK/k831j2vwlWw6ZYF13RFZtLfrfAQdhS8rsVJmFrTMW2mInttOc35fcvPC3xGp+zi5X8ipP8ikcXTJByHoc9cYKUczI+jCkSbyrOwok4B9NwBaZLfmXgdszEt3GS5Ntk/Ain4ic4zVBPIiS9zWzUk5GST6GS7lHYEEdjU3wYpV2Q35tYxka78ImcNz7DFngaA/FzHIRnMBi/wOH4JXKOUJ5ruuvzTDy/ZHxuyfDO43/v+47/zHcd237P8V/zjmPj+43l3ca3vdPYbfi9vcf4977DmGdR/rJ3F28J5LkNQgHBcQDPZRAiCDmEXMJFglMQz3oQkghrCCcIhQTXgTwjQsggrCecINwguA7iPcWE+YSdhAKC6+CyZzvKPmWfsk/Zp+zzn/nYE+L+4v7/KdEZSvf/P9z3f5qh77+b3HdRxrCqitFYTek/km3rXiYp8DDdaSxVP/yjs37//WNlzOOozDjtfmYmQX2vnVPJfbwtxvtWXhWFVv1NrPrOZyVq75shDum7Q0yGMZ2XdWB+Sho/LVn1s5dlzlv1VVHmnZLtMWCvsjXTfde4WRY=
*/