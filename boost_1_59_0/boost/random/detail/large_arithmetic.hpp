/* boost random/detail/large_arithmetic.hpp header file
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_DETAIL_LARGE_ARITHMETIC_HPP
#define BOOST_RANDOM_DETAIL_LARGE_ARITHMETIC_HPP

#include <boost/cstdint.hpp>
#include <boost/integer.hpp>
#include <boost/limits.hpp>
#include <boost/random/detail/integer_log2.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {
namespace detail {

struct div_t {
    boost::uintmax_t quotient;
    boost::uintmax_t remainder;
};

inline div_t muldivmod(boost::uintmax_t a, boost::uintmax_t b, boost::uintmax_t m)
{
    const int bits =
        ::std::numeric_limits< ::boost::uintmax_t>::digits / 2;
    const ::boost::uintmax_t mask = (::boost::uintmax_t(1) << bits) - 1;
    typedef ::boost::uint_t<bits>::fast digit_t;

    int shift = std::numeric_limits< ::boost::uintmax_t>::digits - 1
        - detail::integer_log2(m);

    a <<= shift;
    m <<= shift;

    digit_t product[4] = { 0, 0, 0, 0 };
    digit_t a_[2] = { digit_t(a & mask), digit_t((a >> bits) & mask) };
    digit_t b_[2] = { digit_t(b & mask), digit_t((b >> bits) & mask) };
    digit_t m_[2] = { digit_t(m & mask), digit_t((m >> bits) & mask) };

    // multiply a * b
    for(int i = 0; i < 2; ++i) {
        digit_t carry = 0;
        for(int j = 0; j < 2; ++j) {
            ::boost::uint64_t temp = ::boost::uintmax_t(a_[i]) * b_[j] +
                carry + product[i + j];
            product[i + j] = digit_t(temp & mask);
            carry = digit_t(temp >> bits);
        }
        if(carry != 0) {
            product[i + 2] += carry;
        }
    }

    digit_t quotient[2];

    if(m == 0) {
        div_t result = {
            ((::boost::uintmax_t(product[3]) << bits) | product[2]),
            ((::boost::uintmax_t(product[1]) << bits) | product[0]) >> shift,
        };
        return result;
    }

    // divide product / m
    for(int i = 3; i >= 2; --i) {
        ::boost::uintmax_t temp =
            ::boost::uintmax_t(product[i]) << bits | product[i - 1];

        digit_t q = digit_t((product[i] == m_[1]) ? mask : temp / m_[1]);

        ::boost::uintmax_t rem =
            ((temp - ::boost::uintmax_t(q) * m_[1]) << bits) + product[i - 2];

        ::boost::uintmax_t diff = m_[0] * ::boost::uintmax_t(q);

        int error = 0;
        if(diff > rem) {
            if(diff - rem > m) {
                error = 2;
            } else {
                error = 1;
            }
        }
        q -= error;
        rem = rem + error * m - diff;

        quotient[i - 2] = q;
        product[i] = 0;
        product[i-1] = static_cast<digit_t>((rem >> bits) & mask);
        product[i-2] = static_cast<digit_t>(rem & mask);
    }

    div_t result = {
        ((::boost::uintmax_t(quotient[1]) << bits) | quotient[0]),
        ((::boost::uintmax_t(product[1]) << bits) | product[0]) >> shift,
    };
    return result;
}

inline boost::uintmax_t muldiv(boost::uintmax_t a, boost::uintmax_t b, boost::uintmax_t m)
{ return detail::muldivmod(a, b, m).quotient; }

inline boost::uintmax_t mulmod(boost::uintmax_t a, boost::uintmax_t b, boost::uintmax_t m)
{ return detail::muldivmod(a, b, m).remainder; }

} // namespace detail
} // namespace random
} // namespace boost

#include <boost/random/detail/enable_warnings.hpp>

#endif // BOOST_RANDOM_DETAIL_LARGE_ARITHMETIC_HPP

/* large_arithmetic.hpp
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
*/