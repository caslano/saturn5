
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
qTaYKgPWzsEpXdYSeQa7qpYe3+Qn0POHk19Y7yibBtlUrcinJB3I8vG5UztOOI0Ok76/XBuqSC8YDQm8JdkmRedAuhSenfYazkRLge9tc3dTW4zRmEoU5/kQgYxLyuwVnl4Rx5NJxCB/lfsTYiVj8H6QRaLQON9l4uXRxYD5KfYKE6pd8eoiSLNrCy+zirCur49ytswe0+hA+DVXL7LaT2jjxtuF1CiCyOCiOQTZSDNT8PTjjTrnHXWsZuBPFbQJ7Op2/XfwpOjlJMTuFCOizKIGefgGBaC8seGub9pCLW8au+VmMdRXvVx9hKT5oNOwEz7o/mcRFkFoUDrT+R5xqvymxod0aSQVmmllZcUsTofBNDQlXXX/bBw0pEtrIZKtAUw1OYWy07TBZ82POP03f8cY1L78tiUBrD9aCbIi6ERw5GBbwrGZoJff/zfGKw1xreiiKr1ZE5YF7upqsVVr84IMxb4XLShUKwraUl3C2ArzFBuFArHGLI0vLJFdgk9JItFQqXyJH/9MpHfbVC2yM/TUmQ3hB7opIDqSATztWyIy1wijUkSJQx2amQ==
*/