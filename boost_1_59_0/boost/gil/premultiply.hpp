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
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
*/