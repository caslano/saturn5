
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater

    : greater_impl<
          typename greater_tag<N1>::type
        , typename greater_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, greater, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater)

}}

namespace boost { namespace mpl {

template<>
struct greater_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value > BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater.hpp
RTOEQ7z5y0BpCBf3TdfnmsVQfvPOKuKjpl55ueXGn5TCsxNxknqg5wZvzJTw188omWsQE5fxBs3rB++qocnyZ74bzxyOZIOUQ5LqEFf45tQ9kMkFnRCycXpxktfeFbKqMKNX5sy6MKsYAhttz4cU4PUlhYQSpicllDi+OevgD9+cCGZ64D92DNsEtCXTf23m5izygAr9kork7LmC41hfe+SFKnNCEsWFrXffQrrRuq1fUfGYTN/BZvSUlxS3M4o1/4CkCh2/MN1j4evIN8dJbO34xkzGPqq/Lqifg1K/JGpvS27eNdpHB3vscJNV/bYdLTjn4CuI9u2CggZzNQueJ1rLL7gXDKoQeE1HJX6dYI2nKISZM/SuEsaI/kNEI2z+JIKXgm11vFdf2VN9WSK8x9NifHra4uYlGUj1DiQfHmXM2qIKMv1V4VLWPi1AZRTUR/aMxz74OTqD9hQftuzvM1LJ9oB+eL+gGJs7r+r45I4xF72DhK5wcjHEel7IuC7tqVV45z99UobGjfQQLxT6m7JzIdEmyiaXLwXYB1QPNF/HlyfoOcOaGeDxTga/nEPzrZMEzjzpyfmk0euE1M4r5evRHCn6qw/ReCfsT8oUVQZxZBLqOyuYTDK9/a/0CY6JQ3N6y0cIRU1mZQsSchywJlhlMvVScTIHKgTnSpKFwXM29cHtJ2K1CDrWPOqFjrLuJzWUKqYukmM5UmsS
*/