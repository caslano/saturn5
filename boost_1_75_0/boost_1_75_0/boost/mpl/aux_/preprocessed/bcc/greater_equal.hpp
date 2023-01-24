
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "greater_equal.hpp" header
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
Z6WNp319ROq231cD6+MqpVGpwXO0tT61uIhfSex9C+RqVBvyTCO+aHYNNuSB9PWNRcKSsxeSy/6dvOs3fjaKt+PSufBZn5rAaoZBI/ydVG5nFm+7pP7Fb/Wwa+NkKr9OTVqg73NjtnA99TXWxzuztdjYb416KsGtWf+k69Wtq+9lu5WLaUUznGpjGv+q5Z+FytRjszi+TkqcKz+nL4N7I53C4zN8eG2Et+sh4Jm6LRTL7/b/HZRvI52h20hQltFTqP81LE7hc37LxLfM2zKQsMvEAyZPBE+07+P7TpWnA946VKqGvUWlLFMwdHwH4bKM8NE58Pk5Vf9Og5Ew2Nq/OI9QLeY27hSMzTIF69P0/kdWmYjg6BzXm3hNVcZro8kdAcY7Vd07VXmsYSfBjFRPpKmN6VsIRkJrHc9Y7xFDkuma0J4pyRe+6zeOj1S+jVZbGM8RlaIpm9BsROXYaJXQdKxN0SUYF+6tDtW6BC63Zye141+k7gF8Z6yks0zlY4x3qh5OciR16R5mKu1U9NK01f8LxUmcc6+z05RH+OulUPypsUzeE2p2qLT18lvEnxtVb+rRwNdK83aVeGmu/3wRZeOLhsW5rh98merZdGHHEazr8IuG0Oy6+yWDfP5XLJY28Qy6eFfvRazh1WKDuEJcI1aIV4grxSvFq8TVYpO4TtwgNotWcZN4j/hu8T3q3f4/fd0qbhNfkn8u7xAD
*/