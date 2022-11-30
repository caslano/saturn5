//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IMAGE_VIEW_FACTORY_HPP
#define BOOST_GIL_IMAGE_VIEW_FACTORY_HPP

#include <boost/gil/color_convert.hpp>
#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/gray.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/metafunctions.hpp>
#include <boost/gil/point.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/assert.hpp>

#include <cstddef>
#include <type_traits>

/// Methods for creating shallow image views from raw pixel data or from other image views -
/// flipping horizontally or vertically, axis-aligned rotation, a subimage, subsampled
/// or n-th channel image view. Derived image views are shallow copies and are fast to construct.

/// \defgroup ImageViewConstructors Image View From Raw Data
/// \ingroup ImageViewAlgorithm
/// \brief Methods for constructing image views from raw data and for getting raw data from views

/// \defgroup ImageViewTransformations Image View Transformations
/// \ingroup ImageViewAlgorithm
/// \brief Methods for constructing one image view from another

namespace boost { namespace gil {

struct default_color_converter;

template <typename T> struct transposed_type;

/// \brief Returns the type of a view that has a dynamic step along both X and Y
/// \ingroup ImageViewTransformations
template <typename View>
struct dynamic_xy_step_type
    : dynamic_y_step_type<typename dynamic_x_step_type<View>::type> {};

/// \brief Returns the type of a transposed view that has a dynamic step along both X and Y
/// \ingroup ImageViewTransformations
template <typename View>
struct dynamic_xy_step_transposed_type
    : dynamic_xy_step_type<typename transposed_type<View>::type> {};

/// \ingroup ImageViewConstructors
/// \brief Constructing image views from raw interleaved pixel data
template <typename Iterator>
typename type_from_x_iterator<Iterator>::view_t
interleaved_view(std::size_t width, std::size_t height,
                 Iterator pixels, std::ptrdiff_t rowsize_in_bytes) {
    using RView = typename type_from_x_iterator<Iterator>::view_t;
    return RView(width, height, typename RView::locator(pixels, rowsize_in_bytes));
}

/// \ingroup ImageViewConstructors
/// \brief Constructing image views from raw interleaved pixel data
template <typename Iterator>
auto interleaved_view(point<std::ptrdiff_t> dim, Iterator pixels,
                      std::ptrdiff_t rowsize_in_bytes)
    -> typename type_from_x_iterator<Iterator>::view_t
{
    using RView = typename type_from_x_iterator<Iterator>::view_t;
    return RView(dim, typename RView::locator(pixels, rowsize_in_bytes));
}

/////////////////////////////
//  interleaved_view_get_raw_data, planar_view_get_raw_data - return pointers to the raw data (the channels) of a basic homogeneous view.
/////////////////////////////

namespace detail {
    template <typename View, bool IsMutable> struct channel_pointer_type_impl;

    template <typename View> struct channel_pointer_type_impl<View, true> {
        using type = typename channel_type<View>::type *;
    };
    template <typename View> struct channel_pointer_type_impl<View, false> {
        using type = const typename channel_type<View>::type *;
    };

    template <typename View> struct channel_pointer_type
        : public channel_pointer_type_impl<View, view_is_mutable<View>::value> {};
} // namespace detail

/// \ingroup ImageViewConstructors
/// \brief Returns C pointer to the the channels of an interleaved homogeneous view.
template <typename HomogeneousView>
typename detail::channel_pointer_type<HomogeneousView>::type interleaved_view_get_raw_data(const HomogeneousView& view) {
    static_assert(!is_planar<HomogeneousView>::value && view_is_basic<HomogeneousView>::value, "");
    static_assert(std::is_pointer<typename HomogeneousView::x_iterator>::value, "");

    return &gil::at_c<0>(view(0,0));
}

/// \ingroup ImageViewConstructors
/// \brief Returns C pointer to the the channels of a given color plane of a planar homogeneous view.
template <typename HomogeneousView>
typename detail::channel_pointer_type<HomogeneousView>::type planar_view_get_raw_data(const HomogeneousView& view, int plane_index) {
    static_assert(is_planar<HomogeneousView>::value && view_is_basic<HomogeneousView>::value, "");
    return dynamic_at_c(view.row_begin(0),plane_index);
}


/// \defgroup ImageViewTransformationsColorConvert color_converted_view
/// \ingroup ImageViewTransformations
/// \brief Color converted view of another view

/// \ingroup ImageViewTransformationsColorConvert PixelDereferenceAdaptorModel
/// \brief Function object that given a source pixel, returns it converted to a given color space and channel depth. Models: PixelDereferenceAdaptorConcept
///
/// Useful in constructing a color converted view over a given image view
template <typename SrcConstRefP, typename DstP, typename CC=default_color_converter >        // const_reference to the source pixel and destination pixel value
class color_convert_deref_fn : public deref_base<color_convert_deref_fn<SrcConstRefP,DstP,CC>, DstP, DstP, const DstP&, SrcConstRefP, DstP, false> {
private:
    CC _cc;                     // color-converter
public:
    color_convert_deref_fn() {}
    color_convert_deref_fn(CC cc_in) : _cc(cc_in) {}

