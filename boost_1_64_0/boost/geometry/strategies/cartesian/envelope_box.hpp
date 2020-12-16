// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015-2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/detail/envelope/transform_units.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

#include <boost/geometry/strategies/cartesian/expand_box.hpp>

#include <boost/geometry/strategies/envelope.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{


template
<
    std::size_t Index,
    std::size_t Dimension,
    std::size_t DimensionCount
>
struct envelope_indexed_box
{
    template <typename BoxIn, typename BoxOut>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr)
    {
        detail::indexed_point_view<BoxIn const, Index> box_in_corner(box_in);
        detail::indexed_point_view<BoxOut, Index> mbr_corner(mbr);

        detail::conversion::point_to_point
            <
                detail::indexed_point_view<BoxIn const, Index>,
                detail::indexed_point_view<BoxOut, Index>,
                Dimension,
                DimensionCount
            >::apply(box_in_corner, mbr_corner);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


namespace strategy { namespace envelope
{


struct cartesian_box
{
    typedef cartesian_tag cs_tag;

    typedef strategy::expand::cartesian_box box_expand_strategy_type;

    static inline box_expand_strategy_type get_box_expand_strategy()
    {
        return box_expand_strategy_type();
    }

    template<typename BoxIn, typename BoxOut>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr)
    {
        geometry::detail::envelope::envelope_indexed_box
            <
                min_corner, 0, dimension<BoxIn>::value
            >::apply(box_in, mbr);

        geometry::detail::envelope::envelope_indexed_box
            <
                max_corner, 0, dimension<BoxIn>::value
            >::apply(box_in, mbr);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<box_tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian_box type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_BOX_HPP

/* envelope_box.hpp
fkn/KzgXX8VFWCXb/w18AQ/gHnxTysFb+ClWy/Y+hE2UZ7Xoh+9gNzyM/fFdHI5/xGvxPZyJRzAe30e1jwQ5N8MrZP2MfST0l/UbgPE4CB0YjAsxBO/AwXgPDsP1GIpP4HB8Bq/CSrwa38Rr8G0chZ/jGPwGw7EWx0nbz2v18iLnSrjIorysk2+jrMee+JDkewnejBsk/RsxGzdhLj6KahtROQ/CB2T+xjaid8n8l2MQ3oMzcKXMrxBvxXtle94n+VGEq3AtFuH9en0l5yMYYlFflUr5fBwH4BM41Ed5Tvezz+WYqeezN/NzN+vnbebnbNbP16yfq7mepZURRwjPZ2fG52bmZ2bmZ2Pm52LnCevnYcZnYcZnYNbPvmoJ8zOv+p93WT3rOkzUEtbPtFzPs+RZljzHMj6/Mj+7sn5uZXxmZXpWJc+pPJ9R2Qnt2dR+wvqZlPvzqPqfRRmeO8kzJ9fzpkAifOove8b088+XGvdsSZ4rac+TeP4sz5LQ6llS3c+R6n6GNJSIIhYSxmdF8oxIng95PhvSngv9gJ1uMj8HSiTcn/0cJQzPfKyf9xBlaxmX8L2f8YiZxEJiPVFBHCe8ikk7EVHs9dvPbz+//fz289vPbz+//fz28y//+dc+/89I+Gc9/9/UnutZecazvom8S4mXoA0/UJ5bbGom31wPiY2aMq4Bzyua+T+2uZn2TX6P5xfas8FD8j17W2KI/uzCQciwWB4PyrNK47iD5bmFcdzB+rgFpnGHOMctNI07RB+32DTuUPn+vnHcofq4paZxL3eOW2Ya93J93HKG9ZVxE+TeeSW6f2u/Sn/eyrNQGa9axmMY47l/p58HoIZnMXZ/ZVh6opfhuUdSB2WYnYfndT1vNT+TKWqm/F+9X+4vduTeZ9xjrm0eT2Fx8Dgk0Vb/s8bWXi2Ba4LHmd7w+/ZSeS5M2dig/jsocuKQy71k2IOuYUO1Yfe5hg3Rhq1wDRusDVvmGhaiDbvNNSxYGzZPHzZ4uDbM7hoWqg1LcQ0bpg2b5Rp2hTbsJtcwfT2iXcP09ZjgGqavxzjXMH09rnEN09cj1DVMX48QfViIvh6Xuobp6xHoGqavR0fXMH09WrqG6evRxDVMX4/ax/Rh+np87Rqmr8cJ1zB9PT5wDQv2kjqiWh823Pn7K/rvoc7fK/Tfhzl/36b/foXz91L998udv2/Qfx8qz2i1/Yay69ZmJNpX+b/S7p99FdvjCP4S9YSr3Cckx2fM5vFwij2Ztj3ZjniH+pyMfq+sfsYoM27BXHj3kmV6O9e7y/N6PThYW++/PGeuG8u8zXVjubeW7nnJKQnJzv042lAH5PBsOjFR3ecL9Tok1TZf6gE/5d62vzyvDmGZpjpEraOijOMMZjqpK4Y706HMXZ0uDN9Q2+Poz9qvVJ89xifEUs3IeKH6/FP4nfnrv89R10lPZ3q2sQ1Kttr2iUOSWl9t0qdj/ob2E3H69HavLlJ3y/wYj3qWqlGbbw0u93OmZe5gQ1sZKQtpIMcKmQfjqe2T5Lm6eb7yWFxNx1B9PqlSh7uWRVbrx6bJeh6xXWTaSled7Xy+W0zdG+WrviP+Gh8EA7fjoCN+tqHOVmK0lF8veb57vY96rB6Nnam3C3e4yq8tV2nppCSAw35sOsU3K4Wn+WoZruf4/fhutYyy+s5yfN1uvczq+/SC3W5lW46JprJscYyrdB2TTMfCZs7p0uJn2dLkWKiNl8Z4at4c0Y6tlJkMh9qwTCkPx2VcfbgyhfytRs9PZc9xTSdtq2Q6WhYZpilwzS8nK4u2bPzZnpntts8xUNYpz7V/zgVTXVMj2ypBeZ8Ix2M7ttXZPa5tRauj+DTl/yk=
*/