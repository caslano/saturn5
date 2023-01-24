// Copyright 2020 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_REDUCE_COMMAND_HPP
#define BOOST_HISTOGRAM_DETAIL_REDUCE_COMMAND_HPP

#include <boost/histogram/fwd.hpp>

namespace boost {
namespace histogram {
namespace detail {

struct reduce_command {
  static constexpr unsigned unset = static_cast<unsigned>(-1);
  unsigned iaxis;
  enum class range_t : char {
    none,
    indices,
    values,
  } range = range_t::none;
  union {
    axis::index_type index;
    double value;
  } begin, end;
  unsigned merge = 0; // default value indicates unset option
  bool crop = false;
  // for internal use by the reduce algorithm
  bool is_ordered = true;
  bool use_underflow_bin = true;
  bool use_overflow_bin = true;
};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* reduce_command.hpp
FhyCB5fg7u5+CB48uBMk2OAEHdzd3WFwlwFmmGV9L3Zrr7qmq2suu+rt//m+tyXDwWQ1g2JpbCU9fv1d75mpYdN39GeEU01fiS756UDu/G9n5kKf+KRwwuG9GCPT/hDAGMMJKiXl+TCLYU9tJwHkgy9fpmvCMNP7DomLGk0oROkq9plzVflNv1IJ3Xl+04mg1UWcxUEHwTULDm58p2oTsLZi3rjdMdbDyJ4wGcmUCHjvUzJSevHMV6el1S9sL6L//UFLrhl+hke8lViutHbExjmKbXoQGeKInsvUXQo3yb8lcAjMmvbLLZo0QJwU2qqnBRugv0h9+vZhsdeUnac/7jF9ifGx8kn96W2XkcBWzGJXhfTfjHrahALoGuAPu98Ox8oDlJzpi95bBBq5ffubUXejufixIXnteKSW9DriRuVDf0eU9PBlk9qHrzFu+PmXiOKGknR6e0xr8vDzX326qgvdRdWM4oaFyMBex7yC4oZdQNbwyyOZOd8GBkWZHfiWL9dkAoJCO0pWK/VR4HW+NVWChZhPMelBGxJ4rMPyY3o397UMkFjBd+tmMHkXwtRLTY2tsrlVw1mo8E+n/lmFiBz7LK2MhgxIIoInmZD2OVfZL1Te7SNjkbemkx+p8KTHR3XfNbkjxi9N0eXNAaWymD4XzUVgglegfsnQ+U32inWC4aXypxPiPdbgl9wyPEGesaoEcl7hPzM0BAVM
*/