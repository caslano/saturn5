/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_SIZE_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_SIZE_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/rank.hpp>
#include <boost/type_traits/extent.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct size_impl;

    template<>
    struct size_impl<po_array_tag>
    {
        template<typename Seq>
        struct apply
          : extent<Seq,rank<Seq>::value-1>
        {};
    };
}}}

#endif

/* size_impl.hpp
FXvzm83Ym2dvEGawydnUm3mabVYO7808ddQlNIkYZ07LJ5lPaHESychIvT9XKsXrALBi5cenYBx4UDUdn17BEzDWG5+HAvpaJm7oLjrJLHLRjhqvk2XNNnKSDgZhuqaWhaQtrXJPxnUFl7A51JNZ/+YSluVwaCJcM45vwKMHF5hgbeZ3E7v4Jcn7FlJpWq4LzWafVPYKnNHuNc6/JoqDa832zEQ/hApeK/2cNk8PzTOLvoIA5d5NZLjI+KKxN8k9nEX59bUh9+JvJ3HVhT9fK6Ln0dvo+WSRyb6aNB5UYpKVW/UFCMy6QunhuEvZx/h4POOWo3z5sSyrv44YAgzTSgwT/QsyzKJfkGGOfEzLD3Tw+vfVtPxYjsuPC8fzyQDjYi6W8Ji+GOEmoP1m5hDnFCPn7ADOKXakfjCIJMFDkfxmxxfJRcIyDGE/HoYQ7wdkTaVE/SJzroYwuiD3Rw3Cw/xZkXpEpYhAv1LX8NyWG18uFwmQGS7HL38gIabwfHE0DLqE8AHy0grb3Oc6Kl8daCETf/WysniLjjdUoI69j6yaC5ovM6ODDNVst0wgHPk0qg43ba7jps3DJiRw4ano7l6lku0Wopju5cOEroDhrfNJ9BbOcUwR4x0Or1gfZjx9JvZlqnMgpVjBUyCudHfe0TCSHGt/gDWMcJ+iPnGEsKdGRVAGT1FGyV8PJG3mcP4tfUVVNL4+5w/6ujsS
*/