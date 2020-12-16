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
dvwdewcZj+FS5bOtsX6S8TErM/NLa+SIjMdw5OHXd1FnwmJeZYVhjSSzZtbn4oFoxEdWi+dveskheLaYqa/Pus+3LcccI+P9nOw1rAFyRMbnw2avzzAugWRVmf1rc3c2zpGi3adz1i9FDZJV4XOlgVcU9n5h4x5d/gpzjIzXp+3pza7I3yz9uts/d6MF4hMWMv9GfcRH5sTs3eTZu5A/Mh7fPttfLyF/ZEZe81PG2yM+Mj7/2pQIX4L6FNf8s+rensgtWXlmPkl+m5Bb0S7k6M+7Mf9m6y1yQp8bmH9kvJ/z+j0r3h9EO1fbJZ2RWzIbZtHpzc/huYqM1/zuoDkxmJtkuhyVLd7/Esj4HBtsm2OBtUf0ZXlG5DbELmI4NCI6G3mfo89tSoMvRyDvZHwejXJ/Pw/zlsyWWac0p+qInYzX7umynTFm4WQ8hovfuzfC3i/ajbk9yBN5F+3Oxp6cjHeHZLzme9Ws5oe9g8weZpo7Mxoj73P1sW/t2GID8k7mwmzTcfsQ7B2iXVizsZjTYWQ8hl+/cQ1AfGQ8t2emtvwW8ZHVZnZh6kvUfLa83xx/zBVDuH5tPbb432vY/8h4X2wzUlETvmQ8vkHefj8gR2RGZrV+OPECMYh2wR49k1GDol1Zu6PpiEH0xW7niELE8K2+lnLSf0E7BzI+Lk0stydh/pHxOdYvbcp4xEdWkdm0V7VuYl0i43PlwKWaq7EukfEcrTkzrCLObmR83lr173YAsQs7dvjxVMw/Mh57l5SnMajBefp2Jwr+Qh7cyHjeP//lv40w/8jKM3N6GFMX9UnmxKzr9czJyK1o90ebzrWw9oi+zJ7pbIm1h4zPo/6PqnyC2MX9XE8mL8T8I+Nz83DruDXYU+fr53TBobbvETtZDWZxW6MLkFsynqMmrd+kYm0lc+ax+zSIQu2S8fiSGnS5h/lHxnM0eZbbT9hXyHgeSvpcxpmhQFwzrHzH9qjdBfr4yv/aIxRzk8ya2WO/yljrvMh4fAtvD0RuA8l4fF+Xbe+G2hXtSgZYh6B2yXjeh85s+g1iJzMys37VKAtrKxmfK9+3/nwjckvGc1tiYOID5Hah/r3ijOX/xT7tTMbHLP699RXETubIrNqs/C8RO1n3IvMtsr2n+09CDGT8meT6wLcVEAMZr91Bq7bXx9wk4zH4vU08jbm5SH/Ndw3cKiMGMhtmCXcGBSC3ZA58PLfMyEXtCpsx3+YEapeMj/W4Jx5Yd6NEO4dDobswN8lsmdX6Y0RnzE2yWnxcZgYXz00yXp8+dvHfI/bv9PtK8888kSNPMn6/99OaZCA+Mn6/8NNfYu8PE1b+0/c4g8WS8fga1KvvgTOtuJ93i29OYW6Kdr2n7q+HuUlWgdmEKQ+iEV+Efn05NsPeDvkj4zVov2BRY8Qn2iX8MLs64iPjc+zy6vbfYW6S8dzafJb/CeamsMATJQKQPzInZh5DP/8V+SNzZvbkwMBErD2L9e06Hv3kGOYYWRNeE+uHRyEGMt2z0yT3lcgRGe/n/n0dOiJHZHzMRr74Oh97Pxkfl39sfliHGMh4TaT/Nj8AMSzR569Wibhm2B/IdHU95H5/5IisDrNVl8Y7ID4yHsPomENHsD+Q2TOzsOn7CnOMjI9no019UlCDZHwexV5r0gjxkfHYd8X1wLw1LNXX9Zr7N7ogdjIjn3+JQ/qhPsn4Ot+q/HLE4EvGx2xYyf+uwfpJxmN/sbTOLzgXiL6Ez12xB+MirFeVle8wLqKf32x8NxO1K9od+P79XdSE6OfNJz0bY8xkX6x+fIl5G6nPUfvcpHNYk8n4uPzuWHMoal7Yu6oRFhgXsqo8vtk9VmJcyBx57Vaom4Q=
*/