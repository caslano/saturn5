
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_left.hpp" header
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
SwMECgAAAAgALWdKUmzo8LKOAQAAsQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNzRVVAUAAbZIJGBlktFq4zAQRd8F/oehS14KXjXdlIIRgVLKphCa0HjzrpXHsagtBWlaN3+/YyutSxeE5ZFm7hxdSRFGMjriUijras/TC556H6q4FKuy3I4f+P1Qitq3re9bbzRZ70Sed/o9D1jZEIWSU5WSSegH7DC8YcijrVCogMf2xLuVJp2k5fznHH5dzaFsbAQeGnq0ofJA+E7QYYz6gBD7aFofUSS5AgbkPI6BrPULivWZqYBBXI6d5PWNuPeO0FG+RnegpoCrYcWhSblJlHETkZJnQga/b+1Ql8DNGHBCarkUDdGR0z9CUE53mI4EE0qyy7oD9JYa+GoXg4CSqQqU8V2nXZV0Cylnq82ufNwWs0Fwu3kuZa8dyevbBeTr7zpKfpbz75mUT7DHYOvT6AfomjAANTg6B42O8BfRwUVsPF0I9TbmssAxePLGt0vB9w1T24/LysTKRyrgP8JM/GE38rsDt2djX0MrZ/uH593j5ikTd8bgkZcv5WUmMsac2giFIfhgfMVOLG5570us5CeYnF7pP1BLAwQKAAAACAAtZ0pS/jNvvXECAAAwBgAA
*/