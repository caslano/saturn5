/* boost random/linear_congruential.hpp header file
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

#ifndef BOOST_RANDOM_LINEAR_CONGRUENTIAL_HPP
#define BOOST_RANDOM_LINEAR_CONGRUENTIAL_HPP

#include <iostream>
#include <stdexcept>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/limits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/const_mod.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/seed_impl.hpp>
#include <boost/detail/workaround.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {

/**
 * Instantiations of class template linear_congruential_engine model a
 * \pseudo_random_number_generator. Linear congruential pseudo-random
 * number generators are described in:
 *
 *  @blockquote
 *  "Mathematical methods in large-scale computing units", D. H. Lehmer,
 *  Proc. 2nd Symposium on Large-Scale Digital Calculating Machines,
 *  Harvard University Press, 1951, pp. 141-146
 *  @endblockquote
 *
 * Let x(n) denote the sequence of numbers returned by some pseudo-random
 * number generator. Then for the linear congruential generator,
 * x(n+1) := (a * x(n) + c) mod m. Parameters for the generator are
 * x(0), a, c, m. The template parameter IntType shall denote an integral
 * type. It must be large enough to hold values a, c, and m. The template
 * parameters a and c must be smaller than m.
 *
 * Note: The quality of the generator crucially depends on the choice of
 * the parameters. User code should use one of the sensibly parameterized
 * generators such as minstd_rand instead.
 */
template<class IntType, IntType a, IntType c, IntType m>
class linear_congruential_engine
{
public:
    typedef IntType result_type;

    // Required for old Boost.Random concept
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);

    BOOST_STATIC_CONSTANT(IntType, multiplier = a);
    BOOST_STATIC_CONSTANT(IntType, increment = c);
    BOOST_STATIC_CONSTANT(IntType, modulus = m);
    BOOST_STATIC_CONSTANT(IntType, default_seed = 1);
    
    BOOST_STATIC_ASSERT(std::numeric_limits<IntType>::is_integer);
    BOOST_STATIC_ASSERT(m == 0 || a < m);
    BOOST_STATIC_ASSERT(m == 0 || c < m);
    
    /**
     * Constructs a @c linear_congruential_engine, using the default seed
     */
    linear_congruential_engine() { seed(); }

    /**
     * Constructs a @c linear_congruential_engine, seeding it with @c x0.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(linear_congruential_engine,
                                               IntType, x0)
    { seed(x0); }
    
    /**
     * Constructs a @c linear_congruential_engine, seeding it with values
     * produced by a call to @c seq.generate().
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(linear_congruential_engine,
                                             SeedSeq, seq)
    { seed(seq); }

    /**
     * Constructs a @c linear_congruential_engine  and seeds it
     * with values taken from the itrator range [first, last)
     * and adjusts first to point to the element after the last one
     * used.  If there are not enough elements, throws @c std::invalid_argument.
     *
     * first and last must be input iterators.
     */
    template<class It>
    linear_congruential_engine(It& first, It last)
    {
        seed(first, last);
    }

    // compiler-generated copy constructor and assignment operator are fine

    /**
     * Calls seed(default_seed)
     */
    void seed() { seed(default_seed); }

    /**
     * If c mod m is zero and x0 mod m is zero, changes the current value of
     * the generator to 1. Otherwise, changes it to x0 mod m. If c is zero,
     * distinct seeds in the range [1,m) will leave the generator in distinct
     * states. If c is not zero, the range is [0,m).
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(linear_congruential_engine, IntType, x0_)
    {
        // Work around a msvc 12/14 optimizer bug, which causes
        // the line _x = 1 to run unconditionally sometimes.
        // Creating a local copy seems to make it work.
        IntType x0 = x0_;
        // wrap _x if it doesn't fit in the destination
        if(modulus == 0) {
            _x = x0;
        } else {
            _x = x0 % modulus;
        }
        // handle negative seeds
        if(_x < 0) {
            _x += modulus;
        }
        // adjust to the correct range
        if(increment == 0 && _x == 0) {
            _x = 1;
        }
        BOOST_ASSERT(_x >= (min)());
        BOOST_ASSERT(_x <= (max)());
    }

    /**
     * Seeds a @c linear_congruential_engine using values from a SeedSeq.
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(linear_congruential_engine, SeedSeq, seq)
    { seed(detail::seed_one_int<IntType, m>(seq)); }

    /**
     * seeds a @c linear_congruential_engine with values taken
     * from the itrator range [first, last) and adjusts @c first to
     * point to the element after the last one used.  If there are
     * not enough elements, throws @c std::invalid_argument.
     *
     * @c first and @c last must be input iterators.
     */
    template<class It>
    void seed(It& first, It last)
    { seed(detail::get_one_int<IntType, m>(first, last)); }

    /**
     * Returns the smallest value that the @c linear_congruential_engine
     * can produce.
     */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return c == 0 ? 1 : 0; }
    /**
     * Returns the largest value that the @c linear_congruential_engine
     * can produce.
     */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return modulus-1; }

    /** Returns the next value of the @c linear_congruential_engine. */
    IntType operator()()
    {
        _x = const_mod<IntType, m>::mult_add(a, _x, c);
        return _x;
    }
  
    /** Fills a range with random values */
    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    /** Advances the state of the generator by @c z. */
    void discard(boost::uintmax_t z)
    {
        typedef const_mod<IntType, m> mod_type;
        IntType b_inv = mod_type::invert(a-1);
        IntType b_gcd = mod_type::mult(a-1, b_inv);
        if(b_gcd == 1) {
            IntType a_z = mod_type::pow(a, z);
            _x = mod_type::mult_add(a_z, _x, 
                mod_type::mult(mod_type::mult(c, b_inv), a_z - 1));
        } else {
            // compute (a^z - 1)*c % (b_gcd * m) / (b / b_gcd) * inv(b / b_gcd)
            // we're storing the intermediate result / b_gcd
            IntType a_zm1_over_gcd = 0;
            IntType a_km1_over_gcd = (a - 1) / b_gcd;
            boost::uintmax_t exponent = z;
            while(exponent != 0) {
                if(exponent % 2 == 1) {
                    a_zm1_over_gcd =
                        mod_type::mult_add(
                            b_gcd,
                            mod_type::mult(a_zm1_over_gcd, a_km1_over_gcd),
                            mod_type::add(a_zm1_over_gcd, a_km1_over_gcd));
                }
                a_km1_over_gcd = mod_type::mult_add(
                    b_gcd,
                    mod_type::mult(a_km1_over_gcd, a_km1_over_gcd),
                    mod_type::add(a_km1_over_gcd, a_km1_over_gcd));
                exponent /= 2;
            }
            
            IntType a_z = mod_type::mult_add(b_gcd, a_zm1_over_gcd, 1);
            IntType num = mod_type::mult(c, a_zm1_over_gcd);
            b_inv = mod_type::invert((a-1)/b_gcd);
            _x = mod_type::mult_add(a_z, _x, mod_type::mult(b_inv, num));
        }
    }

    friend bool operator==(const linear_congruential_engine& x,
                           const linear_congruential_engine& y)
    { return x._x == y._x; }
    friend bool operator!=(const linear_congruential_engine& x,
                           const linear_congruential_engine& y)
    { return !(x == y); }
    
