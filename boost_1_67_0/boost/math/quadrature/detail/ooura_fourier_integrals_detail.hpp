// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_MATH_QUADRATURE_DETAIL_OOURA_FOURIER_INTEGRALS_DETAIL_HPP
#define BOOST_MATH_QUADRATURE_DETAIL_OOURA_FOURIER_INTEGRALS_DETAIL_HPP
#include <utility> // for std::pair.
#include <mutex>
#include <atomic>
#include <vector>
#include <iostream>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/special_functions/sin_pi.hpp>
#include <boost/math/special_functions/cos_pi.hpp>
#include <boost/math/constants/constants.hpp>

namespace boost { namespace math { namespace quadrature { namespace detail {

// Ooura and Mori, A robust double exponential formula for Fourier-type integrals,
// eta is the argument to the exponential in equation 3.3:
template<class Real>
std::pair<Real, Real> ooura_eta(Real x, Real alpha) {
    using std::expm1;
    using std::exp;
    using std::abs;
    Real expx = exp(x);
    Real eta_prime = 2 + alpha/expx + expx/4;
    Real eta;
    // This is the fast branch:
    if (abs(x) > 0.125) {
        eta = 2*x - alpha*(1/expx - 1) + (expx - 1)/4;
    }
    else {// this is the slow branch using expm1 for small x:
        eta = 2*x - alpha*expm1(-x) + expm1(x)/4;
    }
    return {eta, eta_prime};
}

// Ooura and Mori, A robust double exponential formula for Fourier-type integrals,
// equation 3.6:
template<class Real>
Real calculate_ooura_alpha(Real h)
{
    using boost::math::constants::pi;
    using std::log1p;
    using std::sqrt;
    Real x = sqrt(16 + 4*log1p(pi<Real>()/h)/h);
    return 1/x;
}

template<class Real>
std::pair<Real, Real> ooura_sin_node_and_weight(long n, Real h, Real alpha)
{
    using std::expm1;
    using std::exp;
    using std::abs;
    using boost::math::constants::pi;
    using std::isnan;

    if (n == 0) {
        // Equation 44 of https://arxiv.org/pdf/0911.4796.pdf
        // Fourier Transform of the Stretched Exponential Function: Analytic Error Bounds,
        // Double Exponential Transform, and Open-Source Implementation,
        // Joachim Wuttke, 
        // The C library libkww provides functions to compute the Kohlrausch-Williams-Watts function, 
        // the Laplace-Fourier transform of the stretched (or compressed) exponential function exp(-t^beta)
        // for exponent beta between 0.1 and 1.9 with sixteen decimal digits accuracy.

        Real eta_prime_0 = Real(2) + alpha + Real(1)/Real(4);
        Real node = pi<Real>()/(eta_prime_0*h);
        Real weight = pi<Real>()*boost::math::sin_pi(1/(eta_prime_0*h));
        Real eta_dbl_prime = -alpha + Real(1)/Real(4);
        Real phi_prime_0 = (1 - eta_dbl_prime/(eta_prime_0*eta_prime_0))/2;
        weight *= phi_prime_0;
        return {node, weight};
    }
    Real x = n*h;
    auto p = ooura_eta(x, alpha);
    auto eta = p.first;
    auto eta_prime = p.second;

    Real expm1_meta = expm1(-eta);
    Real exp_meta = exp(-eta);
    Real node = -n*pi<Real>()/expm1_meta;


    // I have verified that this is not a significant source of inaccuracy in the weight computation:
    Real phi_prime = -(expm1_meta + x*exp_meta*eta_prime)/(expm1_meta*expm1_meta);

    // The main source of inaccuracy is in computation of sin_pi.
    // But I've agonized over this, and I think it's as good as it can get:
    Real s = pi<Real>();
    Real arg;
    if(eta > 1) {
        arg = n/( 1/exp_meta - 1 );
        s *= boost::math::sin_pi(arg);
        if (n&1) {
            s *= -1;
        }
    }
    else if (eta < -1) {
        arg = n/(1-exp_meta);
        s *= boost::math::sin_pi(arg);
    }
    else {
        arg = -n*exp_meta/expm1_meta;
        s *= boost::math::sin_pi(arg);
        if (n&1) {
            s *= -1;
        }
    }

    Real weight = s*phi_prime;
    return {node, weight};
}

#ifdef BOOST_MATH_INSTRUMENT_OOURA
template<class Real>
void print_ooura_estimate(size_t i, Real I0, Real I1, Real omega) {
    using std::abs;
    std::cout << std::defaultfloat
              << std::setprecision(std::numeric_limits<Real>::digits10)
              << std::fixed;
    std::cout << "h = " << Real(1)/Real(1<<i) << ", I_h = " << I0/omega
              << " = " << std::hexfloat << I0/omega << ", absolute error estimate = "
              << std::defaultfloat << std::scientific << abs(I0-I1)  << std::endl;
}
#endif


template<class Real>
std::pair<Real, Real> ooura_cos_node_and_weight(long n, Real h, Real alpha)
{
    using std::expm1;
    using std::exp;
    using std::abs;
    using boost::math::constants::pi;

    Real x = h*(n-Real(1)/Real(2));
    auto p = ooura_eta(x, alpha);
    auto eta = p.first;
    auto eta_prime = p.second;
    Real expm1_meta = expm1(-eta);
    Real exp_meta = exp(-eta);
    Real node = pi<Real>()*(Real(1)/Real(2)-n)/expm1_meta;

    Real phi_prime = -(expm1_meta + x*exp_meta*eta_prime)/(expm1_meta*expm1_meta);

    // Takuya Ooura and Masatake Mori,
    // Journal of Computational and Applied Mathematics, 112 (1999) 229-241.
    // A robust double exponential formula for Fourier-type integrals.
    // Equation 4.6
    Real s = pi<Real>();
    Real arg;
    if (eta < -1) {
        arg = -(n-Real(1)/Real(2))/expm1_meta;
        s *= boost::math::cos_pi(arg);
    }
    else {
        arg = -(n-Real(1)/Real(2))*exp_meta/expm1_meta;
        s *= boost::math::sin_pi(arg);
        if (n&1) {
            s *= -1;
        }
    }

    Real weight = s*phi_prime;
    return {node, weight};
}


template<class Real>
class ooura_fourier_sin_detail {
public:
    ooura_fourier_sin_detail(const Real relative_error_goal, size_t levels) {
#ifdef BOOST_MATH_INSTRUMENT_OOURA
      std::cout << "ooura_fourier_sin with relative error goal " << relative_error_goal 
        << " & " << levels << " levels." << std::endl;
#endif // BOOST_MATH_INSTRUMENT_OOURA
        if (relative_error_goal < std::numeric_limits<Real>::epsilon() * 2) {
            throw std::domain_error("The relative error goal cannot be smaller than the unit roundoff.");
        }
        using std::abs;
        requested_levels_ = levels;
        starting_level_ = 0;
        rel_err_goal_ = relative_error_goal;
        big_nodes_.reserve(levels);
        bweights_.reserve(levels);
        little_nodes_.reserve(levels);
        lweights_.reserve(levels);

        for (size_t i = 0; i < levels; ++i) {
            if (std::is_same<Real, float>::value) {
                add_level<double>(i);
            }
            else if (std::is_same<Real, double>::value) {
                add_level<long double>(i);
            }
            else {
                add_level<Real>(i);
            }
        }
    }

