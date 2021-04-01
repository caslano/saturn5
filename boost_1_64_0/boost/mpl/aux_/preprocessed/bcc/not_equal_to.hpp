
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, not_equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
AkfdZ0crHbDpysNifHo70Dh/XTjOFqhCUS1qNgZnJKR2+k7+/9e8T17pj25uwygpn6ETVra37Ghkx143LBk9xoDWQz53NtJQ+docv3knm/iuxiiNztI4DoV64MD69Sd45lutk+S7HSzFLryW8drc1jveqjhElk87VJHoy6wrjsk2ciUzs1k1Z2c69MxkNWwGPnZWgX7iy4bsUQUl/g9ol45iUd2PKFRLef5ANWf+r3r/7/L5TvPXH1BmYb31Z2gFjcCo/YT4fK6DOTFPhvsxtwYZFOrLngheI9rTiNlNO94X5jkGbpapR82MUDetHLytQKUIuAeVcmOrk1FnQwmkW4oIwc/HT5RDk32VgerFjiQ4zVFmzZlXIJSkqxCvbvy19wIEIhJp+gY99AgBTkKB6JasTA4+LdugQoSX3mzIpxVhYDPeko9O26hl0zzt0aV45lxdP/s/YkQqJkc36bzR2CdlrqsJJSR9znDBJHmi6gE/56MDwl4lEKfhRQ7Wdui/rueUTyAu2RA+OeVVH504aGBvf2QB4jUTcr9PANkr6nM2dmoLjfjX/0Vp3A==
*/