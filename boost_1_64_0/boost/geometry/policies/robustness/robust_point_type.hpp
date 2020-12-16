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
DozF11OXSW23G/3KdOM4liTgILc3bF4dJ9blB48IXTY1kc3kGli4MmVeHq39xz1jdHd6u79fv2flzYlpzWViRY+LxevF5wyeCiE5C79u9Ot0uxXV9fbDq+uftzNiQd83ppz2e5nArSHvh42s3s53lP2xtrrf2ujjrYQ93mkhLq3aEg/AqMubxp0tNApjlE2O7NlSRkduA5h0xzsnRJj21prHz62Be/jIKmUF5tarlhUYf1mlDG4ij2I1hTlTqeOQVFkgskUoUkJRhORHPqvjEncEZtqLgXqrJqS2AUD3Ab/YNuJ4ts1IN2qdnG/gxoGassq4abz9OPIZJcOmIT1h94pLINr+u7tX5yvWmM8BF0aVQWxzsisgTx7rB9aUp7JfCj1P45fFf1ro647Ai0rzHuzzXBeQGapxqMPOG62FH8fsv4+Xn53v26J8UZPIULvcFTezH62uZGKeYe+H+OQCAw4RbXk+OlRut8Tvy0Kxtd6Mfhv+3HsAz3tp+fYxs860oyd3G7GFngWLFsJgLEh9B3didLlVWgOjzl0I2iQd2YPtwfONoYlmTq9hcozcv1GPKJN4mQ4xGJP3H7v//QdllkzeM7m/UU4lNJ+VtfJRBbHZsMzcjvm7f2A9GfsSxvrZy7bn9xr2/5dtr22Dr5FjEMJkSU5belsnVHWWZytRJOLFhQWcQaLfk8l9hwyC+pbic3te6w3jzmQFPhkFqAXU76elXt4QJWNuKDUcoRZORi4cJ8cV9qmy3+/fV0lOmEw+KHXkCFTzhk7zCivN8vygVEIO/2O3rrev2pF+MnxLYCalVaIQpGDaVbL1A/jegLlqqpjG+8oZeAb3sm3k2+kukc31I/2Y1OJi82Q037APJrqkFRDzSlhkTpqM7mjYz/YlBjSHvVYz1t8MCbqrFMnzbjYaOxPNx2RnZ6uIpWa8635O9pvMFSrjHNnLPml/b0BAzOo0R2RfEK/GAfV9/3lLVqKh58UxvrLgauUYQ0lETzV0nz993EjXnH7UMoLRawmlHKDahDXy0C9g21h+R/H8J/1yDL+SnN3zaWC4PR0U7gYq3G8+wTghr8XjB4223u81jquNcofeM/bhj7WhTrWtogDa1nncx5emeRyMrSTUbjOf9ODtOtD7ym9aHYuuEhoPl+c1vvKIvy/JLQEc2pZwGZvb6MIq+FY7wms7+kFTTzgO/3uxw8IQ1+PsztFeKIPjK2H5Invx/ui7GoAgT0b9D9KixjxZySOcc3bb0yJArHo2AWei2v4/AqCwna90Gk1x1qa/j26g74/l7+JHfZ+28cPr9PcIP65lZ5N1Ahr9sGt0Hs1DVj5STn5LPGeNybok5Pvrd/eVN6G+W+XV39+w2y4vf7fLq3XSt+725o02Z1qcLIGdRK4/BVVf8QaxGhzyUYlx8Hj77v+qPaTt4LnyLKKYO6xsIm8Cj0KxhvOLWiZQeuH78c0ecVIQIr3CV+vZQ5WAdEihE/KBvIDymxc3R7uMJoyBS/sWfp/ioesdjH5xWc8GoYcq7Gs2CuzRePDt73Wvo2P4Dxwf9oxyHrhX4M8DM8jJA7H57TxcsJvHbo7Zz3lQPfkdr8I25ssA5gZ5B3b8vg/uGTM/mGFkfH79luUO0Kx5rNaya/DdO4/Z3njK0D+ynZ5YSyKDRKVzDCvqyQy6smfktXGdGG/WOqfufKox31Vzge+gqu9q7pB/k/q+ZOO7W/R3nmsPGbHnJn/3z82Hjrhzk7/z3LTxXH4bz+W38Vx+C++Wn+Nq89zkOWktq4w988B+rOp55XHE+sVGKeNVlC50Ob3h9cVIPj/aXptJxm9nur0ui1iC+h1iC+Ndy4jfRsY66xevGUOMcdc=
*/