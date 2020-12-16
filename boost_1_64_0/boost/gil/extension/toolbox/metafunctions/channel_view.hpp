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
bOp7dGYZ4TsCvQBPgxxlT/n9PdADv6kqRZpI7/fibQdv/o3HKGXaQt5THl4ZaAQPNnT41wbiFLg+EKWeosA5jvpdOTb9taF5/Skl4omSD33Cj5v4URTuuKNCejzI3GFmCcf/WtN8o1OEpL/BLwL2YwTsPcjB3pGnz09+Fegh7ksC7UToKwJ9m+oryNqOx4hZVfVv1J4Q1r/x8U0yuqNvUIEVJxJLi1F5OlUMxHKnjO06dmW2C5XUl/Q+kBdBrhBARB/sNwPiwpTZvortjB9zZcEGoLoGqLqOLfI1Ja7HEOMvGmPm74jxGmNQWQkDM6AuNjUnFJHdyJ82SrVkuPKzooJxJKTF5GdVg9xen1EZ0giuYmSA/NFTP9nqwXfIygD9BBBdb21F+xLRkAixGLlKzEtah1kZa3Cp27JHHlQ5R2tv1tvGDTg8nAI7rb/PeILPussJAX0opzl2rcPXFsuSpZP4Q2AgrQFxQ/VdymV/Uxrm/lhW9HJJsd7h4wqMoXCKCWn7Eocw0kX36so+fr2ceE7R32SbBP2lvQZR0i1nbBEev1+0hOfb7hHWGDln+YIa63rECg5HOQaYQyRklFBPBmVyVkzcxR1X+Diism/1L23lOBwCm/u8aEd2Cr6UEpDq6wwbQ6eQUlWctrPQ7v/FCco0wGaGhTX78yDoaNib6odYs5V4wOiuT7O3e5TfF0nNXKTzp41nL97EsdSQYlxXo8WIdDRRlQa6y4ZxPiK7jgV/ROEtAbcg9yikDiA6OAYSWRci86JPDwk1La0hYttkivCCqoSKAdsFwTpHlazqKmKebi1ItEL+BkhOwQk070gO7bE9pE7bqZFh6zr0Zy8+fLjR2Nr73CLP/cIOGl8z+0aOaB4TbtZUo5nqo3W6v329EanrI7VVbuhkx+GRWevAfHQrOrAFa1aHdYzTMOMhuIb1kbxVcGGBfRjYaKZuyTlp+o03qvwWzSh0lgzjlgFkzrLIsxBnWl3wJdNNxzH9fZyXi+Fi4f8ev7vhWsB/Ndyf8P8B1xH+ZDhvBdcL7j64QXBPwj0Dd4F+lwki/2KsraZwkqgDivjaKZqcaCfqfdX5NKiCFif+9rdVPIm61wzIER3DL9oX/xEVgo+llqIn+4nRzPPZimE+HqnLK+D6au06yM2mgaXIoG2C/WJ9foi1iyg61UEwaKimruEUXbCbGYclDP7NrLb8w4NvmSXw6/5RhCus1CeYS4WW8sQ3Wp/iM/gh+03qgsjAAPmNCtwrvxHYb/jrDPSUX5fsN1YTOX+UlB3KIRGBlorTIyENy0MiA7HlH1Ga8DQWmq8jAkf4Exk4gB8TP0T0M8h+YyKH2Fqn1uj2E/Eetp/84fDDiI1ogjoXGMk3c+4EVIRv677ZlShr2lMpGFCboGYH8Rn3FsTFeL98wjmnjwS2bpskWk9Gm1ce7XJbX6C8g6vKkyujZe/g0cbnwdGmWOTcbz93PuT+YWVOwOkbxn/dc87AuJPw87/G3uKBxbVJJbn6NLQXZd8oLsKPcqtUc4H1SjBj+llJvLBHZatpEqKmR0wOAoXOuvwrsHG0EzCaZBSiZlC1FaIoAjU9Fo6+Hc+G1iExVtlSYBNfDnivbHfylxIJP2M9yORyR/6xG1zCBwGN0eat1TIxrwbIPFjeQBHEQHpLWK7fRFuqe5Ug6NTw4WGJ/mIrvL2Ef+VUdtQMlID05v3k9c7v7gDoBhciQl4TIBZtp7kGAA/IbWSnHEPuHMNl5RUULGMA1vanebqfcr0UefYGvv+usvj4A/fpk63H1zXVv3QG7BefzhhQjBeFqzPRrSEgzIxcSn5BEEYclMeHtMXkCG/+HU4a201Hd2bvdf8wVQY=
*/