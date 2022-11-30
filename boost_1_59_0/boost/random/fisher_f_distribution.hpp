/* boost random/fisher_f_distribution.hpp header file
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

#ifndef BOOST_RANDOM_FISHER_F_DISTRIBUTION_HPP
#define BOOST_RANDOM_FISHER_F_DISTRIBUTION_HPP

#include <iosfwd>
#include <istream>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/chi_squared_distribution.hpp>

namespace boost {
namespace random {

/**
 * The Fisher F distribution is a real valued distribution with two
 * parameters m and n.
 *
 * It has \f$\displaystyle p(x) =
 *   \frac{\Gamma((m+n)/2)}{\Gamma(m/2)\Gamma(n/2)}
 *   \left(\frac{m}{n}\right)^{m/2}
 *   x^{(m/2)-1} \left(1+\frac{mx}{n}\right)^{-(m+n)/2}
 * \f$.
 */
template<class RealType = double>
class fisher_f_distribution {
public:
    typedef RealType result_type;
    typedef RealType input_type;

    class param_type {
    public:
        typedef fisher_f_distribution distribution_type;

        /**
         * Constructs a @c param_type from the "m" and "n" parameters
         * of the distribution.
         *
         * Requires: m > 0 and n > 0
         */
        explicit param_type(RealType m_arg = RealType(1.0),
                            RealType n_arg = RealType(1.0))
          : _m(m_arg), _n(n_arg)
        {}

        /** Returns the "m" parameter of the distribtuion. */
        RealType m() const { return _m; }
        /** Returns the "n" parameter of the distribution. */
        RealType n() const { return _n; }

        /** Writes a @c param_type to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        { os << parm._m << ' ' << parm._n; return os; }

        /** Reads a @c param_type from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        { is >> parm._m >> std::ws >> parm._n; return is; }

        /** Returns true if the two sets of parameters are the same. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._m == rhs._m && lhs._n == rhs._n; }
        
        /** Returns true if the two sets of parameters are the different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:
        RealType _m;
        RealType _n;
    };

    /**
     * Constructs a @c fisher_f_distribution from its "m" and "n" parameters.
     *
     * Requires: m > 0 and n > 0
     */
    explicit fisher_f_distribution(RealType m_arg = RealType(1.0),
                                   RealType n_arg = RealType(1.0))
      : _impl_m(m_arg), _impl_n(n_arg)
    {}
    /** Constructs an @c fisher_f_distribution from its parameters. */
    explicit fisher_f_distribution(const param_type& parm)
      : _impl_m(parm.m()), _impl_n(parm.n())
    {}

    /**
     * Returns a random variate distributed according to the
     * F distribution.
     */
    template<class URNG>
    RealType operator()(URNG& urng)
    {
        return (_impl_m(urng) * n()) / (_impl_n(urng) * m());
    }

    /**
     * Returns a random variate distributed according to the
     * F distribution with parameters specified by @c param.
     */
    template<class URNG>
    RealType operator()(URNG& urng, const param_type& parm) const
    {
        return fisher_f_distribution(parm)(urng);
    }

    /** Returns the "m" parameter of the distribution. */
    RealType m() const { return _impl_m.n(); }
    /** Returns the "n" parameter of the distribution. */
    RealType n() const { return _impl_n.n(); }

    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return 0; }
    /** Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return std::numeric_limits<RealType>::infinity(); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(m(), n()); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        typedef chi_squared_distribution<RealType> impl_type;
        typename impl_type::param_type m_param(parm.m());
        _impl_m.param(m_param);
        typename impl_type::param_type n_param(parm.n());
        _impl_n.param(n_param);
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

    /** Writes an @c fisher_f_distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, fisher_f_distribution, fd)
    {
        os << fd.param();
        return os;
    }

    /** Reads an @c fisher_f_distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, fisher_f_distribution, fd)
    {
        param_type parm;
        if(is >> parm) {
            fd.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two instances of @c fisher_f_distribution will
     * return identical sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(fisher_f_distribution, lhs, rhs)
    { return lhs._impl_m == rhs._impl_m && lhs._impl_n == rhs._impl_n; }
    
    /**
     * Returns true if the two instances of @c fisher_f_distribution will
     * return different sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(fisher_f_distribution)

private:
    chi_squared_distribution<RealType> _impl_m;
    chi_squared_distribution<RealType> _impl_n;
};

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_EXTREME_VALUE_DISTRIBUTION_HPP

/* fisher_f_distribution.hpp
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
*/