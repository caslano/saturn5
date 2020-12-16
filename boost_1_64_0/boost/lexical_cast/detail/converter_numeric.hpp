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
nLdf5/vDTmBP4GucR3fa8xXXnIBxhvnqdfaXnfTj9IbS3ouYL8GQ723m28X++w7zZXKNw5tckMZ83ZgvnXJBd8oFGdpzuWqZ9+fyDPKhGGjlL+G8PZt8OYXP6bnAg3l+EM9n8bw9n1DflmYY/6tZ3utZvjV8z7+Z43MtsCvjzvpnk15bQ/2fYDtu43vhU8BE4JPA/YFPs1w7bF0p+hbpWOmeIZ3bOX9sZHnuotxwN+WE+zhfb6Fc8CpwKvBBYKnQq32/fgR4LvBR4BXAxykPbAOus8oFvNsqF3CzdX/gDuCzwDdJ923g88D3gC8AvwC+BPwa+DJwN/AV4C9WevIp2ak/JH8gN8vvWNbvBI2f1UzX18DPG8jPG8nPm9jeN3PcrQPGhjTMb1e5H767dny17/x3hWQ3fP+xkJrG8eeVUePi0+sv24PsfaDu32t8zd+7F9klNX/dfmQbavzz+/Vv3ZMs6s5QlYGQjVCEsBChCmEHwm6E2I24jpCNUIJQibARYQfCHoTEu0LVAITxCJcgbEHYgRByd6hKRshCKEKoQNiEsAtB3YNrCFkI+QiVCBsRdiDsRojahHsijEEoQVi1KeCfLHAEjsAROAJH4PinHPvE/x/saRvL/9+jbZRtX5pL/3/Zqg4HQxituNjFzgy3l9LkFBfla379C7zZZTC/bbtLu2mzrQLT0laBaXO821wyPW2Q7L3ZzN9RXez7u5435HqIop8o+mmvXTvNSajf1s3yE/X2xZ5+osAf+lp3swMWPrjbN7C+7nvKS73+mv3IGmrH0Fh7wH8s9g2TWp3Qd8oDD5Z9uvjQ0yYccFC8t/X1gN3DkEbeG76x7BKo/+P4wm+D/q8l9VAJXHduxT3h2wO7Uu+bxvX2UYynBvyV16vfCPgrb5juwh+9RWPpLPaVviLk3oAuIHAEjsAROAJH4Pg7j30i/+cXNJr8/7gm/48Noq2EIlL+T3aT/3F7N/mfcrpZ/kd+wz5zZvkfaQ37zJllf6Q17R1nlv2T65H9Z/qQ/cf7KfuXeJP9yRtd9tf1ARGGvdeiXPZZ+2/J/YkHO3D+jrO+vujCzGYVjrWdIz8Z8EH3gNz/b5X7ZWwBj2mA3O+U91OA3Whfn23FA3J/QO4PyP1+yf1zA3J/4AgcgSNwBI7A8Y849oX83ytncmlJeQ9LBbDX8v/Tmvzfswl97wfXfmOUClyVqlTuuSL/Z48YMrpXTvbgEVnDeuQMHzloCJJoPgJKsC1gnb/4BZKnyKQPID17jZ95ueZN3y1PSJokFUSf6TGIfSLnWpj0BqSp6xjK8orKa/fL2wD/FJfL9ahgp7x/qsS7mvQK7uUjLa8+QfR7M30h/Jaa97vXaU9OsNLWelNX2t7/50iat9UlqOtmBOO+9+ca7CSsIrKMSVr6JC099TUuviWStbTJBtpKlQtxvX2OOU98CQVlqjWOSDvd5BIrVQzrMUXS9Aj6ytGJ5xwqV841D2qivtLyzcxHPmmrVWir9XL/PUHN7OvT7X6VeL60o6RdjbS19IZI2vaSttDen22iXPvBcbBah3vhHGLHSf4mkn8t8l8j9woJtup6Vap4eYcf25zykqK6fcy+kTQ3BMWjBYfj3iWOx9VpQVEsk0OFyX2ChOYa0Nwk6T9DmYTX8tVxe/p9WSzXwoJPxzhdr6JVYlCkmhWUqN4Mipb8y5F/maSJkDJNsApg9ZHymbZvoi1IE+lSXqVag348YilSlpODYsGFuY7RalhQjNDdhDypcu10ja8zbL5Omm9du1v6x1sHCh+tO8r9KpH3WDVOeHopGvZnVOQXhN8RfiaWYx75FWiF3xCmteE5Oy7p9CA6NbDZPjQF25Bo8Xs=
*/