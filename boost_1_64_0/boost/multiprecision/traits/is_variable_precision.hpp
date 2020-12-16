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
/ZBf6/KOJ1IrcyLfj3V58j24sS5O8sJxVETf8VtmHzRN0yiPmnpwjpnaiZO++o4x+VyEbpl6pcfFYc7uRG+16seswgJSl4oRve1wjOmxRGIVZRmGFlcEV7LX9/5TP0qXcxzhpp4fhHnA5VhBokzBCFA/itkPRJiXqW94AW8zrzpSvCxcMGSd3HL9JHIEXnzGvqfyvT1VG5dt9W4Ck49FkGVe4UQWyC9j1ZMjYuoBsgIxP6HKg66jFI6LX9IowqHE0kJ1wQeknZV72OSoyeSisMM4iEIHZbiEdofZzn8yO76Xx0WQu1IGX1HW6grl7b5/8rwtwjD2I8eXQmuTpq2ekjtkyLlRhv9ZUg59S9a4XGrIpa4b26mfCsj4+kJuadOUO87kHOG4bmE7kU9jIh5TKjsbTC4USWalbhGKuflZ+DUBh/GXF1964OD+KTn/wX3zFiZrC9fxEidMxNzpxcUW3+xTNs8zOV8Uvle6VuCJLvgGPsgHmw6iPLzM8zCy08gPPUfwnU08nt80fOMXReAFTim8Z6vp2/ouMe6bG0zOE54TRUGSeSDHl4aWV1QaSXb8X1y2tBM7ihzLkCWvoix9U5hsIVIvKvK08E1Z+L5qU+U87q5h37WSMrZqHW61K1juIlOphu+r8tfzmawjojBziyBJddnqgjXu5zVDLrdj38nTAuTU1rRWP7/RiKtnuW4SRomU85b+a1zfZdgsc8tPo7AgWSOu1Idmcq4oiswP/aTKn8ylfCWTYJPuQtRlMxBNkigBk9rsV+OM0XVdJhchJC9zUhdl6LSVOmOk0nbzX0ZbEBZB5HipMJb1zf7Z+L95/cp8vwhCKxNt2wEqYRrX7GOyrogyv0j93BbN7QgNvzxNly1FkARxHlt1dOlWHN6Ol1wmt9LC961S8N0yXKZr2PELO0usRPAdNPw7t/Fvs6+Xh3nipyRkHnmqxKlffo7JOyKPyqhwE5vkqTbzcnaByQUiCp0gyf2Ey/GnXpTNzzFZW9hlUQZBHjJZXP8w4voDQy70Q8sNrUiYxwJqORXXm0ZcCz9wrdyLSY4dn+Xp3DnE36QJnTixPDsUbUcRKlFK5xOZrCWSNMqLInBIlp6yMfrNhs2stJM4SzxTTosulYfnM9lYOJ5TZq5bkqx5hNfw8SuYvC3SNM8DN8gEO+5BPqax9FkmFwgvDsLQyhwu1+7jD5jpTewiK11mczMfXzHiazt5mOWpJcwjd5WcpeSuMTlHuE7g+EHsmXLTFo/rTSOucWGlaRYWonFEj6r3oCwN67KuiH0rsgI7Es2jeY2++GOZrCO80Lb8Ig9F49gfr2uCyVnCDbFV8VJhHL03v/MzTM4XYR6Xnh05ppyWndSOreiyuchCy84C1xP6iblaZEHF85VG+iLbDnM3C0Xj6D5v/84xuVAUSej6uWsZciym+DlQcb2oyxfC9qK8zBJbsJPmldSC8s1lIx/LqHAcN8uYELcnqNwZ+ZHYcR7nSSSMo+Tmt++GkR+lW2ZO5AemHFnV5lR3jOiykYj91HcLSqN5er0xt/FYJp+LzA1tP/SizRS0lYlU11EIx8rKIo5iwU6VVzJz1F9jdi0RpGlaeHEgjKPvtalVKn+6XCaiMrfiNCiEdusIjd1pLpDZcoXtlJYfF4FoHqtRslQezjHZQLieFbtp4Ijm0aZG+b3IZGORZ7ljWZEnNjvyZKzXXDXkfdcJ/Sy2SL7unZjyE6o94/mSOr6Xpr4v2GnESualKl/GRnldLVK7KCLXFqu4y3z21MIc7k/BRVcpSPuL9+hyh9wkDVzfK0Bqig0Xengn3JOfBHnyZFxTxMxuvsv2tAfAeGs/4Zu+y3afYXqXDYl0Tzs=
*/