/* boost random/additive_combine.hpp header file
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

#ifndef BOOST_RANDOM_ADDITIVE_COMBINE_HPP
#define BOOST_RANDOM_ADDITIVE_COMBINE_HPP

#include <istream>
#include <iosfwd>
#include <algorithm> // for std::min and std::max
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/linear_congruential.hpp>

namespace boost {
namespace random {

/**
 * An instantiation of class template @c additive_combine_engine models a
 * \pseudo_random_number_generator. It combines two multiplicative
 * \linear_congruential_engine number generators, i.e. those with @c c = 0.
 * It is described in
 *
 *  @blockquote
 *  "Efficient and Portable Combined Random Number Generators", Pierre L'Ecuyer,
 *  Communications of the ACM, Vol. 31, No. 6, June 1988, pp. 742-749, 774
 *  @endblockquote
 *
 * The template parameters MLCG1 and MLCG2 shall denote two different
 * \linear_congruential_engine number generators, each with c = 0. Each
 * invocation returns a random number
 * X(n) := (MLCG1(n) - MLCG2(n)) mod (m1 - 1),
 * where m1 denotes the modulus of MLCG1. 
 */
template<class MLCG1, class MLCG2>
class additive_combine_engine
{
public:
    typedef MLCG1 first_base;
    typedef MLCG2 second_base;
    typedef typename MLCG1::result_type result_type;

