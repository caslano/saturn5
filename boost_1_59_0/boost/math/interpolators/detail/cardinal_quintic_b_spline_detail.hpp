// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_INTERPOLATORS_CARDINAL_QUINTIC_B_SPLINE_DETAIL_HPP
#define BOOST_MATH_INTERPOLATORS_CARDINAL_QUINTIC_B_SPLINE_DETAIL_HPP
#include <cmath>
#include <vector>
#include <utility>
#include <boost/math/special_functions/cardinal_b_spline.hpp>

namespace boost{ namespace math{ namespace interpolators{ namespace detail{


template <class Real>
class cardinal_quintic_b_spline_detail
{
public:
    // If you don't know the value of the derivative at the endpoints, leave them as nans and the routine will estimate them.
    // y[0] = y(a), y[n -1] = y(b), step_size = (b - a)/(n -1).

    cardinal_quintic_b_spline_detail(const Real* const y,
                                     size_t n,
                                     Real t0 /* initial time, left endpoint */,
                                     Real h  /*spacing, stepsize*/,
                                     std::pair<Real, Real> left_endpoint_derivatives,
                                     std::pair<Real, Real> right_endpoint_derivatives)
    {
        static_assert(!std::is_integral<Real>::value, "The quintic B-spline interpolator only works with floating point types.");
        if (h <= 0) {
            throw std::logic_error("Spacing must be > 0.");
        }
        m_inv_h = 1/h;
        m_t0 = t0;

        if (n < 8) {
            throw std::logic_error("The quintic B-spline interpolator requires at least 8 points.");
        }

        using std::isnan;
        // This interpolator has error of order h^6, so the derivatives should be estimated with the same error.
        // See: https://en.wikipedia.org/wiki/Finite_difference_coefficient
        if (isnan(left_endpoint_derivatives.first)) {
            Real tmp = -49*y[0]/20 + 6*y[1] - 15*y[2]/2 + 20*y[3]/3 - 15*y[4]/4 + 6*y[5]/5 - y[6]/6;
            left_endpoint_derivatives.first = tmp/h;
        }
        if (isnan(right_endpoint_derivatives.first)) {
            Real tmp = 49*y[n-1]/20 - 6*y[n-2] + 15*y[n-3]/2 - 20*y[n-4]/3 + 15*y[n-5]/4 - 6*y[n-6]/5 + y[n-7]/6;
            right_endpoint_derivatives.first = tmp/h;
        }
        if(isnan(left_endpoint_derivatives.second)) {
            Real tmp = 469*y[0]/90 - 223*y[1]/10 + 879*y[2]/20 - 949*y[3]/18 + 41*y[4] - 201*y[5]/10 + 1019*y[6]/180 - 7*y[7]/10;
            left_endpoint_derivatives.second = tmp/(h*h);
        }
        if (isnan(right_endpoint_derivatives.second)) {
            Real tmp = 469*y[n-1]/90 - 223*y[n-2]/10 + 879*y[n-3]/20 - 949*y[n-4]/18 + 41*y[n-5] - 201*y[n-6]/10 + 1019*y[n-7]/180 - 7*y[n-8]/10;
            right_endpoint_derivatives.second = tmp/(h*h);
        }

        // This is really challenging my mental limits on by-hand row reduction.
        // I debated bringing in a dependency on a sparse linear solver, but given that that would cause much agony for users I decided against it.

        std::vector<Real> rhs(n+4);
        rhs[0] = 20*y[0] - 12*h*left_endpoint_derivatives.first +  2*h*h*left_endpoint_derivatives.second;
        rhs[1] = 60*y[0] - 12*h*left_endpoint_derivatives.first;
        for (size_t i = 2; i < n + 2; ++i) {
            rhs[i] = 120*y[i-2];
        }
        rhs[n+2] = 60*y[n-1] + 12*h*right_endpoint_derivatives.first;
        rhs[n+3] = 20*y[n-1] + 12*h*right_endpoint_derivatives.first +  2*h*h*right_endpoint_derivatives.second;

        std::vector<Real> diagonal(n+4, 66);
        diagonal[0] = 1;
        diagonal[1] = 18;
        diagonal[n+2] = 18;
        diagonal[n+3] = 1;

        std::vector<Real> first_superdiagonal(n+4, 26);
        first_superdiagonal[0] = 10;
        first_superdiagonal[1] = 33;
        first_superdiagonal[n+2] = 1;
        // There is one less superdiagonal than diagonal; make sure that if we read it, it shows up as a bug:
        first_superdiagonal[n+3] = std::numeric_limits<Real>::quiet_NaN();

        std::vector<Real> second_superdiagonal(n+4, 1);
        second_superdiagonal[0] = 9;
        second_superdiagonal[1] = 8;
        second_superdiagonal[n+2] = std::numeric_limits<Real>::quiet_NaN();
        second_superdiagonal[n+3] = std::numeric_limits<Real>::quiet_NaN();

        std::vector<Real> first_subdiagonal(n+4, 26);
        first_subdiagonal[0] = std::numeric_limits<Real>::quiet_NaN();
        first_subdiagonal[1] = 1;
        first_subdiagonal[n+2] = 33;
        first_subdiagonal[n+3] = 10;

        std::vector<Real> second_subdiagonal(n+4, 1);
        second_subdiagonal[0] = std::numeric_limits<Real>::quiet_NaN();
        second_subdiagonal[1] = std::numeric_limits<Real>::quiet_NaN();
        second_subdiagonal[n+2] = 8;
        second_subdiagonal[n+3] = 9;


        for (size_t i = 0; i < n+2; ++i) {
            Real di = diagonal[i];
            diagonal[i] = 1;
            first_superdiagonal[i] /= di;
            second_superdiagonal[i] /= di;
            rhs[i] /= di;

            // Eliminate first subdiagonal:
            Real nfsub = -first_subdiagonal[i+1];
            // Superfluous:
            first_subdiagonal[i+1] /= nfsub;
            // Not superfluous:
            diagonal[i+1] /= nfsub;
            first_superdiagonal[i+1] /= nfsub;
            second_superdiagonal[i+1] /= nfsub;
            rhs[i+1] /= nfsub;

            diagonal[i+1] += first_superdiagonal[i];
            first_superdiagonal[i+1] += second_superdiagonal[i];
            rhs[i+1] += rhs[i];
            // Superfluous, but clarifying:
            first_subdiagonal[i+1] = 0;

            // Eliminate second subdiagonal:
            Real nssub = -second_subdiagonal[i+2];
            first_subdiagonal[i+2] /= nssub;
            diagonal[i+2] /= nssub;
            first_superdiagonal[i+2] /= nssub;
            second_superdiagonal[i+2] /= nssub;
            rhs[i+2] /= nssub;

            first_subdiagonal[i+2] += first_superdiagonal[i];
            diagonal[i+2] += second_superdiagonal[i];
            rhs[i+2] += rhs[i];
            // Superfluous, but clarifying:
            second_subdiagonal[i+2] = 0;
        }

        // Eliminate last subdiagonal:
        Real dnp2 = diagonal[n+2];
        diagonal[n+2] = 1;
        first_superdiagonal[n+2] /= dnp2;
        rhs[n+2] /= dnp2;
        Real nfsubnp3 = -first_subdiagonal[n+3];
        diagonal[n+3] /= nfsubnp3;
        rhs[n+3] /= nfsubnp3;

        diagonal[n+3] += first_superdiagonal[n+2];
        rhs[n+3] += rhs[n+2];

        m_alpha.resize(n + 4, std::numeric_limits<Real>::quiet_NaN());

        m_alpha[n+3] = rhs[n+3]/diagonal[n+3];
        m_alpha[n+2] = rhs[n+2] - first_superdiagonal[n+2]*m_alpha[n+3];
        for (int64_t i = int64_t(n+1); i >= 0; --i) {
            m_alpha[i] = rhs[i] - first_superdiagonal[i]*m_alpha[i+1] - second_superdiagonal[i]*m_alpha[i+2];
        }

    }

