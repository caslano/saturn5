
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
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
VDWxJ5uv8pjLC14drGUvS4fUFEP7XsT4uC3ruLQvbDX3Mc0mJW9uqn+Am4a8vMIqM16Ksbmku9cHJyBekS43is6XaxQmc9mDcf87BGzrR64nuArGg986lV2r3TT71qsVfM1JI9EuRXrejg2p0HgY6mm0FnrUM4inQjNVqm44R3oUhLZajUWp4SLYlpwBXVFKGvJpiflpvLI6ZrBIgyGCe4nhCuKrh8mjcIXT3ATonu+F2gYg+aklfp0Cf7i5dwJgQfLld7zwFkLL8MDyR2nnYhup6lzntTZWsBJiryDSrkIQfl4IjijqTXswK8l9rL2yj51a27Tw23GTgWemjUaOaMSQ/8uq12+nmDG/Plb/qBnzX/OIc6m6uMeQ1VP3wVKDZEMvAvrUVPKy1wB+OEwFTY4RK9phHMFIEHQWbnLExIGzbCWyiKYVoiE5EJlVLsuV/D/LV78XqsmvXzT7PbL6tGojoagvCGPP7jXjKQ/AylTsB5qqrTco71a7TW+/Cd6T+XiOkuVxbupNgbBJwEaP4TJP8nwk2cRXhauJ3K54vko7GJPEa9EMrqftEQ==
*/