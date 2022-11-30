/* boost random/independent_bits.hpp header file
 *
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

#ifndef BOOST_RANDOM_INDEPENDENT_BITS_HPP
#define BOOST_RANDOM_INDEPENDENT_BITS_HPP

#include <istream>
#include <iosfwd>
#include <boost/assert.hpp>
#include <boost/limits.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer/integer_mask.hpp>
#include <boost/random/traits.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/integer_log2.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/seed_impl.hpp>
#include <boost/random/detail/signed_unsigned_tools.hpp>

namespace boost {
namespace random {

/**
 * An instantiation of class template @c independent_bits_engine
 * model a \pseudo_random_number_generator.  It generates random
 * numbers distributed between [0, 2^w) by combining one or
 * more invocations of the base engine.
 *
 * Requires: 0 < w <= std::numeric_limits<UIntType>::digits
 */
template<class Engine, std::size_t w, class UIntType>
class independent_bits_engine
{
public:
    typedef Engine base_type;
    typedef UIntType result_type;
    typedef typename Engine::result_type base_result_type;

    // Required by old Boost.Random concept
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);

    /** Returns the smallest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return 0; }
    /** Returns the largest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return max_imp(boost::is_integral<UIntType>()); }

    /**
     * Constructs an @c independent_bits_engine using the
     * default constructor of the base generator.
     */
    independent_bits_engine() { }

    /**
     * Constructs an @c independent_bits_engine, using seed as
     * the constructor argument for both base generators.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(independent_bits_engine,
        base_result_type, seed_arg)
    {
        _base.seed(seed_arg);
    }

    /**
     * Constructs an @c independent_bits_engine, using seq as
     * the constructor argument for the base generator.
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(independent_bits_engine,
        SeedSeq, seq)
    { _base.seed(seq); }

    /** Constructs an @c independent_bits_engine by copying @c base. */
    independent_bits_engine(const base_type& base_arg) : _base(base_arg) {}

    /**
     * Contructs an @c independent_bits_engine with
     * values from the range defined by the input iterators first
     * and last.  first will be modified to point to the element
     * after the last one used.
     *
     * Throws: @c std::invalid_argument if the input range is too small.
     *
     * Exception Safety: Basic
     */
    template<class It>
    independent_bits_engine(It& first, It last) : _base(first, last) { }

    /**
     * Seeds an @c independent_bits_engine using the default
     * seed of the base generator.
     */
    void seed() { _base.seed(); }

    /**
     * Seeds an @c independent_bits_engine, using @c seed as the
     * seed for the base generator.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(independent_bits_engine,
        base_result_type, seed_arg)
    { _base.seed(seed_arg); }

    /**
     * Seeds an @c independent_bits_engine, using @c seq to
     * seed the base generator.
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(independent_bits_engine,
        SeedSeq, seq)
    { _base.seed(seq); }

    /**
     * Seeds an @c independent_bits_engine with
     * values from the range defined by the input iterators first
     * and last.  first will be modified to point to the element
     * after the last one used.
     *
     * Throws: @c std::invalid_argument if the input range is too small.
     *
     * Exception Safety: Basic
     */
    template<class It> void seed(It& first, It last)
    { _base.seed(first, last); }

    /** Returns the next value of the generator. */
    result_type operator()()
    {
        // While it may seem wasteful to recalculate this
        // every time, both msvc and gcc can propagate
        // constants, resolving this at compile time.
        base_unsigned range =
            detail::subtract<base_result_type>()((_base.max)(), (_base.min)());
        std::size_t m =
            (range == (std::numeric_limits<base_unsigned>::max)()) ?
                std::numeric_limits<base_unsigned>::digits :
                detail::integer_log2(range + 1);
        std::size_t n = (w + m - 1) / m;
        std::size_t w0, n0;
        base_unsigned y0, y1;
        base_unsigned y0_mask, y1_mask;
        calc_params(n, range, w0, n0, y0, y1, y0_mask, y1_mask);
        if(base_unsigned(range - y0 + 1) > y0 / n) {
            // increment n and try again.
            ++n;
            calc_params(n, range, w0, n0, y0, y1, y0_mask, y1_mask);
        }

        BOOST_ASSERT(n0*w0 + (n - n0)*(w0 + 1) == w);

        BOOST_ASSERT((n == 1) == (w0 == w));

        // special case to avoid undefined behavior from shifting
        if(n == 1) {
            BOOST_ASSERT(n0 == 1);
            base_unsigned u;
            do {
                u = detail::subtract<base_result_type>()(_base(), (_base.min)());
            } while(u > base_unsigned(y0 - 1));
            return u & y0_mask;
        }

        result_type S = 0;
        for(std::size_t k = 0; k < n0; ++k) {
            base_unsigned u;
            do {
                u = detail::subtract<base_result_type>()(_base(), (_base.min)());
            } while(u > base_unsigned(y0 - 1));
            S = (S << w0) + (u & y0_mask);
        }
        for(std::size_t k = 0; k < (n - n0); ++k) {
            base_unsigned u;
            do {
                u = detail::subtract<base_result_type>()(_base(), (_base.min)());
            } while(u > base_unsigned(y1 - 1));
            S = (S << (w0 + 1)) + (u & y1_mask);
        }
        return S;
    }
  
    /** Fills a range with random values */
    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    /** Advances the state of the generator by @c z. */
    void discard(boost::uintmax_t z)
    {
        for(boost::uintmax_t i = 0; i < z; ++i) {
            (*this)();
        }
    }

    const base_type& base() const { return _base; }

    /**
     * Writes the textual representation if the generator to a @c std::ostream.
     * The textual representation of the engine is the textual representation
     * of the base engine.
     */
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, independent_bits_engine, r)
    {
        os << r._base;
        return os;
    }

    /**
     * Reads the state of an @c independent_bits_engine from a
     * @c std::istream.
     */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, independent_bits_engine, r)
    {
        is >> r._base;
        return is;
    }

    /**
     * Returns: true iff the two @c independent_bits_engines will
     * produce the same sequence of values.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(independent_bits_engine, x, y)
    { return x._base == y._base; }
    /**
     * Returns: true iff the two @c independent_bits_engines will
     * produce different sequences of values.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(independent_bits_engine)

private:

    /// \cond show_private
    typedef typename boost::random::traits::make_unsigned<base_result_type>::type base_unsigned;

    static BOOST_CONSTEXPR UIntType max_imp(const boost::true_type&)
    {
       return boost::low_bits_mask_t<w>::sig_bits;
    }
    static UIntType max_imp(const boost::false_type&)
    {
       // We have a multiprecision integer type:
       BOOST_STATIC_ASSERT(std::numeric_limits<UIntType>::is_specialized);
       return w < std::numeric_limits<UIntType>::digits ? UIntType((UIntType(1) << w) - 1) : UIntType((((UIntType(1) << (w - 1)) - 1) << 1) | 1u);
    }

    void calc_params(
        std::size_t n, base_unsigned range,
        std::size_t& w0, std::size_t& n0,
        base_unsigned& y0, base_unsigned& y1,
        base_unsigned& y0_mask, base_unsigned& y1_mask)
    {
        BOOST_ASSERT(w >= n);
        w0 = w/n;
        n0 = n - w % n;
        y0_mask = (base_unsigned(2) << (w0 - 1)) - 1;
        y1_mask = (y0_mask << 1) | 1;
        y0 = (range + 1) & ~y0_mask;
        y1 = (range + 1) & ~y1_mask;
        BOOST_ASSERT(y0 != 0 || base_unsigned(range + 1) == 0);
    }
    /// \endcond

    Engine _base;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
template<class Engine, std::size_t w, class UIntType>
const bool independent_bits_engine<Engine, w, UIntType>::has_fixed_range;
#endif

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_INDEPENDENT_BITS_HPP

/* independent_bits.hpp
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
*/