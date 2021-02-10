
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
Js+rNFvGswm7x6skE2VtnefeudGF8FVtC3F7f8c4Vz9eXoD5IBuydXnC7oSoSk8WfUXY3ThWyuGOSOPIVcaPQB7OWjbYW+NNbpoQ1mmUoNJGn1rz6YLuKdKO7IG+VLtv6Ia7cna7CLoHwr9wAURxugkge40jXAaQLt8iZOAAkihL+tXLepkFjD20leLKIobf8Q1QSwMECgAAAAgALWdKUquEovtKAQAALQIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyOThVVAUAAbZIJGB1ksFuwjAMhu+W+g4WiGMXaYdpoKjaBJ3GiY4W0HYLratWaxOUZLC+/QxlMG3aIUps/7Y/J5GenM+VowhkrUvD2zt1B2MLF8FTlkDymK5huplBGJZ+F7bkK1OANvmhACmuWin69CEMMSW7Jxu6uiCQlnZNx/FCeRXBtlF4XpzS+6Q4azh12tSk/Tk1PxkscKeCETABq78tlFq1dMJEJsRD7Sv8iYk9JkrRC1Hmpm2VLiL4K0N2TIQYPS/SbJ5MRlw1WSwzUdbWee6ZG10IX43uxrYQt+N7BrlU4+MZlUdYk63LDo+zoSo9WfQV4fGesVIOt0QaB64yfgByf9JygZ013uSmiWCVxktU2uiuNR8uOD5AemR7
*/