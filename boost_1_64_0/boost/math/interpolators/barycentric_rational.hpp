/*
 *  Copyright Nick Thompson, 2017
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  Given N samples (t_i, y_i) which are irregularly spaced, this routine constructs an
 *  interpolant s which is constructed in O(N) time, occupies O(N) space, and can be evaluated in O(N) time.
 *  The interpolation is stable, unless one point is incredibly close to another, and the next point is incredibly far.
 *  The measure of this stability is the "local mesh ratio", which can be queried from the routine.
 *  Pictorially, the following t_i spacing is bad (has a high local mesh ratio)
 *  ||             |      | |                           |
 *  and this t_i spacing is good (has a low local mesh ratio)
 *  |   |      |    |     |    |        |    |  |    |
 *
 *
 *  If f is C^{d+2}, then the interpolant is O(h^(d+1)) accurate, where d is the interpolation order.
 *  A disadvantage of this interpolant is that it does not reproduce rational functions; for example, 1/(1+x^2) is not interpolated exactly.
 *
 *  References:
 *  Floater, Michael S., and Kai Hormann. "Barycentric rational interpolation with no poles and high rates of approximation."
*      Numerische Mathematik 107.2 (2007): 315-331.
 *  Press, William H., et al. "Numerical recipes third edition: the art of scientific computing." Cambridge University Press 32 (2007): 10013-2473.
 */

#ifndef BOOST_MATH_INTERPOLATORS_BARYCENTRIC_RATIONAL_HPP
#define BOOST_MATH_INTERPOLATORS_BARYCENTRIC_RATIONAL_HPP

#include <memory>
#include <boost/math/interpolators/detail/barycentric_rational_detail.hpp>

namespace boost{ namespace math{

template<class Real>
class barycentric_rational
{
public:
    barycentric_rational(const Real* const x, const Real* const y, size_t n, size_t approximation_order = 3);

    barycentric_rational(std::vector<Real>&& x, std::vector<Real>&& y, size_t approximation_order = 3);

    template <class InputIterator1, class InputIterator2>
    barycentric_rational(InputIterator1 start_x, InputIterator1 end_x, InputIterator2 start_y, size_t approximation_order = 3, typename boost::disable_if_c<boost::is_integral<InputIterator2>::value>::type* = 0);

    Real operator()(Real x) const;

    Real prime(Real x) const;

    std::vector<Real>&& return_x()
    {
        return m_imp->return_x();
    }

    std::vector<Real>&& return_y()
    {
        return m_imp->return_y();
    }

private:
    std::shared_ptr<detail::barycentric_rational_imp<Real>> m_imp;
};

template <class Real>
barycentric_rational<Real>::barycentric_rational(const Real* const x, const Real* const y, size_t n, size_t approximation_order):
 m_imp(std::make_shared<detail::barycentric_rational_imp<Real>>(x, x + n, y, approximation_order))
{
    return;
}

template <class Real>
barycentric_rational<Real>::barycentric_rational(std::vector<Real>&& x, std::vector<Real>&& y, size_t approximation_order):
 m_imp(std::make_shared<detail::barycentric_rational_imp<Real>>(std::move(x), std::move(y), approximation_order))
{
    return;
}


template <class Real>
template <class InputIterator1, class InputIterator2>
barycentric_rational<Real>::barycentric_rational(InputIterator1 start_x, InputIterator1 end_x, InputIterator2 start_y, size_t approximation_order, typename boost::disable_if_c<boost::is_integral<InputIterator2>::value>::type*)
 : m_imp(std::make_shared<detail::barycentric_rational_imp<Real>>(start_x, end_x, start_y, approximation_order))
{
}

template<class Real>
Real barycentric_rational<Real>::operator()(Real x) const
{
    return m_imp->operator()(x);
}

template<class Real>
Real barycentric_rational<Real>::prime(Real x) const
{
    return m_imp->prime(x);
}


}}
#endif