    Real operator()(Real t) const {
        using std::ceil;
        using std::floor;
        using boost::math::cardinal_b_spline;
        // tf = t0 + (n-1)*h
        // alpha.size() = n+4
        if (t < m_t0 || t > m_t0 + (m_alpha.size()-5)/m_inv_h) {
            const char* err_msg = "Tried to evaluate the cardinal quintic b-spline outside the domain of of interpolation; extrapolation does not work.";
            throw std::domain_error(err_msg);
        }
        Real x = (t-m_t0)*m_inv_h;
        // Support of B_5 is [-3, 3]. So -3 < x - j + 2 < 3, so x-1 < j < x+5.
        // TODO: Zero pad m_alpha so that only the domain check is necessary.
        int64_t j_min = (std::max)(int64_t(0), int64_t(ceil(x-1)));
        int64_t j_max = (std::min)(int64_t(m_alpha.size() - 1), int64_t(floor(x+5)) );
        Real s = 0;
        for (int64_t j = j_min; j <= j_max; ++j) {
            // TODO: Use Cox 1972 to generate all integer translates of B5 simultaneously.
            s += m_alpha[j]*cardinal_b_spline<5, Real>(x - j + 2);
        }
        return s;
    }

    Real prime(Real t) const {
        using std::ceil;
        using std::floor;
        using boost::math::cardinal_b_spline_prime;
        if (t < m_t0 || t > m_t0 + (m_alpha.size()-5)/m_inv_h) {
            const char* err_msg = "Tried to evaluate the cardinal quintic b-spline outside the domain of of interpolation; extrapolation does not work.";
            throw std::domain_error(err_msg);
        }
        Real x = (t-m_t0)*m_inv_h;
        // Support of B_5 is [-3, 3]. So -3 < x - j + 2 < 3, so x-1 < j < x+5
        int64_t j_min = (std::max)(int64_t(0), int64_t(ceil(x-1)));
        int64_t j_max = (std::min)(int64_t(m_alpha.size() - 1), int64_t(floor(x+5)) );
        Real s = 0;
        for (int64_t j = j_min; j <= j_max; ++j) {
            s += m_alpha[j]*cardinal_b_spline_prime<5, Real>(x - j + 2);
        }
        return s*m_inv_h;

    }

