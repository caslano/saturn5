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
Dh0ejSYnwA0mCI3EKQ7r13T5ybiZoMhQxMBpxbJok6Porp3gQm91u5lBVpc4e2/0kSSOdiT2mwlxtLBQYrjupYuhlNNnruhIWmYed1z8yt+Wc8dKDImmvg6NwzgSc+J/UOXIDyaX+z5WQD8ShVavhPuxjUO6lmEzvkSqBurInwy/VDtohnQcvpA3Zvvpz/5gPhN6VZ2UIF91v0IcAdPlqDZX2Vl4x5LxEgxPuDei57Q8iyudCxy0MtthYr7dIF+A/faghuRG5B4Z6cWSRpdKmiRw8KvM1DMACBo7qOEEvDffoOAIWVozm4+ZiuQt1KgDqQMsfpwC6TKSKzheC5MR6gKZwJ8Tu4OWWtT8ZAnHRiAjWvJZzHF+gUQSZR7Zs6MLtA4Bsd9LPaXmvb21TCugMxu7N4VLZLY9n1Yg0CNLyMXZBSdj1itOiAs10LnQWmqXDTUD8QXLV35stGsb3tcZe+MCIz+CnEQMqvkCPiNltmvIt4T7MlArLPkSordwIdT18Nm2g3yHpGmw3Sro2ks3M3PNK4nYRklNV4s2teHOw5vz0rvqfhZwfG6yWPrLVswF5jm7CQZsrHMv+rhMq8OJGi84sCjl34cP7mu+PySPjT6qrDw4ooAlZZXYU1JkKExtmg/oVzQt+vcWmp833tlIilA+uo4oXZ3e5jVMBvP3H3aXiVhnaH3vKKO0JzEt2zNedUOIy5z0WFInqV5z
*/