#if !defined(BOOST_RANDOM_NO_STREAM_OPERATORS)
    /** Writes a @c linear_congruential_engine to a @c std::ostream. */
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<<(std::basic_ostream<CharT,Traits>& os,
               const linear_congruential_engine& lcg)
    {
        return os << lcg._x;
    }

    /** Reads a @c linear_congruential_engine from a @c std::istream. */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is,
               linear_congruential_engine& lcg)
    {
        lcg.read(is);
        return is;
    }
#endif

private:

    /// \cond show_private

    template<class CharT, class Traits>
    void read(std::basic_istream<CharT, Traits>& is) {
        IntType x;
        if(is >> x) {
            if(x >= (min)() && x <= (max)()) {
                _x = x;
            } else {
                is.setstate(std::ios_base::failbit);
            }
        }
    }

    /// \endcond

    IntType _x;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class IntType, IntType a, IntType c, IntType m>
const bool linear_congruential_engine<IntType, a, c, m>::has_fixed_range;
template<class IntType, IntType a, IntType c, IntType m>
const IntType linear_congruential_engine<IntType,a,c,m>::multiplier;
template<class IntType, IntType a, IntType c, IntType m>
const IntType linear_congruential_engine<IntType,a,c,m>::increment;
template<class IntType, IntType a, IntType c, IntType m>
const IntType linear_congruential_engine<IntType,a,c,m>::modulus;
template<class IntType, IntType a, IntType c, IntType m>
const IntType linear_congruential_engine<IntType,a,c,m>::default_seed;
#endif

/// \cond show_deprecated

// provided for backwards compatibility
template<class IntType, IntType a, IntType c, IntType m, IntType val = 0>
class linear_congruential : public linear_congruential_engine<IntType, a, c, m>
{
    typedef linear_congruential_engine<IntType, a, c, m> base_type;
public:
    linear_congruential(IntType x0 = 1) : base_type(x0) {}
    template<class It>
    linear_congruential(It& first, It last) : base_type(first, last) {}
};

/// \endcond

/**
 * The specialization \minstd_rand0 was originally suggested in
 *
 *  @blockquote
 *  A pseudo-random number generator for the System/360, P.A. Lewis,
 *  A.S. Goodman, J.M. Miller, IBM Systems Journal, Vol. 8, No. 2,
 *  1969, pp. 136-146
 *  @endblockquote
 *
 * It is examined more closely together with \minstd_rand in
 *
 *  @blockquote
 *  "Random Number Generators: Good ones are hard to find",
 *  Stephen K. Park and Keith W. Miller, Communications of
 *  the ACM, Vol. 31, No. 10, October 1988, pp. 1192-1201 
 *  @endblockquote
 */
