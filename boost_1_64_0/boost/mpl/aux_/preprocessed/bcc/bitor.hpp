
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "bitor.hpp" header
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
sh1loT6/jWE2nec0TcJs4nPMvh+QTVwVHxZa1QhUzR+gFRUpFWsVP5odbsdRlaEofEco8YXGe0ie1KKqedSSU0TANlb02iB0koaSldfazqQuiLLQ+J4yvgM4gCOYyCEAEvn0hWY2FCAuceAQrX6t0sC7QI4CZRqqf18IDoROQwTa/O/cDSyMu6lNn6IAfexMIorIMcdkN7E5NLtFLFlTVrZF8aiTFNmMQQ4mo9hoI9MCiYG0wIncasPwzkFzI5rQcLHUKTlj4mkYQycfcB47MYJ+GzFuE5EoXTooXcln8M7Zaj6GmMq0amXVw6LKUQhIxg4+ZAMwDBE5T31UA56R6ywgDpezbrDsBQPeXFScZTI78Y+1oFkms/i9LEMWbXblcwRGU4Fys7SSRxtRac5JCpt9SGyi1D+iBKg2fpIjZYDEkwMkW/Iz2Bl4kV/iGcHU8qbkWKYRR2M/mPyxmAWWV+RSJXM4pqMMma88izRZ88f6mp+D/+p+Pn3fTKcTd2ar8izrltRcgkn4wb4DyHhSrUpljabEnk2+2FtJlZxsolo42bA6RKqtN5QkuNL5c2zWjbbJ5wmaPYk0xyDkw4whhv+JhixFN0k6vJLF2gs9DSWPA5KnFJ4uWReDE95S8S9Bl667XxePpxBdMH6P0aXhNLcwnfJCvaD75Ee/UTx+Et/HJ8OntCDwAqdduiztUu/14d04PXx42OHHflq5m9Nr1xZca2E5+QunCxZ0W5CwocVxTnfv/nj3y5m5zTh1cXF38ajn2pDTpKROSZF5zzXmtF+/C/1e/c68jtMXX9z44nj30b9zevas5exn773txekPP9z64Zf6PzbhdPr0n6Z/X3jzSU4tlg2W9FOfBXK6cuVjK+9+PyyX05SUMSmvNNh8h9OMjGczuv9aGsvpnj3H9iyaaurL6bp1Y9dtO3lff06XL3dd7r7UZTGnmza9uWlKywfPcurlFeiVMdjHzOmjj9549PfFf5/Lad++5/u+cemRQk7bt3e0v5Yz8AdOKypeqkiN/XQnpx999OhHf9+2sxOn+/f32f/wt0+v57R37929c5+cEMXpyJFBIzP/8mQPTn/77fPfNnW69BCn998fcf/sVq99wGnLlmktt0T0fI/TadP2TXv+ze+ucdq//8X+L3yTt4rTL77Y+cWjYz96jtPnnx/+/NK/dmnBaWXl3yrPtf61C6cjRvQd8cjjawROP/446ePnnng5mtNx42aO+7lryUZOjx51O1r/2IrTnPbosbnHmGUpMzj19PT3TO7s/QCn27f/tv1S0uPJnBYXv1Oc0/aho5xOnrx98uMff+jN6bx5vedN2Nr6r5y+996p92bZJw3m9KGHch46G/rOCk71+nB9YbJQxOnt2z/evuX2QwNOjx9vdLxV6ZJPOR069M7Qbw/POMdpvXre9fybefbidNKkWZM6fnmqgNOrV9+6ak/94ClOu3df373ru4munEZEtIkIHjfbzumSJa2WBDzb6CVOX3rpxZdGu6T+ndOZM7+aeXrNzzs4feKJvCcu/tI/ntMLF2IvLH/+1bGc/vLL8V+WBH5j5fS7757/rsuUfSc5nTHj2xlHVt55l9OJE+dNbH3lxBROP/009dMXl7/0KKetW09ovXtk79c5jY11iXUdvjyG0+eei3xu7sVObTk9dqzpsQ6HFp3ntFevXb3yn35gHKfvv3/4/ZXTs3pz2qCBb4Owdk2Gcfrqq8tfdekSu43TBx7If+DrPrtKOJ0zp98c8xvtvuc0JOREyLzfJ77JaVbWyqxhNw9P4NTV1cNV7+nenNNXXln1yoCw+NWcTpny1ymvb7n8GadlZQ3KmpxedpjTNm2MbcpmBp8=
*/