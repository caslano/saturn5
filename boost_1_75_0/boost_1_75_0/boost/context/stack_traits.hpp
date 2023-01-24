
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
am+D9o9JPeFCh/rwOjaL8LFqxDsJxiFtosOTRveIUEwQTPv4HFoSu2juJ/8+kX3p70Ao+tiJ2EWC0tSO8QcvoIfXGNs1jIGFM+jMUbs5CzsnLzJ8LSgXJXm/CMVVpopazBKKtEp8ZvC6h/WWwd17DF45w+RG1SjmsNLJ6vAB3VFhDpwM591J0RJ63QaeHU17i2/e+PhBo7eAsOIKiI4QL49aWgIHv6Tt01fEOoNbeIT2rxRRSFZXbWBz5Dl1x4jazA41/yHcF1VVdfaIi585/v8CADf2q6NeclQqgY+z0dMJkR5kBpU+oK4XKBRoz+n9+3jxcw+x1X8ISxl85Ei2SZuYFtcRDoerQfkDTq0byiuSalHi1wqsdQgvQ9IPAuW7I7sJ8/ZEawXIeI/G23SJZPLJ5IwJOcH6bLkAmgSgkBUofIrDpyaRDltHYbYhuUdEQbbOh6Qh1+YBJNM/dRUisuYpPOjS748E4RLpFyvSnA0WhLdgnWE4hHG2hvMzSlviDMhMY1ngvKdfaA4WUxYVqJmh6PVYVHXgN3JFjaWqF4iyROgRMofeqR10JohB/lUnnlu4Ad+axCkS4CzhxNsQDl7W8D5aDyt5/DEM4lfM8fDVovk8HYtoXITIA8RXqXZBRIuqa94vcY4rQNBNB26LvML5z2RJlgnKRRsCXA375XlOLJWPnknDftbA5cMl6u2v2wIArj331LorjRLr
*/