/* boost random/mersenne_twister.hpp header file
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
 * Revision history
 *  2013-10-14  fixed some warnings with Wshadow (mgaunard)
 *  2001-02-18  moved to individual header files
 */

#ifndef BOOST_RANDOM_MERSENNE_TWISTER_HPP
#define BOOST_RANDOM_MERSENNE_TWISTER_HPP

#include <iosfwd>
#include <istream>
#include <stdexcept>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer/integer_mask.hpp>
#include <boost/random/detail/config.hpp>
#include <boost/random/detail/ptr_helper.hpp>
#include <boost/random/detail/seed.hpp>
#include <boost/random/detail/seed_impl.hpp>
#include <boost/random/detail/generator_seed_seq.hpp>
#include <boost/random/detail/polynomial.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {

/**
 * Instantiations of class template mersenne_twister_engine model a
 * \pseudo_random_number_generator. It uses the algorithm described in
 *
 *  @blockquote
 *  "Mersenne Twister: A 623-dimensionally equidistributed uniform
 *  pseudo-random number generator", Makoto Matsumoto and Takuji Nishimura,
 *  ACM Transactions on Modeling and Computer Simulation: Special Issue on
 *  Uniform Random Number Generation, Vol. 8, No. 1, January 1998, pp. 3-30.
 *  @endblockquote
 *
 * @xmlnote
 * The boost variant has been implemented from scratch and does not
 * derive from or use mt19937.c provided on the above WWW site. However, it
 * was verified that both produce identical output.
 * @endxmlnote
 *
 * The seeding from an integer was changed in April 2005 to address a
 * <a href="http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html">weakness</a>.
 *
 * The quality of the generator crucially depends on the choice of the
 * parameters.  User code should employ one of the sensibly parameterized
 * generators such as \mt19937 instead.
 *
 * The generator requires considerable amounts of memory for the storage of
 * its state array. For example, \mt11213b requires about 1408 bytes and
 * \mt19937 requires about 2496 bytes.
 */
template<class UIntType,
         std::size_t w, std::size_t n, std::size_t m, std::size_t r,
         UIntType a, std::size_t u, UIntType d, std::size_t s,
         UIntType b, std::size_t t,
         UIntType c, std::size_t l, UIntType f>
class mersenne_twister_engine
{
public:
    typedef UIntType result_type;
    BOOST_STATIC_CONSTANT(std::size_t, word_size = w);
    BOOST_STATIC_CONSTANT(std::size_t, state_size = n);
    BOOST_STATIC_CONSTANT(std::size_t, shift_size = m);
    BOOST_STATIC_CONSTANT(std::size_t, mask_bits = r);
    BOOST_STATIC_CONSTANT(UIntType, xor_mask = a);
    BOOST_STATIC_CONSTANT(std::size_t, tempering_u = u);
    BOOST_STATIC_CONSTANT(UIntType, tempering_d = d);
    BOOST_STATIC_CONSTANT(std::size_t, tempering_s = s);
    BOOST_STATIC_CONSTANT(UIntType, tempering_b = b);
    BOOST_STATIC_CONSTANT(std::size_t, tempering_t = t);
    BOOST_STATIC_CONSTANT(UIntType, tempering_c = c);
    BOOST_STATIC_CONSTANT(std::size_t, tempering_l = l);
    BOOST_STATIC_CONSTANT(UIntType, initialization_multiplier = f);
    BOOST_STATIC_CONSTANT(UIntType, default_seed = 5489u);

    // backwards compatibility
    BOOST_STATIC_CONSTANT(UIntType, parameter_a = a);
    BOOST_STATIC_CONSTANT(std::size_t, output_u = u);
    BOOST_STATIC_CONSTANT(std::size_t, output_s = s);
    BOOST_STATIC_CONSTANT(UIntType, output_b = b);
    BOOST_STATIC_CONSTANT(std::size_t, output_t = t);
    BOOST_STATIC_CONSTANT(UIntType, output_c = c);
    BOOST_STATIC_CONSTANT(std::size_t, output_l = l);

