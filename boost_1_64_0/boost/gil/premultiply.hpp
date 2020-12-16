//
// Copyright 2014 Bill Gallafent
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_PREMULTIPLY_HPP
#define BOOST_GIL_PREMULTIPLY_HPP

#include <boost/gil/rgba.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/core/ignore_unused.hpp>

#include <type_traits>

namespace boost { namespace gil {

template <typename SrcP, typename DstP>
struct channel_premultiply
{
    channel_premultiply(SrcP const & src, DstP & dst)
        : src_(src), dst_(dst)
    {}

    template <typename Channel>
    void operator()(Channel /* channel */) const
    {
        // TODO: Explain why 'channel' input paramater is not used, or used as tag only.

        // @todo: need to do a "channel_convert" too, in case the channel types aren't the same?
        get_color(dst_, Channel()) = channel_multiply(get_color(src_,Channel()), alpha_or_max(src_));
    }
    SrcP const & src_;
    DstP & dst_;
};

namespace detail
{
    template <typename SrcP, typename DstP>
    void assign_alpha_if(std::true_type, SrcP const &src, DstP &dst)
    {
        get_color(dst,alpha_t()) = alpha_or_max(src);
    }

    template <typename SrcP, typename DstP>
    void assign_alpha_if(std::false_type, SrcP const& src, DstP& dst)
    {
        // nothing to do
        boost::ignore_unused(src);
        boost::ignore_unused(dst);
    }
}

struct premultiply
{
    template <typename SrcP, typename DstP>
    void operator()(const SrcP& src, DstP& dst) const
    {
        using src_colour_space_t = typename color_space_type<SrcP>::type;
        using dst_colour_space_t = typename color_space_type<DstP>::type;
        using src_colour_channels = mp11::mp_remove<src_colour_space_t, alpha_t>;

        using has_alpha_t = std::integral_constant<bool, mp11::mp_contains<dst_colour_space_t, alpha_t>::value>;
        mp11::mp_for_each<src_colour_channels>(channel_premultiply<SrcP, DstP>(src, dst));
        detail::assign_alpha_if(has_alpha_t(), src, dst);
    }
};

template <typename SrcConstRefP,  // const reference to the source pixel
          typename DstP>          // Destination pixel value (models PixelValueConcept)
class premultiply_deref_fn
{
public:
    using const_t = premultiply_deref_fn<SrcConstRefP, DstP>;
    using value_type = DstP;
    using reference = value_type;      // read-only dereferencing
    using const_reference = const value_type &;
    using argument_type = SrcConstRefP;
    using result_type = reference;
    static constexpr bool is_mutable = false;

    result_type operator()(argument_type srcP) const
    {
        result_type dstP;
        premultiply()(srcP,dstP);
        return dstP;
    }
};

template <typename SrcView, typename DstP>
struct premultiplied_view_type
{
private:
    using src_pix_ref = typename SrcView::const_t::reference;  // const reference to pixel in SrcView
    using deref_t = premultiply_deref_fn<src_pix_ref, DstP>; // the dereference adaptor that performs color conversion
    using add_ref_t = typename SrcView::template add_deref<deref_t>;
public:
    using type = typename add_ref_t::type; // the color converted view type
    static type make(const SrcView& sv) { return add_ref_t::make(sv, deref_t()); }
};

template <typename DstP, typename View> inline
typename premultiplied_view_type<View,DstP>::type premultiply_view(const View& src)
{
    return premultiplied_view_type<View,DstP>::make(src);
}

}} // namespace boost::gil

#endif

