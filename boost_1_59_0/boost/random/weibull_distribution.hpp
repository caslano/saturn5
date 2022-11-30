/* boost random/weibull_distribution.hpp header file
 *
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_WEIBULL_DISTRIBUTION_HPP
#define BOOST_RANDOM_WEIBULL_DISTRIBUTION_HPP

#include <boost/config/no_tr1/cmath.hpp>
#include <iosfwd>
#include <istream>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/uniform_01.hpp>

namespace boost {
namespace random {

/**
 * The Weibull distribution is a real valued distribution with two
 * parameters a and b, producing values >= 0.
 *
 * It has \f$\displaystyle p(x) = \frac{a}{b}\left(\frac{x}{b}\right)^{a-1}e^{-\left(\frac{x}{b}\right)^a}\f$.
 */
template<class RealType = double>
class weibull_distribution {
public:
    typedef RealType result_type;
    typedef RealType input_type;

    class param_type {
    public:
        typedef weibull_distribution distribution_type;

        /**
         * Constructs a @c param_type from the "a" and "b" parameters
         * of the distribution.
         *
         * Requires: a > 0 && b > 0
         */
        explicit param_type(RealType a_arg = 1.0, RealType b_arg = 1.0)
          : _a(a_arg), _b(b_arg)
        {}

        /** Returns the "a" parameter of the distribtuion. */
        RealType a() const { return _a; }
        /** Returns the "b" parameter of the distribution. */
        RealType b() const { return _b; }

        /** Writes a @c param_type to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        { os << parm._a << ' ' << parm._b; return os; }

        /** Reads a @c param_type from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        { is >> parm._a >> std::ws >> parm._b; return is; }

        /** Returns true if the two sets of parameters are the same. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._a == rhs._a && lhs._b == rhs._b; }
        
        /** Returns true if the two sets of parameters are the different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:
        RealType _a;
        RealType _b;
    };

    /**
     * Constructs a @c weibull_distribution from its "a" and "b" parameters.
     *
     * Requires: a > 0 && b > 0
     */
    explicit weibull_distribution(RealType a_arg = 1.0, RealType b_arg = 1.0)
      : _a(a_arg), _b(b_arg)
    {}
    /** Constructs a @c weibull_distribution from its parameters. */
    explicit weibull_distribution(const param_type& parm)
      : _a(parm.a()), _b(parm.b())
    {}

    /**
     * Returns a random variate distributed according to the
     * @c weibull_distribution.
     */
    template<class URNG>
    RealType operator()(URNG& urng) const
    {
        using std::pow;
        using std::log;
        return _b*pow(-log(1 - uniform_01<RealType>()(urng)), 1/_a);
    }

    /**
     * Returns a random variate distributed accordint to the Weibull
     * distribution with parameters specified by @c param.
     */
    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return weibull_distribution(parm)(urng);
    }

    /** Returns the "a" parameter of the distribution. */
    RealType a() const { return _a; }
    /** Returns the "b" parameter of the distribution. */
    RealType b() const { return _b; }

    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return 0; }
    /** Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return std::numeric_limits<RealType>::infinity(); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_a, _b); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        _a = parm.a();
        _b = parm.b();
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

    /** Writes a @c weibull_distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, weibull_distribution, wd)
    {
        os << wd.param();
        return os;
    }

    /** Reads a @c weibull_distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, weibull_distribution, wd)
    {
        param_type parm;
        if(is >> parm) {
            wd.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two instances of @c weibull_distribution will
     * return identical sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(weibull_distribution, lhs, rhs)
    { return lhs._a == rhs._a && lhs._b == rhs._b; }
    
    /**
     * Returns true if the two instances of @c weibull_distribution will
     * return different sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(weibull_distribution)

private:
    RealType _a;
    RealType _b;
};

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_WEIBULL_DISTRIBUTION_HPP

/* weibull_distribution.hpp
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
*/