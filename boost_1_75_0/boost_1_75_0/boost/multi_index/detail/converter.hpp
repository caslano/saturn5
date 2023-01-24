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
6rrQwomy8cLpoOzehFx3A10QbSZBm1T1M1fK48X2uT+cx/AQzP4YEAYN6rW/6BXW4uIuQWuxgzKLu6yyCEy4EhqU6BiCpAbBxYySAPMz9rmJfzHMTXtnEnJzlyAS0kHpwS9QrAYh2+gIM/kLQOsY4Rn47wo2GyFdbikc75IhMMhcw/vq0TYLZ7M/eifvdQ/cyXvdM17+e1L83SSurxV/vxLXvxB/P/OyRWqDV9sjI4mJMTtqS0o6qtMSz8o7kUs4OYs7hukstTTxb7UX+hG1R4wv2p3Xq+CENa9TwZ/WvAjn0xfq8jH/6aXhlroYOHg+Gg4i4WDNpVoesk+yrBbNYQxTvm+W6vdfqtbdgKHjEYFp1rqrJXkTCD5p/TbZy2KyB6Z0tviiMeFWdtFu30l5a13EpRUFVVYkVE77okpoXBfFBl2Ofwb2XD8qSOuojEIf90p2FSdzAud6N/mJi5C/HklGAapU+XQa1kvnxPpSQS+Y890+O87LQujwY6oFN0grGBWmlalqfymSgW1A4tGbO5L0UXXtKX0INvBHSo3rTBVcsPpi5pwLw+pvHeacw+IGeeFFB/NjJTYPUQWqMZ+wUTrLlDkFRNVtkphPoxYAzacMXz4havbM7hZf/zT5jhjyFKxWHiUMPyTJA7D4lPLmQ1bLungauu3KJ1vPqfhAXjUAK65Sqkr0eMcBq12CgYDmGKqCn9K9lAcP6w/K
*/