
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
ym35jzvWdKgseojMvJ78gcfC583asLCyUPPmUYjBvz303jP3C7moLKExdIJlKS5SORRjRveYc/+FkPVlqW3kb6ByzIAvmfUBG9vLEfTcsprGKkunKMsyodQZg668sLzIHkvwxeRAW/mDbRP+fHWJInZQrT4fJx9pMw5LoXybGf+Cjd3WagTXSffkM51VmM90ZRv3WFyZmzRvLK59JS+lbbhf1498KHWTh3dj0zESHTK5l5z+jVd2jOzfOKute1ywyk3Wb1yw+rpI2iC87l8xvqWSL/9GHrL0jLEjR2fEWv8vOv1LFdMvvMyvGv/SCDJjLfeLUfhOF6iTeF395Cvmb+NXaulQ4ZvkKzneZx5K62mMZU1GaN/Cb0xoP6nfoeifRXMvpVjfBVeJxn36msWnz913L5Kv33/Xp++YpMD9Uzu1248JX91//4Anb9tkwEc3t4xPX1qC3i/13plGMrbu/uYLxUMJ7OUk352R8tnIgN3haPk6HQIHypfjADhWPk7j4CTtQ3qxfDqugtnat/QIxYc6Cr4tH45VioeSkGDtR9pN+5FuDycYedqPdBT0w3GwHPphBTwRTpFv3lQ4C54Ib4UnwQXwZPgKPAW+Ck+Vr97p8HN4BlwNz4StW1k+WlvBc+Au8FzYC54X9IHSux5ldfH1Wah6XCRfrVdhD8UxGqY4RqMVx2iM4hjJxqT3LurOxca0pfLtBjuG7H/bG6bCEXBb+dB011zi9rAS7gCvhDvKZ3InxfPqAV+CO8OlcBdTL3BX+BvsKV/KXkYe7AMHwH3hPnA/mGH0lS/lEKs8lE/vX3CmyrNFIB6UdVyk8lTCbvLF20k+eL0Up+wgxSnLki/pSfBa3V+zVI7r4KPyMV2oeGRL5Gv6peKRJSdYPqdbwpvhXvAWeCi8FZYoLtk5ikt2geKSXQLvgjPgHLstaZOgTWeqJ3LcpFKd17mJ8yqjPK/KJveOkPPG2s6rDuYX8bxSj36LzT3p4hNwr9qnCo6Ub+3B8GHNVT+ifYsfVdy4x3SfPQnnKi7YC/BZ+eYuMN8H9g9uei479fTo56+HZ8RjHLXknHWs89XRzFFHuydwVPsBr4e4RrHOQ7ePYf/ftYllFI9jtG5xjFa9Dz9AD9J40nmkO0jVpBWkLkvRdWl8rjZ+xI/4ET/iR/yIH/EjfsSPf8rRmuRrAft/cU6p3/IAWDcfgO7sBTGYCb0V2WYfyszRo0YOO9x78JDMTGLqsS/dZG95uWdHztmccwYeHn7OWG9heX6xOcuKD3BzkqfBjjs1IXwfsDqzD1hCwNYSllE0+1ab2ATd0WVUQJeiktycIi502sKXS659L9M9OjGX28ZFbpP7IjltPHugf47HKW98K/dyZrrJQ9to9nOuL2dKI+WcL7kdJdd8+QbXTHOVy5Y0Uci128qq5VPwquryadLrplytA/kX9p3iDWlDK/8qR7aRYxp2UJ2e2jE0hqFiHmhPkCTZVo1RrqiQ7c31/VHk8ybl5TEwPgXW3iN8n8X3b/F94CFR22WH7PuVyWfaMnBOfX5znfn1DbXZprV2t1fPbtO89up6efNbu9uI57dZvzbioZLfo034fb3Y7HXfID/8FqPcRUVRlNtuF57l4gewxNhkI8iJtW7fkV3YXraeLvb3983+Pm3dZa6NP8BbIfsd7enY78hZB1Uu+iw1/jsR9WHHo7XQRe1NPxa+51F/F/v8R8ZfJYIOsd5z70Rhnx/VTmvI5TPzI1xp9m20fjOm9C1073O6SGIkP7SrEoN+aI31O4qd2mCzD/Unq3XpW5a77P0f7FvkPxb0g9G+SQ7fmEDftanNvwiRsvFT9haw8WcFYmtuWt3+vGO3+2Q=
*/