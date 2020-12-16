// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_QUADRATIC_B_SPLINE_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_QUADRATIC_B_SPLINE_HPP
#include <memory>
#include <boost/math/interpolators/detail/cardinal_quadratic_b_spline_detail.hpp>


namespace boost{ namespace math{ namespace interpolators {

template <class Real>
class cardinal_quadratic_b_spline
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // y[0] = y(a), y[n - 1] = y(b), step_size = (b - a)/(n -1).
    cardinal_quadratic_b_spline(const Real* const y,
                                size_t n,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                                Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
     : impl_(std::make_shared<detail::cardinal_quadratic_b_spline_detail<Real>>(y, n, t0, h, left_endpoint_derivative, right_endpoint_derivative))
    {}

    // Oh the bizarre error messages if we template this on a RandomAccessContainer:
    cardinal_quadratic_b_spline(std::vector<Real> const & y,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                Real left_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN(),
                                Real right_endpoint_derivative = std::numeric_limits<Real>::quiet_NaN())
     : impl_(std::make_shared<detail::cardinal_quadratic_b_spline_detail<Real>>(y.data(), y.size(), t0, h, left_endpoint_derivative, right_endpoint_derivative))
    {}


    Real operator()(Real t) const {
        return impl_->operator()(t);
    }

    Real prime(Real t) const {
       return impl_->prime(t);
    }

    Real t_max() const {
        return impl_->t_max();
    }

private:
    std::shared_ptr<detail::cardinal_quadratic_b_spline_detail<Real>> impl_;
};

}}}
#endif

/* cardinal_quadratic_b_spline.hpp
/m63lc7R+/RfEvOGpu97rPmxz8R+kfTIa1x9D25Q0+NQOD1Kl0py1K1NOGRND9ddyWLewJoeh47dJkyobxz7aBwT1ccumuedUY/L4WCfxLEin3NXJStKafq88TR7sGPFbnvCapefjQtr+GPqEH7uzqSf9knY3k6vHvafq2+56skIDXuOCbuIci8oLCupsQ6PEru9reHGny+c7qFwL9Nw35BevVw9KP+65FZpudoSDjcdV93rGW7s5Urj90MxDVrLlbp11aO6z8frUsZO1Piu1051n4b5VdR9xHdPOL6VKwpWlayoKFGB7dXGsaaMHRS7P2LvU0NzFu0Gn5xFs8tGMOliH6fuFdNfObuxnUHU4o2bF9kvFHBGY7OUeemtTlfjr7Fjn5Oa84MHxMZT7MtqaJ3XusPGPIC/VsgsIDIuf1PdP4x7q8wFa57bv7lg19aWmjnucknDQfSwQdr9VDP2PiSuHnS64nIyrcMa2uobSWvv2LublrNPxP5FtAUpzD0S0E92hsOJqBmohezy0vNQ6vcu99ylnvc9lNvue9DzTfaxZjIkrdHXtEYvzVNmxU9LPb5M0kjcV6vHiemOPA/o+OH+SP8g9tcySZYyXWO7+YHYu5v9o7H2PsNnzWdThj8R8zvYBxtnrd/GvcmzUJAqTDn9TN3fIG3c5JSNaK7D8XVZpEufuGRmm+OC47hsoHm8nB9KVztbsLM5ZCc1Lj6xSaxV/n7iF2w3Qukd7zftvbxP8Jt29L9Cbn/XFD/603KfCZx/9r0zdl8zf9P2h+/r9c2duYjK7f9iMis/kL388sicfjV8GXWt/v0Z6jr9e46PMq9/n8ffsq808k1bx8yrPftKO+u+0i4wE3aNyLT367c5/ba8Gs5E7dO1gp4qg38gzIWDYB4cDOfC4fAcOAJ+B+bq/uFR8Go4Bl4Lx8LNcAK8GU6Ed8HJ8F44FT4A8+BD8FT4CDwN/hWWaHjnwwZ6HqAFXAh7wFLYB06Hw+EMOBLOgWNhGTwVLoEL4VJ4FlwGr4Tl8HuwEu6AK+FDcBX8kZ4neA6eA38Dz4UvwfPgPng+3A/X8v/f4HfgO/ACeBheCD+C6+Dn8CIYr+cNGsNLYBq8FLaGl8EMeDnsAL8Lu+v5g75wAxwMr4bT4PfgLLgJFsJrYAm8Fi6Am+GZ8Hp4NrwBXgJvhOvhzfBquAXeAm+FD8Hb4E/h7fBpeBf8Lbwb/h7ugH+CP4FxFLgnYTz8KUyBP4Nt4FOwPdwJs+APYW94P+wLH4KD4cNwDHwEjoOPw1K4C66Cv4DnwqfhOvgM3Ah3wx/AZ+E98Dm4CxbAF/X9sIyj9bsGTNN6Euuqe531XE83GAO7w0TYAzaBPXW//sDItwLYVv0J2T9B/emr/gyAqXAwzIBD1P24yNwa9lL3caih6j5H3Y9S96NhSzgGtofjYU84AWq8mKtq/bfEa6qem5oGm8LT1L/TYSac7orXIfUn0RKvj7Ud+QzG6fmPIMSJuM8zcyzaGnXfADVK3Z+j4TgPNoTnw0bwuzAJXgDbwcthZ9U/DBeaORBtjPobcj9b/Z2l6TUHJsC5MAhXa/6VwDS4ALaGpbAjXAyHwjI4Qu1H0mGL/l5rSzrE6O81gOkwHraCCer+kBnv0paq+5D5m+r+RSdcvl7W9ngv7AJfgdl6HqOvnscYAvfB0fA1OAW+DqfDN2A+3A9L4R/hKvgneCH8M1wP34Tfg3+B18C/wq3wb3AbfBvuhAfhg/Dvev7rXfgzDedz8DD8HfwnfBkegK/qO2akmY714AMabzmrrvFOIX38MA12g01hD5gOF8BmcBFsDithC3gmbAnXwVbwEtgaXgfbwJthBrwVtoU=
*/