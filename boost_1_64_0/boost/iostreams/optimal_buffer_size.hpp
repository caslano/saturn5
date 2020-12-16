// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OPTIMAL_BUFFER_SIZE_HPP_INCLUDED
#define BOOST_IOSTREAMS_OPTIMAL_BUFFER_SIZE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/constants.hpp>  // constants.
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct optimal_buffer_size_impl;

} // End namespace detail.

template<typename T>
std::streamsize optimal_buffer_size(const T& t)
{
    typedef detail::optimal_buffer_size_impl<T> impl;
    return impl::optimal_buffer_size(detail::unwrap(t));
}

namespace detail {

//------------------Definition of optimal_buffer_size_impl--------------------//

template<typename T>
struct optimal_buffer_size_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          optimal_buffer_size_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, optimally_buffered_tag, device_tag, filter_tag
              >::type
          >
      >::type
    { };

template<>
struct optimal_buffer_size_impl<optimally_buffered_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T& t)
    { return t.optimal_buffer_size(); }
};

template<>
struct optimal_buffer_size_impl<device_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T&)
    { return default_device_buffer_size; }
};

template<>
struct optimal_buffer_size_impl<filter_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T&)
    { return default_filter_buffer_size; }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_OPTIMAL_BUFFER_SIZE_HPP_INCLUDED

/* optimal_buffer_size.hpp
CDv0vceYjhFH5mXH++4tiCTxPO85ql+sXZEj+4831DrgbTEvcGJ4Nw5AXUipOkC5Pd7ppO0ab03PrCLzp++pr/3WvsycyUw1981jjhPzUsc4lol5TXlGbLL4q2By1nzpj/bCNFpkKjmDmTVY2p7wr4hMU3/tU+809z6lhHyiV7eKeV/ipn5xO1a/psJ3xLxeYL71rEmTA2F5SMz76T0z1+U+ImFLNCpP9AXCpjK3mBhqsoHURQl6xtDYmj5FjVNuTZD96/kt9GUuqu6ybHXVkcoeHihW9lRP82WK6sXKGIGfVr5+opRTP5xyVswdkkeMualR9P6HwH3wvb1X19psRYVQd6EO48eRNYuWWz2ZoHiZ9d8xvxL5TaY9sXq1sb571U1H09I/g8ZaRlVW99dSWQmfdaxJ5YPrVWaIrO1dF5QtMFFZ69kyImsdw/Lz9K1i3p9vg1T//fuJ6CX6efzvch9W8+C9vR03TsxvkTHGtajatBGnE8jepNXpCISrVx5I6zBSX9L69OohOL6mrCUo0uY7Az3m28NjbfMVzZ9pkeA5M7pnkOppmhRb5yVxX/RcGY3jYN7LkP+UYZ2/+6DmvYyUonkva86R8940kb/d9MftG03YPr6ZUva8l5FybHkvI6XseS8jpex5T2WtdWMidCSf1C41H50l9jdR48aYDSYUcGemhMZbp7VE5Hj/SZh1TZbo1TLVNf99QN7bmaD5r2HZ8t933J+J/sSaP61+/Fflv86J3rcwl34Lf+bmv2LfjTPmzMi3tFf8dDhH5FvY813V0r+NXU/MEfOmxv++O3JfwdCyfA/H6wLde1CxqG2ob5BNb1g0XHAaUVI8XP55Ox1E/jzTiv/dUWeiLGFUdx1/HN0x7iOsZQtZe3zU1/VTXcR8k2mCy50I1TjUOpSt/k2C20Q+3TRQN+uJmzlTJms4UuEikZkovUlpuDUSeutEjX9ui5YZkZ1LiQmbZqhpqNakTSXD2DWp8gIqA8FJqBf5PRlOQWWinktAz0u/MuxfaMvrbvwla/wF05Q6XK7dTjQeX4JuXZmWEEhTPdjTklf9s6yaiPzzzlD+P+g4ch5VxKg7uL6QmqeNUzuYvmoWrDt5irXuFFn7vpj2ulPlg3Vn/uQ8W91Z3G2jsl751/wzUGQKnCYmxr73RoK1TvX7+taLeRenmlnEt38TevZm+OvyN4tZb9rr95tHzSz//f5JdV2XL3LBe3u93Frceczpjg/vcGKK50X/vdZW5B5yOvONfZsTq+8M+SaYxQmS0p6N+H4e7SSZJk5pMiPETzeY2vi7L/m5mu4HQFtW+iuzakodTv0evR8Fe+jvqao/WPbtdPV/Wh739xYsUZ+jZ63PSecSexBq2vvPUn0Nt00vWJ6W1zZybXOibY+74d/xa+8kvzwFDporWZ7qaxoNEvlbnJ64ko37h0j3a504jXd1j6esM0nBMoV+MN8fuUyprOb7o5ep3kllL1Miay9TtvKDvLX+9uvPoWJ+Mnk7ZGYTF19LXatn1yW7ZqES+b2+1k2jxO51Tnv+T0d9jlrr+G0lkcdr/rrhfSJ/D09Zo2XPe0asH/+vi0wtysZ11nZUdVhD7LTRe8+NiLR73Lp+Ry1t9yyOSMMnrq693dMCvYra/z8Nfa98Tdfy0wc11OVPbA+RpiXLj/m5yo/EsZSVnlpWNtQzcuU40fZEtr57chJtZSU3a0o2vyzvIC+PFCRG66vBrolZZdo5IU0vdZMnpQXfQaJf4lxDaRB6aTiqRlUxtZQftat53LdLKO3lB3lL2bSXH2SP8dxalS8tL66TcFQzDTWu9oh8Bac3uXwuv1ZRe79ijjPfihs6BiV2wlrOvPs=
*/