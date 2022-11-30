/* boost random/inversive_congruential.hpp header file
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

#ifndef BOOST_RANDOM_INVERSIVE_CONGRUENTIAL_HPP
#define BOOST_RANDOM_INVERSIVE_CONGRUENTIAL_HPP

#include <iosfwd>
#include <stdexcept>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/const_mod.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/seed_impl.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {

// Eichenauer and Lehn 1986
/**
 * Instantiations of class template @c inversive_congruential_engine model a
 * \pseudo_random_number_generator. It uses the inversive congruential
 * algorithm (ICG) described in
 *
 *  @blockquote
 *  "Inversive pseudorandom number generators: concepts, results and links",
 *  Peter Hellekalek, In: "Proceedings of the 1995 Winter Simulation
 *  Conference", C. Alexopoulos, K. Kang, W.R. Lilegdon, and D. Goldsman
 *  (editors), 1995, pp. 255-262. ftp://random.mat.sbg.ac.at/pub/data/wsc95.ps
 *  @endblockquote
 *
 * The output sequence is defined by x(n+1) = (a*inv(x(n)) - b) (mod p),
 * where x(0), a, b, and the prime number p are parameters of the generator.
 * The expression inv(k) denotes the multiplicative inverse of k in the
 * field of integer numbers modulo p, with inv(0) := 0.
 *
 * The template parameter IntType shall denote a signed integral type large
 * enough to hold p; a, b, and p are the parameters of the generators. The
 * template parameter val is the validation value checked by validation.
 *
 * @xmlnote
 * The implementation currently uses the Euclidian Algorithm to compute
 * the multiplicative inverse. Therefore, the inversive generators are about
 * 10-20 times slower than the others (see section"performance"). However,
 * the paper talks of only 3x slowdown, so the Euclidian Algorithm is probably
 * not optimal for calculating the multiplicative inverse.
 * @endxmlnote
 */
