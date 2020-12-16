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
ftGixnr//+O6+f83yvO6zGCeTeFC/Af/nmzT5gMdZrHlFDmsrsxsi5UkXHXoM8Jv9VX6uEzW/f4ufV7k78Vav4RwrS+I973wIcpv+xn63/t3amMElL4gX9mV523BHZS/H8/ib4krfXwNffXPyHPyU4QbO7Kti3TbuszJS7YtVofDM9kffStd9qI6vNte+q54+zAY+uy4Vjikj2U6f7+tlt8SpPV1cBn6WBr6K3i26X6ljEHnQ+rWByHwru/Au77/l971HdXVs73zh++989uBfUt6jvnt2/d+sVvpg3AkSNoracdOE7oEkZbu3cuhGIHdcAAOwUE4GYfgXByKd2AkluNo/BjH4N9wLLYkk/HYFifgEJyEUzAe52IC7sZpuA+n45s4A09hIn6LSdiMss7CKZiMN2AKLsRU7TcuaaOk7ar6G1c76VvRAcdhKM7EjpiKYfgDvAJt2AlLsQveg93xQbwKf4FX4wHsiSexF57C3ti2Ds/+A8/9A8/9L+b7mQPP/S/+c//kjTyb3xh4Jh9YAktgCSx+v//Py8lojPt/9xz7A93jWVq77yMXuceCZFgzGAaY7yoOkrH/K0KCtPcujGsm/Zba058Mr8Hx7vgj+T6qvreMwhW5uHVV75PNLwuTSJByjunAO/e4r23iGVvydbyMLSmwKffQwcZxmmn8PdYzDsAzYEMbx7ADv1Hvo/OVdZu1e2anHWVcgbquwJPeAW8f/6JFRfYl6niJXdp4CdYz5EBd36qJrGfcSmFujp1/8uQVwfrHPfmTiHw2EXtJ/pncyqtp2LT1WU7rIu+Ynpe0sjByoijfurjQqY2faRniSScjp1DZtrMyN4KM5/bEn6qlS5l1+UVSto66Mgdp447kGYuMranQ14X7EYWMES1F1mt17i5dkPzbSUM9WVfkFVpt6j6plH/Tj9lI9tY/g0GU8h001EdhVpZ8tkTb7mVsN581PBuhRq1OEtaeDbEtsv9luzci5da2myrxrHcEqceQK98hh5F7fbn2efaXe/slnS7aPi+yFxXlFBbIc6aE0co9WGyY8rd9jPG508fjjX+3iVX+flb+fk3+fkb+7jxZ+7xh3OzhZubzbURO/8/Mt8GYZHm3X/V5HhJIs8xQrsxCxwrlsVl95i8wm28i3Dt/gTz78z0Px3EpWztCcxnXOj2M/5uhL5s7rbrXl3euAOP+SW9hPu9I+IyLN+/IyRbm836UzLg4844sb1n9WEgm/smq+SuHwgWVoX9I7cfBRClXoozb30y4knAvYU4YBUqsWi7iLnJle0bg5Sy326SeptZSxnST+Uiyq85vIevD9WPnyUttJyOqtOWy7bQ50kZV2abwy8y3KWRmbdsUdcltk3r87LzM/PitnOn/eWvUMkS0rl6GVOJHJpmVIfqCytDLx1wsh1qbz51TlnTpzJ2T3MZ07hw+fPHmzvlUyjCD0F3KcgPx06uVof7XnqkNbHPUfbhOxvLPkbLNJCwgzYrqZfNeHC+wfHW5Nqp1F3a5+bxDkckXZ94hbf4jKcdaKcdqwkJ3PZmXI/pCy+HrnIttZz7/kWP2JTT/UTvz+Y8qZzfu/Efq3DujZNDcVwR5F5Hnd+Czs3W/jWZm2zNzLdxU2hnY756co2G/i0Z67ztcaHifXCvZir1kGorPYkFHjtUUXTk8twL1z/tquU6Fhcp33iy7k4tkPl/yrYs4I7tK2cLku3+BS/s3mcNHV27Zt32818OcglwL/2A85pfL9gyUeu0XpGxP+nVVt8eypNhebC+qw3uCq8xnZPiNu4uM13dKfvmS347q+XHTY89ZSgUoNRFU77kr1Ot+Zph6L+ed62ioZx0/pecbj7MXfJQvcm4=
*/