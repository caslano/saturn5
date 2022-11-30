/* boost random/lagged_fibonacci.hpp header file
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
 *  2013-10-14  fixed some warnings with Wshadow (mgaunard)
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_LAGGED_FIBONACCI_HPP
#define BOOST_RANDOM_LAGGED_FIBONACCI_HPP

#include <istream>
#include <iosfwd>
#include <algorithm>     // std::max
#include <iterator>
#include <boost/config/no_tr1/cmath.hpp>         // std::pow
#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer/integer_mask.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/operators.hpp>
#include <boost/random/detail/generator_seed_seq.hpp>

namespace boost {
namespace random {

/**
 * Instantiations of class template \lagged_fibonacci_engine model a
 * \pseudo_random_number_generator. It uses a lagged Fibonacci
 * algorithm with two lags @c p and @c q:
 * x(i) = x(i-p) + x(i-q) (mod 2<sup>w</sup>) with p > q.
 */
template<class UIntType, int w, unsigned int p, unsigned int q>
class lagged_fibonacci_engine
{
public:
    typedef UIntType result_type;
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    BOOST_STATIC_CONSTANT(int, word_size = w);
    BOOST_STATIC_CONSTANT(unsigned int, long_lag = p);
    BOOST_STATIC_CONSTANT(unsigned int, short_lag = q);

    BOOST_STATIC_CONSTANT(UIntType, default_seed = 331u);

    /** Returns the smallest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () { return 0; }
    /** Returns the largest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return low_bits_mask_t<w>::sig_bits; }

    /** Creates a new @c lagged_fibonacci_engine and calls @c seed(). */
    lagged_fibonacci_engine() { seed(); }

    /** Creates a new @c lagged_fibonacci_engine and calls @c seed(value). */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(lagged_fibonacci_engine,
        UIntType, value)
    { seed(value); }

    /** Creates a new @c lagged_fibonacci_engine and calls @c seed(seq). */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(lagged_fibonacci_engine,
        SeedSeq, seq)
    { seed(seq); }

    /**
     * Creates a new @c lagged_fibonacci_engine and calls @c seed(first, last).
     */
    template<class It> lagged_fibonacci_engine(It& first, It last)
    { seed(first, last); }

    // compiler-generated copy ctor and assignment operator are fine

    /** Calls @c seed(default_seed). */
    void seed() { seed(default_seed); }

    /**
     * Sets the state of the generator to values produced by
     * a \minstd_rand0 generator.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(lagged_fibonacci_engine,
        UIntType, value)
    {
        minstd_rand0 intgen(static_cast<boost::uint32_t>(value));
        detail::generator_seed_seq<minstd_rand0> gen(intgen);
        seed(gen);
    }

    /**
     * Sets the state of the generator using values produced by seq.
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(lagged_fibonacci_engine, SeedSeq, seq)
    {
        detail::seed_array_int<w>(seq, x);
        i = long_lag;
    }

    /**
     * Sets the state of the generator to values from the iterator
     * range [first, last).  If there are not enough elements in the
     * range [first, last) throws @c std::invalid_argument.
     */
    template<class It>
    void seed(It& first, It last)
    {
        detail::fill_array_int<w>(first, last, x);
        i = long_lag;
    }

    /** Returns the next value of the generator. */
    result_type operator()()
    {
        if(i >= long_lag)
            fill();
        return x[i++];
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
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, lagged_fibonacci_engine, f)
    {
        os << f.i;
        for(unsigned int j = 0; j < f.long_lag; ++j)
            os << ' ' << f.x[j];
        return os;
    }

