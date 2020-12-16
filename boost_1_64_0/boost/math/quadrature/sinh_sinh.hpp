// Copyright Nick Thompson, 2017
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 * This class performs sinh-sinh quadrature over the entire real line.
 *
 * References:
 *
 * 1) Tanaka, Ken'ichiro, et al. "Function classes for double exponential integration formulas." Numerische Mathematik 111.4 (2009): 631-655.
 */

#ifndef BOOST_MATH_QUADRATURE_SINH_SINH_HPP
#define BOOST_MATH_QUADRATURE_SINH_SINH_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <boost/math/quadrature/detail/sinh_sinh_detail.hpp>

namespace boost{ namespace math{ namespace quadrature {

template<class Real, class Policy = boost::math::policies::policy<> >
class sinh_sinh
{
public:
    sinh_sinh(size_t max_refinements = 9)
        : m_imp(std::make_shared<detail::sinh_sinh_detail<Real, Policy> >(max_refinements)) {}

    template<class F>
    auto integrate(const F f, Real tol = boost::math::tools::root_epsilon<Real>(), Real* error = nullptr, Real* L1 = nullptr, std::size_t* levels = nullptr)->decltype(std::declval<F>()(std::declval<Real>())) const
    {
        return m_imp->integrate(f, tol, error, L1, levels);
    }

private:
    std::shared_ptr<detail::sinh_sinh_detail<Real, Policy>> m_imp;
};

}}}
#endif

/* sinh_sinh.hpp
n3MVcn4Jj3cdMPUd/JvgX1/GSqB9NtfLrWg3hPWbURUH18FM+DeOfbkf+cjl8eYgb2dz38cES1f5eEqwtEPYv/mI9yvO+QLkUt0NWARfBqj7f+B183xbir4+1nQ56nk6j7cKWFterz6CprVYlwrwJqrv/4JXnXNuRg15ue834DhY3f+Dfur8dxe0Ut+Z+hmYWtdqy8/izzkfScAG8BrRSH661Fxt2gTvAazBwfKz8kxew1oA68XYkfIzEOT15Vj5acvnOjhBfkbUWYJDfjrUXnM3+KLucfeQn+X56v6f/CxT/3+GPsB+5rrqJz9L1F79QGBqr/R8xHEt5+NC+KfuVlyCOA5hnbPQTn0m58pP+6scm1d+OpdxbKOglcIKoYGLY7scHFdzjop/4eo842a6uig+j94zRI02WnRGJ0hG7wwRvYzeGb0zWki00YKQmOSNRASZJBKdQfQ2egtGr4lB9PbulW9rffHh/9vn7L3X3uc+9557rkG+azi+KfZvaDTn+3l6nDNiNhv5yv7QfLB9HMtiMLlmf23/esfJ+T/kO5fzXYF+ecVrcDVq2ZLH/gpN5R3zuvQ4X8xsM/w24LHbMbYva7Ab+Z7iPA4gvijnEYWmWdjHSfgtymv1HPL4mOe7BO1/5/muIRZ5p34b9ZDnwX/AnnPMj+AjPa+jZ1i/K7kPXqM3MjFLlMHYXr5GJDfmH8tapTHmHcjX0/TG8su76MyYT/YEsxuLybp0GQtd4/kKGHMJK2Is2oj7oKQx3zEHsbLGPGPYRyXELM9bHyK3K6xBDWORUbL/Zyx8jXVpZCwu72eagcXZrqWxgOTRDvkmZtYJfuXMcXfkIfu2fYw5JrFfPzRNxbkNRW4S8yhoIGeYxyPmhcwmw+9OZp+hls/k/J8x93KOZR5iqch9vwi55Zf9P+SRmNm3xoJyH/YDWBruq1XwsV/O/yG3Ntynf6Bun/Ba2ATtB3BuEdjJO7ld8Cvvy/Yj32tcoyPIQ2p+wtigMRzzWfjtzmMvoje+YnYVLA3Hdwv5viff/2I+eVf+EGPLsd1TrKPL8v0v8u3A+Sa8a2nIGYdkxoJyz5/amEf+VjiN2cfHxDIZc+6R83/GQnLfmRvssZz/M+aT8xGFjbm2cv+VMObuzL1Wxpj3ImtQ0VhYzrJXRXzuJMSqG4tu5/jqwIecIWhoLPIjs6bGAge5n1vAx14HsbYYW5/H+oxllH2zbsh3MNe3N3T+nrUfALvpbDcEtZTeGAl2hOMbh9yaMZtkLHaHdZmGemyU73/RG9W4N+ZC+64c30L0i/TVUsSch69/3xjzyz7N96jHW+7dn+BXzm2Goctoju931EPeJ2/E2IfcQ9vAHjH7E35vy/4feqg653sY+sm+93Hkm4TX1hnoJ88VF+DXzzpfAevJY2/C7wzW4B78ylmrB6ivxPwEa+ug7P+hRp2o5tZ8pn021iCpMbc816Yy5pX7sHeMxfqxzhmNuVLwfNmMReX8UC74XcYsn7FIC+6hQrCT82bFjcVTcc1LG3PI9aoC4ivCrApimcU+qoE9lfN/yPd9vm40MBaUvzNeY2E5L/CJsZCwNtC0luz/wYdo1RX5Xme7Xsac1Zn1h4913C+DjXkS83wj4FfOfI4F+5+c/0Ms7ZhNRT2ycB4zoL3ce88x5rvBNfrCWOAIz7cEPs5xPULwIc8uy1E3J+e7EjonY7uf4aMv57sWPuR6sAH6RXnsVtQ8yPXdCR9t2e9e9LOcST2EfA/yfMeQR6kEYqehc3n5/hd28q3vZdRtHrMb6IO13JN3oX1lzi2OPC7zunz83/rIQOwFmJzJfwtd/uX4kmTCu1nWNKUx/13WKp0xzx1m7xo=
*/