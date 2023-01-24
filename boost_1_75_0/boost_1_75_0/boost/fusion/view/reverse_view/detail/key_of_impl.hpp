/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_KEY_OF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/key_of.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
          : result_of::key_of<typename It::it_type>
        {};
    };
}}}

#endif

/* key_of_impl.hpp
7E1dw4PVRCfiLUx40yjH9nAFQAE5nddGbt78VVidyUJ+H8oTFptWi7C1uMQtdZuhBr9rKdduq5yO3mu+2z/hAYf9hZ15LWXL8P6tsFHn4Tc0rb8KsL6eo6FhtcMOUQdv5bz/+XpP6+hrjqG5tLng0h6Irrd5i6zp3as2t27dOotcK9Be3z+wSCIyGkYiR8TLQyENoSHFMCyij0QUu9MjMPythgqj2r0NxeKUAuoo4Qmpny6yF4yQWSZCAYhPFbPQYoZ4BSIWiTlS7ZBYAD8TyTVgLSS8c8dq1pOOK7WgB0V5cYAt44hKehwLpUhskWtDaoxNQz0vP0TqoV8xhK2WDnSLncIzVnxA+E/qKgDOqc1kNAnaJUAdiihaFFN+N7BKZEHmokQ0wka2mM8Q41CcGYTQvkUKLurMhM/MJAi8SwECphQ1P3Zmxh5cn1AcDrGrCBoszpgBAUjlYvcuHFJnqrkYiakfQi/u7puVErWJ6QABV1M8QhAT8YKt9RaQQA85XXkzHUOdCSNZhYl2eAZxidBYEOa2NOE0EojwzGzGQZ9JQWTBU9Tszi/m4zsirfEfmx6KhE4OICsGsPcVslXJ+KHEVxMDLnFeZ55J8Aoj2R6PVS4XSquah4BWy8RIPZzOjHNC7fuhMKgnQmcURU4Cnuz3hNwyuQItKo6dkxIsAfizWEGHuOtfPAmCCUqmKJvAIAvL5jURq2HiTMIC
*/