/* boost random/subtract_with_carry.hpp header file
 *
 * Copyright Jens Maurer 2002
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2002-03-02  created
 */

#ifndef BOOST_RANDOM_SUBTRACT_WITH_CARRY_HPP
#define BOOST_RANDOM_SUBTRACT_WITH_CARRY_HPP

#include <boost/config/no_tr1/cmath.hpp>         // std::pow
#include <iostream>
#include <algorithm>     // std::equal
#include <stdexcept>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <boost/integer/static_log2.hpp>
#include <boost/integer/integer_mask.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/seed_impl.hpp>
#include <boost/random/detail/generator_seed_seq.hpp>
#include <boost/random/linear_congruential.hpp>


namespace boost {
namespace random {

namespace detail {
   
struct subtract_with_carry_discard
{
    template<class Engine>
    static void apply(Engine& eng, boost::uintmax_t z)
    {
        typedef typename Engine::result_type IntType;
        const std::size_t short_lag = Engine::short_lag;
        const std::size_t long_lag = Engine::long_lag;
        std::size_t k = eng.k;
        IntType carry = eng.carry;
        if(k != 0) {
            // increment k until it becomes 0.
            if(k < short_lag) {
                std::size_t limit = (short_lag - k) < z?
                    short_lag : (k + static_cast<std::size_t>(z));
                for(std::size_t j = k; j < limit; ++j) {
                    carry = eng.do_update(j, j + long_lag - short_lag, carry);
                }
            }
            std::size_t limit = (long_lag - k) < z?
                long_lag : (k + static_cast<std::size_t>(z));
            std::size_t start = (k < short_lag ? short_lag : k);
            for(std::size_t j = start; j < limit; ++j) {
                carry = eng.do_update(j, j - short_lag, carry);
            }
        }

        k = ((z % long_lag) + k) % long_lag;

        if(k < z) {
            // main loop: update full blocks from k = 0 to long_lag
            for(std::size_t i = 0; i < (z - k) / long_lag; ++i) {
                for(std::size_t j = 0; j < short_lag; ++j) {
                    carry = eng.do_update(j, j + long_lag - short_lag, carry);
                }
                for(std::size_t j = short_lag; j < long_lag; ++j) {
                    carry = eng.do_update(j, j - short_lag, carry);
                }
            }

            // Update the last partial block
            std::size_t limit = short_lag < k? short_lag : k; 
            for(std::size_t j = 0; j < limit; ++j) {
                carry = eng.do_update(j, j + long_lag - short_lag, carry);
            }
            for(std::size_t j = short_lag; j < k; ++j) {
                carry = eng.do_update(j, j - short_lag, carry);
            }
        }
        eng.carry = carry;
        eng.k = k;
    }
};

}

/**
 * Instantiations of @c subtract_with_carry_engine model a
 * \pseudo_random_number_generator.  The algorithm is
 * described in
 *
 *  @blockquote
 *  "A New Class of Random Number Generators", George
 *  Marsaglia and Arif Zaman, Annals of Applied Probability,
 *  Volume 1, Number 3 (1991), 462-480.
 *  @endblockquote
 */
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
class subtract_with_carry_engine
{
public:
    typedef IntType result_type;
    BOOST_STATIC_CONSTANT(std::size_t, word_size = w);
    BOOST_STATIC_CONSTANT(std::size_t, long_lag = r);
    BOOST_STATIC_CONSTANT(std::size_t, short_lag = s);
    BOOST_STATIC_CONSTANT(uint32_t, default_seed = 19780503u);

    // Required by the old Boost.Random concepts
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    // Backwards compatibility
    BOOST_STATIC_CONSTANT(result_type, modulus = (result_type(1) << w));
    
    BOOST_STATIC_ASSERT(std::numeric_limits<result_type>::is_integer);

    /**
     * Constructs a new @c subtract_with_carry_engine and seeds
     * it with the default seed.
     */
    subtract_with_carry_engine() { seed(); }
    /**
     * Constructs a new @c subtract_with_carry_engine and seeds
     * it with @c value.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry_engine,
                                               IntType, value)
    { seed(value); }
    /**
     * Constructs a new @c subtract_with_carry_engine and seeds
     * it with values produced by @c seq.generate().
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(subtract_with_carry_engine,
                                             SeedSeq, seq)
    { seed(seq); }
    /**
     * Constructs a new @c subtract_with_carry_engine and seeds
     * it with values from a range.  first is updated to point
     * one past the last value consumed.  If there are not
     * enough elements in the range to fill the entire state of
     * the generator, throws @c std::invalid_argument.
     */
    template<class It> subtract_with_carry_engine(It& first, It last)
    { seed(first,last); }

    // compiler-generated copy ctor and assignment operator are fine