    /**
     * Reads the textual representation of the generator from a @c std::istream.
     */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, lagged_fibonacci_engine, f)
    {
        is >> f.i >> std::ws;
        for(unsigned int j = 0; j < f.long_lag; ++j)
            is >> f.x[j] >> std::ws;
        return is;
    }

    /**
     * Returns true if the two generators will produce identical
     * sequences of outputs.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(lagged_fibonacci_engine, x_, y_)
    { return x_.i == y_.i && std::equal(x_.x, x_.x+long_lag, y_.x); }

    /**
     * Returns true if the two generators will produce different
     * sequences of outputs.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(lagged_fibonacci_engine)

private:
    /// \cond show_private
    void fill();
    /// \endcond

    unsigned int i;
    UIntType x[long_lag];
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class UIntType, int w, unsigned int p, unsigned int q>
const bool lagged_fibonacci_engine<UIntType, w, p, q>::has_fixed_range;
template<class UIntType, int w, unsigned int p, unsigned int q>
const unsigned int lagged_fibonacci_engine<UIntType, w, p, q>::long_lag;
template<class UIntType, int w, unsigned int p, unsigned int q>
const unsigned int lagged_fibonacci_engine<UIntType, w, p, q>::short_lag;
template<class UIntType, int w, unsigned int p, unsigned int q>
const UIntType lagged_fibonacci_engine<UIntType, w, p, q>::default_seed;
#endif

/// \cond show_private

template<class UIntType, int w, unsigned int p, unsigned int q>
void lagged_fibonacci_engine<UIntType, w, p, q>::fill()
{
    // two loops to avoid costly modulo operations
    {  // extra scope for MSVC brokenness w.r.t. for scope
    for(unsigned int j = 0; j < short_lag; ++j)
        x[j] = (x[j] + x[j+(long_lag-short_lag)]) & low_bits_mask_t<w>::sig_bits;
    }
    for(unsigned int j = short_lag; j < long_lag; ++j)
        x[j] = (x[j] + x[j-short_lag]) & low_bits_mask_t<w>::sig_bits;
    i = 0;
}

/// \endcond

/// \cond show_deprecated

// provided for backwards compatibility
template<class UIntType, int w, unsigned int p, unsigned int q, UIntType v = 0>
class lagged_fibonacci : public lagged_fibonacci_engine<UIntType, w, p, q>
{
    typedef lagged_fibonacci_engine<UIntType, w, p, q> base_type;
public:
    lagged_fibonacci() {}
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(lagged_fibonacci, UIntType, val)
    { this->seed(val); }
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(lagged_fibonacci, SeedSeq, seq)
    { this->seed(seq); }
    template<class It>
    lagged_fibonacci(It& first, It last) : base_type(first, last) {}
};

/// \endcond

// lagged Fibonacci generator for the range [0..1)
// contributed by Matthias Troyer
// for p=55, q=24 originally by G. J. Mitchell and D. P. Moore 1958

/**
 * Instantiations of class template @c lagged_fibonacci_01 model a
 * \pseudo_random_number_generator. It uses a lagged Fibonacci
 * algorithm with two lags @c p and @c q, evaluated in floating-point
 * arithmetic: x(i) = x(i-p) + x(i-q) (mod 1) with p > q. See
 *
 *  @blockquote
 *  "Uniform random number generators for supercomputers", Richard Brent,
 *  Proc. of Fifth Australian Supercomputer Conference, Melbourne,
 *  Dec. 1992, pp. 704-706.
 *  @endblockquote
 *
 * @xmlnote
 * The quality of the generator crucially depends on the choice
 * of the parameters. User code should employ one of the sensibly
 * parameterized generators such as \lagged_fibonacci607 instead.
 * @endxmlnote
 *
 * The generator requires considerable amounts of memory for the storage
 * of its state array. For example, \lagged_fibonacci607 requires about
 * 4856 bytes and \lagged_fibonacci44497 requires about 350 KBytes.
 */
