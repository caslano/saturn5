//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_IMAGE_VIEW_FACTORY_HPP
#define BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_IMAGE_VIEW_FACTORY_HPP

#include <boost/gil/extension/dynamic_image/any_image_view.hpp>

#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/point.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstdint>

namespace boost { namespace gil {

// Methods for constructing any image views from other any image views
// Extends image view factory to runtime type-specified views (any_image_view)

namespace detail {

template <typename ResultView>
struct flipped_up_down_view_fn
{
    using result_type = ResultView;

    template <typename View>
    auto operator()(View const& src) const -> result_type
    {
        return result_type{flipped_up_down_view(src)};
    }
};

template <typename ResultView>
struct flipped_left_right_view_fn
{
    using result_type = ResultView;

    template <typename View>
    auto operator()(View const& src) const -> result_type
    {
        return result_type{flipped_left_right_view(src)};
    }
};

template <typename ResultView>
struct rotated90cw_view_fn
{
    using result_type = ResultView;

    template <typename View>
    auto operator()(View const& src) const -> result_type
    {
        return result_type{rotated90cw_view(src)};
    }
};

template <typename ResultView>
struct rotated90ccw_view_fn
{
    using result_type = ResultView;

    template <typename View>
    auto operator()(View const& src) const -> result_type
    {
        return result_type{rotated90ccw_view(src)};
    }
};

template <typename ResultView>
struct tranposed_view_fn
{
    using result_type = ResultView;

    template <typename View>
    auto operator()(View const& src) const -> result_type
    {
        return result_type{tranposed_view(src)};
    }
};

template <typename ResultView>
struct rotated180_view_fn
{
    using result_type = ResultView;

    template <typename View>
    auto operator()(View const& src) const -> result_type
    {
        return result_type{rotated180_view(src)};
    }
};

template <typename ResultView>
struct subimage_view_fn
{
    using result_type = ResultView;

    subimage_view_fn(point_t const& topleft, point_t const& dimensions)
        : _topleft(topleft), _size2(dimensions)
    {}

    template <typename View>
    auto operator()(View const& src) const -> result_type
    {
        return result_type{subimage_view(src,_topleft,_size2)};
    }

    point_t _topleft;
    point_t _size2;
};

template <typename ResultView>
struct subsampled_view_fn
{
    using result_type = ResultView;

    subsampled_view_fn(point_t const& step) : _step(step) {}

    template <typename View>
    auto operator()(View const& src) const -> result_type
    {
        return result_type{subsampled_view(src,_step)};
    }

    point_t _step;
};

template <typename ResultView>
struct nth_channel_view_fn
{
    using result_type = ResultView;

    nth_channel_view_fn(int n) : _n(n) {}

    template <typename View>
    auto operator()(View const& src) const -> result_type
    {
        return result_type(nth_channel_view(src,_n));
    }

    int _n;
};

template <typename DstP, typename ResultView, typename CC = default_color_converter>
struct color_converted_view_fn
{
    using result_type = ResultView;

    color_converted_view_fn(CC cc = CC()): _cc(cc) {}

