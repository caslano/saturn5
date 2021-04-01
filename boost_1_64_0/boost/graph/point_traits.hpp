// Copyright 2004, 2005 The Trustees of Indiana University.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
#ifndef BOOST_GRAPH_POINT_TRAITS_HPP
#define BOOST_GRAPH_POINT_TRAITS_HPP

namespace boost
{
namespace graph
{

    template < typename Point > struct point_traits
    {
        // The type of each component of the point
        typedef typename Point::component_type component_type;

        // The number of dimensions in the point
        static std::size_t dimensions(const Point& point);
    };

}
} // end namespace boost::graph

#endif // BOOST_GRAPH_POINT_TRAITS_HPP

/* point_traits.hpp
C7A7Ils3C6X+v9+qungBokWgOuW+ikhhtvjTuVVMc95WGWD2EypJns0HY/fhZ5eny0FUPG9SmWZE9CwHvpddyKZsXQZvQLXinM6hRb9Lh8WEtcZdzj7QCvG8K2hZHXvhiKAhX9S2mvmPTr5NTh0QCY5S/72cLtzVXDDGkkOso/awij6w7jTpRc/1i70fmZE0GsochNZjicizcfesL4bVapGg+WMyo9hubF6mr34FV9TLt6UJKZLeWWFubHyzn1AGG0iKGlSnLQMxehv0DUez5LN7nc1AQIESNOm0vO9Mj4ghk1QU/PPlgBNeLpNdDNSpgqKqBd+XaZkSCOHsXriqi1TfWMQbqcoPbXdDpj7AfEmKVoyKz5QgziVFg8VZ5bGLZmVTKqefGJxjCPBTdgJaWEf91n/tUHFVbvCj9fmGt25JdpSzuTB4hrTV9ojJm9sc7YDg4NdrKccXV35FU1zPQ9xrKlDI2VjHlyDRsQ76C7kkGP7Ka8uCTmTn4+xpSBnz1f6mzHRwRrK2vqJKEWcura8gPRKmOK2boV8Xjb2FhKU7nX4GNQs1YLh6OA==
*/