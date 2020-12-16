// Copyright 2015-2018 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_COMMON_TYPE_HPP
#define BOOST_HISTOGRAM_DETAIL_COMMON_TYPE_HPP

#include <boost/histogram/detail/detect.hpp>
#include <boost/histogram/fwd.hpp>
#include <boost/mp11/list.hpp>
#include <boost/mp11/utility.hpp>
#include <tuple>
#include <type_traits>

namespace boost {
namespace histogram {
namespace detail {
// clang-format off
template <class T, class U>
using common_axes = mp11::mp_cond<
  is_tuple<T>, T,
  is_tuple<U>, U,
  is_sequence_of_axis<T>, T,
  is_sequence_of_axis<U>, U,
  std::true_type, T
>;
// clang-format on

// Non-PODs rank highest, then floats, than integers; types with more capacity are higher
template <class Storage>
static constexpr std::size_t type_rank() {
  using T = typename Storage::value_type;
  return !std::is_pod<T>::value * 10000 + std::is_floating_point<T>::value * 100 +
         10 * sizeof(T) + 2 * is_array_like<Storage>::value +
         is_vector_like<Storage>::value;
  ;
}

template <class T, class U>
using common_storage = mp11::mp_if_c<(type_rank<T>() >= type_rank<U>()), T, U>;
} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* common_type.hpp
G9G8JRazeVDEsNxUBh+fFxzk4uQNPjFREJS6xUadXBvlrXt0JLHuWrX+yxIe1cY5l/D7b96hAVm5tc3c6izUblbV5aPdWkCOhCSLYZA488wo0YhJHxo4/JtfbXvjAhYEysG5Xl5od9EWhcjG075ZmDUc6az5/cN2k+JyieLO0l6NGTE3kf0X5hq1p0aI9JLNoOaK6jBuQRbw3gP5atIZ6lhYLlQ4yfAmgejRXEI6lA/joLm5TNkazX5XLHrNaLBXHFqnjKcrvcL/KV5SwOxwm44lmV3FtCtKhZ38oA0G5UygGsmV9eXtMZ3K4fAfAjhtq9maIdQaQwrPkolPC3knGr9f3Wbu4GQDQSA4qS0H2miPP30tN+MzVYQ+cZ3dOB9wvhxP9jbV61lyPD0kbfvjzgUssJykeatZ36dBrIZ+NNBqrZ1Ef3rWDJQIu7VGI/4HmdgYYLwxJdWdZKwSmOWGvzRPIziP4e2Kn2o8MrnGyXvEJ6/gNXVwDnmRKkZWhqFJ/lZTz3oWrtjWR7ojt7tFX4dx4bYdAc1D3BZ8+Hr1mr7hH736OT7cfiD3Atogqc0nTDzxntlzDtQLjkpdrOy9V4Vn1YrjIpZPWzy6l3HpoCl3CA0PzMjujk8gcvk8/C58z2Rw/YjBnam5k6LDbyrZ/x9Sw4/ZGBz2hFP4l2z4yMuPzAFDI0fLVmn5jidO/lBM8uDMk/ANZnw6ppe73zW1nIMD7T1BK1+XdZ1W8w0U1u+Q2dkGxbeh+40uZIRIp4ZGtFtsSIh2n9zEE9X/v2PUp2fdZLHkVc6MfXzaeS6cEzMXziH9F1h/4mRhx3+DyzzEBuhvf2zUyYGcJgetsgu1e6ITD+d1Oed1khXuoP4Y1LehpMBK3kg4CmfbPna2/eepozJc1D66tb/oCLFFNkas4p1v8NNvvaIkxgUkHMAuiQURdqvKQ4SapzLYupUzaP0Y4Srs76vMTA9ZjEzPRaZACT/3wrOhWt5C8ZliJVRZ5kA0UaLyW7zTzO+3rElFHhtXm2LtQzKPb8fk4Tgmj6dWGnnU3sLpH1Tpaycg7fCYtPZj0lbuUmkv5LRfMdP2MXpHo3opQr0VnTev3SSEoSMzXFZ8n8DXh++5QP/Okf/c/WemB5b/Nke3lmwzb6ELAa4ENfjc4UrJLKEGh6n55SL1PUnr69AhwbGOcD5HO2R0HyEwThHHYcEqR7iTSu3GwoS2NRwNoxyBUemuyUE5InlGut+Jwq7B14Ov+8qTx0HrS3vi16NPJbxjjRj3fl9C/GZHgv+qjPj3KQnwzoT4K+LjxQE6DqY9+0OpUor9imuh90t0ai1WEbyps/sI8kfcgUC+/9fFDHvOJt71RgcdwkxBXXCnna56FPdQFsAsqcq8Ayx26ZutUO5AN7xNOeYcb5tUjDTKd8d+xWBJpYlJlPzm2QVdT472ITEm+/PKBGA6nX/4uyLvSTyJrXrLYJM9MMG0GvBgZAxcFwPM7jl4sx7zc38YhNyivMBhs/5jM+FcTliqEk6ZgKTUbJ/ISSItEBuUIMWnZoqZnKJzXIp92FizOueTRk18jb0h/qZ79HxQX+2wmXoIp34V3QJdwkruPyMP0iA1tZlKzALNmhSf6CEkAqdFIiyrOWm2kZQWxF7qGaU3m9PXL/q9z5ga3BnZ1GWyddLtfvGcVDmRdJm7xyvO5nywjuF8tC6qSL4XX7ySFD0i10tzJtQnlWnLHb6VgYHhO0OyAumoQAHZZ8Ee0QfvLl9pkWLzyrohCvTqKOjcd/wvsi+9O7fHVLinqrAjpsIC5LlLO0fVwyvOEISMiSsMNdqUCV+cIPwlffxi7AF5oBKT+rIYsriD7D/aFFE1wZE=
*/