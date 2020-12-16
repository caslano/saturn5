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
c1zZF51zcZVtiETK+OtVNic2PQ2+7rbAffWK8GOEd69XNJ++GrzOemXuIY/PPsDRgH2zGbvJwqjfJuyC6y+PgYnWSJizyeWwb7+p95ecMwCUgsMaf4A8W8AaGvx3Jo5oTkGO4qzDd36u8UzkGz8EJ2JwrLeK/ubx/UdbR19mOI/3cOgCcs6vB1m+9HZ+DdgYpcR+A+3RDofynPGMg5MGHMfNlFbCIR+GcGxWMKdkyUDHiKcnGlSBdTz7fBz4OLIv65d6gMtLOZBb/EROCyt68CtBAM1vduHHZ7Y4AOt4LFxp+WHF3tJPa0rfr74jlq/tjDy5BbjFfo7Mo8MR8R0M43SrpPXubnOYfIoBNqdGxxqxhT7OZ8VCwuXRNDBiP2mS8XTSHabEIfKt0n3uMacPL1eKuOuikl52Hz4zFvXh/STvtJRXS2RrhVQpFWQSyIg9u/hZ19jT6NEU5pwMkyokwnymVqoWK4moyxxHd78rPra2Z1d8bi0O3q/jvGTHmcuW8pUyxg9foA3ifOnmeOwPB3Ombzq+kr7bZ9u4j3vTGsL9Z/h4jNi/Frylz9OxrbL6avzuP8vHdtFl4oizfLJycbxvux14S5/5A05pXYff/ecMud19wjn75r5V8Z0LDt6amDzUFn3pjx2c1lb5/v5IPt1sp86rPL2nyec6fuxicbuS4c/+jDhoH8plvSHeMrz8gwijazDNmaDNP6TvcVfV0rq2o74Ku1+xTT+rXuyXvvfPjHC43sVHiWb5zRT+Tu/VattO6PkicOh8iz6/0tDYrT+TGApBYCt1uBZhom/4uTMOUd/f1PhuB6eyY3wOuByHaJwy540cnA41cZ/4cu7bszPOGTiW8RqH456Be5OL0+konf71jKtRMgIpLDiE6TcYKCiH7bPHHlVoFBb62WfHYGFCvNB7i+dsGUqY8Qf9vBPPFETcF9xxz/jP77Zlw0iiKy8abdRgM0YNOPo30N+itao+dxa9YnM22gkw/Ee7Ovn5nIZ+7/hv3ph6hyWPKjVZllrGe70cMyaG3rEdSYnWu8ybZB/6uXX2ivxYqN1FMtR3+22ZzRflmS5TLw9CFvHNA1H0EjG/d/WFjvEfr95gVHtaPw3D5jzi8U8r7rjqKMlIgHmg1uMPquIy/cDJP6ixeBZC4tFgGjx6Y8e8G/NHH4feiBWyzn5OniVCsZi39SbZJvmy5DTRARJJvln31JWCQ2PVQfWkCNZdRHyJLcTj9395pZXL+hb7fBMaTLTUx/ne8+vVlgyMoKNz03G+a07vd8n2Ue91TdHiGL03zeesfuS+0RPHw33+dwjXZqDo046fZ2yi3p5FQPsdtuY32fZqzndmyCzPkV+pefYrvNGgLHi9X9M8evz7qeZQl+Q1f7Ra87CWhahlBstyeKOWB2wWb0SSioBmeLz5CcmKVxfky/rmnaOfEofWLug4V129pnd4bhQ2Deo3j1/EpShp6qvD9DDvq6t1O4hf5kSco4f5KgTmbdvXQzxa4AN7pk3vkgLndxKvWUM81ICnU13g5wJhgGOthuuxv07oJc95tnX/reooNa1DU2qjsNlPWN+mNXbbo4TGc4T2nLJN20gwnQOit0j9YWieIANxuvrWdwmDUlLn8p8i5gK9d+zGxdOpMbmldTl2bRfuGNZx8YzjGBeJ0f9Yb5cwOOOn2fHIaMKc3dAlDK1Emlgwlul47rBEOjoDruBzXH9fTeesiOOa1c3GmDyD2Psvl8/vYzf5rNdviWMyxie1ofkj34zq9RUDcP2+1CGftQA8wW9l/p54hJopWs84jy0PXuPIop5B5eJ8i+M8dnSNk265vWDqXvMA8SjjfWQeA1MdcVOpEVHU6cU=
*/