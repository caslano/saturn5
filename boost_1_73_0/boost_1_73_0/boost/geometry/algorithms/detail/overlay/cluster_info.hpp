// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2016 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_INFO_HPP


#include <set>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


struct cluster_info
{
    std::set<signed_size_type> turn_indices;

    //! Number of open spaces (e.g. 2 for touch)
    std::size_t open_count;

    inline cluster_info()
        : open_count(0)
    {}
};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_CLUSTER_INFO_HPP


/* cluster_info.hpp
LHrZP4bHndPWiW6auIn7yy0hhSnTbfdctY7enK3+gCfod0WkbAaJm80sLW2gaBJr1kOY83jGWKLQiWjvY4q8eJy+j2q2XaVOSLXRoD6acurtDj+ol6rXDw1z1CWEA5sB7YsZv9QhzMibeRdBGGQ3elPhKQpvKYMSWoUHeYGdb2ES4ovMg98eiCQpUXgWmYCPjCm4IJ3P8AQS2bfqJfBTh1OVe6ZZQN3XJ2vxEYzuHrgpyCEw8fimLc0st7VlqTVEV2dk3+jBhg4NeJpEstPwtHuqZAzxMYqv+ehtS0xVQEQqbnzrQN9ubZ7S2Uy+MTpGCn0v0VKD1ZygSnZzeNJj1uVAiT3mj9McHhiZxSBnDnNQV4Eh1JueT8tlk7cWe1w6ZhO1P9e4Fm9Hps9cJ2ebadg2Yq7zxfcJSTEweSW7RJFJPQN4MkxCD52H8LGaPH5bAfl1T1/II1edPeo1LMCvj//drVG1lJpNrLiQqvwfsYxyNYb2Sp7xt/Ruy2W3eG8H0uWLpvEK/Snynky3JVgl5I9c0dNQuR8Nozi6CGM6F3VW/bjT6w/63cO/tQe38m3lP08UcUtD6aTuIo6UYUt4NmGQEUSUrFxAMquIsbznetWSsnuyLX23+ZOL/SUMykxKw5auvzpmU8xcjjp5
*/