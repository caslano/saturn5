// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename MultiGeometry, typename Policy>
struct multi_modify
{
    static inline void apply(MultiGeometry& multi)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it);
        }
    }

    template <typename Strategy>
    static inline void apply(MultiGeometry& multi, Strategy const& strategy)
    {
        typedef typename boost::range_iterator<MultiGeometry>::type iterator_type;
        for (iterator_type it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            Policy::apply(*it, strategy);
        }
    }
};


} // namespace detail
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MULTI_MODIFY_HPP

/* multi_modify.hpp
fSnq82Pvqf/3UUAC9/hYH4n6HsocPYEFbPpf6Sqgq4nPq4+CY2zmW8tJ0Z/jgiLwXnNeFHAE1YUmXks++YXyfzy1fk+0JFtHEiZmu+Dm9GP6UlOpi0YA5/QP020eloDVhl16Hed/41sU/opmLdBhZilfMQY109k3B8w4JZX+6f3dIXWFnk260M2F87gzn1THm6RiU5hqNLAJWsrIwSa5EVQFAifc4r9IUQIlObVDd9aydiiBAoYlUfPMnO5fF6h/9GG2fwS9yywLjKxNoqRhrDFedbFPmSoV6WehklzTbdqWl7yrbqqGAGAudNNtigaVuh36g7MHj8ABN+wheIe8K/OcRhVo8obYoc9wdRa3iiTSFHEUc9gVl6WFGkFU6zD6mB/Br0vHNodXAT4QXfVEARcWoXhiy4EU3bUmIEba2t15aPtEVPDGRPlidt66OAPjWR42bZStfXg6cJ9qHwLHVMu2x5HfbkcmLsWiP/SRHlTMFa2U2Dej+/704zXlh1tlxHLyTaCJBLCfeBysFjO68ANLjqkC2undU5lw97aE0rZVVzIK9kfPzq+C4g==
*/