/* barycentric_rational.hpp
mQ1Exqg9qUsN0R2qchB+Bye0rKpD1Bf06ifz4NUEU1fMuI3yKOO2SD2hTPEuZUrrCfSMac1YVcPsrhM7GzvyXIUKivz/cJ3IDEqdKK6lTtjKO+6s5d30473E/Dxnpt79H2/ctHCXd+NPqru8L6hcaJWp4rLvlrFBO2HK3yliPhK7fupeO7Wndz+57ua31AFx/31xn2rd5zlXzLLwOdE1hlpdVFZQUaHhlTbQVTZN3AeJ29WmXjuuudcR173LSzPD5ebejuGyk2gf45uyUxasX9lJ95QdTWux+76RYUFaqd1PjZ6Jp2ddUeRfaBzUT8/4/vnQvyojvDVsDPcRxv3hslfap6Ba2fPuuTZt6Mdi/9/OdPr+W1CvWPdeq786x5yqcy6V30IhCpl8yOg2jfYgxfkNytYOqx/ucmDKyCbxo4mZV3SS9+1OFrGf57Qz/cXFop8kfpTrHuCWahYjZu874/HnAty84CTXuPc6nX3BD1J/M/nxX6ESGw1IZLhm1oa5t1D2v6aqvVERe8lr13rtqEw7aauexs7VWULar+O7r3uqzjut+7rd82ipJ/ih8+gy1N3D2AvXSMuGZ+7nylPT1pwmdhc4RXrvNWFS90vorSeZfFV90358bNqtqj5wuZiPsZYJdVv9DkvX2LQ5XCV2cjz7vvVOTDGT9jCcbvI+ycydO9GPdEZ5586J9rm9O40lrB+bel5lR2XUVEvzhXqZezP1NB31Li/7I2le6amPWn51/mqvc560Ebt6d6ctLbHvraPW9t7YM+W41m8LE9zfhso993Kb8aYJm97JWZWWZj9E+bdoP8S7sh9i34z+pz+9+eT991x+ywMjJmSe8u3fDzH/PR/6vbt3v3/bZ4tmpw0f2Tu2tOvV3559Enb5TXXbQx5qv7fB7SiRaxP5dgrHWO6JWaD3biyCKXAxbAHLYDu4BHaFS2FvuBzmwhVQ78PRb470W5b7cPKw54MnwwR4KmwMp8NMOAP2hzPV39lwHJwD58C5sBjmw8WwAC6HhfAiWAQj8dyv4RhiiedI7IU4BqbBsbA5HAez4XjYB06GfeFEOFjfD8ONfv0Opt8bt8Gpru/z3ZxwunWH7WAfOBL2hWPhnXA67Adnw/5wERwIl8BBcCkcDM+HI+CFMBdugCPhJjgaboZj4FY4Du6EE1RezVT4NDwZ7oHT4GvwNPgenA59PsowTIGzYQs4B7aBc2FHmA+Hw2JI2RD/zoKl8Dwoe/DhMng1LIc74Ap4L1wAH4MVcBdcBZ+Dq+Hv4Br4FjwLvgfPhp/Ac2DQT5sIO8HzYU94AewDL4Qj4Do4AV4MT4eXwnnwu7AQroeL4RVwJbwaroHfg5fD6+BGuBneAq+HW+EN8E54I9wGx8Ed+v6gvj8BJ8Jn4ST4SzgDvgzPgK/AxfAvcAn8G9wEA5Sb22AQ3g4z4c2wC7wFDoHfhyPgFjgJ3glnwWGwHG6Fq0Q/XC7LfTo/1+8W22B3VHFIQ++TagTfg0Pg57AA/huWwFitV3FwNWwAL4DxcB1sCC+BQXgFzIFXwUbwOpgE79X3B2FzuBu2hC/DtvB12A7+BbaHB2FH+BHsBJMJa2eIcrrA7nAoHAOHwSlwOJwOk+EcmAMLYGN4vupfpPqXwRPgFbAn3Ayz4W2wP3wUDoC74ED4EzgI/gwOhs+oP7+E/9Byehi+K/raHpg5JXNjbW8ao0gzeXbrmZIXYGP4a9gf7oGD4G/gcPhbmANf0nbi93ASfB3Oh2/AUrhf24lX4AXwD/Bi+Cq8Qs31Hjqdg0gaH3UPHXkl7e59sCO8Hw6AD8Lx8CE4BT6sv/+ItlOPwuXw53AtfAxuhI9ru7QL3gqfgI+qvWc=
*/