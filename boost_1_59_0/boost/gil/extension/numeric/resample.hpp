//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_NUMERIC_RESAMPLE_HPP
#define BOOST_GIL_EXTENSION_NUMERIC_RESAMPLE_HPP

#include <boost/gil/extension/numeric/affine.hpp>
#include <boost/gil/extension/dynamic_image/dynamic_image_all.hpp>

#include <algorithm>
#include <functional>

namespace boost { namespace gil {

// Support for generic image resampling
// NOTE: The code is for example use only. It is not optimized for performance

///////////////////////////////////////////////////////////////////////////
////
////   resample_pixels: set each pixel in the destination view as the result of a sampling function over the transformed coordinates of the source view
////
///////////////////////////////////////////////////////////////////////////

template <typename MapFn> struct mapping_traits {};

/// \brief Set each pixel in the destination view as the result of a sampling function over the transformed coordinates of the source view
/// \ingroup ImageAlgorithms
///
/// The provided implementation works for 2D image views only
template <typename Sampler,        // Models SamplerConcept
          typename SrcView,        // Models RandomAccess2DImageViewConcept
          typename DstView,        // Models MutableRandomAccess2DImageViewConcept
          typename MapFn>        // Models MappingFunctionConcept
void resample_pixels(const SrcView& src_view, const DstView& dst_view, const MapFn& dst_to_src, Sampler sampler=Sampler())
{
    typename DstView::point_t dst_dims=dst_view.dimensions();
    typename DstView::point_t dst_p;

    for (dst_p.y=0; dst_p.y<dst_dims.y; ++dst_p.y) {
        typename DstView::x_iterator xit = dst_view.row_begin(dst_p.y);
        for (dst_p.x=0; dst_p.x<dst_dims.x; ++dst_p.x) {
            sample(sampler, src_view, transform(dst_to_src, dst_p), xit[dst_p.x]);
        }
    }
}

///////////////////////////////////////////////////////////////////////////
////
////   resample_pixels when one or both image views are run-time instantiated.
////
///////////////////////////////////////////////////////////////////////////

namespace detail {
    template <typename Sampler, typename MapFn>
    struct resample_pixels_fn : public binary_operation_obj<resample_pixels_fn<Sampler,MapFn> > {
        MapFn  _dst_to_src;
        Sampler _sampler;
        resample_pixels_fn(const MapFn& dst_to_src, const Sampler& sampler) : _dst_to_src(dst_to_src), _sampler(sampler) {}

        template <typename SrcView, typename DstView> BOOST_FORCEINLINE void apply_compatible(const SrcView& src, const DstView& dst)  const {
            resample_pixels(src, dst, _dst_to_src, _sampler);
        }
    };
}

/// \brief resample_pixels when the source is run-time specified
///        If invoked on incompatible views, throws std::bad_cast()
/// \ingroup ImageAlgorithms
template <typename Sampler, typename ...Types1, typename V2, typename MapFn>
void resample_pixels(const any_image_view<Types1...>& src, const V2& dst, const MapFn& dst_to_src, Sampler sampler=Sampler())
{
    apply_operation(src, std::bind(
        detail::resample_pixels_fn<Sampler, MapFn>(dst_to_src, sampler),
        std::placeholders::_1,
        dst));
}

/// \brief resample_pixels when the destination is run-time specified
///        If invoked on incompatible views, throws std::bad_cast()
/// \ingroup ImageAlgorithms
template <typename Sampler, typename V1, typename ...Types2, typename MapFn>
void resample_pixels(const V1& src, const any_image_view<Types2...>& dst, const MapFn& dst_to_src, Sampler sampler=Sampler())
{
    using namespace std::placeholders;
    apply_operation(dst, std::bind(
        detail::resample_pixels_fn<Sampler, MapFn>(dst_to_src, sampler),
        src,
        std::placeholders::_1));
}

/// \brief resample_pixels when both the source and the destination are run-time specified
///        If invoked on incompatible views, throws std::bad_cast()
/// \ingroup ImageAlgorithms
template <typename Sampler, typename ...SrcTypes, typename ...DstTypes, typename MapFn>
void resample_pixels(const any_image_view<SrcTypes...>& src, const any_image_view<DstTypes...>& dst, const MapFn& dst_to_src, Sampler sampler=Sampler()) {
    apply_operation(src,dst,detail::resample_pixels_fn<Sampler,MapFn>(dst_to_src,sampler));
}

///////////////////////////////////////////////////////////////////////////
////
////   resample_subimage: copy into the destination a rotated rectangular region from the source, rescaling it to fit into the destination
////
///////////////////////////////////////////////////////////////////////////

// Extract into dst the rotated bounds [src_min..src_max] rotated at 'angle' from the source view 'src'
// The source coordinates are in the coordinate space of the source image
// Note that the views could also be variants (i.e. any_image_view)
template <typename Sampler, typename SrcMetaView, typename DstMetaView>
void resample_subimage(const SrcMetaView& src, const DstMetaView& dst,
                         double src_min_x, double src_min_y,
                         double src_max_x, double src_max_y,
                         double angle, const Sampler& sampler=Sampler()) {
    double src_width  = std::max<double>(src_max_x - src_min_x - 1,1);
    double src_height = std::max<double>(src_max_y - src_min_y - 1,1);
    double dst_width  = std::max<double>((double)(dst.width()-1),1);
    double dst_height = std::max<double>((double)(dst.height()-1),1);

    matrix3x2<double> mat =
        matrix3x2<double>::get_translate(-dst_width/2.0, -dst_height/2.0) *
        matrix3x2<double>::get_scale(src_width / dst_width, src_height / dst_height)*
        matrix3x2<double>::get_rotate(-angle)*
        matrix3x2<double>::get_translate(src_min_x + src_width/2.0, src_min_y + src_height/2.0);
    resample_pixels(src,dst,mat,sampler);
}

///////////////////////////////////////////////////////////////////////////
////
////   resize_view: Copy the source view into the destination, scaling to fit
////
///////////////////////////////////////////////////////////////////////////

template <typename Sampler, typename SrcMetaView, typename DstMetaView>
void resize_view(const SrcMetaView& src, const DstMetaView& dst, const Sampler& sampler=Sampler()) {
    resample_subimage(src,dst,0.0,0.0,(double)src.width(),(double)src.height(),0.0,sampler);
}

} }  // namespace boost::gil

#endif // BOOST_GIL_EXTENSION_NUMERIC_RESAMPLE_HPP

/* resample.hpp
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
*/