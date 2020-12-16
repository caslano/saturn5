
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct bitand_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct bitand_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitand_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitand_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitand_2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitand_

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , bitand_2< N1,N2 >
        , bitand_<
              bitand_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitand_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitand_2
    : aux::msvc_eti_base< typename apply_wrap2<
          bitand_impl<
              typename bitand_tag<N1>::type
            , typename bitand_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitand_2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, bitand_)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct bitand_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 & n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct bitand_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::bitand_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* bitand.hpp
nt0xHPbGatgbM2FvrIa9MRMVN4bDeOyFvbEI9sZk2BujYG+shr3f59gbw2FvrmN7Yy/sjfmwNyaj7GNBjMfc2BsjYn9MT7dA5fUN3b1SzzSasHhX2s85H368to+9MTT2xnzYm8vaubEgUSa5NourSEGaOZTnyViQRdgaF2NvXIJ9cCmOxGWYhssxE1fgclyJhfnINVLcapBPg0rkg02wNfpgIDbFIGyOo9EXl2ML3IAtcTO2QvJhLItca5RrkEo+ynouyflpe5ZriLdjS7wDh6CfrL8DTsEuGItdcQl2w+3YHbOxBx7GAMzDP+EFDJQ4+uCP2B8bkfcAbIkDMQCDsR8OwqH4Z5yKd2IiDsFUHIoZGIrbcDgewBGYg2GYhyPxPRyHn+B4rELZJ2AwTsRonITTMBo34lS8D2MxC+PwEE7H6m6cE2BvnIlDMBFnYzIuQDNWUT4v0BPTsRHOwWY4F/0xA7vgPAzE+TgTF+JWXIQP42LcjZn4DC7Fl3AZnsHleAFXYDUP2hfWxruk3qtVkuuLct1R2f7N+PsGySRzjDfAS9gGL6Mffotd8QqOwu9xKl7FdPwBF+KPuBGv4Wb8CXfhdXwef8YzeAM/xF/wMv6K3+JveKsSHPHWwcrSPtywBXpgW6yCnbAa9sAaOABrYgTWwiSsjWl4K96Nnrge60h95JnkWiDeJvWhlP+k1Iev7N/tsB62x5Z4O/bFOzAc/XACdpV66Ybx2B2TMRDXYl/cg/0wG4PwJeyPH+AAPIfBeBFD8CcchPWV9o8NcQg2xqHYHEOxJQ5HuZ+rXNOz1Dnlsr2fa4yUKx5bYQL2whk4HGfiZEyU+GdhGibhPZiMBzAFz+BsfB9T8Qs044/Ie6TdyTU5uVanbXdsG0u7W48t8R7siA9gD9yBQfggDsKHMB6z8C58BDfgX/Fx/Bs+hXvwEj6B3+NT+Cvuw6rKvoC18QD2w4M4GA+hGQ/jQnwGV2EOPolH8Wl8Fl/F5zAfj+O3mItulPEFrIMvYgM8Ie2OfkC5noZuhfXRSflckOPwu3K8fx+98CNsin/HXngOB+AnOAH/gamYj/Pwn7gMP8P78XN8Hb/Ad/BL/Aq/RqUdXcIueBl747c4AAtwAn6HqXhF9qPvcRNex934M76AN6Q+fsV38Df8Cj0qUy9YBatS1qp4K1ZDb7wF/bA6dsMaGIq1MBxr4wy8FWdjHczEuvgQ1sMj6IXH0RvzsD5exAb4LTbGetR3E2yATdEHmyHbhf4uuUaGd8l+UxMTpZ2OlP1mtBwPxqAPjsWWOA7vwAjsjOMxACdif5yM43AKJmIkLsMoLLo3hCp/7XnAmsrkj+uxNd6DgbgBg3ATjsbNaMZ7cQluwWV4n5TT012uVck1LCUfZTl3uQh4f2WZIx5b4g4cgn/FUfg3nIk7MRUfx0W4C1fjbrwX9+BTuBcP4lP4OWajm7LfYU08iK3xELbHZzAEc3AsHkEzHsV9eAzfwufwEh7H2pQhF+vhC+iPL+JgPIHD8CWchy/jenwFN+BruAVfl/b0Bj6Np/AtfBNP49t4Ad/BKm7sp3grnkYvfA/98X3sjx/gFDyL9+NHuA//jofwHJ7Fj7EAP8EfMB+VbfQpNsZ/og+exwH4OU7EL3AWfomp+BUuxK9xC17EJ/AS7sdv8GX8Fk/jd/gdXsHr+D3+hj9gEw9+U4p++CPeiddwJV7He/Bn3I438CD+gjn4K76Av+HLyI8NM7/GSliZ7x2VsSq6Ywf0wEFYBSOwKsZhNdyCt+ABrI7PYg3MxVp4DmvjZbwVqyvfL3AQ1sXB6IXD0BtHYH2ciA1wOjZEMzbCJdgEt2FTrFyN82tsjL7YHFs=
*/