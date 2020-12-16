
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_TRAMPOLINE_H
#define BOOST_COROUTINES_DETAIL_TRAMPOLINE_H

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/fcontext.hpp>
#include <boost/cstdint.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/detail/data.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

template< typename Coro >
void trampoline( context::detail::transfer_t t)
{
    typedef typename Coro::param_type   param_type;

    data_t * data = static_cast< data_t * >( t.data);
    data->from->ctx_ = t.fctx;
    param_type * param(
        static_cast< param_type * >( data->data) );
    BOOST_ASSERT( 0 != param);
    BOOST_ASSERT( 0 != param->data);

    Coro * coro(
        static_cast< Coro * >( param->coro) );
    BOOST_ASSERT( 0 != coro);

    coro->run( param->data);
}

template< typename Coro >
void trampoline_void( context::detail::transfer_t t)
{
    typedef typename Coro::param_type   param_type;

    data_t * data = static_cast< data_t * >( t.data);
    data->from->ctx_ = t.fctx;
    param_type * param(
        static_cast< param_type * >( data->data) );
    BOOST_ASSERT( 0 != param);

    Coro * coro(
        static_cast< Coro * >( param->coro) );
    BOOST_ASSERT( 0 != coro);
    
    coro->run();
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_TRAMPOLINE_H

/* trampoline.hpp
+WN0CP0a3C8Jhv44lgZ6FZe/QPfDp5LjYIhYrf+MdSixu848F1wAQ/hlZHkxn0yHHnANbZek3Vhf/9nhm/KueSXI+WmPIWo4UWywOuc7CAtvwUtN1BWq5HzH0RNP8ZNxgS5TH3Ysix8fna4v6fwzApZ73nxze6SIvVllwsbHL9lzKb9/XnzdlCSW3bdzLfdJp//VAmccNh9tnMefbq0Ev+RZvdz7kZ5y+RdpPvG7nqa6sBbfyqNmbZyTR+Cnb/lN8N+HYcu32Gsv/+/2gD7y16I0VpPH+GpnOEOTvRwFW0vQh7TuHLg3JRV+3mSt29iraEW0QloxrZR2sZY6C5dUEDfBWp1nzlDPS4xg5/3yqXbGPVSebX1u7ceBhsUBg+RicGBUT/uG6dSm9lE0nAcn3uKDt5v74L3WP/LpYzioGH6LVb+gH5r6/Om7XVePn0fx+yzrPF/xd/WlmGA/QG/rSU3gt2NditiTst/nedXZrtDnobgtLAbn86c9/m4Hi9x//6eR6smwjf/3fJ5+g2exPcV+qvVpXFF4hHm9yfMO4tCtauNNcPDbtACujIHDQc34B/PavrSY2C3OjSlpOn+A6QfpnyKr/dSfhHT27kSLzsMFD9qn/KQY/8H+44fU3J8VD3Kb99PkHiPUe9qG1XQjgxg9vW/t6jnsAu/WhvykY+fWkRPTVD+phb0+D2/Ly66gx1+QO/ZpSWcUpm9oo0HxcLIoPZCM++Vnq8V08YXwOQZ+seX1M/mPfuYdYo/rBvp7JN/7IHSaJ1qy3furYfUMOdPj6llsVQKfpcjPk2nbF1fgCvWXhlXpPOeVSIcNuKH6OnpRPLbYaB3POkvvbBoP/5fmn/kX4jrzOO0FfSugnlJKnRyH3p+ldua8sX+Av99H4nc+8rvQ6e+HHfEp3KOBC5WjeferwX0m/6Nb7nnRPETDD7W4zJO04yafw+jyQT7zg/HivOEPmP/f0w/qaqei1bZa83X58TG5+HR1+ff0qclcvu1YE7os/KXc5Vl69kc57wAxAWsn0XeVCsA8+xIa+SzlVjxOa7QapDa/TZ4M9z9dhTsGwpw7+Ng35rwFjacWU0/N/Y1EmN6BllHfbrlMHxLlne8Ywxw5bDLtXU38s08NMdIa70Wc5AN0b+0vjKMY/2uY831/ReFbl5J0fQ84i9OrV/N8rYK2AS5kT6Qj6caGj/LVYXxOH2c6lt4W3/C79vKLlsGewaP8KBJGJpsbew4rLwmJRXtRjWvbJjzOzjXgwbeXW2Myh/cNDosRfnNCLtWarsnWMsSPOLlbrNdrTN9P0Hc65Wgfvpga8t+8MNYSbCdPqXw3nFDr7blNvV6+GZYv3qN23qIRrbwcbtyQUxs5pYbZqSetdDV9miaO/PerUldHnP7evfSO9I4cvynfv+IHftxUjnyb+Ogp96eHrtnNxt1w+VU53zPVHpY2H0xDZNDST4fUjKzv1MWJ+rIwy1rI9XAn0bOuV4tPoH92yw96qF0Pghv0/oCP4N698lK5wB1L6Cdx/nEd97SHekw+e1SS8NUhcfqR+XxNbUTO0Vj8PfBIxOm16EUT1EsfgfF4eXjw3kaI/UaZH3w0/aD5i5C3rlKje5suToDtTf2+nc7Gmzcv8Pe35uVpz2gq1tXu28HEsWn6AxNfcXxYSzHcxfrDQecM0PeK7gt/sz376eLGw2bfsfOIJ9TI1XHHqHMVgw1DW/N5PpV6nE+9ST/jkgzzNkO+cJN46fy5479RA8FH48uqkcSJ26vgEi29Q7zXkF8v3c9nI+inBHn/dHEwgs6c63O4O8Ycfi4H3Bd8J8Yu66b8qHMGbJhCN3YXe7TI8oM0QxLOnEjzvIQrN4Y=
*/