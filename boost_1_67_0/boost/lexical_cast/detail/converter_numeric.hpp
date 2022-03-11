// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2020.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// what:  lexical_cast custom keyword cast
// who:   contributed by Kevlin Henney,
//        enhanced with contributions from Terje Slettebo,
//        with additional fixes and suggestions from Gennaro Prota,
//        Beman Dawes, Dave Abrahams, Daryle Walker, Peter Dimov,
//        Alexander Nasonov, Antony Polukhin, Justin Viiret, Michael Hofmann,
//        Cheng Yang, Matthew Bradbury, David W. Birdsall, Pavel Korzh and other Boosters
// when:  November 2000, March 2003, June 2005, June 2006, March 2011 - 2016

#ifndef BOOST_LEXICAL_CAST_DETAIL_CONVERTER_NUMERIC_HPP
#define BOOST_LEXICAL_CAST_DETAIL_CONVERTER_NUMERIC_HPP

#include <boost/config.hpp>
#ifdef BOOST_HAS_PRAGMA_ONCE
#   pragma once
#endif

#include <boost/limits.hpp>
#include <boost/type_traits/type_identity.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_float.hpp>

#include <boost/numeric/conversion/cast.hpp>

namespace boost { namespace detail {

template <class Source >
struct detect_precision_loss
{
    typedef Source source_type;
    typedef boost::numeric::Trunc<Source> Rounder;
    typedef BOOST_DEDUCED_TYPENAME conditional<
        boost::is_arithmetic<Source>::value, Source, Source const&
    >::type argument_type ;

    static inline source_type nearbyint(argument_type s, bool& is_ok) BOOST_NOEXCEPT {
        const source_type near_int = Rounder::nearbyint(s);
        if (near_int && is_ok) {
            const source_type orig_div_round = s / near_int;
            const source_type eps = std::numeric_limits<source_type>::epsilon();

            is_ok = !((orig_div_round > 1 ? orig_div_round - 1 : 1 - orig_div_round) > eps);
        }

        return s;
    }

    typedef typename Rounder::round_style round_style;
};

template <typename Base, class Source>
struct fake_precision_loss: public Base
{
    typedef Source source_type ;
    typedef BOOST_DEDUCED_TYPENAME conditional<
        boost::is_arithmetic<Source>::value, Source, Source const&
    >::type argument_type ;

    static inline source_type nearbyint(argument_type s, bool& /*is_ok*/) BOOST_NOEXCEPT {
        return s;
    }
};

struct nothrow_overflow_handler
{
    inline bool operator() ( boost::numeric::range_check_result r ) const BOOST_NOEXCEPT {
        return (r == boost::numeric::cInRange);
    }
};

template <typename Target, typename Source>
inline bool noexcept_numeric_convert(const Source& arg, Target& result) BOOST_NOEXCEPT {
    typedef boost::numeric::converter<
            Target,
            Source,
            boost::numeric::conversion_traits<Target, Source >,
            nothrow_overflow_handler,
            detect_precision_loss<Source >
    > converter_orig_t;

    typedef BOOST_DEDUCED_TYPENAME boost::conditional<
        boost::is_base_of< detect_precision_loss<Source >, converter_orig_t >::value,
        converter_orig_t,
        fake_precision_loss<converter_orig_t, Source>
    >::type converter_t;

    bool res = nothrow_overflow_handler()(converter_t::out_of_range(arg));
    result = converter_t::low_level_convert(converter_t::nearbyint(arg, res));
    return res;
}

template <typename Target, typename Source>
struct lexical_cast_dynamic_num_not_ignoring_minus
{
    static inline bool try_convert(const Source &arg, Target& result) BOOST_NOEXCEPT {
        return noexcept_numeric_convert<Target, Source >(arg, result);
    }
};

template <typename Target, typename Source>
struct lexical_cast_dynamic_num_ignoring_minus
{
    static inline bool try_convert(const Source &arg, Target& result) BOOST_NOEXCEPT {
        typedef BOOST_DEDUCED_TYPENAME boost::conditional<
                boost::is_float<Source>::value,
                boost::type_identity<Source>,
                boost::make_unsigned<Source>
        >::type usource_lazy_t;
        typedef BOOST_DEDUCED_TYPENAME usource_lazy_t::type usource_t;

        if (arg < 0) {
            const bool res = noexcept_numeric_convert<Target, usource_t>(0u - arg, result);
            result = static_cast<Target>(0u - result);
            return res;
        } else {
            return noexcept_numeric_convert<Target, usource_t>(arg, result);
        }
    }
};

/*
 * lexical_cast_dynamic_num follows the rules:
 * 1) If Source can be converted to Target without precision loss and
 * without overflows, then assign Source to Target and return
 *
 * 2) If Source is less than 0 and Target is an unsigned integer,
 * then negate Source, check the requirements of rule 1) and if
 * successful, assign static_casted Source to Target and return
 *
 * 3) Otherwise throw a bad_lexical_cast exception
 *
 *
 * Rule 2) required because boost::lexical_cast has the behavior of
 * stringstream, which uses the rules of scanf for conversions. And
 * in the C99 standard for unsigned input value minus sign is
 * optional, so if a negative number is read, no errors will arise
 * and the result will be the two's complement.
 */
template <typename Target, typename Source>
struct dynamic_num_converter_impl
{
    static inline bool try_convert(const Source &arg, Target& result) BOOST_NOEXCEPT {
        typedef BOOST_DEDUCED_TYPENAME boost::conditional<
            boost::is_unsigned<Target>::value &&
            (boost::is_signed<Source>::value || boost::is_float<Source>::value) &&
            !(boost::is_same<Source, bool>::value) &&
            !(boost::is_same<Target, bool>::value),
            lexical_cast_dynamic_num_ignoring_minus<Target, Source>,
            lexical_cast_dynamic_num_not_ignoring_minus<Target, Source>
        >::type caster_type;

        return caster_type::try_convert(arg, result);
    }
};

}} // namespace boost::detail

#endif // BOOST_LEXICAL_CAST_DETAIL_CONVERTER_NUMERIC_HPP


/* converter_numeric.hpp
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
*/