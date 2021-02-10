
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
qmf/uEVl2xk8jM4Dl6zmctkQI1HfJVHZMchoZ1OiYBRA0K+BYPQh2yUelqZRpRYxu9xDNrruNTZZaiZ6+wv4T5vObciiBJV0jB7inTPEzFKZfap4l1Aiy42q5anMbIc2+5GP0z5OAn2dLUp/W2tIMdbJQRouQgMO+PrskBYrWtZ2hdR7hzEpmudZyWWdXsnXE2GeFHNAAvp6laGbexgBy0jgICDYRDtiHvILLmE8U+3oK4nv17olChbhD5HAMIaeHY3Yoo4xR6GSWYTitQ5bst3rnVGtoKwRz4qjXPBdvUDsY+9hMTodlpcg2Jk3plpX/mCru3RFSJq44rg84Ytlf/amPm8iutzvJ3q/GC1LXAhtDdn6AXMMjPVytbY55pL0mlzsIocrKmIBnDvnRm24Pqlt1Do3edPut40Zr/njGvjdGoR7W1sFW58EjXCnoDsoVkUqFyeh1sV8l+JEmwWm064ca8eWpUYJZ5O5Sxq2kqfQp0Wc6RWTxcSCKLdLfGkVUTj0y218l4kjZBOs7ynyViXOo+NztdCc78JxcdXxpq1adSTq7UpztRY5be/n6+nMDhpGuLfxfrgc6oVDOWrUp/dlc+KXC6hTJGJyvZUAcLzEMW7QE503fTwg3YHgJz3ahATpL0b7ppBHpjyS
*/