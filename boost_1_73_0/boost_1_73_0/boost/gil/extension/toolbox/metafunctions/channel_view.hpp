//
// Copyright 2010 Fabien Castan, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_CHANNEL_VIEW_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_CHANNEL_VIEW_HPP

#include <boost/gil/image_view_factory.hpp>

namespace boost {
namespace gil {

template <typename Channel, typename View>
struct channel_type_to_index
{
    static constexpr int value = detail::type_to_index
        <
            typename color_space_type<View>::type, // color (Boost.MP11-compatible list)
            Channel                                // channel type
        >::value;                                  // index of the channel in the color (Boost.MP11-compatible list)
};

template<typename Channel, typename View>
struct channel_view_type : kth_channel_view_type
    <
        channel_type_to_index<Channel, View>::value,
        View
    >
{
    static constexpr int index = channel_type_to_index
        <
            Channel,
            View
        >::value;

    using parent_t = kth_channel_view_type<index, View>;
    using type = typename parent_t::type;

    static type make( const View& src )
    {
        return parent_t::make( src );
    }
};

/// \ingroup ImageViewTransformationsKthChannel
template<typename Channel, typename View>
auto channel_view(View const& src)
    -> typename channel_view_type<Channel, View>::type
{
   return channel_view_type<Channel, View>::make(src);
}

}} // namespace boost::gil

#endif

/* channel_view.hpp
mYU1DRvSNhIZlgep2JhU1NgVh1TbDRkWFCBV+oiVu3BmWVhyoRqTVFC8T9Keu0pyPFphYPiJbSAb9bWFhWT9E2tTrOQghRXwpUGQ2FbAEmzjtEhsG/iTsKiYoXDiBRET8zRQxQywETCxxrEOBUaQgvHG4xBUksBSFSIq3px2+q13IHKIY971+hB0DK463TMKuKXFIjvHsY2Q+yHFefuG7R/V2J80xzxTtAABN0e7h3Cl+lLI8ct+4yvZOCvmMcbaa6aw9hUWjJ4dC12EZIPuVwsoA7PIdI399VeyJoWQm9m51GCAAtwC1NcokIQVRm5gXCX9E/6XLDacmHecjU3bwepSdWhmjbO2zSoZzakMhGPpAEXWE8Odw9yx9k3+xvKCAE9whk+iHMV5cONWpNDwE5CFSQN71zo1TnrdQRsCmnb3pIfFPAX6bU3+MA44r6Iabr3VJls7xnJhwH3HtPBE4In5Ab+3vVko7B1sVaDnMGF5p6bjeFZ2BWMuYfFe5AcsngJ4cqP33rhoX/SuPh8rnqd8avlPea7rTKlSft2+1nNLLhj6tialkSMndTxzhbhIM/mRdlfcWIRLlCsszR3X3/XAmb5CzBZbJwtfp4ojW3d59OAFd8Ls18EFM8eOIodviSIp2z3cGtpRYvj3
*/