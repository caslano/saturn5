// Copyright 2019 Henry Schreiner
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_ALGORITHM_EMPTY_HPP
#define BOOST_HISTOGRAM_ALGORITHM_EMPTY_HPP

#include <boost/histogram/fwd.hpp>
#include <boost/histogram/indexed.hpp>

namespace boost {
namespace histogram {
namespace algorithm {
/** Check to see if all histogram cells are empty. Use coverage to include or
  exclude the underflow/overflow bins.

  This algorithm has O(N) complexity, where N is the number of cells.

  Returns true if all cells are empty, and false otherwise.
 */
template <class A, class S>
auto empty(const histogram<A, S>& h, coverage cov) {
  using value_type = typename histogram<A, S>::value_type;
  const value_type default_value = value_type();
  for (auto&& ind : indexed(h, cov)) {
    if (*ind != default_value) { return false; }
  }
  return true;
}
} // namespace algorithm
} // namespace histogram
} // namespace boost

#endif

/* empty.hpp
K01gl/E6TNdV4Z5LRHeBdRun5W7BrIVX2Zj4oDjFllUi97D9/lt/SE9rfePv7H3eqK0vwXxfWxv7AFuYklVP8seBXvmVW8W8qnf8q2M/6i/Vx1hQNx1oFIHlmKJpZtjIR/ltjb6G5gRa/eCk4g+/zSKuyN6jxDc0nXV3fgpOrhYpbWuUD7O05gq2IZA+ttr+jWoc7Tm7/BGZppIsNOmLUs+55kZUfQARH3ZDyGtyjkmp/N7hliQ1yqcN/x+e8Ki5BxYhKz6jvX+MBL4yoB/EchydLMtHm7E7QRIdI3L58o5GcJ0lpr+GBu7hsOZbQxH1T0een8ycLpRX1svcOX5u7JIROW8nTKnGZOQzOTrETmUlfVRM3Pc5yblh+TonjKcj7GeZ6lRyJ3gVhCqi8631RVJQBJ4Gtzx6wrW6asmD9SBGabX7vX2iUZ1lIsoR1eg57d0LyfgLnpVDZ1k+SZ154f6qHvwOJRDxqCWuCtGsO0HRQYznSAPdwzUrcjM8T0T4wgFtcoNQU/GnYhGVxmVBsplqGJQS2ZzXeWL/MPaGHQ0Wz89lbOtDIx/fFw==
*/