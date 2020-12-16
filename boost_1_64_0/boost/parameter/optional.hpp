// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_OPTIONAL_HPP
#define BOOST_PARAMETER_OPTIONAL_HPP

#include <boost/parameter/aux_/use_default.hpp>

namespace boost { namespace parameter {

    // This metafunction can be used to describe the treatment of particular
    // named parameters for the purposes of overload elimination with SFINAE,
    // by placing specializations in the parameters<...> list.  In order for
    // a treated function to participate in overload resolution:
    //
    //   - The actual argument type matched by every keyword tag
    //     associated with a predicate must satisfy that predicate
    //
    //   - If a keyword k is specified without an optional<...> or
    //     required<...> wrapper, it is treated as though
    //     optional<k> were specified.
    template <
        typename Tag
      , typename Predicate = ::boost::parameter::aux::use_default
    >
    struct optional
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
    struct is_optional
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_false
#else
      : ::boost::mpl::false_
#endif
    {
    };

    template <typename Tag, typename Predicate>
    struct is_optional< ::boost::parameter::optional<Tag,Predicate> >
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
      : ::boost::mp11::mp_true
#else
      : ::boost::mpl::true_
#endif
    {
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* optional.hpp
YzO+r5qXc/G8XFYibJFRbuiqfMSSnjNBX1FmlJ13jG8KFHk82+BdRL9bi8LfuWo7jjC9z3WGlrMLCrNFmTpF/vO1m8Ct05TGGjQ5kzyib/k90SzCN60IohkTY9DIfbqET7kGcr4F0XNfhNpB7G/FmVRwoI2heoL5A3LIg8A2z8wDXQ8NWQ+yTlN/MIivYp1eCefRdfqpt05xx0RmnmbTqegH7CL6rmpdwk9aP8vyBx6r+JK9oyn7jwbxP1n24XB1k/QxvZDdS+4T1J7qr6vkbki0aUq5EY5YP9kLejoM9y1ijgqPjQqtXzVme92sQ0x3Du4FvQ7VC7XRmM8nYpyvH9blbshyy3k3+yees+B7xMLwZwxoS6X05+vHU+vT1fa8E+OU9US/E1c2B+Mk5LoqXXCYLlGOXVI5jgXeWKH7Jivtq8ybTHlFUunzchTPPYa/6yL8XQF3QrXPUxkOaqT6XBnQ2uyzqHNdWFZV3Y7V9Un+Q3EvTKR8brOwt/sp7EuhrVb2us825jOieQAlC20A3+FdqIeLMHm+mOrvzTG6q3ldNu0p8gTvkCfSnAh0hHeka3rnNt+R3ix24Bcjoj+Djbmn34A/oCyVV1SVJYzYMtNxV66mqE/t2C5+RvTfBetzUN/BpbhCtMeCQrRpMO4vwu2CS6QxFoeNGJ93ZWmNgwq0F4IucUllDv7W/C4pyhyTQ/p04bnRF9Q20nOQLjs9x6jKoAgrVoRlHLNUUAg6Dq8p+CEPytpxVflDGMpyLORpC374CnmGfK4/u1XlE2FZ7w0w9sU04/KzhHi/CmoF7nFwg1wztXVBYaozkBCWdX1/Ni0aacH1201hbQjegF7pn3CfuOZo/fHBZ3JwshaPvEiQ8uJp13jkQ5zIB/azrHmgeTYxZvuJ0t1HjM2/pedtrjItzqXXn31UkIshD8+bG/IEtUPvpL6rj1aGGwcnBdXRlsKZ5xx9CxqEEaTqX31H4a915eMGRfNc9xFf0rcLn+1sDoUXIdrZWfTcLThOaxxsGbuKdNxK8cQHFWpl8hyBsAMryd+NNJ7TolmPBXiHcIP0MLsY9HShEPKN5nmihT4KczC2YNuAfyR/V+6juFinK1z18e4uLdGlt0FlsPdpp3FnPn2XuxcLAsPrULvDfsXwO6a3T/Xv7imPlWSaBaA5Svfy332ZGMtZaDaDZgqNue6KEP1EC00FaFZQG3dXrkmz0txvzjThZ/Bdjvqbd50XFVzf1p+Uz95MjBHnbxJOhfsXeF+CK4QffuO9gd/huT6/O8F8QDwLOrjA81yK9pXtKdtJtjfxsj31shuwqQo7G2eek8V1OlY+14rrphk3yh3emXMmoJPmgUBDZaaL8YxyxOsN2Gaf+EWMNQXm6zb7a7LZebl0pMvQ3kOH9hs8KH10YQ73iedS+52Xq6nHU+D3Xkdwkd91BMlefTU97IYctizr4bN2WeclohypZKWjYFlW0LiwfmqCUlbmZ9v0MNFmgdbHWl1Lui6rTrqojJAcoowgPrxDfOZaT07rzF/taR3fGPNqyrTClqbjo05+kaO8qbSkoUV10iDljSyv5ze7vMMhr3ZUJW9hDgbnOZMcliWEIfph7zeitkmZN0wnnUtds3SZe1QRF95le6Uz93d7OjfCALmNdOIz8uCeQ9PSh/QemtavV7qnwCPVmabGvMJ4dTo5DO5fDGqo0+q8o0smZKnLItNL4wPn6W1K6YUs0lpSxIl3Ik6vvl25It0PJiFUke6hPYfpdQ5lMS9Pq5rjcyCTPB4rPqeo44gnxTse7jtgriaATlMsOtrhQB5TR40kHckyJvxhl3EOZEz1khF5zzImBZAx1SLjkmrUxyQfMp4=
*/