    Real double_prime(Real t) const {
        using std::ceil;
        using std::floor;
        using boost::math::cardinal_b_spline_double_prime;
        if (t < m_t0 || t > m_t0 + (m_alpha.size()-5)/m_inv_h) {
            const char* err_msg = "Tried to evaluate the cardinal quintic b-spline outside the domain of of interpolation; extrapolation does not work.";
            throw std::domain_error(err_msg);
        }
        Real x = (t-m_t0)*m_inv_h;
        // Support of B_5 is [-3, 3]. So -3 < x - j + 2 < 3, so x-1 < j < x+5
        int64_t j_min = (std::max)(int64_t(0), int64_t(ceil(x-1)));
        int64_t j_max = (std::min)(int64_t(m_alpha.size() - 1), int64_t(floor(x+5)) );
        Real s = 0;
        for (int64_t j = j_min; j <= j_max; ++j) {
            s += m_alpha[j]*cardinal_b_spline_double_prime<5, Real>(x - j + 2);
        }
        return s*m_inv_h*m_inv_h;
    }


    Real t_max() const {
        return m_t0 + (m_alpha.size()-5)/m_inv_h;
    }

private:
    std::vector<Real> m_alpha;
    Real m_inv_h;
    Real m_t0;
};

}}}}
#endif

/* cardinal_quintic_b_spline_detail.hpp
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
*/