/* boost random/uniform_real_distribution.hpp header file
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
 */

#ifndef BOOST_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP
#define BOOST_RANDOM_UNIFORM_REAL_DISTRIBUTION_HPP

#include <iosfwd>
#include <ios>
#include <istream>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/signed_unsigned_tools.hpp>
#include <boost/type_traits/is_integral.hpp>

namespace boost {
namespace random {
namespace detail {

template<class Engine, class T>
T generate_uniform_real(
    Engine& eng, T min_value, T max_value,
    boost::false_type  /** is_integral<Engine::result_type> */)
{
    for(;;) {
        typedef T result_type;
        result_type numerator = static_cast<T>(eng() - (eng.min)());
        result_type divisor = static_cast<T>((eng.max)() - (eng.min)());
        BOOST_ASSERT(divisor > 0);
        BOOST_ASSERT(numerator >= 0 && numerator <= divisor);
        T result = numerator / divisor * (max_value - min_value) + min_value;
        if(result < max_value) return result;
    }
}

template<class Engine, class T>
T generate_uniform_real(
    Engine& eng, T min_value, T max_value,
    boost::true_type  /** is_integral<Engine::result_type> */)
{
    for(;;) {
        typedef T result_type;
        typedef typename Engine::result_type base_result;
        result_type numerator = static_cast<T>(subtract<base_result>()(eng(), (eng.min)()));
        result_type divisor = static_cast<T>(subtract<base_result>()((eng.max)(), (eng.min)())) + 1;
        BOOST_ASSERT(divisor > 0);
        BOOST_ASSERT(numerator >= 0 && numerator <= divisor);
        T result = numerator / divisor * (max_value - min_value) + min_value;
        if(result < max_value) return result;
    }
}

template<class Engine, class T>
inline T generate_uniform_real(Engine& eng, T min_value, T max_value)
{
    if(max_value / 2 - min_value / 2 > (std::numeric_limits<T>::max)() / 2)
        return 2 * generate_uniform_real(eng, T(min_value / 2), T(max_value / 2));
    typedef typename Engine::result_type base_result;
    return generate_uniform_real(eng, min_value, max_value,
        boost::is_integral<base_result>());
}

}

/**
 * The class template uniform_real_distribution models a \random_distribution.
 * On each invocation, it returns a random floating-point value uniformly
 * distributed in the range [min..max).
 */
template<class RealType = double>
class uniform_real_distribution
{
public:
    typedef RealType input_type;
    typedef RealType result_type;

    class param_type
    {
    public:

        typedef uniform_real_distribution distribution_type;

        /**
         * Constructs the parameters of a uniform_real_distribution.
         *
         * Requires min <= max
         */
        explicit param_type(RealType min_arg = RealType(0.0),
                            RealType max_arg = RealType(1.0))
          : _min(min_arg), _max(max_arg)
        {
            BOOST_ASSERT(_min < _max);
        }

        /** Returns the minimum value of the distribution. */
        RealType a() const { return _min; }
        /** Returns the maximum value of the distribution. */
        RealType b() const { return _max; }

        /** Writes the parameters to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._min << " " << parm._max;
            return os;
        }

        /** Reads the parameters from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            RealType min_in, max_in;
            if(is >> min_in >> std::ws >> max_in) {
                if(min_in <= max_in) {
                    parm._min = min_in;
                    parm._max = max_in;
                } else {
                    is.setstate(std::ios_base::failbit);
                }
            }
            return is;
        }

        /** Returns true if the two sets of parameters are equal. */
        BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(param_type, lhs, rhs)
        { return lhs._min == rhs._min && lhs._max == rhs._max; }

        /** Returns true if the two sets of parameters are different. */
        BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(param_type)

    private:

        RealType _min;
        RealType _max;
    };

    /**
     * Constructs a uniform_real_distribution. @c min and @c max are
     * the parameters of the distribution.
     *
     * Requires: min <= max
     */
    explicit uniform_real_distribution(
        RealType min_arg = RealType(0.0),
        RealType max_arg = RealType(1.0))
      : _min(min_arg), _max(max_arg)
    {
        BOOST_ASSERT(min_arg < max_arg);
    }
    /** Constructs a uniform_real_distribution from its parameters. */
    explicit uniform_real_distribution(const param_type& parm)
      : _min(parm.a()), _max(parm.b()) {}

    /**  Returns the minimum value of the distribution */
    RealType min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return _min; }
    /**  Returns the maximum value of the distribution */
    RealType max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return _max; }

    /**  Returns the minimum value of the distribution */
    RealType a() const { return _min; }
    /**  Returns the maximum value of the distribution */
    RealType b() const { return _max; }

    /** Returns the parameters of the distribution. */
    param_type param() const { return param_type(_min, _max); }
    /** Sets the parameters of the distribution. */
    void param(const param_type& parm)
    {
        _min = parm.a();
        _max = parm.b();
    }

    /**
     * Effects: Subsequent uses of the distribution do not depend
     * on values produced by any engine prior to invoking reset.
     */
    void reset() { }

    /** Returns a value uniformly distributed in the range [min, max). */
    template<class Engine>
    result_type operator()(Engine& eng) const
    { return detail::generate_uniform_real(eng, _min, _max); }

    /**
     * Returns a value uniformly distributed in the range
     * [param.a(), param.b()).
     */
    template<class Engine>
    result_type operator()(Engine& eng, const param_type& parm) const
    { return detail::generate_uniform_real(eng, parm.a(), parm.b()); }

    /** Writes the distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, uniform_real_distribution, ud)
    {
        os << ud.param();
        return os;
    }

    /** Reads the distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, uniform_real_distribution, ud)
    {
        param_type parm;
        if(is >> parm) {
            ud.param(parm);
        }
        return is;
    }

    /**
     * Returns true if the two distributions will produce identical sequences
     * of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(uniform_real_distribution, lhs, rhs)
    { return lhs._min == rhs._min && lhs._max == rhs._max; }
    
    /**
     * Returns true if the two distributions may produce different sequences
     * of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(uniform_real_distribution)

private:
    RealType _min;
    RealType _max;
};

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_UNIFORM_INT_HPP

/* uniform_real_distribution.hpp
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
*/