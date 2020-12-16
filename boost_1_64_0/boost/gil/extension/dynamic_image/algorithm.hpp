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
T2gWQ+bC62W6c5pmqWT2H9/hGqkmz75+Y6tZdgesn0X2T7OEDhizjnRNZjWH3P8OtUtWkVlm8137MC5k5Zh19O7hgHERlhRtORDj0hGxF1larUsNUbtkpZgt/6PrdIwZWTV2zXa1K+3EuJBVYDY6ZeOQD2YwxJG5fzTTgPxz51GYZtlk6ZU/zE2TLb5we5NmNPPxHtNkL3rllMY7YzIju+aoyCd/aOZGZs+sbiBl5qN5kVmya2ZOmGOFd83COleoXl4zX2EVHlcqq5k/WSlmttnNv9AsgKwMs0+7bA3XLEhYubKLGms2VtzvTfK3AzQLFXblixh/zcLJrFjsA7p7BmoWRWbNrMrMVhPwfl60a3t4e4Fm8eJ+6ztduanZfrLSzOw+/e2NZkmi3fRpFzprliLsXkVvjFmayLt9H8cHmqWL+93fk4/P+DLFeKZfv/cOdSbafRvjdlGzXNGXsIFudprliXHZvqHsb5oZhuit39Y7UahdMn6/UIfagzWzJ7PkNTFoVJxmTmQ89prer25p5iysb9zTu5q56O9H/90e9ekuzN629XbNWoi+VB4XgLnSTtxvQf0N+IzWS9hn138Yq1lXcb9m1Rau1MxHtFtYdsavmvkKO13mUxvN/EQ/w308KmsWINr1KPMM4xko7HhsHGoiSFyzfco2fEY0VliHzPZNNQsV8RU+Hz5Cs1lkZXjsd+dh/i0Qltr5CGopUlijSynNNVslYsiZMyFFsxjRLqDZyueaxQortzVvlmZxonYvrW6KdSmRzIZZ13XJIzVLFba5/KHHmmWSlWVmm7v4J81yhXmf639Ks3wRX8+RWUmaFYg8RLpWWfPRKFh9u5CS/T7XzIKMx+79/DE+7zeS8XUw+Lz9S82cRLuXkZ8O18xFWGfHUZh/7sKmWm6P1KwFWWk+xwbNwli3E3bAZ2E3zbzJeI7++aJ3Oc38hfk3mtkGdS3G5cGdd0M1Cxb97HV4UU3NQsgsmU0bfB/f1wgTNn39wjTNwskqs74EHl3thRoUdu6ovZNmyWQuzOo4f4L1M4+sMbPd05LwGbTblzRXmTX3XT0X/STrwGxPWMEU1C4Zr8FSi+osRe2S8bq+MHaOM2pXtJvToPQB1CdZeWae/fp7amb1ld4Glb57WjMHYVV3ZbREfGRVmA05uu4IakLYlXsVByK3ZA7Mxh39ETmKEDZ8tKsH1gIy3bjUm468J5JZ8/m+6g1iTyWrwOzp0V+/x3iS8fGsfttQCuMprvnJf54sx3gK84nrH4bxHErzhVmSXcQl7B1kfD641ngWgD2AzJnZyaa+7TEuZHw+HH596JFmUWR8XFYsaNpdsw2i3eUy9VBnW8gsmS1NWbxOs3hhB8K6Yc/ZL645r533NswVEV/FRY7faJZOxsfM60LbY5plixg+dfbMwRwTVqJy7ndYWwNF3o9Pqo31k4y3+8a13CvNnIUZet6sr5kHGa+JBceHu2rmJezuL5EvkFthEVGLw5BbYQ/eB2LvDyHjc6zMtz//iTVLWNDjniWQdzJe1yNuROzAeibMcvmw6ZoliDELenDED/kT/Tzj9/kC5I+sKjP/Jesua/aQjNeLYb+9O+aKGOu//5gLsximr6U97nMHI3/DimvJdNA9+rJaa+RPWNyDihhPDzJrZrXPHc5D/oTdjFnzr2Y+wxBDkVWav+4l9jFxv/vvY9diHxPtep+7+xdyS2bD2t3be+gGciv6kv4qIxm5JSvHzNN6aAfklqwysxFW7S8gf2RVmL0uuNURc4ysKrO9dVtjrTP9GKgas3br1hZ/l4qsDIsvrcf5xdgDyOxZO5uI2w8w1mR8zCZ2csOa7EvmyOzt0bitGDOyisw=
*/