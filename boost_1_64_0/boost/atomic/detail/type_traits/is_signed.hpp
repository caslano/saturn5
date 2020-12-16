/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/is_signed.hpp
 *
 * This header defines \c is_signed type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/is_signed.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::is_signed;
#else
using boost::is_signed;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_IS_SIGNED_HPP_INCLUDED_

/* is_signed.hpp
WKQc85HgBLWTo8FJ4ETwBOWan6TlvSNy+lxBn1E0e3z+DpX6EAdTwWKXXLPKdQ+QO1bljgO7gSeq3BTCLpUrULk0cLTK9dd2FoA54ACwj8Yd+X1x5Aep/GCVLxR54iofdX5/AneqfCZY5Tw/U33O0PE7C5wCzgZPBOeApWA5WAbOBc8HTwHrwVPBq8AzwI2az3AT9br5hGiKm4OHvJubmGC+7N3ufOEcxpIE85W58jXF4yYmmG99gvma28lXnp7gHsiHib+Y9PucmN/nw+HzGV5kqN/nrXcm5vu5I3zJQ+n/GQ5lwj6gP2z/z3AtO+wDuuzxdOVgHlof0DYns+bx9KQvaI8v6CZ0spnwBGE/Ie/77AtNOJdwGWEz4QnCfkK/J0gjLCGsJTQT9hLeJ+T9AF+BP0hyO5NH8kgeySN5JI/kcfiPfxv/P7qy7lDx/0e5+P+7lLf+rPLjHgDPsrk2zW6O9OlnzlxQThVqhZgQtBcr70dUZqrhPH5K4p+LdDecgHpJm2fyjjf+1S+W+FcD/UrXmPxjJb6ceJ3Eb5f8fx+jPqJcvvgvkvTbIl7fZfn8lb7NTvst71ReMn6ru8i5u4Vvls9fzRKfzzOnbjzTSkGWfOb8Ajlvl50rZS83PtQ2ynXzDd/FcvFd5tg6FvkTDYc+W+K/t/pyzvEfz7JZ+RxNj9j+49Pm4yU0hNOWrzK3pyhnIrOpJSs1z/L5ANV8z6UoX67bmkVZadMoOL5f+vdTlLPWc81nwnzJD0w1eaLePMpJlT29H9Q9vvmbfWlBsAQcr2EC4WjCxAT8jNo8hXe2+f1Bm31olf+x0HBC6pXfFs47a+mq3KE0OLPgftpVY38Lc3/s9wKnzV8wUwdD+L7EIrMzVceGlnGs2Mw091gwaSPMWNgu8U0Rx8dx+QPCHU4ZYy0MGx9axjFmfDwu8Z+kujnNVNeMzesfcHipxM01ZqScZK0L9A+YD178LfGRqfGIdYnE84L41aYta6TchaFtGdDKaamwXHV78P7WucBftxkRF9+6+hKXzCOS54TA9rjmANOWSql7N4nXI3+y5H89kqttGy/ppTLOcyWPc26mb+zn69h/Rep9RMqxPPl/EgtzOPh/lbKHKOfer+sh0p6Kle59pHdLWU+l2mNsTyrjlnF6jD2+h8+XeWIJ8RbCZM6lnpk5JHNi5oqM1Ky0bjo/XzRO+PUxPpt/I2WOkboPVX04Nvg7tUGHszpIr9u1i/pwTFtzL06NgWuz0ruEzEUqU9JFfThmrXkxK7WPby5y2lTelm+Pb77SPGu7OPPVFRuz0o4Nn680/5Yuzlx0xUNh132qLc/XvHluIE6V2DubsnS+sv/+K/i+/v0DMjzoSvsewdl3+xYCKPPaFAJ/O+elvGM95xSZC2UOBP1zYXVRYvPhJd9KbD6cluB8+Jx+A0N2DtpIGMnEuPkhMx/Kx0P69Quw0owLuBPKjdP8lGL36XPMseu6id3i17pL5kiMtkeaz2bNHgt3ieww5uNIoN3eLenFhiNoxdORcjVzpb0NjNusnDqu2TIkHflKuxWLGyuWx+jg5e7BOtjn1sHK5Ytbv2IQFQTqYJ9LB3tp/1XdE9fB79rRwe8PQgcF6KB+HJGhtg60FSjB+y3dq5nBeijc7udLtmcPyBhd7EMPN2Ymrovh2+PrYuT2hHQxN8weolwzOkR0YezBzSU6kMU/7neJhBXILGnVQ1X94salFcurJ9B27oWBtqB5i7xtNG1wpw8VWbwDa3qZK93VfqOfCjsN7Qzk34623+GOUyfiqnfljg+VPNTDw6MsU67+AeXR/oKwBPn1241/W5kjaqt0xRT++0Flxpl74CMSf4R2Olw=
*/