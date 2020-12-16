/*
 *  Copyright Nick Thompson, 2019
 *  Use, modification and distribution are subject to the
 *  Boost Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  Exactly the same as barycentric_rational.hpp, but delivers values in $\mathbb{R}^n$.
 *  In some sense this is trivial, since each component of the vector is computed in exactly the same
 *  as would be computed by barycentric_rational.hpp. But this is a bit more efficient and convenient.
 */

#ifndef BOOST_MATH_INTERPOLATORS_VECTOR_BARYCENTRIC_RATIONAL_HPP
#define BOOST_MATH_INTERPOLATORS_VECTOR_BARYCENTRIC_RATIONAL_HPP

#include <memory>
#include <boost/math/interpolators/detail/vector_barycentric_rational_detail.hpp>

namespace boost{ namespace math{

template<class TimeContainer, class SpaceContainer>
class vector_barycentric_rational
{
public:
    using Real = typename TimeContainer::value_type;
    using Point = typename SpaceContainer::value_type;
    vector_barycentric_rational(TimeContainer&& times, SpaceContainer&& points, size_t approximation_order = 3);

    void operator()(Point& x, Real t) const;

    // I have validated using google benchmark that returning a value is no more expensive populating it,
    // at least for Eigen vectors with known size at compile-time.
    // This is kinda a weird thing to discover since it goes against the advice of basically every high-performance computing book.
    Point operator()(Real t) const {
        Point p;
        this->operator()(p, t);
        return p;
    }

    void prime(Point& dxdt, Real t) const {
        Point x;
        m_imp->eval_with_prime(x, dxdt, t);
    }

    Point prime(Real t) const {
        Point p;
        this->prime(p, t);
        return p;
    }

    void eval_with_prime(Point& x, Point& dxdt, Real t) const {
        m_imp->eval_with_prime(x, dxdt, t);
        return;
    }

    std::pair<Point, Point> eval_with_prime(Real t) const {
        Point x;
        Point dxdt;
        m_imp->eval_with_prime(x, dxdt, t);
        return {x, dxdt};
    }

private:
    std::shared_ptr<detail::vector_barycentric_rational_imp<TimeContainer, SpaceContainer>> m_imp;
};


template <class TimeContainer, class SpaceContainer>
vector_barycentric_rational<TimeContainer, SpaceContainer>::vector_barycentric_rational(TimeContainer&& times, SpaceContainer&& points, size_t approximation_order):
 m_imp(std::make_shared<detail::vector_barycentric_rational_imp<TimeContainer, SpaceContainer>>(std::move(times), std::move(points), approximation_order))
{
    return;
}

template <class TimeContainer, class SpaceContainer>
void vector_barycentric_rational<TimeContainer, SpaceContainer>::operator()(typename SpaceContainer::value_type& p, typename TimeContainer::value_type t) const
{
    m_imp->operator()(p, t);
    return;
}

}}
#endif

/* vector_barycentric_rational.hpp
y/r/Gpfs/1jdv19R81IBfRJxD3KN/4lm2tTcvY9vI2PMW9FPyRjzh2cWfPb6oiULjx2+/ozY7cu/KL81zLKuDfqv6Zkxr+aXcvAZ89bUMW8tWAHWhmkw52BZ92ItS9alWGOSNSIZA28NxsCBClSgAhWoQAUqUIEKVKAC9Z9Tf9H4n4vTy2f9/zHX+v9IlfXVmkwcCOvBzeG7/zeY8f+YieFHF7/+L/KPViFj6BAJsyd0q12ZW1hWGVlJ5zwbth9KGquY+27ai99ezjJO0n/JTmLxi82l4ncdPnsZ2UGtn5F7leQ5MZamjRRv5jnPOhXNury6+e07kLCxJYRVN/99CBp+JXnsKH4qxSwn/I2ET1V5OgvE/mUnmVQcYq1HtsQj1k77BSPHa7O4jw+FrCNDIi+qhLSom98eB0nHWtLRQ9x/Ci0j7NWEraHpOFjsM8RfXAnPwM3/GRmFz0gsIaxx85wfyM4qDJtcQthkT9g9ctcUbcuyjJyvPHG3nIHW7XY4vpQS4kvxxHeuzFDlTM+eKWmR+2QiZR9H2KvsR+0q5g6dqUZu5V3S7hrarawlxIMdpgKxS3HFmzclh/Kpi/tCTIvF/WK7C7dKrGE39j72SP7FzbTju+3qtO+hSIqZzI1nX3CrRlf7OJGjtYF0Rfz0tSqacrQoRx5hZGmdJH4+pEavNTL1Zord/XYI27HWoXaqltuTks9jQhdYtZFnkmktsG37Lt4wCWfyc6Q9DukZHew6loTDZru8X92cVoQ7hnuvbrPrWk2cOibfseF8S9vrEX+t9nnziYuQxPG47I/ZQn7cebA0DwlwnaRrNebrTHlfL898nrKcjy7sJ1qLv19Cda3Bdo79oL1f6DHcCvPcR9xaOqdaq3FtaF1nnxNtL5KW961xKncwwbxvz4qktDFWtqnT/Z6XuxL1mUhOk3Rc6YSsVfZhTn1rtlNL4q1j4si3r7NmS7zJpgxPsdpSViPIfZG20Z48S5vz1K22N++9jS0k/gTazPD4SphvT4jqtU0L9eOiC+de+1tGuWVl9SAu+suDRM5bbcv+U/cZGbsM3WdknmP2Hsn7ynuNnb7Xeq/TuWIn76bYbTF2lJ3Xn5an+w7BzjUsUS1CyHGBSfAtfqsGvWB+q9w/VN7fKSNrb/eLIjvWbmyl2XW1rl8Wu0V2OhJojrC+tSbh6rOvjWf5/r4Y2WddXw7bpWnbRE6WmEdYrbHz2ftGfGXb+4Z/39+FGvq7MF3cK4UibWyimA8z/ckzks8r7cHWdp/9cn75k3qV+J8i/pPF/Venrv42XyHxvcnHzyzrCuse7nDL99tbR7y+fb55F+4X97q+e+00rPc9Mv3GVHG3Qh3tmtZD6JOcmuL3nS6FfRFty/Q7iZLepVYPSrOulsksCT/fWYz9YHuKtdW+2krS/NV7CTdsq5K356z8IvFm5ETTf7LEm2zkAY4Qc5r5/W8m5otpz5OsGtr/Jxe2OVectKUc8qVt6WxJ1wXO9YTrR6+9mXvgmolbJL7DnArctHQiX26v8axd1kPWCrujleykudM5lShNPzpX4rzUuZk4BxFngX2V3p+ncfJNVgUpVtORhbyRd+F7SuoQO8daaR9g1XYaS7yvdYn+FtbQ/u7lwnfKuLt/xxbCVeJ+mlWPt5kykt+RHWKXIHE8TxyPi3lG0WdoG1kIN4l7XfH/djHP5B8T/xpxT+QJmPkr4r+61dW3fcTDI6W+b2J/4wlGJvKN2EXuPFzDc4eJ+XpvWzC/dwPFfRGyxKqauh4tdlf55E3Kz989I5qXutKPJJm8x4l5ore8xf8i+KvEl8B/mPkr4j9O8u5fvrXET7Kmyf8ZlqtOf5RnTOaM2oE=
*/