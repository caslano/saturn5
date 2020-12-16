
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_right_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n >> s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_right_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_right.hpp
QuV99u+kQV6kKQcz599y1Bar41DHRV0tFbRQ6jgHw1jHiAB1HcvuInXscZ7vi5zAs3+3hUi9tbTtnpEyylkKh2cx5cqXiOO68GapK/nNx3yO249HN9f7YWJ/9bpx+7Zi8fnPM16M/fBGKWOylHGCtDuq7ccKrjKm7dGG40Rr2hv1sqSl8rmXoSfzHemlyld2rdadM+I3mb/1cz/38T25h8vfYLIfOZ+flG3dxX501Gk/anCxH9Wfez+S9oDzbzTZL13vX/xWkP3LuU49pX9T6nQSelOntf6qOrXvSq26Z+Ct3s77ktRfocvtz3UbSLWOrLaLOpd1c2rryD0G8jmc1S40OB9Lqr1c728etv1NaljZ3Vpx3cKF3N9s7VQpo17K6CW/nZpsvw/K8nLKSwtMy5SOhfOfp3X1+0C9fwdIp3e53D+yBLcqz5CItuRXYiBLc320bnvYNcy6PZy/T8dF3di+c9WfvXp7sAxpyXarer6C+RtAVd9Nki7bgG27UDIrVJYpbcZmCu3PfP9gOiGWcqu2RXOZpK7U/T27pb6i5fOJJG5jojbOen74p/c9qc+pe6jOa6u3k5geloWlye+jVOK9lKNJymE+R23ILjbkGJfp2vAb/40g9qUyE9P2+0jKSnMc7gnJctqGtvc4e5sdoRxXeqnLsqA0rw2/Zzkuu+wHi/eW/k45hiXjDtY7M16Vl/x+zSlp27pzHFG3b/gcpH3jvK2WGSqHx0Q51MFOb9f7bW2QulxlBcvbUAfO+2wz6jpcuGsFXD9zseVrCFw/s7Clc9gtX1twva+SXr8q95b7fb5+/GSP7L+8tPqZgRfumgPXz6q8+NcibPY0Lyd16/iTe4piasKPvPr5DxtCf37XKLT0TMptpUr667fWJ895rClg5jUdjv/6YFOflp896fqahpaeSXlhr2nI1Mk5DkiRa2g6YZrsSNvbcY4Z78MeuAP9cCf2xV0Yi/fjGHwAx+NvMBn34FcYQcyUfHpKPh0wWPI5znwdsB598D15XyKxWt4XJ+9TP3/FT87V+2M37I39sA/GImWU/OVcAvq4yD9L8s+W9cyR/NN1cm4Aq+V9HTFF3lco7yvCcViMk7AEZ6IRy3EJLsMyXIEmWf524hFZv2OyfE/cKMt/oT31jy+hP76MQfgKDsDDOBxfw9n4Os7FN3AhvomFeBRX4Vu4Gd/GbfguPobH8Y9Yj6/h+3gUP0DKSf7Sxy99/0o5Z/H6ACrhQynnX1GPjVLOz6WcX2AEfoVX4tc4HpsxBb+Rcn+Ly/AfuAK/w9vxDO7CH/AA/hOfw3/hi9i+A8+qxA74CbphI16GX+LleBmFvwL12BH7YWcciL/AZPTAReiJRvTCcuyOd6Met6E37kIf3Iu++Dr2xLexF76P/vgR9sZPsS9+iQHoTd0Foh8G4RAMxmgMwckYiqk4EA04CJdiOO7CwbgHh+CTGIXPYjS+iDF4GGPxPRyGJzEOv8R4/AaHYxc25BHohSOxPyZgDI7C0ZiIOTgG83EcFmMSXovjcQdOwN/gRHwYr8K3cDK+iyn4F5yOJ3EGfo9peAXb10zshLPQE2ejD6ZjT5yDg/FqjMG5mIbzcS5m4RLMxmsxB6sxF81jhreTcxNyziJdqXO5bkoJibI9J6Eex6MfTsABOBEjcDImYwrOxSmYib/EIkzFJTgdq3EGrsU0XIcz8U6chZsxHR/Cq/EAzpX9MgPfwXlYjwb8FjOxG2XOQj3mYQwuwBRciFNxEc7CQszAIpyPi3EpFuMKLMHb0Yi/xlLchWX4WzTh01iOdVghxwe+J+QchOXcRDoxUnVf/TKpz+Woxyqpz+swCKulXtfgGFyLE3C91Os=
*/