    // old Boost.Random concept requirements
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);


    /**
     * Constructs a @c mersenne_twister_engine and calls @c seed().
     */
    mersenne_twister_engine() { seed(); }

    /**
     * Constructs a @c mersenne_twister_engine and calls @c seed(value).
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(mersenne_twister_engine,
                                               UIntType, value)
    { seed(value); }
    template<class It> mersenne_twister_engine(It& first, It last)
    { seed(first,last); }

    /**
     * Constructs a mersenne_twister_engine and calls @c seed(gen).
     *
     * @xmlnote
     * The copy constructor will always be preferred over
     * the templated constructor.
     * @endxmlnote
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(mersenne_twister_engine,
                                             SeedSeq, seq)
    { seed(seq); }

    // compiler-generated copy ctor and assignment operator are fine

    /** Calls @c seed(default_seed). */
    void seed() { seed(default_seed); }

    /**
     * Sets the state x(0) to v mod 2w. Then, iteratively,
     * sets x(i) to
     * (i + f * (x(i-1) xor (x(i-1) rshift w-2))) mod 2<sup>w</sup>
     * for i = 1 .. n-1. x(n) is the first value to be returned by operator().
     */
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(mersenne_twister_engine, UIntType, value)
    {
        // New seeding algorithm from
        // http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html
        // In the previous versions, MSBs of the seed affected only MSBs of the
        // state x[].
        const UIntType mask = (max)();
        x[0] = value & mask;
        for (i = 1; i < n; i++) {
            // See Knuth "The Art of Computer Programming"
            // Vol. 2, 3rd ed., page 106
            x[i] = (f * (x[i-1] ^ (x[i-1] >> (w-2))) + i) & mask;
        }

        normalize_state();
    }

    /**
     * Seeds a mersenne_twister_engine using values produced by seq.generate().
     */
    BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(mersenne_twister_engine, SeeqSeq, seq)
    {
        detail::seed_array_int<w>(seq, x);
        i = n;

        normalize_state();
    }

    /** Sets the state of the generator using values from an iterator range. */
    template<class It>
    void seed(It& first, It last)
    {
        detail::fill_array_int<w>(first, last, x);
        i = n;

        normalize_state();
    }

    /** Returns the smallest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return 0; }
    /** Returns the largest value that the generator can produce. */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION ()
    { return boost::low_bits_mask_t<w>::sig_bits; }

    /** Produces the next value of the generator. */
    result_type operator()();

    /** Fills a range with random values */
    template<class Iter>
    void generate(Iter first, Iter last)
    { detail::generate_from_int(*this, first, last); }

    /**
     * Advances the state of the generator by @c z steps.  Equivalent to
     *
     * @code
     * for(unsigned long long i = 0; i < z; ++i) {
     *     gen();
     * }
     * @endcode
     */
    void discard(boost::uintmax_t z)
    {
#ifndef BOOST_RANDOM_MERSENNE_TWISTER_DISCARD_THRESHOLD
#define BOOST_RANDOM_MERSENNE_TWISTER_DISCARD_THRESHOLD 10000000
#endif
        if(z > BOOST_RANDOM_MERSENNE_TWISTER_DISCARD_THRESHOLD) {
            discard_many(z);
        } else {
            for(boost::uintmax_t j = 0; j < z; ++j) {
                (*this)();
            }
        }
    }

#ifndef BOOST_RANDOM_NO_STREAM_OPERATORS
    /** Writes a mersenne_twister_engine to a @c std::ostream */
    template<class CharT, class Traits>
    friend std::basic_ostream<CharT,Traits>&
    operator<<(std::basic_ostream<CharT,Traits>& os,
               const mersenne_twister_engine& mt)
    {
        mt.print(os);
        return os;
    }

    /** Reads a mersenne_twister_engine from a @c std::istream */
    template<class CharT, class Traits>
    friend std::basic_istream<CharT,Traits>&
    operator>>(std::basic_istream<CharT,Traits>& is,
               mersenne_twister_engine& mt)
    {
        for(std::size_t j = 0; j < mt.state_size; ++j)
            is >> mt.x[j] >> std::ws;
        // MSVC (up to 7.1) and Borland (up to 5.64) don't handle the template
        // value parameter "n" available from the class template scope, so use
        // the static constant with the same value
        mt.i = mt.state_size;
        return is;
    }
