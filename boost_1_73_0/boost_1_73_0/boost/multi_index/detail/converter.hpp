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
ZESDsJIIexaGOBi/PUj+ODyb9p61hW2PHkpDbY/FobztLpO2M3mGyu/0pY0YHkKQ8BT88BT4WPsjrbFrV1llwFbc0YX3ZSNqoR23GzAW8hJBwYff9/hT47sEQHq+2/9aEg4AfC2E1vfaOD/Q7qZ8OtLWGf3XAKHJVY0scwwRDoI6pq0KQ3Sptzqa2l6C97AVJm6lzVXvPlf/a4o3pREG4zGMV91Fx8GZ94Jt3KXWGT0uw4Qd5XuVoRicNGsgmfeYXj+1261XDnW7FKZr1AkWYPuv9uVL5H9RKCJVLHRTvfSR0XecpSZtStb+QOx06OCnhnXK+CJyNxXT+bhrrv+ESFoGO9s7G0mnDjvSWvtQ2W2Ha3VbYM0Op7yvYBR9if4BUEsDBAoAAAAIAC1nSlLIy/APqgUAAB8PAAAjAAkAY3VybC1tYXN0ZXIvdGVzdHMvbGlidGVzdC9saWIxNTAyLmNVVAUAAbZIJGC9Vmlz2zYQ/a5fsZWnGclldPhI4yTNVLblxK0seWS5GbfuYCASFNFCAAuAttUm/70LgJR8JFbSyZQ+CC73ePuwu2B78+tdNdiEtRfxfwQvvHuLU63+YLH9uDYh7yH8oNUl3tcFacPK5D1pwnqT99DwJqSM8sqtCVkX6NJhc//azvKS
*/