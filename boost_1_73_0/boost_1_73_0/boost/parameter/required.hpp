// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_REQUIRED_HPP
#define BOOST_PARAMETER_REQUIRED_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.  In order for
    // a treated function to participate in overload resolution:
    //
    //   - all keyword tags wrapped in required<...> must have a matching
    //     actual argument
    //
    //   - The actual argument type matched by every keyword tag
    //     associated with a predicate must satisfy that predicate
    template <
        typename Tag
      , typename Predicate = ::boost::parameter::aux::use_default
    >
    struct required
    {
        typedef Tag key_type;
        typedef Predicate predicate;
    };
}}

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/integral.hpp>
#else
#include <boost/mpl/bool.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct is_required
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag, typename Predicate>
    struct is_required< ::boost::parameter::required<Tag,Predicate> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* required.hpp
4eZuDJ97o1FvOL6Hm3fQG94T1p+D4RXVmxOTAnzMFGpiVsAXWcoxdoS/7iHCK7Sn44KEz8DWrRlJMeNzaDYzJY2MZKqDZnOGzOQkhqpmooRWEmjNpwSKXJLB1CKwzyjjPUKtQ63aG73/C066cAEN71/PTkumuDBQudNsjm2onR2SN20bU2u4rS14U+Ymy03TtXQJv9kxTkSl43DxkSr+e8f75nmLNdRWCTPdmqX/++Kh45HmEbLYVbIAtHU9PobLs1vhDr1bIXSZoaj370YffagUiOcPFbpNNlRwhEqfiVMDcyxkF8w0ndo4aTR7Kdbh0ua/2ZnwHQ10IY3qNbqinG2Bw2gHHBr2PFEqNfUfAdA5fsj8D3QwUUHQeeqrYLL6rQ311qtGjQLeOoFd0NRThm7HwK+dO2towvXeXDfkQhrQeZZJZbt5uj4s0w5orjCrnwT/1K9wms83Y8Wir9e4kGq9uUbDUi6+bj4yGmhbvE0/YaovxZK0cB8cRuNAFDEVmz+rVqmASuViw+LzQZH6N8N3A7r0KjqBolpnD1RjZ+nm2bKV3f+T6hXA+xpGdKVkRe9Vgc+FJNeOB2lnqDWTbmb77akufXYsxUjkpPXwOP62HY6rXwggdw5Dj5zbubFrZdcNFPNFEv8pnPql
*/