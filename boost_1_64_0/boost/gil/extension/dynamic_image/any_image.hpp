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
2u7uiLm5QPTluw1dUfORwqpvfTUC509xTeuE2/cxH8h4jhbNnPE3xpOsPDOnLsFfYT6QlWX23X7/Mxhrcc27m+rOx3omrjniN4+3yMM3+nbll/tWwnwg4+2MJ+Ziv3Um42N9buLg9pgPZLyWXjQoX/x8JO73+ekLnyBHZLyuA619LmA+iGuuP7nDgP2dzIK1m3r4dAByS8bz4L2mxafY40Rf7nhk9UX+hDmmuC/FuUDYLy/7Xce5QFjfkj+XxrlAjKf1spevcS4Q9ubeZxE4Fwjr3Gv6NKx1wvY1OW2Jc0GQ3v4KuZCPc5aw9b92mo45JuzS9k54/+JJxvNeuW5BdeSPzLcMmcG3yFxt8rJxv3E4zxeZX/BI7P3OZPyaP8wZYIfnBzI+x67XOP4CfSHj86HfXMvfcB4kq8CsYXBIJmqJjNdEa99F8Xi+JeM1WDXevzXO0GQ8t4vrf78TtURmy6zdzlF5WD/JnJidTE9yRU2IGP5dFroRNUHGa/7vBXe+QE2QOTJLvnXsKfI+Xh9Dt3/ejcScJuNjndvrKnLrLGzaEWMr5EFcs/nWTv2QBzIX1u7JxonTMTfJeHwxm0ORv1BxzRJlc5thrxpfvK+YFqRff3hwEONJ1pjZkNTHoRgzMldmvssOfo1xmUB1wOyrITW8sS6RVWU2eP5t5D2QrCyz7scOXsL6QlaT2cn83cXfnyezY1ZhyOse2APIyjO70epLrMnJol3su7ymiE+0Wxhd7zPUBJkNs3Gjn0zCOkFWmVlIn8kdMDdD9PdLubfiKtZysnLMFowL2oIxE+3Gzm00AXOMzIlZM+cTS5BbMiOzjMsNW2PMyCowK/X4Vl2su2S2zF4diIjGmJFVYrbvB+OXGDNhv91bOwt7I1ltZkudKt/HuEyk+3H7ugvy7kFmzWx/9bnIrRcZj6/wTB8HjAsZz9Goi6cyMVfIHJn1WdwAczpiItbBIru4u+FynN3I+Fxx7HKqLepMxNBxXPoyrD1kFZldTZh3FOcJMj5mIWs2/4haEv1slLawHcZskj5/UyseGIB9hYzX4Jbvvi6L9ZqsGrPPflyUgnEhq86s/9mAsxgXMt7PYXuPYX2JFe2uT22NWkoWfZn934rF51Yye2aP6BU8YidzYxbhHd0b8U3Wj0vm+5lLEB+ZAx+zLwKdEB8Zj32aoc8dxCfsadtJMzEfyMrzHC1bibFOJOPzr9aj0p0RHxmvXZulfisxH8iMzHaF7UE7q1C9dfv97nnsHWSuzFrX2eKCc4Fo1//INzMQOxnPQ3qbGncROxmvz9cr4oufScicmbWtPawc6pqM12CZCV/txlpAppsPEzw2I3Zxv7mtPYci9in63MY5ni6NvJPx+9lU6RyKvZGM99OhnRMskIzX2cVKLdCXMHG/in5vtmCNJOO11Pn84K+QdzKe99u721kh72Q8D+P3lRiNuhbtBp9vgvs5T9X3JT762/9irSPj9bmz3Xh3xEdWi49L1KebkFuyqszO1K0+DXVNxmvi/sTF6GcqGR+zpNfr/0J8ZDy3LX+b2hPxkdVktrtE0/6Ib5p+H9syc+Ie5I+M92Vo/xUBWMvJeOz3j67tjPyJa05/eOYB1muy6sz++eJQSazXZC7Myi3vfhDxkfE68+4Q9x1ql4zHvrNWmxDUbpjBUIfZ5TplsD94kDkz+89K15qIj4z3ZfCJdxWRPzKeh8BfvjuBuUlWg9mUc3U2IH9kfDzfTPLyxvmFjNfZuBtHYxHDdP1Yu8TWNmL+kfHYmzrWjkd9inYz2507i/okq8usf0yl88gRGa+XJTHh+Zhjot0dizsbEIPoS8Kav/G5mmGGfq9ad/qWI/ZNMn7N9/8=
*/