//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_SIMILAR_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_SIMILAR_HPP

#include <boost/gil/channel.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_similar metafunctions
/// \brief Determines if two pixel types are similar.

template<typename A, typename B>
struct is_similar : std::false_type {};

template<typename A>
struct is_similar<A, A> : std::true_type {};

template<typename B,int I, int S, bool M, int I2>
struct is_similar
    <
        packed_channel_reference<B,  I, S, M>,
        packed_channel_reference<B, I2, S, M>
    > : std::true_type {};

}} // namespace boost::gil

#endif

/* is_similar.hpp
wkJXoqw366YNNXnqRPjwZ9wGrcncpjWYgyCd/lyCZe6XGRHh6kJj5M6i7QXJR+peAVhNHb50hD8HZbLueNoQqTnmDRbP490MfhIiOy5XmKGqzG6+KoMNb/mvmWaRiqzfYPnm30o957GdDPVysys/o3mzWML54gJbsTxWW8kVl/E71nDpApaSwZKS3rfYEEV+DUk8mN8Qsp3gCUPwYVwdouN7eZQtz29EVVo71BCwshSbC2xE/6NK8WRqV9jAkM3b935QXWvv33WtbF3r36Wmn1Nq2vu/Vmr6n6jy7P0/7sfYm9uPcX6xc35x3wQ1DX3scJA3l/Zj4Ig7+CWNuwiPOF29/2PvEL+Sd8piLcTbp1YQvdCkoc/Hqx5Qwakv/elH/rRgvGwbxyHVnhYU0nII+6WrWwdNAV79rTmnwLWC/Xxfy0eq+FW69oW9p840QCUZj/N44hYeE1MP89h+5KMtCtfFuxNGfMwyFRZJ1I2KiCZ3RMGruV/E64Ixc60t4F8MgQHkXkrcxteCJhiUwX1TQopOmLhKQz2Z8rgQD+6WHoSrh+TZ30Xf5yv2vnXeb1M5EUfDNObLh15/0G1dtI2L1j/VMV+lki05opfPXtOListKgoi/oFCYrSnmK41IYHFREoWJNv4G3bM1Capi
*/