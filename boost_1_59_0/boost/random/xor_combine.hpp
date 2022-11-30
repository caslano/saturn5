/* boost random/xor_combine.hpp header file
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
 */

#ifndef BOOST_RANDOM_XOR_COMBINE_HPP
#define BOOST_RANDOM_XOR_COMBINE_HPP

#include <istream>
#include <iosfwd>
#include <cassert>
#include <algorithm> // for std::min and std::max
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/cstdint.hpp>     // uint32_t
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/seed_impl.hpp>
#include <boost/random/detail/operators.hpp>

namespace boost {
namespace random {

/**
 * Instantiations of @c xor_combine_engine model a
 * \pseudo_random_number_generator.  To produce its output it
 * invokes each of the base generators, shifts their results
 * and xors them together.
 */
template<class URNG1, int s1, class URNG2, int s2>
class xor_combine_engine
{
public:
    typedef URNG1 base1_type;
    typedef URNG2 base2_type;
    typedef typename base1_type::result_type result_type;

    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    BOOST_STATIC_CONSTANT(int, shift1 = s1);
    BOOST_STATIC_CONSTANT(int, shift2 = s2);

    /**
     * Constructors a @c xor_combine_engine by default constructing
     * both base generators.
     */
    xor_combine_engine() : _rng1(), _rng2() { }

    /** Constructs a @c xor_combine by copying two base generators. */
    xor_combine_engine(const base1_type & rng1, const base2_type & rng2)
      : _rng1(rng1), _rng2(rng2) { }

    /**
     * Constructs a @c xor_combine_engine, seeding both base generators
     * with @c v.
     *
     * @xmlwarning
     * The exact algorithm used by this function may change in the future.
     * @endxmlwarning
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(xor_combine_engine,
        result_type, v)
    { seed(v); }

    /**
     * Constructs a @c xor_combine_engine, seeding both base generators
     * with values produced by @c seq.
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(xor_combine_engine,
        SeedSeq, seq)
    { seed(seq); }

    /**
     * Constructs a @c xor_combine_engine, seeding both base generators
     * with values from the iterator range [first, last) and changes
     * first to point to the element after the last one used.  If there
     * are not enough elements in the range to seed both generators,
     * throws @c std::invalid_argument.
     */
    template<class It> xor_combine_engine(It& first, It last)
      : _rng1(first, last), _rng2( /* advanced by other call */ first, last) { }

    /** Calls @c seed() for both base generators. */
    void seed() { _rng1.seed(); _rng2.seed(); }

    /** @c seeds both base generators with @c v. */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(xor_combine_engine, result_type, v)
    { _rng1.seed(v); _rng2.seed(v); }

    /** @c seeds both base generators with values produced by @c seq. */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(xor_combine_engine, SeedSeq, seq)
    { _rng1.seed(seq); _rng2.seed(seq); }

    /**
     * seeds both base generators with values from the iterator
     * range [first, last) and changes first to point to the element
     * after the last one used.  If there are not enough elements in
     * the range to seed both generators, throws @c std::invalid_argument.
     */
    template<class It> void seed(It& first, It last)
    {
        _rng1.seed(first, last);
        _rng2.seed(first, last);
    }

    /** Returns the first base generator. */
    const base1_type& base1() const { return _rng1; }

    /** Returns the second base generator. */
    const base2_type& base2() const { return _rng2; }

    /** Returns the next value of the generator. */
    result_type operator()()
    {
        return (_rng1() << s1) ^ (_rng2() << s2);
    }
  
    /** Fills a range with random values */
    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    /** Advances the state of the generator by @c z. */
    void discard(boost::uintmax_t z)
    {
        _rng1.discard(z);
        _rng2.discard(z);
    }

    /** Returns the smallest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return (URNG1::min)()<(URNG2::min)()?(URNG1::min)():(URNG2::min)(); }
    /** Returns the largest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return (URNG1::max)()>(URNG2::max)()?(URNG1::max)():(URNG2::max)(); }

    /**
     * Writes the textual representation of the generator to a @c std::ostream.
     */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, xor_combine_engine, s)
    {
        os << s._rng1 << ' ' << s._rng2;
        return os;
    }
    
    /**
     * Reads the textual representation of the generator from a @c std::istream.
     */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, xor_combine_engine, s)
    {
        is >> s._rng1 >> std::ws >> s._rng2;
        return is;
    }
    
    /** Returns true if the two generators will produce identical sequences. */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(xor_combine_engine, x, y)
    { return x._rng1 == y._rng1 && x._rng2 == y._rng2; }
    
    /** Returns true if the two generators will produce different sequences. */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(xor_combine_engine)

private:
    base1_type _rng1;
    base2_type _rng2;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class URNG1, int s1, class URNG2, int s2>
const bool xor_combine_engine<URNG1, s1, URNG2, s2>::has_fixed_range;
template<class URNG1, int s1, class URNG2, int s2>
const int xor_combine_engine<URNG1, s1, URNG2, s2>::shift1;
template<class URNG1, int s1, class URNG2, int s2>
const int xor_combine_engine<URNG1, s1, URNG2, s2>::shift2;
#endif

/// \cond show_private

/** Provided for backwards compatibility. */
template<class URNG1, int s1, class URNG2, int s2,
    typename URNG1::result_type v = 0>
class xor_combine : public xor_combine_engine<URNG1, s1, URNG2, s2>
{
    typedef xor_combine_engine<URNG1, s1, URNG2, s2> base_type;
public:
    typedef typename base_type::result_type result_type;
    xor_combine() {}
    xor_combine(result_type val) : base_type(val) {}
    template<class It>
    xor_combine(It& first, It last) : base_type(first, last) {}
    xor_combine(const URNG1 & rng1, const URNG2 & rng2)
      : base_type(rng1, rng2) { }

    result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (std::min)((this->base1().min)(), (this->base2().min)()); }
    result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () const { return (std::max)((this->base1().min)(), (this->base2().max)()); }
};

/// \endcond

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_XOR_COMBINE_HPP

/* xor_combine.hpp
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
*/