#endif

    /**
     * Returns true if the two generators are in the same state,
     * and will thus produce identical sequences.
     */
    friend bool operator==(const mersenne_twister_engine& x_,
                           const mersenne_twister_engine& y_)
    {
        if(x_.i < y_.i) return x_.equal_imp(y_);
        else return y_.equal_imp(x_);
    }

    /**
     * Returns true if the two generators are in different states.
     */
    friend bool operator!=(const mersenne_twister_engine& x_,
                           const mersenne_twister_engine& y_)
    { return !(x_ == y_); }

private:
    /// \cond show_private

    void twist();

    /**
     * Does the work of operator==.  This is in a member function
     * for portability.  Some compilers, such as msvc 7.1 and
     * Sun CC 5.10 can't access template parameters or static
     * members of the class from inline friend functions.
     *
     * requires i <= other.i
     */
    bool equal_imp(const mersenne_twister_engine& other) const
    {
        UIntType back[n];
        std::size_t offset = other.i - i;
        for(std::size_t j = 0; j + offset < n; ++j)
            if(x[j] != other.x[j+offset])
                return false;
        rewind(&back[n-1], offset);
        for(std::size_t j = 0; j < offset; ++j)
            if(back[j + n - offset] != other.x[j])
                return false;
        return true;
    }

    /**
     * Does the work of operator<<.  This is in a member function
     * for portability.
     */
    template<class CharT, class Traits>
    void print(std::basic_ostream<CharT, Traits>& os) const
    {
        UIntType data[n];
        for(std::size_t j = 0; j < i; ++j) {
            data[j + n - i] = x[j];
        }
        if(i != n) {
            rewind(&data[n - i - 1], n - i);
        }
        os << data[0];
        for(std::size_t j = 1; j < n; ++j) {
            os << ' ' << data[j];
        }
    }

    /**
     * Copies z elements of the state preceding x[0] into
     * the array whose last element is last.
     */
    void rewind(UIntType* last, std::size_t z) const
    {
        const UIntType upper_mask = (~static_cast<UIntType>(0)) << r;
        const UIntType lower_mask = ~upper_mask;
        UIntType y0 = x[m-1] ^ x[n-1];
        if(y0 & (static_cast<UIntType>(1) << (w-1))) {
            y0 = ((y0 ^ a) << 1) | 1;
        } else {
            y0 = y0 << 1;
        }
        for(std::size_t sz = 0; sz < z; ++sz) {
            UIntType y1 =
                rewind_find(last, sz, m-1) ^ rewind_find(last, sz, n-1);
            if(y1 & (static_cast<UIntType>(1) << (w-1))) {
                y1 = ((y1 ^ a) << 1) | 1;
            } else {
                y1 = y1 << 1;
            }
            *(last - sz) = (y0 & upper_mask) | (y1 & lower_mask);
            y0 = y1;
        }
    }

    /**
     * Converts an arbitrary array into a valid generator state.
     * First we normalize x[0], so that it contains the same
     * value we would get by running the generator forwards
     * and then in reverse.  (The low order r bits are redundant).
     * Then, if the state consists of all zeros, we set the
     * high order bit of x[0] to 1.  This function only needs to
     * be called by seed, since the state transform preserves
     * this relationship.
     */
    void normalize_state()
    {
        const UIntType upper_mask = (~static_cast<UIntType>(0)) << r;
        const UIntType lower_mask = ~upper_mask;
        UIntType y0 = x[m-1] ^ x[n-1];
        if(y0 & (static_cast<UIntType>(1) << (w-1))) {
            y0 = ((y0 ^ a) << 1) | 1;
        } else {
            y0 = y0 << 1;
        }
        x[0] = (x[0] & upper_mask) | (y0 & lower_mask);

        // fix up the state if it's all zeroes.
        for(std::size_t j = 0; j < n; ++j) {
            if(x[j] != 0) return;
        }
        x[0] = static_cast<UIntType>(1) << (w-1);
    }

    /**
     * Given a pointer to the last element of the rewind array,
     * and the current size of the rewind array, finds an element
     * relative to the next available slot in the rewind array.
     */
    UIntType
    rewind_find(UIntType* last, std::size_t size, std::size_t j) const
    {
        std::size_t index = (j + n - size + n - 1) % n;
        if(index < n - size) {
            return x[index];
        } else {
            return *(last - (n - 1 - index));
        }
    }

    /**
     * Optimized algorithm for large jumps.
     *
     * Hiroshi Haramoto, Makoto Matsumoto, and Pierre L'Ecuyer. 2008.
     * A Fast Jump Ahead Algorithm for Linear Recurrences in a Polynomial
     * Space. In Proceedings of the 5th international conference on
     * Sequences and Their Applications (SETA '08).
     * DOI=10.1007/978-3-540-85912-3_26
     */
    void discard_many(boost::uintmax_t z)
    {
        // Compute the minimal polynomial, phi(t)
        // This depends only on the transition function,
        // which is constant.  The characteristic
        // polynomial is the same as the minimal
        // polynomial for a maximum period generator
        // (which should be all specializations of
        // mersenne_twister.)  Even if it weren't,
        // the characteristic polynomial is guaranteed
        // to be a multiple of the minimal polynomial,
        // which is good enough.
        detail::polynomial phi = get_characteristic_polynomial();

        // calculate g(t) = t^z % phi(t)
        detail::polynomial g = mod_pow_x(z, phi);

        // h(s_0, t) = \sum_{i=0}^{2k-1}o(s_i)t^{2k-i-1}
        detail::polynomial h;
        const std::size_t num_bits = w*n - r;
        for(std::size_t j = 0; j < num_bits * 2; ++j) {
            // Yes, we're advancing the generator state
            // here, but it doesn't matter because
            // we're going to overwrite it completely
            // in reconstruct_state.
            if(i >= n) twist();
            h[2*num_bits - j - 1] = x[i++] & UIntType(1);
        }
        // g(t)h(s_0, t)
        detail::polynomial gh = g * h;
        detail::polynomial result;
        for(std::size_t j = 0; j <= num_bits; ++j) {
            result[j] = gh[2*num_bits - j - 1];
        }
        reconstruct_state(result);
    }
    static detail::polynomial get_characteristic_polynomial()
    {
        const std::size_t num_bits = w*n - r;
        detail::polynomial helper;
        helper[num_bits - 1] = 1;
        mersenne_twister_engine tmp;
        tmp.reconstruct_state(helper);
        // Skip the first num_bits elements, since we
        // already know what they are.
        for(std::size_t j = 0; j < num_bits; ++j) {
            if(tmp.i >= n) tmp.twist();
            if(j == num_bits - 1)
                assert((tmp.x[tmp.i] & 1) == 1);
            else
                assert((tmp.x[tmp.i] & 1) == 0);
            ++tmp.i;
        }
        detail::polynomial phi;
        phi[num_bits] = 1;
        detail::polynomial next_bits = tmp.as_polynomial(num_bits);
        for(std::size_t j = 0; j < num_bits; ++j) {
            int val = next_bits[j] ^ phi[num_bits-j-1];
            phi[num_bits-j-1] = val;
            if(val) {
                for(std::size_t k = j + 1; k < num_bits; ++k) {
                    phi[num_bits-k-1] ^= next_bits[k-j-1];
                }
            }
        }
        return phi;
    }
    detail::polynomial as_polynomial(std::size_t size) {
        detail::polynomial result;
        for(std::size_t j = 0; j < size; ++j) {
            if(i >= n) twist();
            result[j] = x[i++] & UIntType(1);
        }
        return result;
    }
    void reconstruct_state(const detail::polynomial& p)
    {
        const UIntType upper_mask = (~static_cast<UIntType>(0)) << r;
        const UIntType lower_mask = ~upper_mask;
        const std::size_t num_bits = w*n - r;
        for(std::size_t j = num_bits - n + 1; j <= num_bits; ++j)
            x[j % n] = p[j];

        UIntType y0 = 0;
        for(std::size_t j = num_bits + 1; j >= n - 1; --j) {
            UIntType y1 = x[j % n] ^ x[(j + m) % n];
            if(p[j - n + 1])
                y1 = (y1 ^ a) << UIntType(1) | UIntType(1);
            else
                y1 = y1 << UIntType(1);
            x[(j + 1) % n] = (y0 & upper_mask) | (y1 & lower_mask);
            y0 = y1;
        }
        i = 0;
    }

    /// \endcond

    // state representation: next output is o(x(i))
    //   x[0]  ... x[k] x[k+1] ... x[n-1]   represents
    //  x(i-k) ... x(i) x(i+1) ... x(i-k+n-1)

    UIntType x[n];
    std::size_t i;
};

