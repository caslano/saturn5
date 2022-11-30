/* boost random/uniform_real.hpp header file
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
 *  2001-04-08  added min<max assertion (N. Becker)
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_UNIFORM_REAL_HPP
#define BOOST_RANDOM_UNIFORM_REAL_HPP

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/random/uniform_real_distribution.hpp>

namespace boost {

/**
 * The distribution function uniform_real models a random distribution.
 * On each invocation, it returns a random floating-point value uniformly
 * distributed in the range [min..max).
 *
 * This class is deprecated.  Please use @c uniform_real_distribution in
 * new code.
 */
template<class RealType = double>
class uniform_real : public random::uniform_real_distribution<RealType>
{
    typedef random::uniform_real_distribution<RealType> base_type;
public:

    class param_type : public base_type::param_type
    {
    public:
        typedef uniform_real distribution_type;
        /**
         * Constructs the parameters of a uniform_real distribution.
         *
         * Requires: min <= max
         */
        explicit param_type(RealType min_arg = RealType(0.0),
                            RealType max_arg = RealType(1.0))
          : base_type::param_type(min_arg, max_arg)
        {}
    };

    /**
     * Constructs a uniform_real object. @c min and @c max are the
     * parameters of the distribution.
     *
     * Requires: min <= max
     */
    explicit uniform_real(RealType min_arg = RealType(0.0),
                          RealType max_arg = RealType(1.0))
      : base_type(min_arg, max_arg)
    {
        BOOST_ASSERT(min_arg < max_arg);
    }

    /** Constructs a uniform_real distribution from its parameters. */
    explicit uniform_real(const param_type& parm)
      : base_type(parm)
    {}

    /** Returns the parameters of the distribution */
    param_type param() const { return param_type(this->a(), this->b()); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm) { this->base_type::param(parm); }
};

} // namespace boost

#endif // BOOST_RANDOM_UNIFORM_REAL_HPP

/* uniform_real.hpp
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
*/