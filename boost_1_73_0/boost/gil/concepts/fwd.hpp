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
0bL9P/hs9d6t1+98d/9rv33ng2s/PxbPrlLZ+t3UX1epZJs2GgEFxh9UALD332Hk3wfqv3+8O7nviXvr/731/976f2/9v7f+31v/763/9ztxb/2/t/7fW//vrf/31v976/+99f/e+v//X////fvfOHmJPZox/MxcV0Nm2keREX1F3fhkr1z8zDVrl9S8SwDslTvbjl2Lx2ptZM7caVn455WxK+PXJNcSV8ZqO90acpD3nCsf
*/