    template <typename View>
    auto operator()(View const& src) const -> result_type
    {
        return result_type{color_converted_view<DstP>(src, _cc)};
    }

private:
    CC _cc;
};

} // namespace detail

/// \ingroup ImageViewTransformationsFlipUD
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto flipped_up_down_view(any_image_view<Views> const& src)
    -> typename dynamic_y_step_type<any_image_view<Views>>::type
{
    using result_view_t = typename dynamic_y_step_type<any_image_view<Views>>::type;
    return apply_operation(src, detail::flipped_up_down_view_fn<result_view_t>());
}

/// \ingroup ImageViewTransformationsFlipLR
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto flipped_left_right_view(any_image_view<Views> const& src)
    -> typename dynamic_x_step_type<any_image_view<Views>>::type
{
    using result_view_t = typename dynamic_x_step_type<any_image_view<Views>>::type;
    return apply_operation(src, detail::flipped_left_right_view_fn<result_view_t>());
}

/// \ingroup ImageViewTransformationsTransposed
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto transposed_view(const any_image_view<Views>& src)
    -> typename dynamic_xy_step_transposed_type<any_image_view<Views>>::type
{
    using result_view_t = typename dynamic_xy_step_transposed_type<any_image_view<Views>>::type;
    return apply_operation(src, detail::tranposed_view_fn<result_view_t>());
}

/// \ingroup ImageViewTransformations90CW
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto rotated90cw_view(const any_image_view<Views>& src)
    -> typename dynamic_xy_step_transposed_type<any_image_view<Views>>::type
{
    using result_view_t = typename dynamic_xy_step_transposed_type<any_image_view<Views>>::type;
    return apply_operation(src,detail::rotated90cw_view_fn<result_view_t>());
}

/// \ingroup ImageViewTransformations90CCW
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto rotated90ccw_view(const any_image_view<Views>& src)
    -> typename dynamic_xy_step_transposed_type<any_image_view<Views>>::type
{
    return apply_operation(src,detail::rotated90ccw_view_fn<typename dynamic_xy_step_transposed_type<any_image_view<Views>>::type>());
}

/// \ingroup ImageViewTransformations180
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto rotated180_view(any_image_view<Views> const& src)
    -> typename dynamic_xy_step_type<any_image_view<Views>>::type
{
    using step_type = typename dynamic_xy_step_type<any_image_view<Views>>::type;
    return apply_operation(src, detail::rotated180_view_fn<step_type>());
}

/// \ingroup ImageViewTransformationsSubimage
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto subimage_view(
    any_image_view<Views> const& src,
    point_t const& topleft,
    point_t const& dimensions)
    -> any_image_view<Views>
{
    using subimage_view_fn = detail::subimage_view_fn<any_image_view<Views>>;
    return apply_operation(src, subimage_view_fn(topleft, dimensions));
}

/// \ingroup ImageViewTransformationsSubimage
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto subimage_view(
    any_image_view<Views> const& src,
    std::ptrdiff_t x_min, std::ptrdiff_t y_min, std::ptrdiff_t width, std::ptrdiff_t height)
    -> any_image_view<Views>
{
    using subimage_view_fn = detail::subimage_view_fn<any_image_view<Views>>;
    return apply_operation(src, subimage_view_fn(point_t(x_min, y_min),point_t(width, height)));
}

/// \ingroup ImageViewTransformationsSubsampled
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto subsampled_view(any_image_view<Views> const& src, point_t const& step)
    -> typename dynamic_xy_step_type<any_image_view<Views>>::type
{
    using step_type = typename dynamic_xy_step_type<any_image_view<Views>>::type;
    using subsampled_view = detail::subsampled_view_fn<step_type>;
    return apply_operation(src, subsampled_view(step));
}

/// \ingroup ImageViewTransformationsSubsampled
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto subsampled_view(any_image_view<Views> const& src, std::ptrdiff_t x_step, std::ptrdiff_t y_step)
    -> typename dynamic_xy_step_type<any_image_view<Views>>::type
{
    using step_type = typename dynamic_xy_step_type<any_image_view<Views>>::type;
    using subsampled_view_fn = detail::subsampled_view_fn<step_type>;
    return apply_operation(src, subsampled_view_fn(point_t(x_step, y_step)));
}

namespace detail {

template <typename View>
struct get_nthchannel_type { using type = typename nth_channel_view_type<View>::type; };

template <typename Views>
struct views_get_nthchannel_type : mp11::mp_transform<get_nthchannel_type, Views> {};

} // namespace detail

/// \ingroup ImageViewTransformationsNthChannel
/// \brief Given a runtime source image view, returns the type of a runtime image view over a single channel of the source view
template <typename Views>
struct nth_channel_view_type<any_image_view<Views>>
{
    using type = any_image_view<typename detail::views_get_nthchannel_type<Views>::type>;
};

/// \ingroup ImageViewTransformationsNthChannel
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename Views>
inline
auto nth_channel_view(const any_image_view<Views>& src, int n)
    -> typename nth_channel_view_type<any_image_view<Views>>::type
{
    using result_view_t = typename nth_channel_view_type<any_image_view<Views>>::type;
    return apply_operation(src,detail::nth_channel_view_fn<result_view_t>(n));
}

namespace detail {

template <typename View, typename DstP, typename CC>
struct get_ccv_type : color_converted_view_type<View, DstP, CC> {};

template <typename Views, typename DstP, typename CC>
struct views_get_ccv_type
{
private:
    // FIXME: Remove class name injection with detail:: qualification
    // Required as workaround for MP11 issue that treats unqualified metafunction
    // in the class definition of the same name as the specialization (Peter Dimov):
    //    invalid template argument for template parameter 'F', expected a class template
    template <typename T>
    using ccvt = detail::get_ccv_type<T, DstP, CC>;

public:
    using type = mp11::mp_transform<ccvt, Views>;
};

} // namespace detail

/// \ingroup ImageViewTransformationsColorConvert
/// \brief Returns the type of a runtime-specified view, color-converted to a given pixel type with user specified color converter
template <typename Views, typename DstP, typename CC>
struct color_converted_view_type<any_image_view<Views>,DstP,CC>
{
    using type = any_image_view<typename detail::views_get_ccv_type<Views, DstP, CC>::type>;
};

/// \ingroup ImageViewTransformationsColorConvert
/// \brief overload of generic color_converted_view with user defined color-converter
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename DstP, typename Views, typename CC>
inline
auto color_converted_view(const any_image_view<Views>& src, CC)
    -> typename color_converted_view_type<any_image_view<Views>, DstP, CC>::type
{
    using cc_view_t = typename color_converted_view_type<any_image_view<Views>, DstP, CC>::type;
    return apply_operation(src, detail::color_converted_view_fn<DstP, cc_view_t>());
}

/// \ingroup ImageViewTransformationsColorConvert
/// \brief Returns the type of a runtime-specified view, color-converted to a given pixel type with the default coor converter
template <typename Views, typename DstP>
struct color_converted_view_type<any_image_view<Views>,DstP>
{
    using type = any_image_view<typename detail::views_get_ccv_type<Views, DstP, default_color_converter>::type>;
};

/// \ingroup ImageViewTransformationsColorConvert
/// \brief overload of generic color_converted_view with the default color-converter
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename DstP, typename Views>
inline
auto color_converted_view(any_image_view<Views> const& src)
    -> typename color_converted_view_type<any_image_view<Views>, DstP>::type
{
    using cc_view_t = typename color_converted_view_type<any_image_view<Views>, DstP>::type;
    return apply_operation(src, detail::color_converted_view_fn<DstP, cc_view_t>());
}

/// \ingroup ImageViewTransformationsColorConvert
/// \brief overload of generic color_converted_view with user defined color-converter
///        These are workarounds for GCC 3.4, which thinks color_converted_view is ambiguous with the same method for templated views (in gil/image_view_factory.hpp)
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename DstP, typename Views, typename CC>
inline
auto any_color_converted_view(const any_image_view<Views>& src, CC)
    -> typename color_converted_view_type<any_image_view<Views>, DstP, CC>::type
{
    using cc_view_t = typename color_converted_view_type<any_image_view<Views>, DstP, CC>::type;
    return apply_operation(src, detail::color_converted_view_fn<DstP, cc_view_t>());
}

/// \ingroup ImageViewTransformationsColorConvert
/// \brief overload of generic color_converted_view with the default color-converter
///        These are workarounds for GCC 3.4, which thinks color_converted_view is ambiguous with the same method for templated views (in gil/image_view_factory.hpp)
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename DstP, typename Views>
inline
auto any_color_converted_view(const any_image_view<Views>& src)
    -> typename color_converted_view_type<any_image_view<Views>, DstP>::type
{
    using cc_view_t = typename color_converted_view_type<any_image_view<Views>, DstP>::type;
    return apply_operation(src, detail::color_converted_view_fn<DstP, cc_view_t>());
}

/// \}

}}  // namespace boost::gil

#endif

/* image_view_factory.hpp
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
*/