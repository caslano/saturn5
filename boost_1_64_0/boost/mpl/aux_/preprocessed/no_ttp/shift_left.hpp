
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
5v3CE73/s/1tAcTqEY7P5GuHeqJO+jGs8xnPMd+VqvlqzjHfRNV822W+vi7mC5P5ThOPyHwJ8mw8f143ynzTpX9jBuoxDf1wJvbDWTgAZ2MEpuN4nIOT8WqcjXNxPs7HXDRgKWbicszBNZiLt2EebsUF+BvMx0exAA/iInwTC/FDLMIvcbGMNVKMvliCQViKsViG8WhS1VNmQsv1NEXmq1QmpJ5myHzuWCTz6eV+wR7YCb2xO/pIffliEPbEMOyFQ9APE9Bf6q03pmBfnIYB6s9dyul3js9zk06O7XLMf8npmrul8nleg95YhX3xWinXCozE66Qc1TJO4krMwOsxD1dhIa5GE66Rz3EtVuENuApvwjvwZrTtD6NkPVqo7y3n6G+K39rJ1ueUxuu9aMKNxGP+HXSNxIb1rvuiNh383+qP2n/w4vZJHTt4/n6pRubxV6YP/ff3T+1jGzpCbCR2vKeTLpiYSMwgGonribvv0fquLmS4BOf/lYvv8y/U+f93VO3wMGmHp8hv62Tir6P5L8SxHZ5bbjT/XnVrxe9VaXc5X6uv/k0v4385PtN7WyjfY075Gkv5udyKdo8178XMlW2U38ryG78S1W2tCGmbx0nescTN0crJFFubLzffeP48vSRPPYU3KifKW9k+VZdlk5RF/Wz+QUwcCbKNXVhgasXYCa7Koh4j0Vfa5dWSzwpiT+b16GdrXy42qm7zaE1bs6stT1X7RKazUf3s+2Nkala2s6PEFcGsZ4g9f7ayPPNWr2vNNRjkjX/sx7ZVwPrLtnZ3L9ZfnsegPGvBvwN5ERcw3SnU/qyF07bnD2RTW/bxFoeQllW0UCm7Q/mbpO272o3yYzUq5W8IVZc/r1hd/hSU4PI6jJHh1uswXK9Pk2MZ5ZkE8iwDsmJ2W9v0Wdab1bY8913WY2lpltGgrIysc4O8N5eHK0iaXENjWR7bpzntsFx3o8xHmnmZh8zzyTKLC3Kt76+XvEyqfPaTNs3TcZ84IuuiZO2tGuuSB5sYzI9vkPeeIH22vyV9ca58VurPVZZX5/ScjX0yTZYU2f48jYnK51lCeaVv5CVzOWQ9GJnEup3Us400Xma5x2NNmH07Oab6DFw9kyP9Cp05HJL+rjpsz4nYmsHq7aIsz2Qw5uWVUrpW9U9c5jlgqHXbsO/bznXgjrK92o4zTtuLfL6q50jI9uLjwfukH0jqWD4zyil5Wj8j8/M1JM8T8jwJo9SnahstKsgx2PaletXnI98DsnypV6fPRrZt6bNTymCp69FSz3XSSfiyjPH6PLpRz0eGOtWzPAPFoDwEpZV1bYxqXV2r9816F/V62sX+dcJpX+oq6y51KH1Jtn3Dtt+zP7MtF1ICyzwN9vq07T9RnpZ5Coz5VBf5qfZ90tkszj6uyeev3lcctuck+WmYL8fpXGIMx/Na+/dEiXGZwxdFq38XKJ+/qYRyqr4nFpSWUFeOn/V+KcNQ+a4aLN+JicHWMiwuKCvjZ81P/L5SH98zO5+93kOYrylQ8rTkxTeU8lid86+zdTuyHwft633C6Vk7Hqh+zozsL7IvOJbzhJTTX+qmFzHSR2mYO5RTHv9z/jpx8btByql+JpBjGW6kz8lc31IGf+U1728IdijDj/7tJvnbyuRcTwXFuXks2Damsj/zsaM4nH8Jlx8PhfJ5LiSOUpbX31ZGlmzgEUBFP+qztF3jSSxx+p1Hz3mk8/2rpEU512MNBVNChXx3lGIwZUztYy0jNVghm1wrjmVeHMt29+W9ymajHM0krUbS8nJIPM/6BCl1FO/03SHHf+ftUo6DfJc4nlNosB/f5Fgvy1GOgLbfLDLPYvux/wulPHwn24+d8r4=
*/