/// \cond show_private

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION
//  A definition is required even for integral static constants
#define BOOST_RANDOM_MT_DEFINE_CONSTANT(type, name)                         \
template<class UIntType, std::size_t w, std::size_t n, std::size_t m,       \
    std::size_t r, UIntType a, std::size_t u, UIntType d, std::size_t s,    \
    UIntType b, std::size_t t, UIntType c, std::size_t l, UIntType f>       \
const type mersenne_twister_engine<UIntType,w,n,m,r,a,u,d,s,b,t,c,l,f>::name
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, word_size);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, state_size);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, shift_size);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, mask_bits);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, xor_mask);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, tempering_u);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, tempering_d);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, tempering_s);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, tempering_b);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, tempering_t);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, tempering_c);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, tempering_l);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, initialization_multiplier);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, default_seed);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, parameter_a);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, output_u );
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, output_s);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, output_b);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, output_t);
BOOST_RANDOM_MT_DEFINE_CONSTANT(UIntType, output_c);
BOOST_RANDOM_MT_DEFINE_CONSTANT(std::size_t, output_l);
BOOST_RANDOM_MT_DEFINE_CONSTANT(bool, has_fixed_range);
#undef BOOST_RANDOM_MT_DEFINE_CONSTANT
#endif

template<class UIntType,
         std::size_t w, std::size_t n, std::size_t m, std::size_t r,
         UIntType a, std::size_t u, UIntType d, std::size_t s,
         UIntType b, std::size_t t,
         UIntType c, std::size_t l, UIntType f>
