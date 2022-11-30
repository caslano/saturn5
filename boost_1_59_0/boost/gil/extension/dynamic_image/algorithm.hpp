//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_ALGORITHM_HPP
#define BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_ALGORITHM_HPP

#include <boost/gil/extension/dynamic_image/any_image.hpp>

#include <boost/gil/algorithm.hpp>

#include <functional>

////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some basic STL-style algorithms when applied to runtime type specified image views
/// \author Lubomir Bourdev and Hailin Jin \n
///         Adobe Systems Incorporated
/// \date 2005-2007 \n Last updated on September 24, 2006
///
////////////////////////////////////////////////////////////////////////////////////////

namespace boost { namespace gil {

namespace detail {

struct equal_pixels_fn : binary_operation_obj<equal_pixels_fn, bool>
{
    template <typename V1, typename V2>
    BOOST_FORCEINLINE
    bool apply_compatible(V1 const& v1, V2 const& v2) const
    {
        return equal_pixels(v1, v2);
    }
};

} // namespace detail

/// \ingroup ImageViewSTLAlgorithmsEqualPixels
/// \tparam Types Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam View Model MutableImageViewConcept
template <typename ...Types, typename View>
bool equal_pixels(any_image_view<Types...> const& src, View const& dst)
{
    return apply_operation(
        src,
        std::bind(detail::equal_pixels_fn(), std::placeholders::_1, dst));
}

/// \ingroup ImageViewSTLAlgorithmsEqualPixels
/// \tparam View Model ImageViewConcept
/// \tparam Types Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename View, typename ...Types>
bool equal_pixels(View const& src, any_image_view<Types...> const& dst)
{
    return apply_operation(
        dst,
        std::bind(detail::equal_pixels_fn(), src, std::placeholders::_1));
}

/// \ingroup ImageViewSTLAlgorithmsEqualPixels
/// \tparam Types1 Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam Types2 Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename ...Types1, typename ...Types2>
bool equal_pixels(any_image_view<Types1...> const& src, any_image_view<Types2...> const& dst)
{
    return apply_operation(src, dst, detail::equal_pixels_fn());
}

namespace detail {

struct copy_pixels_fn : public binary_operation_obj<copy_pixels_fn>
{
    template <typename View1, typename View2>
    BOOST_FORCEINLINE
    void apply_compatible(View1 const& src, View2 const& dst) const
    {
        copy_pixels(src,dst);
    }
};

} // namespace detail

/// \ingroup ImageViewSTLAlgorithmsCopyPixels
/// \tparam Types Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam View Model MutableImageViewConcept
template <typename ...Types, typename View>
void copy_pixels(any_image_view<Types...> const& src, View const& dst)
{
    apply_operation(src, std::bind(detail::copy_pixels_fn(), std::placeholders::_1, dst));
}

/// \ingroup ImageViewSTLAlgorithmsCopyPixels
/// \tparam Types Model Boost.MP11-compatible list of models of MutableImageViewConcept
/// \tparam View Model ImageViewConcept
template <typename ...Types, typename View>
void copy_pixels(View const& src, any_image_view<Types...> const& dst)
{
    apply_operation(dst, std::bind(detail::copy_pixels_fn(), src, std::placeholders::_1));
}

/// \ingroup ImageViewSTLAlgorithmsCopyPixels
/// \tparam Types1 Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam Types2 Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename ...Types1, typename ...Types2>
void copy_pixels(any_image_view<Types1...> const& src, any_image_view<Types2...> const& dst)
{
    apply_operation(src, dst, detail::copy_pixels_fn());
}

//forward declaration for default_color_converter (see full definition in color_convert.hpp)
struct default_color_converter;

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam Types Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam View Model MutableImageViewConcept
/// \tparam CC Model ColorConverterConcept
template <typename ...Types, typename View, typename CC>
void copy_and_convert_pixels(any_image_view<Types...> const& src, View const& dst, CC cc)
{
    using cc_fn = detail::copy_and_convert_pixels_fn<CC>;
    apply_operation(src, std::bind(cc_fn{cc}, std::placeholders::_1, dst));
}

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam Types Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam View Model MutableImageViewConcept
template <typename ...Types, typename View>
void copy_and_convert_pixels(any_image_view<Types...> const& src, View const& dst)
{
    using cc_fn = detail::copy_and_convert_pixels_fn<default_color_converter>;
    apply_operation(src, std::bind(cc_fn{}, std::placeholders::_1, dst));
}

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam View Model ImageViewConcept
/// \tparam Types Model Boost.MP11-compatible list of models of MutableImageViewConcept
/// \tparam CC Model ColorConverterConcept
template <typename View, typename ...Types, typename CC>
void copy_and_convert_pixels(View const& src, any_image_view<Types...> const& dst, CC cc)
{
    using cc_fn = detail::copy_and_convert_pixels_fn<CC>;
    apply_operation(dst, std::bind(cc_fn{cc}, src, std::placeholders::_1));
}

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam View Model ImageViewConcept
/// \tparam Type Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename View, typename ...Types>
void copy_and_convert_pixels(View const& src, any_image_view<Types...> const& dst)
{
    using cc_fn = detail::copy_and_convert_pixels_fn<default_color_converter>;
    apply_operation(dst, std::bind(cc_fn{}, src, std::placeholders::_1));
}

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam Types1 Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam Types2 Model Boost.MP11-compatible list of models of MutableImageViewConcept
/// \tparam CC Model ColorConverterConcept
template <typename ...Types1, typename ...Types2, typename CC>
void copy_and_convert_pixels(
    any_image_view<Types1...> const& src,
    any_image_view<Types2...> const& dst, CC cc)
{
    apply_operation(src, dst, detail::copy_and_convert_pixels_fn<CC>(cc));
}

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam Types1 Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam Types2 Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename ...Types1, typename ...Types2>
void copy_and_convert_pixels(
    any_image_view<Types1...> const& src,
    any_image_view<Types2...> const& dst)
{
    apply_operation(src, dst,
        detail::copy_and_convert_pixels_fn<default_color_converter>());
}

namespace detail {

template <bool IsCompatible>
struct fill_pixels_fn1
{
    template <typename V, typename Value>
    static void apply(V const &src, Value const &val) { fill_pixels(src, val); }
};

// copy_pixels invoked on incompatible images
template <>
struct fill_pixels_fn1<false>
{
    template <typename V, typename Value>
    static void apply(V const &, Value const &) { throw std::bad_cast();}
};

template <typename Value>
struct fill_pixels_fn
{
    fill_pixels_fn(Value const& val) : val_(val) {}

    using result_type = void;
    template <typename V>
    result_type operator()(V const& view) const
    {
        fill_pixels_fn1
        <
            pixels_are_compatible
            <
                typename V::value_type,
                Value
            >::value
        >::apply(view, val_);
    }

    Value val_;
};

} // namespace detail

/// \ingroup ImageViewSTLAlgorithmsFillPixels
/// \brief fill_pixels for any image view. The pixel to fill with must be compatible with the current view
/// \tparam Types Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename ...Types, typename Value>
void fill_pixels(any_image_view<Types...> const& view, Value const& val)
{
    apply_operation(view, detail::fill_pixels_fn<Value>(val));
}

}}  // namespace boost::gil

#endif

/* algorithm.hpp
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
*/