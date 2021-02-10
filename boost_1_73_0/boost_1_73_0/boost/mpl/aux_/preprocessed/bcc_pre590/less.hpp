
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "less.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct less_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< less_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< less_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct less_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct less_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct less_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct less

    : less_impl<
          typename less_tag<N1>::type
        , typename less_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, less, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, less)

}}

namespace boost { namespace mpl {

template<>
struct less_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N2)::value > BOOST_MPL_AUX_VALUE_WKND(N1)::value ) >
    {
    };
};

}}

/* less.hpp
K4oMlYE+GOkCM3P8Drj1VofNlPSrNpB24R53wDwUGYehbJdhdOdRvsGfR9ooCB5VV+RPHssPEx32VEVWtT6K/+t/Gw2G6mD0vdcBZhzjA+97IU1wpcOoFmIdMGGUY8r7c0wTnupw2KYojnnGqA5jwir8QPn1ATcuL1xKeUE64PlIad1PcSi8ifGrG0qQYkLYvTz3sojoPrLtLE9I1tDdZjluAzHMt42PQcr5QXzwO4QGDQs8/jwh8JzxFEYZDcsaXnHJcAUzChsTuBRo6QaHRsyKIqToRqhL0tOLu/TtN/2pYXpzPV9Sh6oQ+sSJ17uX1mWAy2xXw/aMhTuOS8hT3PYIpmEFI4wp7FUp4z1gnFqsoDiUjLOYkTForDYK8PdMdMELq7gO//LRBSux2b6ZCG1R82NJpKfA8pa2u+je+6bDr9LXLugKjw8FQ/qUlR4/mF9QSwMECgAAAAgALWdKUma5OPG+AQAA7wIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNjNVVAUAAbZIJGCFUk1v2zAMvQvwfyBS5FLUVdIVAWoIAYKuaIJujdF4vWs2EwuzJcNi0vjfj7LzcRmwgz9EPpLvPUoResq1x7lQxm4df/5g9+Xaws/FMsvS/gWvL5lY
*/