    /** Seeds the generator with the default seed. */
    void seed() { seed(default_seed); }
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry_engine,
                                        IntType, value)
    {
        typedef linear_congruential_engine<uint32_t,40014,0,2147483563> gen_t;
        gen_t intgen(static_cast<boost::uint32_t>(value == 0 ? default_seed : value));
        detail::generator_seed_seq<gen_t> gen(intgen);
        seed(gen);
    }

    /** Seeds the generator with values produced by @c seq.generate(). */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(subtract_with_carry, SeedSeq, seq)
    {
        detail::seed_array_int<w>(seq, x);
        carry = (x[long_lag-1] == 0);
        k = 0;
    }

    /**
     * Seeds the generator with values from a range.  Updates @c first to
     * point one past the last consumed value.  If the range does not
     * contain enough elements to fill the entire state of the generator,
     * throws @c std::invalid_argument.
     */
    template<class It>
    void seed(It& first, It last)
    {
        detail::fill_array_int<w>(first, last, x);
        carry = (x[long_lag-1] == 0);
        k = 0;
    }

    /** Returns the smallest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return 0; }
    /** Returns the largest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return boost::low_bits_mask_t<w>::sig_bits; }

    /** Returns the next value of the generator. */
    result_type operator()()
    {
        std::size_t short_index =
            (k < short_lag)?
                (k + long_lag - short_lag) :
                (k - short_lag);
        carry = do_update(k, short_index, carry);
        IntType result = x[k];
        ++k;
        if(k >= long_lag)
            k = 0;
        return result;
    }

    /** Advances the state of the generator by @c z. */
    void discard(boost::uintmax_t z)
    {
        detail::subtract_with_carry_discard::apply(*this, z);
    }

    /** Fills a range with random values. */
    template<class It>
    void generate(It first, It last)
    { detail::generate_from_int(*this, first, last); }
 
    /** Writes a @c subtract_with_carry_engine to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, subtract_with_carry_engine, f)
    {
        for(unsigned int j = 0; j < f.long_lag; ++j)
            os << f.compute(j) << ' ';
        os << f.carry;
        return os;
    }

    /** Reads a @c subtract_with_carry_engine from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, subtract_with_carry_engine, f)
    {
        for(unsigned int j = 0; j < f.long_lag; ++j)
            is >> f.x[j] >> std::ws;
        is >> f.carry;
        f.k = 0;
        return is;
    }

    /**
     * Returns true if the two generators will produce identical
     * sequences of values.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(subtract_with_carry_engine, x, y)
    {
        for(unsigned int j = 0; j < r; ++j)
            if(x.compute(j) != y.compute(j))
                return false;
        return true;
    }

    /**
     * Returns true if the two generators will produce different
     * sequences of values.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(subtract_with_carry_engine)

private:
    /// \cond show_private
    // returns x(i-r+index), where index is in 0..r-1
    IntType compute(unsigned int index) const
    {
        return x[(k+index) % long_lag];
    }

    friend struct detail::subtract_with_carry_discard;

    IntType do_update(std::size_t current, std::size_t short_index, IntType carry)
    {
        IntType delta;
        IntType temp = x[current] + carry;
        if (x[short_index] >= temp) {
            // x(n) >= 0
            delta =  x[short_index] - temp;
            carry = 0;
        } else {
            // x(n) < 0
            delta = modulus - temp + x[short_index];
            carry = 1;
        }
        x[current] = delta;
        return carry;
    }
    /// \endcond

    // state representation; next output (state) is x(i)
    //   x[0]  ... x[k] x[k+1] ... x[long_lag-1]     represents
    //  x(i-k) ... x(i) x(i+1) ... x(i-k+long_lag-1)
    // speed: base: 20-25 nsec
    // ranlux_4: 230 nsec, ranlux_7: 430 nsec, ranlux_14: 810 nsec
    // This state representation makes operator== and save/restore more
    // difficult, because we've already computed "too much" and thus
    // have to undo some steps to get at x(i-r) etc.

    // state representation: next output (state) is x(i)
    //   x[0]  ... x[k] x[k+1]          ... x[long_lag-1]     represents
    //  x(i-k) ... x(i) x(i-long_lag+1) ... x(i-k-1)
    // speed: base 28 nsec
    // ranlux_4: 370 nsec, ranlux_7: 688 nsec, ranlux_14: 1343 nsec
    IntType x[long_lag];
    std::size_t k;
    IntType carry;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const bool subtract_with_carry_engine<IntType, w, s, r>::has_fixed_range;
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const IntType subtract_with_carry_engine<IntType, w, s, r>::modulus;
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_engine<IntType, w, s, r>::word_size;
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_engine<IntType, w, s, r>::long_lag;
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_engine<IntType, w, s, r>::short_lag;
template<class IntType, std::size_t w, std::size_t s, std::size_t r>
const uint32_t subtract_with_carry_engine<IntType, w, s, r>::default_seed;
#endif


// use a floating-point representation to produce values in [0..1)
/**
 * Instantiations of \subtract_with_carry_01_engine model a
 * \pseudo_random_number_generator.  The algorithm is
 * described in
 *
 *  @blockquote
 *  "A New Class of Random Number Generators", George
 *  Marsaglia and Arif Zaman, Annals of Applied Probability,
 *  Volume 1, Number 3 (1991), 462-480.
 *  @endblockquote
 */
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
class subtract_with_carry_01_engine
{
public:
    typedef RealType result_type;
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    BOOST_STATIC_CONSTANT(std::size_t, word_size = w);
    BOOST_STATIC_CONSTANT(std::size_t, long_lag = r);
    BOOST_STATIC_CONSTANT(std::size_t, short_lag = s);
    BOOST_STATIC_CONSTANT(boost::uint32_t, default_seed = 19780503u);

