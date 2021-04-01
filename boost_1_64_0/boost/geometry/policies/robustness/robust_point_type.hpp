// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2013 Bruno Lalande, Paris, France.
// Copyright (c) 2013 Mateusz Loskot, London, UK.
// Copyright (c) 2013 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP
#define BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP

namespace boost { namespace geometry
{

// Meta-function to typedef a robust point type for a policy
template <typename Point, typename Policy>
struct robust_point_type
{
    // By default, the point itself is the robust type
    typedef Point type;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_POLICIES_ROBUSTNESS_ROBUST_POINT_TYPE_HPP

/* robust_point_type.hpp
N1dQCaFDFXMNrlIUTD0D2szyb8uEAyx+IiHG+5+DnbLYpuMixxjcQWZgMoMZyZPm+qUgseSvaC4IrixfWaC1NAl92A/NchdgKLW3OVKCIiCFTPcphE7yo8AQDkK65stZGzsItWKOR8BARtHFhYcKt14vwj05ufG3mw0gzdXiN+fk1Iwi6zqzLIqvwg6xooqyKw85qsuyAtGTqJr8JLt5sYfziyrj0SFmbtUsj/lk8durpSDUwVbDYhTJ1/haL7lHWOz8uYGjyR0N3mO3e2/UY3kgdIN7pYYSxVS3TqM7+51OfrJ1QgAtViTki0lB1yNikWu9jNgVidcWrZ7lpBF4GS+rGaLIljNMgVFSU1AxoN5aND88GvSjTjXzI187qLREFyHIxEWjOqsFbxZca/uPeYl9rBUma8pPkNDBAfPRcyD975RQdJCsMgzTDNM3zBoDafFl8YqgmGePwWeuf0fXwYvhY9fRzjW9QsykutX2eCqVJ9nqe9ir6mGcUKQ4lxYfO7KzUGN0l/b3YhazGSzYMMwBfObRqIN74dCRALIBpKIC4Q93+S5s7hLOOw==
*/