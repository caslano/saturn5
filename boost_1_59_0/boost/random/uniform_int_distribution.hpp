/* boost random/uniform_int_distribution.hpp header file
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
 *  2001-04-08  added min<max assertion (N. Becker)
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP
#define BOOST_RANDOM_UNIFORM_INT_DISTRIBUTION_HPP

#include <iosfwd>
#include <ios>
#include <istream>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/assert.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/uniform_int_float.hpp>
#include <boost/random/detail/signed_unsigned_tools.hpp>
#include <boost/random/traits.hpp>
#include <boost/type_traits/integral_constant.hpp>
#ifdef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#include <boost/type_traits/conditional.hpp>
#endif

namespace boost {
namespace random {
namespace detail {
    

#ifdef BOOST_MSVC
#pragma warning(push)
// disable division by zero warning, since we can't
// actually divide by zero.
#pragma warning(disable:4723)
#endif

template<class Engine, class T>
T generate_uniform_int(
    Engine& eng, T min_value, T max_value,
    boost::true_type /** is_integral<Engine::result_type> */)
{
    typedef T result_type;
    typedef typename boost::random::traits::make_unsigned_or_unbounded<T>::type range_type;
    typedef typename Engine::result_type base_result;
    // ranges are always unsigned or unbounded
    typedef typename boost::random::traits::make_unsigned_or_unbounded<base_result>::type base_unsigned;
    const range_type range = random::detail::subtract<result_type>()(max_value, min_value);
    const base_result bmin = (eng.min)();
    const base_unsigned brange =
      random::detail::subtract<base_result>()((eng.max)(), (eng.min)());

    if(range == 0) {
      return min_value;    
    } else if(brange == range) {
      // this will probably never happen in real life
      // basically nothing to do; just take care we don't overflow / underflow
      base_unsigned v = random::detail::subtract<base_result>()(eng(), bmin);
      return random::detail::add<base_unsigned, result_type>()(v, min_value);
    } else if(brange < range) {
      // use rejection method to handle things like 0..3 --> 0..4
      for(;;) {
        // concatenate several invocations of the base RNG
        // take extra care to avoid overflows

        //  limit == floor((range+1)/(brange+1))
        //  Therefore limit*(brange+1) <= range+1
        range_type limit;
        if(range == (std::numeric_limits<range_type>::max)()) {
          limit = range/(range_type(brange)+1);
          if(range % (range_type(brange)+1) == range_type(brange))
            ++limit;
        } else {
          limit = (range+1)/(range_type(brange)+1);
        }

        // We consider "result" as expressed to base (brange+1):
        // For every power of (brange+1), we determine a random factor
        range_type result = range_type(0);
        range_type mult = range_type(1);

        // loop invariants:
        //  result < mult
        //  mult <= range
        while(mult <= limit) {
          // Postcondition: result <= range, thus no overflow
          //
          // limit*(brange+1)<=range+1                   def. of limit       (1)
          // eng()-bmin<=brange                          eng() post.         (2)
          // and mult<=limit.                            loop condition      (3)
          // Therefore mult*(eng()-bmin+1)<=range+1      by (1),(2),(3)      (4)
          // Therefore mult*(eng()-bmin)+mult<=range+1   rearranging (4)     (5)
          // result<mult                                 loop invariant      (6)
          // Therefore result+mult*(eng()-bmin)<range+1  by (5), (6)         (7)
          //
          // Postcondition: result < mult*(brange+1)
          //
          // result<mult                                 loop invariant      (1)
          // eng()-bmin<=brange                          eng() post.         (2)
          // Therefore result+mult*(eng()-bmin) <
          //           mult+mult*(eng()-bmin)            by (1)              (3)
          // Therefore result+(eng()-bmin)*mult <
          //           mult+mult*brange                  by (2), (3)         (4)
          // Therefore result+(eng()-bmin)*mult <
          //           mult*(brange+1)                   by (4)
          result += static_cast<range_type>(static_cast<range_type>(random::detail::subtract<base_result>()(eng(), bmin)) * mult);

          // equivalent to (mult * (brange+1)) == range+1, but avoids overflow.
          if(mult * range_type(brange) == range - mult + 1) {
              // The destination range is an integer power of
              // the generator's range.
              return(result);
          }

          // Postcondition: mult <= range
          // 
          // limit*(brange+1)<=range+1                   def. of limit       (1)
          // mult<=limit                                 loop condition      (2)
          // Therefore mult*(brange+1)<=range+1          by (1), (2)         (3)
          // mult*(brange+1)!=range+1                    preceding if        (4)
          // Therefore mult*(brange+1)<range+1           by (3), (4)         (5)
          // 
          // Postcondition: result < mult
          //
          // See the second postcondition on the change to result. 
          mult *= range_type(brange)+range_type(1);
        }
        // loop postcondition: range/mult < brange+1
        //
        // mult > limit                                  loop condition      (1)
        // Suppose range/mult >= brange+1                Assumption          (2)
        // range >= mult*(brange+1)                      by (2)              (3)
        // range+1 > mult*(brange+1)                     by (3)              (4)
        // range+1 > (limit+1)*(brange+1)                by (1), (4)         (5)
        // (range+1)/(brange+1) > limit+1                by (5)              (6)
        // limit < floor((range+1)/(brange+1))           by (6)              (7)
        // limit==floor((range+1)/(brange+1))            def. of limit       (8)
        // not (2)                                       reductio            (9)
        //
        // loop postcondition: (range/mult)*mult+(mult-1) >= range
        //
        // (range/mult)*mult + range%mult == range       identity            (1)
        // range%mult < mult                             def. of %           (2)
        // (range/mult)*mult+mult > range                by (1), (2)         (3)
        // (range/mult)*mult+(mult-1) >= range           by (3)              (4)
        //
        // Note that the maximum value of result at this point is (mult-1),
        // so after this final step, we generate numbers that can be
        // at least as large as range.  We have to really careful to avoid
        // overflow in this final addition and in the rejection.  Anything
        // that overflows is larger than range and can thus be rejected.

        // range/mult < brange+1  -> no endless loop
        range_type result_increment =
            generate_uniform_int(
                eng,
                static_cast<range_type>(0),
                static_cast<range_type>(range/mult),
                boost::true_type());
        if(std::numeric_limits<range_type>::is_bounded && ((std::numeric_limits<range_type>::max)() / mult < result_increment)) {
          // The multiplcation would overflow.  Reject immediately.
          continue;
        }
        result_increment *= mult;
        // unsigned integers are guaranteed to wrap on overflow.
        result += result_increment;
        if(result < result_increment) {
          // The addition overflowed.  Reject.
          continue;
        }
        if(result > range) {
          // Too big.  Reject.
          continue;
        }
        return random::detail::add<range_type, result_type>()(result, min_value);
      }
    } else {                   // brange > range
#ifdef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
      typedef typename conditional<
         std::numeric_limits<range_type>::is_specialized && std::numeric_limits<base_unsigned>::is_specialized
         && (std::numeric_limits<range_type>::digits >= std::numeric_limits<base_unsigned>::digits),
         range_type, base_unsigned>::type mixed_range_type;
#else
      typedef base_unsigned mixed_range_type;
#endif

      mixed_range_type bucket_size;
      // it's safe to add 1 to range, as long as we cast it first,
      // because we know that it is less than brange.  However,
      // we do need to be careful not to cause overflow by adding 1
      // to brange.  We use mixed_range_type throughout for mixed
      // arithmetic between base_unsigned and range_type - in the case
      // that range_type has more bits than base_unsigned it is always
      // safe to use range_type for this albeit it may be more effient
      // to use base_unsigned.  The latter is a narrowing conversion though
      // which may be disallowed if range_type is a multiprecision type
      // and there are no explicit converison operators.

      if(brange == (std::numeric_limits<base_unsigned>::max)()) {
        bucket_size = static_cast<mixed_range_type>(brange) / (static_cast<mixed_range_type>(range)+1);
        if(static_cast<mixed_range_type>(brange) % (static_cast<mixed_range_type>(range)+1) == static_cast<mixed_range_type>(range)) {
          ++bucket_size;
        }
      } else {
        bucket_size = static_cast<mixed_range_type>(brange + 1) / (static_cast<mixed_range_type>(range)+1);
      }
      for(;;) {
        mixed_range_type result =
          random::detail::subtract<base_result>()(eng(), bmin);
        result /= bucket_size;
        // result and range are non-negative, and result is possibly larger
        // than range, so the cast is safe
        if(result <= static_cast<mixed_range_type>(range))
          return random::detail::add<mixed_range_type, result_type>()(result, min_value);
      }
    }
}

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template<class Engine, class T>
inline T generate_uniform_int(
    Engine& eng, T min_value, T max_value,
    boost::false_type /** is_integral<Engine::result_type> */)
{
    uniform_int_float<Engine> wrapper(eng);
    return generate_uniform_int(wrapper, min_value, max_value, boost::true_type());
}