    BOOST_STATIC_ASSERT(!std::numeric_limits<result_type>::is_integer);

    /** Creates a new \subtract_with_carry_01_engine using the default seed. */
    subtract_with_carry_01_engine() { init_modulus(); seed(); }
    /** Creates a new subtract_with_carry_01_engine and seeds it with value. */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry_01_engine,
                                               boost::uint32_t, value)
    { init_modulus(); seed(value); }
    /**
     * Creates a new \subtract_with_carry_01_engine and seeds with values
     * produced by seq.generate().
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(subtract_with_carry_01_engine,
                                             SeedSeq, seq)
    { init_modulus(); seed(seq); }
    /**
     * Creates a new \subtract_with_carry_01_engine and seeds it with values
     * from a range.  Advances first to point one past the last consumed
     * value.  If the range does not contain enough elements to fill the
     * entire state, throws @c std::invalid_argument.
     */
    template<class It> subtract_with_carry_01_engine(It& first, It last)
    { init_modulus(); seed(first,last); }

private:
    /// \cond show_private
    void init_modulus()
    {
#ifndef BOOST_NO_STDC_NAMESPACE
        // allow for Koenig lookup
        using std::pow;
#endif
        _modulus = pow(RealType(2), RealType(word_size));
    }
    /// \endcond

public:
    // compiler-generated copy ctor and assignment operator are fine

    /** Seeds the generator with the default seed. */
    void seed() { seed(default_seed); }

    /** Seeds the generator with @c value. */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry_01_engine,
                                        boost::uint32_t, value)
    {
        typedef linear_congruential_engine<uint32_t, 40014, 0, 2147483563> gen_t;
        gen_t intgen(value == 0 ? default_seed : value);
        detail::generator_seed_seq<gen_t> gen(intgen);
        seed(gen);
    }

    /** Seeds the generator with values produced by @c seq.generate(). */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(subtract_with_carry_01_engine,
                                      SeedSeq, seq)
    {
        detail::seed_array_real<w>(seq, x);
        carry = (x[long_lag-1] ? result_type(0) : result_type(1 / _modulus));
        k = 0;
    }

    /**
     * Seeds the generator with values from a range.  Updates first to
     * point one past the last consumed element.  If there are not
     * enough elements in the range to fill the entire state, throws
     * @c std::invalid_argument.
     */
    template<class It>
    void seed(It& first, It last)
    {
        detail::fill_array_real<w>(first, last, x);
        carry = (x[long_lag-1] ? result_type(0) : result_type(1 / _modulus));
        k = 0;
    }

    /** Returns the smallest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return result_type(0); }
    /** Returns the largest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return result_type(1); }

    /** Returns the next value of the generator. */
    result_type operator()()
    {
        std::size_t short_index =
            (k < short_lag) ?
                (k + long_lag - short_lag) :
                (k - short_lag);
        carry = do_update(k, short_index, carry);
        RealType result = x[k];
        ++k;
        if(k >= long_lag)
            k = 0;
        return result;
    }

    /** Advances the state of the generator by @c z. */
    void discard(boost::uintmax_t z)
    { detail::subtract_with_carry_discard::apply(*this, z); }

