// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_TRANSFORM_INVERSE_TRANSFORMER_HPP
#define BOOST_GEOMETRY_STRATEGIES_TRANSFORM_INVERSE_TRANSFORMER_HPP

#include <boost/qvm/mat.hpp>
#include <boost/qvm/mat_operations.hpp>

#include <boost/geometry/strategies/transform/matrix_transformers.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace transform
{

/*!
\brief Transformation strategy to do an inverse transformation in a Cartesian coordinate system
\ingroup strategies
 */
template
<
    typename CalculationType,
    std::size_t Dimension1,
    std::size_t Dimension2
>
class inverse_transformer
    : public matrix_transformer<CalculationType, Dimension1, Dimension2>
{
public :
    template <typename Transformer>
    inline inverse_transformer(Transformer const& input)
    {
        this->m_matrix = boost::qvm::inverse(input.matrix());
    }

};


}} // namespace strategy::transform


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_TRANSFORM_INVERSE_TRANSFORMER_HPP

/* inverse_transformer.hpp
sbbMV5XPFcZqst1qYF2sqYw3qFyfKRPzW4xzMF3ynYVv4mxZztvYCOdhR1yAXTBBWR+57qKjxvr04XMO2FfK56e0L5RrKHrLfObtCwdIeQZieRws5fFHDxyCXhionFdyTcSuGufVIlneO1gBF2NVXCLb6V1sjEuxHS5Db1wu670Cz+bO3rNbzee01p/RyrPZ/9xzWa1nsvlm2WXruWyWZ7Kv+XlsTp/FPiW5ZeP563/Tc9fX+cxV/bxVedZqes6q+Yz19T1fVT1b/Q+048t8rlqS47chyZcUQppBSiGlkc6TnpJcGKDEbbbtuattsk22yTbZJttkm2yTbbJNtsk22ab/rulf9/5/VHBMSERQ9Gtq85/qpFP6eHSTd/L5ZB3ykpa78Dxioqk/86FhofSN6G8shO7l7+yq6goVZQxhPsi7GY1FGHrst3iPt8lKOdxM5ZC5X55/eck/vYSSvypj8jWtv512vp5m+fJ+OzY4KufrH1+avLIuQoqh7sM0ScpRQt6XOks5upvKEVvf3129IbPRJsP8nfd9K3lEqvOQhWdv2VJ+3g1pLztRvWzZEDkrf+a+2mElj22qPFRbKFvLN7UJ0F7+KdXyZcE5LHuklWXfN1+2bJ2clF2Wz3j52sexU5xh+VlP4xwcxynO+rysncbq8zjSwUp9opQj++dR+cz8C0r+6ozV628lXzclX9m4r7D+rkUkf83TWH0eDMyjvZ89lXKwmzMP0hweS5nH6R4reQSo8sjZOSbl552q9rLjVcuWDZHD8mfmEW8ljxTzPNz/3DY6byWPNFUer7aNPPNpLztdtexX20aZx3OKdh4MFG7KQ7ZQjupr98zzxcryXc2W/yr1kF9+K8e/slylmstRudtkXsPya5/nAZOUuD7/QHrwZ/k5vm+pK+e7Z1ny1FyU9et3fAHtckWayqU/KHJcppqZdVA58tNejJRHffzrCmqXJ15dnmzfU1WScrBjzcqhKoBqeyRayT9RnX+O760yt0dKKfLTXIz29aFkIe3ypKjKo9qsLy1L5vUhoIypLBp7Rj1Oj5VybDMvRw6uUZn7xbW4qQyqzC22g2th7fzTTPkrJ2hOt0NaSVMZNPaI6vjYZqUcp4zlMC6jfs7vWWpm7hMXyqK5GCmMxfni5qhdnnRVebJ/nFbKLEdh83JYrz/SrOR/X5V/zu9hMrdHupNZObJxH9O9iHZ5aABjKo/7q++feJJd5mKysX9OWSmPk6o8Od8/8YXMy2F9/wQ4WbmvVeX/6vtHJ/sn62K0z+MMK+VxU8qj1EXZruMzz2PPN6QsmtWZ+j4ioKiV789m5chuPVI+M39HJX9Vxqr1t5JvdyVfpQ7K8fqnFZX8Naux7MW357QNpXabWuttZLXb5lpvC6vd1tN6W1vttrPW2xBrt1W13nY2Vw7bhmq3bc15m9GctlHWbnOc8zESXtdYFDkdc0K7bXfO2yifN8S3n2/nFZXg03T2zI1FRs4otPutzLa28rwQ81m2MZS+s/Wuwbzys3E+0gvmi5X5omW+WPM2qi+Y722Zb7bMx8/KfN1lvhIa8z2WNpB/Qxl3U5kv8gXz3ZT5bil9TpvmS3zBfPdkvvsy3wPzNpsvmM8hF/NhHnTGvKi0XX3BfM8kv98kv9/N8rv/gvl0hvxA8rMzy88pzvp+6CL7oRPmlZ+V4+UF870h8znLfG+YHy8vmM9N5qsj87mZHy9x1tfvgGyXg+iMf0GlDfkL5tst8+2R+faazRf/gvlSZb7PZL7PzeZLecF822S+7f9k707go6juAI6HcAoIIURAQAmn4Q5JuA8TIOEKIZCIQSibTXZDQq5ls+FQ0FRBgyJGAUUEwYqKSi0=
*/