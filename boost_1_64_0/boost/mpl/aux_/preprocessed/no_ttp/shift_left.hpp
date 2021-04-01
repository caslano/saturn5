
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/shift_left.hpp" header
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

namespace aux {
template< typename T, typename Shift, T n, Shift s >
struct shift_left_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n << s));
    typedef integral_c< T,value > type;
};

}

template<>
struct shift_left_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply
        : aux::shift_left_wknd<
              typename N::value_type
            , typename S::value_type
            , N::value
            , S::value
            >::type

    {
    };
};

}}

/* shift_left.hpp
HFZvkFwoQH8zvDoVmIA+dwMo6eSOvZL9/bVRDwYs8EI6IhCZiVkK0u1W3hMTPDhA2DopwpKGYSD6mrtborre5rBKGVIDnZlPRemIeM6NhhNGIBZrGLCkFcKlq0Y1d7L+dufHzZDVF6Vq5xdTJJh3BKtGVSnyD91OUg9gXEYzM78rTzgVqZxj6vbSsqU8GNn44FE+lT2DQ70Uy47AvqJnxYEtWr6UxSKJGvG3lHqHzYgJlEsg+OOq/s2n36GiBuZlECMy4FFpHtI4aN5W1PRabT+xV9k03q3ECfKz4kR28yI2NvsmKk55XWBTJjb9S/HOD0AMHA0NhZp+Yi4vonbPlXMnu/8ml09spnwM/HKQuyvO0fmA2MddGCPEzrqPaUF3ZGgX4HTi+g2Voaq5ALgbuFeJaQH9a8tm6HqncAM9LUWgqlErj/baeQiG4FOF0At/xn1MI7auq5t3+cWlDep15S9Xeusn6Lopu9HEpr59YeJWChG1u2X56z2T+mVxOQwor4gdsyKGCl1q8WfddRztvJRWS+0MtJqn+5WWncD/sxkNnEBjgiJd/WcBCA==
*/