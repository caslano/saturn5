///////////////////////////////////////////////////////////////////////////////
//  Copyright Vicente J. Botet Escriba 2009-2011
//  Copyright 2012 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_RESTRICTED_CONVERSION_HPP
#define BOOST_MP_RESTRICTED_CONVERSION_HPP

#include <boost/multiprecision/traits/explicit_conversion.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multiprecision/detail/number_base.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class From, class To>
struct is_lossy_conversion
{
   typedef typename mpl::if_c<
       ((number_category<From>::value == number_kind_floating_point) && (number_category<To>::value == number_kind_integer))
           /* || ((number_category<From>::value == number_kind_floating_point) && (number_category<To>::value == number_kind_rational))*/
           || ((number_category<From>::value == number_kind_rational) && (number_category<To>::value == number_kind_integer)) || ((number_category<From>::value == number_kind_fixed_point) && (number_category<To>::value == number_kind_integer)) || (number_category<From>::value == number_kind_unknown) || (number_category<To>::value == number_kind_unknown),
       mpl::true_,
       mpl::false_>::type type;
   static const bool      value = type::value;
};

template <typename From, typename To>
struct is_restricted_conversion
{
   typedef typename mpl::if_c<
       ((is_explicitly_convertible<From, To>::value && !is_convertible<From, To>::value) || is_lossy_conversion<From, To>::value),
       mpl::true_,
       mpl::false_>::type type;
   static const bool      value = type::value;
};

}}} // namespace boost::multiprecision::detail

#endif // BOOST_MP_RESTRICTED_CONVERSION_HPP

/* is_restricted_conversion.hpp
e3O88g06CSM/4H3C5PVZ+she9z6cV3866ft3fifham6GbJT3VVjmtrUdNF9u8k4P5qrc+zWwxtmMiwZHnQba0Nfy7884vLyqtDQ56ogYzOdo/dBdjMfKKuW3ySE95Ft4T0bjaGWUzgVqeKWeZPEjT1i1wwq3Jmt9TYbTDlJqH35u4qwRxmho964/qI3bvI/hKuPxHaSUn3cxDts9SvnZyqnGPXTW6MFNjpkHb2UcvhOU3hvZ3c5ZWa8fy6hcQX57XRsfj33iKmLNpfbvIU0uO3OoxiIaj3ZYajZ37DHx/qZ59dYmtzWv9j20yTPz6nyT08irJ97d5Jh5dbHJaeTV0x7W5Jh5damVs3lezext8DfNq+tNbmteLT5c42E7UzeI1JZpeG2DMPEIDavEqG/7WKNv61ql7VhefKd9W6Xv+UxfLiLXD1LXt9r7oUuQEL0rKuPI7o5+C9OXiqx0i8i3nE30LZxpqjsm6nmfr0DbI6ox4iqsVa3Vtxugj2ne597ST/ZLoWmdWYZ9J3oezI8oXO7EfkmnUjN4445wvL8ACMqAlt8ro+0cWMlfYvk9pnh9ZusZyi9/GWF3UMZx6PuO54pZvBFXuhUE11fIOzgpot1h+TR3iN3R61h2nNhlLqDffhLunpxaW14GFfiKBd1paqtzRsx2IhLfSz3bTsQcLF0swsutm0eA4v8DpiMUeRJntpUlour76ddgTslr8it5S8nfYvKBCCw/LayyFLAKeRoO5+DlwHAfcL1VicxbE2od7q+afCpS3808184FtkTMIjzzp2w+9q/c56FXeKXluwKbptogdsN6p3tLZBJs+rW8y+RLEeZOWMRBWMvTGZjNVCk9i7oexxGO5SRpEgpslWtZfDNsAcSrG5FlI3VkSnbpxOA89ltYfDyRlJZju3YhugtYBsBynZHYZlT7qUj2A4YvgrLMwtz2dNkVvheL8v4ub4jlXZQWtu9mkZBur65OhiqBBUg+bVI7cspW43FmOxJBUTpJ6QVKHsrdmpQ/uYA3V+NzeiovTqk4XGc6ApEUQZDnlivgPnq0iuKzkBO4/0h6odIgKnncTMjTX6Z+moWlY8qv9mc18cE9sHuYvCsKN/DKMs11eZDszmvSyvYkk/WEa+Wum5WuKctMa7ZTw7ZT5p7lZYkh39MTbqv9w0vDzPehn9mh61hC87VR9cj3SkeX2U9Elrq553mxWFhc7J3Cy7Pl2cpmCQIdKg2vMfxvp2Xph3Eu6CUmWZWoKuv+ezuTDYTvuXnmuK6Qn/Q6+qSHEmAp259g8o7wyqRMIjsD+TMg0eUFj7c7H7igyWbC9lwvD0uXRLUM6yl7r3z+MMsvz7Fsp8wCJlRX7/lKmOJ61Yyrk6VWkKUkO2h2qL2it3x12VIUiZXnUWgLuQm+/u6ur6okanXj79y/cVmWdpH4At4rWl7FmC6cXgAXw2PVcAf2wL9Kfg+TD0WOjUNceiDfx4vKoWjjOitmEngZF6J42/SDd3B/+ZnjF26esjuWebnap9I8o9suRJCncejHuViCr6H6NEH70vBV+ALNZiEyP7RtKy5QjmJLclp56II9to+1sN0oTlCOPqJm27HG/GOLwg1Dzy0CENKyk9nbZ6uyy2RjkRZJWBaFJyo5FDOLP9VfX+0dZjoKkaZBkeRJJsCtKLQI0cbt5YswVJDuln0K8jW1JUP/4HEpAycJksAS9R7D2gPVHRj8o0x9kb2GDj9xCjssUkNHb4np4PVZMB2uyLIyjTMnFNUexloFugWb80pa5d+541q+lyIOgzAOPQFXsy/BQzdUZlj780pmLxC+FdlxWhYDKZg717Zgm/XjS4Z8WDhB4AWl0LdmY6SpReA=
*/