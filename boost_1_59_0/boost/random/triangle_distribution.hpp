/* boost random/triangle_distribution.hpp header file
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

#ifndef BOOST_RANDOM_TRIANGLE_DISTRIBUTION_HPP
#define BOOST_RANDOM_TRIANGLE_DISTRIBUTION_HPP

#include <boost/config/no_tr1/cmath.hpp>
#include <iosfwd>
#include <ios>
#include <istream>
#include <boost/assert.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/uniform_01.hpp>

namespace boost {
namespace random {

/**
 * Instantiations of @c triangle_distribution model a \random_distribution.
 * A @c triangle_distribution has three parameters, @c a, @c b, and @c c,
 * which are the smallest, the most probable and the largest values of
 * the distribution respectively.
 */
template<class RealType = double>
class triangle_distribution
{
public:
    typedef RealType input_type;
    typedef RealType result_type;

    class param_type
    {
    public:

        typedef triangle_distribution distribution_type;

        /** Constructs the parameters of a @c triangle_distribution. */
        explicit param_type(RealType a_arg = RealType(0.0),
                            RealType b_arg = RealType(0.5),
                            RealType c_arg = RealType(1.0))
          : _a(a_arg), _b(b_arg), _c(c_arg)
        {
            BOOST_ASSERT(_a <= _b && _b <= _c);
        }

        /** Returns the minimum value of the distribution. */
        RealType a() const { return _a; }
        /** Returns the mode of the distribution. */
        RealType b() const { return _b; }
        /** Returns the maximum value of the distribution. */
        RealType c() const { return _c; }

        /** Writes the parameters to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._a << " " << parm._b << " " << parm._c;
            return os;
        }

        /** Reads the parameters from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            double a_in, b_in, c_in;
            if(is >> a_in >> std::ws >> b_in >> std::ws >> c_in) {
                if(a_in <= b_in && b_in <= c_in) {
                    parm._a = a_in;
                    parm._b = b_in;
                    parm._c = c_in;
                } else {
                    is.setstate(std::ios_base::failbit);
                }
            }
            return is;
        }

        /** Returns true if the two sets of parameters are equal. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._a == rhs._a && lhs._b == rhs._b && lhs._c == rhs._c; }

        /** Returns true if the two sets of parameters are different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:
        RealType _a;
        RealType _b;
        RealType _c;
    };

    /**
     * Constructs a @c triangle_distribution with the parameters
     * @c a, @c b, and @c c.
     *
     * Preconditions: a <= b <= c.
     */
    explicit triangle_distribution(RealType a_arg = RealType(0.0),
                                   RealType b_arg = RealType(0.5),
                                   RealType c_arg = RealType(1.0))
      : _a(a_arg), _b(b_arg), _c(c_arg)
    {
        BOOST_ASSERT(_a <= _b && _b <= _c);
        init();
    }

    /** Constructs a @c triangle_distribution from its parameters. */
    explicit triangle_distribution(const param_type& parm)
      : _a(parm.a()), _b(parm.b()), _c(parm.c())
    {
        init();
    }

    // compiler-generated copy ctor and assignment operator are fine

    /** Returns the @c a parameter of the distribution */
    result_type a() const { return _a; }
    /** Returns the @c b parameter of the distribution */
    result_type b() const { return _b; }
    /** Returns the @c c parameter of the distribution */
    result_type c() const { return _c; }

    /** Returns the smallest value that the distribution can produce. */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return _a; }
    /** Returns the largest value that the distribution can produce. */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return _c; }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_a, _b, _c); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        _a = parm.a();
        _b = parm.b();
        _c = parm.c();
        init();
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

    /**
     * Returns a random variate distributed according to the
     * triangle distribution.
     */
    template<class Engine>
    result_type operator()(Engine& eng)
    {
        using std::sqrt;
        result_type u = uniform_01<result_type>()(eng);
        if( u <= q1 )
            return _a + p1*sqrt(u);
        else
        return _c - d3*sqrt(d2*u-d1);
    }

    /**
     * Returns a random variate distributed according to the
     * triangle distribution with parameters specified by param.
     */
    template<class Engine>
    result_type operator()(Engine& eng, const param_type& parm)
    { return triangle_distribution(parm)(eng); }

    /** Writes the distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, triangle_distribution, td)
    {
        os << td.param();
        return os;
    }

    /** Reads the distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, triangle_distribution, td)
    {
        param_type parm;
        if(is >> parm) {
            td.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two distributions will produce identical
     * sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(triangle_distribution, lhs, rhs)
    { return lhs._a == rhs._a && lhs._b == rhs._b && lhs._c == rhs._c; }

    /**
     * Returns true if the two distributions may produce different
     * sequences of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(triangle_distribution)

private:
    /// \cond show_private
    void init()
    {
        using std::sqrt;
        d1 = _b - _a;
        d2 = _c - _a;
        d3 = sqrt(_c - _b);
        q1 = d1 / d2;
        p1 = sqrt(d1 * d2);
    }
    /// \endcond

    RealType _a, _b, _c;
    RealType d1, d2, d3, q1, p1;
};

} // namespace random

using random::triangle_distribution;

} // namespace boost

#endif // BOOST_RANDOM_TRIANGLE_DISTRIBUTION_HPP

/* triangle_distribution.hpp
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
*/