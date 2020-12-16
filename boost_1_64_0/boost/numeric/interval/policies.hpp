/* Boost interval/policies.hpp template implementation file
 *
 * Copyright 2003 Guillaume Melquiond
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or
 * copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_INTERVAL_POLICIES_HPP
#define BOOST_NUMERIC_INTERVAL_POLICIES_HPP

#include <boost/numeric/interval/interval.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * policies class
 */

template<class Rounding, class Checking>
struct policies
{
  typedef Rounding rounding;
  typedef Checking checking;
};

/*
 * policies switching classes
 */

template<class OldInterval, class NewRounding>
class change_rounding
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::checking checking;
public:
  typedef interval<T, policies<NewRounding, checking> > type;
};

template<class OldInterval, class NewChecking>
class change_checking
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::rounding rounding;
public:
  typedef interval<T, policies<rounding, NewChecking> > type;
};

/*
 * Protect / unprotect: control whether the rounding mode is set/reset
 * at each operation, rather than once and for all.
 */

template<class OldInterval>
class unprotect
{
  typedef typename OldInterval::base_type T;
  typedef typename OldInterval::traits_type p;
  typedef typename p::rounding r;
  typedef typename r::unprotected_rounding newRounding;
public:
  typedef typename change_rounding<OldInterval, newRounding>::type type;
};

} // namespace interval_lib
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_INTERVAL_POLICIES_HPP

/* policies.hpp
ZcKarLQ739uDa/OM0u5exItjXH9Ku5D3tte4/pR2Ts1jq7LuwsyEOSRfr8y6W1273csTIax1Gphst9J8yG7GXWlX5tp1xs8XJvMs8vDyQ1xHSruwMWuSGHel3c/tR8eyfirtlvTTjWJslXb9LRN/cK0oFrt03knexxQ7X7QgkOc6mLGw6S/jl3L/U9rd/o9FO64VmIxR9OkdjJ9eDe12E761XcK9CmYs82z+MN5zAmAyr92nzuaeWktpV7A3dATXGEzO2fjq75qyZsEshEW1eRzEdQSTY0ioovHkXMMshbkZli7HtQIzFza8SuO6XCtKu7QxiZUYB8UatY915H6kjGFR/2a0y0q7T94FrlwPSl8e5qekM0ZKO+/6kdncc2pq11Y7vcl6zHmYbLek2s0z/J4MM5JnqfDXZRgjpd2RlkOuM+eVdgVZ9+14nlDamQX8Zt0dpLR72rKzDfcOpd1NnZ487yYo7cJODfRljJR2Pca+mMMYKe2uXvjNuGcq7Tzj9zZjjJR2PSIvmXLPUdot+FCjMWuW0i5miN9o3gOUdgmtFvMcYllL+ft0nlMdxg8m2xUr7biX8YPpCyuZ3NOd+xjMVNjGEq/ZLgQm8+U/b08kMH5Ku/Cl95uznintyq/z1+F+BCsmrFbwrXvc32HOwmZb3vjEvQPmLWzn0IyVzHllfHmDy47ifCrthr38YcJaHqi9b57flMI4lIPJdo8/5tXi2GFy7OMbpWZy7Eq7jpbzUnjPgbkLW9NxUxzzDFZS2AGbWSH83qO878ennc84PpifsH45FnocQ23t96XdqJ7MGgmT7ZKDGy3mXQ2mEVZgu3cWx6C0q9W58wbuKzAzYWXNXW9xPSjtJh2sXJF5HaSdu1Nmd2XN8obJsW95aNWK35dg1sJsY97zXhWq/OaqHWbbeM6CyX7GpXZm7g6COQrrf3gt+zIHZi5sbI2phXuA0m6qz9gdPBPBTISt7p7UknuA0u5i7mt+I8uFFRPmXHF/f9byYO12JcaYG3HOYPJ901vbvWVOKO16xviU45zBiskxXL3GWh6rtJv77lQo667yvqHeUTGcF5iMQxf/xRGsuzA3WSca9VnO8yDMQVjCOK/6rJ8wA2Hh67zG8c4FkzmxcMabNOZZHe31kP/hxTfmEsxJWJ9tVX9zrcDk+wZfCavHWgCT7zu47MdhzhnMU/Zln/1AzovyvjoHfN6wFijv+3Zt93fmC0zm7v3UJcs4ZzA5n1l1BlXlvMBshbWtEejCeamrfc46U79EJPcVmMz53cMms34GwFyEVewYtYa5BJPjW6sT7skaCZP5Evi7wQOewWAWwvruSxnC9QeTOeG2JvoJ9w6YnOtnEeO5Vi4rv3nzakwFnqWU8Y3u4zKX+0pd5e8Wo1vGcf3V014PTes0uc/1BzMS1uq8ZSLXH0wjzO5svQJ+m4HZCNv28WQOv9cp7ZaEhfjwTAuzErbcLv8Qz0tKu5mHH3bgfCpjKON+8DXnU2ln4n19GusZzFKY4WpH1uRspZ3R/K6Ff2+EyfiVaxQ5kPmptJttGhPOua6vHaO8Rh0YW0eYHPvABwvbMj9hXsKaPUpl/MKVdjk6dxtwPpX3hQ+o0ZL5qbSr1vjdbc6n8j67rqG8O2Uo7eKX7j/Hs41iUz5v7cs5UyzsfZYZ6yDMVdhV/Vo8D9o20G6XFzDLnecemIzflt7tuf5qwayFNbzbxJlzBnMRts6r8yXWOqWd3fycO5wXmKHMwTO/RvAOq/Tzw1aLT8xBmK3sZ94OfvM4qrSrP6LRM9ZBmJEw98fP1nJPVdptrN1/NNe70s+glKz3PGcp7WxyffqwfjbUrmdmM075sn7CZLtLU6M=
*/