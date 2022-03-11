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