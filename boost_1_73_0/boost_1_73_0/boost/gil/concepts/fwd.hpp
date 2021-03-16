//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_FWD_HPP
#define BOOST_GIL_CONCEPTS_FWD_HPP

namespace boost { namespace gil {

// Forward declarations used by concepts

template <typename ColorBase, int K> struct kth_element_type;
template <typename ColorBase, int K> struct kth_element_reference_type;
template <typename ColorBase, int K> struct kth_element_const_reference_type;
template <typename ColorBase, int K> struct kth_semantic_element_reference_type;
template <typename ColorBase, int K> struct kth_semantic_element_const_reference_type;
template <typename ColorBase> struct size;
template <typename ColorBase> struct element_type;

template <typename T> struct is_pixel;
template <typename T> struct is_planar;
template <typename T> struct channel_type;
template <typename T> struct color_space_type;
template <typename T> struct channel_mapping_type;
template <typename T> struct num_channels;

template <typename T> struct dynamic_x_step_type;
template <typename T> struct dynamic_y_step_type;
template <typename T> struct transposed_type;

}} // namespace boost::gil

#endif

/* fwd.hpp
6Em3Qk8av3ITX3ig479LYBqHFvGj6P9HuWm8QgfFCtT4jwf/5RLUeLUu92CyEnQGgbe2Q5PaVJMay2wxxXPoVLdOp9pahzmUyOsPJxN53eOdRF7fGDOQ02EeTv3WutDLqN9a//msJK97jK/zyekYp1O/tc72G9RvrbN9g/qtdbajnImsXnQB9VvrZu+gfmvd7AZnef3kQBd5/eR51D8v3GNY5Imau9cPcjt/ozILHs6bqd9an7me+q31vdu7ot8=
*/