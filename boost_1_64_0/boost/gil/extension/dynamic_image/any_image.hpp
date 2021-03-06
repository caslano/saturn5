//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_ANY_IMAGE_HPP
#define BOOST_GIL_EXTENSION_DYNAMIC_IMAGE_ANY_IMAGE_HPP

#include <boost/gil/extension/dynamic_image/any_image_view.hpp>
#include <boost/gil/extension/dynamic_image/apply_operation.hpp>

#include <boost/gil/image.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/config.hpp>
#include <boost/variant.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4512) //assignment operator could not be generated
#endif

namespace boost { namespace gil {

namespace detail {

template <typename T>
using get_view_t = typename T::view_t;

template <typename Images>
using images_get_views_t = mp11::mp_transform<get_view_t, Images>;

template <typename T>
using get_const_view_t = typename T::const_view_t;

template <typename Images>
using images_get_const_views_t = mp11::mp_transform<get_const_view_t, Images>;

struct recreate_image_fnobj
{
    using result_type = void;
    point<std::ptrdiff_t> const& _dimensions;
    unsigned _alignment;

    recreate_image_fnobj(point<std::ptrdiff_t> const& dims, unsigned alignment)
        : _dimensions(dims), _alignment(alignment)
    {}

    template <typename Image>
    result_type operator()(Image& img) const { img.recreate(_dimensions,_alignment); }
};

template <typename AnyView>  // Models AnyViewConcept
struct any_image_get_view
{
    using result_type = AnyView;
    template <typename Image>
    result_type operator()(Image& img) const
    {
        return result_type(view(img));
    }
};

template <typename AnyConstView>  // Models AnyConstViewConcept
struct any_image_get_const_view
{
    using result_type = AnyConstView;
    template <typename Image>
    result_type operator()(Image const& img) const { return result_type{const_view(img)}; }
};

} // namespce detail

////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup ImageModel
/// \brief Represents a run-time specified image. Note it does NOT model ImageConcept
///
/// Represents an image whose type (color space, layout, planar/interleaved organization, etc) can be specified at run time.
/// It is the runtime equivalent of \p image.
/// Some of the requirements of ImageConcept, such as the \p value_type alias cannot be fulfilled, since the language does not allow runtime type specification.
/// Other requirements, such as access to the pixels, would be inefficient to provide. Thus \p any_image does not fully model ImageConcept.
/// In particular, its \p view and \p const_view methods return \p any_image_view, which does not fully model ImageViewConcept. See \p any_image_view for more.
////////////////////////////////////////////////////////////////////////////////////////

template <typename Images>
class any_image : public make_variant_over<Images>::type
{
    using parent_t = typename make_variant_over<Images>::type;
public:
    using view_t = any_image_view<detail::images_get_views_t<Images>>;
    using const_view_t = any_image_view<detail::images_get_const_views_t<Images>>;
    using x_coord_t = std::ptrdiff_t;
    using y_coord_t = std::ptrdiff_t;
    using point_t = point<std::ptrdiff_t>;

    any_image() = default;
    any_image(any_image const& img) : parent_t((parent_t const&)img) {}

    template <typename Image>
    explicit any_image(Image const& img) : parent_t(img) {}

    template <typename Image>
    explicit any_image(Image& img, bool do_swap) : parent_t(img, do_swap) {}

    template <typename OtherImages>
    any_image(any_image<OtherImages> const& img)
        : parent_t((typename make_variant_over<OtherImages>::type const&)img)
    {}

    any_image& operator=(any_image const& img)
    {
        parent_t::operator=((parent_t const&)img);
        return *this;
    }

    template <typename Image>
    any_image& operator=(Image const& img)
    {
        parent_t::operator=(img);
        return *this;
    }

    template <typename OtherImages>
    any_image& operator=(any_image<OtherImages> const& img)
    {
            parent_t::operator=((typename make_variant_over<OtherImages>::type const&)img);
            return *this;
    }

    void recreate(const point_t& dims, unsigned alignment=1)
    {
        apply_operation(*this, detail::recreate_image_fnobj(dims, alignment));
    }

    void recreate(x_coord_t width, y_coord_t height, unsigned alignment=1)
    {
        recreate({ width, height }, alignment);
    }

    std::size_t num_channels() const
    {
        return apply_operation(*this, detail::any_type_get_num_channels());
    }

    point_t dimensions() const
    {
        return apply_operation(*this, detail::any_type_get_dimensions());
    }

    x_coord_t width()  const { return dimensions().x; }
    y_coord_t height() const { return dimensions().y; }
};

///@{
/// \name view, const_view
/// \brief Get an image view from a run-time instantiated image

/// \ingroup ImageModel

/// \brief Returns the non-constant-pixel view of any image. The returned view is any view.
/// \tparam Types Models ImageVectorConcept
template <typename Types>
BOOST_FORCEINLINE
auto view(any_image<Types>& img) -> typename any_image<Types>::view_t
{
    using view_t = typename any_image<Types>::view_t;
    return apply_operation(img, detail::any_image_get_view<view_t>());
}

/// \brief Returns the constant-pixel view of any image. The returned view is any view.
/// \tparam Types Models ImageVectorConcept
template <typename Types>
BOOST_FORCEINLINE
auto const_view(any_image<Types> const& img) -> typename any_image<Types>::const_view_t
{
    using view_t = typename any_image<Types>::const_view_t;
    return apply_operation(img, detail::any_image_get_const_view<view_t>());
}
///@}

}}  // namespace boost::gil

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

#endif

/* any_image.hpp
VJ02dMugtH5mANdA2Yhwv8Oc6/cW9HVXGz0ybhelYPBECX27DKDRO1BzMcoaI+THOPEf85eMsdxKvUtMnXWAsG+htsiCp0biuIqyqlLQI92cS4V/CSSWV2cD2ewAMXD8rcsEQN1KJLTVMuQSyOlOgRsbzjm7uATMVYOuyKfgXxyfYH6pZE8+eCAup9b9TtgleS5A0LpdwpDZmwt9OZjJ/JNwtBs5AyV6oCbtfOvRsb5+coxSBHqDtCxvvSLALShGKWVDquYVcso0D0ZEb4TSNoitljRojoLD1MAnj3uc1L6dzy6wPFLgg6hYve+ABoG9z+sUDoOiatzt4AqsieA3ixnJS5cfIKF8WFRv74n6F/1FDKxWfCScTg60qnX/++OR8salV3PICItdVKcD9kPNlptnz8cHlIgbFhJQkB3AvLN76RvYc0Ydzcdih3K55+BSJuafV+nbZNJ8bcHkERO1AjQdUhX/u/pszJliB27LBHFJrhxHcPsRlfrIKYB+ak/EySo2ogHfKeNDVQVAFA8B6OHIKjBDTVxCBV+z7FCadKP+ykmFBwpLtwmthg==
*/