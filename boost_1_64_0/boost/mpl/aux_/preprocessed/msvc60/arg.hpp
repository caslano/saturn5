
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value  = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value  = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U2 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value  = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U3 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value  = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U4 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value  = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U5 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int, arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

/* arg.hpp
qqjL66Qur9RlvlmsXsT0kNbGe+3Zqu5NODZoKHfs4zXS/816KefyFfpxY+TzT8p0fERKrF7nO5SPq3Sdha26/zaeJWReicybIetoq2pHSYmIU/6rwn0hiiwr72uPMrHqFzuzthTTJqr1PibjDCrVvY2q7s3GGbDNqt3HTN+TddLvX8KKt8ZzuI51z6p23WX3kv0rruoyLKUMfKcHGOrbnk9U9rXlv5fta5dePnspn/m+JdegSLmr39d2sT4J9rxfmHF6ndm+t8Vs39tQxb63RtqGyva9HWb7XmYV+57yXpuq2Ncy1PuavN922dd8h2rXwlzJbUabDG1GFo/vzw55bKrb4HzXYxOHHU78Z9uM3C3kNxBd5L4RlljWDp4ufdn3YEdcaerjld8d+T3KNOvjXS1tMg+hHa7BtvgIdpK+WFfpi+2J6/FG6ZMdJn2yfvg0BuAWvAmfwVC5J6Een8VYzMA78Tnp287EzfiiXJvyktyPYhsewu3SJ/yKXGPzqvQF78QL+DpayT0MbfENdMbdMhYgC4fgXhyB2RiGOajHfbgYD+ByfAsfwUO4Ho/gVnwbt+FRZf3wHdyDubgfj2MT6jQPbfA97InvYx/pux0lfbcB0nebgCelT/gUzsUzmI6f40b8Ap/BLzEbz+IZPIfn8Dw6sF2/xU74HXbFYuyLP+IY/BkD8BeU/Ynfuer3JyfZn9rJ/tReXufHZ2bJ60pkfxrB34Nkf3JhudbS5tgeXfE67Io9sIeMheiJXuiO3uiBvnLNVBB6yrVNfXEaDkKdjHGIQ29MxsEy1mAILkEfueZpKK43u5/IPmlL/Az98FcchX/gGGxIWfyxGY7F1hiInXAc9sPxOAiDcDQGy/40EXVybdRsDMGV0qb4gLQpPo6huAWnytiDaZiDYTL2IBxP4XS8gJFoKfdabYd6HIhR6IPRmIgzcC3G4Cs4E49iLB7HeNlvErAUE/EquefqCExFP5yF43A2JuAcTMK5eDvOwztwPm7ABfiy3Ht1Fy7E3bgI9+Ft+BEuxS9xOZ7DFRiiuvZr9TdWtbr+q5p7j/6nrwOjn/+KuBYsY2f9Xw+Wwf6TR7b61srC9dv/R7tj/cT/yQl1Ef8rcX6O6nl/IRLnh5Gbypj19fx42BSXx8jJjF5mdo3vxRdvw3EzqbyPui0daWnYTDWuOzEqSvqNK/czj2fNkmIrjK1nQp5jJ+s5h7yB9Vxltp5hUUk1Xs+n7Dh+X8Z6GsppUb8xRtXnuFrsUdexx/uG2CP2tRemeQTHBHa/s9fPpyLWDa4u9qjbGCPEQr5/8r08qLr3nXqca2dsJed4vaRfuY/0K/ujK4ZgVxlH203OHcPJq+T958v7N8Zgef8W8v6tsDPaY3/pB78R2+B46Q+fIf3hqeiEc7Cddj15jc4jroRziPo+f9jAOcOO/8l5g5a0pCUt/cnencBHTeUBHC+0IKdcpVwFC5S7SAsFClYocghSoEARELAHHdrSa+gBRUHLIYfcggiCUhUFFaVyX64oVQERi4uKiGvRilVRK7CAisv+MvOfaSaT6UVh3d3J5/P8kpiX9/LyJp0k/3lxTs7JOf33Trfm+p9fL8eUz/v/DlPTbvLb7lS5/l+BNcVLym+7fzVdV5vGxLM+JU+IKsG1dQ3TdvMukF81f8Y6X6nOZvO/vYOH9rBei8vvd23G0ZNi1c+UWYe3Csg1t2UfLsk+JMq9gcmk5xpznXPatA9G5fV3ShNOjDdEJKYZS/wOg6cby3NMud6/TLskKws05a+RexOXpfwLpA3k9fpcU36ScXpp7qMo5UelpJrvT8h8SvJEc3tIfVKkPuo6RunUcbnscDbWFPeyvcxvNXU=
*/