template<class RealType, int w, unsigned int p, unsigned int q>
class lagged_fibonacci_01_engine
{
public:
    typedef RealType result_type;
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);
    BOOST_STATIC_CONSTANT(int, word_size = w);
    BOOST_STATIC_CONSTANT(unsigned int, long_lag = p);
    BOOST_STATIC_CONSTANT(unsigned int, short_lag = q);

    BOOST_STATIC_CONSTANT(boost::uint32_t, default_seed = 331u);

    /** Constructs a @c lagged_fibonacci_01 generator and calls @c seed(). */
    lagged_fibonacci_01_engine() { seed(); }
    /** Constructs a @c lagged_fibonacci_01 generator and calls @c seed(value). */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(lagged_fibonacci_01_engine, uint32_t, value)
    { seed(value); }
    /** Constructs a @c lagged_fibonacci_01 generator and calls @c seed(gen). */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(lagged_fibonacci_01_engine, SeedSeq, seq)
    { seed(seq); }
    template<class It> lagged_fibonacci_01_engine(It& first, It last)
    { seed(first, last); }

    // compiler-generated copy ctor and assignment operator are fine

    /** Calls seed(default_seed). */
    void seed() { seed(default_seed); }

    /**
     * Constructs a \minstd_rand0 generator with the constructor parameter
     * value and calls seed with it. Distinct seeds in the range
     * [1, 2147483647) will produce generators with different states. Other
     * seeds will be equivalent to some seed within this range. See
     * \linear_congruential_engine for details.
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(lagged_fibonacci_01_engine, boost::uint32_t, value)
    {
        minstd_rand0 intgen(value);
        detail::generator_seed_seq<minstd_rand0> gen(intgen);
        seed(gen);
    }

    /**
     * Seeds this @c lagged_fibonacci_01_engine using values produced by
     * @c seq.generate.
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(lagged_fibonacci_01_engine, SeedSeq, seq)
    {
        detail::seed_array_real<w>(seq, x);
        i = long_lag;
    }

    /**
     * Seeds this @c lagged_fibonacci_01_engine using values from the
     * iterator range [first, last).  If there are not enough elements
     * in the range, throws @c std::invalid_argument.
     */
    template<class It>
    void seed(It& first, It last)
    {
        detail::fill_array_real<w>(first, last, x);
        i = long_lag;
    }

    /** Returns the smallest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () { return result_type(0); }
    /** Returns the upper bound of the generators outputs. */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () { return result_type(1); }

    /** Returns the next value of the generator. */
    result_type operator()()
    {
        if(i >= long_lag)
            fill();
        return x[i++];
    }

    /** Fills a range with random values */
    template<class Iter>
    void generate(Iter first, Iter last)
    { return detail::generate_from_real(*this, first, last); }

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
    BOOST_RANDOM_DETAIL_OSTREAM_OPERATOR(os, lagged_fibonacci_01_engine, f)
    {
        // allow for Koenig lookup
        using std::pow;
        os << f.i;
        std::ios_base::fmtflags oldflags = os.flags(os.dec | os.fixed | os.left);
        for(unsigned int j = 0; j < f.long_lag; ++j)
            os << ' ' << f.x[j] * f.modulus();
        os.flags(oldflags);
        return os;
    }

    /**
     * Reads the textual representation of the generator from a @c std::istream.
     */
    BOOST_RANDOM_DETAIL_ISTREAM_OPERATOR(is, lagged_fibonacci_01_engine, f)
    {
        is >> f.i;
        for(unsigned int j = 0; j < f.long_lag; ++j) {
            typename lagged_fibonacci_01_engine::result_type value;
            is >> std::ws >> value;
            f.x[j] = value / f.modulus();
        }
        return is;
    }

    /**
     * Returns true if the two generators will produce identical
     * sequences of outputs.
     */
    BOOST_RANDOM_DETAIL_EQUALITY_OPERATOR(lagged_fibonacci_01_engine, x_, y_)
    { return x_.i == y_.i && std::equal(x_.x, x_.x+long_lag, y_.x); }

    /**
     * Returns true if the two generators will produce different
     * sequences of outputs.
     */
    BOOST_RANDOM_DETAIL_INEQUALITY_OPERATOR(lagged_fibonacci_01_engine)

private:
    /// \cond show_private
    void fill();
    static RealType modulus()
    {
        using std::pow;
        return pow(RealType(2), word_size);
    }
    /// \endcond
    unsigned int i;
    RealType x[long_lag];
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
template<class RealType, int w, unsigned int p, unsigned int q>
const bool lagged_fibonacci_01_engine<RealType, w, p, q>::has_fixed_range;
template<class RealType, int w, unsigned int p, unsigned int q>
const unsigned int lagged_fibonacci_01_engine<RealType, w, p, q>::long_lag;
template<class RealType, int w, unsigned int p, unsigned int q>
const unsigned int lagged_fibonacci_01_engine<RealType, w, p, q>::short_lag;
template<class RealType, int w, unsigned int p, unsigned int q>
const int lagged_fibonacci_01_engine<RealType,w,p,q>::word_size;
template<class RealType, int w, unsigned int p, unsigned int q>
const boost::uint32_t lagged_fibonacci_01_engine<RealType,w,p,q>::default_seed;
#endif

/// \cond show_private
template<class RealType, int w, unsigned int p, unsigned int q>
void lagged_fibonacci_01_engine<RealType, w, p, q>::fill()
{
    // two loops to avoid costly modulo operations
    {  // extra scope for MSVC brokenness w.r.t. for scope
    for(unsigned int j = 0; j < short_lag; ++j) {
        RealType t = x[j] + x[j+(long_lag-short_lag)];
        if(t >= RealType(1))
            t -= RealType(1);
        x[j] = t;
    }
    }
    for(unsigned int j = short_lag; j < long_lag; ++j) {
        RealType t = x[j] + x[j-short_lag];
        if(t >= RealType(1))
            t -= RealType(1);
        x[j] = t;
    }
    i = 0;
}
/// \endcond

