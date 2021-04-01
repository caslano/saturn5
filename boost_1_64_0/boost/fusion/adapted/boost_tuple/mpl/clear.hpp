/*=============================================================================
    Copyright (c) 2012 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CLEAR_10172012_0100)
#define BOOST_FUSION_CLEAR_10172012_0100

#include <boost/mpl/identity.hpp>
#include <boost/fusion/adapted/boost_tuple/tag_of.hpp>

namespace boost { namespace fusion { namespace detail {

  template <typename Tag>
  struct clear;

  template <>
  struct clear<boost_tuple_tag> : mpl::identity<boost::tuple<> > {};

}}}

#endif

/* clear.hpp
DcBI8QlYorzbs513jE7rQZ+/RkEsoAfYclceLko9O2UmHrh7xrW6o323KMYv8qXgJAyyJtVCibB+s/LplSnijQTeNZdlhbS3aYSc796hy7W6mF1oRxBw0YRczwmIH8lPBvCmlkImSYnblxzSKD4QjgZXYH/PX+3EaMYQRPDjbPcM0rNzmYBz2ey+0C2ITVhSMyw/eDNM+mcJHMq7ltWvXmDwRyQpeCRslk6Ddvqm0kFHUydq8rl6wWPf3cyRbwgHMESsClxF4jwKcETVQR9kmBbAYf9tfuA1VwCKYp2uAooeq3yE5CWI9w7/j8f5uAWGBRyx3QZr7dCgzqXsTPnmGARSTO5/9whMbb4L6Ncsj+xwFHCQvjtzwdKFwmF2ydLGBn03dmqsbS3HX9l9iq+VmJN6/9tmcHOEFteO5lVN1a9HBarXLwVyjvQTd90IEO6CTp+vGKQ8+1w3p0jkKLuSx9fCCINZs6yaCT3/QgDtGyfPdSrjW+6YX2dp2R26lkrujI8/u+cq9eKft8y9RrRvIvzJzwYLhEJWwZLI+FSnN26xsJa2iWm8SBKvYQ==
*/