    std::vector<std::vector<Real>> const & big_nodes() const {
        return big_nodes_;
    }

    std::vector<std::vector<Real>> const & weights_for_big_nodes() const {
        return bweights_;
    }

    std::vector<std::vector<Real>> const & little_nodes() const {
        return little_nodes_;
    }

    std::vector<std::vector<Real>> const & weights_for_little_nodes() const {
        return lweights_;
    }

    template<class F>
    std::pair<Real,Real> integrate(F const & f, Real omega) {
        using std::abs;
        using std::max;
        using boost::math::constants::pi;

        if (omega == 0) {
            return {Real(0), Real(0)};
        }
        if (omega < 0) {
            auto p = this->integrate(f, -omega);
            return {-p.first, p.second};
        }

        Real I1 = std::numeric_limits<Real>::quiet_NaN();
        Real relative_error_estimate = std::numeric_limits<Real>::quiet_NaN();
        // As we compute integrals, we learn about their structure.
        // Assuming we compute f(t)sin(wt) for many different omega, this gives some
        // a posteriori ability to choose a refinement level that is roughly appropriate.
        size_t i = starting_level_;
        do {
            Real I0 = estimate_integral(f, omega, i);
#ifdef BOOST_MATH_INSTRUMENT_OOURA
            print_ooura_estimate(i, I0, I1, omega);
#endif
            Real absolute_error_estimate = abs(I0-I1);
            Real scale = (max)(abs(I0), abs(I1));
            if (!isnan(I1) && absolute_error_estimate <= rel_err_goal_*scale) {
                starting_level_ = (max)(long(i) - 1, long(0));
                return {I0/omega, absolute_error_estimate/scale};
            }
            I1 = I0;
        } while(++i < big_nodes_.size());

        // We've used up all our precomputed levels.
        // Now we need to add more.
        // It might seems reasonable to just keep adding levels indefinitely, if that's what the user wants.
        // But in fact the nodes and weights just merge into each other and the error gets worse after a certain number.
        // This value for max_additional_levels was chosen by observation of a slowly converging oscillatory integral:
        // f(x) := cos(7cos(x))sin(x)/x
        size_t max_additional_levels = 4;
        while (big_nodes_.size() < requested_levels_ + max_additional_levels) {
            size_t ii = big_nodes_.size();
            if (std::is_same<Real, float>::value) {
                add_level<double>(ii);
            }
            else if (std::is_same<Real, double>::value) {
                add_level<long double>(ii);
            }
            else {
                add_level<Real>(ii);
            }
            Real I0 = estimate_integral(f, omega, ii);
            Real absolute_error_estimate = abs(I0-I1);
            Real scale = (max)(abs(I0), abs(I1));
#ifdef BOOST_MATH_INSTRUMENT_OOURA
            print_ooura_estimate(ii, I0, I1, omega);
#endif
            if (absolute_error_estimate <= rel_err_goal_*scale) {
                starting_level_ = (max)(long(ii) - 1, long(0));
                return {I0/omega, absolute_error_estimate/scale};
            }
            I1 = I0;
            ++ii;
        }

        starting_level_ = static_cast<long>(big_nodes_.size() - 2);
        return {I1/omega, relative_error_estimate};
    }

private:

    template<class PreciseReal>
    void add_level(size_t i) {
        using std::abs;
        size_t current_num_levels = big_nodes_.size();
        Real unit_roundoff = std::numeric_limits<Real>::epsilon()/2;
        // h0 = 1. Then all further levels have h_i = 1/2^i.
        // Since the nodes don't nest, we could conceivably divide h by (say) 1.5, or 3.
        // It's not clear how much benefit (or loss) would be obtained from this.
        PreciseReal h = PreciseReal(1)/PreciseReal(1<<i);

        std::vector<Real> bnode_row;
        std::vector<Real> bweight_row;

        // This is a pretty good estimate for how many elements will be placed in the vector:
        bnode_row.reserve((static_cast<size_t>(1)<<i)*sizeof(Real));
        bweight_row.reserve((static_cast<size_t>(1)<<i)*sizeof(Real));

        std::vector<Real> lnode_row;
        std::vector<Real> lweight_row;

        lnode_row.reserve((static_cast<size_t>(1)<<i)*sizeof(Real));
        lweight_row.reserve((static_cast<size_t>(1)<<i)*sizeof(Real));

        Real max_weight = 1;
        auto alpha = calculate_ooura_alpha(h);
        long n = 0;
        Real w;
        do {
            auto precise_nw = ooura_sin_node_and_weight(n, h, alpha);
            Real node = static_cast<Real>(precise_nw.first);
            Real weight = static_cast<Real>(precise_nw.second);
            w = weight;
            if (bnode_row.size() == bnode_row.capacity()) {
                bnode_row.reserve(2*bnode_row.size());
                bweight_row.reserve(2*bnode_row.size());
            }

            bnode_row.push_back(node);
            bweight_row.push_back(weight);
            if (abs(weight) > max_weight) {
                max_weight = abs(weight);
            }
            ++n;
            // f(t)->0 as t->infty, which is why the weights are computed up to the unit roundoff.
        } while(abs(w) > unit_roundoff*max_weight);

        // This class tends to consume a lot of memory; shrink the vectors back down to size:
        bnode_row.shrink_to_fit();
        bweight_row.shrink_to_fit();
        // Why we are splitting the nodes into regimes where t_n >> 1 and t_n << 1?
        // It will create the opportunity to sensibly truncate the quadrature sum to significant terms.
        n = -1;
        do {
            auto precise_nw = ooura_sin_node_and_weight(n, h, alpha);
            Real node = static_cast<Real>(precise_nw.first);
            if (node <= 0) {
                break;
            }
            Real weight = static_cast<Real>(precise_nw.second);
            w = weight;
            using std::isnan;
            if (isnan(node)) {
                // This occurs at n = -11 in quad precision:
                break;
            }
            if (lnode_row.size() > 0) {
                if (lnode_row[lnode_row.size()-1] == node) {
                    // The nodes have fused into each other:
                    break;
                }
            }
            if (lnode_row.size() == lnode_row.capacity()) {
                lnode_row.reserve(2*lnode_row.size());
                lweight_row.reserve(2*lnode_row.size());
            }
            lnode_row.push_back(node);
            lweight_row.push_back(weight);
            if (abs(weight) > max_weight) {
                max_weight = abs(weight);
            }
            --n;
            // f(t)->infty is possible as t->0, hence compute up to the min.
        } while(abs(w) > (std::numeric_limits<Real>::min)()*max_weight);

        lnode_row.shrink_to_fit();
        lweight_row.shrink_to_fit();

        // std::scoped_lock once C++17 is more common?
        std::lock_guard<std::mutex> lock(node_weight_mutex_);
        // Another thread might have already finished this calculation and appended it to the nodes/weights:
        if (current_num_levels == big_nodes_.size()) {
            big_nodes_.push_back(bnode_row);
            bweights_.push_back(bweight_row);

            little_nodes_.push_back(lnode_row);
            lweights_.push_back(lweight_row);
        }
    }