void
mersenne_twister_engine<UIntType,w,n,m,r,a,u,d,s,b,t,c,l,f>::twist()
{
    const UIntType upper_mask = (~static_cast<UIntType>(0)) << r;
    const UIntType lower_mask = ~upper_mask;

    const std::size_t unroll_factor = 6;
    const std::size_t unroll_extra1 = (n-m) % unroll_factor;
    const std::size_t unroll_extra2 = (m-1) % unroll_factor;

    // split loop to avoid costly modulo operations
    {  // extra scope for MSVC brokenness w.r.t. for scope
        for(std::size_t j = 0; j < n-m-unroll_extra1; j++) {
            UIntType y = (x[j] & upper_mask) | (x[j+1] & lower_mask);
            x[j] = x[j+m] ^ (y >> 1) ^ ((x[j+1]&1) * a);
        }
    }
    {
        for(std::size_t j = n-m-unroll_extra1; j < n-m; j++) {
            UIntType y = (x[j] & upper_mask) | (x[j+1] & lower_mask);
            x[j] = x[j+m] ^ (y >> 1) ^ ((x[j+1]&1) * a);
        }
    }
    {
        for(std::size_t j = n-m; j < n-1-unroll_extra2; j++) {
            UIntType y = (x[j] & upper_mask) | (x[j+1] & lower_mask);
            x[j] = x[j-(n-m)] ^ (y >> 1) ^ ((x[j+1]&1) * a);
        }
    }
    {
        for(std::size_t j = n-1-unroll_extra2; j < n-1; j++) {
            UIntType y = (x[j] & upper_mask) | (x[j+1] & lower_mask);
            x[j] = x[j-(n-m)] ^ (y >> 1) ^ ((x[j+1]&1) * a);
        }
    }
    // last iteration
    UIntType y = (x[n-1] & upper_mask) | (x[0] & lower_mask);
    x[n-1] = x[m-1] ^ (y >> 1) ^ ((x[0]&1) * a);
    i = 0;
}
/// \endcond

template<class UIntType,
         std::size_t w, std::size_t n, std::size_t m, std::size_t r,
         UIntType a, std::size_t u, UIntType d, std::size_t s,
         UIntType b, std::size_t t,
         UIntType c, std::size_t l, UIntType f>
