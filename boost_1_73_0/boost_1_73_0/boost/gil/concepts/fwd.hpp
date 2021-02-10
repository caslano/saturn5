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
iZhFCzCZB28gdxgAewYwM1JN+UwJIWOWT1LlkmCjhqi0bBkLDtOUsShOoStlI4TL9ATsBhkpVp5PzmjHVHeJmT1wpDwyyjS3mogoD+QkDaU5gJw2kS2ci5WvKJY5LRL8aGk2eiUYTWLgoB1CLzyASeSUC+Bzb3Q+uBrB5/Zw2O6PxjA4g3Z/zGCfev1TKr0iMgs4zyw6IregZlmqUC45v9/Rqh0qHae5RDjg4gmHPs+ayUGNpgILoo3pjV9klOYp6UjVxEZ2cXynKGKa65hbhLrHmluySJgsgFsgptBWrcYzJjbk2WFopZUX0hxRdnLa6oUNI7eAhox8FMDSHhutaRSwDRp8UX+7A2Qy1HtQGryAinPBSl1my/EnH6GnuNqtUbK0Ty0iZeJx34cceSy8EUzPtiO+eVXczeOKb5wah/vUM3JWfwutBu2NzDhF/U5tF69XXOec7oCVudoDF8DEmBQadKHj1UXGxYzNOq4ijlr3cciiSrVHZ+G+8i2JJUZyxUn9UqEtmq5w+HbanZVJo5HwH5ZSWPwnR+eF85Hfl/y9VaWR6FCk5kZpIdHTuHNHpNHRGpPIQqO4w8OLTU79i8JDivoLWtdHCdDgtsy8DVbXWeTcnWTL12PQHOUtSEHcwksxWwtMaBimNEwa
*/