    DstP operator()(SrcConstRefP srcP) const {
        DstP dstP;
        _cc(srcP,dstP);
        return dstP;
    }
};

namespace detail {
    // Add color converter upon dereferencing
    template <typename SrcView, typename CC, typename DstP, typename SrcP>
    struct _color_converted_view_type {
    private:
        using deref_t = color_convert_deref_fn<typename SrcView::const_t::reference,DstP,CC>;
        using add_ref_t = typename SrcView::template add_deref<deref_t>;
    public:
        using type = typename add_ref_t::type;
        static type make(const SrcView& sv,CC cc) {return add_ref_t::make(sv,deref_t(cc));}
    };

    // If the Src view has the same pixel type as the target, there is no need for color conversion
    template <typename SrcView, typename CC, typename DstP>
    struct _color_converted_view_type<SrcView,CC,DstP,DstP> {
        using type = SrcView;
        static type make(const SrcView& sv,CC) {return sv;}
    };
} // namespace detail


/// \brief Returns the type of a view that does color conversion upon dereferencing its pixels
/// \ingroup ImageViewTransformationsColorConvert
template <typename SrcView, typename DstP, typename CC=default_color_converter>
struct color_converted_view_type : public detail::_color_converted_view_type<SrcView,
                                                                             CC,
                                                                             DstP,
                                                                             typename SrcView::value_type> {
    BOOST_GIL_CLASS_REQUIRE(DstP, boost::gil, MutablePixelConcept)//why does it have to be mutable???
};


/// \ingroup ImageViewTransformationsColorConvert
/// \brief view of a different color space with a user defined color-converter
template <typename DstP, typename View, typename CC>
inline typename color_converted_view_type<View,DstP,CC>::type color_converted_view(const View& src,CC cc) {
    return color_converted_view_type<View,DstP,CC>::make(src,cc);
}

/// \ingroup ImageViewTransformationsColorConvert
/// \brief overload of generic color_converted_view with the default color-converter
template <typename DstP, typename View>
inline typename color_converted_view_type<View,DstP>::type
color_converted_view(const View& src) {
    return color_converted_view<DstP>(src,default_color_converter());
}

/// \defgroup ImageViewTransformationsFlipUD flipped_up_down_view
/// \ingroup ImageViewTransformations
/// \brief view of a view flipped up-to-down

/// \ingroup ImageViewTransformationsFlipUD
template <typename View>
inline typename dynamic_y_step_type<View>::type flipped_up_down_view(const View& src) {
    using RView = typename dynamic_y_step_type<View>::type;
    return RView(src.dimensions(),typename RView::xy_locator(src.xy_at(0,src.height()-1),-1));
}

/// \defgroup ImageViewTransformationsFlipLR flipped_left_right_view
/// \ingroup ImageViewTransformations
/// \brief view of a view flipped left-to-right

/// \ingroup ImageViewTransformationsFlipLR
template <typename View>
inline typename dynamic_x_step_type<View>::type flipped_left_right_view(const View& src) {
    using RView = typename dynamic_x_step_type<View>::type;
    return RView(src.dimensions(),typename RView::xy_locator(src.xy_at(src.width()-1,0),-1,1));
}

/// \defgroup ImageViewTransformationsTransposed transposed_view
/// \ingroup ImageViewTransformations
/// \brief view of a view transposed

/// \ingroup ImageViewTransformationsTransposed
template <typename View>
inline typename dynamic_xy_step_transposed_type<View>::type transposed_view(const View& src) {
    using RView = typename dynamic_xy_step_transposed_type<View>::type;
    return RView(src.height(),src.width(),typename RView::xy_locator(src.xy_at(0,0),1,1,true));
}

/// \defgroup ImageViewTransformations90CW rotated90cw_view
/// \ingroup ImageViewTransformations
/// \brief view of a view rotated 90 degrees clockwise

/// \ingroup ImageViewTransformations90CW
template <typename View>
inline typename dynamic_xy_step_transposed_type<View>::type rotated90cw_view(const View& src) {
    using RView = typename dynamic_xy_step_transposed_type<View>::type;
    return RView(src.height(),src.width(),typename RView::xy_locator(src.xy_at(0,src.height()-1),-1,1,true));
}

/// \defgroup ImageViewTransformations90CCW rotated90ccw_view
/// \ingroup ImageViewTransformations
/// \brief view of a view rotated 90 degrees counter-clockwise

/// \ingroup ImageViewTransformations90CCW
template <typename View>
inline typename dynamic_xy_step_transposed_type<View>::type rotated90ccw_view(const View& src) {
    using RView = typename dynamic_xy_step_transposed_type<View>::type;
    return RView(src.height(),src.width(),typename RView::xy_locator(src.xy_at(src.width()-1,0),1,-1,true));
}

/// \defgroup ImageViewTransformations180 rotated180_view
/// \ingroup ImageViewTransformations
/// \brief view of a view rotated 180 degrees

/// \ingroup ImageViewTransformations180
template <typename View>
inline typename dynamic_xy_step_type<View>::type rotated180_view(const View& src) {
    using RView = typename dynamic_xy_step_type<View>::type;
    return RView(src.dimensions(),typename RView::xy_locator(src.xy_at(src.width()-1,src.height()-1),-1,-1));
}

/// \defgroup ImageViewTransformationsSubimage subimage_view
/// \ingroup ImageViewTransformations
/// \brief view of an axis-aligned rectangular area within an image_view

/// \ingroup ImageViewTransformationsSubimage
template <typename View>
inline View subimage_view(
    View const& src,
    typename View::point_t const& topleft,
    typename View::point_t const& dimensions)
{
    return View(dimensions, src.xy_at(topleft));
}

/// \ingroup ImageViewTransformationsSubimage
template <typename View>
inline View subimage_view(View const& src,
    typename View::coord_t x_min,
    typename View::coord_t y_min,
    typename View::coord_t width,
    typename View::coord_t height)
{
    return View(width, height, src.xy_at(x_min, y_min));
}

/// \defgroup ImageViewTransformationsSubsampled subsampled_view
/// \ingroup ImageViewTransformations
/// \brief view of a subsampled version of an image_view, stepping over a number of channels in X and number of rows in Y

/// \ingroup ImageViewTransformationsSubsampled
template <typename View>
inline
auto subsampled_view(View const& src, typename View::coord_t x_step, typename View::coord_t y_step)
    -> typename dynamic_xy_step_type<View>::type
{
    BOOST_ASSERT(x_step > 0 && y_step > 0);
    using view_t =typename dynamic_xy_step_type<View>::type;
    return view_t(
        (src.width()  + (x_step - 1)) / x_step,
        (src.height() + (y_step - 1)) / y_step,
        typename view_t::xy_locator(src.xy_at(0,0), x_step, y_step));
}

/// \ingroup ImageViewTransformationsSubsampled
template <typename View>
inline auto subsampled_view(View const& src, typename View::point_t const& step)
    -> typename dynamic_xy_step_type<View>::type
{
    return subsampled_view(src, step.x, step.y);
}

/// \defgroup ImageViewTransformationsNthChannel nth_channel_view
/// \ingroup ImageViewTransformations
/// \brief single-channel (grayscale) view of the N-th channel of a given image_view

namespace detail {
    template <typename View, bool AreChannelsTogether> struct __nth_channel_view_basic;

