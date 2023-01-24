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
IhrT0V0aoUM/OmyIzNRjJRbakIZb6/tzOuuJFz87aqUR7Z7GWVkPrxNXRs0WcrkYzVpBO8MHsPhcm5NtjRhuu/TvhVCfP0qfktEyZwn5jMiKIb61ikbHnvqawmmp+QwD7w4yITNa0K675gtsRaiRte1eFONyfNEIORrwt03zkWtKSjLPgwfeWv+zPv5a4L/r4+50Q55wgj8ooG9EX03XH/9CZTRzDjezbj2I/mQXxQp53giZDlFUSf20/+fsXw3x4ugvT5U4a+SA0dtzVTxibrMaAu9sC5ERj5K41KVyy1fO3/1NH9coEcb2nJQBRJzYcC9zXsdNXztfkwJ/fPuzBjrUtt5FFtTS4QJfCbhDnTz0u0fGG8liLzvicXSVKhEGz+4KZwY/Slu/MC/VCKeXvlcq/uAazQ3VNKtAGn0j23PKSgcC/qaPv/xI7hTppUjAHLz43fvB+QvQw2Z8sG7jSe+dwtbt9cHoP/TxP2Ia6NfVRc3oCA9LTsYQNT4XoUc5Dzswz0xzzi4CL1BxU/wX98TjyT7ZabeG0ZSLxImWR4x9psa9jBleUQOv/Sfmp6FZt6kD2VdIH0LX/qE8YKILiS3wGkjKCpPZsebs9n/jELrQ63tlpiw9To/tU8hTIrAEbdMtwM9uhp4ytW0zMebGHIFhpFjW5iA80f3VYBw28pJXBB1xOpC3nh6Yv6gk22SKTZbd/4IMollJWWS6
*/