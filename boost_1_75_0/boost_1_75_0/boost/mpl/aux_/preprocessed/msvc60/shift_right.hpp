
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct shift_right_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
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
    : aux::msvc_eti_base< typename apply_wrap2<
          shift_right_impl<
              typename shift_right_tag<N1>::type
            , typename shift_right_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_right_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n >> s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_right_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_right.hpp
JUhOQ36CTgHiEiWPjq3uqI68bMWdxpRfrN/3zc8xdZ/RfzJm8foYgcJN+92Br/08QiHPUTU51M/9MYZrmAZ8YBIzLrD9TH5hbe9sa3OtVqT9FfBCIj1dQvDBFHEeG/UYdqN74NNuV8fp/nDpoXztF3h+Hebdtkbn37bDo1kKRV38xVq96UR+RmLabd6HY5m2uUIE7tcmh9I04rEp15DZD6a72J3Dy0nwjn8vpeJSJLVXAFudhZr2+F8LZMzkqM+wTgqYTqPdLn53j6uAE19H+/WCoTdX8WkXEHS2fAjC3XtkoBpbyaeNk4Wfo26PZa/CwkPScalx+IjMcNsfNyfMb3bXdj2ww0vHow/Rx03H3cJ1xONly1tT4ArRx9fH1cdfwskOcQjh8Wt/CDsOruq+7ibvju3W6J7orsqCTbiml+4pHue+9R6g2AZ3++CC8GHzb5b2Ov3Hm12G6saOmhBGkY9vNJtEk2uK4lJd724oKJYfiSZCtZROP8VDyIoZRFdm+pa+ZZ94NdeteRA58kn7zvk7e/rNKe82zvm83kjU9J8seL+qeQqOL5N04sq9OIEdd5iteSQF/sn2BRB6V6lAWISgbFaVzITBzlGC6J8qTF0AZZB5rETeRrJ3Rw/MZyW0rerq0beEm/Wwx2BjWa8zvL7mXJrpqc6cEgTqheT3V/ssSaolG8AS3fTsC7/PRKApzQq3vUcJKuUIJLhD
*/