    // nth_channel_view when the channels are not adjacent in memory. This can happen for multi-channel interleaved images
    // or images with a step
    template <typename View>
    struct __nth_channel_view_basic<View,false> {
        using type = typename view_type<typename channel_type<View>::type, gray_layout_t, false, true, view_is_mutable<View>::value>::type;

        static type make(const View& src, int n) {
            using locator_t = typename type::xy_locator;
            using x_iterator_t = typename type::x_iterator;
            using x_iterator_base_t = typename iterator_adaptor_get_base<x_iterator_t>::type;
            x_iterator_t sit(x_iterator_base_t(&(src(0,0)[n])),src.pixels().pixel_size());
            return type(src.dimensions(),locator_t(sit, src.pixels().row_size()));
        }
    };

    // nth_channel_view when the channels are together in memory (true for simple grayscale or planar images)
    template <typename View>
    struct __nth_channel_view_basic<View,true> {
        using type = typename view_type<typename channel_type<View>::type, gray_layout_t, false, false, view_is_mutable<View>::value>::type;
        static type make(const View& src, int n) {
            using x_iterator_t = typename type::x_iterator;
            return interleaved_view(src.width(),src.height(),(x_iterator_t)&(src(0,0)[n]), src.pixels().row_size());
        }
    };

    template <typename View, bool IsBasic> struct __nth_channel_view;

    // For basic (memory-based) views dispatch to __nth_channel_view_basic
    template <typename View>
    struct __nth_channel_view<View,true>
    {
    private:
        using src_x_iterator = typename View::x_iterator;

        // Determines whether the channels of a given pixel iterator are adjacent in memory.
        // Planar and grayscale iterators have channels adjacent in memory, whereas multi-channel interleaved and iterators with non-fundamental step do not.
        static constexpr bool adjacent =
            !iterator_is_step<src_x_iterator>::value &&
            (is_planar<src_x_iterator>::value || num_channels<View>::value == 1);

    public:
        using type = typename __nth_channel_view_basic<View,adjacent>::type;

        static type make(const View& src, int n) {
            return __nth_channel_view_basic<View,adjacent>::make(src,n);
        }
    };

    /// \brief Function object that returns a grayscale reference of the N-th channel of a given reference. Models: PixelDereferenceAdaptorConcept.
    /// \ingroup PixelDereferenceAdaptorModel
    ///
    /// If the input is a pixel value or constant reference, the function object is immutable. Otherwise it is mutable (and returns non-const reference to the n-th channel)
    template <typename SrcP>        // SrcP is a reference to PixelConcept (could be pixel value or const/non-const reference)
                                    // Examples: pixel<T,L>, pixel<T,L>&, const pixel<T,L>&, planar_pixel_reference<T&,L>, planar_pixel_reference<const T&,L>
    struct nth_channel_deref_fn
    {
        static constexpr bool is_mutable =
            pixel_is_reference<SrcP>::value && pixel_reference_is_mutable<SrcP>::value;
    private:
        using src_pixel_t = typename std::remove_reference<SrcP>::type;
        using channel_t = typename channel_type<src_pixel_t>::type;
        using const_ref_t = typename src_pixel_t::const_reference;
        using ref_t = typename pixel_reference_type<channel_t,gray_layout_t,false,is_mutable>::type;
    public:
        using const_t = nth_channel_deref_fn<const_ref_t>;
        using value_type = typename pixel_value_type<channel_t,gray_layout_t>::type;
        using const_reference = typename pixel_reference_type<channel_t,gray_layout_t,false,false>::type;
        using argument_type = SrcP;
        using reference = mp11::mp_if_c<is_mutable, ref_t, value_type>;
        using result_type = reference;