/* premultiply.hpp
gRha/9N14BjvmcCPIf9Zb9golPTFve/RuwrHPY7LtqxK7NqLqNzPKniN+3wuaKW20Erml6Umxa93j/J0f037/iIaGy/EjpoMzOjM+91ti4vy/IK/yfxI8NB4psWK9/1UMjF51y6oNpMaszTMs8IvdR/8vtom2V/gVrinI9xYyBGkfEpcdi3+Rk31g8/29ZJPnuw8fta6FzhXeJRqcm8TjDXeUAnTC7bu7Atugp1y1dZtxZOsbery1ENPBZ5tf6FtD1h771m04DXm/4p/7jX2D0CiQfFIh9Z5PFLZQCvGUHk7fbkXGbt0WMBG8PaD1bS1sBjUo/I9aYXDnmhhf0fa2HyAXXPQM4L3BHydIXseDkqCX3XwxEvF4Z9SmxiiOVRDZKgbczMMsC8UfDcZ3OKz2nZtxd0emmA3RL8tPJLqCFIyQfI8wPN16XOIsJccD5ddXvo1G/pF62L8zkviO20Zg7RNCjDjLhC9f69w+MqDm2uGULnKhRnZiGdlF19XebZ8aPshDrxex1ibeIS9NfkwrWs/lSipwJ7DHY44VxVM6lp/Xpf3VN7CHp373ZdBo9g/P+/8ofF3x4G+H/Baod7Ea1u1Mu6m6b+QH9cmx39qW0Gwy+LG48W3FuRPf1rJslVtWiw57znDJeTLDCNsLXkc92khlKg0QOQlfx0cbS+ntQ2hqoyJENDRyWsHUqP1dVrWvArgIAnVzUl7guTuwN/bxTjUVZNVNU7O0Mo4DvbmAfZ9AjbG22sCB6kzDHR2M/lbS15qOMvEtY1ZhS+SUc8CVMv2tPTRDhDkHWJd7QB6Y42JXcyP96enpU9520bGPmGGnYz4nO740mfBuWfy70CoDFJQmsxVIXTfPOyn67z/441fQhpEOL5xSh/t8QH+z/IbUOsMbu5Ig721I1FI1pT8N1XlR7hCzuOeIMVSf/PsjKBRoN4VjhH4NKxfNAfhHDoj6MSNibMKISHI/q8IsT3CcZ5mxThMCVTZbmsu1PnNYSsPr4VJGsMl8fmdpaSGY5X8bk9+Qxm1sbHlckMtEzJ+DMd5CvzaAsimWN+bLL/pwM8LJT+QgKB8ojSz9pt71LAmOPyTkdC5KSpEMEFLUHvsjNxj8ANLrVj6nO6wyZESIqHrnWrRyW9tUphhigybzIoDoW+QnmPp3L8qcRCXb5ocm61HmRMK5ZqT8AkWRG2idqBBTPE18SOJk4fwZq7qcCBydgrnl2dUDEcTocKUm2b1LZT/XuJkeQ3dCO6ZvRWNfQ3DuSFx8syEJowMEaIPYjj/kji2jHKR1i3ROTuBc/sNuS/ipC5K407cA8btJomT2yIGcJ4lJDPxPUckTtPiJm/LyuOnod5/xznO0/IAoxblEaoqzS2KXL93fjFfv02eQBrC0QnTu5TJbjrP4I41WYLjr/emfPWq5jnjsK0NOYrbFu9Jz+lV2OdyAYTqDnMcA9UbIn0dQh+2DuGJqzWxkLxvnxcyVJ6UNnAuINGM8j1xuNoLkXA48O3dz6yQ2g59+byy4aQ2A2rWug1rIBBtQsI4o2uCXRN4tYdxQmn3BgXddk+SeNLunJzwUfvVsId/yfs4nsMkkKZ5iSl/jpD1Tg7wv+fwFe6CAqukTnFnShSqEXFe12suYSqG383zOjtx1YlBikO+Fm6/w8c9wfNoE8KHzmyy3G0k93PYp1VWvaowiifJ/M/lfgFbwoJfIIlOB4tYPQn7eMFDWmIvNbCwtTQjVn8Z+r3HbHab2dra1vn5Wl8m9fwcP7dD+xHVvtMDtI9y+lPW60/hWhm/yNpikHu5lyrWrIQx8+7v4BoOd/bC5uZstvYw1/birg1PIq4yA3JeRFkfMD1rhn27o3Ka19A=
*/