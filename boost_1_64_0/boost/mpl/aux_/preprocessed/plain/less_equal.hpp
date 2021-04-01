
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/less_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less_equal

    : less_equal_impl<
          typename less_equal_tag<N1>::type
        , typename less_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less_equal)

}}

namespace boost { namespace mpl {

template<>
struct less_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value <= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* less_equal.hpp
RYJ7kGyFSsyueI0+xzY/5hw79I37L3bUfbc6+pO9XMQHi6Ms18qySojXbJWPjeeiisqZQ2z0jWbwc9bSC3XcPn8FgNaOr68bqizwDiBhkDrMhl1ZAIbOcOgrek8qVc0gLUY1m1JLYbsHI69pcG1O2sWmd74clOnLyd48dRlR1IwPp5qWOI/xIftPoMVKTIgvGcxdtRfLT4JAUpe/uhGfQ+akZmdlWIuEHlyNuvaQdiVFQYdyDfmxRNHZCYkOhHnJUVwrY4tI3Eg6dmjpr0v7209e+SLbYeoAi40oKd75ggFooU6OBj+sbwLLL9YjmpvcT3J/ShiQn2eE8Dc96pdfcWqRfrqHENqtNAxzUcbz185GIqfTaGoSRyr+dJOHySeDFSyGLbGp/bQQ/t96TL08Ok2Mc90mEEvUVpfn5740L2tEvy+bVDTTkXGe0I2Lv7f5gGm6vVEOJJ9HkQtBHaWPIq60Pn7xnRlrvRv7PvJRa8WqNp4eYg1m14qFtuRLFwx6YUEGVl6NOeiy5nyD8NGVKCcDj5PH+DpHbKnSgrKb/514K/iHsC3EXe3vAg==
*/