//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_MAP_HPP
#define BOOST_CONTAINER_PMR_MAP_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/map.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
using map = boost::container::map<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options>;

template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
using multimap = boost::container::multimap<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options>;

#endif

//! A portable metafunction to obtain a map
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
struct map_of
{
   typedef boost::container::map<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options> type;
};

//! A portable metafunction to obtain a multimap
//! that uses a polymorphic allocator
template <class Key
         ,class T
         ,class Compare  = std::less<Key>
         ,class Options = void >
struct multimap_of
{
   typedef boost::container::multimap<Key, T, Compare, polymorphic_allocator<std::pair<const Key, T> >, Options> type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_MAP_HPP

/* map.hpp
ayCzmZnjEaxNxJn7D7Bepb3IeU7rgb5ZlTBoZ8XOiDJLMVsxv2JBxeIVS1QsWbFUxdIVy1QspFiOYnmKhRUrVKxYsVLFyhWrFGaO/bBqYfx7jrVkXmbmvADWRGYx48+7tSm1dCjWpViP0t6AEuca62weMpuZ2TZhASUuTrEEMqc6U0Qcfy4vTdQy/bcP9sOyhf26bF0nrEDY33dO2QcrI/MyG7ry7Xdh1cLmP7D+LViD0r8mxVpEzrc2TfkA1imWizlnh/UKq772hJNhETIfsxUnXD4A842LtuLkBXWwRDKb2blFG4pg6WS8zg1XvXMMLFvExcYmfggrEPbKtTsfhZUpVqNYk2IdZH5mSRd8fhpsQNgL+/YEYL7x0f0z13iweDKLmbnPDEser+x3FUtXLFOxkGI5iuWR2czMXBCsmMzHbG6iOxlWReY0ButEzjNqjyyGtQh7MtLeBOsSy3rJgvTxsH5Ri7k3CPMmRtvX3hOvh8WT8faeipRvgaWKuIaDNw3Assl4Lea9SFiYzM/sq+9iT4GVC3tw09YGWL3Iae5hwlqEBVwvr4V1ipxtewu+gUVEnPlmP8x7fnTcQ/f+ZTcsgczDl/XBsRtgSWQ+Zmtuf+wqWCZZPLO03zelwYqF3ff1L4fB6kXOhiO9B2Btohb+7cUOMptZ2Ywvr4T1CUse6zkG5pngbAHFkhTLIHM65mSROR2rcpW4fDKn/XwxmY9Z80XfnAGrEnW++swlZ8MaRM6i1UvPhbWSBZhFvlp7LaxPxN2YWPUhzH1BdNxxhz9WB4sj8zN75PKgB5ZGxnN+tyyuGxYi4/0b99GuUbACYQ+03lEEKxc5L35t8WGwGjKb2fdXJC6BNYm4Ty87+UhYO5nT+usmc9pHRsic1q07yTnOn+TcXnyScq4v4jKOT7sUlkoWZLZ9UtpmWJ6wD0a0ToSVJznvW+uUPrQofegQOc11HKxf5Nw7t2QxzLow2hKO3b8EFhS2+IdJdbBkMi+z8bNrLoNlkDn1L4+M98H8/gOsULS3uaykHFZO5nR8qBE5yyo/GQtrIPPz8XlN0yewDtHe5Xf9vh3WJ9r75/GT3oK5J0Zvm7lHfXErLI6Mx+1d+uTJsGRm8niUQea03nPJnPZZhWRO+/JisiCzxCGnlMNqyZz2Ia1kTttYu9KHnolO43Osa4DlPDt2DtvGaFVd5GwexbyK+RQLKBanWIJiSYqlKJamWIZiWYplK5arWL5iBYoVKVYizIwlWJkwc/0OqyCzmQXfnHYsrI7MYsbHWZNibUqdHYp1KTn7hL3xRMcqmCs5ug+Vi85eD/MJS/i0/xFYApmP2TMVj5wISxd25DHflMByk5V1q1gBmZeZ2aZhpUpcuWKVIueW3SctgNWJuGN/PmMerEEslzUv5HbC2oTtda84AOsR7YVXL3wWFhF28eo3v4F5L1b2IYoFhK0urwnC4pS4BMWSFEshs5mZ4wMsS8SZb2jAskVcwrvn7IEVkHmZvfeUOxZWKuLM72/CqkV7/Hm+WmZxvA9k9Yo1KtZMZsH49kfWrsR1KtatWK/SXkSJc09yNksxWzG/YkEyVie7b3iPK5HFjeLz7GTJiqUqlq5YpmIhMi8zs3+B5ZP5mfF3msrILGZmPcCqhOUu2PIMrE7kXPq5+25Ym7Ble9/4K6xPac91SbT9d9W318K8ZDznuMu6mmAJZF5mb/7z05GwVDKbGX8OIiTs3MQz/woLi5wn1e3dDysRcQ/n/LIOVkXmY2bOy2GNon9mbg3WKuL4u1c9oj3MQ5PRPzrn9KY41xKvxCWT8faGbP1uxiE715VJhjE4OvaewTFIFlIsx9Hot3HJsKzH0LdTzH0=
*/