    /** Fills a range with random values. */
    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_real(*this, first, last); }

    /** Writes a \subtract_with_carry_01_engine to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, subtract_with_carry_01_engine, f)
    {
        std::ios_base::fmtflags oldflags =
            os.flags(os.dec | os.fixed | os.left); 
        for(unsigned int j = 0; j < f.long_lag; ++j)
            os << (f.compute(j) * f._modulus) << ' ';
        os << (f.carry * f._modulus);
        os.flags(oldflags);
        return os;
    }
    
    /** Reads a \subtract_with_carry_01_engine from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, subtract_with_carry_01_engine, f)
    {
        RealType value;
        for(unsigned int j = 0; j < long_lag; ++j) {
            is >> value >> std::ws;
            f.x[j] = value / f._modulus;
        }
        is >> value;
        f.carry = value / f._modulus;
        f.k = 0;
        return is;
    }

    /** Returns true if the two generators will produce identical sequences. */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(subtract_with_carry_01_engine, x, y)
    {
        for(unsigned int j = 0; j < r; ++j)
            if(x.compute(j) != y.compute(j))
                return false;
        return true;
    }

    /** Returns true if the two generators will produce different sequences. */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(subtract_with_carry_01_engine)

private:
    /// \cond show_private
    RealType compute(unsigned int index) const
    {
        return x[(k+index) % long_lag];
    }

    friend struct detail::subtract_with_carry_discard;

    RealType do_update(std::size_t current, std::size_t short_index, RealType carry)
    {
        RealType delta = x[short_index] - x[current] - carry;
        if(delta < 0) {
            delta += RealType(1);
            carry = RealType(1)/_modulus;
        } else {
            carry = 0;
        }
        x[current] = delta;
        return carry;
    }
    /// \endcond
    std::size_t k;
    RealType carry;
    RealType x[long_lag];
    RealType _modulus;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
const bool subtract_with_carry_01_engine<RealType, w, s, r>::has_fixed_range;
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_01_engine<RealType, w, s, r>::word_size;
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_01_engine<RealType, w, s, r>::long_lag;
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
const std::size_t subtract_with_carry_01_engine<RealType, w, s, r>::short_lag;
template<class RealType, std::size_t w, std::size_t s, std::size_t r>
const uint32_t subtract_with_carry_01_engine<RealType, w, s, r>::default_seed;
#endif


/// \cond show_deprecated

template<class IntType, IntType m, unsigned s, unsigned r, IntType v>
class subtract_with_carry :
    public subtract_with_carry_engine<IntType,
        boost::static_log2<m>::value, s, r>
{
    typedef subtract_with_carry_engine<IntType,
        boost::static_log2<m>::value, s, r> base_type;
public:
    subtract_with_carry() {}
    BOOST_RANDOM_DETAIL_GENERATOR_CONSTRUCTOR(subtract_with_carry, Gen, gen)
    { seed(gen); }
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry,
                                               IntType, val)
    { seed(val); }
    template<class It>
    subtract_with_carry(It& first, It last) : base_type(first, last) {}
    void seed() { base_type::seed(); }
    BOOST_RANDOM_DETAIL_GENERATOR_SEED(subtract_with_carry, Gen, gen)
    {
        detail::generator_seed_seq<Gen> seq(gen);
        base_type::seed(seq);
    }
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry, IntType, val)
    { base_type::seed(val); }
    template<class It>
    void seed(It& first, It last) { base_type::seed(first, last); }
};

template<class RealType, int w, unsigned s, unsigned r, int v = 0>
class subtract_with_carry_01 :
    public subtract_with_carry_01_engine<RealType, w, s, r>
{
    typedef subtract_with_carry_01_engine<RealType, w, s, r> base_type;
public:
    subtract_with_carry_01() {}
    BOOST_RANDOM_DETAIL_GENERATOR_CONSTRUCTOR(subtract_with_carry_01, Gen, gen)
    { seed(gen); }
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(subtract_with_carry_01,
                                               uint32_t, val)
    { seed(val); }
    template<class It>
    subtract_with_carry_01(It& first, It last) : base_type(first, last) {}
    void seed() { base_type::seed(); }
    BOOST_RANDOM_DETAIL_GENERATOR_SEED(subtract_with_carry_01, Gen, gen)
    {
        detail::generator_seed_seq<Gen> seq(gen);
        base_type::seed(seq);
    }
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(subtract_with_carry_01, uint32_t, val)
    { base_type::seed(val); }
    template<class It>
    void seed(It& first, It last) { base_type::seed(first, last); }
};

/// \endcond

namespace detail {

template<class Engine>
struct generator_bits;

template<class RealType, std::size_t w, std::size_t s, std::size_t r>
struct generator_bits<subtract_with_carry_01_engine<RealType, w, s, r> > {
    static std::size_t value() { return w; }
};

template<class RealType, int w, unsigned s, unsigned r, int v>
struct generator_bits<subtract_with_carry_01<RealType, w, s, r, v> > {
    static std::size_t value() { return w; }
};

}

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_SUBTRACT_WITH_CARRY_HPP

/* subtract_with_carry.hpp
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
*/