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
        int64_t j_min = std::max(int64_t(0), int64_t(ceil(x-1)));
        int64_t j_max = std::min(int64_t(m_alpha.size() - 1), int64_t(floor(x+5)) );
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
        int64_t j_min = std::max(int64_t(0), int64_t(ceil(x-1)));
        int64_t j_max = std::min(int64_t(m_alpha.size() - 1), int64_t(floor(x+5)) );
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
        int64_t j_min = std::max(int64_t(0), int64_t(ceil(x-1)));
        int64_t j_max = std::min(int64_t(m_alpha.size() - 1), int64_t(floor(x+5)) );
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