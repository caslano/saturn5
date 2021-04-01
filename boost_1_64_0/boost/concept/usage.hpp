// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_USAGE_DWA2006919_HPP
# define BOOST_CONCEPT_USAGE_DWA2006919_HPP

# include <boost/concept/assert.hpp>
# include <boost/config/workaround.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts { 

template <class Model>
struct usage_requirements
{
    ~usage_requirements() { ((Model*)0)->~Model(); }
};

#  if BOOST_WORKAROUND(__GNUC__, <= 3)

#   define BOOST_CONCEPT_USAGE(model)                                    \
      model(); /* at least 2.96 and 3.4.3 both need this :( */           \
      BOOST_CONCEPT_ASSERT((boost::concepts::usage_requirements<model>)); \
      ~model()

#  else

#   define BOOST_CONCEPT_USAGE(model)                                    \
      BOOST_CONCEPT_ASSERT((boost::concepts::usage_requirements<model>)); \
      ~model()

#  endif

}} // namespace boost::concepts

#endif // BOOST_CONCEPT_USAGE_DWA2006919_HPP

/* usage.hpp
nYZg14xKXzhO27KQi8izC7MIuRqECS3vihkqvozelE3wQoL5OhuTyqCnbSCAyRXm/N/w39j9IyPEJeLGhFte0LB3iEUTVtBynEf/PPyNtmLMp1jAKwFcJaqsXirkLeh3RXetdZicIYXC8tB9ybth0XX5okGlfDbI143VzqMrc5vemfBzClIe6o1zPhJHmUP9O389ultGI8iPGvj78YxPoTmwtCcoI/FuitsUKzjHtYQPb/cgGtNgxhxcCHD7MeXRowzVrUIKar/HUK3WkwDGaz7ZrJrrrqz+h1ASh+nLYwUdZ0hYNJTcuGBKpztaZTVQTx0Y8+Fi+F5EwxrRqQk0EQhoHOa4mZFuvRJbqr/4pG6W6ytC7qhlyD+gd0jYV+MIniq3IJ+bQw77hTqBB5LpxmCxDfzNK3/+64OUqQUql1B4ChZ+L9oZ7PQEOgSZQ3PEf+oCYaSVht2faTOyU+/jNZ8g/UNS1KgckV9BYP2Jv2C5nTRCdpF6ulRlYxNlSwU4AI0oYtJocl4SlwCVktWRy3DbEqf2rcJr5ArIg2iri47Wz4BAllvTZGHU3g==
*/