/*
Copyright 2014-2016 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_INTEGRAL_CONSTANT_HPP
#define BOOST_ALIGN_DETAIL_INTEGRAL_CONSTANT_HPP

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>
#endif

namespace boost {
namespace alignment {
namespace detail {

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
using std::integral_constant;
using std::true_type;
using std::false_type;
#else
template<class T, T Value>
struct integral_constant {
    typedef T value_type;
    typedef integral_constant type;

    BOOST_CONSTEXPR operator value_type() const BOOST_NOEXCEPT {
        return Value;
    }

    BOOST_CONSTEXPR value_type operator()() const BOOST_NOEXCEPT {
        return Value;
    }

    BOOST_STATIC_CONSTEXPR T value = Value;
};

template<class T, T Value>
BOOST_CONSTEXPR_OR_CONST T integral_constant<T, Value>::value;

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;
#endif

} /* detail */
} /* alignment */
} /* boost */

#endif

/* integral_constant.hpp
GPUfcDYg7imuW6v3tTIgJTgIdUf8A1H3SFV3f7Pu0ah7uFuPm0igiAIbN4BNPc6PQtdz8Xz/HURrw7nkS3zYwN9SiDaptezASDAx8ykbknIfE7hmqcyQSno7n6WS/mQSMF1GSw77T6etrYZLiLPgEaerLS6aGrtbIAKzY+imgGBRMwZB72lREHxCd0ygMbfUQeSgQ650bnXnhnWtSzAbu61h05q2+//4f/b00fZT5dLPlnyEB8tXLE9+kG49szuRZoYn353hd2pjugIU42lTepW2Lz0eVHg4Mj8NR5P2micPnoEQ54b1G/3r+eIaiaLdJkl+oGwfciqZu/2CObGnkpq2zoZgwY9DQcN6Lebzf4r1mGX6RpLfXLHFWGTgnuayPB/4L3VVDtD/1OIZk0dnTGkk3N3gwLQv0pBYcRiRQ0oo0D4yzQl4eWkSEpYlHFntO2LFLB4flXpya7s8siAKtYNUcSn9K9NLZjfk9j1CSwivhtw+Z0WElt1S7A3MzyuN8vNI5NgBFps78pLJ0CvTE9sKRl1mZeiVnhiGXqkNQ69Ubz5auHCR85mhF9tRK0PvnKMx9FDU0+dLUX/GG0OxWRDvn7gjNQX53zqXPHzY5PdiwE0bA16sTsXv5QmzzBVOmle2/Tv+NaLXTbjairjWny2Ia04dkmTDYjEwWKCtCkG0rhoL+oop+QlWL8tOACvZPZeX7ankKBeg0k1/wC/oyoRCoUKl0sf2cSQuVfVJAjBeKTqUvP+UFnHAfvMHLXU5V+IifQLWqLBCQRaQ3k4pU71VssNfqfPTA07OFvRd0wk0T4XsVbKvOxCm8q4Aozkd3WISAx2LGAJvgTjlexvXF1rbXkgeMjfZk39wzo3meRW9z7zHhI/RmRgp4HDYBmkUXprMtyHhEwLeRc0H5IS3ZwPih/M5EecABL+FYN5SAWmsucGAJ2QGoVpdBp98/rcsmXw7ULkgB27tLb0U9Qvtj1DIpC68/Gk6VlMeJmxs14q76udxkxL8o/Ctz0Cm4CraREbxfmv2pi0iUA6IDEXB59R+u4jWVldq/0U4wdzOFc+7sTUk1BZi9amcWMhAVQI54hssA4V4gg8tVzsC2E8QgBsygK+CmZ68K7PnJHmCM7Lxqy/3fR2tQeeoqtpDxoKs3Xf4BBnC+p5/x6JvfnOFYZMKZu6wwtiez6d6cd+90SF5T+MR1r05gK/N+bt9CZHq6EivnkFJV8zDl7KwMhUzRKRvt9YaHF5f68CWru5g68LgwNpPKJF5P67vz64iLyY6VmN4LEa5qsBlYhcItwj94XJB380aX9QPX87ruTxa8CouePYTCtiIfk7KSqPToN4U6M/TV6rkgSgUlX3oNyvrHa3s3MaV3SGVdaZ8qOlsqWldOM0daN0KXQw3xz/8Tjo69fZ77xfH+0dTb7XC3/JnwileQLxR2IQvUDJptavT/Kl1bJsjzdd+dZKvNytJWW3Xr3b42jQK1BawwG8wHhuVbmw5YrDLq3c8i8d64pVXWvabkC7zOw0UCbYyt0sN/OfxTKftAoLsYmXL4UKvBjSktf5gW4ryF1BumeKns8XejldbRInFvEIgF+b83XWbMv3d0VCTthLTZLDF3N2VcuEb207wn709SUX/vpzHXlwfaK+J8aKvdD/IHDlvEqFj5mkeDUgmGx4cLrruc2Vnf3SAHFEflAizPtGrfUP5cV8HUOYgMefvjfwSlKnyD9Zep8/rVf77kJ8yVxN6muIl1hWEpmD2nylXwnnZCvYuc+hEhzIWJdVmC7Xqh1qSPAI96JqfWozk0ZG/8VQ+l9IAImTYJaMqnBz4MF6rjiUIYW0/dKYYiFKLuvV0jEFukl8cCQE=
*/