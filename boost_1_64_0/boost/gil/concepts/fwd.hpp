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
kT6IEhK6Ufewz9Np4rAKdpWtnh5pOUXkVHeM8WTDvOrgY/gq1eH5ZdZn0FEF2jJBUn/bFdKd6OD4HHVQX68SSITXLinCPNTkJbuyzCVYrXE8cJ1VfbDHKGjdtPMIJX1xyw8k1ryvK+/wtyRo3XX8O2E5NCSxA8HMnghohqU2IlPp5tgx9hfIbujm1abN1ZF4MLKXdhsqeOYVOZSW+g5NuGxUSRjWRTfXMJzrIrUHh1CUCzoa8UMyB1CqkN/EFz6BXIQQmffAjg09ikL+RMH93hKomlfPXwPslJykOKep3WpqJHeUI0NrLUsFonHGbSRjH2YQ96V5fLH0ru2n72JjpwnOcqYdyAzUPDPv295SnANnDTu8sKLYwQP/ECeXvA9gSy92qGJGEM+r2OqFM0Y8E1t0d4dK1PLrs3VUqquZ/hGDqmusgz+h4lj8SOGWsdIT2xSmjnoLDgJ99cIk/ds0YbYErT1LpjB5URnEyc69av9Y5eldhfRPYXACCXQW/reSbO6Lt7J94yy3O81sOobn1aHIpIOE7EfNvVEzesXx9rLjI9BQlypA4vXA5Q==
*/