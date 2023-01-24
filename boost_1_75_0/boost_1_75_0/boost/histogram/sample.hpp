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
LycSHZ/SRvo8Defxgm9oxdxYMs/xfv6+5Q16RpB0A6GGfsFcegi8IU4QJmfwNwsQB5WEB6O0sGjvPhdIFTEp7maHFVVp28JB6G4wjP/ygW4Ez/8kI3LcVtnPO0h8j4Xva7knienw56qfeQpjp1m5F+tCUsB3+fRSQDoAeILwjvIOZyFykp48UuIWTvy2l2A3f/91WFEambg6tVfgyHg2+27G6IRhxY5CxSoG6JKq5zqfZz4tK38f1ZGMU8CyGLSbcRf6536B8E4m7LM5IHdkMQetKIF1UvUCdPlJblISiH5PfMcniDwClABGVoDHhccu6aBI5Qr3kSA59+gWMdZx4XHh7LzoB8TKdubSXlXqZiZjj4AWuVK/XsQ7DCgjlNgr4SG1JWFztwUj9a0IY5xZI5mnjf8UeAyoX2TbEdjjxO02ImRCXkltRWtNOym1GSuYiHTTk6SMJ/BJHR4YL8OTDikilaHFJcivC4NqSJe1Hg1c/VBmce1gmQ85WYuXnU8pIjVcJSxWrh5SAJi08m7KzdLknN7PDUGd9kPTzeI33WpPIxaM3J+O5r916kiQzD8SmIh2fE4ymufUWiKqMbCAdptRbARgSO34vj5NTKvy1CeeskZft4KPfrC3KIfsOJjVzayLSAqw5Fueix2E9Vlk31IrJoqbU8gGKo7pHEYpGEiwwSQe7ecMN7yXjaewqcJRK2uShRHA5EXTe6vF
*/