        nth_channel_deref_fn(int n=0) : _n(n) {}
        template <typename P> nth_channel_deref_fn(const nth_channel_deref_fn<P>& d) : _n(d._n) {}

        int _n;        // the channel to use

        result_type operator()(argument_type srcP) const {
            return result_type(srcP[_n]);
        }
    };

    template <typename View> struct __nth_channel_view<View,false> {
    private:
        using deref_t = nth_channel_deref_fn<typename View::reference>;
        using AD = typename View::template add_deref<deref_t>;
    public:
        using type = typename AD::type;
        static type make(const View& src, int n) {
            return AD::make(src, deref_t(n));
        }
    };
} // namespace detail

/// \brief Given a source image view type View, returns the type of an image view over a single channel of View
/// \ingroup ImageViewTransformationsNthChannel
///
/// If the channels in the source view are adjacent in memory (such as planar non-step view or single-channel view) then the
/// return view is a single-channel non-step view.
/// If the channels are non-adjacent (interleaved and/or step view) then the return view is a single-channel step view.
template <typename View>
struct nth_channel_view_type {
private:
    BOOST_GIL_CLASS_REQUIRE(View, boost::gil, ImageViewConcept)
    using VB = detail::__nth_channel_view<View,view_is_basic<View>::value>;
public:
    using type = typename VB::type;
    static type make(const View& src, int n) { return VB::make(src,n); }
};


/// \ingroup ImageViewTransformationsNthChannel
template <typename View>
typename nth_channel_view_type<View>::type nth_channel_view(const View& src, int n) {
    return nth_channel_view_type<View>::make(src,n);
}







/// \defgroup ImageViewTransformationsKthChannel kth_channel_view
/// \ingroup ImageViewTransformations
/// \brief single-channel (grayscale) view of the K-th channel of a given image_view. The channel index is a template parameter

namespace detail {
    template <int K, typename View, bool AreChannelsTogether> struct __kth_channel_view_basic;

    // kth_channel_view when the channels are not adjacent in memory. This can happen for multi-channel interleaved images
    // or images with a step
    template <int K, typename View>
    struct __kth_channel_view_basic<K,View,false> {
    private:
        using channel_t = typename kth_element_type<typename View::value_type,K>::type;
    public:
        using type = typename view_type<channel_t, gray_layout_t, false, true, view_is_mutable<View>::value>::type;

        static type make(const View& src) {
            using locator_t = typename type::xy_locator;
            using x_iterator_t = typename type::x_iterator;
            using x_iterator_base_t = typename iterator_adaptor_get_base<x_iterator_t>::type;
            x_iterator_t sit(x_iterator_base_t(&gil::at_c<K>(src(0,0))),src.pixels().pixel_size());
            return type(src.dimensions(),locator_t(sit, src.pixels().row_size()));
        }
    };

    // kth_channel_view when the channels are together in memory (true for simple grayscale or planar images)
    template <int K, typename View>
    struct __kth_channel_view_basic<K,View,true> {
    private:
        using channel_t = typename kth_element_type<typename View::value_type, K>::type;
    public:
        using type = typename view_type<channel_t, gray_layout_t, false, false, view_is_mutable<View>::value>::type;
        static type make(const View& src) {
            using x_iterator_t = typename type::x_iterator;
            return interleaved_view(src.width(),src.height(),(x_iterator_t)&gil::at_c<K>(src(0,0)), src.pixels().row_size());
        }
    };

    template <int K, typename View, bool IsBasic> struct __kth_channel_view;

    // For basic (memory-based) views dispatch to __kth_channel_view_basic
    template <int K, typename View> struct __kth_channel_view<K,View,true>
    {
    private:
        using src_x_iterator = typename View::x_iterator;

        // Determines whether the channels of a given pixel iterator are adjacent in memory.
        // Planar and grayscale iterators have channels adjacent in memory, whereas multi-channel interleaved and iterators with non-fundamental step do not.
        static constexpr bool adjacent =
            !iterator_is_step<src_x_iterator>::value &&
            (is_planar<src_x_iterator>::value || num_channels<View>::value == 1);

    public:
        using type = typename __kth_channel_view_basic<K,View,adjacent>::type;

        static type make(const View& src) {
            return __kth_channel_view_basic<K,View,adjacent>::make(src);
        }
    };

    /// \brief Function object that returns a grayscale reference of the K-th channel (specified as a template parameter) of a given reference. Models: PixelDereferenceAdaptorConcept.
    /// \ingroup PixelDereferenceAdaptorModel
    ///
    /// If the input is a pixel value or constant reference, the function object is immutable. Otherwise it is mutable (and returns non-const reference to the k-th channel)
    /// \tparam SrcP reference to PixelConcept (could be pixel value or const/non-const reference)
    /// Examples: pixel<T,L>, pixel<T,L>&, const pixel<T,L>&, planar_pixel_reference<T&,L>, planar_pixel_reference<const T&,L>
    template <int K, typename SrcP>
    struct kth_channel_deref_fn
    {
        static constexpr bool is_mutable =
            pixel_is_reference<SrcP>::value && pixel_reference_is_mutable<SrcP>::value;

