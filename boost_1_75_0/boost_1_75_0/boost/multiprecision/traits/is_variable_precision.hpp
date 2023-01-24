///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_IS_VARIABLE_PRECISION_HPP
#define BOOST_MP_IS_VARIABLE_PRECISION_HPP

#include <boost/type_traits/integral_constant.hpp>
#include <boost/multiprecision/detail/number_base.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class Backend>
struct is_variable_precision : public false_type
{};

template <class Backend, expression_template_option ExpressionTemplates>
struct is_variable_precision<number<Backend, ExpressionTemplates> > : public is_variable_precision<Backend>
{};

}
}
} // namespace boost::multiprecision::detail

#endif // BOOST_MP_IS_BACKEND_HPP

/* is_variable_precision.hpp
Xvg4mOki4NMSaegt7zRmukSiveV0eVh/faaDYWju+cl2iea3mQPwVUDNjnlJtKLdaoUG6anTYFqbiIZCzebrEprYsNeiNqoFegtOOFfdgt5yLJU1Kd6ci9VtdpnK18PFVv/o6JCXWaZi9QYHqUkHvIFBh7yBMfsxnhc3Qjei4/GGH5ErAmO2oZOM5o5PIjF5geb+GY5ALokagezNUhyL278p0NL1UIXJ7eujFZTRJGdMhdoq1iqF5TBBPW6ry6zHoSZ/5juhpx9IxoNaCsN6hY3kcsJJWNT4NY0xwtl6YuVJlSDiPWN9AAe373u7VN0Gz/v48uF8jtitjlUnXG3FycIC0sKkvJHCu+12jmqLpW0s0NQ097hkTrrm8G/Tqp1yAkq0vbVJGnAV2hZYn5vfD8jAirMqlXMHcbWiLyyqKusrb+UPhyetrC+7jXVwsOAZEOCreCH8Qhtd97g0UzkMAgdFD8mcFDScBW/srbmtV3HYGwKqJ1zNSpgsefeeySj70bW4PWYRgDcFR0Z6lZ3q5tsxb5iSISF/J3zsP3mhq+x7Wn46+k4kjeULLls58iA2T76ddgMyQKi39QQn2NOVHXBLw1sPY+QE34riyyfw8ly6XIuXW/Dl3/HyFLq8Hy9bMmBWhuu/4PVh5AAL8jdCUECE2PiM5AAipRWgcN8h4rov1JunMh/9okam8NHv6tlkPjqhHhNHmloljg6q
*/