
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/bitand.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitand_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitand_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitand_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitand_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct bitand_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_
    : bitand_< bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct bitand_< N1,N2,N3,N4,na >

    : bitand_< bitand_< bitand_< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct bitand_< N1,N2,N3,na,na >

    : bitand_< bitand_< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct bitand_< N1,N2,na,na,na >
    : bitand_impl<
          typename bitand_tag<N1>::type
        , typename bitand_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , bitand_
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {
template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  & BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitand.hpp
bsL7cTOuxS1Ygi/ifizGw1iCR3ErHsdXMZi6vIYt8HWcgDsxFd/Al/BNfAvfwuO4C3/H3cgx7vM2TsY9GIPv4Ax8FxOwDBfge1iI7+Mm3I978QM8ih/ht3gAf8GDyL7r8wmOwE9xDH6GM/ALfASP4mb8Gqv780wTa+JxrI0nsSdW4Aj8Aefhj3gP/ozP4i94Bn/F83gWa9VgO+MV+DvK/RIHlMxv5+L3UpF1ORe/Q8qty7m4zw4MleWc3afJuWaALPe9LBeAUbLcXLkuZ+E1mI0tMAf74zy5fi3AY7gIj+PfUMoh/XG5l3NR/0Lrci7qX6Zeznn9OQHLcpXUP7qa9BeV/qMmknLdjpTj9U05b7yFwbgbe+HbOBr34HTcK+eLd2Vs9n/hCtyH/8T3cD3uxzfxI9yPB/BK5TqN1+An2Aw/xa54GHthOY7CzzEav8R4PIKJ+BXm4Nc4D7/BO/A43okn8CH8DgvwJD6DFfgc/oj78Vf8Ds/gefwNfWiTcxiEv2M3rFaNcqEf9kd/jMQa8nuwiBQh7U/fTtrV8nthrbT/U9KuG7ALbsRh+AzG47O4EItwFT6Pj+ALuBs34bu4Bb/DF/EHfAmrk18xNscSbIVbpR23YX/cgZH4Mo7AV2R/OOYjfTKxjuwPynX8kJQ7j//Vx8VyHVki15HbsS8uxRi8E2NxGT6Jy3Ej3oVv4d1S/nvwI8zHcnl/Xt4rhbgXG+B9OANXyvZ+QLb3g7gQV+FyXI134UP4FK7BI1iAF/BR9KNOhbb7cumniV0N7suHyXYajtfiSGyJUdgBx2BHjJb1nSaVyvoKZLtzP8/+JzFW1SzrO4bN8BvsgcexH36LE/AETsXvcDp+j4n4A96OP+I/8Cfcg6fwFP6C5/BXrKbsx3gV/oZBeFaeZ/yOnfE8jkOf6uSL1TAdq2Mm+uJt6IdLsAYuw8vwQayFq/FypP7sd9I/E9tL/UPM+7f8gUbqvxg74hLsiXdgf1yKQ/FOHIvLMBNXYA7ehffg3bgS78GnMB9fxnvlOc99+BPer+Sn7CdYF1dhI3xInu+sQe6n2FZyPagm/S6lP6aJZN7ecj78p5T/aWyNG3AwPoPj8Fl5PvUcxmMR3ovP43p8AZ/BTbgPt+CH+KJst2LZblulfNtwCG7HkbgDE/FlXISv4N+xFO/GV/EBfA2fxNfxBdyJZfgWnsVdGKbcl2BjfBt74h6ciHtxKr6DM/FdTMd/4XIswwdxH76I+/Fl/ADfwAO4Dz/G9/Gg/bwo/S2Vc7j+vNhKrret5blBG2yD7XEcdsQY7ISJ2BkzsQvmYldciN1wKXbHFdgDC7EXPo+9cRP2xZ04AMtwIB7CQfgZDpb9mgJLX0u+K/vF1cpxJ+WeIPvF9RiFMfI8cgoW41QsxWm4C6djGc7AT/AGaZ9YDCOTeAzHBGyCSdgKk7ENzsJOmIJdcDb2xjnYF9MxEjNwKJpwNM7FsZiNkzEHY3AezsD5uAQX4Aq8SfanRernnK3cm6umopV7c9UEtnY+V02or+p5uixX18Vy0W6uz+TmcvluLlfkZvnK3FyuQpYLc7FcYBv31hfRxr16RLu5PlMly/mr20+Wq+ViuUJr+VwsV+pmvuWyXJiL5Xzaure+8LbulW+Am+uLU62vyGG5ePUcTbb1OV8uxlf6S0g/ClN1yzPCKBm3b778HeAmbIyLsDnegr0xDyfjrTgDF+NiXIKr8A58BJfiOlyOO3AF7sa78HO8G7/De9CfwuRjbbwXQ/A+bIv3Y2dciT3xAeyND+JkXI234T9wKRZgAT6CT+CjuA4fw424DrfhBnwDN2I5PoOn8VlsSJs8J38/KMKZ+DzOwU1Kfrg=
*/