    template<class F>
    Real estimate_integral(F const & f, Real omega, size_t i) {
        // Because so few function evaluations are required to get high accuracy on the integrals in the tests,
        // Kahan summation doesn't really help.
        //auto cond = boost::math::tools::summation_condition_number<Real, true>(0);
        Real I0 = 0;
        auto const & b_nodes = big_nodes_[i];
        auto const & b_weights = bweights_[i];
        // Will benchmark if this is helpful:
        Real inv_omega = 1/omega;
        for(size_t j = 0 ; j < b_nodes.size(); ++j) {
            I0 += f(b_nodes[j]*inv_omega)*b_weights[j];
        }

        auto const & l_nodes = little_nodes_[i];
        auto const & l_weights = lweights_[i];
        // If f decays rapidly as |t|->infty, not all of these calls are necessary.
        for (size_t j = 0; j < l_nodes.size(); ++j) {
            I0 += f(l_nodes[j]*inv_omega)*l_weights[j];
        }
        return I0;
    }

    std::mutex node_weight_mutex_;
    // Nodes for n >= 0, giving t_n = pi*phi(nh)/h. Generally t_n >> 1.
    std::vector<std::vector<Real>> big_nodes_;
    // The term bweights_ will indicate that these are weights corresponding
    // to the big nodes:
    std::vector<std::vector<Real>> bweights_;

