/* boost random/lognormal_distribution.hpp header file
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

#ifndef BOOST_RANDOM_LOGNORMAL_DISTRIBUTION_HPP
#define BOOST_RANDOM_LOGNORMAL_DISTRIBUTION_HPP

#include <boost/config/no_tr1/cmath.hpp>      // std::exp, std::sqrt
#include <cassert>
#include <iosfwd>
#include <istream>
#include <boost/limits.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/normal_distribution.hpp>

namespace boost {
namespace random {

/**
 * Instantiations of class template lognormal_distribution model a
 * \random_distribution. Such a distribution produces random numbers
 * with \f$\displaystyle p(x) = \frac{1}{x s \sqrt{2\pi}} e^{\frac{-\left(\log(x)-m\right)^2}{2s^2}}\f$
 * for x > 0.
 *
 * @xmlwarning
 * This distribution has been updated to match the C++ standard.
 * Its behavior has changed from the original
 * boost::lognormal_distribution.  A backwards compatible
 * version is provided in namespace boost.
 * @endxmlwarning
 */
template<class RealType = double>
class lognormal_distribution
{
public:
    typedef typename normal_distribution<RealType>::input_type input_type;
    typedef RealType result_type;

    class param_type
    {
    public:

        typedef lognormal_distribution distribution_type;

        /** Constructs the parameters of a lognormal_distribution. */
        explicit param_type(RealType m_arg = RealType(0.0),
                            RealType s_arg = RealType(1.0))
          : _m(m_arg), _s(s_arg) {}

        /** Returns the "m" parameter of the distribution. */
        RealType m() const { return _m; }

        /** Returns the "s" parameter of the distribution. */
        RealType s() const { return _s; }

        /** Writes the parameters to a std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._m << " " << parm._s;
            return os;
        }

        /** Reads the parameters from a std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            is >> parm._m >> std::ws >> parm._s;
            return is;
        }

        /** Returns true if the two sets of parameters are equal. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._m == rhs._m && lhs._s == rhs._s; }

        /** Returns true if the two sets of parameters are different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:
        RealType _m;
        RealType _s;
    };

    /**
     * Constructs a lognormal_distribution. @c m and @c s are the
     * parameters of the distribution.
     */
    explicit lognormal_distribution(RealType m_arg = RealType(0.0),
                                    RealType s_arg = RealType(1.0))
      : _normal(m_arg, s_arg) {}

    /**
     * Constructs a lognormal_distribution from its parameters.
     */
    explicit lognormal_distribution(const param_type& parm)
      : _normal(parm.m(), parm.s()) {}

    // compiler-generated copy ctor and assignment operator are fine

    /** Returns the m parameter of the distribution. */
    RealType m() const { return _normal.mean(); }
    /** Returns the s parameter of the distribution. */
    RealType s() const { return _normal.sigma(); }

    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return RealType(0); }
    /** Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return (std::numeric_limits<RealType>::infinity)(); }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(m(), s()); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        typedef normal_distribution<RealType> normal_type;
        typename normal_type::param_type normal_param(parm.m(), parm.s());
        _normal.param(normal_param);
    }
    
    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { _normal.reset(); }

    /**
     * Returns a random variate distributed according to the
     * lognormal distribution.
     */
    template<class Engine>
    result_type operator()(Engine& eng)
    {
        using std::exp;
        return exp(_normal(eng));
    }

    /**
     * Returns a random variate distributed according to the
     * lognormal distribution with parameters specified by param.
     */
    template<class Engine>
    result_type operator()(Engine& eng, const param_type& parm)
    { return lognormal_distribution(parm)(eng); }

    /** Writes the distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, lognormal_distribution, ld)
    {
        os << ld._normal;
        return os;
    }

    /** Reads the distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, lognormal_distribution, ld)
    {
        is >> ld._normal;
        return is;
    }

    /**
     * Returns true if the two distributions will produce identical
     * sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(lognormal_distribution, lhs, rhs)
    { return lhs._normal == rhs._normal; }

    /**
     * Returns true if the two distributions may produce different
     * sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(lognormal_distribution)

private:
    normal_distribution<result_type> _normal;
};

} // namespace random

/// \cond show_deprecated

/**
 * Provided for backwards compatibility.  This class is
 * deprecated.  It provides the old behavior of lognormal_distribution with
 * \f$\displaystyle p(x) = \frac{1}{x \sigma_N \sqrt{2\pi}} e^{\frac{-\left(\log(x)-\mu_N\right)^2}{2\sigma_N^2}}\f$
 * for x > 0, where \f$\displaystyle \mu_N = \log\left(\frac{\mu^2}{\sqrt{\sigma^2 + \mu^2}}\right)\f$ and
 * \f$\displaystyle \sigma_N = \sqrt{\log\left(1 + \frac{\sigma^2}{\mu^2}\right)}\f$.
 */
template<class RealType = double>
class lognormal_distribution
{
public:
    typedef typename normal_distribution<RealType>::input_type input_type;
    typedef RealType result_type;

    lognormal_distribution(RealType mean_arg = RealType(1.0),
                           RealType sigma_arg = RealType(1.0))
      : _mean(mean_arg), _sigma(sigma_arg)
    {
        init();
    }
    RealType mean() const { return _mean; }
    RealType sigma() const { return _sigma; }
    void reset() { _normal.reset(); }
    template<class Engine>
    RealType operator()(Engine& eng)
    {
        using std::exp;
        return exp(_normal(eng) * _nsigma + _nmean);
    }
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, lognormal_distribution, ld)
    {
        os << ld._normal << " " << ld._mean << " " << ld._sigma;
        return os;
    }
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, lognormal_distribution, ld)
    {
        is >> ld._normal >> std::ws >> ld._mean >> std::ws >> ld._sigma;
        ld.init();
        return is;
    }
private:
    /// \cond show_private
    void init()
    {
        using std::log;
        using std::sqrt;
        _nmean = log(_mean*_mean/sqrt(_sigma*_sigma + _mean*_mean));
        _nsigma = sqrt(log(_sigma*_sigma/_mean/_mean+result_type(1)));
    }
    RealType _mean;
    RealType _sigma;
    RealType _nmean;
    RealType _nsigma;
    normal_distribution<RealType> _normal;
    /// \endcond
};

/// \endcond

} // namespace boost

#endif // BOOST_RANDOM_LOGNORMAL_DISTRIBUTION_HPP

/* lognormal_distribution.hpp
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
*/