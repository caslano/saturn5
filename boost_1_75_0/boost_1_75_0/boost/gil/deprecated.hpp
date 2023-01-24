//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DEPRECATED_HPP
#define BOOST_GIL_DEPRECATED_HPP

#include <cstddef>

/// This file is provided as a courtesy to ease upgrading GIL client code.
/// Please make sure your code compiles when this file is not included.

#define planar_ptr          planar_pixel_iterator
#define planar_ref          planar_pixel_reference
#define membased_2d_locator memory_based_2d_locator
#define pixel_step_iterator memory_based_step_iterator
#define pixel_image_iterator iterator_from_2d

#define equal_channels      static_equal
#define copy_channels       static_copy
#define fill_channels       static_fill
#define generate_channels   static_generate
#define for_each_channel    static_for_each
#define transform_channels  static_transform
#define max_channel         static_max
#define min_channel         static_min

#define semantic_channel    semantic_at_c

template <typename Img>
void resize_clobber_image(Img& img, const typename Img::point_t& new_dims) {
    img.recreate(new_dims);
}

template <typename Img>
void resize_clobber_image(Img& img, const typename Img::x_coord_t& width, const typename Img::y_coord_t& height) {
    img.recreate(width,height);
}

template <typename T> typename T::x_coord_t get_width(const T& a) { return a.width(); }
template <typename T> typename T::y_coord_t get_height(const T& a) { return a.height(); }
template <typename T> typename T::point_t get_dimensions(const T& a) { return a.dimensions(); }
template <typename T> std::size_t get_num_channels(const T& a) { return a.num_channels(); }

#define GIL boost::gil
#define ADOBE_GIL_NAMESPACE_BEGIN  namespace boost { namespace gil {
#define ADOBE_GIL_NAMESPACE_END    } }

#define ByteAdvancableIteratorConcept  MemoryBasedIteratorConcept
#define byte_advance                   memunit_advance
#define byte_advanced                  memunit_advanced
#define byte_step                      memunit_step
#define byte_distance                  memunit_distance

#define byte_addressable_step_iterator memory_based_step_iterator
#define byte_addressable_2d_locator    memory_based_2d_locator

// These are members of memory-based locators
//#define row_bytes    row_size         // commented out because row_bytes is commonly used
#define pix_bytestep pixel_size

#endif

/* deprecated.hpp
flks/al3dy/NF7INzSysVf5VIS4qysD0HnD/rYkdYbFSAPL4d8hLo3ja7FY918TcClDcrt0zAYXAKNJQZxGKqDs8SbLWg8TulRAemV3+gs38FBw8evyIKCyG2nvUD1cKXiJoSMtgVrgxyBhX/1gpsDeeXlml4WnnVEWvefbHOLoty8mfMoPZhWyrWoW7cYr0e2/ElTX51tBfb+ed0s4YFdvFIw90SngavrcWB4j0OgBVgoRYK5SFr/q83ch7W1+PlTsV5jaUnMskPRLtgkh7R9bm2klL6kefwN8YGnaFxersDLHOOB8ej1/v3r+wvzjrDAL6YZjj5kP1/Xpf/Mi9/sjvGDzFeeW4pWEdkXDvtHgJglCtB35mGIiM443PtFkwrqXYjt2+ZBiIHolCZmyOBn6+M2ReS0EylG5rL/VUKYZJaHeysChwLc0LZ3rxJE6ZLzV5JnmL/GkadiAG8v28VsEVpt7OQ6YsJGmLMhwcV/swNajfHP+FCMucqVq6N6wrgUCGQE3TAaHaOt1BtNqcsihxdhQxbNmJ8IPGoJmBnehixfE8hf9I6AxCAVsIu0pmRVEd61J8waFgEgmqpHkamxipNMU0rpXSCnsKehCdCZa9XGtpinn1CA5NKfMyUvDIuI6A/rQWRz5PA8+51YLju6cVv0mHj7ekyc5mpCOfy8aH3p7abbfXUgsbJgIZTbB8LsyEVrBPuLaDhJ+M
*/