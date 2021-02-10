
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/not_equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct not_equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< not_equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< not_equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct not_equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct not_equal_to_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct not_equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct not_equal_to

    : not_equal_to_impl<
          typename not_equal_to_tag<N1>::type
        , typename not_equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, not_equal_to)

}}

namespace boost { namespace mpl {

template<>
struct not_equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value != BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* not_equal_to.hpp
IBMZWlnfgmmFBharLOMyqeyFlO6/HY5t6OG+MzQavo/oq6MW+D2onR6cmEWOpw9WKU8NFpIbcYe1CgJsopJFJ5oJDfYxM4SZyVKwIWqhJKOluLJj8N5QJ13qbirlKRcSHGKlugQdLvezVN1Qx4aNrm7ujT1+C7ULbjCEgZLPoQU9nECj3T6CZiN82QybL8EPjoMADkbj6LDC9wqVhdArMIGeUhNeAJuW+xne8yxPsW7T06mwkQrhVuGmpBIMUGt+g34/CYG9brZetFt+0Ajc+ouZ8Xxyi7EJgU9d8pSSkCEaS4+Vzy1RWIQa4wKNJfeBHDYVKYLj7LT25807ZJU5LoEbw+OZvY9TqBPSN5DxBcRKGpdRLhfgkg9qCgk3vG6dOKQrvVWFlbV3jYWYLkpMFWlJi3MLM65hgiihpmfK1Ai7K7GuNE0hclcZHaLpV3/r+sT9H4Hf/vKMbse4Ra2ZiZrLhBeL08eNPQqtbNqeWcfJ8kIZFau0Q7pB0IDz7qj7un/Vjz567qAJV8M3/XclLVDRUp6/WLWYa46Dz2ObjkP4edxu/irFR05t+CHyrLO1AzbPU8Utm+eWDdfZkWUiXHcpzcQ9Jiew0z08MrDd7F9X3RFCox54ZPf698hute+Rv9S99b1jzXtke717
*/