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

#ifndef BOOST_RANDOM_DETAIL_SEED_HPP
#define BOOST_RANDOM_DETAIL_SEED_HPP

#include <boost/config.hpp>

// Sun seems to have trouble with the use of SFINAE for the
// templated constructor.  So does Borland.
#if !defined(BOOST_NO_SFINAE) && !defined(__SUNPRO_CC) && !defined(BOOST_BORLANDC)

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_arithmetic.hpp>

namespace boost {
namespace random {
namespace detail {

template<class T>
struct disable_seed : boost::disable_if<boost::is_arithmetic<T> > {};

template<class Engine, class T>
struct disable_constructor : disable_seed<T> {};

template<class Engine>
struct disable_constructor<Engine, Engine> {};

#define BOOST_RANDOM_DETAIL_GENERATOR_CONSTRUCTOR(Self, Generator, gen) \
    template<class Generator>                                           \
    explicit Self(Generator& gen, typename ::boost::random::detail::disable_constructor<Self, Generator>::type* = 0)

#define BOOST_RANDOM_DETAIL_GENERATOR_SEED(Self, Generator, gen)    \
    template<class Generator>                                       \
    void seed(Generator& gen, typename ::boost::random::detail::disable_seed<Generator>::type* = 0)

#define BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(Self, SeedSeq, seq)    \
    template<class SeedSeq>                                             \
    explicit Self(SeedSeq& seq, typename ::boost::random::detail::disable_constructor<Self, SeedSeq>::type* = 0)

#define BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(Self, SeedSeq, seq)   \
    template<class SeedSeq>                                     \
    void seed(SeedSeq& seq, typename ::boost::random::detail::disable_seed<SeedSeq>::type* = 0)

#define BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(Self, T, x)  \
    explicit Self(const T& x)

#define BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(Self, T, x) \
    void seed(const T& x)
}
}
}

#else

#include <boost/type_traits/is_arithmetic.hpp>

#define BOOST_RANDOM_DETAIL_GENERATOR_CONSTRUCTOR(Self, Generator, gen) \
    Self(Self& other) { *this = other; }                                \
    Self(const Self& other) { *this = other; }                          \
    template<class Generator>                                           \
    explicit Self(Generator& gen) {                                     \
        boost_random_constructor_impl(gen, ::boost::is_arithmetic<Generator>());\
    }                                                                   \
    template<class Generator>                                           \
    void boost_random_constructor_impl(Generator& gen, ::boost::false_type)

#define BOOST_RANDOM_DETAIL_GENERATOR_SEED(Self, Generator, gen)    \
    template<class Generator>                                       \
    void seed(Generator& gen) {                                     \
        boost_random_seed_impl(gen, ::boost::is_arithmetic<Generator>());\
    }\
    template<class Generator>\
    void boost_random_seed_impl(Generator& gen, ::boost::false_type)

#define BOOST_RANDOM_DETAIL_SEED_SEQ_CONSTRUCTOR(Self, SeedSeq, seq)    \
    Self(Self& other) { *this = other; }                                \
    Self(const Self& other) { *this = other; }                          \
    template<class SeedSeq>                                             \
    explicit Self(SeedSeq& seq) {                                       \
        boost_random_constructor_impl(seq, ::boost::is_arithmetic<SeedSeq>());\
    }                                                                   \
    template<class SeedSeq>                                             \
    void boost_random_constructor_impl(SeedSeq& seq, ::boost::false_type)

#define BOOST_RANDOM_DETAIL_SEED_SEQ_SEED(Self, SeedSeq, seq)           \
    template<class SeedSeq>                                             \
    void seed(SeedSeq& seq) {                                           \
        boost_random_seed_impl(seq, ::boost::is_arithmetic<SeedSeq>()); \
    }                                                                   \
    template<class SeedSeq>                                             \
    void boost_random_seed_impl(SeedSeq& seq, ::boost::false_type)

#define BOOST_RANDOM_DETAIL_ARITHMETIC_CONSTRUCTOR(Self, T, x)  \
    explicit Self(const T& x) { boost_random_constructor_impl(x, ::boost::true_type()); }\
    void boost_random_constructor_impl(const T& x, ::boost::true_type)

#define BOOST_RANDOM_DETAIL_ARITHMETIC_SEED(Self, T, x) \
    void seed(const T& x) { boost_random_seed_impl(x, ::boost::true_type()); }\
    void boost_random_seed_impl(const T& x, ::boost::true_type)

#endif

#endif

/* seed.hpp
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
*/