    // Nodes for n < 0: Generally t_n << 1, and an invariant is that t_n > 0.
    std::vector<std::vector<Real>> little_nodes_;
    std::vector<std::vector<Real>> lweights_;
    Real rel_err_goal_;
    std::atomic<long> starting_level_;
    size_t requested_levels_;
};

template<class Real>
class ooura_fourier_cos_detail {
public:
    ooura_fourier_cos_detail(const Real relative_error_goal, size_t levels) {
#ifdef BOOST_MATH_INSTRUMENT_OOURA
      std::cout << "ooura_fourier_cos with relative error goal " << relative_error_goal
        << " & " << levels << " levels." << std::endl;
      std::cout << "epsilon for type = " << std::numeric_limits<Real>::epsilon() << std::endl;
#endif // BOOST_MATH_INSTRUMENT_OOURA
        if (relative_error_goal < std::numeric_limits<Real>::epsilon() * 2) {
            throw std::domain_error("The relative error goal cannot be smaller than the unit roundoff!");
        }

        using std::abs;
        requested_levels_ = levels;
        starting_level_ = 0;
        rel_err_goal_ = relative_error_goal;
        big_nodes_.reserve(levels);
        bweights_.reserve(levels);
        little_nodes_.reserve(levels);
        lweights_.reserve(levels);

        for (size_t i = 0; i < levels; ++i) {
            if (std::is_same<Real, float>::value) {
                add_level<double>(i);
            }
            else if (std::is_same<Real, double>::value) {
                add_level<long double>(i);
            }
            else {
                add_level<Real>(i);
            }
        }

    }

    template<class F>
    std::pair<Real,Real> integrate(F const & f, Real omega) {
        using std::abs;
        using std::max;
        using boost::math::constants::pi;

        if (omega == 0) {
            throw std::domain_error("At omega = 0, the integral is not oscillatory. The user must choose an appropriate method for this case.\n");
        }

        if (omega < 0) {
            return this->integrate(f, -omega);
        }

        Real I1 = std::numeric_limits<Real>::quiet_NaN();
        Real absolute_error_estimate = std::numeric_limits<Real>::quiet_NaN();
        Real scale = std::numeric_limits<Real>::quiet_NaN();
        size_t i = starting_level_;
        do {
            Real I0 = estimate_integral(f, omega, i);
#ifdef BOOST_MATH_INSTRUMENT_OOURA
            print_ooura_estimate(i, I0, I1, omega);
#endif
            absolute_error_estimate = abs(I0-I1);
            scale = (max)(abs(I0), abs(I1));
            if (!isnan(I1) && absolute_error_estimate <= rel_err_goal_*scale) {
                starting_level_ = (max)(long(i) - 1, long(0));
                return {I0/omega, absolute_error_estimate/scale};
            }
            I1 = I0;
        } while(++i < big_nodes_.size());

        size_t max_additional_levels = 4;
        while (big_nodes_.size() < requested_levels_ + max_additional_levels) {
            size_t ii = big_nodes_.size();
            if (std::is_same<Real, float>::value) {
                add_level<double>(ii);
            }
            else if (std::is_same<Real, double>::value) {
                add_level<long double>(ii);
            }
            else {
                add_level<Real>(ii);
            }
            Real I0 = estimate_integral(f, omega, ii);
#ifdef BOOST_MATH_INSTRUMENT_OOURA
            print_ooura_estimate(ii, I0, I1, omega);
#endif
            absolute_error_estimate = abs(I0-I1);
            scale = (max)(abs(I0), abs(I1));
            if (absolute_error_estimate <= rel_err_goal_*scale) {
                starting_level_ = (max)(long(ii) - 1, long(0));
                return {I0/omega, absolute_error_estimate/scale};
            }
            I1 = I0;
            ++ii;
        }

        starting_level_ = static_cast<long>(big_nodes_.size() - 2);
        return {I1/omega, absolute_error_estimate/scale};
    }

private:

