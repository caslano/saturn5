//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_ANY_IMAGE_VIEW_HPP
#define BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_ANY_IMAGE_VIEW_HPP

#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/point.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/variant.hpp>

namespace boost { namespace gil {

template <typename View>
struct dynamic_xy_step_transposed_type;

namespace detail {

template <typename View>
struct get_const_t { using type = typename View::const_t; };

template <typename Views>
struct views_get_const_t : mp11::mp_transform<get_const_t, Views> {};

// works for both image_view and image
struct any_type_get_num_channels
{
    using result_type = int;
    template <typename T>
    result_type operator()(const T&) const { return num_channels<T>::value; }
};

// works for both image_view and image
struct any_type_get_dimensions
{
    using result_type = point<std::ptrdiff_t>;
    template <typename T>
    result_type operator()(const T& v) const { return v.dimensions(); }
};

// works for image_view
struct any_type_get_size
{
    using result_type = std::size_t;
    template <typename T>
    result_type operator()(const T& v) const { return v.size(); }
};

} // namespace detail

////////////////////////////////////////////////////////////////////////////////////////
/// CLASS any_image_view
///
/// \ingroup ImageViewModel
/// \brief Represents a run-time specified image view. Models HasDynamicXStepTypeConcept, HasDynamicYStepTypeConcept, Note that this class does NOT model ImageViewConcept
///
/// Represents a view whose type (color space, layout, planar/interleaved organization, etc) can be specified at run time.
/// It is the runtime equivalent of \p image_view.
/// Some of the requirements of ImageViewConcept, such as the \p value_type alias cannot be fulfilled, since the language does not allow runtime type specification.
/// Other requirements, such as access to the pixels, would be inefficient to provide. Thus \p any_image_view does not fully model ImageViewConcept.
/// However, many algorithms provide overloads taking runtime specified views and thus in many cases \p any_image_view can be used in places taking a view.
///
/// To perform an algorithm on any_image_view, put the algorithm in a function object and invoke it by calling \p apply_operation(runtime_view, algorithm_fn);
////////////////////////////////////////////////////////////////////////////////////////

template <typename Views>
class any_image_view : public make_variant_over<Views>::type
{
    using parent_t = typename make_variant_over<Views>::type;
public:
    using const_t = any_image_view<detail::views_get_const_t<Views>>;
    using x_coord_t = std::ptrdiff_t;
    using y_coord_t = std::ptrdiff_t;
    using point_t = point<std::ptrdiff_t>;
    using size_type = std::size_t;

    any_image_view() = default;
    any_image_view(any_image_view const& view) : parent_t((parent_t const&)view) {}

    template <typename View>
    explicit any_image_view(View const& view) : parent_t(view) {}

    template <typename OtherViews>
    any_image_view(any_image_view<OtherViews> const& view)
        : parent_t((typename make_variant_over<OtherViews>::type const&)view)
    {}

    any_image_view& operator=(any_image_view const& view)
    {
        parent_t::operator=((parent_t const&)view);
        return *this;
    }

    template <typename View>
    any_image_view& operator=(View const& view)
    {
        parent_t::operator=(view);
        return *this;
    }

    template <typename OtherViews>
    any_image_view& operator=(any_image_view<OtherViews> const& view)
    {
        parent_t::operator=((typename make_variant_over<OtherViews>::type const&)view);
        return *this;
    }

    std::size_t num_channels()  const { return apply_operation(*this, detail::any_type_get_num_channels()); }
    point_t     dimensions()    const { return apply_operation(*this, detail::any_type_get_dimensions()); }
    size_type   size()          const { return apply_operation(*this, detail::any_type_get_size()); }
    x_coord_t   width()         const { return dimensions().x; }
    y_coord_t   height()        const { return dimensions().y; }
};

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename Views>
struct dynamic_x_step_type<any_image_view<Views>>
{
private:
    // FIXME: Remove class name injection with gil:: qualification
    // Required as workaround for Boost.MP11 issue that treats unqualified metafunction
    // in the class definition of the same name as the specialization (Peter Dimov):
    //    invalid template argument for template parameter 'F', expected a class template
    template <typename T>
    using dynamic_step_view = typename gil::dynamic_x_step_type<T>::type;

public:
    using type = any_image_view<mp11::mp_transform<dynamic_step_view, Views>>;
};

/////////////////////////////
//  HasDynamicYStepTypeConcept
/////////////////////////////

template <typename Views>
struct dynamic_y_step_type<any_image_view<Views>>
{
private:
    // FIXME: Remove class name injection with gil:: qualification
    // Required as workaround for Boost.MP11 issue that treats unqualified metafunction
    // in the class definition of the same name as the specialization (Peter Dimov):
    //    invalid template argument for template parameter 'F', expected a class template
    template <typename T>
    using dynamic_step_view = typename gil::dynamic_y_step_type<T>::type;

public:
    using type = any_image_view<mp11::mp_transform<dynamic_step_view, Views>>;
};

template <typename Views>
struct dynamic_xy_step_type<any_image_view<Views>>
{
private:
    // FIXME: Remove class name injection with gil:: qualification
    // Required as workaround for Boost.MP11 issue that treats unqualified metafunction
    // in the class definition of the same name as the specialization (Peter Dimov):
    //    invalid template argument for template parameter 'F', expected a class template
    template <typename T>
    using dynamic_step_view = typename gil::dynamic_xy_step_type<T>::type;

public:
    using type = any_image_view<mp11::mp_transform<dynamic_step_view, Views>>;
};

template <typename Views>
struct dynamic_xy_step_transposed_type<any_image_view<Views>>
{
private:
    // FIXME: Remove class name injection with gil:: qualification
    // Required as workaround for Boost.MP11 issue that treats unqualified metafunction
    // in the class definition of the same name as the specialization (Peter Dimov):
    //    invalid template argument for template parameter 'F', expected a class template
    template <typename T>
    using dynamic_step_view = typename gil::dynamic_xy_step_type<T>::type;

public:
    using type = any_image_view<mp11::mp_transform<dynamic_step_view, Views>>;
};

}}  // namespace boost::gil

#endif

/* any_image_view.hpp
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
*/