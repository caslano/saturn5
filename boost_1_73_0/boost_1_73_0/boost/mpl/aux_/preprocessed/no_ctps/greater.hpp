
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

template<> struct greater_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_impl< integral_c_tag,na >
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
wcLKGgmvYuElPVRBWueOfsO95E7rriCd3E0mU9/vS+BKHHxoFlUNwj8GqzPEwIDTfga80oeDH/aejNLRYr0tPzZsFISb9XcI9aHxyxtKhPxBI5srBH4QjUMDrsUYH7TCwg5RwcC22g0IP0ettzga7XQVAP2NAfXEcL+ShCy0dQyUVH8iJMTpU83pw4I+/4h/UEsDBAoAAAAIAC1nSlKOdcSrKQEAAOYCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0NTU3VVQFAAG2SCRgjZIxT8MwEIV3/4qjHQoDylSxWJEQIwMDEmvlxufEwjlX9qVV/z3nJA1SQWqn3PP7/HKXnGbM3JiMtdKeXJTHN55PMdlcq0PyxE4N5LlgSle/nq4mfK3W8InpiOk5e4tKJzyEc/HnQvy34JF49ptRCJDHW7WiSHJcXeQaOMYAPsOpMywChozgKTMaC9HBphlS2ChdsFoFv99uX+T+JJUm08swhdn10wCPT1Da99QKNtm6iX1vyJa3czc5y5GUc4/jdF+YvDuDNWzAOMYE3OGYCJ3JsEckWOUu8krp48iW4djGQRJeQ4CrXgbKviW0IHcSj0EZPt4f/mPvJ5dU0Xdl3uSWxBCpvSvyNjjK6NzuVo8sVZuvIBei
*/