// Boost.Geometry

// Copyright (c) 2014-2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP
#define BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace formula_dispatch
{

template <typename ResultType, typename Geometry, typename Tag = typename tag<Geometry>::type>
struct flattening
    : not_implemented<Tag>
{};

template <typename ResultType, typename Geometry>
struct flattening<ResultType, Geometry, srs_sphere_tag>
{
    static inline ResultType apply(Geometry const& /*geometry*/)
    {
        return ResultType(0);
    }
};

template <typename ResultType, typename Geometry>
struct flattening<ResultType, Geometry, srs_spheroid_tag>
{
    static inline ResultType apply(Geometry const& geometry)
    {
        // (a - b) / a
        return ResultType(get_radius<0>(geometry) - get_radius<2>(geometry))
                    / ResultType(get_radius<0>(geometry));
    }
};

} // namespace formula_dispatch
#endif // DOXYGEN_NO_DISPATCH

#ifndef DOXYGEN_NO_DETAIL
namespace formula
{

template <typename ResultType, typename Geometry>
ResultType flattening(Geometry const& geometry)
{
    return formula_dispatch::flattening<ResultType, Geometry>::apply(geometry);
}

} // namespace formula
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_FORMULAS_FLATTENING_HPP

/* flattening.hpp
Gr9pV7W5SRZT6jAyUbN+26cMrtNp/gCnI/0+zAKw/wsJiiRkiSCzZHJm0SyMENXF5uZcKKyNRMhX6iM0RNqgZLZW5gww/h59AsZWtePziLVEcptw+9KCkSMjKxSuU1fhQ7gW8IlZAfkikcmVm56SCr7Kt1iZAdkHT9sv3tkjV2A27E2zgiWlCAOHw3IGESJNrJdun+kWtlBMz4IMEtASV2OXPCgTTUVc+U8/1+dtxWEzu8aHVFIJ9+ZuhlkRGN2z5t/e4iSxAk1TSugkqi/s1Nnr/0dURPbzq4vEJyvgSKUC1gaLem1Nzo3L9LSvXo50hBAnnFN2PoUYmls7zN1CpTrYPHTfyXLPmc8i+oGrcY8pSnswn2AQ6EtFgMF0RF7xL5yw/OYxZZB6ZQZ9OsfNUMhkG4UM7AblFs8IknYA01nns1budPKpWSHQLfBxBkxx+Y8k5DbuyMCOPj34IFTftONz6C56Sc6vw4zGHjAeEwKKZtVLR5jh/EvJCk7TVP8cHem7Xor0uopyBXFBrGvpjZ6D0rvD2rkMiJG0VOn0D8939c1AyqxjtzBnSg==
*/