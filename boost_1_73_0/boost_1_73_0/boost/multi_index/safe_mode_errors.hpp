/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_SAFE_MODE_ERRORS_HPP
#define BOOST_MULTI_INDEX_SAFE_MODE_ERRORS_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace safe_mode{

/* Error codes for Boost.MultiIndex safe mode. These go in a separate
 * header so that the user can include it when redefining
 * BOOST_MULTI_INDEX_SAFE_MODE_ASSERT prior to the inclusion of
 * any other header of Boost.MultiIndex.
 */

enum error_code
{
  invalid_iterator=0,
  not_dereferenceable_iterator,
  not_incrementable_iterator,
  not_decrementable_iterator,
  not_owner,
  not_same_owner,
  invalid_range,
  inside_range,
  out_of_bounds,
  same_container
};

} /* namespace multi_index::safe_mode */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* safe_mode_errors.hpp
ta5hc10XKXJxQTCUkLxYclTCOOiM4UyeSuuYsHZSqy5rExyZ0noOLy8KqyEuhCzEnIWEQ+5cZd9HUVKbgt1HqU5slNym381deZfJCZsoxTV05eA0akshfGSIUqcy8zsXhC+rel5Im4f3blhKpZE2sFQUnotxkuzSNmG6Kk/ow1CxY+n8ZrWyXuoy1+U/gVxHz5LVRrEQ14GDUs1lDlGrlEwT3GR+K7GqaVPgJ1tz7zeFVmwGrf4Ue9MW5sJKG+Job7Y7OZzhqH9w0B/PTjD5jP74xJN93RsPufWSxQzoqjJkWdxAllUhKV1pPt+KgpdSJUWdElq+ebElV1fdvBU8fLEgl2vrlChp+TqlTCrC7mQ6G/e/j+Lv/WNs9rbeBIFUjlssVdsfhFkk3OFcGGzw+eL0vBP8CrC8mddZdvo3w/k2v5JZ26Pw4gO2OvDBQGWYLGu3Dq1Y0Hu8shgd748Gs9EwvsWfqVaIRqJ33tluUIazMQqb/ul3sKQePMim7U2E/+TReaj6H6aDjMefUtZ8Siry81lWfij86HjYKojnYn6NRzgvue9NMHee/w2b+SFwkxrjPFUqKauV3ybRzfM1xhfa8Szf0XmtpZO5SH6G+DaM9w9G3yb94Zp87p5728Hv4A9QSwMECgAAAAgA
*/