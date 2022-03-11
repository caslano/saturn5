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