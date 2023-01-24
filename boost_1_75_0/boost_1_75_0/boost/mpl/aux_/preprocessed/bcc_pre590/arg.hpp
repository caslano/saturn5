
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
jXptAdk/E8fk4sJ9dPPsckt65IZhYnR7BCCUeN39uo1an9KjwGN8BjWLgRAPdNPd+pV98o3tUSoOrRGnDijztPWIkhjwoAfCfXueg3HRqOTvn5h7rHvIgvGX8MvQHTHF/+L9ly8ES6r0wFOZBx4zcjOhPOIvJEuYtmj36OgfGPLwZgiXCJZwbdFPccUxbFNvaBgDm9+KEtpiNmJ+D37xJ72LuLA2bDWUq5EOkxq3k+4bxgyRMJ63UZxI7HWUyBCqppiLsyZ3gSvd14Ye+P62Lj8jqju5P9SX1bxkR0dP7W5lKM+SserOBEnIVJXeyzF8NpDnLNavli3iNJCNLHOG3YqdxVlSkWvEgcTLTT1F3ScVln2necVKVsMXyfnfTdJKFmewTdDSKeu178MaVwPKhdm5NLof5N+ZElE1b5wwnm6DhmHbu5nzJGTUYub4On57tSCuFzHHB3lPOYfzJ2lWe6Ql7nQW/vxhFePr5f5nRdvp7UI1/XXJcXCGKtMFDWukjXyDr4dmdIaNsI9iS3Kev1YDQsMgN3BBXrR3wCp/y+7d1aO8HjBAp4+rUaZl1qbtJjx2L6+cqCP8e8z6VF25l22XKOBIULY1n7R5lZI/ey8jCl2TTtA3dv1YP50VeOwhvCPi0QeqS1gkCF+2YWwynwQ1Msvxe6STRJ5gVris1i1Irv/GVf60aJHsotlgmZmJhechbF4RAGDJp+3S
*/