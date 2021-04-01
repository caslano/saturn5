
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct shift_right_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
UHMvOmN0bbe8h3MX1NmuIkV/3uRh4YXGCOzWQScw0YUKnyugJk7/7OR+CqpJYvq6GKFQwC01ib8ZB2DF0btHGkTYjUqtDfIdlKuC2WDtH20xgsHA7w0k+ftYipKhZrRkqDxunzKB0DErk1YHlIyj+g9ImXuzb8tqCT8sK3M6W+Yl86TblUa8cKDcMe/P78/+13tYVhuuS5b98bYUQ3zHFtRNVKbs6F1P1JmhW3AaezwByerWkMbwyH3xfEuzJj8dBWFMrNSMPqJEpuayXK2+NzOiev3eIaCPI9Mx7JCW7R7Yq7Vu/WrO9eYOo4cMrBHAd55tCjGBY8EofU0zv4I+hkV3kJxZkID/37YOk5RBbhHgVZI5XuDdcz8FT8URMquaiRiLLH3CT6Fd2wZNuWnrRp8XZWdIYf6xMZvmHpdssww0wbFn3aNqVS9Ck2yW1lVmPyV3M89hCZ3WEufazkI71//QxvLo42LVZk9ZuHQ/VQvZhOYPoxCT8IWA7uAWrGyO0PJ+sBm9l1rBML6q7m4ZrrA0MheffHUP57gE/6oGrk42A4nykXj10HlrCA==
*/