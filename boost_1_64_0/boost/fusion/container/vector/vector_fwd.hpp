/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_FORWARD_11052014_1626
#define FUSION_VECTOR_FORWARD_11052014_1626

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/vector/detail/cpp03/vector_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

namespace boost { namespace fusion
{
    template <typename ...T>
    struct vector;

#define FUSION_VECTOR_N_ALIASES(z, N, d)                                    \
    template <typename ...T>                                                \
    using BOOST_PP_CAT(vector, N) = vector<T...>;

    BOOST_PP_REPEAT(51, FUSION_VECTOR_N_ALIASES, ~)

#undef FUSION_VECTOR_N_ALIASES
}}

#endif
#endif


/* vector_fwd.hpp
M5NRdd6+mnlsuLo9VcZ9I9t53GR/y7FRa5+dMe4zmR+JD6rp8QdbXpqzpu7xiqxDZku7CHStR00xROpKZ7aUfWVLcb2ovhVtY1ZRF/RFf+V5PfPlWIzQ9qtDa1tCOhK3Jp1iHKnWk7NP1HS6G/arsZ44Quq+35U2Jm8RFikVP99y7aeCeVkOW0pBbl9m+/w+bdkXjpp6YVTzr22/Q8sXjQWcKTz6Nr43n5my/VEeY1dwrGr7ar6Uh/vvxWnZKQUF7v0Uo5U7xSHbXtMX0v86VfM6Se91jOZ1ld7rVM3rlv2vKzavY/ReF21eV+mtT+KXV7ds3mfTe52weR27/3XR3up+vz9KmT867sURtgf+sabNrt6LPnEOLPTWt9H/uuKnHMr8JicLtjQ58rMfdmnyi5lJ6T9pTb1dY2X+q+8m/mZ/dofL/9xSGfeTbkeoEPura37Vx9O7PJ584NaVt73ZIOTzZ06odcXJDeQ7Uo5lB+Fu/p8gdWUZMhbvHIzBTIzDeTgec3Am5mIq5mE2OtCJ83Ex5uNmLMA30YnvYSGexyK8gguxG2kvwghcjMOwBG24BEtwKT6OD2M1lvLvBC7DM7gcf44r8BdYhg2kTqo5rsIgXI134xrshWtxKK7D4bgeZ+EGzMaNmIubsQDLcTFuwS34KG7HrViJ29x9CRvId5Z8lynl3EMblwilLnUQDsLBUs5D0IqxmIhDMRmHYSYORwfG4SIcgatxJG7FUfgkxuMzOBqfxzF4Csfi93AcvoPjZb9MwAs4Ef+JVmwife5a4GTsiFOwBybgYHwIR+BUnI3TMBUTcTFOx4dxBlbgTNyOSfgizsKTOBu/jzZ8G5O19+HKd4p81zgM78MNkzr8jng3huMk7IKzsSumYjcswO64AHvgUrwTH8W78CRG4Bm8G9/Cnsh4Nj69j/V4Xu13siY5PPsYORzEMfQzajSf+j6Cu84ymHeWxvKZustafY7s8733O9rA3/YRzhKkDxInIssSivl/d/RWxxmfX1PPWZLv2S+pks/HCecJXxBiCsg7wd1XKZb8fsbydqzg85oCz35LVQWkxd+M/ZfaOdU601i0E/R9mUr4XEEw9mk6xLxr+CYa61WvOM37N4UV1vRxOkU+3PWtduafxxLcSjhEaDeUdaPa74lQVNP3KYb/JxHc9bJl/H87wV0/e7qINFi/1NNSoV67X1S7S41q1d3GMy+GZRMIV5hXhu5+UtsX1O4rdW6BWr97FSOGM78Y+dwbjfW9CcX+9Z2qYPnzhKsEfR+qdgvVOmEruvtS2Req9cNbF9avT9VrC+vuV3V5ofe+VYcIUYtq6pGt/D+bsizDfYR45p1Gs3rlS8xfw/ztlxr51Oeq+WKWYdlyPvfm/9HM+4zPCfw/gf8XYznB3R+rmv+fwvNo7JcVVqLWVUcp8jkRSwit44mL+jrsaj5fINBfiy/Dmvrs7vw/kXnxqO+7VbzEs/9WFZ/PUZ99ldB6VbOv4v6fBpxfzv3/qFCL9l6ZEvkezZU+ulmEuK6s+6jc/xteJ5PuTM8voIGxxe+2uK420ob7BdqO5qQrI/IY7oElzbx87b66R5jrfivVIu3Iw46RP2V58qq/790tzzOew3Dcj8r2JB/T2kizH5xZucp2qW+z8ak9+bHjhvbkJttV7GW7Sr1s1xrDdsnzAl0bXuP91xwpD609eV/jfZu00ZW23dpydJ+/sXa0/2njzfh7rxNoR3v9e6N3HMr8ttdOnmj6aOoPc0NSWrx/wnqpfu1oYy1y/ZDrSrBh/I/20n4xFCOxA07CMMzCjvhHrGog562cz8HyjHK3uw+RrGcwRuAQ7ItDcSAOw+E4HOMxDifjCEw=
*/