template<class Engine, class T>
inline T generate_uniform_int(Engine& eng, T min_value, T max_value)
{
    typedef typename Engine::result_type base_result;
    return generate_uniform_int(eng, min_value, max_value,
        boost::random::traits::is_integral<base_result>());
}

}

/**
 * The class template uniform_int_distribution models a \random_distribution.
 * On each invocation, it returns a random integer value uniformly
 * distributed in the set of integers {min, min+1, min+2, ..., max}.
 *
 * The template parameter IntType shall denote an integer-like value type.
 */
template<class IntType = int>
class uniform_int_distribution
{
public:
    typedef IntType input_type;
    typedef IntType result_type;

    class param_type
    {
    public:

        typedef uniform_int_distribution distribution_type;

        /**
         * Constructs the parameters of a uniform_int_distribution.
         *
         * Requires min <= max
         */
        explicit param_type(
            IntType min_arg = 0,
            IntType max_arg = (std::numeric_limits<IntType>::max)())
          : _min(min_arg), _max(max_arg)
        {
            BOOST_ASSERT(_min <= _max);
        }

        /** Returns the minimum value of the distribution. */
        IntType a() const { return _min; }
        /** Returns the maximum value of the distribution. */
        IntType b() const { return _max; }

        /** Writes the parameters to a @c std::ostream. */
        BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, param_type, parm)
        {
            os << parm._min << " " << parm._max;
            return os;
        }

