// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_SAMPLE_HPP
#define BOOST_HISTOGRAM_SAMPLE_HPP

#include <tuple>
#include <utility>

namespace boost {
namespace histogram {

template <class T>
struct sample_type {
  T value;
};

/** Helper function to mark arguments as sample.

  @param ts arguments to be forwarded to the accumulator.
*/
template <class... Ts>
auto sample(Ts&&... ts) noexcept {
  return sample_type<std::tuple<Ts...>>{std::forward_as_tuple(std::forward<Ts>(ts)...)};
}

} // namespace histogram
} // namespace boost

#endif

/* sample.hpp
/7g1uP0onGvVhXdLtHFLsxKmW4TCOlKHfUXDnYF2WUgtcqP0fogZ4RmaULvmIOEkz7W4KEQpa2nTwQy12jgdJ+ECbrI94LpqjW7wyC7+0ZtNHhdaOySuY1c93qOz+pTfkeMCO9x/71TXG8ykc9/batytouonzvAC6kM71vXw519tjWuxE7q76Q7YXuxUBnvVOdLRPLJ/sWxV2U7v1jJfQ5Xln7HZz0rrWG0j61XfYaReP4nbUbX4u8XWdJ1wHHNKCr/g1exqa2PLVavFMMu97rr9NqmTLaz+5m0qS8zjfEH8FLdrzCbpjPgRT/HS+OQNFkiyoLZ2yYrv4y4s6tOFBf4TzFsgpmv4X37K76L048d3V/+jsbdYUVu5DOy2QD/Qh6o8rwYWo6ocy+2cw9i9fLKnD7KRS7sw6jCjHejQIiywfaHZbTkJQ5NruTVeP1jWjZv45xspqkbs7FsOS46VGdHxPDxfPClCX2o8vKF4j9HzxU/4cBEkKQtZ0lX420Myc4cpvg34jPxJX0D5acBuEs6D9J6Fb67TURC8iMSbfNLDO9ALwO/PwL8Axsdp+QpQSwMECgAAAAgALWdKUvrC6P6wCAAAohcAABMACQBjdXJsLW1hc3Rlci9tYWtldGd6VVQFAAG2SCRgtVj7
*/