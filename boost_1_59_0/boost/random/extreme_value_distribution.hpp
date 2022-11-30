/* boost random/extreme_value_distribution.hpp header file
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

#ifndef BOOST_RANDOM_EXTREME_VALUE_DISTRIBUTION_HPP
#define BOOST_RANDOM_EXTREME_VALUE_DISTRIBUTION_HPP

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
 * The extreme value distribution is a real valued distribution with two
 * parameters a and b.
 *
 * It has \f$\displaystyle p(x) = \frac{1}{b}e^{\frac{a-x}{b} - e^\frac{a-x}{b}}\f$.
 */
template<class RealType = double>
class extreme_value_distribution {
public:
    typedef RealType result_type;
    typedef RealType input_type;

    class param_type {
    public:
        typedef extreme_value_distribution distribution_type;

        /**
         * Constructs a @c param_type from the "a" and "b" parameters
         * of the distribution.
         *
         * Requires: b > 0
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
     * Constructs an @c extreme_value_distribution from its "a" and "b" parameters.
     *
     * Requires: b > 0
     */
    explicit extreme_value_distribution(RealType a_arg = 1.0, RealType b_arg = 1.0)
      : _a(a_arg), _b(b_arg)
    {}
    /** Constructs an @c extreme_value_distribution from its parameters. */
    explicit extreme_value_distribution(const param_type& parm)
      : _a(parm.a()), _b(parm.b())
    {}

    /**
     * Returns a random variate distributed according to the
     * @c extreme_value_distribution.
     */
    template<class URNG>
    RealType operator()(URNG& urng) const
    {
        using std::log;
        return _a - log(-log(uniform_01<RealType>()(urng))) * _b;
    }

    /**
     * Returns a random variate distributed accordint to the extreme
     * value distribution with parameters specified by @c param.
     */
    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return extreme_value_distribution(parm)(urng);
    }

    /** Returns the "a" parameter of the distribution. */
    RealType a() const { return _a; }
    /** Returns the "b" parameter of the distribution. */
    RealType b() const { return _b; }

    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return -std::numeric_limits<RealType>::infinity(); }
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

    /** Writes an @c extreme_value_distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, extreme_value_distribution, wd)
    {
        os << wd.param();
        return os;
    }

    /** Reads an @c extreme_value_distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, extreme_value_distribution, wd)
    {
        param_type parm;
        if(is >> parm) {
            wd.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two instances of @c extreme_value_distribution will
     * return identical sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(extreme_value_distribution, lhs, rhs)
    { return lhs._a == rhs._a && lhs._b == rhs._b; }
    
    /**
     * Returns true if the two instances of @c extreme_value_distribution will
     * return different sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(extreme_value_distribution)

private:
    RealType _a;
    RealType _b;
};

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_EXTREME_VALUE_DISTRIBUTION_HPP

/* extreme_value_distribution.hpp
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
*/