        /** Reads the parameters from a @c std::istream. */
        BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, param_type, parm)
        {
            IntType min_in, max_in;
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

        IntType _min;
        IntType _max;
    };

    /**
     * Constructs a uniform_int_distribution. @c min and @c max are
     * the parameters of the distribution.
     *
     * Requires: min <= max
     */
    explicit uniform_int_distribution(
        IntType min_arg = 0,
        IntType max_arg = (std::numeric_limits<IntType>::max)())
      : _min(min_arg), _max(max_arg)
    {
        BOOST_ASSERT(min_arg <= max_arg);
    }
    /** Constructs a uniform_int_distribution from its parameters. */
    explicit uniform_int_distribution(const param_type& parm)
      : _min(parm.a()), _max(parm.b()) {}

    /**  Returns the minimum value of the distribution */
    IntType min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return _min; }
    /**  Returns the maximum value of the distribution */
    IntType max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return _max; }

    /**  Returns the minimum value of the distribution */
    IntType a() const { return _min; }
    /**  Returns the maximum value of the distribution */
    IntType b() const { return _max; }

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

    /** Returns an integer uniformly distributed in the range [min, max]. */
    template<class Engine>
    result_type operator()(Engine& eng) const
    { return detail::generate_uniform_int(eng, _min, _max); }

    /**
     * Returns an integer uniformly distributed in the range
     * [param.a(), param.b()].
     */
    template<class Engine>
    result_type operator()(Engine& eng, const param_type& parm) const
    { return detail::generate_uniform_int(eng, parm.a(), parm.b()); }

    /** Writes the distribution to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, uniform_int_distribution, ud)
    {
        os << ud.param();
        return os;
    }

    /** Reads the distribution from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, uniform_int_distribution, ud)
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
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(uniform_int_distribution, lhs, rhs)
    { return lhs._min == rhs._min && lhs._max == rhs._max; }
    
    /**
     * Returns true if the two distributions may produce different sequences
     * of values given equal generators.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(uniform_int_distribution)

private:
    IntType _min;
    IntType _max;
};

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_UNIFORM_INT_HPP

/* uniform_int_distribution.hpp
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
*/