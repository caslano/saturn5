
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
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
KtuJq6qXyQE9kWCW4Lwzsa42BmnZ6Prkvr0zs/7g/FkkPe/X3zaJIiO8PHZtFBGXFzqyHsQt+16U+cKrYgYj9H7xhGCMsKh1a1NCFnDK1HHp5ap1Jjluzj6WA3D027M820qByQoQ0BGerQ6wlXShoClY7XetntwrqMLoM/dlEpTTh/QXzIUo9Fw6v87GoZkdB8C8n9eQjDmqn115yfYhgiDeyaKy07md5BeFpN9NLY7urmYk1iLlRjRCNCcZxCkhiYEEP4hOZfHTCpcYkQreVAS4eWNW+9hlxXgurt00WQ8/qGlBDcippOmlbWPjWqDs8UhUld/G5cZGo67Loz8kRpj5oYhs4BbVyto58TaRjtSf9S7lOdiuiekeTexaEOL7+WCj30fe8AhzAW7SXQCnd5hQTE7pMkGvSL5OY2tyFpAmfO+sCOYqDvhrWTqoZDgRHJRjRsFjzo3OQOcp/x0+wUEH30vMB7N0hRLXXFhrG31ek7ZzV3ieYcXIfNiKvQaNW8gQA0KKDAFHRRpWKcGWsNiaoEpopb1TT3GlGJYxIXUbbutLO6FoSktjvA==
*/