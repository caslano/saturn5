/* boost random/cauchy_distribution.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
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

#ifndef BOOST_RANDOM_CAUCHY_DISTRIBUTION_HPP
#define BOOST_RANDOM_CAUCHY_DISTRIBUTION_HPP

#include <boost/config/no_tr1/cmath.hpp>
#include <iosfwd>
#include <istream>
#include <boost/limits.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/uniform_01.hpp>

namespace boost {
namespace random {

// Cauchy distribution: 

/**
 * The cauchy distribution is a continuous distribution with two
 * parameters, median and sigma.
 *
 * It has \f$\displaystyle p(x) = \frac{\sigma}{\pi(\sigma^2 + (x-m)^2)}\f$
 */
template<class RealType = double>
class cauchy_distribution
{
public:
    typedef RealType input_type;
    typedef RealType result_type;

    class param_type
    {
    public:

        typedef cauchy_distribution distribution_type;

        /** Constructs the parameters of the cauchy distribution. */
        explicit param_type(RealType median_arg = RealType(0.0),
                            RealType sigma_arg = RealType(1.0))
          : _median(median_arg), _sigma(sigma_arg) {}

        // backwards compatibility for Boost.Random

        /** Returns the median of the distribution. */
        RealType median() const { return _median; }
        /** Returns the sigma parameter of the distribution. */
        RealType sigma() const { return _sigma; }

        // The new names in C++0x.

        /** Returns the median of the distribution. */
        RealType a() const { return _median; }
        /** Returns the sigma parameter of the distribution. */
        RealType b() const { return _sigma; }

        /** Writes the parameters to a std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._median << " " << parm._sigma;
            return os;
        }

        /** Reads the parameters from a std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            is >> parm._median >> std::ws >> parm._sigma;
            return is;
        }

        /** Returns true if the two sets of parameters are equal. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._median == rhs._median && lhs._sigma == rhs._sigma; }

        /** Returns true if the two sets of parameters are different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:
        RealType _median;
        RealType _sigma;
    };

    /**
     * Constructs a \cauchy_distribution with the paramters @c median
     * and @c sigma.
     */
    explicit cauchy_distribution(RealType median_arg = RealType(0.0), 
                                 RealType sigma_arg = RealType(1.0))
      : _median(median_arg), _sigma(sigma_arg) { }
    
    /**
     * Constructs a \cauchy_distribution from it's parameters.
     */
    explicit cauchy_distribution(const param_type& parm)
      : _median(parm.median()), _sigma(parm.sigma()) { }

    // compiler-generated copy ctor and assignment operator are fine

    // backwards compatibility for Boost.Random

    /** Returns: the "median" parameter of the distribution */
    RealType median() const { return _median; }
    /** Returns: the "sigma" parameter of the distribution */
    RealType sigma() const { return _sigma; }
    
    // The new names in C++0x

    /** Returns: the "median" parameter of the distribution */
    RealType a() const { return _median; }
    /** Returns: the "sigma" parameter of the distribution */
    RealType b() const { return _sigma; }

    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return -(std::numeric_limits<RealType>::infinity)(); }

    /** Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return (std::numeric_limits<RealType>::infinity)(); }

    param_type param() const { return param_type(_median, _sigma); }

    void param(const param_type& parm)
    {
        _median = parm.median();
        _sigma = parm.sigma();
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

    /**
     * Returns: A random variate distributed according to the
     * cauchy distribution.
     */
    template<class Engine>
    result_type operator()(Engine& eng)
    {
        // Can we have a boost::mathconst please?
        const result_type pi = result_type(3.14159265358979323846);
        using std::tan;
        RealType val = uniform_01<RealType>()(eng)-result_type(0.5);
        return _median + _sigma * tan(pi*val);
    }

    /**
     * Returns: A random variate distributed according to the
     * cauchy distribution with parameters specified by param.
     */
    template<class Engine>
    result_type operator()(Engine& eng, const param_type& parm)
    {
        return cauchy_distribution(parm)(eng);
    }

    /**
     * Writes the distribution to a @c std::ostream.
     */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, cauchy_distribution, cd)
    {
        os << cd._median << " " << cd._sigma;
        return os;
    }

    /**
     * Reads the distribution from a @c std::istream.
     */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, cauchy_distribution, cd)
    {
        is >> cd._median >> std::ws >> cd._sigma;
        return is;
    }

    /**
     * Returns true if the two distributions will produce
     * identical sequences of values, given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(cauchy_distribution, lhs, rhs)
    { return lhs._median == rhs._median && lhs._sigma == rhs._sigma; }

    /**
     * Returns true if the two distributions may produce
     * different sequences of values, given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(cauchy_distribution)

private:
    RealType _median;
    RealType _sigma;
};

} // namespace random

using random::cauchy_distribution;

} // namespace boost

#endif // BOOST_RANDOM_CAUCHY_DISTRIBUTION_HPP

/* cauchy_distribution.hpp
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
*/