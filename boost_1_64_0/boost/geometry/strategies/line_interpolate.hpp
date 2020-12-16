// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP
#define BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace line_interpolate
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::line_interpolate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_LINE_INTERPOLATE_HPP

/* line_interpolate.hpp
Li09iVHDtWmWLHqtZtXEEytyC2qOFU0c0St0l8mR7uCtKNxopUS7gJjm1UqoVB/egmmUV8e2JepAS7cBX0gcMaqEUyFb+HX/hAM+jajaISka6XaS3ipW6a/QXgVbA/BUEtsnIblhMb5cA9jCJysiagoRIBHhl4dquGoz0WDx5V1BBj4/zS6P0lPn01S5ULCkdEmqyRYQWtfho5VW7UutViMWcrdyWe9EdHlMRqW00XALTyHo8rSINtotFjAcoCTlK1VxDFbVOz0eUps/exnhQD3fIO7IaBS6Y1Fv5Fy8miwvlCK0cctUNVZ5EtN2wxkMF5+EAwdrNh5q45XWxCN9XSmLKpdpbgVufbzoaEQXT2tF37xMjCPuIBe/tlg53yYpERTEKZ6DR74E8RbdFF4rxBfgwTzReMLSS4+lxoMVQI6GpCoPXqsummvhxSQywv8i96ouXrJPSQ5liXnb+5DQY91cofM+TOKO9PS+R+Pz3tZ4b0JHfCqH3xJlZmw6Qhm3xVYwbpD8KFLwc4FOudLkPonbC08jbR+LziEkJX1penxoLdaUWGp0m55YJnoh6G4p7fZx/3Xvb3dVyabD/ezgxUv1ZsuPl92/ai9IZ/8aj8wxeYUHWWY5sfslU0EuWrb+I1msVF2J5kAdFIuVq0wLlzQxYHcY+Jh46GZ3f6nxo5KfgnrdhWj0MFePdAofvhp7d5TCJ0PKLq99O2aFLl4tumTjZbdTpIXOGja6ibaI98PPC5dDuoInpx17hdJ+XWlmYJ/Pa56nn1vLjZBtZV0v4/kkyY9PfW1ScOg0LzYLZD5a9o4uJ2Qk6eZYuwstOhjmZFPUrtKS1fTh07pPnQl0F59w5PvHIf9efOpto//IU6o0YyLLYcqjk5QX158wmYxFRE8Qhw4cqFQvmE3RmT5VIJ1ulQ9dvUHGB/HsmwXAY5XJVjtzYdcD088sn3Dt8ga+5s9lyRT86jTpL0ZCPGNRr7h5ZPbtA21zn7e+2q6F9R84QdfL7g1iWfMr22Sxin6BWbtM7t4Cm/G8SCd4jQh+HvLo48aLXQ+mJ5fjRmI/4ciVLk8CQ/LckJdtYqMe7Ra2JcbFdweQ8a27UF48DDDPK5Js7GksfHS38pp48FuFxOYopJ3zmg65zpt6nHx8uO9m8uFrL3diV8X+/rDfKaXpYJOmh9TGw5rl6mvg8UIOh2Jmef1OpgRPuYulJ9Hqnmw6gjmTjrDP4GAnoUzjJXen3PJKuhskeUrssvE1+zrUq2V9hMQjh527Uq9d6KEZWfT8NrJN3kvf/w4uDny2kt40++nQHVKn62gFjCPtUc8ur7tK41nVuXj+LsG7yWhilY1mh67FYNNLbGSTzjJMd/i2xHXIykoHPM2Ei29bdtCD8BVLO6VRaURV0hC28xz1oFzaj62UF3m8iGy7VcaP7ljrO7bz2O4EeI9aqMZW+ojaNVsORPn00SfwjLVqwSpPm7XREdaLqfLcJXZ5a43A7wZZh1Oab2y/Sc8rvYV8lGcHtNhvNoTiBCCFR0N0USMagbfzmSdHGp8ZZ51NRly0YuNrv1UaT2jPQiNZb409gljMtAibeHAbXKJOsDe7CNbiIizXutiTiqOepD+r9aLaeIlxgOz58f3tJVcemWpgQ+erRUkpJWlHmnIixsYp71c6DjrqhS7ocQcbl+KLiY/t0hJ5yZPCoOynm2UX0zKDhQNKwPZ623S67mg5sLy454WaTo87xzg5A1RHcO2aGJkKrY7PAINeulntVDqBuozaJ3x2PMwOna47Sw4+6wAHj4Y8ks694JSHMVmjlsldlKODNT4cRioN0jgKDWkMkqP12OA/ps1Wl+EOYJTQmxKrvBIUqZg=
*/