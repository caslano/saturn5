//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_NUMERIC_SAMPLER_HPP
#define BOOST_GIL_EXTENSION_NUMERIC_SAMPLER_HPP

#include <boost/gil/extension/numeric/pixel_numeric_operations.hpp>
#include <boost/gil/extension/dynamic_image/dynamic_image_all.hpp>

namespace boost { namespace gil {

// Nearest-neighbor and bilinear image samplers.
// NOTE: The code is for example use only. It is not optimized for performance

///////////////////////////////////////////////////////////////////////////
////
////     resample_pixels: set each pixel in the destination view as the result of a sampling function over the transformed coordinates of the source view
////
///////////////////////////////////////////////////////////////////////////
/*
template <typename Sampler>
concept SamplerConcept {
    template <typename DstP,      // Models PixelConcept
              typename SrcView,    // Models RandomAccessNDImageViewConcept
              typename S_COORDS>  // Models PointNDConcept, where S_COORDS::num_dimensions == SrcView::num_dimensions
    bool sample(const Sampler& s, const SrcView& src, const S_COORDS& p, DstP result);
};
*/

/// \brief A sampler that sets the destination pixel to the closest one in the source. If outside the bounds, it doesn't change the destination
/// \ingroup ImageAlgorithms
struct nearest_neighbor_sampler {};

template <typename DstP, typename SrcView, typename F>
bool sample(nearest_neighbor_sampler, SrcView const& src, point<F> const& p, DstP& result)
{
    typename SrcView::point_t center(iround(p));
    if (center.x >= 0 && center.y >= 0 && center.x < src.width() && center.y < src.height())
    {
        result=src(center.x,center.y);
        return true;
    }
    return false;
}

struct cast_channel_fn {
    template <typename SrcChannel, typename DstChannel>
    void operator()(const SrcChannel& src, DstChannel& dst) {
        using dst_value_t = typename channel_traits<DstChannel>::value_type;
        dst = dst_value_t(src);
    }
};

template <typename SrcPixel, typename DstPixel>
void cast_pixel(const SrcPixel& src, DstPixel& dst) {
    static_for_each(src,dst,cast_channel_fn());
}

namespace detail {

template <typename Weight>
struct add_dst_mul_src_channel {
    Weight _w;
    add_dst_mul_src_channel(Weight w) : _w(w) {}

    template <typename SrcChannel, typename DstChannel>
    void operator()(const SrcChannel& src, DstChannel& dst) const {
        dst += DstChannel(src*_w);
    }
};

// dst += DST_TYPE(src * w)
template <typename SrcP,typename Weight,typename DstP>
struct add_dst_mul_src {
    void operator()(const SrcP& src, Weight weight, DstP& dst) const {
        static_for_each(src,dst, add_dst_mul_src_channel<Weight>(weight));
//        pixel_assigns_t<DstP,DstP&>()(
//            pixel_plus_t<DstP,DstP,DstP>()(
//                pixel_multiplies_scalar_t<SrcP,Weight,DstP>()(src,weight),
//                dst),
//            dst);
    }
};
} // namespace detail

/// \brief A sampler that sets the destination pixel as the bilinear interpolation of the four closest pixels from the source.
/// If outside the bounds, it doesn't change the destination
/// \ingroup ImageAlgorithms
struct bilinear_sampler {};

template <typename DstP, typename SrcView, typename F>
bool sample(bilinear_sampler, SrcView const& src, point<F> const& p, DstP& result)
{
    using SrcP = typename SrcView::value_type;
    point_t p0(ifloor(p.x), ifloor(p.y)); // the closest integer coordinate top left from p
    point<F> frac(p.x-p0.x, p.y-p0.y);

    if (p0.x < -1 || p0.y < -1 || p0.x>=src.width() || p0.y>=src.height())
    {
        return false;
    }

	pixel<F,devicen_layout_t<num_channels<SrcView>::value> > mp(0); // suboptimal
	typename SrcView::xy_locator loc=src.xy_at(p0.x,p0.y);

	if (p0.x == -1)
    {
		if (p0.y == -1)
        {
		    // the top-left corner pixel
			++loc.y();
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(loc.x()[1],  1        ,mp);
		}
        else if (p0.y+1<src.height())
        {
            // on the first column, but not the top-left nor bottom-left corner pixel
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(loc.x()[1], (1-frac.y),mp);
			++loc.y();
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(loc.x()[1],    frac.y ,mp);
		}
        else
        {
			// the bottom-left corner pixel
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(loc.x()[1],  1        ,mp);
		}
	}
    else if (p0.x+1<src.width())
    {
		if (p0.y == -1)
        {
		    // on the first row, but not the top-left nor top-right corner pixel
			++loc.y();
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(*loc,      (1-frac.x)           ,mp);
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(loc.x()[1],   frac.x            ,mp);
		}
        else if (p0.y+1<src.height())
        {
			// most common case - inside the image, not on the frist nor last row/column
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(*loc,      (1-frac.x)*(1-frac.y),mp);
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(loc.x()[1],   frac.x *(1-frac.y),mp);
			++loc.y();
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(*loc,      (1-frac.x)*   frac.y ,mp);
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(loc.x()[1],   frac.x *   frac.y ,mp);
		}
        else
        {
			// on the last row, but not the bottom-left nor bottom-right corner pixel
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(*loc,      (1-frac.x)           ,mp);
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(loc.x()[1],   frac.x            ,mp);
		}
	}
    else
    {
        if (p0.y == -1)
        {
            // the top-right corner pixel
            ++loc.y();
            detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(*loc,  1        ,mp);
        }
        else if (p0.y+1<src.height())
        {
			// on the last column, but not the top-right nor bottom-right corner pixel
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(*loc, (1-frac.y),mp);
			++loc.y();
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(*loc,    frac.y ,mp);
		}
        else
        {
			// the bottom-right corner pixel
			detail::add_dst_mul_src<SrcP,F,pixel<F,devicen_layout_t<num_channels<SrcView>::value> > >()(*loc,  1        ,mp);
		}
	}

	// Convert from floating point average value to the source type
	SrcP src_result;
	cast_pixel(mp,src_result);

	color_convert(src_result, result);
	return true;
}

}}  // namespace boost::gil

#endif

/* sampler.hpp
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
*/