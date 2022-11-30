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
template <typename ...Views>
inline
auto flipped_up_down_view(any_image_view<Views...> const& src)
    -> typename dynamic_y_step_type<any_image_view<Views...>>::type
{
    using result_view_t = typename dynamic_y_step_type<any_image_view<Views...>>::type;
    return apply_operation(src, detail::flipped_up_down_view_fn<result_view_t>());
}

/// \ingroup ImageViewTransformationsFlipLR
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename ...Views>
inline
auto flipped_left_right_view(any_image_view<Views...> const& src)
    -> typename dynamic_x_step_type<any_image_view<Views...>>::type
{
    using result_view_t = typename dynamic_x_step_type<any_image_view<Views...>>::type;
    return apply_operation(src, detail::flipped_left_right_view_fn<result_view_t>());
}

/// \ingroup ImageViewTransformationsTransposed
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename ...Views>
inline
auto transposed_view(const any_image_view<Views...>& src)
    -> typename dynamic_xy_step_transposed_type<any_image_view<Views...>>::type
{
    using result_view_t = typename dynamic_xy_step_transposed_type<any_image_view<Views...>>::type;
    return apply_operation(src, detail::tranposed_view_fn<result_view_t>());
}

/// \ingroup ImageViewTransformations90CW
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename ...Views>
inline
auto rotated90cw_view(const any_image_view<Views...>& src)
    -> typename dynamic_xy_step_transposed_type<any_image_view<Views...>>::type
{
    using result_view_t = typename dynamic_xy_step_transposed_type<any_image_view<Views...>>::type;
    return apply_operation(src,detail::rotated90cw_view_fn<result_view_t>());
}

/// \ingroup ImageViewTransformations90CCW
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename ...Views>
inline
auto rotated90ccw_view(const any_image_view<Views...>& src)
    -> typename dynamic_xy_step_transposed_type<any_image_view<Views...>>::type
{
    return apply_operation(src,detail::rotated90ccw_view_fn<typename dynamic_xy_step_transposed_type<any_image_view<Views...>>::type>());
}

/// \ingroup ImageViewTransformations180
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename ...Views>
inline
auto rotated180_view(any_image_view<Views...> const& src)
    -> typename dynamic_xy_step_type<any_image_view<Views...>>::type
{
    using step_type = typename dynamic_xy_step_type<any_image_view<Views...>>::type;
    return apply_operation(src, detail::rotated180_view_fn<step_type>());
}

/// \ingroup ImageViewTransformationsSubimage
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename ...Views>
inline
auto subimage_view(
    any_image_view<Views...> const& src,
    point_t const& topleft,
    point_t const& dimensions)
    -> any_image_view<Views...>
{
    using subimage_view_fn = detail::subimage_view_fn<any_image_view<Views...>>;
    return apply_operation(src, subimage_view_fn(topleft, dimensions));
}

/// \ingroup ImageViewTransformationsSubimage
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename ...Views>
inline
auto subimage_view(
    any_image_view<Views...> const& src,
    std::ptrdiff_t x_min, std::ptrdiff_t y_min, std::ptrdiff_t width, std::ptrdiff_t height)
    -> any_image_view<Views...>
{
    using subimage_view_fn = detail::subimage_view_fn<any_image_view<Views...>>;
    return apply_operation(src, subimage_view_fn(point_t(x_min, y_min),point_t(width, height)));
}

/// \ingroup ImageViewTransformationsSubsampled
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename ...Views>
inline
auto subsampled_view(any_image_view<Views...> const& src, point_t const& step)
    -> typename dynamic_xy_step_type<any_image_view<Views...>>::type
{
    using step_type = typename dynamic_xy_step_type<any_image_view<Views...>>::type;
    using subsampled_view = detail::subsampled_view_fn<step_type>;
    return apply_operation(src, subsampled_view(step));
}

