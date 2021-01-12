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
PB20pMcDkjhfQDmU8Z5/De3ovhuxTnD6Iox38Z5G93ks/qsTe1xKHdsQCMb8aTqi7mCsLzcX4xoMe3zehsY0iaEDOWwBe7EcKii+85+a85u+MCT/bvEWYn1v3egtHXHM7LZYhR7Tnm7H4SJYkJ1a541uJj/eEJ1XkhL05c2x6HumHQU3QGyLjunTdTWJaPMptD3brvWb8O5Ih7RpvZ5E9K1U6HtOJQCjuud33Lc6rygl6PtF
*/