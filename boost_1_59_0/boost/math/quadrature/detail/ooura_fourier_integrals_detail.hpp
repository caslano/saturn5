// Copyright Nick Thompson, 2019
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_MATH_QUADRATURE_DETAIL_OOURA_FOURIER_INTEGRALS_DETAIL_HPP
#define BOOST_MATH_QUADRATURE_DETAIL_OOURA_FOURIER_INTEGRALS_DETAIL_HPP
#include <utility> // for std::pair.
#include <vector>
#include <iostream>
#include <boost/math/special_functions/expm1.hpp>
#include <boost/math/special_functions/sin_pi.hpp>
#include <boost/math/special_functions/cos_pi.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/math/tools/config.hpp>

#ifdef BOOST_HAS_THREADS
#include <mutex>
#include <atomic>
#endif

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

        #ifdef BOOST_HAS_THREADS
        // std::scoped_lock once C++17 is more common?
        std::lock_guard<std::mutex> lock(node_weight_mutex_);
        #endif 
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

    #ifdef BOOST_HAS_THREADS
    std::mutex node_weight_mutex_;
    #endif
    // Nodes for n >= 0, giving t_n = pi*phi(nh)/h. Generally t_n >> 1.
    std::vector<std::vector<Real>> big_nodes_;
    // The term bweights_ will indicate that these are weights corresponding
    // to the big nodes:
    std::vector<std::vector<Real>> bweights_;

    // Nodes for n < 0: Generally t_n << 1, and an invariant is that t_n > 0.
    std::vector<std::vector<Real>> little_nodes_;
    std::vector<std::vector<Real>> lweights_;
    Real rel_err_goal_;

    #ifdef BOOST_HAS_THREADS
    std::atomic<long> starting_level_;
    #else
    long starting_level_;
    #endif
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

        #ifdef BOOST_HAS_THREADS
        std::lock_guard<std::mutex> lock(node_weight_mutex_);
        #endif

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

    #ifdef BOOST_HAS_THREADS
    std::mutex node_weight_mutex_;
    #endif 

    std::vector<std::vector<Real>> big_nodes_;
    std::vector<std::vector<Real>> bweights_;

    std::vector<std::vector<Real>> little_nodes_;
    std::vector<std::vector<Real>> lweights_;
    Real rel_err_goal_;

    #ifdef BOOST_HAS_THREADS
    std::atomic<long> starting_level_;
    #else
    long starting_level_;
    #endif

    size_t requested_levels_;
};


}}}}
#endif

