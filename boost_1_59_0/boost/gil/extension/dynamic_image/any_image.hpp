//
// Copyright 2005-2007 Adobe Systems Incorporated
// Copyright 2020 Samuel Debionne
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
#include <boost/variant2/variant.hpp>

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

template <typename ...Images>
class any_image : public variant2::variant<Images...>
{
    using parent_t = variant2::variant<Images...>;
public:    
    using view_t = mp11::mp_rename<detail::images_get_views_t<any_image>, any_image_view>;
    using const_view_t = mp11::mp_rename<detail::images_get_const_views_t<any_image>, any_image_view>;
    using x_coord_t = std::ptrdiff_t;
    using y_coord_t = std::ptrdiff_t;
    using point_t = point<std::ptrdiff_t>;

    any_image() = default;
    any_image(any_image const& img) : parent_t((parent_t const&)img) {}

    template <typename Image>
    explicit any_image(Image const& img) : parent_t(img) {}
    
    template <typename Image>
    any_image(Image&& img) : parent_t(std::move(img)) {}

    template <typename Image>
    explicit any_image(Image& img, bool do_swap) : parent_t(img, do_swap) {}

    template <typename ...OtherImages>
    any_image(any_image<OtherImages...> const& img)
        : parent_t((variant2::variant<OtherImages...> const&)img)
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

    template <typename ...OtherImages>
    any_image& operator=(any_image<OtherImages...> const& img)
    {
            parent_t::operator=((typename variant2::variant<OtherImages...> const&)img);
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
/// \tparam Images Models ImageVectorConcept
template <typename ...Images>
BOOST_FORCEINLINE
auto view(any_image<Images...>& img) -> typename any_image<Images...>::view_t
{
    using view_t = typename any_image<Images...>::view_t;
    return apply_operation(img, detail::any_image_get_view<view_t>());
}

/// \brief Returns the constant-pixel view of any image. The returned view is any view.
/// \tparam Types Models ImageVectorConcept
template <typename ...Images>
BOOST_FORCEINLINE
auto const_view(any_image<Images...> const& img) -> typename any_image<Images...>::const_view_t
{
    using view_t = typename any_image<Images...>::const_view_t;
    return apply_operation(img, detail::any_image_get_const_view<view_t>());
}
///@}

}}  // namespace boost::gil

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

#endif

/* any_image.hpp
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
*/