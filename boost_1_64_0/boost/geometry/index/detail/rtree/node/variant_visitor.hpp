// Boost.Geometry Index
//
// R-tree nodes static visitor related code
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_VISITOR_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_VISITOR_HPP

#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>
#include <boost/variant/variant.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// nodes variants forward declarations

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct variant_internal_node;

template <typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
struct variant_leaf;

// nodes conversion

template <typename V, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline V & get(
    boost::variant<
        variant_leaf<Value, Parameters, Box, Allocators, Tag>,
        variant_internal_node<Value, Parameters, Box, Allocators, Tag>
    > & v)
{
    return boost::get<V>(v);
}

// apply visitor

template <typename Visitor, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline void apply_visitor(Visitor & v,
                          boost::variant<
                              variant_leaf<Value, Parameters, Box, Allocators, Tag>,
                              variant_internal_node<Value, Parameters, Box, Allocators, Tag>
                          > & n)
{
    boost::apply_visitor(v, n);
}

template <typename Visitor, typename Value, typename Parameters, typename Box, typename Allocators, typename Tag>
inline void apply_visitor(Visitor & v,
                          boost::variant<
                              variant_leaf<Value, Parameters, Box, Allocators, Tag>,
                              variant_internal_node<Value, Parameters, Box, Allocators, Tag>
                          > const& n)
{
    boost::apply_visitor(v, n);
}

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_INDEX_DETAIL_RTREE_NODE_VARIANT_VISITOR_HPP

/* variant_visitor.hpp
VQdfi/9ERweUv2KM6mD+tmrpYPF5QR10C9NBT3TQvRo6WK46aKY6WCr2eG9oG+iFDu6KrgcN865/33HawkKR2RlVD78J0cPCMcifF9TDpcfVQ2fVw5rzVQ/XhveFTCrGyqTCy3RiCo7WcfpAycMo8qB9oNgneX245aOHHRj7Gd9qjM8bVR8arndgsD96u2ghMi9F1Udr8Z8g+liKLladr/q49ttq6WPjBUF95FUdG9r56oRoJKo+nr/ZzsOlVjvVx1axv+v14VaGTkLbRhz6KIuuEw17X+ARf/Q28ojI7I6qk0fFv1R0shZ9bLggqJNl1dLJ9rGqk3lf/2KdjFadnKo6yRb7cJ/oBPMJehmEPu7FpKKPmZhPoutFw2fEtAhEbyuDRWZvVL2cGaIXOdtibFAvTaull33jgnqZU6mX4pPTyycrHL10Vr3sFfuWSr1gRvPMbjN6qY8+rsV8jhnti6YbjYNn9CsC0dvMqyLzSVTd7Bb/MtHNTvSyd5zqZt6m4+qmu+om/SJHNzE+37xaMbFoJ0W0o6PsWb7kmERo66diGT7R9FMm+bjI6q76KRV7O78Pt0r9XGo9j46ao5cbMN9gxqGf56vqyNwn5kk811RbZ6NN2tGvswkrKtvTfvRV56Lguuz+1WpPF1+s7Wnuusr2NFE11tmXXJ325FN99Q6+5xf7rY6+MEZfmC7eUdZydPU9Jh9d7cB08bvoTO/Lr5N7/wS9x2f8EvtzNfoGSrzRrsHvRGZmtXX4D+SD9zYN0N/Yi4PPbf5SrXa3/5KgDlvFpKO2GF9dFBjPr2a+hIQzYk71xYSqMfr4LvnI45kHdlPWeILkOXrEVOrxUusudOlDf0WY1zG90ONdVXVZbd3J2C8ywzxRx37xL6nybYPZ40P8T6cM2E2adQIJ1iBrFgcR/R1zEXsav4zpw1cZ73nZ8NCXbV2OeQ8zwJ9t3Y+x6yKXeth3SbAuJhy3LgZqXdTJMX3AwqbaB5i7i2m+2PAeQKZbcfZ0q/5x7jWuvVXuNcx8q0LseRb3GlH6Q7QqMu09D1jDqzxHqqJ7bes7V0lbN3PQt8TexhutLq6UNK4TXR1AT0k5eu0vHHJcXQXnpNm5RlcLNoXqyjRetBUTM0aab8Xq496bpkpeLjVzsySxv2oF7z+iPbvwi9wxd52YeA5GvXZriH9p1PZ4ivifrmugND7uDu32eL/lF92lo7ezclV3C/ZVq9/MzqvU3QhHdyGz2VxfslFZdJ3duzp8TvcHsfdx5jTo7X30Fu25+O9F9lJPFL1pXOOiXsd3rK68hx+TS/nzguUvr1b5x4w35b/+02D5zWxmTLXKP2h1+JwuS+x3hMxpL+X+LHrb6SnyO6O1HY3vmag66BOqA8qfPT6og1rV0sHF+ZU6mIZ8odFBX3SQ7atTDR28u8oZO3VOxzWvczrcitHBa5i+9PcbPNHbwl8lzF8j9VDtfuQ18S8SPYxFB2PzVQ/Xrz+uHjKC4x/yVyUhf8OahI50pjHxLnvr6TPyA9IHdlU7X5TKs7Oarnvt1YM/iTxrJsRunq3xVn2h9TzuD/OETd6haF4S0Ut8KoxdFB+yp0uYTCYyCbZMwqKxjgz2CJkxEwjnyFxXuX9OuMwMZOKctA4EZQIR8axBpqYj82KVfctUZtsE/OXdyKI/JsbGh+x/Eh7X/mB6gUUbo6WXWKAySYtujpQZjj0Z+zHd96wuchkY3jdhd7gKUwe3+mpwM+YJR8a8n1p6grXpG93WpqvfY5D3IPiFP1NthN9WNz99R5KG/3aX99e1cN8VsrdfCvbc8G9VxK3QuOk1wvtn5/k6/Ul9x/7Q78z76LB3UGdd5hSwffC9me4=
*/