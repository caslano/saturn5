//
// Copyright 2019 Mateusz Loskot <mateusz at loskot dot net>
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DETAIL_IS_CHANNEL_INTEGRAL_HPP
#define BOOST_GIL_DETAIL_IS_CHANNEL_INTEGRAL_HPP

#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template <typename ChannelValue>
struct is_channel_integral : std::is_integral<ChannelValue> {};

template <int NumBits>
struct is_channel_integral<boost::gil::packed_channel_value<NumBits>> : std::true_type {};

template <typename BitField, int FirstBit, int NumBits, bool IsMutable>
struct is_channel_integral
    <
        boost::gil::packed_channel_reference<BitField, FirstBit, NumBits, IsMutable>
    > : std::true_type
{};

template <typename BitField, int NumBits, bool IsMutable>
struct is_channel_integral
    <
        boost::gil::packed_dynamic_channel_reference<BitField, NumBits, IsMutable>
    > : std::true_type
{};

template <typename BaseChannelValue, typename MinVal, typename MaxVal>
struct is_channel_integral
    <
        boost::gil::scoped_channel_value<BaseChannelValue, MinVal, MaxVal>
    > : std::is_integral<BaseChannelValue>
{};

}}} //namespace boost::gil::detail

#endif

/* is_channel_integral.hpp
Z8b+kzX7TJNRNzzLU3jagkDHR0Jy/lQWJEgXNhHvQWR4IP9RfuOkt7H/VWxV7QQIOMJzn3kKfCKOt4EmmiKmdoFE15w0Cw1XDmB2zPSJRE3YUYcFfXz9twEJoPpIJxUSeKuAb9vNH2SSUpYTlbsiC9ZyFd40DIYwNnxy/rIO804BwWBBej78WfnSNgND/VnL19hXhv1cxFKaIWPqhG+rFMF77dehgdHP2w1iobob+nvRCD+2Pri8277U8FP1l6uEaI3YR8MSs4R0QPnemvwCVXypmaBif8SQXYGf0A50F9ED1wvShRxqR2o6TiOjhi2W8JH+yCt0741eos38KQOc7pLkcE0uY+DbC/n0VCccapVmBVqSutr5Z7ZgYmazqO5cm8nk7lig7ObuUfnnkk+byy60RO4JjLtod8S/pzXP2T9AJ0j4q/m4E//V0HYcEmgwOdrVCzynqtnDtXuOR/eyJIWRp8ZBYzNd83442mf0jpLhiO25AnTiefZC1c8Ma6bYcGCF3Xjd9qsCTMs1Wgt+BbtOuXGcvH+JrIs6Xs4tlTJNFdp/7Cj3b3dM8Q==
*/