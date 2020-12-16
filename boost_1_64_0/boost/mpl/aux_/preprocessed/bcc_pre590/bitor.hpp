
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
N8Bd9tntEnPaZ7+VeKh99jvJcdpnvwfuss9GdgPmsM92AGbaZzuy3j2W0EliTvtsZ+Au+2wXC7Pts10lx2mf3QG4yz7bDZjLPrsjMNM+uxP00j4r0mVnqQ+1wXYHx2WD3UViThvsrsAdNljGd9Pw2gQfzBWvafLLVh5w00bbA/qWbLQ9wbFttALfHXiYHbYX8JbssHuAE2aH3VPiTjvsXgqu1h29Vb2MFnZzb2BhNto+wE0b7Y+gN220faEPs9H+GLjLRrsPMNNGu6/UO220/QLc7pf/RGLOfvl+Enf2y/cH7rLRHiAxrW98oNRbfeODJGb1jQ8GZtpo+0Nv2mgPgd600R4KvctGexgwl432cGAuG+0REnPaaI+UuNNG+1Pgpo12APQuG+1AC5PpMgiYy0Y7GJjLRjtEYk4b7VESd9pohwIPs9EOA+6y0Q53YahfRgALs9EeLXGnjfZnEnfaaEcCd9lojwEWZqM9FnhLNtrjwHHZaEcBc9lo84GZNtrR0LtstAXAXDbaQok5bbRFwE0b7RjoXTbascBcNtpxwFw22mJgLhvteGAuG+0EYC4bbQkwl412osScNtpSiTtttGXAXTbacok5bbSTgJs22groTRttJfSmjbYKepeNthqYaqOdDJ3LRnu8xJw22inAXTbaqcBMG+0J0Js22hOhV22006Bz2WhPAuay0Z4sMaeNNgrcZaM9BVi4jRbjizqParIx/O5aqXfabuuAu2y3MYk5bbdxC7dtt/UaR7bTDZYevRg8N13DOVk4PhLQm3Zbr1+l2lxPbYkHG+8Mi2PbiRtDOOSGWF8bhicTMdU/yZZ48E9KckJtzukWOOr7Zlo82+bcDI5pc85Ab9qcs1LvtDnngJs251nQu2zOs4H9kM15Dngum/NcYKrN+TRdF5T306E3+2rzoDdtzmfY+qDvd6aNBe6dBcy0Oc+H3mVzXuDEZJk5W+LOvu05wF0254UWpvf3zrVwOA38PIk7bc7nA3fZnBdJTOtXX2Drg7j9uYXJtLoQmGlzXgy9anO+SNPJdvdi6F0250uAuWzOSyTmtDlf6saDduUy4KrN+XJdF+TVpbo+CP8V0Js25yuhd9mcrwJm2pyXQe+yOf8CmMvmfLXEnDbnayxc1jvXAjNtztdBr9qcr4fOtDnfYOuDvLgcmMvmfCMw0+Z8E/Qum/PNwEyb8y3QmzbnW6F32ZxvA+ayOd8OzGVzXgHMZXO+w40FfeQ7gZs255VS77Q5rwLusjnfBcy0Od9t6pWw32NhMuyrLUyG/V5gLpvzfcBMm/P90Js25zXQmzbnB1S9Uu896Oub4zJZsrUZH39IxeF1gWPPcQNXsUcElqLvYVldoy77JTCvjvPj/FHoZL2H8UKhz4TZVx8PwaNsesSYITgu++kTEpP2U7z7SYk5baFPCTzrsqM+LbBZYTblXwN3fXs/48IqMZ7oYalBCVe8PgdMjdfnoZPxKtxZ6+kzpHfEyQvAXHHyG2B2nAj8RQ+fBdwR7nXAXeH+LTCXzeElFyaWQkW2kvQmOYkkr8OD67e9fs7MIbnMlK07XnHzEzMj7b/2X/vvf/TXmaQ+0qGH93/h0dNS6XhSLCsS/2Yaj6jNJRpjRww8cuCRA+qPmJUZNGDgsACbM3zoERk6JjweOyIWr801+Hhd89x0NjUt1tjYVJNIHpmq5XX5R0dG9oj0i0R2iOwe2SnyaE0kuE5M1DWnMqn6bL/+FYf0K0vTWszEaTRC268g1ZRONNKi166Rkh5H5nn7VeexX5d2EP6fS7ILSYZkPeFP3tUn0iHSobCxcSK92avbetIRws7f2T25Dt+5Rze6jqRnpyeSmWwhjeJB7z0=
*/