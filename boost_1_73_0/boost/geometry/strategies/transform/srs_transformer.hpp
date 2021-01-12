// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_TRANSFORM_SRS_TRANSFORMER_HPP
#define BOOST_GEOMETRY_STRATEGIES_TRANSFORM_SRS_TRANSFORMER_HPP


namespace boost { namespace geometry
{
    
namespace strategy { namespace transform
{

/*!
    \brief Transformation strategy to do transform using a forward
           Map Projection or SRS transformation.
    \ingroup transform
    \tparam ProjectionOrTransformation SRS projection or transformation type
 */
template
<
    typename ProjectionOrTransformation
>
class srs_forward_transformer
{
public:
    inline srs_forward_transformer()
    {}

    template <typename Parameters>
    inline srs_forward_transformer(Parameters const& parameters)
        : m_proj_or_transform(parameters)
    {}

    template <typename Parameters1, typename Parameters2>
    inline srs_forward_transformer(Parameters1 const& parameters1, Parameters2 const& parameters2)
        : m_proj_or_transform(parameters1, parameters2)
    {}

    template <typename Geometry1, typename Geometry2>
    inline bool apply(Geometry1 const& g1, Geometry2 & g2) const
    {
        return m_proj_or_transform.forward(g1, g2);
    }

private:
    ProjectionOrTransformation m_proj_or_transform;
};


/*!
    \brief Transformation strategy to do transform using an inverse
           Map Projection or SRS transformation.
    \ingroup transform
    \tparam ProjectionOrTransformation SRS projection or transformation type
 */
template
<
    typename ProjectionOrTransformation
>
class srs_inverse_transformer
{
public:
    inline srs_inverse_transformer()
    {}

    template <typename Parameters>
    inline srs_inverse_transformer(Parameters const& parameters)
        : m_proj_or_transform(parameters)
    {}

    template <typename Parameters1, typename Parameters2>
    inline srs_inverse_transformer(Parameters1 const& parameters1, Parameters2 const& parameters2)
        : m_proj_or_transform(parameters1, parameters2)
    {}

    template <typename Geometry1, typename Geometry2>
    inline bool apply(Geometry1 const& g1, Geometry2 & g2) const
    {
        return m_proj_or_transform.inverse(g1, g2);
    }

private:
    ProjectionOrTransformation m_proj_or_transform;
};


}} // namespace strategy::transform

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_TRANSFORM_SRS_TRANSFORMER_HPP

/* srs_transformer.hpp
mwM5UIUTG4X2nLHotCfvIjqJ3/0olzp9MH99aY58t9VllIhQ87zI29gqH045n8Ibz1F7VAxxhlXmtq7lkHQZUU+6HFEDXY5SunykTpf1tEvr0Oc5MuuM9a7z5EvLZyq8eX7r8m60RrOy7ixFe2M0eUe5Q/ORfjQfVcP70ep9vzqNrv3rAtuiZyt5FKN0cKyi6zj/7wagV8odmk8M1ds58wtYF+0nE5PUGMY6MlFrr9HlygD2
*/