inline typename
mersenne_twister_engine<UIntType,w,n,m,r,a,u,d,s,b,t,c,l,f>::result_type
mersenne_twister_engine<UIntType,w,n,m,r,a,u,d,s,b,t,c,l,f>::operator()()
{
    if(i == n)
        twist();
    // Step 4
    UIntType z = x[i];
    ++i;
    z ^= ((z >> u) & d);
    z ^= ((z << s) & b);
    z ^= ((z << t) & c);
    z ^= (z >> l);
    return z;
}

/**
 * The specializations \mt11213b and \mt19937 are from
 *
 *  @blockquote
 *  "Mersenne Twister: A 623-dimensionally equidistributed
 *  uniform pseudo-random number generator", Makoto Matsumoto
 *  and Takuji Nishimura, ACM Transactions on Modeling and
 *  Computer Simulation: Special Issue on Uniform Random Number
 *  Generation, Vol. 8, No. 1, January 1998, pp. 3-30.
 *  @endblockquote
 */
typedef mersenne_twister_engine<uint32_t,32,351,175,19,0xccab8ee7,
    11,0xffffffff,7,0x31b6ab00,15,0xffe50000,17,1812433253> mt11213b;

/**
 * The specializations \mt11213b and \mt19937 are from
 *
 *  @blockquote
 *  "Mersenne Twister: A 623-dimensionally equidistributed
 *  uniform pseudo-random number generator", Makoto Matsumoto
 *  and Takuji Nishimura, ACM Transactions on Modeling and
 *  Computer Simulation: Special Issue on Uniform Random Number
 *  Generation, Vol. 8, No. 1, January 1998, pp. 3-30.
 *  @endblockquote
 */
typedef mersenne_twister_engine<uint32_t,32,624,397,31,0x9908b0df,
    11,0xffffffff,7,0x9d2c5680,15,0xefc60000,18,1812433253> mt19937;

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
typedef mersenne_twister_engine<uint64_t,64,312,156,31,
    UINT64_C(0xb5026f5aa96619e9),29,UINT64_C(0x5555555555555555),17,
    UINT64_C(0x71d67fffeda60000),37,UINT64_C(0xfff7eee000000000),43,
    UINT64_C(6364136223846793005)> mt19937_64;
#endif

/// \cond show_deprecated

template<class UIntType,
         int w, int n, int m, int r,
         UIntType a, int u, std::size_t s,
         UIntType b, int t,
         UIntType c, int l, UIntType v>
class mersenne_twister :
    public mersenne_twister_engine<UIntType,
        w, n, m, r, a, u, ~(UIntType)0, s, b, t, c, l, 1812433253>
{
    typedef mersenne_twister_engine<UIntType,
        w, n, m, r, a, u, ~(UIntType)0, s, b, t, c, l, 1812433253> base_type;
public:
    mersenne_twister() {}
    BOOST_RANDOM_DETAIL_GENERATOR_CONSTRUCTOR(mersenne_twister, Gen, gen)
    { seed(gen); }
    BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(mersenne_twister, UIntType, val)
    { seed(val); }
    template<class It>
    mersenne_twister(It& first, It last) : base_type(first, last) {}
    void seed() { base_type::seed(); }
    BOOST_RANDOM_DETAIL_GENERATOR_SEED(mersenne_twister, Gen, gen)
    {
        detail::generator_seed_seq<Gen> seq(gen);
        base_type::seed(seq);
    }
    BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(mersenne_twister, UIntType, val)
    { base_type::seed(val); }
    template<class It>
    void seed(It& first, It last) { base_type::seed(first, last); }
};

/// \endcond

} // namespace random

using random::mt11213b;
using random::mt19937;
using random::mt19937_64;

} // namespace boost

BOOST_RANDOM_PTR_HELPER_SPEC(boost::mt11213b)
BOOST_RANDOM_PTR_HELPER_SPEC(boost::mt19937)
BOOST_RANDOM_PTR_HELPER_SPEC(boost::mt19937_64)

#include <boost/random/detail/enable_warnings.hpp>

#endif // BOOST_RANDOM_MERSENNE_TWISTER_HPP

/* mersenne_twister.hpp
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
*/