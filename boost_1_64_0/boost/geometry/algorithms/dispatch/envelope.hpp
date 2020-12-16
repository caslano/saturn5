// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_ENVELOPE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_ENVELOPE_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct envelope : not_implemented<Tag>
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_ENVELOPE_HPP

/* envelope.hpp
9gm+1hH0IrN1NfF1vL8vxnv5FZTJq7/qgiKJTA74wRi3bbPhw05EFZRNAXNnpNJRokWeIkyMg68TAuRA8Y8OeJPRfkKBu8Wmm8iZODLSj3+yS/r8VHqSbMcn0hJf+3mnY8kJqbNVatJrR6GC5ML7hd09kuILKqRtqQoJg1nO4kaq3oZTtWTAoF0t6gqhA0diRoERkkG8bB0STEzouSRQXnk06in3RsbQAYncPFQ8M6s9Hv4OlMpB/jm4JbpFUwLfiVeaTyQlPOsVSphyjZDCy+YFyc5/hhTelz+1fv8mSxEPz2c343DaNT6RFn9pN/E3pMV/774T46vT4ku6yX9OWvyhe0+M75UWv7Wb+D2eVHxDN/FPpsUf6ab+36TFz+omfyItfko38TekxZ/fTXx1WnwB4rvIN3KHXJhpBEFxXAaofNRqjE8O1pQ7aeCFBk9fFS+FR6qMo/P7cgtjucAT6bmLzYBTuaAwDsFDnHnfD0XoqoSMNmMbuZl3IgR+6BdFBx6oLPBG8xGWXGPORWjFjnnPdWRbBo/nB4P01B2fHwxVHJ8dCJT/3Osmi2y1ur4PQ1mW58lNpuFSN0Vi8ZneoQc4Uz7Kguudyp7Bsz8QefSCnuKbNVhdsW72XqOqEraYOY8Wwx1YCxkQz/nXOZIsO4hE8AtMV7NBpNNugYOW+9kg3O5Uwgu9mGacDLml6koaqyOqzCNO7eRC67y3fxH7KAFoGgpyHyJMNav2E0yB6PN5YvTQ9n/8FLFpPFHmjfStOWyt9o3JpkBZYfQ1nIlWvDkMKPHFzlF+x7Am9AgWbxY9iMEICtSfCfvYbH+gfqoTsVlsLwEgu5lA1DsTF2cxQX2Q8e7u4t06nj+YagAZyytEwUycbEqllYRTnBJu3E0oLGSZ3sd0T7o7CTSALHFrIH/57kCiacngmOMOMkPJJBWgy45bQGdZQJ9x3AJad1pPxDq7A8rZDVD1BbrlbBoBY8M/+WhGw8W714cAGZItxA/n5FFB4965fAa/lnZHR4sdZQ8XlmPKTdqZfPkKXgB3pdrA1z0OpZLgkJoX2fUHdwZPfRZTuVsAu+bYCYCFjwlgYRuwvPcAmIZoPsTySKlWW9zbSKt2W9AHFK0N8dfliJyPX4RGwGFZtUSESVfVKw2ZaGkwMWb1GicMk3tFz8X/Jw9/ByD4IQl28bWX+kXgvQw80OyM9JUjBe/9L6X042eOAt4tr4dqkscXAH0yWj5PjF3ICOjdxqr5YKybmOg5nws2+SW0MgYlNWBlhEZJro2OOH4TV3iqocVTJvrofjhiwXZEKfEk54o0I0SLcurdtB8Fn1lcRjnJhGKvO6NbpKDinbAr5QGaBb1ErctG7Rq7qq60b81Wmly07cFKKuRe4VTTFR2Yy2XFJn/iklzz6FudIgfzUdEWvu7C6FCQE481PHz3hXkQCgri8sv4fhF3E3PD5T9nbGQO+u8erYj0xXD5VG9kuu+RAvqVIGVthG9Hemb/xD1iYVWbO2NR2tUr5UYtt3SvHSFl3s3SZOhc6jWnLE+ljN9TpJoTHdThDhnPpVWcLRXfTHKSjrr/iEW6HpqAJul++0h6J51+UsgD5gj9KMsALvNshoo8W2w+1pAxItFHfElz6+efEWuD4LSaWN1unNcKieDvMG4xw2CzhbPtYgcejx3HjfgCzvMQQtFuO7CMyEB8+jCheRryYNnB4u1YFHy1axCEVQO8sBaMR0Kyzu/spef+YOIzLsz92TL3/2l/ZxI5AWW7tz4PD/Ucmy3yerELPuzYbL0GxFbR/hesLv7AKd01RTxBHuWyef3dsmwG0+6n7CRgxExCNBe/FpM7FmoTDUcLdXxyTfAezgE=
*/