    private:
        using src_pixel_t = typename std::remove_reference<SrcP>::type;
        using channel_t = typename kth_element_type<src_pixel_t, K>::type;
        using const_ref_t = typename src_pixel_t::const_reference;
        using ref_t = typename pixel_reference_type<channel_t,gray_layout_t,false,is_mutable>::type;

    public:
        using const_t = kth_channel_deref_fn<K,const_ref_t>;
        using value_type = typename pixel_value_type<channel_t,gray_layout_t>::type;
        using const_reference = typename pixel_reference_type<channel_t,gray_layout_t,false,false>::type;
        using argument_type = SrcP;
        using reference = mp11::mp_if_c<is_mutable, ref_t, value_type>;
        using result_type = reference;

        kth_channel_deref_fn() {}
        template <typename P> kth_channel_deref_fn(const kth_channel_deref_fn<K,P>&) {}

        result_type operator()(argument_type srcP) const {
            return result_type(gil::at_c<K>(srcP));
        }
    };

    template <int K, typename View> struct __kth_channel_view<K,View,false> {
    private:
        using deref_t = kth_channel_deref_fn<K,typename View::reference>;
        using AD = typename View::template add_deref<deref_t>;
    public:
        using type = typename AD::type;
        static type make(const View& src) {
            return AD::make(src, deref_t());
        }
    };
} // namespace detail

/// \brief Given a source image view type View, returns the type of an image view over a given channel of View.
/// \ingroup ImageViewTransformationsKthChannel
///
/// If the channels in the source view are adjacent in memory (such as planar non-step view or single-channel view) then the
/// return view is a single-channel non-step view.
/// If the channels are non-adjacent (interleaved and/or step view) then the return view is a single-channel step view.
template <int K, typename View>
struct kth_channel_view_type {
private:
    BOOST_GIL_CLASS_REQUIRE(View, boost::gil, ImageViewConcept)
    using VB = detail::__kth_channel_view<K,View,view_is_basic<View>::value>;
public:
    using type = typename VB::type;
    static type make(const View& src) { return VB::make(src); }
};

/// \ingroup ImageViewTransformationsKthChannel
template <int K, typename View>
typename kth_channel_view_type<K,View>::type kth_channel_view(const View& src) {
    return kth_channel_view_type<K,View>::make(src);
}

} }  // namespace boost::gil

#endif

