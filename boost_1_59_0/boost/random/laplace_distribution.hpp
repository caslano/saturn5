/* boost random/laplace_distribution.hpp header file
 *
 * Copyright Steven Watanabe 2014
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_LAPLACE_DISTRIBUTION_HPP
#define BOOST_RANDOM_LAPLACE_DISTRIBUTION_HPP

#include <cassert>
#include <istream>
#include <iosfwd>
#include <boost/random/detail/operators.hpp>
#include <boost/random/exponential_distribution.hpp>

namespace boost {
namespace random {

/**
 * The laplace distribution is a real-valued distribution with
 * two parameters, mean and beta.
 *
 * It has \f$\displaystyle p(x) = \frac{e^-{\frac{|x-\mu|}{\beta}}}{2\beta}\f$.
 */
template<class RealType = double>
class laplace_distribution {
public:
    typedef RealType result_type;
    typedef RealType input_type;

    class param_type {
    public:
        typedef laplace_distribution distribution_type;

        /**
         * Constructs a @c param_type from the "mean" and "beta" parameters
         * of the distribution.
         */
        explicit param_type(RealType mean_arg = RealType(0.0),
                            RealType beta_arg = RealType(1.0))
          : _mean(mean_arg), _beta(beta_arg)
        {}

        /** Returns the "mean" parameter of the distribtuion. */
        RealType mean() const { return _mean; }
        /** Returns the "beta" parameter of the distribution. */
        RealType beta() const { return _beta; }

        /** Writes a @c param_type to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        { os << parm._mean << ' ' << parm._beta; return os; }

        /** Reads a @c param_type from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        { is >> parm._mean >> std::ws >> parm._beta; return is; }

        /** Returns true if the two sets of parameters are the same. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._mean == rhs._mean && lhs._beta == rhs._beta; }
        
        /** Returns true if the two sets of parameters are the different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:
        RealType _mean;
        RealType _beta;
    };

    /**
     * Constructs an @c laplace_distribution from its "mean" and "beta" parameters.
     */
    explicit laplace_distribution(RealType mean_arg = RealType(0.0),
                               RealType beta_arg = RealType(1.0))
      : _mean(mean_arg), _beta(beta_arg)
    {}
    /** Constructs an @c laplace_distribution from its parameters. */
    explicit laplace_distribution(const param_type& parm)
      : _mean(parm.mean()), _beta(parm.beta())
    {}

    /**
     * Returns a random variate distributed according to the
     * laplace distribution.
     */
    template<class URNG>
    RealType operator()(URNG& urng) const
    {
        RealType exponential = exponential_distribution<RealType>()(urng);
        if(uniform_01<RealType>()(urng) < 0.5)
            exponential = -exponential;
        return _mean + _beta * exponential;
    }

    /**
     * Returns a random variate distributed accordint to the laplace
     * distribution with parameters specified by @c param.
     */
    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return laplace_distribution(parm)(urng);
    }

    /** Returns the "mean" parameter of the distribution. */
    RealType mean() const { return _mean; }
    /** Returns the "beta" parameter of the distribution. */
    RealType beta() const { return _beta; }

    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return RealType(-std::numeric_limits<RealType>::infinity()); }
    /** Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return RealType(std::numeric_limits<RealType>::infinity()); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_mean, _beta); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        _mean = parm.mean();
        _beta = parm.beta();
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

    /** Writes an @c laplace_distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, laplace_distribution, wd)
    {
        os << wd.param();
        return os;
    }

    /** Reads an @c laplace_distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, laplace_distribution, wd)
    {
        param_type parm;
        if(is >> parm) {
            wd.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two instances of @c laplace_distribution will
     * return identical sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(laplace_distribution, lhs, rhs)
    { return lhs._mean == rhs._mean && lhs._beta == rhs._beta; }
    
    /**
     * Returns true if the two instances of @c laplace_distribution will
     * return different sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(laplace_distribution)

private:
    RealType _mean;
    RealType _beta;
};

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_LAPLACE_DISTRIBUTION_HPP

/* laplace_distribution.hpp
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
*/