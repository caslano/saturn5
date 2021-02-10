
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
ZnzIF4Ol8a6xHJo8gqPwb+B3F/BFjmL0vrrxP2qf9+j8wvHYX8wjGlNnhbT53ZgSzYICHIQes/wpfLmEuORjdC3z0vMOM2ly8LxmMHqqsrd5Qcd8dw5iknDMy9RlJmX1pMJaS+Ocn/HSWIXBuwbvcan+7tXdQ9IfRLu27ODuPnlWYbWRycLKMPSbJWUi8KuScYbcTGqkOe3Ge+yvd3agOdLMeTffZgrUxICyatdIhhJKHVEWW8PyOWlvVmr32JgEbqzfJGXhyBImpGEHKq61fVW4i7SzOrL9CGycCf88E1rYBMHauPSL0H/HWmZzsC4DzwxNa9sRtp8g5xp+IpbQ1rkybRZPm1hKQDIYJVTRY/Tig9ctWfZ7i10pbaJtki12SrqpWj4tWsK9NNMft4X4df5BXF48iW46uvl6ctJi34iWdzok5PRcT+rC3/1+fv/Qv7ulLEJgRdt7/l6LDaxJ3uYU+IJYeacFdXyLtTYxvzxBnmHeDnsVdH8NevhWoJ9NleeAVyH/DkHsr22P/VUv+Ot/SL8BUEsDBAoAAAAIAC1nSlLhxr8nCgQAAHIMAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjU4VVQFAAG2SCRg7Vdbb9s2FH4n4P9wqiJYG0SR
*/