/// \ingroup ImageViewTransformationsSubsampled
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename ...Views>
inline
auto subsampled_view(any_image_view<Views...> const& src, std::ptrdiff_t x_step, std::ptrdiff_t y_step)
    -> typename dynamic_xy_step_type<any_image_view<Views...>>::type
{
    using step_type = typename dynamic_xy_step_type<any_image_view<Views...>>::type;
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
template <typename ...Views>
struct nth_channel_view_type<any_image_view<Views...>>
{
    using type = typename detail::views_get_nthchannel_type<any_image_view<Views...>>;
};

/// \ingroup ImageViewTransformationsNthChannel
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename ...Views>
inline
auto nth_channel_view(const any_image_view<Views...>& src, int n)
    -> typename nth_channel_view_type<any_image_view<Views...>>::type
{
    using result_view_t = typename nth_channel_view_type<any_image_view<Views...>>::type;
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
template <typename ...Views, typename DstP, typename CC>
struct color_converted_view_type<any_image_view<Views...>,DstP,CC>
{
    //using type = any_image_view<typename detail::views_get_ccv_type<Views, DstP, CC>::type>;
    using type = detail::views_get_ccv_type<any_image_view<Views...>, DstP, CC>;
};

/// \ingroup ImageViewTransformationsColorConvert
/// \brief overload of generic color_converted_view with user defined color-converter
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename DstP, typename ...Views, typename CC>
inline
auto color_converted_view(const any_image_view<Views...>& src, CC)
    -> typename color_converted_view_type<any_image_view<Views...>, DstP, CC>::type
{
    using cc_view_t = typename color_converted_view_type<any_image_view<Views...>, DstP, CC>::type;
    return apply_operation(src, detail::color_converted_view_fn<DstP, cc_view_t>());
}

/// \ingroup ImageViewTransformationsColorConvert
/// \brief Returns the type of a runtime-specified view, color-converted to a given pixel type with the default coor converter
template <typename ...Views, typename DstP>
struct color_converted_view_type<any_image_view<Views...>,DstP>
{
    using type = detail::views_get_ccv_type<any_image_view<Views...>, DstP, default_color_converter>;
};

/// \ingroup ImageViewTransformationsColorConvert
/// \brief overload of generic color_converted_view with the default color-converter
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename DstP, typename ...Views>
inline
auto color_converted_view(any_image_view<Views...> const& src)
    -> typename color_converted_view_type<any_image_view<Views...>, DstP>::type
{
    using cc_view_t = typename color_converted_view_type<any_image_view<Views...>, DstP>::type;
    return apply_operation(src, detail::color_converted_view_fn<DstP, cc_view_t>());
}

/// \ingroup ImageViewTransformationsColorConvert
/// \brief overload of generic color_converted_view with user defined color-converter
///        These are workarounds for GCC 3.4, which thinks color_converted_view is ambiguous with the same method for templated views (in gil/image_view_factory.hpp)
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename DstP, typename ...Views, typename CC>
inline
auto any_color_converted_view(const any_image_view<Views...>& src, CC)
    -> typename color_converted_view_type<any_image_view<Views...>, DstP, CC>::type
{
    using cc_view_t = typename color_converted_view_type<any_image_view<Views...>, DstP, CC>::type;
    return apply_operation(src, detail::color_converted_view_fn<DstP, cc_view_t>());
}

/// \ingroup ImageViewTransformationsColorConvert
/// \brief overload of generic color_converted_view with the default color-converter
///        These are workarounds for GCC 3.4, which thinks color_converted_view is ambiguous with the same method for templated views (in gil/image_view_factory.hpp)
/// \tparam Views Models Boost.MP11-compatible list of models of ImageViewConcept
template <typename DstP, typename ...Views>
inline
auto any_color_converted_view(const any_image_view<Views...>& src)
    -> typename color_converted_view_type<any_image_view<Views...>, DstP>::type
{
    using cc_view_t = typename color_converted_view_type<any_image_view<Views...>, DstP>::type;
    return apply_operation(src, detail::color_converted_view_fn<DstP, cc_view_t>());
}

/// \}

}}  // namespace boost::gil

#endif

/* image_view_factory.hpp
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
*/