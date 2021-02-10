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
ZVO+cyxPiphsBFzDwf1qax5wPpXhY8hyIdqrVMehIuxrS93i6J/OseEo7VRdu3hZ0lIRI4GrhvAIXNsbAKFhnJsAgQ5TNyZVBdU60EhkUBXmPCLubYuEMZQPi/XdyFwr49llJalJc5a75xR/YlfwXxzTQlVQQ8k172kHIydCA/0NtxyEQHU0Cp579EhQ6ZYWlQQkRuY0isCKqTjSSqpwAIKnGFFzG2MKQs4Nd225SLgAVG8TH4UP7TjpDKSqtq92/HWdEoIMTo5efPf8O7ykzMB2/q39ov0SzVuq0uDmG0dpAs9jGeghUcKdV46tcoTiMurYLW1axZkapDRkDGC3oD1tPIF7HF/DbfRDd0G3lH4Md9R7DW1v6RdQ70kk5Esd51TondsOZBHN6K/SjsaEu+VkmgfD788vQRzon49sPAUsJ04ocA6xFkSIOJ2K4cAZy3Gxq3cd9fC2wsKCGE8B6BxafRaGLeiHDcbYlhts4Sos8IZXhLscrVBw3LHmhJsBBJin1MwOCwHRvSKIoDaKtkW/NmIx6MTUYTx0n6ro+m6/d6IsSGeR+7wxmMLj9scUyuuUcYR39nTZfp89/a8ye2P3uCTTnnSFLJhNufLnu/PBqHs8fvdxfET5akc/eEJOwXq9jKIpM29jQIHz
*/