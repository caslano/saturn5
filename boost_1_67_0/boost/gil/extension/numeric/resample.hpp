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
template <typename Sampler, typename Types1, typename V2, typename MapFn>
void resample_pixels(const any_image_view<Types1>& src, const V2& dst, const MapFn& dst_to_src, Sampler sampler=Sampler())
{
    apply_operation(src, std::bind(
        detail::resample_pixels_fn<Sampler, MapFn>(dst_to_src, sampler),
        std::placeholders::_1,
        dst));
}

/// \brief resample_pixels when the destination is run-time specified
///        If invoked on incompatible views, throws std::bad_cast()
/// \ingroup ImageAlgorithms
template <typename Sampler, typename V1, typename Types2, typename MapFn>
void resample_pixels(const V1& src, const any_image_view<Types2>& dst, const MapFn& dst_to_src, Sampler sampler=Sampler())
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
template <typename Sampler, typename SrcTypes, typename DstTypes, typename MapFn>
void resample_pixels(const any_image_view<SrcTypes>& src, const any_image_view<DstTypes>& dst, const MapFn& dst_to_src, Sampler sampler=Sampler()) {
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