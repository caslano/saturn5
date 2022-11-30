// Boost.Geometry

// Copyright (c) 2021, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_DETAIL_ANY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_DETAIL_ANY_HPP


#include <utility>

#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/util/type_traits_std.hpp>


namespace boost { namespace geometry
{

namespace detail
{

template
<
    typename CastPolicy,
    typename TypeSequence,
    std::size_t N = util::sequence_size<TypeSequence>::value
>
struct visit_any
{
    static const std::size_t M = N / 2;

    template <std::size_t Offset, typename Function, typename Any>
    static bool apply(Function && function, Any && any)
    {
        return visit_any<CastPolicy, TypeSequence, M>::template apply<Offset>(
                    std::forward<Function>(function), std::forward<Any>(any))
            || visit_any<CastPolicy, TypeSequence, N - M>::template apply<Offset + M>(
                    std::forward<Function>(function), std::forward<Any>(any));
    }
};

template <typename CastPolicy, typename TypeSequence>
struct visit_any<CastPolicy, TypeSequence, 1>
{
    template <std::size_t Offset, typename Function, typename Any>
    static bool apply(Function && function, Any && any)
    {
        using elem_t = typename util::sequence_element<Offset, TypeSequence>::type;
        using geom_t = util::transcribe_const_t<std::remove_reference_t<Any>, elem_t>;
        geom_t * g = CastPolicy::template apply<geom_t>(&any);
        if (g != nullptr)
        {
            using geom_ref_t = std::conditional_t
                <
                    std::is_rvalue_reference<decltype(any)>::value,
                    geom_t&&, geom_t&
                >;
            function(static_cast<geom_ref_t>(*g));
            return true;
        }
        else
        {
            return false;
        }
    }
};

template <typename CastPolicy, typename TypeSequence>
struct visit_any<CastPolicy, TypeSequence, 0>
{
    template <std::size_t Offset, typename Function, typename Any>
    static bool apply(Function &&, Any &&)
    {
        return false;
    }
};

} // namespace detail

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_DETAIL_ANY_HPP

/* any.hpp
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
*/