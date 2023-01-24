// Copyright 2019 Hans Dembinski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HISTOGRAM_DETAIL_PRIORITY_HPP
#define BOOST_HISTOGRAM_DETAIL_PRIORITY_HPP

#include <cstdint>

namespace boost {
namespace histogram {
namespace detail {

// priority is used to priorise ambiguous overloads

template <std::size_t N>
struct priority : priority<(N - 1)> {};

template <>
struct priority<0> {};

} // namespace detail
} // namespace histogram
} // namespace boost

#endif

/* priority.hpp
OnsrvTk5IBYUmXAMaYNQaz3Kh5rRlBKPDu1xuNSmo3hxXictuPTzSSf5JO18GMuO5SbjXOXrJ+4+QbV9Oc3mGcpRRsrYimrkM+KOxRIYU3KXI3gcwlBqEvrVEK3DEfVDxWY4ckwyIt7Fl69GuBeE0G9fnJI3A4t6cfDZ5esZme/ddRzLr8oAyZoO89pRFbp2LqVPvg0dp7a6looHnJ0GEdldIYQlBLXDDt5s0kJXvku9oR+OaPtk9FT2xQHucdh5T57a7q3e8Fdn0o5ozC5onarTnREBKTGzWQ1ZAtNFYStTValAZTNCGlgHAe89r38Y7HtXlMs9pXeHnGTDI+6AUj4TYSdvJD5V4kqrTB4/wbDtQWSrDKvaBQFxfOqmAGhSFZhzfeDT2q3CvATanl0JlTGJnBh5rM8d9RELuopaXz7vGBsupiNh8K7LVGuKyjUaaZ+QvojGf8mdVK1+LTvxHXWhZ6G2csqWhMWEaQmrgjxhsYxfP9/6ZL5dKstsnr7U6rs9S3nNS61BRgsWjTDJzm8sA248RsC/pM0rdJuiK02jltSaEhQr4dgLwyuIPGl4vDwgOxb7JqQW1BbsJSRrlDsbAmMvdMJyny9pGZk1n3o4EUdRKl7XqPUwIpa/1Qhfbn+zichtgMzHlBbRnXHP0p2cvvQhKHzDtRbjywBSH+WLFuCIOxf6D+u/EXZXQXGsaRiAcUkCBA9+cPfg
*/