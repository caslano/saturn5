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
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
*/