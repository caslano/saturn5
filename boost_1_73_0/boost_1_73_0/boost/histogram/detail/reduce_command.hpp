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
J9jyrXr+24HS2axX+IRtHgGqwIWr1Ty78KFsrFkoET6wD/2VbloPC8XCJBEHDM5SSkFvHYbFM9ZqDO4w+hz9DVBLAwQKAAAACAAtZ0pSr6UtiPQ4AABkBQIAJgAJAGN1cmwtbWFzdGVyL3BhY2thZ2VzL09TNDAwL2N1cmwuaW5jLmluVVQFAAG2SCRg7X1tc+O4se73/ApW7ofZ3bPZtSjZY6fOvRVKomzGEqklKXucShVLluixzsiSI8qzO6fy4y8afBEJNCmhSSue3WEqOzM2+aDR6AYa3Y2GpsHzQ2PPn7QYUNv7BPz/AXvYn7vPxpv1/4SzLf5JEPxbi//HPv0n+/Og5n7Wdt/9O/heO/C7f2vf8e+CpL3/hr8HwUFN/hNIhf/8DJ//M4C/sp+k32YYvfXzl83i4+NW+673vda6uDjX/qLpJ3rrR60/XS3CpeZtw9V9uPn4o/bfc/6Tvz1Of/vtpyj8fz9q4VabLn+SQP3HRaRF64ftr9NNqLG/LxezcBWFc20aafMwmm0W9+wfi5W2fQy1h8Uy1HrO+M6yL3/Ufn1czB4zpC/rFy16XL8s59rj9HOobcJZuPgcAz1PN1tt/cAwWAvzRbRlqC/bxXr1EyMg1Lbh5inKgICQ6TJaa9PP08Vyes+a
*/