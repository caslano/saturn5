/* boost random/shuffle_order.hpp header file
 *
 * Copyright Jens Maurer 2000-2001
 * Copyright Steven Watanabe 2010
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 */

#ifndef BOOST_RANDOM_SHUFFLE_ORDER_HPP
#define BOOST_RANDOM_SHUFFLE_ORDER_HPP

#include <iostream>
#include <algorithm>     // std::copy
#include <cassert>
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/signed_unsigned_tools.hpp>
#include <boost/random/linear_congruential.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {

/**
 * Instatiations of class template @c shuffle_order_engine model a
 * \pseudo_random_number_generator. It mixes the output
 * of some (usually \linear_congruential_engine)
 * \uniform_random_number_generator to get better statistical properties.
 * The algorithm is described in
 *
 *  @blockquote
 *  "Improving a poor random number generator", Carter Bays
 *  and S.D. Durham, ACM Transactions on Mathematical Software,
 *  Vol 2, No. 1, March 1976, pp. 59-64.
 *  http://doi.acm.org/10.1145/355666.355670
 *  @endblockquote
 *
 * The output of the base generator is buffered in an array of
 * length k. Every output X(n) has a second role: It gives an
 * index into the array where X(n+1) will be retrieved. Used
 * array elements are replaced with fresh output from the base
 * generator.
 *
 * Template parameters are the base generator and the array
 * length k, which should be around 100.
 */
template<class UniformRandomNumberGenerator, std::size_t k>
class shuffle_order_engine
{
public:
    typedef UniformRandomNumberGenerator base_type;
    typedef typename base_type::result_type result_type;

    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    BOOST_STATIC_CONSTANT(std::size_t, buffer_size = k);
    BOOST_STATIC_CONSTANT(std::size_t, table_size = k);

    BOOST_STATIC_ASSERT(std::numeric_limits<result_type>::is_integer);
    BOOST_STATIC_ASSERT(k > 0);

    /**
     * Constructs a @c shuffle_order_engine by invoking the
     * default constructor of the base generator.
     *
     * Complexity: Exactly k+1 invocations of the base generator.
     */
    shuffle_order_engine() : _rng() { init(); }
    /**
     * Constructs a @c shuffle_output_engine by invoking the one-argument
     * constructor of the base generator with the parameter seed.
     *
     * Complexity: Exactly k+1 invocations of the base generator.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(shuffle_order_engine,
                                               result_type, s)
    { _rng.seed(s); init(); }
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(shuffle_order_engine, SeedSeq, seq)
    { _rng.seed(seq); init(); }
    /**
     * Constructs a @c shuffle_output_engine by using a copy
     * of the provided generator.
     *
     * Precondition: The template argument UniformRandomNumberGenerator
     * shall denote a CopyConstructible type.
     *
     * Complexity: Exactly k+1 invocations of the base generator.
     */
    explicit shuffle_order_engine(const base_type & rng) : _rng(rng) { init(); }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
    explicit shuffle_order_engine(base_type&& rng) : _rng(rng) { init(); }
#endif

