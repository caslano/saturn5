
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/divides.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct divides_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< divides_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< divides_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct divides_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct divides_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct divides_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct divides
    : divides< divides< divides< divides< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , divides
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct divides< N1,N2,N3,N4,na >

    : divides< divides< divides< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct divides< N1,N2,N3,na,na >

    : divides< divides< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct divides< N1,N2,na,na,na >
    : divides_impl<
          typename divides_tag<N1>::type
        , typename divides_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , divides
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, divides)

}}

namespace boost { namespace mpl {
template<>
struct divides_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  / BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* divides.hpp
p+v/Kd//6t5/lpzsVRe//t9A5uy/yx/xSnXOfqrVal+1TokgP73QpJ5/j/Mp4zjPLE0mJ6UWpDvPq20IQx1z+TXr9/WEl8Nu8H3CNwW72hDmTF9mmZaYpC7h58sagi3te4ax6pZh2rXh8q2Kl36+VlpuurQXaPZG08zVso7Vz3lkpq46F7W2r/1v+B9Jg3Zec7W0lbwr87jekX3RzP0M0ilbo11MWpXE5aXmGu+NJt9ipzB0H3Yt5/gZ1Q5XmpaSULJASYOarsH97ec/kHQ52oDi5Ls8VsovBtYr5d/fM11Mezxvenpo0mN12xNR8SsQP8WmdSF2mz50m/d7XGyyIe2RAtl/sCnE0yYm8vi05qFbPqvx9xtgj/8jiX+qxB8jCbxM4u+MfMw1FQM842cCX5TFmpFRQMW8EDt0dcxLvPu9xkukFxinI60Rl3rG2TAKW4zjtPDEUKfYXmxa93mJ95hxvBcVpyOtQT/wjHMf19V6iZMndIHaVHaB8TrS2ijxrpNnRyHyJ9JabxBvVkbxWPU5eQH7Q0p7kfb553xuoFfX/rMqO8+5lyC6lGNn22ezri2SNUcGyjPR7dmRI6+1fSQ/eyGnuaZ0oGe6mAh33jxsae3WMP7mZED39QHc4/+Lcr8Yx2/JTve9HO1ztozjj5f4yzt5xt+o1GGD+Au5X2VvSGbtZuZfSF12li/lx/2g+xvIMeWnf44Fy3z5rmJfAPK5Uu+M7LvIe7uHZr6f6NDdA/u92GIaZGDLRdzv57MjUQZUz5F7cYbci6FGdtgKxl7oO0tL9yJ67feitINScOp9tmqQ3Gdufw9PiM3JknfLkb8p95mbzepbYmp6epQP+ea4197BXvX10u3eminrB4yRsfmj4RfqIqEGcbIHb2v+DtW57bn7juy5q40/OEAa+6Wc1iNfKmkebBB/JvPgJf5iH9Ks2z9XyuGrUfIOKM8/xSabnN/M8Ssc01ytvnclkDdB2Kfk84OD9etiaOd6atNTLumJlDIcifwFnVFhnulp7boMddoy1K7FI/Pkh0mc4cjXo7jWIE71hUJ9Mp0/Xuc6BB3QpX4+ZKe7+vbEPzMndXWhvLtKGYuJumfUcbExUGzsipxVnuFebLQvceLb+hsG+eOc039GyQeNLm2+mbt62vQN1x/zYpOv9d/DHk2e/UO1Bz1utjQTufu6499ybb1XW3hgXaQt5xRbRE9vKb9/iZ982OjKsLKbu40wkvwb4sXG9Az14/ZCy7Cf2GkiDqvokuVknPa205xzL9+EQE97f8D1sd7tLci+IaMtbFX0iKmue6OD65wuX88FGuer1ZudGXltl6/o8pqvci4zT5+vm7t73jeduH6/F3tV3Rdoaw+traJH9+zr4Zl3l3HtMS+2yLvZBdmiyze7Ho8y7uw6pyvjei92Nnmzk8VrUnNXZ/jyTXJeW0WXw9reWls18WjztayncZ0MDfdib2H26gu1tbfWVvQ47OyhrYuiX5un0UGeNnbjWnNLNvLSdrH3TYDDHnS53zeXa865P49OGdjbg+tLvdl7A8+KzBsvylY1T+16POpqoOuc7ntnXy/jsq9u2U5LAftE8POC7A0zsFf0Oe3up60PbnFq60VCb0/7exGmvmX7KbE2qBeiS2qGs1701J3Tv4M3iL2zkMtlbm5vrg8camAvH7it+U6R71td26q8sjnb67Rp0eajrY/nt1ywkg4juwov/p3NYeOD+Ikq7f1D5J729MOeCkN72uZ9bT9+okZnS2WwZ5tAiHKPGNrSNu9rL+Anapz16iX8tO3Q2vIz9/W0cSA21hra2Hbva/fhJ6o8njkHXOf0778GtoZia5OhrRf3rtZbY6fmVc0=
*/