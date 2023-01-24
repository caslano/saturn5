
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

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct greater_equal_impl
    : if_c<
          ( tag1_ > tag2_ )
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

template<> struct greater_equal_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct greater_equal_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
    : tag< T,na >
{
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal
    : aux::msvc_eti_base< typename apply_wrap2<
          greater_equal_impl<
              typename greater_equal_tag<N1>::type
            , typename greater_equal_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

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

    {
        BOOST_STATIC_CONSTANT(bool, value =
             ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >=
             BOOST_MPL_AUX_VALUE_WKND(N2)::value )
            );
        typedef bool_<value> type;
    };
};

}}

/* greater_equal.hpp
8lPt1aLoGkQYRss15tQPbJxrysOOFps/aFptyMJq5zz045NlfzKexHzKsTMoa/pBPN33J5+69JA3I4O7zmAKaX1xiME5LpPOIprXxAsGx8/6I8oR7R70FIS2hmJaa07SEfg7Z+XdynGhmh7aLxps3ETrJC0GmyEVZ8HfegzY9N9Uee+rUJj+FKD9BeQ9wJS00vXF6J0NUyghxxLCyl+YgDet2x4uRnd/IQ/YRLimTOwXxzDoS9OwKNyiTPTM0qLd6tP5yax3gELjUOMUjSsWV3C5RbdNbQywA3xWptaIUf99QY68HbTJGfbwkRiBlYeh6RrbJGIL3cRluCCVPq9FRT6Q+lIdcRDSZQXIo+wQjpcXeKojmu6+W8zpqhJyr87VYIJOxfjt3qYrg0j8SO+7iq8lSL67o95/rOhKpZbZLuuWPFcs0SnvSvUpvFZ8FdsuuPx8vnOkUXit/YzuDnABKL8qvXcndVUp58+SCu/M8FYo74qpjLBQEwRvl0kYBySlH6crF7Nv4HO3SR68jx/A46C80X8xMFeiycf4Nf0s0cj+mbNHw5FnY5asvSLXsqmnaPP8r3Q+vXXzw0SIJO9HGFUlK7zpfox6+myKvxc7mA/9axPn14u4yjWV1YcXkzujtWjUw+KnxYrdDig1XeKdE1N19WF9Y/zgBB8m/QXa4ASFLNZjQ8ZU9qz+xy0s6GKM1Ysn3cwD8Xw4c46l
*/