
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
ezHzu1HZM3orMTju0arC06NNaDRup9xYCUeb81jckmXzQeTFckMi72LtCWUi9wobgSNCUXXsonVj+FVrKiq5L1VMxqBHv/E4gfu4ImueqVo9JRG7alrkzS19UUDiVLn8JSv/NRZOnlgVmZ+ZzZht/2W+wlrJwHLj3KEitGyU/9vf8/Ht8uaSHwQ5Z0mu2DnGk4kOh7Y8UR2rvpvlFIlAYl0IzVFudEGqEDw0J+S3/oVw6BUKZTp06XoWJX/y+Ha05Bcvwc6UU3lw9ARzgkhxqxUDDZd274snCaEGhgXqU3LkfvZF4rVJqDqqz9MtToaIz9zhZ+AfCgtTiBWyfsgDPiGX+F9IZE6m2q1uC7+cC+X+Svb8G+V2FdQGlwUAuEsLlGKlFFp8i5YiKe5W3Iu7/FCsuAanuDvFIbi7uxTXYCV4cPcEAoGQ1dl92d2ZnTv34TzdmXte7jn3fFGL6gzHC3l7PNYIwCEGfBp0MAv2J897j/8GD65w5o5UOLuZq2zWYTWh7tT3ab71HroJfak47t+4/cmosk3fObZUx5Cm0wFpjv52L3N2c+WCbI5i+QjUksApCuhEKtzwkCWpYmansHQV7VGAFsGsSPxYy8MDanhkbbfsofWwKKgkbTTUq+bl6jJTVYF8TCflmWjSIwv8VXdZZdnE85XF5tpK41qI4/HFCbq6UtCyxHhwRZclIv7Pk/oYTek/GxRSh1jz
*/