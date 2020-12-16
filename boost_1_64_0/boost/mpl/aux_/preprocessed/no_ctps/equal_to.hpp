
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/equal_to.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct equal_to_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< equal_to_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< equal_to_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct equal_to_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct equal_to_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct equal_to_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct equal_to

    : equal_to_impl<
          typename equal_to_tag<N1>::type
        , typename equal_to_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, equal_to, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, equal_to)

}}

namespace boost { namespace mpl {

template<>
struct equal_to_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value  == BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* equal_to.hpp
LXwRNsKX4H1wJXwEvgqfh6/Bl+DrId+t3FPDUWKf6rvNEvv2gxlwmLT3/jDUX+S+zKXTX3aR9LtK++wOs+AQeABMh3kwAxbAoUq+ze3kO1zyPUiZ+5gFR0q+h0i+oyXfw0LllftC2FenvMXSjiUwAZbCJFimvqd2pnE/3lHS94d2OEB5f2qdpDtN0qnvTz1eylMr5TlByjMfToAnwjnwJHgiXABPhqeqMQW5HvfRsWsnsWsQTIRpyvGVLeme0zm+Foldt8G+8A6YChfDneGdcAy8Cx4Ll0AvvBfeCe+D98Mm+Di8Hy6DD8LlcCnEDuyR+wOYJLq1/+3y/+HKfk7Zr5/Bfj7t+lsebxuGBHzyCP/PR9rxzUftl6/1/X98842+2P3zi6g31Ue/0rd5/PQbfD3+U7769B+6x18//gfzPvslj/33/fYVb8WZ8t2voJ+tQ1IreIcsUotcj7Qgtjkcz4gTqUeWIT4koZLjoNLy6VubtVmbtf3D3nnAR1FEcfjQoBFRSgIioAZsEaNEREQEDEooGjRiUFQ0JLmERI/kTC6IihohICIqKvaGir3F3lCjYm+xd429a+zY/fbuf8fc3l5yF+zu/Hx+7GVn3pvZ2d3ZeW9n3eQmN7npr0p/hf8fhFzzf4D/34r/r6WM5qD/P1hqYZmvaFqNJ+T3/yDNE4n5Hiy/fyfNLaciX1qx5hPsftqV5STiUzLjyq+WjnWkY23kK3TkROmoSVpHd81j1yLKEzVvTkybYuDQK/3foTd/QpSvqAKVJdP9besLz5t/QxlF2u6s7WKb7sWrxbbrCvbzx+ouL6opT0p3ie1d+FT52gukayLyE/vVmbrUtiW+0qLKWn+b+sJt+wPlBHPadDZI51C162DkF/ZtcdDprcIRlYBfNaxzpnSavsjPrXoXy0dk+ITCvrYW/u611Nj63odyjr/QIWTnM/A3q+/tHmun/GaRWICMVo9Hx26efMrApVTpdW6v7rL9MwxWu0fsN31R6dDuI+4Fo3zE+r2vfudskQMbW4yYDuJngmU2s/2xZct0v68oUBrlkyzyeku9hv/MCjotoxLm8f1UsQEnq91OgKux36L82HarKfWVlgRCbbZJa8eXNttrT/JjVvVhlaUzA6F2/G7P+O3YSrwQ/jzV16g/Dkk/CP72mkMbtIT9h5UVgerSGqc2UN8hn2IJdtN5NR5Jsdpgor0NTK9r29eRuHW0r3Wha8m7siNPduyKrIEdLSE7KioD4dMaN2zobGvThvD1xKq3X/q2lj6/fPwDpC8T6cR++XtF9HkT0dHduGb5K6imcU6kDtT5qjijGqtsnefmddSjC8beus5MRNa2jsFKW3RhK+f7uYnFw0Ta3rAngJRUl9JNVp4XndHjK48+FotlT5XsOdgqk/08BWF7TAc8V6wE1nbpbhwLtZP6g3MsQqWtf/RaK9Y/3M1qo5BNvvKwfzh/fF5um/0j2kesNoi0Uxe2gyXYvovSIBvWlw3rIens2xDfBv2SuL9atqhtsCl4zkbHDXBPiIqZKOhktwshX1ObdoV+Gb3HqLy8JPz3dht7mDaq32Nj1PFb7hBLsD77tTjaSCxLEj5+2RO1ls24tWP7Sx/26zrJSV9FZU1pdSCZGIaoNlC/9tr67MMONmzEftmONlSWHpqE/r6UU06jh/VvwHYJ22Yb5HWO1d+P/fId9XOXqa4ondGOdjfHiF7bGPFhBxs2Jp9/ki2uw8sNNlCasO5nneI6bO0/bp1Y3Zuie5Gz7kJ/oLrd+q3zkvxRdV/uoH8z9DfY9VsBmkkc+0R0Z68be75lorspRjenWjt0m+28aN3Y54At0NVi10UXJ1bI50tAn1mXzl0=
*/