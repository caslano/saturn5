// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP
#define BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP


namespace boost { namespace geometry
{


// free function to test if an iterator range has a single element
template <typename Iterator>
inline bool has_one_element(Iterator first, Iterator beyond)
{
    return first != beyond && ++first == beyond;
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP

/* has_one_element.hpp
ukFKkGXpDulc6Q7p2GWBhSW2nu99f+/rmzl35s6555zbc+Z3P9zlQe/lR8YJHt8Th30L658tfY7acmzBEYZee8A8vdwUQqmkBuvWk06MvZpOgmMGHLsvApMvF6feNG/hlk4CXQheLm2v21+IAtr9mS4napEsIbknMg0QmG57ajBikeflLQMvb6c1d2uNym4l7X03KsYRy6sIh/u2RVn6BFq/oGvZQcYlAodNy82K6iW7jdMx7kDWDToOqf4zWHnPnt4W266YvKwowaYsOE8Pxe5yM9UO+8jBWqdn0C3ojfuRoNGMgFK6XnkWmOzPXWWj7wzc8/WoJQ1W9njz2/t5pqXYo3p3eclLSNw/Fw1Z8f0TftLp1bA1ZakNbdTH3t+Ia+36TWBw6t1CQJynuqqjKDppY0C+ca39QDoze8/rBZek2dVR6dt8zQaVC+FprPy7P+r3mXToVkEyUQeq9kqs7EPRfsqtXAa6a4npA3N9TL6/+/tGoz9OFFqUP7mfENc/ai8RIURv2vTwvICtotv89e2V2LtHKVNhcvxjs9d8A6SazUfRejybKoklZu06x0pv9nInKLofW1oLrTa/cXqCC/rzaNEjpDQVZF/zQRquWveEf2Xux9biXUziU4Vll1qivpNwtznswMWndah38ZrLN9nX73wDJss1V/UGAGSjQRV6D30X5NRnzTZZMt7itNwPpjvNbEaZ/SydgXKg
*/