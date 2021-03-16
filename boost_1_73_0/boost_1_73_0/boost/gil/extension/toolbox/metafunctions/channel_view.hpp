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
e9tW37JeXktT26r50BGfdlrC2/XhZrWb7FB58rZ8LFEEL0JyN2bHN519XgP/6y2ObzM5x+cLOpfNFcS9ZF5QGS6ZXLGxcjrj55iImT1izPa5I+yptta1FLR6wLpl4dCWUT0Klo0sYCxcNrKQsXjZyGLGzstGdmasWDayovYNVDzqbXt3n3nEsrztnbkqUMoo63p3m5atLevYao5mqzmOreYksZoTYTdPY8tJP/RfWVBWlgrTHfLyC/YIMmX/H38=
*/