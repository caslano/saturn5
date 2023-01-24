
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/modulus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct modulus_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< modulus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< modulus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct modulus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct modulus_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct modulus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct modulus
    : aux::msvc_eti_base< typename apply_wrap2<
          modulus_impl<
              typename modulus_tag<N1>::type
            , typename modulus_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, modulus)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct modulus_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 % n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct modulus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::modulus_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* modulus.hpp
M2llxcGxyWYc1jk5xMqjNKc1YDXwYYRXyba0yfroqbkrEZThBqoIR43JWmCHf142oDUos1IWeUCNmpq2y9njekAV0dWIDknGQpVeLYq5qo9wtngRyGJ8WG1Mr5FdSY4pOHj6RqzPu97vGR6ZLMNpPDTd8FD9Y6qUc50FvCLtHZVjS5AwkQ9atLDBSlhles0wLKrYI6DU/J6D462smVKr9BT7FFun+OdjfSZ1zWgVIdL6ZUkPh9HScBXr8WOV+asec5UlZnWo8C+BVe8DjdYwPFTRMYO932dG5UeWmKBwT4fAEV/MR0OMOOmdLuTjT21ABj0zFAV9IMBFQmtVybD8+vTuDusgaNTLCXsdiW9SpfHTrf3s2gAZyjDQu3GzOrWlHg69yXt2Lf7486i67dT5B8Ffa3p/EJg+oqHx0vpOKt+RVE8Sd2gLYM3JW26qpTh9nJ/WP2OVrJW8lDIZGl9V91ZKYVx18EbM9uWHR3M8IZQLe30OhphV+6Y1cFLQPEaV01puZlHk9shiz2+jEL63XdwYxDyuEdR8AnxxKd/zYE2bg2aawoih6J0SyU+XEBGordzWWJ/SLRa0ierq9s8fEZgg1dV91c/uiYjqwc2g72Ovry40VxesHH5A2Ifkp1dWtjEYHg0M2zd1DIbY238Ag8+WZzSdsJ1g7IXU8OoFB3UZTCB1S68V1dZuaStFHPSI9i2PGMqPy52os+K1
*/