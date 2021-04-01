
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
ZRa+DKbT29tGurO6BuG+Kx0qWdNt9wTcL5wjZQBdAkTKeOvlHPBAiQLK7v5QwSPsksRXFwPW5TzV/I4HMqT4IGGfM7dk/36SlIZvTOOtEqQ/wxY6u0Vc3FhJyz8wueBcc4hnuN3WhzeVdm6KCWmfmUW/9YCKDA4Kw1PGfFfeKZL917lMQ/tJNH3MBr0EaHLIIfGaosn7KfboVj/jdJLGjIyvc7CN9bSoxJwd/xQLTBPPqP5L7dJBE9KHGJdp54EK0CseurBB/8sgeSkUUBRx4/vyPu5biZwonwBh45zTKFL5s7ZjE3MUM3ATvrzZLIoxJ/VjahcCWrGUqM8EK3iTbx2dnZQt96hytw+Fz+e7+HSw7POT8O93GgrEdU/g9Ev5D+sG/FD0DOF7vm7cvLNmgcZ2ottbWbZGQYe34vs6Cy6+iGv1sWQPlaMgxo1X+XYdlcNQ1JmQWqO95eJbj70FoH6857WkDidJSzqOW0hhasdg5My7DZ6U2dlvJskQPW7gnjEB8ie+/Qrz9301bCYiJVlcNOCvPbOCAZzIgchvImM7abKuvA1TbK1Emg==
*/