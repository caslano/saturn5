
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
          typename U1, typename U2, typename U3, typename U4, typename U5
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
c21YaTsc5qsFa52YzEDJcSClcBQpq8cljOVXbepYy4keoi3ndlvVaoe9ithCEWVLMSLdpmD19/DTXlyyAUo7sXF6D20IQ7fOqPwRObIlOyw6WeU3Kx+NGmu8C5bUvnH9PXxs2SP/TygYaac5RQadsbYSzs22hsYlatY/tbnVMke1ofdUrlCNaaKHl3wDxHyVoKvRGRu1vllePKHM1ZojwQl2TQsFug3myHDzQjVIq26gWdDXTdQ0QEuvl6bnufNrPqxb3prSiqL2cr/VQqvNq+kRU2qKZIp2c06586EesknbeTbVLfZRggN+IahjuHjQvgla5KU8m6yxqqtki/9F2fowOxjWxodRm4802e4Io2AiIId/WlyPV9BCUuGTXnhkDR0TwnJAJgwgD3m3tNdVQ4XN+QKGr3WKkuX8be2Y2IZEmrN4h6owk3RenDYoGpKxNY4lYNyfWmDU7MiaIuq4BkRDl1uL3+J4iKtf9mu5iNtQRu3iBptu4IqwCnsVb5GlNW7Tq/Q6+qObkbYeYbEtN23B9C37tyDt87lslI+9w3HQBSpCcawwo5+WqY6Ov1nrmXqToOUjm1p528ex7CNG2lUoy5WhQxUbWTFxohCO8Ryl0wiBw9lSME77fo3O7iTmlhQCRVXInttNtTN2u+mzFVolsnVcjNjK3YhGtrgOCi+Vk+X6BRQGPHpgSIF86MYNXDK9+PiKrsVdbi6J
*/