// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017-2017 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_IS_SELF_TURN_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_IS_SELF_TURN_HPP

#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

template <overlay_type OverlayType>
struct is_self_turn_check
{
    template <typename Turn>
    static inline bool apply(Turn const& turn)
    {
        return turn.operations[0].seg_id.source_index
                == turn.operations[1].seg_id.source_index;
    }
};

template <>
struct is_self_turn_check<overlay_buffer>
{
    template <typename Turn>
    static inline bool apply(Turn const& /*turn*/)
    {
        return false;
    }
};

template <>
struct is_self_turn_check<overlay_dissolve>
{
    template <typename Turn>
    static inline bool apply(Turn const& /*turn*/)
    {
        return false;
    }
};

template <overlay_type OverlayType, typename Turn>
bool is_self_turn(Turn const& turn)
{
    return is_self_turn_check<OverlayType>::apply(turn);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_IS_SELF_TURN_HPP

/* is_self_turn.hpp
hSTEfw9RJPJIk+DwJ0eO4O00ZS3Ik3UM//e7f1MdKALrc+pLB1rimlx9B4h8Zxt2kPc4CTYGIxP8dpt5L0edojg8ZwS0mEGDNdr5ohhjI1rnLRZaWA/muwmjcqCy8bvTyaPnGPJC6B0d0G24Gx5tYUL55tOqf1e0l8Iatg1EI/UK2/2jFXXj9Z+v3h19fWC6ujtj9KS3vxK+269JaQ+1+64Kw3/IheL54vT2upwLo2lWd4aMInVC8ckeh6e9VNgnG8hSCSwBXTdMJMMYtkMPd68kNlWXEtantePhblAkHxV0bHzwZShH7oaRRrS8S/NvvmwByzAjTuN29r71MQiTaxnj8sBTYCROdcFx22nDRY2jni9sfVuYVw8ksI5R1XcyzD4edI96Sk8SHxK/rCP5pqiGRj42m/A9kBzI1Alncu9cvS5Jz16X2jmyt4nd2Mp+80R39Poepe7ZL/2lJ7jp57+Rq/44CIbvWGWpD8PqqttIl8e1YkPbQNAUWuAz/kxor2vlRDRigRO3GvC32LI0ezTe0slyl+aSqBRtW8weiVyHL67QX2EBTRbYmVUVzTGN7zFC3CJaffinGjPSeNLewWW9zP398ufHb7cRsLMRQzv6uWXtr3UnheJ3/UjecTlkVlfkr9KMyCevuLMuqgyrUgUXrgBj4HON6JcMuatMpV2wS3/l9EGnrprHJxyq7H4yWrmn10/hmEzM+rPq
*/