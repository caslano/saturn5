// Boost.Geometry Index
//
// Abs of difference
//
// Copyright (c) 2011-2013 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_DIFF_ABS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_DIFF_ABS_HPP

namespace boost { namespace geometry { namespace index { namespace detail {

template <typename T>
inline T diff_abs_dispatch(T const& v1, T const& v2, boost::mpl::bool_<true> const& /*is_integral*/)
{
    return v1 < v2 ? v2 - v1 : v1 - v2;
}

template <typename T>
inline T diff_abs_dispatch(T const& v1, T const& v2, boost::mpl::bool_<false> const& /*is_integral*/)
{
    return ::fabs(v1 - v2);
}

template <typename T>
inline T diff_abs(T const& v1, T const& v2)
{
    typedef boost::mpl::bool_<
        boost::is_integral<T>::value
    > is_integral;
    return diff_abs_dispatch(v1, v2, is_integral());
}

}}}} // namespace boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_DIFF_ABS_HPP

/* diff_abs.hpp
WeeRkL7PjW3+OMhqwxKud46D/mq0YSKH431Q/dpmbKPjoUbXNtde75x/L4csW0UW7ZugurQBT2Rz74bSJv8GxxoY5dFOkcfxDqhWFtA35Q3Q0FjGRa4nbtCPGw9r5cLFDX2bDfrmjxutPJuy2ikL1qPxQycLtj6wKt3A+AB8jco0PJI1k4MsVxbnXTLPgfwOuXgvxpk+TJss+fZ+E/QL6cbYS37L/S3L1IXnHPmqTAsx59D1aUzXEyPlFiLT4maMi+0y7buRzwqyTFMtnUdhMmHcr5OJ6XqhdY2XPfJbyS3BdS5wDfkP184FNsWpc4FnyB5jo50hY8U/kB9WTqkNhD48pO8SxOdxWjtPSvTFtYyOxdY1Og97elEb34S5xfDmzC3WrDGZH+b95Fthdhtzi1C6lpfUGjeiZmLqPVvRVeNSN5i3s5x3To837Ktht+4ogdsa3wj9OWzHXgPo6ewm95MGfZFtHF0uPEPZLjyU/r/jvDLOiORxP3AmuQVk/SfA9MYY4S3kRQzSoZLukpb7ojNC+XBTqpoPVemhNyiCIND8w3EU8ONWXcBrpLmX8mC11zmWX+u17ikhPXgsv85r6eu1xRnueUDEy8hDpf3o9Xvzo6dx25FvjY3jlfwLlFWVIvtcxsScFlYcFyPkS1Oat05o1detv3eseZFc+QkiFxTrlOLkvl4m0EWk60LT5kvaDPqDfuxSaJeBpw0uc2XQNn/s0sdaP7nJJPwYgiQD3wMa92OLQ3LgHWU3HZ1MhxLTjutTDdn3xvTi8zofwPw+xivjHY9tj/Iboh0ZMwWtZnJMnOdi5HGm6L9wvle8EN9/HPZCIN4qprupVxuxAMLgLVDTDIVbEPQvp9H9TdxpbfTdNTlbnZAUJWerHbo3+Q7eAl+UdfdeSUv/zWZgh7jPfBtmHmQItpK0xNrzHO1d+w1Es91jvCU9HOYWGE5j5u/iWIfmNor9O1FYE2C/k+w7Ud6xHw9zJ4zZj/DZNaBBmwVcR7S7UEexKg1zjzXvknDzXPUchO7Knph+g3LNmnVA+gWS11UPQnmymRev5qh7lutvduzxU/3amix50WC7A7rm7+uzTHvC7mjm32IyfsPlo57KB1BkonVKbfmI8xs0O6h8jIW5Q8oH87uXD/ir5SOawnqRyse5MJtdywf+Ee2rVD6mwzwYKh8I9/+/fLzql/KhtL+7OC/6cfnoad6Vh68tL+SGjXa+xrT9Ii4jdj2NZ6ZIG6KMeebeqperUCtXUcmMGTVlC/gSkPas0QnIuFRkVNe8jrOMPg4gkWVcrZeR65lWPubxRdyH6ea8+etMwt0wXRlfM+bfIg/fPrXdnrLmT8+lqHfkIRPzjZT6MyjVXJfP5LH5x+Q/BSU/GaulLeS8L9/Dc+grHi9h7kCoZewm4dBIj/Xx2N9w4L6f12cljIHEPwX2N8n+e9y3iGGdhyE++5i0Qnj7E28l7PvIvtbza3w59E3zOCTYlHPN4HXcvce3hN7+dne118PxWom+p69ytw/hKPfxW8paU4W8+73XoEHvtwo5HPK/RNbVPiX/q/DiRV92s9LxInCMseKCf6F5cibfCXmV6G6DZAme38HIuSSshZXUzZe3y1OA/SjPB2NWltDoWNPQMQd6GjfMwg5rqU1PAMqXsh5eLmvkXEbYPSB6AUL5ngP3RfJGhuSr8ASFh/ONeVYKj5I/6vrHOseaA9XhdalSZ3g6hbqMM3mua1apka01aOqvtMXrb3e+ob3PWLOyy1KXb24kuujQfgG0tnezmTfTOkeG38QtdRr+yrvZL8Fufzf75PRIdCjq72fEk52+p7btdzj3yl435rNqPJ333lzSHnxh77SVLVI=
*/