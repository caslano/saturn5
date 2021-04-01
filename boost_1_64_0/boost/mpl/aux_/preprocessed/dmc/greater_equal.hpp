
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
eE0/qz4DaRN7l+ANbrTMjF4yLQgRyZ046pUpdAFvwq9vSKBAz90/vNlH0gpQauumz+4tuUIdg36CaNg0fyAD06j4sQjuA6GYk+iC/ODWMTh/YwetnmDsNe19tnXviv3oB6+bcwf8pLWFebPqxywJOclHNYswpuoonHrzXK0uT1mZiDi4wacHFTPJYgnXWg+oyPiV940n/vtEb58I2aSRc9DwmEBch0TSj/LcHFVthYLzHasxF7bXHdABnNxpdsk30Rw5Yhief8wFq0BX5yvGlgivoRCoyqUBrAzKLgJj9H14tB7bq6YBlVWWyReXtbTtAOU8W8Q2oe2RT6hTEOrSl7WNHt/Sj24956PKDRptAswDADfOoLfYp/ox9OOEmPoJz/p1q3BKk6tmFRwxOlVGG3SgZIbxDsTAWH/f6/vDp9p0kMKiT37XbS7ssd20TQPacY/1GVwptkV+FDBZ3aLCh00D2iAReqvqTL1wWuMB1/Grd9e6sjCreWQTmkGllpD1/Nf6wM6TFRe4xSMowVIU9IvaNPl0fxQBYfyH1OUxM85gx+TJwaphw/jjHA==
*/