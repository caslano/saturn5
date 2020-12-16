// Copyright 2015-2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_RELAXED_EQUAL_HPP
#define BOOST_HISTOGRAM_DETAIL_RELAXED_EQUAL_HPP

#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/detail/static_if.hpp>

namespace boost {
namespace histogram {
namespace detail {

template <class T>
constexpr bool relaxed_equal(const T& a, const T& b) noexcept {
  return static_if<has_operator_equal<T>>(
      [](const auto& a, const auto& b) { return a == b; },
      [](const auto&, const auto&) { return true; }, a, b);
}

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* relaxed_equal.hpp
mCGKBJWmdTD8VMjYNGEwcju6LLGa1YNPk7HRbrT4nE7v/OMf6WXeoS1Bhdo0dI43cffQAuLctK/kWb/+LaKvW3x5iJ7Pz1eymMPEGPrI4Ss5dCQWLUOXB1o6FvWDsqhLLklyLN+o9wVDqEBQpFwwbvJjj4kwoVH52WTn4WghMzVyctzo94lf2ZVj3SeCFjqLrRYyxRFuuhxzJyJwy8xNNE6PeN3OLCvPm3OojfE5/nxdZqeJS0o4I9w7ssTKs/01ckOqA7kVIKdtJYLPh24ug3lueCYZTWmLcyMt1oVOsi9PKUsNOyKbrZEmK8IWvR05/V7o6nUpo1LRd55+P3TZurHmUdXmcF7kdHuo77qxKaOqU8L9IqfjIdu6sZZR1ZZwujpgBrXnAicJ/8AnIR9cW9ZwmH2sOLHEJSeE+7j0huilR+7HDw3Ty+/NqxLlF07TK11WBlbJMJ5xz4svlalYffKYfg79ZZAIWmRLofrztPZxI0gPUPYlYnu5UfhLsezBfSXJYvQc3BJ/4Iezm5nI7h2cvYKk7MWH6tnrpbKX3KEpzhcnOrTNA3SZrJ+anHm3G0jSneTbPNvObx1I2ezcQ0QGJEYFi+yinHoWz3MurusbNtYJkNFF8Krfa8VdoZkw7Om5ZLL9yZUFhVkO2PZk4weijpLAgPXDnqqxLcIZSKZLhR14z6xa+BcQhGbOLfxGyS1klgZGOX5pU/AOlqUUN6yNv43mfTpjyavYDigBKbKaaaiJoy9YMsFPI/EIRVKdzYzEU8OpJ8c5slszI3FruH/bOIeJXJUOYHcdNtF3ELvriNY7jMYS0BR/7CusZSbYkcw4kphBH5cacgYeNHA/T7jXAnc0eRsPXySj5BhRpJTBq7h9fTaw6uAPgsN18RttSoGdYu/At8yGLtPyh3bCS1Vo+inSoX5x3SC1loiDJOsvUUuH/UkP/Ey+fr7UmijxHxmJ3tqyHomCeSuYf0IF84DWshCQ0RkO6Ws3nNWx8MGvUzGCkoicTg1dHDlNqbxgpPJVSqWIUrGpVPpqU+hohaVLYtkqMZ2XVzvy8hd05LxFY2iwmzJ5SwgaJ52K7y/3kOrtSEqe58NBwjlIubk6nx13SpW/wNSBSEtHIqtAhA4BaL78umhvrboAmPffVJDlWIqvY0iW4yH8mswpKSmWFAv+3/8c3q9HuIbvL/AtuyrLcfUQDuPn9/C7Vv9966r/vj0e+nRez7wM1glcqsrZ3f2yPX+6n3FEkzwT/LpgX3+HttmzLnvUxeEBqw+ELlo3wzzqJnM4K7IpJRJLWX0g/CfXptYe8Mi61Ux20vtQV7+esRiRmtg/zTrHqN6I+CIius2jpiUivtghIt1lwK2Wopfvo+i3nWf8FIo/kOLvXtfnAuJbKP4BE+JXnT/9UPGvJ3Osc8QPp7Fjt9Y7fz39PKP1oGgjNj6eh4PVgytM67JG2RDxeUScYh5Vi4hYtkTc1c93jJi7MVWagyf7Ls4Vj/yZRqLsmXMaYSWiepvFShjCTrkQQ307Brtfz2JhOEdZCF/mi/fNf2CgA0STnSLni6uYaM5MpLjgglO0UIpWPcV9fzJSXH1eKU4mkw/SRXEo6HRPw/3S2ya56QR/zVZFh4prAejQXAUHJVZkEoLYKbtxHA8C7a+eF+1hPjH8+DF9EEgLjEb5t851d3YRDarvvq4q6dePnReFKbB3O6Yo5AWqjRb/taQWf/9FspKpybs7XnXE1JcZ1Dc+DerrehoCN1EXuM2dBY57gqb34+oO19felMVGB+8f4i2SnORLkbgK+4KMdoova1nRJzBdseoT9amsdmEnYub5qz//8x+5HqR90hlZbjWF88SYtmPx6Hg=
*/