/* ooura_fourier_integrals_detail.hpp
brLMPz+BX5UNNIln/dGdskipAFyBWh4dIfEuUmW264GGLVEoMo2w2ydOnaHDlqv17jhkb1EiZFIQoB8APN8fQrdWvxvs+gxJDIi4J1jiuo5lkJSg7YsUBau9JqXAMHJm0MCjJDDjclYDORllJJRUHkfRqGWQho4RMFQAasJMNra//AoVZsfefj7ejSaQu8wDyE9yddKZjSq4KFEtDABROpZi15fldsDDMskilFwXL7GJFPO/XRlUDRDG2DhEpLiQAcfD+DGE7Dg/qm8lEM8AO6y/B7Ft9NuhFjwOwDAHgAIW63emAnDI48fQ1WRT7QNCCvPV9wfDeCVzE5l3bvryu//5foTV5DcKnq3uzofq667zpn61L1e/fzUrYk5ZrNVyWAQiGjsAW5uHRCFOPnLQG+WqtmqLV537JBEUMftFle/hLBJY9yFFj+igWqGKSsdSJyuEMGLQEVLqsYbw8DWIByjab4c5JmabovEsxMWxleREwwDIB2H/QlHfBNblXYWBYDivjOOpdQQ3oDoXLGeGSXFYCXmnegSPDnVEpSEh1vMdupZF74I4g0Ij57JeGKLRDM80kQv0DJlOKOYfjodkJvRTMGfwpyVJxNBmCGJwoREMrrpR3LdAtnPutUFquXrlajJ7uVztLtyZlMU8JoAsL05DziJEiWaNx8UCRulKgB3m9lBCoZiTXe5Ut1+BnIXysJbQwqIMqXND2jukXDlclBtf3NP/UgtdUh7qFTKLZiTtH0xXqfwAEMgfP9pImcmEasAg9cwlSpBOXxfBSWJnwCMAOE5rSCma1hyLYFsnN9WNJSw9SfiehtCun+h7FZr61xMYchJICIA1CIGIwgd9QppLGnuqcVpBLddh+6FKcM4t3g0ij522Wp6mElrFl7lxCETxrXOhCpjYx5DM82Wa8kNBuVEtxjvxHwRfopvh5xf7C62NqBiCWQSYXD3ohrE1ncmk68LSBfwaOpxzpZHNISxhRZrCxKwrTXiJvBd2gOQKZEri6aRCuPgozn7BUsgyDmrijwP+94JiO+QdeAe9Dg4wnhFEd44TDxONHhkDIJ31F8iNQ18KsaV+bEJsMlJ9IXOYE5gKDdQqQaiuxhBpzU/ddKrfWlcdawVXjgtoxr9LDOFYxCpaw8heWP9XnMyovzOql03v1KMmPvl87PWIdCJADfSJefhEfI9M2JYgSwWI9zcUHXTWk2iyyqprpnZRF6/HnuZEL7fhB46A7s/NVErR6Id6GMmewsXOAYeA3tX2JsOhkKWyjyIZr/WW1hm8s8i9cFWgritHfoOlHoENTJtUANa4SXVW/zdJOr3WZA/4sJ9VCXOs6MUrBxCJPlZbR9JaMGKsIwwhjBkSEMyKfFtgK/BCLJWc3s86fjBgbuEIF5kWqC3RgIgauN2b59vve7xy7i7l5FkXz+ZiUDJrv/Qur192MIePABYUjQGVRYoA8GXooF0xSCKUp+Rwom+qld6fPnt5X29+GNR8xOhfl3AjeEVtWI9n0wuFmop2T1C3ix9XuT4UMyEK/DCG/j2go/F1voReIiriTtll36qpl/J9+d9C3YEfQeMmDIjDsRMqckLI/WJNEjGbFp+k/D+fdMXzQEanNqSaKY6UANls5BDv9x58AlLFmxWj6lkxQQdQXWRdrirlixJ1KD9LEl9ioHZgUgzP3BlpsoZ04WOkWrdhjy4/OD7CYuic6nzj7GTifLqrue2Aax0KlXKtTKV95lp46+C9osZi0odNEaibPE+VVaYkT1DmL8BWrlwOEQcN/mft/DHpCTd/LQyKUL64ER/KxOtJZnny4EDlYqll2n2sdciU9JSfxDvOQDqotdP6M17+GStJopffp7wPxKDsISEaASUSei8C9syyIdq/TniC/wUWfoKwAz3qUQUoM8zfA0zRgIn0/QKAhJa7unHFBC6g1zxG5bv5TPh9I3gE7wbmbEztxwJTXmL+CP4+uD88H5QHsPr8Rnxyh1ZOx9sDtqb6OWE5P8MYLvLXhHkb9vGMu2vvrvFLmMo9BMF0LHValqZSWSsjKoKJMixrg5DJdCYtrEGDCLnHB5TdUZiXH3rWKk78L8KgGVqg7mwHPieiz3afXxEBbp5HIGD6i41F4Otn5/IHYoX3kb80h7kBvs0fmc6iE7WeTQHLT0joowdIJC0x+VwS4PMjN1qQBcQEqJ8U1etqF0mnYS9SNV9cmQnsKBMRAmk8AR6Tu27ZrnZyTW2ZwJt9h0j8Fl/EkukCb98VgPgsvOrrwl4MoLJzEsvIpX+H6B0S2dD5qgXgGBoiCJQqKMj7dqovmitqbLIPCZvvtOukmVMI8TBcx/HjfhiKHCHfAwdUd+a7Ss7itJoDfSrZwpwHDy/546uYgYNBgng5mgGAWAn5JC/gy0QRmAyRDq2K309o/caWQP32EPpTov8Kcpoo6TprlPCLvJwm1onCyhTWhocci4zHQoBynyiBhBGbb/pxAYzuIHXuhCfZkNAc6EpN+F9fE5noT+NGXS/WL0nzZrFo4J4UvlasaYwuiiqADAR0jnTd6cXctSmUCYDXVj8pqW7DvzOfqHwkwK0FAbNQ0rNXSaITwIVsHUczZeHBhU0ABeOI9CdGKnGJPYCGuj2zHbT4ZtASUy3FJkFi9GYjK55xPm0hA8wFjrcwBzehp7Qnm90rUJLwfstwMqZhJLbgBxSmFaStPrkoI/+UaXTl+ag9zvjsNvobCM7wzgcTkDKc/+6gWcT3E9T0BDyuPB7QaXDRFsB1G2S1gCi6s4I0X+5ZryChvDtiRAFtAv7RNwqODHad/lQ2Ea4zXYI3l/KW1LxyExDzGiFg5XotXk7dR8yEB4HhVOBIPV1eJ4tJto7pOYaCCkrlHqibiaAZ/fBzBgeeQSAaK5Nsu0/33KTv7F20OZQqloKCCMZ7QkPzAvF3g+rQXCt0xN6ja9yCObxaLzn1Lo3nGLbyZR1xnPpAvY1DvAE3q9Qfppbvh/s6H1oR5R+P9VYPYuxuD4QuyopwTpNkeg3w11bHExaannI6itUJS0qvIYTT94cjjmkWM93McPTF1L4uzZRakGjnWXfpWConxkw5p7HJ4xx+ntYHsYWYGAJialt3Gm8sW5vTw/rWr3WKrZTYCp2AEFdUO8sziM1s2N9im8mCGsWUCwcSo1xDGEAzw1lRhhaBHqwDWAAbNMRId6FxPfayU/tkwpben1vLGhmKio2W31S9M/kFAR33U2m9OInjL6wvibo5wOXlGjbfRB2tc2s5S1RpXY/nR7ROhSt3nHgQAKFGJvEJjYjKStZBJHgZFaNwjoN3LbAEq4C3dyNjQNodMCflP6mo512n54lgNvsSwWV9xbOkj9T4+N+JUFBsEjrV7faNxA1ALBDywtzAMcrev2hheuDxKgaowuY2U/L0u60GlNxYW2oxvWXC7A3OG4R9UrJNbXqfGiYwONq9vYXZqmCv81ZWVeYl10Qb489bi+TwnVt7rN/qT0sJvwhtT8JI36r3R0qdkAaYKR/UYJQJL+gnChFpORtui6TLqCkS3NiGhVMaxhHBDieBHr89Y5XZOZh8MlHYrFkRpywe6HujhaoE8Te5rbiW+FiGtJQBKcNJXLyL8Q6SBB98HH3Ic3MP3fBsNhGP7PpCmmfCJATnwwBy6nO7tG5XtF57D3PGYtzvtdtmkodRpuimHsyfG6P2h3yTGj0IcmnRY2j3SFQ6PTu7aPESYmiswoEqn1WR9y56Ltjyco7F7aHqn2YX+AZROF+VLSXakBjX82hklIMfDT2gt7zeHzef3YLK7X2I1j4Tjx7dX6AdwUudTOHu33TjXjm7pYq6S/EJnY67YAiXB+yhDo/ZD9FwNoBKGhP2kzWdvFPX579NyXb+R+kaGKs5BC4Y5Q4ScnY9QsNTrOtxoAjA43A5oSM2Ofr8KdDSi4cPfotygjwHiqsY0gN6HdnL1zr66NJ5kwWhMcLq4piYr/ocwdf+GH0er/G4B/BMJB9IkE1yTzeDG5JTWkISqUgJKglSjBH9+48OlHPfhSAl5Q4iSUcYCs7TTzOZPOmmfR/hXwv8Pk9vgaoofi8sKWU6Aezn8+MitBahp0EMeqVZkquXz1MVAArisgykEQsbeinekZBY+P6jGEKJu0614rTbubz5x5zt0n2yUKT2m3MMY+v6TRmw87BDzgKzoY3qebQ61ZxbO37fGZv6uON63LNr6hSHynNt2i2Rd2g1MC3JRz8AAVE0iTSDd+ZRl5WRnKBr/wyaOAp7/MXNLoLVR1j4TrviLR2m5WQC6hpFCY5eKtQBZEMqpl5rLeXtbSdmwGjdnb3RjfxgHioV0KNK1qvKSFyEyCWTjr9zoOwS8PlIIh+cXkEUrcKSbHHmgLDRGZh19a49ayF3xVoAiDpzAGC2qJcM77D2A94s1SLBdkQhTFkclk7TvcgoRJrFl3ImVvXsq1lyWUn8c2kX1Wz3jo5k9P6jQN5EAm/5CT9SMSkm4kdS+e5uetSgYbrwKIhv8NMxx8Abv/UNWMVa130EICKgQjjU1PvNJ6HnPhF4koB4+WUrdEEC3YR2+IMk5mdX4i6tSbPsINeeppeEDr5t8cp+pZcMRjKllv1Vn9dpCg6xehWfZ99+1pHRGPolkECIFHQEYWFBsdK5y2uCrWYokM2DOq5dP8emiYAZzPWH0wbWav+FIwlAnwHgXdD1iXPgKKJdYgLqf4fy5LOh9IWaiWIZLSnb6CycQacW49HcFOCiVoFDd1W0fbSXICsrdX8/443xDUW+ffvJbSEMYptQoktVsH+5Vigah+w5vK//GW9myfdog57yR6Hsx2F59wTny5k0NCETlfmOe1ts1G8PcUyJUrXkifGLO4/sP8FbVYVdwlHKZG957o/YpTDRKGvmYI98DxCe4EJGg1GURwSuVIgByZ8tSv1EbWH0BhRQmGot1+BBmroW+oL2H7asj3xQ8gA1kmAofoALfl2ldW9V/GiFdzcLJyZrtGrfiqfg12n8SpGr/yy12+XFJOCXRhiC/vM3xCDuXkJISxxMyxjwUx0H0FNhlguuOYwGEhkrPRoM3j/Dx5ChRz5Xnf3aFOMhtlMKjgXB3C3v0T0r7pzuM0RzIHIoHKSrF2bpHGgvjI7amJWlvelzAHRCplF6lPNv8IKkQPwPa49EUeSFNLLjVk/IsKAtG73Q18h+iiICPkzlYnMRuMgFuSbqmdMJHzRW3Li3AKLNzTdDo44S+zwspETAXbKdBQBheIiFHk7pQNtRAvLpR7ZY9P2iNxxDzsAQ76uHxzzaXdaVVvTg1m7TVRBIOxQw0l8EXb+MthsZUfeHlLX7Sb9PzVPg2xo47qdW6NGamwM/xb+1fSpwtyPhcNgJYDImYqDVFEnKTNXCgGi2dg/AFHoNImRx0GhS1sNyHVSyZZLLv/MwcALaI3A6nh00jixTJNQYCAGRPcCPOdNWvFKCVqAERKzfCsq1CfcAfPKIYQjZuv7G3Yd9mCQMeVPG0dzzlTL+zA7SmJtjEPHtfiBrHF3JQPMQIyo0GcQ8GHBYSIOJBhohdleJK8kXEnDQw1NFfQHoC7RQOV49DaTPQ/BMHKlGaSULUqL70yirWjDVQOktbRpqXM5cXWhzz4NIAx1BufCkTuKcNhjfrsB+El0+SgnklrZS7Zsb8l4tbVyeGax870s4WZjf3dC51BWrCT0MkFCCEMl4ae64HYKC3oO0X7VedYMS4x9pyf55xFqKAnxJ0Y9UHXskSkffdWLsL5AlCQCCDL3wAQoY8crxca56BsFbKxhemOuS1bkfsCCOkuLdAJFIMsBc9VyW+vsklx2R6wLy0FMJqSUIVTmlN5IUVNHGf/hNb8CHLE84WXyd8ATMalJfFr+cIkzEMRKkhiAyHcHU7YNG5zHpH+g6n2djRNzaEJuY14Dr+oyBZ5V0CzTw5lyHyD0//0AW3kpGnJPXJNNk+aZiJXn3lGboCU/YJ73Ixr/gJnLg7nG9Bg9QnrA7Tqnk/glLkRIMeXZ6OeKlaDWhcDd+Kaku4lRsc6X8DLHUgoZQizLgv+0KAREInijr1Q3qiPgSMtCpwVlbAAajOLpAy41dc/Sg4Py7wWCzC2ij2WpJ1IFSDEIU8j0/HC2icbGKSuCbKxZ4xlvTeqFrJK5fZ1M+NE29eSK/5PtWxbTFOxkLEwoSSCf4kk3eKivrkJOyG8ToswynwPgy9u3pCc7gUJCAqfntc0BkNgFZzDGSwwbwGlaFqyCqh3lvhOFQBDLgNZUOHZTJRnQEZ/EdHeR0uZEyJDczIBPcopEo7/sIQAA4UmxVE9C6/3eJvQ4JLf/Coy+t2APCj4QCYGLAzNLn+VwjagB3KxhA0aPkR+Ug6GTN1Vk0crkdAQ5REXYeR9kKHAmdqjsQSJSyyyRj01n0ekKGBjtZ0FFL/1NRqAaQrQ+MFMttpH561XubrAUbehwj18Sf/eqrkEjWJGTmCZxKydFcLbEGydhnus4cJEQyKXbsIbQgNBkpQJLvmwfA6oPCY7LXKVQCRb0BvOr8Iv0rfo0/sH/wmnXU5vNYWDqICiTl0dRH7LLDMO9rWpNG3PWfch0xpDd0YNoNo2DtRCJ/eryx0NnRjetYKThBN2IuyWSj9MX+Owl+mBoVSmKjgPGYHtiUG4uo6kPgmJia3RyXmeWhW1oQ1iObpE/rVeCtwbUEbsCEcsVAzYwJEghFDfUHgyFJwSi8ja+IIKqrkdn6IqILwOVohLwyV3r/RMBQGqNNFuIhijZKm/IAvWrUcy2jhp6VydDU6FUYQeEwk9SbsNG6MhxkEYB8eYpVLZQSZwA+Nt0TxbxWoTdV7PQUfzlVegQAeLuRwTWdbN2LP2dcduwC7JD+LO8yPLzzReEB00vOTfHGwLFYbLM+Rlkjr27JyjsM51bEdpkXaq8st8QDbXgV0Ouqwl5BoEfJo1raPe2bN393+j5ljCYxRNpeyqRPgeVrJ/GIGOA4SnRPsSZXSOHCUoNVSNIMTpTBb6Cs+a6FkVrS4ebxCXru80hBu6AdlA0FsAKmEbBzajuTx7Pw1Zd9Odi0Qku2pJ+3o+p/oJ2qnpAiRFKlgRBm+i6dzrs64BpkWx0yNdP4eDNTiv1mzBUHzvaAr2m7EmXoxctnDTpgK+yVRsVK+EEQU9JDzI1fubAY8PW8Vkx7M1+lJiFVomOkyG8ceASzw8S0PQtxud8rN0m7MQSyshmQVyz3a1g9yG8hzCrjLA40S2FiCZ1khfEA1FWSQ1wpBPgxZGNoheawJcEa4WCJUhAqpWrchRBBi5o7YDigGO69qBOTfGIqcGxcUQksa1EIMdGJ5QTr2F84gAO8faZKqwnFKznFLFgOlEj6WJ+scuHATMCDwSpo5wRLDglK80hYpyXjRO9pTH0JtbKcOXP/IDPyKbMRTD04m8Ilf24EiJct4ittCfI/iZIKrSSRY8zv+pQsCEvzBsDtXKXiVE3isihyhWKGQIWh1qk1kZWIKComGTK3qnGw5r6/gbqTDVkox29vwm2TRt1/pbAn+I7OvMNai8nZv0cEBjt++bmUcPQZH4riJjozHkq+TgZoyEABdu/hh6Wk55AJII1FE+xpIRx+dR95DLgAoWorQ8wfyOkuzMQstjF+xD3uKMYASzrrdakZSyZ9jmTXlUPTU1v0
*/