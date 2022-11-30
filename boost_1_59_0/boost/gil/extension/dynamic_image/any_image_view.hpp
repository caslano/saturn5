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

#include <boost/variant2/variant.hpp>

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

template <typename ...Views>
class any_image_view : public variant2::variant<Views...>
{
    using parent_t = variant2::variant<Views...>;

public:    
    using const_t = detail::views_get_const_t<any_image_view>;
    using x_coord_t = std::ptrdiff_t;
    using y_coord_t = std::ptrdiff_t;
    using point_t = point<std::ptrdiff_t>;
    using size_type = std::size_t;

    any_image_view() = default;
    any_image_view(any_image_view const& view) : parent_t((parent_t const&)view) {}

    template <typename View>
    explicit any_image_view(View const& view) : parent_t(view) {}

    template <typename ...OtherViews>
    any_image_view(any_image_view<OtherViews...> const& view)
        : parent_t((variant2::variant<OtherViews...> const&)view)
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

    template <typename ...OtherViews>
    any_image_view& operator=(any_image_view<OtherViews...> const& view)
    {
        parent_t::operator=((variant2::variant<OtherViews...> const&)view);
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

template <typename ...Views>
struct dynamic_x_step_type<any_image_view<Views...>>
{
private:
    // FIXME: Remove class name injection with gil:: qualification
    // Required as workaround for Boost.MP11 issue that treats unqualified metafunction
    // in the class definition of the same name as the specialization (Peter Dimov):
    //    invalid template argument for template parameter 'F', expected a class template
    template <typename T>
    using dynamic_step_view = typename gil::dynamic_x_step_type<T>::type;

public:
    using type = mp11::mp_transform<dynamic_step_view, any_image_view<Views...>>;
};

/////////////////////////////
//  HasDynamicYStepTypeConcept
/////////////////////////////

template <typename ...Views>
struct dynamic_y_step_type<any_image_view<Views...>>
{
private:
    // FIXME: Remove class name injection with gil:: qualification
    // Required as workaround for Boost.MP11 issue that treats unqualified metafunction
    // in the class definition of the same name as the specialization (Peter Dimov):
    //    invalid template argument for template parameter 'F', expected a class template
    template <typename T>
    using dynamic_step_view = typename gil::dynamic_y_step_type<T>::type;

public:
    using type = mp11::mp_transform<dynamic_step_view, any_image_view<Views...>>;
};

template <typename ...Views>
struct dynamic_xy_step_type<any_image_view<Views...>>
{
private:
    // FIXME: Remove class name injection with gil:: qualification
    // Required as workaround for Boost.MP11 issue that treats unqualified metafunction
    // in the class definition of the same name as the specialization (Peter Dimov):
    //    invalid template argument for template parameter 'F', expected a class template
    template <typename T>
    using dynamic_step_view = typename gil::dynamic_xy_step_type<T>::type;

public:
    using type = mp11::mp_transform<dynamic_step_view, any_image_view<Views...>>;
};

template <typename ...Views>
struct dynamic_xy_step_transposed_type<any_image_view<Views...>>
{
private:
    // FIXME: Remove class name injection with gil:: qualification
    // Required as workaround for Boost.MP11 issue that treats unqualified metafunction
    // in the class definition of the same name as the specialization (Peter Dimov):
    //    invalid template argument for template parameter 'F', expected a class template
    template <typename T>
    using dynamic_step_view = typename gil::dynamic_xy_step_type<T>::type;

public:
    using type = mp11::mp_transform<dynamic_step_view, any_image_view<Views...>>;
};

}}  // namespace boost::gil

#endif

/* any_image_view.hpp
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
*/