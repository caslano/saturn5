// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTION_BOX_POLICIES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTION_BOX_POLICIES_HPP


#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/expand.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace section
{

template <typename ExpandBoxStrategy>
struct get_section_box
{
    template <typename Box, typename Section>
    static inline void apply(Box& total, Section const& section)
    {
        geometry::expand(total, section.bounding_box,
                         ExpandBoxStrategy());
    }
};

template <typename DisjointBoxBoxStrategy>
struct overlaps_section_box
{
    template <typename Box, typename Section>
    static inline bool apply(Box const& box, Section const& section)
    {
        return ! detail::disjoint::disjoint_box_box(box, section.bounding_box,
                                                    DisjointBoxBoxStrategy());
    }
};


}} // namespace detail::section
#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTION_BOX_POLICIES_HPP

/* section_box_policies.hpp
1Xj6GnnYAS603C0WPs9CgQv1uwVLwrU/xJDfh/24fTYK/YFjL2kZsB3lWXC623yKlQnEJDNSVgUnLVTLqQ1Kk124KdQWG7Ev/i2AEw1egId4/3/LzV6sP2rpmb5BjGLh3rJu/cwiTLk3b5ZLxM90TLrzxRLxBpaIXGsrpmrScJyccZa1jhiaVLqf1ybE9dDgA6yj1vK5rYHprT740mxN+Sz5GN/RtvdztlH38/F36+35+P69B87Ht8zz0mA1FlMy/CwnpNfcZ1Zk60+VrDHEEc5rzuky8p8z5h4ihFyM2c3SMioHl5ifzrwtU/O2zJM6Za/+iz1ljboFXLsr0mCBxFoFz/i2lPQyIZxW5hLzqELNozI1jyrEPDL9aVE/3O5Oyg4UX+MPXTTx48ZnuTnywPGJqWWPzx0Yn6M4PuVYH0NbGmZZWvGotOCvys197UU+tAS+JRx8FtDHlAow/J4tLWBgxnrRcrS16yHloPd6NW1bUqft4xs+bdo+AYfoL/55byL8keems6Cqk+2NpeX5ILoeI5qNKvrQ1FXruLc1faiHt2b69XF+b6KREgm/bYr0FJ3mK2m6YUv7dYGqsuxyc50XqZiYKYGGzS4avy3D5XEDtrku0YYIvTlBI4wl6248KlC1cuJCKGj7Y+ckEisrYvBE2+JzJRJ6RXbTHr3kuRteZ5l8ejOOmwkCJoafCnuCgO0r/kHaTVhURspF5U+mWFTmz3eDy3yVxg4vM/8SMMf4fRCtCr+aWV7V6EcJhhtLcj2AcgqhDF3nNRat9Jprhq4LHeZFrBfa49U5SOqtGaYl4AMD7zPeAy6IjMplRmcjIzpHa8T2Gohe4xcrzTGCfrNRLoYHb5ArngedFT8fMRy3nRfFvz+JJBybbwv1q4sl6O3zRB1crMOl31cLY3zAvzvt58v4HWC/0VlXuHaNfdZeV+6526GU+hXCRT0ongZBphZUs2okZkcMYaIh1pmteBXzHZG0+eL3PJ7tbPylxtJzPfr6wnNzISMnMaWVkW8PHCXMI09ssriojLTpcX2eU6DuFUywSZ7lciUeU+0N35jrKsOMLjfHlhq+l/w4jGIEWxsiQPgxFAPSOqH+VHRBBHegBmN5silDJMdpRY43Sioken/BQh3xkZoCIgve6MIizt/oYh67yhx7Cnk5zP8BxOG2Yoi4Lc3HzYB9DMTLZvnDFHEOJ11BOjorQ+POxUd8zMfjEPlYgMd8+ViER37FAg6xvrNyb0LUrKGPkiUpqs8VPtvWkT2xH4PYWPpCRfRXRcmiV0QfJ1hzU0X0zwJo9HcEaB0KWOUK5dolaU5Y+KKPsHSxCyA4W5FnNV2hYa2feYXoPatulZoj5ba9QRKn/VzjNqOLKZpXCdG8Id2K5jny4KdJXZJFc8F/mGPbCb8bGZEi8Pun/1N+pecrobezn7Knwi0/tqeCtAa7R/Fk6G2JI1+O5LM4koeokXymPZIDaEDbb8OMOW6npdhEjrnW4Pd43mvVud/FBStTZy84g54uIZChFA0R5qM57AOU5ODkqM9WjpvGC6dOXabIJk6PR+u+lOnRWoPpgd/XMEXOXJE6RTg7KMSECWJtbRKzIxB9wJkdbI4VcnZAv1FyFEQJrN1PoD+kXVM5N1pnsUz8kTKL1gbFAaJuys9UwGSrmqKh0exK/kX1BmX2OEkexUihNNTln4uw8C/6lQJ1VO7dq9vEiIafmVa3ZMu8y92glGZekvZT1Raq9k8DjWvjcbekRo/HaewWcRorPt8zbaqdPg1LVfj6XLiKJMnb+ttERbyp+q5DvJkadog3b05wiDeXhB3izdoJKcQbX1jSRBomSKm1m5BBfByNH4Sv90PmWZ0=
*/