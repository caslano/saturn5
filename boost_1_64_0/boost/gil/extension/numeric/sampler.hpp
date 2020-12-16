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
mntPFLwSrS9yFI35698GHK2sEKjZ92+mSChuWIzrWtk79o9xXpY4E/cEV+kW+4UoXc+ZYTNXGm4MQOYDZn6uQ+Y2rZVLY8Kt8H6errWPqKH9XkrjOBDMP0AjNExtgf66WOw4HVmsPboWuZVFr4T1IFogiVAVjohpBOpVY24Pz0UKvTWkN1Dz9CNAph4i9MkGhvYi9n8976umUuIJ74qUmJ1ZnuwdkvcH/ajQMquPn4ZsfNRr2gDeuWUts5xYA6yAIQzQlhmDIq1GsxHuxvusZvhcMZP+l9XPAIhJFi0Fi/N+01fhvS34doUHTDzgV42fxgBZ+/U8H+ZZyBfzrtZ/Qtg0n8znRRGoAvccqY5d9FdBdPaPwwLbbj7Gr0RHAuV0oP4wP4oSoSXKPrDUHvODnTLmRTIt+nDrKJHxUKzOPy35J45/OvJPAv94WEffzQnvaWEC/dtIh/T/UZFs+U+5Z748W7P5ABC5xibm7FKkhxVpXHUgfQGkUAzRtswTdFHG5nzYU+j3i5GjitWRzPQn8+QwRqk0IRXtUOMkpTxhcuT8dym3D0OpyzoE58tPQ135xysqRM8v5fxAThJEPbPsKFN3Pznv2HLQZHl3PP4cVcROQJ71wSKytkVowurxOwL9nObTRbJGBPEjO52x5gt443foqjAAJfHPU8sR/uKs30q91yU9NqV5DL67ol+AaW0lZTVuuWLqmnnMGT4e67NIe2Rv/Ko1Kzkr5dSZgU8UPn6Rzd7egOoBap15GsVg+rDF2rdGiLDbeBYRpoy/vlo3T4bgTjHMYMw2fKGtWiMp0fGUgxMJ3h4WRmAURJhNQAw2lYMq3D20j3DF/MMbCLIuqc/QTdAEsfkiNwjexoEU9C0zLwzytUIKV9w7RTp2Iqp/BEKiy5J54S7X1E8F2qMaE0wHZyhVwXrQlZrdxAMfegA3V/Slg1hCKf6Z32HcQ3hzd6C3M8mPboy0JHmkI8kLNXP2ZVYPtn0pXGdXUyYTqi5bJ+7qcAtm7eoP9IA3Sa9UF5itiCIYpulc9aWaDMuXbu6ELxm8OnS5qPbi7vKra0bTy7b1MDW2Sds7IIJWwRqgbMUM2miShjIOvXxfhF8xRQRYCfya3z6IZ13qxZmuaBC9pI3fdzt4MTnIqAsc9E1y72O5EOTNUQ7sC/yyS3TQ7YLF8JcdXgYvgxS6950RZg98bMxcSdgZ+lj5+avuvxbx/mtjuf/6D9WjuJDvnsH6j9+U7y6iBzud6tAwkKur/v34WQJXgFuwSYFHnPAuTcp+f6xclPVkB1gFSfSl4OcIABxA+JIZaaTcl9W7sYEVDgmIgXeJeANL9cdoQBy8C9WbAO9s9XaEa4xPjkP8OJR6id6pddcBKEepFCr+SHgz1VsN3hL15sCbq3gF+lOkP9P1Z5+ijYJjdlPh0uEycPs3O+VodsovvL6bsgsXe3G/Fx3Wy3rKTsnE3d1890F+5Lt/beukwmqxBk3JDozCN+8Nm3S/qKh6ZJDXd9FuvUJ0b1GZkM1zBNIYEF9Mon9DsEM1OV8uaR/NkY9O06+9Sld63azCjbXRDrFbgpOnbicrgruY9Sgg3b6lN9A7WsUtt7mmZcErm68pI+2TkawWLO5UMVEzAsFmNADokLCb+zmNKR0M9osmABUBOfCj3I3+Jq+LvSAS+XRAPQK9SOibCs0A9BaBXiI0ACjvhLgz4NLhUk1VTQXXRep4YNORV/ZkhMjZxNmAci35krK7hDHwu4Kx8VuHlIKfRYHyhhuBQUOjy/j1mX6tCL4SxeovlMtls8T/i/iz4E/8KoLesfBicQiOwm8WWsYZfAi+SfA58BscTHDKFGcwlR5pv6hgUthfLdg=
*/