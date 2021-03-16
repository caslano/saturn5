/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_CONVERTER_HPP
#define BOOST_MULTI_INDEX_DETAIL_CONVERTER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* converter offers means to access indices of a given multi_index_container
 * and for convertibilty between index iterators, so providing a
 * localized access point for get() and project() functions.
 */

template<typename MultiIndexContainer,typename Index>
struct converter
{
  static const Index& index(const MultiIndexContainer& x){return x;}
  static Index&       index(MultiIndexContainer& x){return x;}

  static typename Index::const_iterator const_iterator(
    const MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }

  static typename Index::iterator iterator(
    MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* converter.hpp
RLdlvztBwbSMW9EYidAtfXJlW8MJ+ZU0siy+kib6PrmOy3MAyt/f+bghqtrzdxmg1Vz+uJXU9nJIfJxqjDx+IwT66GQeeL9dYEfGZQGxGLVDevxquWxynYyQGwNioe4mpFTm2yRfdxUZ3TkKblHYrxX2B4Xdp7BnFfaCwrSvtbSI71mUJk5FpIUQsazPE8NsniGKWwHJ9LKsupVKYy3/9xtoLECxQXdh7spXsNziSP9+A8T86Q8G259p6Q/6SMU=
*/