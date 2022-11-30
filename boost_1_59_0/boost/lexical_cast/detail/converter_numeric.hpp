// Copyright Kevlin Henney, 2000-2005.
// Copyright Alexander Nasonov, 2006-2010.
// Copyright Antony Polukhin, 2011-2022.
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
    if (res) {
        result = converter_t::low_level_convert(converter_t::nearbyint(arg, res));
    }

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