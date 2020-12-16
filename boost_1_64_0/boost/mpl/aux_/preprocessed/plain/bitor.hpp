
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
template<>
struct bitor_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* bitor.hpp
SDtT2p+xzKMpUow6ZMl1ScvQF7MxEHNwIOZp14VJ+xEzZT7G/Joect62Nw7GPjgJ++Ji7IdLsD+m4kBciiGoXccl8x8j8zdex7VRzluWYCe8HoPxBuyLN+JI3CT13W+Rdpa0v5if+vd+r8yvXOb3CgbgaxiIr2Mw/gWt+AaOwgM4Dt/E+fgW5mAF5uO7eCO+h7fg+/gIfoCP4sf4IX6C3+EhPIaf4Sn8HM+jnl9gKzyMbbAKJb9K2lVsE1k/xvyqy2R5FmIXXIQ9MR7H4GIXzzGahUtwDqbiAlyKmZiGyzAdZftI24rXLrbPufIcsPPQF32wC/piCJ6PE9FPe06OtKGwvczP+Jyc1jK/NngBtsW22E57vpi0c/B8md543dyFMr0/+mALbTpps2AzdbqGPc9si0XaHficTGd8jlS1rP+/YzB+h32wBsfhMZyIJzAeT2Iqfo+r8Qdcg//C2/EnvAN/xnvxF3wQLdTnKQV8Gs9B2T+kzcEHXewfU6R+URiAl2JHnIoDMBqtOB0n4wycgrMwDmdjMsZiAc7FQpyHxzHLIm0C/JOU3wwTpfx8Kb8Au2Mh9sWrMBxX4nhcjQvwalyMa/BKLMaVuA434XqU7Wn7/Q7tXGzP8XJ8m4BtcKLxOXMyXYSL/XmE1HckdsFR2BNHYxiG4xgcK/OrsMhvazwt82uL5TK/rTK/O7AV3okdcDt2wR0y/3twEN6HU3EnxuD9OBsfxCzchWvxYSzBMrwRH8NbcDfei0/gQ7gHX8Gn8TV8Ft/E5/EgvoAncR+ewheNeRav6t+zGsKYxzDCmGchn2tRz+dq5HOt6/4cvysb9rmQuj4neRZhwznHTBQRZUQVETCC899ELrGLMOZgVBJ67oUx58Ik12Kknm9RTVSM1PMtKnkdjouIE7wuRJ8w/o0IJxY45VqkhRlzLVzlVeg5Fe+hZRR1NORVWHm9U3IqYpR/w0TMJaJ4XYL2vIp9hJ5XoeVUsKOzHvAjq5fFf7RjbsV4IobIJySvQsup2DJaz6nYP5r3+BGeInyUnAnCLJeiBBdhFMeRHWO0XAotj2IB4/1iWM9jGEfYcymOUsdK3geGs84JKzFe8ioKw/X7gJWEO+ZX7NJyLBzzKmqU+YylzBjHfIrAsa5zKkIZH0kYcytix+q5FcVjkbobcyy2MM45x6JG8iwkx0LNr4jCFMLKuPFELJFG1JVjsY3XZcp7otKQb3GC1+RbkGuh51jsI5xzKxZgFnE61pZPsZ7XW4idxB7CyrijlPVRBJ+dq+dSHI3QcylORdhyKUpZ7jLiEOHD8bEfEUWkEOuJncQBoorw47gQQsQSRcQOopyoJCx8xwNf8+RZeAbP4Bk8w//j8Duc/6dP+7ef/+/Avf9uUhKg2yltES61407ZcUqHam6OpRP/1ieI9nl7w79lJ8XnZGbkWBiU3IHg1hbt/GNkE/3cgRcxlhjNv5facgcmzJhh67+3zYlq5NR/rkL6NrnmyqzPzawvy6wP0/17czdWH5e7fYPu9m2a9bW+r/bd9appHdii9729JuZn/Fi6ofk1Zn195n2J0hZle+pt0VCnexhNNTzruxPOwP44E8NwNo7FORhC+QcqeIZjhW+D2zO0ZZxzxp3zxWm76O2WHVhO6G0U8/aJnu9ta48EE1HEDpN2x37C2NaIIfT2hda2oF1Rd1uCdoRz+4G2g9ZmkLxrp5xr8/aAtAUallddO6fa6be+4+98+Y3fsLzphvx+13+767/V9d/p2m909fe5z9ue39SewTN4Bs/gGTyDZ/AMnuGPOfwO7f/FQ62/vf2vtOF7GO7pv1Pa8E2wOf5M3KzksT6t57HqOZSS0Gip/95hrvI=
*/