/* boost random/student_t_distribution.hpp header file
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_STUDENT_T_DISTRIBUTION_HPP
#define BOOST_RANDOM_STUDENT_T_DISTRIBUTION_HPP

#include <boost/config/no_tr1/cmath.hpp>
#include <iosfwd>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/chi_squared_distribution.hpp>
#include <boost/random/normal_distribution.hpp>

namespace boost {
namespace random {

/**
 * The Student t distribution is a real valued distribution with one
 * parameter n, the number of degrees of freedom.
 *
 * It has \f$\displaystyle p(x) =
 *   \frac{1}{\sqrt{n\pi}}
 *   \frac{\Gamma((n+1)/2)}{\Gamma(n/2)}
 *   \left(1+\frac{x^2}{n}\right)^{-(n+1)/2}
 * \f$.
 */
template<class RealType = double>
class student_t_distribution {
public:
    typedef RealType result_type;
    typedef RealType input_type;

    class param_type {
    public:
        typedef student_t_distribution distribution_type;

        /**
         * Constructs a @c param_type with "n" degrees of freedom.
         *
         * Requires: n > 0
         */
        explicit param_type(RealType n_arg = RealType(1.0))
          : _n(n_arg)
        {}

        /** Returns the number of degrees of freedom of the distribution. */
        RealType n() const { return _n; }

        /** Writes a @c param_type to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        { os << parm._n; return os; }

        /** Reads a @c param_type from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        { is >> parm._n; return is; }

        /** Returns true if the two sets of parameters are the same. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._n == rhs._n; }
        
        /** Returns true if the two sets of parameters are the different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:
        RealType _n;
    };

    /**
     * Constructs an @c student_t_distribution with "n" degrees of freedom.
     *
     * Requires: n > 0
     */
    explicit student_t_distribution(RealType n_arg = RealType(1.0))
      : _normal(), _chi_squared(n_arg)
    {}
    /** Constructs an @c student_t_distribution from its parameters. */
    explicit student_t_distribution(const param_type& parm)
      : _normal(), _chi_squared(parm.n())
    {}

    /**
     * Returns a random variate distributed according to the
     * Student t distribution.
     */
    template<class URNG>
    RealType operator()(URNG& urng)
    {
        using std::sqrt;
        return _normal(urng) / sqrt(_chi_squared(urng) / n());
    }

    /**
     * Returns a random variate distributed accordint to the Student
     * t distribution with parameters specified by @c param.
     */
    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return student_t_distribution(parm)(urng);
    }

    /** Returns the number of degrees of freedom. */
    RealType n() const { return _chi_squared.n(); }

    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return -std::numeric_limits<RealType>::infinity(); }
    /** Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return std::numeric_limits<RealType>::infinity(); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(n()); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        typedef chi_squared_distribution<RealType> chi_squared_type;
        typename chi_squared_type::param_type chi_squared_param(parm.n());
        _chi_squared.param(chi_squared_param);
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset()
    {
        _normal.reset();
        _chi_squared.reset();
    }

    /** Writes a @c student_t_distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, student_t_distribution, td)
    {
        os << td.param();
        return os;
    }

    /** Reads a @c student_t_distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, student_t_distribution, td)
    {
        param_type parm;
        if(is >> parm) {
            td.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two instances of @c student_t_distribution will
     * return identical sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(student_t_distribution, lhs, rhs)
    { return lhs._normal == rhs._normal && lhs._chi_squared == rhs._chi_squared; }
    
    /**
     * Returns true if the two instances of @c student_t_distribution will
     * return different sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(student_t_distribution)

private:
    normal_distribution<RealType> _normal;
    chi_squared_distribution<RealType> _chi_squared;
};

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_STUDENT_T_DISTRIBUTION_HPP

/* student_t_distribution.hpp
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
*/