    template<class PreciseReal>
    void add_level(size_t i) {
        using std::abs;
        size_t current_num_levels = big_nodes_.size();
        Real unit_roundoff = std::numeric_limits<Real>::epsilon()/2;
        PreciseReal h = PreciseReal(1)/PreciseReal(1<<i);

        std::vector<Real> bnode_row;
        std::vector<Real> bweight_row;
        bnode_row.reserve((static_cast<size_t>(1)<<i)*sizeof(Real));
        bweight_row.reserve((static_cast<size_t>(1)<<i)*sizeof(Real));

        std::vector<Real> lnode_row;
        std::vector<Real> lweight_row;

        lnode_row.reserve((static_cast<size_t>(1)<<i)*sizeof(Real));
        lweight_row.reserve((static_cast<size_t>(1)<<i)*sizeof(Real));

        Real max_weight = 1;
        auto alpha = calculate_ooura_alpha(h);
        long n = 0;
        Real w;
        do {
            auto precise_nw = ooura_cos_node_and_weight(n, h, alpha);
            Real node = static_cast<Real>(precise_nw.first);
            Real weight = static_cast<Real>(precise_nw.second);
            w = weight;
            if (bnode_row.size() == bnode_row.capacity()) {
                bnode_row.reserve(2*bnode_row.size());
                bweight_row.reserve(2*bnode_row.size());
            }

            bnode_row.push_back(node);
            bweight_row.push_back(weight);
            if (abs(weight) > max_weight) {
                max_weight = abs(weight);
            }
            ++n;
            // f(t)->0 as t->infty, which is why the weights are computed up to the unit roundoff.
        } while(abs(w) > unit_roundoff*max_weight);

        bnode_row.shrink_to_fit();
        bweight_row.shrink_to_fit();
        n = -1;
        do {
            auto precise_nw = ooura_cos_node_and_weight(n, h, alpha);
            Real node = static_cast<Real>(precise_nw.first);
            // The function cannot be singular at zero,
            // so zero is not a unreasonable node,
            // unlike in the case of the Fourier Sine.
            // Hence only break if the node is negative.
            if (node < 0) {
                break;
            }
            Real weight = static_cast<Real>(precise_nw.second);
            w = weight;
            if (lnode_row.size() > 0) {
                if (lnode_row.back() == node) {
                    // The nodes have fused into each other:
                    break;
                }
            }
            if (lnode_row.size() == lnode_row.capacity()) {
                lnode_row.reserve(2*lnode_row.size());
                lweight_row.reserve(2*lnode_row.size());
            }

            lnode_row.push_back(node);
            lweight_row.push_back(weight);
            if (abs(weight) > max_weight) {
                max_weight = abs(weight);
            }
            --n;
        } while(abs(w) > (std::numeric_limits<Real>::min)()*max_weight);

        lnode_row.shrink_to_fit();
        lweight_row.shrink_to_fit();

        std::lock_guard<std::mutex> lock(node_weight_mutex_);
        // Another thread might have already finished this calculation and appended it to the nodes/weights:
        if (current_num_levels == big_nodes_.size()) {
            big_nodes_.push_back(bnode_row);
            bweights_.push_back(bweight_row);

            little_nodes_.push_back(lnode_row);
            lweights_.push_back(lweight_row);
        }
    }

    template<class F>
    Real estimate_integral(F const & f, Real omega, size_t i) {
        Real I0 = 0;
        auto const & b_nodes = big_nodes_[i];
        auto const & b_weights = bweights_[i];
        Real inv_omega = 1/omega;
        for(size_t j = 0 ; j < b_nodes.size(); ++j) {
            I0 += f(b_nodes[j]*inv_omega)*b_weights[j];
        }

        auto const & l_nodes = little_nodes_[i];
        auto const & l_weights = lweights_[i];
        for (size_t j = 0; j < l_nodes.size(); ++j) {
            I0 += f(l_nodes[j]*inv_omega)*l_weights[j];
        }
        return I0;
    }

    std::mutex node_weight_mutex_;
    std::vector<std::vector<Real>> big_nodes_;
    std::vector<std::vector<Real>> bweights_;

    std::vector<std::vector<Real>> little_nodes_;
    std::vector<std::vector<Real>> lweights_;
    Real rel_err_goal_;
    std::atomic<long> starting_level_;
    size_t requested_levels_;
};


}}}}
#endif

/* ooura_fourier_integrals_detail.hpp
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
*/