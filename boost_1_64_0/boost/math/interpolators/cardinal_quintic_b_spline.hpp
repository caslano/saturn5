// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_QUINTIC_B_SPLINE_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_QUINTIC_B_SPLINE_HPP
#include <memory>
#include <limits>
#include <boost/math/interpolators/detail/cardinal_quintic_b_spline_detail.hpp>


namespace boost{ namespace math{ namespace interpolators {

template <class Real>
class cardinal_quintic_b_spline
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // y[0] = y(a), y[n - 1] = y(b), step_size = (b - a)/(n -1).
    cardinal_quintic_b_spline(const Real* const y,
                                size_t n,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                std::pair<Real, Real> left_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()},
                                std::pair<Real, Real> right_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()})
     : impl_(std::make_shared<detail::cardinal_quintic_b_spline_detail<Real>>(y, n, t0, h, left_endpoint_derivatives, right_endpoint_derivatives))
    {}

    // Oh the bizarre error messages if we template this on a RandomAccessContainer:
    cardinal_quintic_b_spline(std::vector<Real> const & y,
                                Real t0 /* initial time, left endpoint */,
                                Real h  /*spacing, stepsize*/,
                                std::pair<Real, Real> left_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()},
                                std::pair<Real, Real> right_endpoint_derivatives = {std::numeric_limits<Real>::quiet_NaN(), std::numeric_limits<Real>::quiet_NaN()})
     : impl_(std::make_shared<detail::cardinal_quintic_b_spline_detail<Real>>(y.data(), y.size(), t0, h, left_endpoint_derivatives, right_endpoint_derivatives))
    {}


    Real operator()(Real t) const {
        return impl_->operator()(t);
    }

    Real prime(Real t) const {
       return impl_->prime(t);
    }

    Real double_prime(Real t) const {
        return impl_->double_prime(t);
    }

    Real t_max() const {
        return impl_->t_max();
    }

private:
    std::shared_ptr<detail::cardinal_quintic_b_spline_detail<Real>> impl_;
};

}}}
#endif

/* cardinal_quintic_b_spline.hpp
P4Dt4TaYCbfDdvB+1S+ux3mKqDzmL39W4ouek/hvOx+x8B9BZz1qJ2o3aj/qCCr5cNDpghqFmodajdp8OHpWIvpEn+gTfaJP9Ik+0Sf6RJ/oE32+zc/Xs/9fb/8/DrL/b3Dt/3/fpzKa9NtZESo1dO/8W1V7yUdPOW3y6FNGTBs9Kn9BSWW1u//MOv5wsd/Fvt9MzHziroms/a3AfKT8Lbt4xTxT9cIB2ih6DYwMSpusw/liJ1nffeom4IisQcx34tWNxDWxcTezlnsT75H1wHjHPHW6YzAUDsLM+wpZ58vVNNyv6yKR+Mi+hmH8fo1pGMrME/s58jukiaydlq/g1ZZ+6o/Pne7W9VRjz8S17vLoCAPxkjB47lMsqHb2YG/AyOXjwRzVgvKyxx7Xikh5GVDzXZG41XCb/eWrbPEz9tLJ3zdD6xqE5eZQ/vpjEpMCjon3LZE8rtedhJLH+puyBlwtj3dh0SuXcOVQvmvWFG+Tx8eO/yFP/WC/hS3+xp6JZx3yt6Y4ajmudgfljtijy3EJEU1+2xrHymX5uVO0DEfKZam9DKsf/Kfy3vmr0H4eSO264/n9epzD0TJb6rj2S/B76PF7HvmeR+J0XQWVgDpJ7z7NdsV3/JRpo8eOPkWuPXXdCWravX5i17o/C3+89XaN2Sc5UMx62OKPu9r3F5aIeYJp95bKu999ZqFkgUve8Wgx74Z50HXP6rH3JHruK/W0C2uqpeXmBvZ7Vtda0pIrVo95vyrujsv9qpHw7dXGfpr2c3naz220hI8G2t3WmnS/Rexa5friT+193BOYe/u4194+dh/3AHbcfRxuTB93E2m+iXhtCbWByelfSR8XaRueTLD3cc47tvTTxq+O/ZvzTt36N+edr65/i8RzW8Oj41lOO59ZQzxXSkTD8exwjHhm1jGemZ543lqP9q9D7fE09eGmoL0fz7HEk87smH1Yzjt168OxZ/rwHaT1DMLxy45fbR8eydtzEu19+DxrnLUM16H/nvdO3frvee98tf33DN0fv1j3H0xHVRC/tfb4admtFj8jK/p2cTPU3ja74tuh5vgae+3J67WJ6BG+20JtVXzTYFJcILFBbLBLnD+xaWpioIXrLmmpS+s7yX5ATsJUycVviT+ZjQhDEuEL+RPbIbgEDxrFOiYsCZ5293oJw3AnHb0UDf/NoteWNEyo1h7vFH3Rk7YWu0Yvydx1smz+fNc5gW1iPlDKakh55eLH13rmyp63HTRv3ePuUY1rGJsdPDpvZWBW13HZwXqMyw5+teOySDnul3x0XP9GXLPDcc2dEoqhZzTqaHzPdsXBOiZzxXeAK22s4zBPfLfWI75na9zc8R3gSgN33mam2OOb54mvyeE6xjWvHnHN+4rjGtlrH6+R/K2Ow15APTmMPjYc19C3jtrGD2Zf+KNiv9BJYcdWD+sZJ/HTc/d9oTXuas/UceyxYdsufwC7nn37jLVtsgc8v99Bx4QtXW3THWJ+KenUhD2NQWmjUiPnJsTseqcNPrnbqB5/D+knmjFjRD7/Ha4zn/F1yDPLeEj3rheac5IrUbyTFt67jiTOZryo7VW1fO7YVO/N03NJl6N+NkwEs5p8rmX8ZMa/n4r9Rtb8xS9v/pozCj8Ws1FOrP3MEm6teW7uzdgg5mc7nfilAShLWcAPe/6maoK/IeYtcJ1AOY2RfGymZgfFjLuRRE/PnYheG/xprGXBJ3b/LPrd8SVR7dM3Gf0M0efsguTFS6I3yHU3V6np018Ws05ax+3lJbke48qay0vtZaNSB51dtQ3ogtpF2ch5t6pslK80ZcOcMySPTFymiN1mlnKh/vCfd0yQohEbJ+Ztq9W3UaLXkpQ=
*/