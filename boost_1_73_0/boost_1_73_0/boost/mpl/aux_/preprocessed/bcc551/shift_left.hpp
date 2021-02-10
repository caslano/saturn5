
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
lhX2UkLfF98gOBYuhwPFeOenRlrrGwNFDS/rJ8rhfRIIpatK1ruYhXsYePyI80zrrTQRLbp9HS6STTpbrqKhLzFbJeuUT6aTAXH4SKbrWUen8BVNkZ3AiweZOTTgcgQ/XsilhS1iDQOba0cgbRdLEI3RTitdxswL8CXgfTwBW2jrIvgPlYDd0uy1Kf7KfgD9h3ir5u3v6scpqR5zVb212+PNTcBeqCHh7Z6I0qAOpuTD1/v1Zpk8E4pS2JD5ml8HLCBBFzqCf3Dkly/6D1BLAwQKAAAACAAtZ0pS3lECNu0EAABvDgAAHgAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDI0M1VUBQABtkgkYO1XbW/bNhD+LiD/4eoiwNZFlt+6dp4dgLLd2J2d+C0pvC8DTdGSYllUSTqK+ut3lPySpu3WruuAARUMi6Tvjsfn7p6jW5orzaji51YrjFcCX2uepUJ66tzqz+fj/AsuevNikEhxnz0YwuV8OAK61YFl2/mKTeMsn7eco6WWUxi3nsKMyzsubRV63GpJnkQZLrc8qmmxoVMtV6FReQEEjQgZvqM6FDFM+dttKLkHKlUsEoqfWIWlJpCEsoCjXr1cewE/dKlMw/hHGPfHTqNcLddOrHHumDHIYx0y
*/