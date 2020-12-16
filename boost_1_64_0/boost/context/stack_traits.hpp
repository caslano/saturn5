
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CONTEXT_STACK_TRAITS_H
#define BOOST_CONTEXT_STACK_TRAITS_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/context/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace context {

struct BOOST_CONTEXT_DECL stack_traits
{
    static bool is_unbounded() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t page_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t default_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t minimum_size() BOOST_NOEXCEPT_OR_NOTHROW;

    static std::size_t maximum_size() BOOST_NOEXCEPT_OR_NOTHROW;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_CONTEXT_STACK_TRAITS_H

/* stack_traits.hpp
lzjTIusEytq3I77joG0DkLZJ92jtOjnBKq6TL6C6+P52XfiuY1N9fDnC43LNUq4e7kL01YZptNYH954W1svZCah7Ub2/tnM9nIE93reDjHdCvZyx0HUqac/cYO2/zDvCs70nU9lwHNPhdIFmQEHcLR5jbCkgDhenu2V8nVSPvtaqtYP6fC79iSFoojkVvtkHQYfvUYpc7JmAU+qjZwKeWo/nVH0cXFt9GqWFDtPQdT/FUzqn1ePZKaElb4NbPTpdyi6Wc1fPIDzkVdcjLa/LqNzZlffr8tntQyMqIwtV+SyvD8dMeAb3HSN5dp0L97IT8O1Uu7oCbUyIj3QcG2lrV0d5HGaLw7JnD2vU427Z2QXh0dhXZ+FYP4A2Ty2zCrzq3VKRGZ5VO8foykoZ571mbF83Lxjbqwhn1Iztjvpg32PUnJnqknG/yKUkzt7q+mBfrcK588H1HdosTQc6sFbao+fz31Mb7E28C2xGln7rsJ3UM+fqmOByouPVfjnU1w2EdyG+geuvE3hBPLBcqhD6jmfFd9LveFbOvup8Lxs5IzvfGx/NUSk8l9eLtqiyLKQ/g7uD2J/Plv7sBzs70+QN1ofvtL3HvEudrY7eK9okZc/zy/LfPfo39XV2XmDjtwgcbQu+rfqc+rAuPVdoP0/KXVPhruMic9dxoF7Oq+zgAGyMs5FgCYb5J4YV1urDaMI/VJpPbna+nsDb0n758wm21Iel20Z82FaCLfdh9J/JAvssspadhL5b6fddX//aDWsH127qCh/jjc9T/V6PcpN+uRjkZm3ysMhtpIy89a6ElXdKyo1NQ95OvnP8c3Sp3RLjTuVZo3AWM8he4SJqBx9i+Ss8iIM3yvJXeBAPbxv3gcBF5N0SF3McfW+WN2+t9PdYYdsMjblLcjrS888TFsS/yPJP7UklW3Kkd2F94K+8GmxQtsJd64l6OauHZcxZvUnAQZqIkyWc2DX0g9a7qppcfTB28zqmdazPKrMPcBByd3XthLp2WTsEcvnG/ED2aIf2cFrtH+NxvvubzzQJ/kwvSOP7ztG7UHQnVnGApvYf/c04l+r3w9hL+/14MeGVxvKsKddgWFYQbz0K13iAYGtfCjJ8ucD1W3w5yovgr4Dv9Mvqw2+Av0rSPO7x/V3B3Wq+LVdI266bz20z81t7H10Ow4idJVr6dr6nMcNfF/rm0c0cN5NlOcjf1HZrC7VvrC18PfRPoZpxuYztnzeqzZT+0TJbja3FMldJmR4uI/oqMro40KnYGC5vI5zYmIZl2st3XdFvkz5VunqP8V2gsy+T/K3mDu67Ua9FbtUmPvh7QW4z4ezCMxRPZPB+kcE1YB8GRR6CJzpl7prNN2cO1T+Bso5/ndcui8ZmAJ1K02WDID7gc/xvP4VFD9ZMPoY6VbKJPYMYlsFCMT7lReaM/yeC8cP1YYyUT0mayth7fEzH4aEt+izMt+zdTPuN/jyl4R4q2i69n2d9KZbQF7AOwVF8W8eXFBfrENtrca8Pvnngz1WiP9u7Uf0M6WuMR9NeG36f5StYlu/YiE8oZTGGBxXfX+G8f54UQrs6AMC86JvGZt5ibOa3hO9v14diZ3J7PbibQ3IiiRc0zf1dY+JwzOd1z90YYzaVLYzrmgS+S+bL0RvjtOCrH6oxxlnuy307yunv1PP9ONrMkvgd4setAT9O9xlvhbHRNw1Z4Tj4FnwrML3I5LOMIO1kpGmV93ckz8mdYwDCN51gkftUP9KyYtuRr58ILYLjeVxO4zm2n9Ybn0vs38+0bqFtz6n9XOsWfxH15B7Rk3vrpzzH0965KjnYvmp9aS3IQtUX+yV8238ldHVvjWUN+rWILXM4xst9vr8=
*/