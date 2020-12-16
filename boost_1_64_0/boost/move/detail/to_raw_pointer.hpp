/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2017-2017
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_MOVE_DETAIL_TO_RAW_POINTER_HPP
#define BOOST_MOVE_DETAIL_TO_RAW_POINTER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/config_begin.hpp>
#include <boost/move/detail/workaround.hpp>
#include <boost/move/detail/pointer_element.hpp>

namespace boost {
namespace movelib {

template <class T>
BOOST_MOVE_FORCEINLINE T* to_raw_pointer(T* p)
{  return p; }

template <class Pointer>
BOOST_MOVE_FORCEINLINE typename boost::movelib::pointer_element<Pointer>::type*
to_raw_pointer(const Pointer &p)
{  return ::boost::movelib::to_raw_pointer(p.operator->());  }

} //namespace movelib
} //namespace boost

#include <boost/move/detail/config_end.hpp>

#endif //BOOST_MOVE_DETAIL_TO_RAW_POINTER_HPP

/* to_raw_pointer.hpp
2Kawq7fXHK8V3nAXZsWZFfwarDZeg8nDbA5h44rkyiswX+dhEcdbQCe/yPS6J+ISB5uRGB2GbdBPX21sx0UPj7i5f31m1NFmVMw8MZGsFvTL5v0Z+bC0/ikL21TnOK1Vupw3Ta+m1c2p2IAw3fZ95wav6rnRq66i7+QWr3oMMcjP0fNLzV5Vpf+Xz/eqL9L/ORTuKnWX8sfj9RWVvjOf4szXEgW/I3a9+/kP+Fjr7zANm8gJQlOVemq3Q8iQkfyYMZG6wBkjp3BKDc/6p57hxLwsU3iwK+S1MzKZk/D+2IRHOAVR93weXz4uY4qjjMOkDMoNfoVhX07GAZHTOAmPfhraf1jDiSK1dsk/W2OWfEwiDNdwso+psFhTyUHlGGNvl8rE9v8PFtCsyJi9whJZIrMyWPokA+Kw3Y5yMrszQs/mUMnboLsklIDfMb3SkHPJsx2e3no7LH343Kcs/aeIGAL5eN57SGVz9x9+w+z/IXQlKH+AFC1IYb4DeH3fk6ivP4++5I3960u6PNb0E3tcZgGAOAARa4BFrAGClLQddD72mlE054ooTo6S/0gyLfvEJbncSptth8DC9jhKWR0CxaKjzvJVz1RqtwZuu9mcrBRaPMTctpjXjWT0PNNXjdcUlV7d5G/7ReA2WOVLYR8MpeZ/gsCp5nnCz3OVwlMVyeef/AxLO1a13mkKk7pihqg4baNKud6mflyJBMndnzyTRPPc8kZIeQIf6SJ4HlMsLYRDl9PPCop+SSleoK1eXnhHhjYkxDJBN+5P4BXZTzO0Nv28mug3VhMpWU30nui2tTb9vZWCQFiwTVeaj5FxS8okBh5wGgAMjjmdPfP6zRSiWVJ6P02LD+6h0YJJLMVm+lpaBE1tW1qiEp4xOT66LEupA+h/tc2p1LGh7zGg70nQ4zWmUqc/qTlQ5YfaS3oFSXmBFi0FAQdu/+I+QKjC9NOhpytjpRpVe+VsWz2nmOo5hdeMqqgQDmDw/hd8LH44ajvzF2O8C3OZ4eQ0H8iWaUoXmzzGEPpu2SzDHUP/MLGoGFJTa+oTZl2YpU+45o1C+gQnUGOzgbpla1qyDXX/0hE/Hc56NRq49Scec70aXcrr1XOWGutVJXtF+qwn/4r00S2WjLwCSZi4sCJdYi0p8q7+2j35V38Ru7w6JOGllLmwwtpnIq19TuKB3Fc73UdrppewH3GPuSr8gmma2E8DC2umEpSCkV0b6o+eK/CR0++WEeYqQ5EJUcZKI9tqnfkpMVboN4uWOP21h0wbLjhIUASK+HRf791ZS4sf2MuFWRsNyslta8tjZls55eYtsk6pp8zOpfbnTM25gnVKnj441Sqnt1wqht7ll7zwNYWeluvystlxS80lJpN2rYCA5eYC1nW/aK6TB2obwDW5jOrwgBTjDQ0YaLO4ppVC2H7Sb5ETFi2fxaIlz4otutlatDTJlR0RtyysG2lpgrupbrkvd2kiGJfRMjUfYo7Y7FyaHKGNd0t/wg3yQtl7WbHWsTqZs+y8uFe9k75dS7zqbxJe9Vv0fDs999B/Nw0OV4m7RD60KCl5Zz5FWe/Fu/4/P7b8T1QZOU06zq/f+oRT/hcZN3IGx2rgDvqcJyyZ3w3qPw0S/4eRQOTymgdNufxUQ+KfaGgfFFu0dQv/Y011JQe9JRk3b3uaH3PI5+fZ8nkjwygDVG9/QATxT0ggBkplo36dhDJAlZb4LYI4hPMDAdKSv1/ZfCDy9/u+fADy90X7MuVvldu/uZD8/aQJgqnvwTs3HU5kAnIKYK25kdN6vc/VMoa3K3y8STmAzuSLtcgEuWmQ9FumVcwC3q+dG1hLLtK6SzixWhtO0cYPbyfy/DTWOKk=
*/