/// \cond show_deprecated

// provided for backwards compatibility
template<class RealType, int w, unsigned int p, unsigned int q>
class lagged_fibonacci_01 : public lagged_fibonacci_01_engine<RealType, w, p, q>
{
    typedef lagged_fibonacci_01_engine<RealType, w, p, q> base_type;
public:
    lagged_fibonacci_01() {}
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(lagged_fibonacci_01, boost::uint32_t, val)
    { this->seed(val); }
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(lagged_fibonacci_01, SeedSeq, seq)
    { this->seed(seq); }
    template<class It>
    lagged_fibonacci_01(It& first, It last) : base_type(first, last) {}
};

/// \endcond

namespace detail {

template<class Engine>
struct generator_bits;

template<class RealType, int w, unsigned int p, unsigned int q>
struct generator_bits<lagged_fibonacci_01_engine<RealType, w, p, q> >
{
    static std::size_t value() { return w; }
};

template<class RealType, int w, unsigned int p, unsigned int q>
struct generator_bits<lagged_fibonacci_01<RealType, w, p, q> >
{
    static std::size_t value() { return w; }
};

}

#ifdef BOOST_RANDOM_DOXYGEN
namespace detail {
/**
 * The specializations lagged_fibonacci607 ... lagged_fibonacci44497
 * use well tested lags.
 *
 * See
 *
 *  @blockquote
 *  "On the Periods of Generalized Fibonacci Recurrences", Richard P. Brent
 *  Computer Sciences Laboratory Australian National University, December 1992
 *  @endblockquote
 *
 * The lags used here can be found in
 *
 *  @blockquote
 *  "Uniform random number generators for supercomputers", Richard Brent,
 *  Proc. of Fifth Australian Supercomputer Conference, Melbourne,
 *  Dec. 1992, pp. 704-706.
 *  @endblockquote
 */
struct lagged_fibonacci_doc {};
}
#endif

/** @copydoc boost::random::detail::lagged_fibonacci_doc */
typedef lagged_fibonacci_01_engine<double, 48, 607, 273> lagged_fibonacci607;
/** @copydoc boost::random::detail::lagged_fibonacci_doc */
typedef lagged_fibonacci_01_engine<double, 48, 1279, 418> lagged_fibonacci1279;
/** @copydoc boost::random::detail::lagged_fibonacci_doc */
typedef lagged_fibonacci_01_engine<double, 48, 2281, 1252> lagged_fibonacci2281;
/** @copydoc boost::random::detail::lagged_fibonacci_doc */
typedef lagged_fibonacci_01_engine<double, 48, 3217, 576> lagged_fibonacci3217;
/** @copydoc boost::random::detail::lagged_fibonacci_doc */
typedef lagged_fibonacci_01_engine<double, 48, 4423, 2098> lagged_fibonacci4423;
/** @copydoc boost::random::detail::lagged_fibonacci_doc */
typedef lagged_fibonacci_01_engine<double, 48, 9689, 5502> lagged_fibonacci9689;
/** @copydoc boost::random::detail::lagged_fibonacci_doc */
typedef lagged_fibonacci_01_engine<double, 48, 19937, 9842> lagged_fibonacci19937;
/** @copydoc boost::random::detail::lagged_fibonacci_doc */
typedef lagged_fibonacci_01_engine<double, 48, 23209, 13470> lagged_fibonacci23209;
/** @copydoc boost::random::detail::lagged_fibonacci_doc */
typedef lagged_fibonacci_01_engine<double, 48, 44497, 21034> lagged_fibonacci44497;

} // namespace random

using random::lagged_fibonacci607;
using random::lagged_fibonacci1279;
using random::lagged_fibonacci2281;
using random::lagged_fibonacci3217;
using random::lagged_fibonacci4423;
using random::lagged_fibonacci9689;
using random::lagged_fibonacci19937;
using random::lagged_fibonacci23209;
using random::lagged_fibonacci44497;

} // namespace boost

#endif // BOOST_RANDOM_LAGGED_FIBONACCI_HPP

/* lagged_fibonacci.hpp
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
*/