/* image_view_factory.hpp
S5MPykILHDSQPebKDo0S66lba9qWR3UFZZMVsCgyGGnBzTFdGXZbMdVgVUTdWpIxNilfCYJp1UldQDXgC1YSJbDHQCG45TOE4rxKN39mbMwIw8HfyZFT5HAugM4PXa4bLihfWYK49frMlh7cGcyoyKsOlbyNhJ/GeXcuvD334X4VV2U/I8b6jGfH7/fNZ15FOV2QD4GfkzqT0Tdf2K7jdcTe5+mPnCIOGrA29DWT3fNfNlkpz/31ClvYLj/Ip6v5HJ0F2a6vd+0kcqTwG5XxWf0SegtXHDbn59nB09aaS8uD6v2O5ca5o2vIhKPHwwYsgceNUOenvdZzZfi4EMcvzI00sQrr2CZ2sJdQiWJxVw3UWtq2jaFrm17nvs63z9XbvJ9+i2NczYR1gmjgNgkWQJlgH63DS8dXIjPGxagrUUcUDfXWIYd8Z9q62rRz9j6UGBY+qrXltPeSmW2L5RKpAGLfGtJv1sViAs3iM+L2L9tlkUWbJnlzhTtXUqA6U6sgd4YGyN/JPG/Ei94wEl0nYj345DOINfxcz/uFoYBmsWPrtYy1IrpaNTVXiI7lFGWqIyYXC5slBQ4LBn4G3AXanP1iPKWU0/nMtNEiyHgnVolEefWkfIbm25oawXbh7aHlavGhhaerEZlupBAxXklhADg6Lsqng9vHcHDriDVrHHuONBkShl5fiDurk691232pDEykFPvlqEak2zeuzFI1aMcZEluOynJrtJZmfQmtT5qD/1VXTVjj1oIXUBi2+sabJI9+BrPmMwf1j9zknaawPJzTJSWw+/FH1ybcDx2NrIEfM+0es4zfNXijqb7zWyTiFFUduxkLJRHoPt1ZxBPtgux1Z86zcBrPtU3+Hjmpq5kidoa+dikidYKurpCMOmqSzIoB2K0HI3qR2HTShM/tqKiaXYHZ2pi5LLBvVnFOIg+pBWcPij3yievIvtJJTNPA66uD+mYkcxO6jmsqqj5xx94Goy1pSXUI+Ah6+PStnyfSwsJULxU4rONvltOLKvoyqb6kPH+MQxSb8/iQHUylSClYLfpqy6dSnyYhaR6qajBWFv0KNtdJLpjAKPWwTWSD1j66uolrDMj166owL59+uIixTaKkTqJsx3BlyTPmECg+ttHke7pjJ36XWtskxGZSS4kwzBeLtHvZ16+ZBPQ0XXCQXmYLgEGMy3I9TLiBq6mfl4lkjGYjW6Ubanc0J+5TbWdUJ9JIw65EoFohWE0VUWPOunvtQkUk461DvKR7+sfMZFTFS0qC0IyQia1gCXy3EW/ZaVh2kdTkOSUKQND6BTwnMzw7g3VLNjeOmk7YEim4jRRLcBMzVBIYrVl6/wxr67Z0ycui8tRFaHEHb2adMWXpKOhR4jle2Ob6+E5V8FynrpHcNtFI23hjuEK2Tzdd0k50L3GOLs09mhKI+X8QoQgJJTNgYb5SVFbRES4a5Ba+CLxwQxoA1IUS1cGqXLBZ9vudZAhFFfuH+QTM8lpelxKklisjbcVxdjdUpJpzav+TKKxGNr98n2lLXvBN9nKWao2d/G4z2CGlcdlaEJG1cTEcyf/4tduxWpIe6PlAGPetLLk8aIZ0za075ab5Ielk9bGOWfathurG7dtAorAK0GeoZi5oMleHn/fMms0lscV8YD0/k3BpGq9TSvMZsFz4h3B7IV5EI/eCayBjDOMRszSOVAcuNswBX8KdKHVPKuoaDhOU8FTK6cWoo3MOGn7DO4KSIUHxHzNNTanZ/PICiQCtYZyTUOu2x0ko3ffcPkpoRABAWuSdcfaUvZVJkPYVrK8BjVs8tkvJVLF5qMNB9Me2YVT1SxIbKTVguizfYjfDxzkP8jkdjmF4j/rIDVTgc9OoJAkGYwroE559PqKKolPaj5YLTS2WcwvxyKxcsF3oQCxxDrKcc54QmhplfIjEQLXqDS3hZCvKD5otDRjatHMboffeBw9mg35uem9mVeX+imA9v+Z191e4mnjOBx+h4Vg3SzyCs5zObFiFxTgDixrBYHspT3pLy4ZTVG1AmTXwwsQpOF1csfvKTqydURcWBucWNcXjIb851eSyB+Ch7o0oVZei6u2KS8V9aZtWxdYm5GHQt9sP8Qv2mwA+VuJE0o3Y4uOVoYtOxoaOQKRoPktwm4GM1UInap27Bvd2oqQ91cpcqBIkzMY953sBwr9NT6VwEWsMhkZJD5lQTkq5MKgY6HKJG9aDtvtCFthZdcw1syhvPQW59hy1lXGdbVynNqFpdMrCptTQhw3wyoGU3iFaD63iuNNOlBpn8dmq1hNac26Tpso12hjc9U8KllFuUb2TuTT6qjUVbjyz9ZsHw+sj9CaTvhzT8oZPD4rgo1o6lQiRn5dFUXOwhKIggc59POJf1tWDoOdVjZcm5ArYZ4nNRlaJYAXh/fVRRNfqHlEXwYsMyuEyquyoZ1Oa9IrWy9lW0oktxgTRPuITN0eb9HrRlJGj0GAgjgmMJFduWkVcf+lYzVGENNg8MwOfvmgYSHJwzbn5nkvFc9NgCRfnsQGdMcYMxp3BWViMTeoddKokKXlDw8X/XNp2BJBXgP2Qq0mSr8NM9FVawl9Hj8pxjEquGRUZFCIJp/MPcNhsD1Kco60QDSBvW3blD9fHW69T2O3KxxWnWnegUMDVg7s4AuZvXK3UoAeJSPksHNofLMR74thXL4lIaWqAa2Ae/JMRlJ0Iho0FQD9Okg4EXwBvyLQlXO1DddX3HFHtGCFeJ3natewkNX2aFzcFzbMzq9hW8NmcX7CedGb5cNvbQmuKY0h/uk26i3Bmqfoh0t54jbj8BtYiwTG44GxDN0XrUK+Obq9W6yGImwpDZSOaQcOdM0j+Ngel/EmyB5kwwsyqUnnCLKBlcgj/QiG6WX7S3oG1umjzd3b3Z8ft7rYfjTr2GfboaR4wecfK3Ja0FXnUTBjeF/PiiRdt+x3AqYfLB+p172e2rozK1y4CzQOBqSGFJluEwmPgCW0VhWBM5cZ1y7fYPOUQIchgG2MWo4mjWjA4VSSd26HuhUJF+gZxT3aiZoOu8Ggl77LzzcCnnS0Y4YY1LJGiD7uXI0UG/IjiY1A+Cu0snPK3h/2i3+vvc+6eMCg+qK7k4ndS4aPOFSoPU5wzTvtndXL+4PZ5ZAoN1kW6AEdtlssGqruyZ6/9z8QqbBvSL/N5eHDrM9JDbzvu1py3EmOwAjMu1Vrdj7Ogh1kUde3b4y+lZlwZaXz918AleIe2qdAlrVFIIDQx2jmtV8OxSnuaMvzf6HPHDmADeUam1tfxzJjjI1qtLZFb+qGkrfA0W+iYsr1fx2EoswH/29qd/TX5jmuqJIyq7X/SKBEGNwXDwEeCJWS6MpBVSlNLSBkwcTY1EYgbaGFuN+I5DWsMAaO/ANrgnB1I3edHoegT+GSkLMJmfERPR/eBdgJykjhBGl2KD+NNtb/GY3s9Tt5Wk5U4UykqmyTaslZRUn75lpOJfM7ZZNy7lhYpqjF0NOcTyanIA1pqZvCjyEPIIa4/KMAt/DkzlZXAXhvMlVTMzQ+J9fjfI6mPA4PXvGVH4G8Pee3WH9/KXm1qn8Pvnjk7CyiLEnl4fjgTanQLREdqQqlZi7/aDoNPvN2wf+ljF52uMlI2nlBvlhDZ2cbLT2dJSZU6xdlTaje5cLS3lF7zIXnlEI/ZzdiQqnKjSInNi5JkI92hOwl9zvXhuQTDZhfkuP3rn4mmbwwnjV+kiQauLtoHF2Nx/6MXnt+30ZXP6H1v5M8G7U/v5Dxt41+h4qeG+7qZvyNwvcxE4LvFioGFzCWKMxiyWssG2tl/j8y0DfJhuEyWtXsZPlZpNo1qpcMRZ3MrO4IEzLOuzno+26h0SofYvpQ7mlsA7TSUK2nOzvXf6shqk7KGLdmT0br0aKZjsFJzDwMLJqH7NkPGXMg2YBdnMisqzm5Fi3n4M3Gl5MTaWn2jmR2olQBoWh4MzB2FPBAneYBCnj/LHpo8AJE+BgwOcm+k4xVSVKK5kDOaOkSGAFqaPs4aTEugzx6G/iIiGnMg9VwfZx1o22XdwnqAJZwmXvvX8MU2HCo++vV6jLMXYzbkudIauAnyJU1PWPVFqL7bmhmOZDmHUfWOvRONn2VvsqxdhMdyXYqdvc6S9vbvDjx5xenUvSGte81N5GIrK8sqL0WpC2MIL2vOwBc08sKpptH34qVkvue1XfeaKourzzmbWqtG5Sg1PK28yi8I2OOtijp4QQHtKFbQT85Ml5+xXrbL9zzv0o8G7PygpNLT8CuzMDZ4ZoFRKovwKQznRwnmDQptNNV5znLbQs8yRk2iw3bMpbU2/MHG1YQVyYKDHOHoPbf/5dFrgbW4PZwOUYxf8vYZ9ioVjlZCL4Wy7Ytmas5LGRR2Roq3ERn9eB1zt0PFZ/pMxCPmYhhmCOOOtGpp26GQ8BUrq1osJFfSLE5kFH03Tmqn0s8zpRwZ8qXN7a00DIx8T/cqq1poYWJqnn5PD7/N92O4CuS8CzKSHZ/pG2/aM6ZR2/aH6kCW0dQo8v1/z6B+9Wmfb68Ib1p+vm4/I7niY1pqPUuVM0yFYGc0THpzxXcfg6NRW+IGNm3T8pO5q3/5wepMxNNusU7X+SE0/zBYsKaDZojrdPmGGJDmQ33ui7sMGv5Wk06vLAH006THkgcLPZPFmVolu/VtpmwQiahWO7HkKHBqg52+YlVGEtKIuvLQb9kLq6Q/GPumNGHOSpG11JcGKbtR+Wwk3CyzYIcVi03FCyRiV/hp4tx+b0MmIkftJZsjoeZBquTE35d7H7BFvV8YNVjIO4gv9XAbZSADdIhlMQB/lfZg9eL+86VIrsEMZ9YJ1UXHaYz3bDNxl/+Uv3QKf6jkLulko5Vg0pILFWm9+sQ5TfZQEK4dRkZ3f2wC/ndvbOIq99M4OCiSd7hsw4pBmWUs2/eJ3/eVwPvbCLBQmCXguwO6HRHLTeB8A/xMgDM+pjHpop4APIVFv/tBmxyNXHfsB+XV7V3DVTgqOW0AxrRBoaSBsCaqmR5nFXEnpfpO6R7v2wbjP1jqzbdWJrJ1G+/k3ujzQrDtMbPnmv4Lh1XKFACDbwC/VHQjIdh5ZEuhJ3J33H9A4P28ddDW4Fp9PPo49P2Uc3BoAe/6uGnAMf9yEXECZdPDPz3tCeHZ7CGugDv7WesQ0/DhGfV506BijrEKwPto60DT9FHNwRqddlz4uSth3MhFnhz49Z6fxa+vkWIAeCR7Dr5j9uhjcPoCtZhA8TwAW2DhOw1FzjLyunmSKxRW4h5pN/na4LpqhUZSJmMwxU0SccqFOZcTYVs8hroKzkO+xwXtfW1v+TclWfmjXZPoOKNbMYO7XG4tl//j1kGsynkI3b9l5VLySPaj6YUrluZzxSe9A/h1zm8jpdZjBNQhFcjj6yZFOSLrWYWp5zvq9/0vK9z1Rm+KDy/fa63PWI1NyxVpyUvq98Dq/aDhGw8nu8HWoLtaKSP38TypRkBMo8HHm+fo5fSC+eifQEZX/imwIHpoVqwrsaKGSVztblVwx66eN42gHQfoaOtX5SqsespZu/LIwiSjf4bB1yHQD+7sf28/MBVXREnzakHyvxcsIWwFz5vLD7XpJxien/vZUfeB9VL//b5X3do9ztyx3IVk939mnj5kwvZ+K3msk7bQ8dB5XnWI4rpO0n07qVlxVz5yrOwIQC6glt91JytXdPOIj9r3qlMn3x8ZRteqU8vbdQqCjeE+gTU5lvmJUqhmUygE4bsVLauRq6FMpzcHPFSgjlhm6iphzjgXc+ZPeAG7lHyxhNe9z7eQeW1yJWR3N/UUr5wXR1ckO7cyGvNs19wd4147dFEc03+4t1FbqAVPTpbjMQuTXbzlXAu/DDwWgtMhGsD3XiWjd87O1pue+uzjDiahIXsNKM9IHbkMsmF1P6wxVWCQYrrSFxQXwCWJQaimVb0s6BpWsW0u50gSgyPp3KPypNmCexr6jPsrm1mhs9Qu/w8qgNV/UefYZ5D9UEP2M7bcBcuzrIq77+/5sTMH/OBT59tzwOZXfGNTLCXseSBw3ukdiNO7mWK7Rw4ulwvNPb3XBuxruoNUjSNrQ8g/JqyftbCXsiz7rLMOmf91py5Hgutir1qp7z/9RcYaHz5fyuSLy2P2/fHlo677r9r3p5azXdY9a1bs+8nNu1zu9L9e/vfz5f4xTd/brVCNolrTvuxtT3X2ZGOd8WSofDt6is+m/jk4noH4joqXFUL2C8Tuc5C9zO1IhX9b7gpSFcb1vuoKVe4FWOPK4sVDtKcv5oGeWVOi5pOif04cq54HRJ5ivC79ZUN0k0zj7FcuiI5NiH3W+a82RefB7/jFwm/Jtgui89cLv2terU5T2FTO5BIwhlaseHuWzSH2XMC60m03h/hbc6LPJAwLZwcZ+WW4/vWOP0TMFkphdmzAMrymHe5LLni9EzBPUzq+JT3b/QrWirLvnzvq9P3BV8W/yVFtT7naS5jetvF+jnB2u4WMET68SrJcieNiP57yj5+9IDpnXJTrxdea+P7+hbKdL2Li3wGYxoTNRb9eTzqKbLCZ4FJA+ncOo+/1GGsH85D2KVm3va60/+9rofaSf6kRVlcKR28Kh4elPVLfHOG1OSuaJn6Ewm4MKuftfwqfz8PWe86U7Czwqu1bp81D7JRUvKvTVo1SrML2yLznbq59IOvALXRt6l1qhNiLCMS3z2OGqgSsF+TPB5oFja+EDvzFabOAvWH6yilgT0C4Hj3bEJ0j4849PDm6/90irexxn4zQAsZUR4PXHjRuC/R5kboWyYbbssKfsg5co7j8g9ZZcQyf0DWMz99KP6is3YXBQb3oaMAQf1jKSU0VO6FVYRKFsvVTE7FiQfxyVnhazkFuiL/CzxxC1umuM6Ww8oXtF4l4UpjrL2209MHEM5+80NYHc15vip56V2N0ppj/JupXXRg9WhJ+V77u6MegtnRNN/49Va1UpRHFO/ebH26MLpzts5HJ3kwU1hbyAWcNbvvZpVCoPI1zG9/a3ES6SxkM1M0e+9+jBULmR2UweK/YWsu5/PdERDmnyvaLMGe9MH9+YzQzSaxPHmBToquXirrMf0O0va+MNc81aXrxClFA2akJSWrl2jG/qDF6VMrDHfOm2HPi2Buh84NnCyz94cZoScZ/Kj3FtpNfe8ORmVrr+Zp2R7xSNvVRTDGOQX9edZuIfgva86QGwaijj/f4j3chxAkUaHdzo7WHwP7uy1NsOT98oim6DX7100R95j7s2JX/Dr8N8Nso6/p3DwAJLPbTO231qxPVbUVfPyX0W4u11vxWGK6vgvSLK41Bly0WtA6j7ix369U6k/x7xGunjR2N0eOy/AfrLoouleVP/yG0r51fKfGN3/rgMUFFtj8bqNr/cntW96NY43LlJn5KIE8/S8aXyiHrFMs7WCbennM5a7/SdSoXNq9bdmuGL49C7BCnbcsB4u2fC0WCPSNq4HcY4oNn+o4raeZC/F3nqW6/lXT+Jl9q4H2Dxx7+EkBV2N6UK2xVGWvHRT6og/S0ZCA8H69nkPyE5ROon8qO0NK/6zXx8cbofGFnTwybjvxvPBmwvrP6JmzfnD4alW8ZeOcp1TTph6F7SIJrltMzHJpXNfK9Eyrb4X+4yNaj+/1lo/cwKIHw
*/