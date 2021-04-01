
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater_equal, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
ALkwSy5Q3xVDxh3N146x3RFykf3aBvq4fHvjH4/1bYZelw4KMr/vUIGqMKeJKjCqwdHzvjHKpZu++5kl65txc2h/PY1PEg6Icqiyy1CCAcgBB0vC6AG1WnRB0l1I42ubi8uyIIpPaIAua3nwxG7oPzb0b7gZSuRGiHRqoQo9QQ0LRuyTqbLs0d1TOEITC6xlGOEPK3d4TZ6v3SgRhnUywtc67f4CWRDnbdTLsvtjvflGlC8MoFyTC3GpLrAtv4qU5numxFMZto/NUt7H/zYKgsRpe2LM/dqtsWZY7Ssw6zfYHa/XtVCtnEMMxw69+VyyMPT1bhvXungbPJypBe+YW2GUY9kp8hxFevJUPtU1zK1mzIGb6ERtJPGH/n50x6HR9tQopFey/pbG0IlJx92OXGu1rCEKPcaN6eYi297EW1uGQhNflz0h49oozgSpYSTI/IavZDX5ypDw7TDTT3y0k9AFQeyXxAK/RZlBhOUHp3A8q0Kkcl41ieGAHIXoj6I7PN6mm2IgE7wynsqdMtXs7dngv33QdIOtOZGRcw3j2y5HNtF0MnBok/lAVQ==
*/