    template<class It> shuffle_order_engine(It& first, It last)
      : _rng(first, last) { init(); }
    void seed() { _rng.seed(); init(); }
    /**
     * Invokes the one-argument seed method of the base generator
     * with the parameter seed and re-initializes the internal buffer array.
     *
     * Complexity: Exactly k+1 invocations of the base generator.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(shuffle_order_engine,
        result_type, seed_arg)
    { _rng.seed(seed_arg); init(); }
    /**
     * Invokes the one-argument seed method of the base generator
     * with the parameter seq and re-initializes the internal buffer array.
     *
     * Complexity: Exactly k+1 invocations of the base generator.
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(shuffle_order_engine, SeedSeq, seq)
    { _rng.seed(seq); init(); }
    template<class It> void seed(It& first, It last)
    { _rng.seed(first, last); init(); }

    const base_type& base() const { return _rng; }

    result_type operator()() {
        // calculating the range every time may seem wasteful.  However, this
        // makes the information locally available for the optimizer.
        typedef typename boost::random::traits::make_unsigned<result_type>::type base_unsigned;
        const base_unsigned brange =
            detail::subtract<result_type>()((max)(), (min)());
        const base_unsigned off =
            detail::subtract<result_type>()(y, (min)());

        base_unsigned j;
        if(k == 1) {
            j = 0;
        } else if(brange < (std::numeric_limits<base_unsigned>::max)() / k) {
            // try to do it in the native type if we know that it won't
            // overflow
            j = k * off / (brange + 1);
        } else if(brange < (std::numeric_limits<uintmax_t>::max)() / k) {
            // Otherwise try to use uint64_t
            j = static_cast<base_unsigned>(
                static_cast<uintmax_t>(off) * k /
                (static_cast<uintmax_t>(brange) + 1));
        } else {
            boost::uintmax_t divisor =
                static_cast<boost::uintmax_t>(brange) + 1;
            j = static_cast<base_unsigned>(detail::muldiv(off, k, divisor));
        }
        // assert(0 <= j && j < k);
        y = v[j];
        v[j] = _rng();
        return y;
    }

    /** Advances the generator by z steps. */
    void discard(boost::uintmax_t z)
    {
        for(boost::uintmax_t j = 0; j < z; ++j) {
            (*this)();
        }
    }

    /** Fills a range with pseudo-random values. */
    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    /** Returns the smallest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return (base_type::min)(); }
    /** Returns the largest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return (base_type::max)(); }

    /** Writes a @c shuffle_order_engine to a @c std::ostream. */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, shuffle_order_engine, s)
    {
        os << s._rng;
        for(std::size_t i = 0; i < k; ++i)
            os << ' ' << s.v[i];
        os << ' ' << s.y;
        return os;
    }

    /** Reads a @c shuffle_order_engine from a @c std::istream. */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, shuffle_order_engine, s)
    {
        is >> s._rng;
        for(std::size_t i = 0; i < k; ++i)
            is >> std::ws >> s.v[i];
        is >> std::ws >> s.y;
        return is;
    }

    /** Returns true if the two generators will produce identical sequences. */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(shuffle_order_engine, x, y)
    { return x._rng == y._rng && x.y == y.y && std::equal(x.v, x.v+k, y.v); }
    /** Returns true if the two generators will produce different sequences. */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(shuffle_order_engine)

private:

    /// \cond show_private

    void init()
    {
        // we cannot use std::generate, because it uses pass-by-value for _rng
        for(result_type * p = v; p != v+k; ++p)
            *p = _rng();
        y = _rng();
    }

    /// \endcond

    base_type _rng;
    result_type v[k];
    result_type y;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class URNG, std::size_t k>
const bool shuffle_order_engine<URNG, k>::has_fixed_range;
template<class URNG, std::size_t k>
const std::size_t shuffle_order_engine<URNG, k>::table_size;
template<class URNG, std::size_t k>
const std::size_t shuffle_order_engine<URNG, k>::buffer_size;
#endif

/**
 * According to Harry Erwin (private e-mail), the specialization
 * @c kreutzer1986 was suggested in:
 *
 * @blockquote
 * "System Simulation: Programming Styles and Languages (International
 * Computer Science Series)", Wolfgang Kreutzer, Addison-Wesley, December 1986.
 * @endblockquote
 */
typedef shuffle_order_engine<
    linear_congruential_engine<uint32_t, 1366, 150889, 714025>,
    97> kreutzer1986;

/**
 * The specialization @c knuth_b is specified by the C++ standard.
 * It is described in
 *
 * @blockquote
 * "The Art of Computer Programming, Second Edition, Volume 2,
 * Seminumerical Algorithms", Donald Knuth, Addison-Wesley, 1981.
 * @endblockquote
 */
typedef shuffle_order_engine<minstd_rand0, 256> knuth_b;

} // namespace random

using random::kreutzer1986;

} // namespace boost

#include <boost/random/detail/enable_warnings.hpp>

#endif // BOOST_RANDOM_SHUFFLE_OUTPUT_HPP

/* shuffle_order.hpp
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
*/