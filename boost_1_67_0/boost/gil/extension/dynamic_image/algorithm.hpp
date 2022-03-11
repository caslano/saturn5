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
template <typename Types, typename View>
bool equal_pixels(any_image_view<Types> const& src, View const& dst)
{
    return apply_operation(
        src,
        std::bind(detail::equal_pixels_fn(), std::placeholders::_1, dst));
}

/// \ingroup ImageViewSTLAlgorithmsEqualPixels
/// \tparam View Model ImageViewConcept
/// \tparam Types Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename View, typename Types>
bool equal_pixels(View const& src, any_image_view<Types> const& dst)
{
    return apply_operation(
        dst,
        std::bind(detail::equal_pixels_fn(), src, std::placeholders::_1));
}

/// \ingroup ImageViewSTLAlgorithmsEqualPixels
/// \tparam Types1 Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam Types2 Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename Types1, typename Types2>
bool equal_pixels(any_image_view<Types1> const& src, any_image_view<Types2> const& dst)
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
template <typename Types, typename View>
void copy_pixels(any_image_view<Types> const& src, View const& dst)
{
    apply_operation(src, std::bind(detail::copy_pixels_fn(), std::placeholders::_1, dst));
}

/// \ingroup ImageViewSTLAlgorithmsCopyPixels
/// \tparam Types Model Boost.MP11-compatible list of models of MutableImageViewConcept
/// \tparam View Model ImageViewConcept
template <typename Types, typename View>
void copy_pixels(View const& src, any_image_view<Types> const& dst)
{
    apply_operation(dst, std::bind(detail::copy_pixels_fn(), src, std::placeholders::_1));
}

/// \ingroup ImageViewSTLAlgorithmsCopyPixels
/// \tparam Types1 Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam Types2 Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename Types1, typename Types2>
void copy_pixels(any_image_view<Types1> const& src, any_image_view<Types2> const& dst)
{
    apply_operation(src, dst, detail::copy_pixels_fn());
}

//forward declaration for default_color_converter (see full definition in color_convert.hpp)
struct default_color_converter;

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam Types Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam View Model MutableImageViewConcept
/// \tparam CC Model ColorConverterConcept
template <typename Types, typename View, typename CC>
void copy_and_convert_pixels(any_image_view<Types> const& src, View const& dst, CC cc)
{
    using cc_fn = detail::copy_and_convert_pixels_fn<CC>;
    apply_operation(src, std::bind(cc_fn{cc}, std::placeholders::_1, dst));
}

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam Types Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam View Model MutableImageViewConcept
template <typename Types, typename View>
void copy_and_convert_pixels(any_image_view<Types> const& src, View const& dst)
{
    using cc_fn = detail::copy_and_convert_pixels_fn<default_color_converter>;
    apply_operation(src, std::bind(cc_fn{}, std::placeholders::_1, dst));
}

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam View Model ImageViewConcept
/// \tparam Types Model Boost.MP11-compatible list of models of MutableImageViewConcept
/// \tparam CC Model ColorConverterConcept
template <typename View, typename Types, typename CC>
void copy_and_convert_pixels(View const& src, any_image_view<Types> const& dst, CC cc)
{
    using cc_fn = detail::copy_and_convert_pixels_fn<CC>;
    apply_operation(dst, std::bind(cc_fn{cc}, src, std::placeholders::_1));
}

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam View Model ImageViewConcept
/// \tparam Type Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename View, typename Types>
void copy_and_convert_pixels(View const& src, any_image_view<Types> const& dst)
{
    using cc_fn = detail::copy_and_convert_pixels_fn<default_color_converter>;
    apply_operation(dst, std::bind(cc_fn{}, src, std::placeholders::_1));
}

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam Types1 Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam Types2 Model Boost.MP11-compatible list of models of MutableImageViewConcept
/// \tparam CC Model ColorConverterConcept
template <typename Types1, typename Types2, typename CC>
void copy_and_convert_pixels(
    any_image_view<Types1> const& src,
    any_image_view<Types2> const& dst, CC cc)
{
    apply_operation(src, dst, detail::copy_and_convert_pixels_fn<CC>(cc));
}

/// \ingroup ImageViewSTLAlgorithmsCopyAndConvertPixels
/// \tparam Types1 Model Boost.MP11-compatible list of models of ImageViewConcept
/// \tparam Types2 Model Boost.MP11-compatible list of models of MutableImageViewConcept
template <typename Types1, typename Types2>
void copy_and_convert_pixels(
    any_image_view<Types1> const& src,
    any_image_view<Types2> const& dst)
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
template <typename Types, typename Value>
void fill_pixels(any_image_view<Types> const& view, Value const& val)
{
    apply_operation(view, detail::fill_pixels_fn<Value>(val));
}

}}  // namespace boost::gil

#endif

/* algorithm.hpp
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
*/