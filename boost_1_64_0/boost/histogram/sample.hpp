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
hvrz86BL33utjIK+qo1DIbO4te8rYcww+u/oy4pC8j/FE+9QSbA1qy6L0BijjxZ1e+j4+W7gYWhTQeyhRwr/J6uRx+ZaTw9/a7QFCYkG71v7MsIdmR1o8mCD56unKCOhwowb73YrNCLVzXPqRnjFti/EZCPhzLYx5oS9bcB48W6gnX2xJSGnRWEXBxZWAKEWAk7b9ThsV7/0KtnszVhWzdM4Xe60F17vq9cKQwrxypk1a6o4UrzbnLNeTPb7dm+/ptbvfPnJ5qcTiq5u7OItuIwqgNqwNdRV+fiC0Fx+w319j9YnnEMEoLRDCVrc5gORjJMmiVbLc+TPw4nEe7IEHQQcDgmW4rnn7lZXX96NRDlgCpU5pe6RFui1FpIVI2Dkf3oh6JWyiGdIgeI/PDX1CgUvAGRoBboU4w+5DU8if2zuK6B3ZsX3pY6/ZZkan8hnceFdsbCeiv9ZqDCk3pvysrG2JY2MRKdUma46QYAVE4tXWMq2nooT1IDY095uRPnUGr79H9lCKOh0jb04MRCZn1EfCcAM88+iIyv4HM18s0b0rGoQPCfkrEG+hw==
*/