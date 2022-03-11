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
auto interleaved_view(point<std::size_t> dim, Iterator pixels,
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
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
*/