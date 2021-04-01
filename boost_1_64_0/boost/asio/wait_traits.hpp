//
// wait_traits.hpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_WAIT_TRAITS_HPP
#define BOOST_ASIO_WAIT_TRAITS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

/// Wait traits suitable for use with the basic_waitable_timer class template.
template <typename Clock>
struct wait_traits
{
  /// Convert a clock duration into a duration used for waiting.
  /**
   * @returns @c d.
   */
  static typename Clock::duration to_wait_duration(
      const typename Clock::duration& d)
  {
    return d;
  }

  /// Convert a clock duration into a duration used for waiting.
  /**
   * @returns @c d.
   */
  static typename Clock::duration to_wait_duration(
      const typename Clock::time_point& t)
  {
    typename Clock::time_point now = Clock::now();
    if (now + (Clock::duration::max)() < t)
      return (Clock::duration::max)();
    if (now + (Clock::duration::min)() > t)
      return (Clock::duration::min)();
    return t - now;
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_WAIT_TRAITS_HPP

/* wait_traits.hpp
9xDoxNcQe60ErYJzNgohSLMjOVIIvtbhP8hh6rBSfq7bJ8kBZpkyBJBPQ8B+EUFEr5ffEsk2TNSmKBbz/Sz9FkCZLjqaupTFtLF+qS26PezXTaobFTmTnbpiqW2Idwa7Ak+p11NcwFNYML1HLsVaf8VMMwBXRugLFcKufW/FYejREPdtYVnpy7FET8Im68o1/ONkG2qlTPPJN5blpG+MzGeQ35ny7vdkDN8YVD57p7n2dSB/kFnktXc0UEO3iTrdIc6YBx1ZzHIyVHXlh1R+H/DEbpQx0zHz5BxACUomW6rlEJrN1J+NxyzU/84fllSz4wAvLI4V9RGUVXsfYzlJD/2QfZoAWNMbIrfKvDuvqZRTtGwvX+M1W5tNM3gEjFYHeXfn/niorGmnMW0YWM6kCsJflo7SB1tt9srhoVUm1c104aim4pOPv8Nr0GiMckU9n4X9TrHEXq1PAw6mJbhBmi8rZtvmVxYmYREZ8peCYAIbklF/VqCV3ScCSrio6P2buHmvtp6+Ded/IAdcJfT7my29n3WFcWqa4MnyziJkTRPA+VOGa1YusgC4Aw==
*/