    // Required by old Boost.Random concept
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    /**
     * Returns the smallest value that the generator can produce
     */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return 1; }
    /**
     * Returns the largest value that the generator can produce
     */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return MLCG1::modulus-1; }

    /**
     * Constructs an @c additive_combine_engine using the
     * default constructors of the two base generators.
     */
    additive_combine_engine() : _mlcg1(), _mlcg2() { }
    /**
     * Constructs an @c additive_combine_engine, using seed as
     * the constructor argument for both base generators.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(additive_combine_engine,
        result_type, seed_arg)
    {
        _mlcg1.seed(seed_arg);
        _mlcg2.seed(seed_arg);
    }
    /**
     * Constructs an @c additive_combine_engine, using seq as
     * the constructor argument for both base generators.
     *
     * @xmlwarning
     * The semantics of this function are liable to change.
     * A @c seed_seq is designed to generate all the seeds
     * in one shot, but this seeds the two base engines
     * independantly and probably ends up giving the same
     * sequence to both.
     * @endxmlwarning
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(additive_combine_engine,
        SeedSeq, seq)
    {
        _mlcg1.seed(seq);
        _mlcg2.seed(seq);
    }
    /**
     * Constructs an @c additive_combine_engine, using
     * @c seed1 and @c seed2 as the constructor argument to
     * the first and second base generators, respectively.
     */
    additive_combine_engine(typename MLCG1::result_type seed1, 
                            typename MLCG2::result_type seed2)
      : _mlcg1(seed1), _mlcg2(seed2) { }
    /**
     * Contructs an @c additive_combine_engine with
     * values from the range defined by the input iterators first
     * and last.  first will be modified to point to the element
     * after the last one used.
     *
     * Throws: @c std::invalid_argument if the input range is too small.
     *
     * Exception Safety: Basic
     */
    template<class It> additive_combine_engine(It& first, It last)
      : _mlcg1(first, last), _mlcg2(first, last) { }

    /**
     * Seeds an @c additive_combine_engine using the default
     * seeds of the two base generators.
     */
    void seed()
    {
        _mlcg1.seed();
        _mlcg2.seed();
    }

    /**
     * Seeds an @c additive_combine_engine, using @c seed as the
     * seed for both base generators.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(additive_combine_engine,
        result_type, seed_arg)
    {
        _mlcg1.seed(seed_arg);
        _mlcg2.seed(seed_arg);
    }

    /**
     * Seeds an @c additive_combine_engine, using @c seq to
     * seed both base generators.
     *
     * See the warning on the corresponding constructor.
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(additive_combine_engine,
        SeedSeq, seq)
    {
        _mlcg1.seed(seq);
        _mlcg2.seed(seq);
    }

    /**
     * Seeds an @c additive_combine generator, using @c seed1 and @c seed2 as
     * the seeds to the first and second base generators, respectively.
     */
    void seed(typename MLCG1::result_type seed1,
              typename MLCG2::result_type seed2)
    {
        _mlcg1.seed(seed1);
        _mlcg2.seed(seed2);
    }

    /**
     * Seeds an @c additive_combine_engine with
     * values from the range defined by the input iterators first
     * and last.  first will be modified to point to the element
     * after the last one used.
     *
     * Throws: @c std::invalid_argument if the input range is too small.
     *
     * Exception Safety: Basic
     */
    template<class It> void seed(It& first, It last)
    {
        _mlcg1.seed(first, last);
        _mlcg2.seed(first, last);
    }

    /** Returns the next value of the generator. */
    result_type operator()() {
        result_type val1 = _mlcg1();
        result_type val2 = _mlcg2();
        if(val2 < val1) return val1 - val2;
        else return val1 - val2 + MLCG1::modulus - 1;
    }
  
    /** Fills a range with random values */
    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    /** Advances the state of the generator by @c z. */
    void discard(boost::uintmax_t z)
    {
        _mlcg1.discard(z);
        _mlcg2.discard(z);
    }

    /**
     * Writes the state of an @c additive_combine_engine to a @c
     * std::ostream.  The textual representation of an @c
     * additive_combine_engine is the textual representation of
     * the first base generator followed by the textual representation
     * of the second base generator.
     */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, additive_combine_engine, r)
    { os << r._mlcg1 << ' ' << r._mlcg2; return os; }

    /**
     * Reads the state of an @c additive_combine_engine from a
     * @c std::istream.
     */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, additive_combine_engine, r)
    { is >> r._mlcg1 >> std::ws >> r._mlcg2; return is; }

    /**
     * Returns: true iff the two @c additive_combine_engines will
     * produce the same sequence of values.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(additive_combine_engine, x, y)
    { return x._mlcg1 == y._mlcg1 && x._mlcg2 == y._mlcg2; }
    /**
     * Returns: true iff the two @c additive_combine_engines will
     * produce different sequences of values.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(additive_combine_engine)

private:
    MLCG1 _mlcg1;
    MLCG2 _mlcg2;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
template<class MLCG1, class MLCG2>
const bool additive_combine_engine<MLCG1, MLCG2>::has_fixed_range;
#endif

/// \cond show_deprecated

/** Provided for backwards compatibility. */
template<class MLCG1, class MLCG2, typename MLCG1::result_type val = 0>
class additive_combine : public additive_combine_engine<MLCG1, MLCG2>
{
    typedef additive_combine_engine<MLCG1, MLCG2> base_t;
public:
    typedef typename base_t::result_type result_type;
    additive_combine() {}
    template<class T>
    additive_combine(T& arg) : base_t(arg) {}
    template<class T>
    additive_combine(const T& arg) : base_t(arg) {}
    template<class It>
    additive_combine(It& first, It last) : base_t(first, last) {}
};

/// \endcond

/**
 * The specialization \ecuyer1988 was suggested in
 *
 *  @blockquote
 *  "Efficient and Portable Combined Random Number Generators", Pierre L'Ecuyer,
 *  Communications of the ACM, Vol. 31, No. 6, June 1988, pp. 742-749, 774
 *  @endblockquote
 */
typedef additive_combine_engine<
    linear_congruential_engine<uint32_t, 40014, 0, 2147483563>,
    linear_congruential_engine<uint32_t, 40692, 0, 2147483399>
> ecuyer1988;

} // namespace random

using random::ecuyer1988;

} // namespace boost

#endif // BOOST_RANDOM_ADDITIVE_COMBINE_HPP

/* additive_combine.hpp
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
*/