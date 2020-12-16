// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 * References:
 * Ooura, Takuya, and Masatake Mori. "A robust double exponential formula for Fourier-type integrals." Journal of computational and applied mathematics 112.1-2 (1999): 229-241.
 * http://www.kurims.kyoto-u.ac.jp/~ooura/intde.html
 */
#ifndef BOOST_MATH_QUADRATURE_OOURA_FOURIER_INTEGRALS_HPP
#define BOOST_MATH_QUADRATURE_OOURA_FOURIER_INTEGRALS_HPP
#include <memory>
#include <boost/math/quadrature/detail/ooura_fourier_integrals_detail.hpp>

namespace boost { namespace math { namespace quadrature {

template<class Real>
class ooura_fourier_sin {
public:
    ooura_fourier_sin(const Real relative_error_tolerance = tools::root_epsilon<Real>(), size_t levels = sizeof(Real)) : impl_(std::make_shared<detail::ooura_fourier_sin_detail<Real>>(relative_error_tolerance, levels))
    {}

    template<class F>
    std::pair<Real, Real> integrate(F const & f, Real omega) {
        return impl_->integrate(f, omega);
    }

    // These are just for debugging/unit tests:
    std::vector<std::vector<Real>> const & big_nodes() const {
        return impl_->big_nodes();
    }

    std::vector<std::vector<Real>> const & weights_for_big_nodes() const {
        return impl_->weights_for_big_nodes();
    }

    std::vector<std::vector<Real>> const & little_nodes() const {
        return impl_->little_nodes();
    }

    std::vector<std::vector<Real>> const & weights_for_little_nodes() const {
        return impl_->weights_for_little_nodes();
    }

private:
    std::shared_ptr<detail::ooura_fourier_sin_detail<Real>> impl_;
};


template<class Real>
class ooura_fourier_cos {
public:
    ooura_fourier_cos(const Real relative_error_tolerance = tools::root_epsilon<Real>(), size_t levels = sizeof(Real)) : impl_(std::make_shared<detail::ooura_fourier_cos_detail<Real>>(relative_error_tolerance, levels))
    {}

    template<class F>
    std::pair<Real, Real> integrate(F const & f, Real omega) {
        return impl_->integrate(f, omega);
    }
private:
    std::shared_ptr<detail::ooura_fourier_cos_detail<Real>> impl_;
};


}}}
#endif

/* ooura_fourier_integrals.hpp
7QEsgs+K93XkXO3VLxWsXPEuR19VG6ugvbpH8RHy1pzHq0C7Em73GXK+g+PdjPxOU/f/wDuF5/42aLqV87ELNa7OUn9GbOqeTO1kqeexrEGSYBG1n90ImOJomoyzGLX/J1i6qpcWaJfKNX5kssSWzu2OBce5HO8JghWvY10c6NuKc95NsBIX9+0hWLl6zj4V7ZYz1ge8LRnrJ1hgPes3MBl3a9X+H8brzfpdCOwM9uUS6PIgt8tCHLV5vcqFVmpfz4t2fTjeUfClO/tSiFyq+xGXJ2MOMkcxYhvA/l0rmPN0rtMboYu613JzVTvmmAaf53Bsd6Dvy/y5eg/aqb3w++DzCl4jZsNnVaePQr8g+/IkdH6Ja+NZ5Fx9LrwoWIrq+zI4prIvr4FjJM/ptxCvum8WQU1OZf3eA696x/lQMNtKrquPgTXgvp8il2qP8Qvk/BPW5Wv4117t/yGXl7MGO+Hztzwvf8J46p5RrUaClXDfeo2EYwf7lyxYxSKOo4lgZf3V/h/G68d1cLhgKZ2Z1y6YLcKaHgNsDOvXVrC0W3m8joLZlX5dBXOEeU08CT4PY95TgH3HddBbsMhI1rQv2imfByCOL9T+n2DlmzhHFwjmPC+BsOGIQ30XIBPjPce+5AgWUHc6RkLnOqx9QLBiL/MWQHsbt7sMfZeq/T/ot4jnxzWI1632/5CPTazpZNTGWI5jKnx5nWvtdvR9levqbvQ9k2O7F+3UHt5D8EXdSZgLn5uwL08IVrlW3f+DLxPU/h/aqXvm5cibuof8KrRfxvl9E+0msKbLkLfvuO9K5Pcd5vgA7bys1TrEsYBr4xP0Ve9lmwQrmcS8XyG/03m8rdBPfTdoB3K+hfPxI/qqmkxoLPGew7x1G+M9mfPWULDy7oylCJai3t8OQrtbOB+HCZZ2AufjCLRTdXA0eGfwHDxeMHsef/52AK+6f9oF4x3AHCcK5sxgX3qh72H8Pni6YLYrmPcswSLqffUcxDGM6/RccHThOTgUvvTkOX2xYKXqPMopWElnxtyI9yqO41LBikewBv4qXrX/B/26Me8YcLzN9TIO46ln4KvBq7SaAGw8+zJJsPRnmeOWxr+9K3Qb2qmzu7sw3lTmmIX6y+HxHkQ+7uO+j6Bvodr/Q45UvTyN/N7MfZ9HPh5R9/+gi7ov8Ap8SeQ5/QawHezzO9D5AEFq7v+BdxPPt/fRtw3rtxa8p/Fc3SBY2avcbiM0iHAcW1B/l3A7+XiX+yWMfQ/tv+Ha+AEaXMo+40u8dvXcWUew4gTGGgjmKFb3/wQLLOR1splglWrNORTjteB4WwlW9iLrfJRgEXUXpw3aTWZf2gtWUZvj6CyYU60l8kgszxvM0VOwkmwe7zTEpu70nimYbTf7fDZ4J3HfdHCo59MhgqWpM6Bh8E/dg8+AViPZPxfyUcFrrAe83zPmQxy7uW8I2Cb+7CkCpr4PewUw9a47Hrwv89y6Hrzq3WAidFHnUVOQI+XLdOR8C493J7BCnm+l0H4x+/cA6mqQ2v9Dbah7aY8De5RrbR6wbazVc8iRh+tloWClzdT3f9FO7TEuQWyp6v4fcqm+p/4uxpun7v+hnTqHXQPMxWvdemCT2OfPBSvvx+2+BId6/61EPjLV93+BqftNu5Ff9QyyB3Wq9vASU6RvS17r6gsWOZ9z1DgF99xYlwMFcxZzvRwC7Eqely0Fq3yKfWktWEh9r+04cOziumonWEoe57IT/CvmXKYKVqbuHJ8sWKAe65KGdo+q7/8KZldnO/0Fc5zL7QYJVqrm/mDBKg5g7CK0e4G1GoE4zuBayxasWO1l5KFdWH3/F/6tVPt/0Opn1n402rXgvmORD7U=
*/