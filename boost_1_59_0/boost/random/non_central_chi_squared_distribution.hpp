/* boost random/non_central_chi_squared_distribution.hpp header file
 *
 * Copyright Thijs van den Berg 2014
 * 
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_NON_CENTRAL_CHI_SQUARED_DISTRIBUTION_HPP
#define BOOST_RANDOM_NON_CENTRAL_CHI_SQUARED_DISTRIBUTION_HPP

#include <boost/config/no_tr1/cmath.hpp>
#include <iosfwd>
#include <istream>
#include <boost/limits.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/uniform_real_distribution.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/chi_squared_distribution.hpp>
#include <boost/random/poisson_distribution.hpp>

namespace boost {
namespace random {

/**
 * The noncentral chi-squared distribution is a real valued distribution with
 * two parameter, @c k and @c lambda.  The distribution produces values > 0.
 *
 * This is the distribution of the sum of squares of k Normal distributed
 * variates each with variance one and \f$\lambda\f$ the sum of squares of the
 * normal means.
 *
 * The distribution function is
 * \f$\displaystyle P(x) = \frac{1}{2} e^{-(x+\lambda)/2} \left( \frac{x}{\lambda} \right)^{k/4-1/2} I_{k/2-1}( \sqrt{\lambda x} )\f$.
 *  where  \f$\displaystyle I_\nu(z)\f$ is a modified Bessel function of the
 * first kind.
 *
 * The algorithm is taken from
 *
 *  @blockquote
 *  "Monte Carlo Methods in Financial Engineering", Paul Glasserman,
 *  2003, XIII, 596 p, Stochastic Modelling and Applied Probability, Vol. 53,
 *  ISBN 978-0-387-21617-1, p 124, Fig. 3.5.
 *  @endblockquote
 */
template <typename RealType = double>
class non_central_chi_squared_distribution {
public:
    typedef RealType result_type;
    typedef RealType input_type;
    
    class param_type {
    public:
        typedef non_central_chi_squared_distribution distribution_type;
        
        /**
         * Constructs the parameters of a non_central_chi_squared_distribution.
         * @c k and @c lambda are the parameter of the distribution.
         *
         * Requires: k > 0 && lambda > 0
         */
        explicit
        param_type(RealType k_arg = RealType(1), RealType lambda_arg = RealType(1))
        : _k(k_arg), _lambda(lambda_arg)
        {
            BOOST_ASSERT(k_arg > RealType(0));
            BOOST_ASSERT(lambda_arg > RealType(0));
        }
        
        /** Returns the @c k parameter of the distribution */
        RealType k() const { return _k; }
        
        /** Returns the @c lambda parameter of the distribution */
        RealType lambda() const { return _lambda; }

        /** Writes the parameters of the distribution to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._k << ' ' << parm._lambda;
            return os;
        }
        
        /** Reads the parameters of the distribution from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            is >> parm._k >> std::ws >> parm._lambda;
            return is;
        }

        /** Returns true if the parameters have the same values. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._k == rhs._k && lhs._lambda == rhs._lambda; }
        
        /** Returns true if the parameters have different values. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)
        
    private:
        RealType _k;
        RealType _lambda;
    };

    /**
     * Construct a @c non_central_chi_squared_distribution object. @c k and
     * @c lambda are the parameter of the distribution.
     *
     * Requires: k > 0 && lambda > 0
     */
    explicit
    non_central_chi_squared_distribution(RealType k_arg = RealType(1), RealType lambda_arg = RealType(1))
      : _param(k_arg, lambda_arg)
    {
        BOOST_ASSERT(k_arg > RealType(0));
        BOOST_ASSERT(lambda_arg > RealType(0));
    }

    /**
     * Construct a @c non_central_chi_squared_distribution object from the parameter.
     */
    explicit
    non_central_chi_squared_distribution(const param_type& parm)
      : _param( parm )
    { }
    
    /**
     * Returns a random variate distributed according to the
     * non central chi squared distribution specified by @c param.
     */
    template<typename URNG>
    RealType operator()(URNG& eng, const param_type& parm) const
    { return non_central_chi_squared_distribution(parm)(eng); }
    
    /**
     * Returns a random variate distributed according to the
     * non central chi squared distribution.
     */
    template<typename URNG> 
    RealType operator()(URNG& eng) 
    {
        using std::sqrt;
        if (_param.k() > 1) {
            boost::random::normal_distribution<RealType> n_dist;
            boost::random::chi_squared_distribution<RealType> c_dist(_param.k() - RealType(1));
            RealType _z = n_dist(eng);
            RealType _x = c_dist(eng);
            RealType term1 = _z + sqrt(_param.lambda());
            return term1*term1 + _x;
        }
        else {
            boost::random::poisson_distribution<> p_dist(_param.lambda()/RealType(2));
            boost::random::poisson_distribution<>::result_type _p = p_dist(eng);
            boost::random::chi_squared_distribution<RealType> c_dist(_param.k() + RealType(2)*_p);
            return c_dist(eng);
        }
    }

    /** Returns the @c k parameter of the distribution. */
    RealType k() const { return _param.k(); }
    
    /** Returns the @c lambda parameter of the distribution. */
    RealType lambda() const { return _param.lambda(); }
    
    /** Returns the parameters of the distribution. */
    param_type param() const { return _param; }
    
    /** Sets parameters of the distribution. */
    void param(const param_type& parm) { _param = parm; }
    
    /** Resets the distribution, so that subsequent uses does not depend on values already produced by it.*/
    void reset() {}
    
    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION() const
    { return RealType(0); }
    
    /** Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION() const
    { return (std::numeric_limits<RealType>::infinity)(); }

    /** Writes the parameters of the distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, non_central_chi_squared_distribution, dist)
    {
        os << dist.param();
        return os;
    }
    
    /** reads the parameters of the distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, non_central_chi_squared_distribution, dist)
    {
        param_type parm;
        if(is >> parm) {
            dist.param(parm);
        }
        return is;
    }

    /** Returns true if two distributions have the same parameters and produce 
        the same sequence of random numbers given equal generators.*/
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(non_central_chi_squared_distribution, lhs, rhs)
    { return lhs.param() == rhs.param(); }
    
    /** Returns true if two distributions have different parameters and/or can produce 
       different sequences of random numbers given equal generators.*/
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(non_central_chi_squared_distribution)
    
private:

    /// @cond show_private
    param_type  _param;
    /// @endcond
};

} // namespace random
} // namespace boost

#endif

/* non_central_chi_squared_distribution.hpp
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
*/