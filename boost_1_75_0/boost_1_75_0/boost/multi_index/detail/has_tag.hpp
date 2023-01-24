/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_HAS_TAG_HPP
#define BOOST_MULTI_INDEX_DETAIL_HAS_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/mpl/contains.hpp>

namespace boost{

namespace multi_index{

namespace detail{

/* determines whether an index type has a given tag in its tag list */

template<typename Tag>
struct has_tag
{
  template<typename Index>
  struct apply:mpl::contains<BOOST_DEDUCED_TYPENAME Index::tag_list,Tag>
  {
  }; 
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* has_tag.hpp
qWAFZ38UG1a5WLujOvYNREl9hUgVsZ1UbLWrxlgs2v7jx/j/df3jy1qufzywqeoKdga/uYNLH3cd2JqRS17R1FQWCqYbLmtxPv+d2gSmglndLL6hUmBoDCb4PjOIN7EE2vTU1oC29N9NQeNq5jX9WLkWAk7/pS3C+aezCZzy0G74/jEAcKzF11YKjIhVRjyK0A6N1bT6KM0bgu8GZ2vAP/xac+BfJMDfIc+JB4Fv89/VJ0+CfxL8y5T8qTlYnxwvOOFfOlzIchZPyPFPAAAnoJKp16ekaAZ2FrF3Ex0C7YhIqaDDXCxa7ixezVuA1biks/2rOcHV6hryeFq9H7234a1zjqDYetGc03R5DtZggbt8troBE2auVuiX7gQiVmJNdz89JQVeigq3BJdFHxKvrHo9hJ5R8tuy/WXdqHkZWvv9ZfHwWzn/GvhF38DK+eg9ytu9iBWPo9ZlfhJ7az3PZ04+m89nEneVTl1l8kkW/8nlP/nUPnoEtV84m888fFYMZ87isuV0MXRt9mBfgDmb8BHlaRfWNaTOlJl4LC/E11DRjbxo/aVMXRYSIOJGrvlGlulGlnEjsBC/SunNL8HvVbrzMY6EEs0vjDU9HGt+GCdDCT9KrHoX6SPn0zTJC08Lh5LmGLa/jCe8jCa8TKHJjZgx0dyHRirxtcUGDQ1EbKUVMTjXmVSGCw6tFkPzg60W6bCCp+QjjVDysURD
*/