/* Copyright 2006-2008 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_NO_TRACKING_HPP
#define BOOST_FLYWEIGHT_NO_TRACKING_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/flyweight/no_tracking_fwd.hpp>
#include <boost/flyweight/tracking_tag.hpp>

/* Null tracking policy: elements are never erased from the factory.
 */

namespace boost{

namespace flyweights{

struct no_tracking:tracking_marker
{
  struct entry_type
  {
    template<typename Value,typename Key>
    struct apply{typedef Value type;};
  };

  struct handle_type
  {
    template<typename Handle,typename TrackingHelper>
    struct apply{typedef Handle type;};
  };
};

} /* namespace flyweights */

} /* namespace boost */

#endif

/* no_tracking.hpp
k7Zbkz+pocJvXHNFWGzjfxZH7DttrcF9p8TkxoXtKKY0zjkNSqPJalQad2ZG02Fu/jbY8Ev0LswVHea+3DDY8NdGpnt0Zki6bwa6x9jrHegHtMN/W3G6yTBuO0ZF+dJd4Sj/6nJBedPlFP+5l2HcGuowc1FEG/uTGeFxpVld+kieC3GSmpgRDc0Hd4ajuePlYdp4ly9iG59Ij9jGA3gbxzoD2nhlejT0XhOW3imXqeefL6Pzzz3Dt7HVF7GN/5MesY3tvIkToyLZuyMcyR9dGhDD4gZ9vOmpC1VQz7m45Y3HOTDeoTbPLkzTq8M7uDp8j2SpeTYWDoH9aKleGovH2EsooPH8bEDdZHmUkWczGUbLeGzcezHqGI9czf6RVIjCCmirKkSYVayXpaHvPwAjgufuXJ025T4PoiSTrt1k5z7DubEiAWnSpQgOqyIaNkEmr7EbzzGzqzV8kMA+aLkEvG7SJAjOxSlSzxgIvW22prcRZdWp/FSCxFVzNQX8LMV7h++GUh40iZHiT0kzmaoZARQncK8K5oc4azWn8bCQYu3AMrZ/iraIPoTv6DqHE6VDD6kkDI7WXTi0KaPosMWqyxZW+TVH3Ol5XwH31ltEpi23QGYlkhYI6vkHwfC3ORhO7zyeEgEcLSqcXi4+FvBsrTg8mzu2UD6KCG0rzITBluXwFftxalzrkL/hntrL6KWlOhndDDjATPOZ04oi
*/