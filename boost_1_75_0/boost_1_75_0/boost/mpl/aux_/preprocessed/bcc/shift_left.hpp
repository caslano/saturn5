
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_left.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_left_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_left_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_left_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_left_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_left_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_left_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_left

    : shift_left_impl<
          typename shift_left_tag<N1>::type
        , typename shift_left_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_left, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_left)

}}

namespace boost { namespace mpl {
template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  << BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_left.hpp
BmLOxwdv5X6SU1xmviqz+BHKcytLHosjfx6GrvijDglfMWJ6145cr2iKvqrUANdmnZLma1FrothC4dS2qZmWhz9kv1HitMzRzv2UjTUxJLddlZa7tIaXjPo0bqRpiYO9JXE4bV1oF0OwwpRSIyeIeyLQfSvdQsJAQ0AkV2jaxNXPCEl3HJCFLl/q1PQys5dShFs/iB3Tpig6VlG/Po1nwFeyPB0vx2MQnc9FJSQQdOyLBfrNF2SgSOktr8RoiPyGLe3Vk6qFY1pOBul10JJXpJn+66iYSb6zThPDuVRlhVvrx6ThFOES2+TGrKdPt4g/eDoCZ97S364Xcv9M3etQCSEhdmqFYCjp8tMbewzQTDnRs+BagjFGS6pNw05ecXtcfPZqL/sNWWX+7J1QkHCF0DNmXGKk8C6UKzCsW4IOJMb2LyA4/3gtamGgHRum1Ml8RHhHCvfpS2CO9vvdOtrBvwIuOIZ0zFOskRrkDG2EPfpWXn5niysDr2M7KHu5lY5UoWXZjsV729WSpAHqVCRFutQ+JPT8zMgJBkNbd7Yf2nKRiRE9QOUb5W2+9m2TJG31alp+lunZAtT58ySyRrOJVnlfmpUC4nxPk0wkFJgnayWdtZ/smxsJ3VD1Uakk8OFfzTF7NJGw3+Xhd+CIWaXsOIda7PjWTglbTlyRv1Zt9q85ze3aP5Flyv+1BfW7ysr2Gec7OgXNnUxUYNwQ
*/