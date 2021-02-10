/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_DO_NOT_COPY_ELEMENTS_TAG_HPP
#define BOOST_MULTI_INDEX_DETAIL_DO_NOT_COPY_ELEMENTS_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* Used to mark a special ctor variant that copies the internal objects of
 * a container but not its elements.
 */

struct do_not_copy_elements_tag{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* do_not_copy_elements_tag.hpp
CMtRHbc5pQFPu1bb4DIWBdJQtwisldVviV4JjoVlWtnr+3rYL8LprqRYElLgFt6VItaEYU7BL/LEJYNJ/2xC3vaGb8jk+KTvyuNZB7PpdjqdWg3xgYvQiDOqYROzatb+qYHPDzYZNQv4AYbng8HLpTAp8urhBDZDmisd59AgXEF0ISUyUgmx4FCt87KGzz6YZgnHQWF/6z7r/O7F7U04HJ7hbsXIH5dubuOccLwB+tQFjnE3B4jB9rUIRBridYl79h4wCJkJNaWCcMltw4Ekbwaj/d6A9AaDpgeTNlCtCS5NZ2GxS52he/fBOZkbmWuE7PQCxAgM/5uplaAZQX2m1AybNVbzF98a/K376nVkEqpnW1Ht9jy/9Wa76aEai4OReKHFfZezRpDfzQopW6VMaJ4zmTQc19GSvyqpb+5aVgmmZS7G4uDRiPuhvyakOHJZcinr3hmEmCWRZWc1ylclYb6q+uMxOen9NBqT/d7hkj9XNYF+twpZeZlhFoezl0bLDsJbBK7uXj6q9rbfO+yPI+iuUyw7MrpHZEkuToiSUe8Bn33nsgqqZxKlFXsr1YqGpWIAge7KhvjgYAkcNLcsA82pZoxQIRoPIK0NsX4jXN59gm1NRkfkpH8yGl+sKtk1Z9gKvwwkBClNElLm
*/