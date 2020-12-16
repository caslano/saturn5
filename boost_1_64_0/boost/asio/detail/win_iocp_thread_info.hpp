//
// detail/win_iocp_thread_info.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP
#define BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/thread_info_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct win_iocp_thread_info : public thread_info_base
{
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WIN_IOCP_THREAD_INFO_HPP

/* win_iocp_thread_info.hpp
EE+FF5HDTpHktPi+XR9kC2TGzLUHHtE98Lt1jN6rfOWd5atGX+Zjfm9KKsuLygLepTTPQInPIr5S4uVB/Cp9lrH3XS7xTU3OrU8IzRCdI2gFiXfXdCvepcl59WWhSfWWYXREVXVRZbWxb1kn6UXIVKOPvGWMy4GuOu/SZ7jnnLH1nZTaqCsSs2/xn2d2HwsnfewWXoo9P99s7etPz59YXFxZUlU1tWh9adlNLtuFC3p69/fJa3Tpqu6+tgvQtNx2gTo9tgvU47ZdMPZIx9PVJoqKuoDtwQ0IQE7j2onI5MoVRg9zjXWvyqLq0opyaW9aSGl1XO9vlD98TZhvImj6s9R5m/G99GO5liJ5PiF5eDtS+/J8k+cwT5fv03cJk0f82nH/t71zlNTwBiB555i8SeHRoVug4ZorL89X7udNI4OThO4vofvUJ9xpGMylj3bG9EO32h1ue7QRxDsSz6eP74Dm3VwfDn6AsIuQMZR9IPBOwtLuzd8L1G+LvuuYvjaySv9yXftXn4M+Ide0/7g2zbwXSb+c9a3RatfxH2vX0Xls7PrLnWff1qnNsi0HS2tOtd3+1u7E7ToS9fXxv2wHovvZ8t62Jyz2A9xLzN+885m/md9yHk3WXN+v1/tz/X3698dtNiG11cF7of3tZ+Wrgm1C+tr3VuMs77jSZfnQFdjoUjcEl7fQ/h1speuvdOZ70uqTABCfBMngUbAL+GMwHXwR7Af+xGaTEDX1em0SlquvgiLNvwLM1LixiWgi/880/0ua/ziYqXHjX39DcH/Pt/djHP2TK2tbwe1Zqu1Zpu25DszUuPGBsLH5evYQokpXr3Sp4E6lK1PfDpXgCLAazAU3gOPBjeAcsAZcCG4CV4CbwS3gFvA9aiN0J/ge8CPgVvBe8DbwIfAW8BHwVrWteK/dtunG+ORz143N87uLUK90ryhdF3Cr0h1Q24XHwGzwq+Bq8BvgVvAJ8H3gk+BO8Ijy8y3wU+C3lY/D4NfB76htyNPgYaX/Afg4eFTjRi5qmuczL6TvD+AgH1uQ76tcPKty0aDj9xzYX69bNjJ5Ws7dXhsZsSEZCN4JDgN3g9M1PkNtUwrBu8E1autzI1gHbgLvA2vB+3X8PwluAx9Um6y9hm993tTn3OMuvtGHQrffes7TZ0XaK2sTDyjdYNUPF4Np4CXgILWNGg2OByeBE8BZ4FXgEjAPXAVOBCvBSeAt4NXgDnAKeA84FXwYnAk+Cs4CD4DZ4JfA4eA3wCtAnmElvYaBmXZjEvKbFJeNyGbo9hAsnx7RlEabka1gE749gvx6qA3J2+Pb47z59bgy6V/i2+N/ya/H0c/9Z/j2OB9+Pd763Pn37XGutjPn07/Hv8O3x3+bX4+D6LyjhNOE1BrscQh5hGLCVsI+wlOEY4QzhPSbkkI5hJmEYkIt4W7CIcJxQuTmt89Wp/XX+mv9tf5af62/1l/rr/XX+mv9tf7O5fevsf+vLLlBzP/Pzf7fsuU/+aax1587ZU7jGYB+egYg74+ONDXlJ13zZjrT5bMhFCC+Be8lf4M33XEeYKPNt+Bhn/MAT46hDTcYG1NTiP1MwMtXOGwaoE/IPtxhg0FZHt+C4wLOBByPetuVyLmA/D8F+xbc63Mu4Cn6IurTFy09G2DZiOX6nA34JnXVOesy5wMqujtsZKBr+fkAyvLYph/xOR/w4hXIkqs9KgLaJrsMQHsOMkBZnnMh49r6y0Co0tGmhOy56/7oGX9TX11bH5tL+iDVWV+LbLqtOvb4nAH4dmy+VTrtOqlH+vjxS519DF3Tts2Vzdg2V7bcpvPxSxO36Rxr8e1jK//d2Nzy8i3zy5Kxwy4bt2gz/Eeb4T8=
*/