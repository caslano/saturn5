/* boost random/detail/seed.hpp header file
 *
 * Copyright Steven Watanabe 2009
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 */

#ifndef BOOST_RANDOM_DETAIL_SEED_IMPL_HPP
#define BOOST_RANDOM_DETAIL_SEED_IMPL_HPP

#include <stdexcept>
#include <boost/cstdint.hpp>
#include <boost/throw_exception.hpp>
#include <boost/config/no_tr1/cmath.hpp>
#include <boost/integer/integer_mask.hpp>
#include <boost/integer/static_log2.hpp>
#include <boost/random/traits.hpp>
#include <boost/random/detail/const_mod.hpp>
#include <boost/random/detail/integer_log2.hpp>
#include <boost/random/detail/signed_unsigned_tools.hpp>
#include <boost/random/detail/generator_bits.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/integral_constant.hpp>

#include <boost/random/detail/disable_warnings.hpp>

namespace boost {
namespace random {
namespace detail {

// finds the seed type of an engine, given its
// result_type.  If the result_type is integral
// the seed type is the same.  If the result_type
// is floating point, the seed type is uint32_t
template<class T>
struct seed_type
{
    typedef typename boost::conditional<boost::is_integral<T>::value,
        T,
        boost::uint32_t
    >::type type;
};

template<int N>
struct const_pow_impl
{
    template<class T>
    static T call(T arg, int n, T result)
    {
        return const_pow_impl<N / 2>::call(T(arg * arg), n / 2,
            n%2 == 0? result : T(result * arg));
    }
};

template<>
struct const_pow_impl<0>
{
    template<class T>
    static T call(T, int, T result)
    {
        return result;
    }
};

// requires N is an upper bound on n
template<int N, class T>
inline T const_pow(T arg, int n) { return const_pow_impl<N>::call(arg, n, T(1)); }

template<class T>
inline T pow2(int n)
{
    typedef unsigned int_type;
    const int max_bits = std::numeric_limits<int_type>::digits;
    T multiplier = T(int_type(1) << (max_bits - 1)) * 2;
    return (int_type(1) << (n % max_bits)) *
        const_pow<std::numeric_limits<T>::digits / max_bits>(multiplier, n / max_bits);
}

template<class Engine, class Iter>
void generate_from_real(Engine& eng, Iter begin, Iter end)
{
    using std::fmod;
    typedef typename Engine::result_type RealType;
    const int Bits = detail::generator_bits<Engine>::value();
    int remaining_bits = 0;
    boost::uint_least32_t saved_bits = 0;
    RealType multiplier = pow2<RealType>( Bits);
    RealType mult32 = RealType(4294967296.0); // 2^32
    while(true) {
        RealType val = eng() * multiplier;
        int available_bits = Bits;
        // Make sure the compiler can optimize this out
        // if it isn't possible.
        if(Bits < 32 && available_bits < 32 - remaining_bits) {
            saved_bits |= boost::uint_least32_t(val) << remaining_bits;
            remaining_bits += Bits;
        } else {
            // If Bits < 32, then remaining_bits != 0, since
            // if remaining_bits == 0, available_bits < 32 - 0,
            // and we won't get here to begin with.
            if(Bits < 32 || remaining_bits != 0) {
                boost::uint_least32_t divisor =
                    (boost::uint_least32_t(1) << (32 - remaining_bits));
                boost::uint_least32_t extra_bits = boost::uint_least32_t(fmod(val, mult32)) & (divisor - 1);
                val = val / divisor;
                *begin++ = saved_bits | (extra_bits << remaining_bits);
                if(begin == end) return;
                available_bits -= 32 - remaining_bits;
                remaining_bits = 0;
            }
            // If Bits < 32 we should never enter this loop
            if(Bits >= 32) {
                for(; available_bits >= 32; available_bits -= 32) {
                    boost::uint_least32_t word = boost::uint_least32_t(fmod(val, mult32));
                    val /= mult32;
                    *begin++ = word;
                    if(begin == end) return;
                }
            }
            remaining_bits = available_bits;
            saved_bits = static_cast<boost::uint_least32_t>(val);
        }
    }
}

template<class Engine, class Iter>
void generate_from_int(Engine& eng, Iter begin, Iter end)
{
    typedef typename Engine::result_type IntType;
    typedef typename boost::random::traits::make_unsigned<IntType>::type unsigned_type;
    int remaining_bits = 0;
    boost::uint_least32_t saved_bits = 0;
    unsigned_type range = boost::random::detail::subtract<IntType>()((eng.max)(), (eng.min)());

    int bits =
        (range == (std::numeric_limits<unsigned_type>::max)()) ?
            std::numeric_limits<unsigned_type>::digits :
            detail::integer_log2(range + 1);

    {
        int discarded_bits = detail::integer_log2(bits);
        unsigned_type excess = (range + 1) >> (bits - discarded_bits);
        if(excess != 0) {
            int extra_bits = detail::integer_log2((excess - 1) ^ excess);
            bits = bits - discarded_bits + extra_bits;
        }
    }

    unsigned_type mask = (static_cast<unsigned_type>(2) << (bits - 1)) - 1;
    unsigned_type limit = ((range + 1) & ~mask) - 1;

    while(true) {
        unsigned_type val;
        do {
            val = boost::random::detail::subtract<IntType>()(eng(), (eng.min)());
        } while(limit != range && val > limit);
        val &= mask;
        int available_bits = bits;
        if(available_bits == 32) {
            *begin++ = static_cast<boost::uint_least32_t>(val) & 0xFFFFFFFFu;
            if(begin == end) return;
        } else if(available_bits % 32 == 0) {
            for(int i = 0; i < available_bits / 32; ++i) {
                boost::uint_least32_t word = boost::uint_least32_t(val) & 0xFFFFFFFFu;
                int suppress_warning = (bits >= 32);
                BOOST_ASSERT(suppress_warning == 1);
                val >>= (32 * suppress_warning);
                *begin++ = word;
                if(begin == end) return;
            }
        } else if(bits < 32 && available_bits < 32 - remaining_bits) {
            saved_bits |= boost::uint_least32_t(val) << remaining_bits;
            remaining_bits += bits;
        } else {
            if(bits < 32 || remaining_bits != 0) {
                boost::uint_least32_t extra_bits = boost::uint_least32_t(val) & ((boost::uint_least32_t(1) << (32 - remaining_bits)) - 1);
                val >>= 32 - remaining_bits;
                *begin++ = saved_bits | (extra_bits << remaining_bits);
                if(begin == end) return;
                available_bits -= 32 - remaining_bits;
                remaining_bits = 0;
            }
            if(bits >= 32) {
                for(; available_bits >= 32; available_bits -= 32) {
                    boost::uint_least32_t word = boost::uint_least32_t(val) & 0xFFFFFFFFu;
                    int suppress_warning = (bits >= 32);
                    BOOST_ASSERT(suppress_warning == 1);
                    val >>= (32 * suppress_warning);
                    *begin++ = word;
                    if(begin == end) return;
                }
            }
            remaining_bits = available_bits;
            saved_bits = static_cast<boost::uint_least32_t>(val);
        }
    }
}

template<class Engine, class Iter>
void generate_impl(Engine& eng, Iter first, Iter last, boost::true_type)
{
    return detail::generate_from_int(eng, first, last);
}

template<class Engine, class Iter>
void generate_impl(Engine& eng, Iter first, Iter last, boost::false_type)
{
    return detail::generate_from_real(eng, first, last);
}

template<class Engine, class Iter>
void generate(Engine& eng, Iter first, Iter last)
{
    return detail::generate_impl(eng, first, last, boost::random::traits::is_integral<typename Engine::result_type>());
}



template<class IntType, IntType m, class SeedSeq>
IntType seed_one_int(SeedSeq& seq)
{
    static const int log = ::boost::conditional<(m == 0),
        ::boost::integral_constant<int, (::std::numeric_limits<IntType>::digits)>,
        ::boost::static_log2<m> >::type::value;
    static const int k =
        (log + ((~(static_cast<IntType>(2) << (log - 1)) & m)? 32 : 31)) / 32;
    ::boost::uint_least32_t array[log / 32 + 4];
    seq.generate(&array[0], &array[0] + k + 3);
    IntType s = 0;
    for(int j = 0; j < k; ++j) {
        IntType digit = const_mod<IntType, m>::apply(IntType(array[j+3]));
        IntType mult = IntType(1) << 32*j;
        s = const_mod<IntType, m>::mult_add(mult, digit, s);
    }
    return s;
}

template<class IntType, IntType m, class Iter>
IntType get_one_int(Iter& first, Iter last)
{
    static const int log = ::boost::conditional<(m == 0),
        ::boost::integral_constant<int, (::std::numeric_limits<IntType>::digits)>,
        ::boost::static_log2<m> >::type::value;
    static const int k =
        (log + ((~(static_cast<IntType>(2) << (log - 1)) & m)? 32 : 31)) / 32;
    IntType s = 0;
    for(int j = 0; j < k; ++j) {
        if(first == last) {
            boost::throw_exception(::std::invalid_argument("Not enough elements in call to seed."));
        }
        IntType digit = const_mod<IntType, m>::apply(IntType(*first++));
        IntType mult = IntType(1) << 32*j;
        s = const_mod<IntType, m>::mult_add(mult, digit, s);
    }
    return s;
}

// TODO: work in-place whenever possible
template<int w, std::size_t n, class SeedSeq, class UIntType>
void seed_array_int_impl(SeedSeq& seq, UIntType (&x)[n])
{
    boost::uint_least32_t storage[((w+31)/32) * n];
    seq.generate(&storage[0], &storage[0] + ((w+31)/32) * n);
    for(std::size_t j = 0; j < n; j++) {
        UIntType val = 0;
        for(std::size_t k = 0; k < (w+31)/32; ++k) {
            val += static_cast<UIntType>(storage[(w+31)/32*j + k]) << 32*k;
        }
        x[j] = val & ::boost::low_bits_mask_t<w>::sig_bits;
    }
}

template<int w, std::size_t n, class SeedSeq, class IntType>
inline void seed_array_int_impl(SeedSeq& seq, IntType (&x)[n], boost::true_type)
{
    BOOST_STATIC_ASSERT_MSG(boost::is_integral<IntType>::value, "Sorry but this routine has not been ported to non built-in integers as it relies on a reinterpret_cast.");
    typedef typename boost::make_unsigned<IntType>::type unsigned_array[n];
    seed_array_int_impl<w>(seq, reinterpret_cast<unsigned_array&>(x));
}

template<int w, std::size_t n, class SeedSeq, class IntType>
inline void seed_array_int_impl(SeedSeq& seq, IntType (&x)[n], boost::false_type)
{
    seed_array_int_impl<w>(seq, x);
}

template<int w, std::size_t n, class SeedSeq, class IntType>
inline void seed_array_int(SeedSeq& seq, IntType (&x)[n])
{
    seed_array_int_impl<w>(seq, x, boost::random::traits::is_signed<IntType>());
}

template<int w, std::size_t n, class Iter, class UIntType>
void fill_array_int_impl(Iter& first, Iter last, UIntType (&x)[n])
{
    for(std::size_t j = 0; j < n; j++) {
        UIntType val = 0;
        for(std::size_t k = 0; k < (w+31)/32; ++k) {
            if(first == last) {
                boost::throw_exception(std::invalid_argument("Not enough elements in call to seed."));
            }
            val += static_cast<UIntType>(*first++) << 32*k;
        }
        x[j] = val & ::boost::low_bits_mask_t<w>::sig_bits;
    }
}

template<int w, std::size_t n, class Iter, class IntType>
inline void fill_array_int_impl(Iter& first, Iter last, IntType (&x)[n], boost::true_type)
{
    BOOST_STATIC_ASSERT_MSG(boost::is_integral<IntType>::value, "Sorry but this routine has not been ported to non built-in integers as it relies on a reinterpret_cast.");
    typedef typename boost::make_unsigned<IntType>::type unsigned_array[n];
    fill_array_int_impl<w>(first, last, reinterpret_cast<unsigned_array&>(x));
}

template<int w, std::size_t n, class Iter, class IntType>
inline void fill_array_int_impl(Iter& first, Iter last, IntType (&x)[n], boost::false_type)
{
    fill_array_int_impl<w>(first, last, x);
}

template<int w, std::size_t n, class Iter, class IntType>
inline void fill_array_int(Iter& first, Iter last, IntType (&x)[n])
{
    fill_array_int_impl<w>(first, last, x, boost::random::traits::is_signed<IntType>());
}

template<int w, std::size_t n, class RealType>
void seed_array_real_impl(const boost::uint_least32_t* storage, RealType (&x)[n])
{
    boost::uint_least32_t mask = ~((~boost::uint_least32_t(0)) << (w%32));
    RealType two32 = 4294967296.0;
    const RealType divisor = RealType(1)/detail::pow2<RealType>(w);
    unsigned int j;
    for(j = 0; j < n; ++j) {
        RealType val = RealType(0);
        RealType mult = divisor;
        for(int k = 0; k < w/32; ++k) {
            val += *storage++ * mult;
            mult *= two32;
        }
        if(mask != 0) {
            val += (*storage++ & mask) * mult;
        }
        BOOST_ASSERT(val >= 0);
        BOOST_ASSERT(val < 1);
        x[j] = val;
    }
}

template<int w, std::size_t n, class SeedSeq, class RealType>
void seed_array_real(SeedSeq& seq, RealType (&x)[n])
{
    using std::pow;
    boost::uint_least32_t storage[((w+31)/32) * n];
    seq.generate(&storage[0], &storage[0] + ((w+31)/32) * n);
    seed_array_real_impl<w>(storage, x);
}

template<int w, std::size_t n, class Iter, class RealType>
void fill_array_real(Iter& first, Iter last, RealType (&x)[n])
{
    boost::uint_least32_t mask = ~((~boost::uint_least32_t(0)) << (w%32));
    RealType two32 = 4294967296.0;
    const RealType divisor = RealType(1)/detail::pow2<RealType>(w);
    unsigned int j;
    for(j = 0; j < n; ++j) {
        RealType val = RealType(0);
        RealType mult = divisor;
        for(int k = 0; k < w/32; ++k, ++first) {
            if(first == last) boost::throw_exception(std::invalid_argument("Not enough elements in call to seed."));
            val += *first * mult;
            mult *= two32;
        }
        if(mask != 0) {
            if(first == last) boost::throw_exception(std::invalid_argument("Not enough elements in call to seed."));
            val += (*first & mask) * mult;
            ++first;
        }
        BOOST_ASSERT(val >= 0);
        BOOST_ASSERT(val < 1);
        x[j] = val;
    }
}

}
}
}

#include <boost/random/detail/enable_warnings.hpp>

#endif

/* seed_impl.hpp
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
*/