template<class IntType, IntType a, IntType b, IntType p>
class inversive_congruential_engine
{
public:
    typedef IntType result_type;
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);

    BOOST_STATIC_CONSTANT(result_type, multiplier = a);
    BOOST_STATIC_CONSTANT(result_type, increment = b);
    BOOST_STATIC_CONSTANT(result_type, modulus = p);
    BOOST_STATIC_CONSTANT(IntType, default_seed = 1);

    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () { return b == 0 ? 1 : 0; }
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () { return p-1; }
    
    /**
     * Constructs an @c inversive_congruential_engine, seeding it with
     * the default seed.
     */
    inversive_congruential_engine() { seed(); }

    /**
     * Constructs an @c inversive_congruential_engine, seeding it with @c x0.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(inversive_congruential_engine,
                                               IntType, x0)
    { seed(x0); }
    
    /**
     * Constructs an @c inversive_congruential_engine, seeding it with values
     * produced by a call to @c seq.generate().
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(inversive_congruential_engine,
                                             SeedSeq, seq)
    { seed(seq); }
    
    /**
     * Constructs an @c inversive_congruential_engine, seeds it
     * with values taken from the itrator range [first, last),
     * and adjusts first to point to the element after the last one
     * used.  If there are not enough elements, throws @c std::invalid_argument.
     *
     * first and last must be input iterators.
     */
    template<class It> inversive_congruential_engine(It& first, It last)
    { seed(first, last); }

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
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(inversive_congruential_engine, IntType, x0)
    {
        // wrap _x if it doesn't fit in the destination
        if(modulus == 0) {
            _value = x0;
        } else {
            _value = x0 % modulus;
        }
        // handle negative seeds
        if(_value <= 0 && _value != 0) {
            _value += modulus;
        }
        // adjust to the correct range
        if(increment == 0 && _value == 0) {
            _value = 1;
        }
        BOOST_ASSERT(_value >= (min)());
        BOOST_ASSERT(_value <= (max)());
    }

    /**
     * Seeds an @c inversive_congruential_engine using values from a SeedSeq.
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(inversive_congruential_engine, SeedSeq, seq)
    { seed(detail::seed_one_int<IntType, modulus>(seq)); }
    
    /**
     * seeds an @c inversive_congruential_engine with values taken
     * from the itrator range [first, last) and adjusts @c first to
     * point to the element after the last one used.  If there are
     * not enough elements, throws @c std::invalid_argument.
     *
     * @c first and @c last must be input iterators.
     */
    template<class It> void seed(It& first, It last)
    { seed(detail::get_one_int<IntType, modulus>(first, last)); }

    /** Returns the next output of the generator. */
    IntType operator()()
    {
        typedef const_mod<IntType, p> do_mod;
        _value = do_mod::mult_add(a, do_mod::invert(_value), b);
        return _value;
    }
  
    /** Fills a range with random values */
    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    /** Advances the state of the generator by @c z. */
    void discard(boost::uintmax_t z)
    {
        for(boost::uintmax_t j = 0; j < z; ++j) {
            (*this)();
        }
    }

    /**
     * Writes the textual representation of the generator to a @c std::ostream.
     */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, inversive_congruential_engine, x)
    {
        os << x._value;
        return os;
    }

    /**
     * Reads the textual representation of the generator from a @c std::istream.
     */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, inversive_congruential_engine, x)
    {
        is >> x._value;
        return is;
    }

    /**
     * Returns true if the two generators will produce identical
     * sequences of outputs.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(inversive_congruential_engine, x, y)
    { return x._value == y._value; }

    /**
     * Returns true if the two generators will produce different
     * sequences of outputs.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(inversive_congruential_engine)

private:
    IntType _value;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class IntType, IntType a, IntType b, IntType p>
const bool inversive_congruential_engine<IntType, a, b, p>::has_fixed_range;
template<class IntType, IntType a, IntType b, IntType p>
const typename inversive_congruential_engine<IntType, a, b, p>::result_type inversive_congruential_engine<IntType, a, b, p>::multiplier;
template<class IntType, IntType a, IntType b, IntType p>
const typename inversive_congruential_engine<IntType, a, b, p>::result_type inversive_congruential_engine<IntType, a, b, p>::increment;
template<class IntType, IntType a, IntType b, IntType p>
const typename inversive_congruential_engine<IntType, a, b, p>::result_type inversive_congruential_engine<IntType, a, b, p>::modulus;
template<class IntType, IntType a, IntType b, IntType p>
const typename inversive_congruential_engine<IntType, a, b, p>::result_type inversive_congruential_engine<IntType, a, b, p>::default_seed;
#endif

/// \cond show_deprecated

// provided for backwards compatibility
template<class IntType, IntType a, IntType b, IntType p, IntType val = 0>
class inversive_congruential : public inversive_congruential_engine<IntType, a, b, p>
{
    typedef inversive_congruential_engine<IntType, a, b, p> base_type;
public:
    inversive_congruential(IntType x0 = 1) : base_type(x0) {}
    template<class It>
    inversive_congruential(It& first, It last) : base_type(first, last) {}
};

/// \endcond

/**
 * The specialization hellekalek1995 was suggested in
 *
 *  @blockquote
 *  "Inversive pseudorandom number generators: concepts, results and links",
 *  Peter Hellekalek, In: "Proceedings of the 1995 Winter Simulation
 *  Conference", C. Alexopoulos, K. Kang, W.R. Lilegdon, and D. Goldsman
 *  (editors), 1995, pp. 255-262. ftp://random.mat.sbg.ac.at/pub/data/wsc95.ps
 *  @endblockquote
 */
typedef inversive_congruential_engine<uint32_t, 9102, 2147483647-36884165,
  2147483647> hellekalek1995;

} // namespace random

using random::hellekalek1995;

} // namespace boost

#include <boost/random/detail/enable_warnings.hpp>

#endif // BOOST_RANDOM_INVERSIVE_CONGRUENTIAL_HPP

/* inversive_congruential.hpp
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
*/