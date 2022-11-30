/* boost random/bernoulli_distribution.hpp header file
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

#ifndef BOOST_RANDOM_BERNOULLI_DISTRIBUTION_HPP
#define BOOST_RANDOM_BERNOULLI_DISTRIBUTION_HPP

#include <iosfwd>
#include <boost/assert.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>

namespace boost {
namespace random {

/**
 * Instantiations of class template \bernoulli_distribution model a
 * \random_distribution. Such a random distribution produces bool values
 * distributed with probabilities P(true) = p and P(false) = 1-p. p is
 * the parameter of the distribution.
 */
template<class RealType = double>
class bernoulli_distribution
{
public:
    // In principle, this could work with both integer and floating-point
    // types.  Generating floating-point random numbers in the first
    // place is probably more expensive, so use integer as input.
    typedef int input_type;
    typedef bool result_type;

    class param_type
    {
    public:

        typedef bernoulli_distribution distribution_type;

        /** 
         * Constructs the parameters of the distribution.
         *
         * Requires: 0 <= p <= 1
         */
        explicit param_type(RealType p_arg = RealType(0.5))
          : _p(p_arg)
        {
            BOOST_ASSERT(_p >= 0);
            BOOST_ASSERT(_p <= 1);
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
            is >> parm._p;
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
     * Constructs a \bernoulli_distribution object.
     * p is the parameter of the distribution.
     *
     * Requires: 0 <= p <= 1
     */
    explicit bernoulli_distribution(const RealType& p_arg = RealType(0.5)) 
      : _p(p_arg)
    {
        BOOST_ASSERT(_p >= 0);
        BOOST_ASSERT(_p <= 1);
    }
    /**
     * Constructs \bernoulli_distribution from its parameters
     */
    explicit bernoulli_distribution(const param_type& parm)
      : _p(parm.p()) {}

    // compiler-generated copy ctor and assignment operator are fine

    /**
     * Returns: The "p" parameter of the distribution.
     */
    RealType p() const { return _p; }

    /** Returns the smallest value that the distribution can produce. */
    bool min BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return false; }
    /** Returns the largest value that the distribution can produce. */
    bool max BOOST_PREVENT_MACRO_SUBSTITUTION () const
    { return true; }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_p); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm) { _p = parm.p(); }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

    /**
     * Returns: a random variate distributed according to the
     * \bernoulli_distribution.
     */
    template<class Engine>
    bool operator()(Engine& eng) const
    {
        if(_p == RealType(0))
            return false;
        else
            return RealType(eng() - (eng.min)()) <= _p * RealType((eng.max)()-(eng.min)());
    }

    /**
     * Returns: a random variate distributed according to the
     * \bernoulli_distribution with parameters specified by param.
     */
    template<class Engine>
    bool operator()(Engine& eng, const param_type& parm) const
    {
        return bernoulli_distribution(parm)(eng);
    }

    /**
     * Writes the parameters of the distribution to a @c std::ostream.
     */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, bernoulli_distribution, bd)
    {
        os << bd._p;
        return os;
    }

    /**
     * Reads the parameters of the distribution from a @c std::istream.
     */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, bernoulli_distribution, bd)
    {
        is >> bd._p;
        return is;
    }

    /**
     * Returns true iff the two distributions will produce identical
     * sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(bernoulli_distribution, lhs, rhs)
    { return lhs._p == rhs._p; }
    
    /**
     * Returns true iff the two distributions will produce different
     * sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(bernoulli_distribution)

private:
    RealType _p;
};

} // namespace random

using random::bernoulli_distribution;

} // namespace boost

#endif // BOOST_RANDOM_BERNOULLI_DISTRIBUTION_HPP

/* bernoulli_distribution.hpp
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
*/