typedef linear_congruential_engine<uint32_t, 16807, 0, 2147483647> minstd_rand0;

/** The specialization \minstd_rand was suggested in
 *
 *  @blockquote
 *  "Random Number Generators: Good ones are hard to find",
 *  Stephen K. Park and Keith W. Miller, Communications of
 *  the ACM, Vol. 31, No. 10, October 1988, pp. 1192-1201
 *  @endblockquote
 */
typedef linear_congruential_engine<uint32_t, 48271, 0, 2147483647> minstd_rand;


#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
/**
 * Class @c rand48 models a \pseudo_random_number_generator. It uses
 * the linear congruential algorithm with the parameters a = 0x5DEECE66D,
 * c = 0xB, m = 2**48. It delivers identical results to the @c lrand48()
 * function available on some systems (assuming lcong48 has not been called).
 *
 * It is only available on systems where @c uint64_t is provided as an
 * integral type, so that for example static in-class constants and/or
 * enum definitions with large @c uint64_t numbers work.
 */
class rand48 
{
public:
    typedef boost::uint32_t result_type;

    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    /**
     * Returns the smallest value that the generator can produce
     */
    static BOOST_CONSTEXPR uint32_t min BOOST_PREVENT_MACRO_SUBSTITUTION () { return 0; }
    /**
     * Returns the largest value that the generator can produce
     */
    static BOOST_CONSTEXPR uint32_t max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return 0x7FFFFFFF; }
  
    /** Seeds the generator with the default seed. */
    rand48() : lcf(cnv(static_cast<uint32_t>(1))) {}
    /**
     * Constructs a \rand48 generator with x(0) := (x0 << 16) | 0x330e.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(rand48, result_type, x0)
    { seed(x0); }
    /**
     * Seeds the generator with values produced by @c seq.generate().
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(rand48, SeedSeq, seq)
    { seed(seq); }
    /**
     * Seeds the generator using values from an iterator range,
     * and updates first to point one past the last value consumed.
     */
    template<class It> rand48(It& first, It last) : lcf(first, last) { }

    // compiler-generated copy ctor and assignment operator are fine

    /** Seeds the generator with the default seed. */
    void seed() { seed(static_cast<uint32_t>(1)); }
    /**
     * Changes the current value x(n) of the generator to (x0 << 16) | 0x330e.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(rand48, result_type, x0)
    { lcf.seed(cnv(x0)); }
    /**
     * Seeds the generator using values from an iterator range,
     * and updates first to point one past the last value consumed.
     */
    template<class It> void seed(It& first, It last) { lcf.seed(first,last); }
    /**
     * Seeds the generator with values produced by @c seq.generate().
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(rand48, SeedSeq, seq)
    { lcf.seed(seq); }

    /**  Returns the next value of the generator. */
    uint32_t operator()() { return static_cast<uint32_t>(lcf() >> 17); }
    
    /** Advances the state of the generator by @c z. */
    void discard(boost::uintmax_t z) { lcf.discard(z); }
  
    /** Fills a range with random values */
    template<class Iter>
    void generate(Iter first, Iter last)
    {
        for(; first != last; ++first) {
            *first = (*this)();
        }
    }

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
    /**  Writes a @c rand48 to a @c std::ostream. */
    template<class CharT,class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<<(std::basic_ostream<CharT,Traits>& os, const rand48& r)
    { os << r.lcf; return os; }

    /** Reads a @c rand48 from a @c std::istream. */
    template<class CharT,class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is, rand48& r)
    { is >> r.lcf; return is; }
#endif

    /**
     * Returns true if the two generators will produce identical
     * sequences of values.
     */
    friend bool operator==(const rand48& x, const rand48& y)
    { return x.lcf == y.lcf; }
    /**
     * Returns true if the two generators will produce different
     * sequences of values.
     */
    friend bool operator!=(const rand48& x, const rand48& y)
    { return !(x == y); }
private:
    /// \cond show_private
    typedef random::linear_congruential_engine<uint64_t,
        // xxxxULL is not portable
        uint64_t(0xDEECE66DUL) | (uint64_t(0x5) << 32),
        0xB, uint64_t(1)<<48> lcf_t;
    lcf_t lcf;

    static boost::uint64_t cnv(boost::uint32_t x)
    { return (static_cast<uint64_t>(x) << 16) | 0x330e; }
    /// \endcond
};
#endif /* !BOOST_NO_INT64_T && !BOOST_NO_INTEGRAL_INT64_T */

} // namespace random

using random::minstd_rand0;
using random::minstd_rand;
using random::rand48;

} // namespace boost

#include <boost/random/detail/enable_warnings.hpp>

#endif // BOOST_RANDOM_LINEAR_CONGRUENTIAL_HPP

/* linear_congruential.hpp
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
*/