
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
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
K9JX8YpjVytc0dP5bfce+yTpkkIULWMqOlLyaJoytscEOiK21l4HObqOK96VskvPlYhMDEyCZz+D/1CeIU0VZZmL9YebLaFzaoCiqOUo6CRd/VA36RkZ6fMTEuik7Ty6JfKcxqzyaeb3FoTiD0oS2X37QHV47cBEelFlXGIC/qSlzYp4Y97qoaUHwW3jse1f1Xc52jdXrbPyvCz7v/tKqRDdomJ86mIwCw2YlGsJSp9Ugjg2t3qg4ISABXtzV5U+c4JW1vUfSVP3/tdvGRq93gR0PT3nwV+v1N/dH/K4LUk3sT1BN3acyi+okqMsNZmmn4OPiGtXe+8bSTvFCvmgtdHrZxC5XuctaOYymhEkpiJ5ca9aj+seodKetkneYFTSq0uBvtWxAxXLg9sXSQQ8GK0JUX2GcacHBqq24SscUJ7J5+f8eO7CX3qgHepqZ9/9jDnbcOP+SRXlw7LJEPUwS1chULGB3Fjuq+rTZFAF+8D84aYPn8N9ReiVXqR6LEc/f8ARuJHqkrvE0ygYBPsSk4PqgSm62zYy1K774bh5RXHpOJEqHjMPAvtTIOBRLLLT+adAgPW/BQKk/zYQ4PlrIGD+5yBAy9YOSx2rW9XgQF/kN+XtKFSl1aI1D/G8jiztdlHdc9FIEVEN3lDRjugO3QQ8U/9toe+vkqATK45EPAxSoa8SkTTDAVKsNDTpkw5PzfMbWStpK8LkTJVH
*/