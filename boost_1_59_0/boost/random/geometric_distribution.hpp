/* boost random/geometric_distribution.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_GEOMETRIC_DISTRIBUTION_HPP
#define BOOST_RANDOM_GEOMETRIC_DISTRIBUTION_HPP

#include <boost/config/no_tr1/cmath.hpp>          // std::log
#include <iosfwd>
#include <ios>
#include <boost/assert.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/uniform_01.hpp>

namespace boost {
namespace random {

/**
 * An instantiation of the class template @c geometric_distribution models
 * a \random_distribution.  The distribution produces positive
 * integers which are the number of bernoulli trials
 * with probability @c p required to get one that fails.
 *
 * For the geometric distribution, \f$p(i) = p(1-p)^{i}\f$.
 *
 * @xmlwarning
 * This distribution has been updated to match the C++ standard.
 * Its behavior has changed from the original
 * boost::geometric_distribution.  A backwards compatible
 * wrapper is provided in namespace boost.
 * @endxmlwarning
 */
template<class IntType = int, class RealType = double>
class geometric_distribution
{
public:
    typedef RealType input_type;
    typedef IntType result_type;

    class param_type
    {
    public:

        typedef geometric_distribution distribution_type;

        /** Constructs the parameters with p. */
        explicit param_type(RealType p_arg = RealType(0.5))
          : _p(p_arg)
        {
            BOOST_ASSERT(RealType(0) < _p && _p < RealType(1));
        }

        /** Returns the p parameter of the distribution. */
        RealType p() const { return _p; }

        /** Writes the parameters to a std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._p;
            return os;
        }

        /** Reads the parameters from a std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            double p_in;
            if(is >> p_in) {
                if(p_in > RealType(0) && p_in < RealType(1)) {
                    parm._p = p_in;
                } else {
                    is.setstate(std::ios_base::failbit);
                }
            }
            return is;
        }

        /** Returns true if the two sets of parameters are equal. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._p == rhs._p; }

        /** Returns true if the two sets of parameters are different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)


    private:
        RealType _p;
    };

    /**
     * Contructs a new geometric_distribution with the paramter @c p.
     *
     * Requires: 0 < p < 1
     */
    explicit geometric_distribution(const RealType& p_arg = RealType(0.5))
      : _p(p_arg)
    {
        BOOST_ASSERT(RealType(0) < _p && _p < RealType(1));
        init();
    }

    /** Constructs a new geometric_distribution from its parameters. */
    explicit geometric_distribution(const param_type& parm)
      : _p(parm.p())
    {
        init();
    }

    // compiler-generated copy ctor and assignment operator are fine

    /** Returns: the distribution parameter @c p  */
    RealType p() const { return _p; }

    /** Returns the smallest value that the distribution can produce. */
    IntType min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return IntType(0); }

    /** Returns the largest value that the distribution can produce. */
    IntType max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return (std::numeric_limits<IntType>::max)(); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_p); }

    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        _p = parm.p();
        init();
    }
  
    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

    /**
     * Returns a random variate distributed according to the
     * geometric_distribution.
     */
    template<class Engine>
    result_type operator()(Engine& eng) const
    {
        using std::log;
        using std::floor;
        RealType x = RealType(1) - boost::uniform_01<RealType>()(eng);
        return IntType(floor(log(x) / _log_1mp));
    }

    /**
     * Returns a random variate distributed according to the
     * geometric distribution with parameters specified by param.
     */
    template<class Engine>
    result_type operator()(Engine& eng, const param_type& parm) const
    { return geometric_distribution(parm)(eng); }

    /** Writes the distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, geometric_distribution, gd)
    {
        os << gd._p;
        return os;
    }

    /** Reads the distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, geometric_distribution, gd)
    {
        param_type parm;
        if(is >> parm) {
            gd.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two distributions will produce identical
     * sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(geometric_distribution, lhs, rhs)
    { return lhs._p == rhs._p; }

    /**
     * Returns true if the two distributions may produce different
     * sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(geometric_distribution)

private:

    /// \cond show_private

    void init()
    {
        using std::log;
        _log_1mp = log(1 - _p);
    }

    RealType _p;
    RealType _log_1mp;

    /// \endcond
};

} // namespace random

/// \cond show_deprecated

/**
 * Provided for backwards compatibility.  This class is
 * deprecated.  It provides the old behavior of geometric_distribution
 * with \f$p(i) = (1-p) p^{i-1}\f$.
 */
template<class IntType = int, class RealType = double>
class geometric_distribution
{
public:
    typedef RealType input_type;
    typedef IntType result_type;

    explicit geometric_distribution(RealType p_arg = RealType(0.5))
      : _impl(1 - p_arg) {}

    RealType p() const { return 1 - _impl.p(); }

    void reset() {}

    template<class Engine>
    IntType operator()(Engine& eng) const { return _impl(eng) + IntType(1); }

    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, geometric_distribution, gd)
    {
        os << gd.p();
        return os;
    }

    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, geometric_distribution, gd)
    {
        RealType val;
        if(is >> val) {
            typename impl_type::param_type impl_param(1 - val);
            gd._impl.param(impl_param);
        }
        return is;
    }

private:
    typedef random::geometric_distribution<IntType, RealType> impl_type;
    impl_type _impl;
};

/// \endcond

} // namespace boost

#endif // BOOST_RANDOM_GEOMETRIC_DISTRIBUTION_HPP

/* geometric_distribution.hpp
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
*/