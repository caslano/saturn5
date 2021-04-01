
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
UvkAYqxZk5ZS3F/v2r1mFVbIp4TrfkWW0EJ1PAUMA49SQmnAvymE11A9VCALv9d2IvgZiABRCOo06tiziZtqo8VfFSL/U6qUjzqwzaN6M8AOyi/lE56eTUbtvMQGEB7wbxIP3HM1gEdwpoBOUk2ZbLwcljbXfzCx5hfvVzHGpZmtiF45JlJ/R8dkYZ42cqj9hMhrWKTERs366YEqHLd1/pkYf6G/0zFW5vmq/IHA/G3b5UDvdcCCD+iugLw82BipSQWc5wD22emYZ7of7B10XkfwfYdlAugmtGDHR8bAnJsUKt/ZUfIENlxaCQs4PZu447L/9W0HuHoOnKi4gtzJzs+kitPZ66ZM/G5Frud8EVtjZHDnckVZvysvzLvRbu5M6C/ji/0DqOPLOUpLqyu8D+w7rJMYVfkHd7VbF9IvDyAYMuHuzvSr5848tdkP02O3LgZNDkh3Yz4dJEQCcGI1FSnS2058XE9LAyuaa5Z09/hKnZWm5gi/HFI/SBSybQ8KtktBtJdrde+mkATQ65BPlQM4BwiVu/VvhRMaNVtIQ6Srdf9dXay6jAtHsw==
*/