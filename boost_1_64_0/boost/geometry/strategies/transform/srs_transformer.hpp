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
PF+//JOSVJUS/xBqIT5Tij9k98xSTzHF1b/XI/QbybMSEaYr8WWmDB2QQ+GSsuGQFzUpefsfFoE6mygoy5yTBykRe9HHJLm3hloVEyxd5QRXP7/7a4za3P6MEf1xxcjmSxor3UGxJOmrAH4G5Zy4u8OOm0/95dUuapeEyBYKTUZp4XRrglqyWRz1ZDSuYt5jrtfWo1nNRZNWjGbMBV+vkCKM87jQstVbM/QTr8554l9kc9Pw6jJPIfTHPM8gJwTeul6fOJNrfv+scW4qI0gtEMMH7MJD+T/LDwEjscP4s9PaTg9ko6Q73uQ/a+VcYjiIPy7UVrwa3UeTVXAgTsb4wQMmb8QRtMJ5WdJc28Uo7N4zCWIQwIOIjPK4sjdcWqHYqOIkHr+fsPhVH/vVrpI1aCbr8rJkBPRkXUQPZdd9OJL6ViRwyJsTA/aviLPDBwt1xd/HFKevQ5wkk8zTv5j4J7YNDVcFgf/Q7TQGI/87k3xT1+rxAg2dMAwPn85wLs0PAftjC7GndNn2W6IsHb0q/0LRv6Zfida3YVEAFzKe5MnF1nL/61OzNn5HvA==
*/