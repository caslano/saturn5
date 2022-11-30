#ifndef BOOST_NUMERIC_AUTOMATIC_HPP
#define BOOST_NUMERIC_AUTOMATIC_HPP

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// policy which creates expanded results types designed
// to avoid overflows.

#include <limits>
#include <cstdint>     // (u)intmax_t,
#include <type_traits> // conditional
#include <boost/integer.hpp>

#include "safe_common.hpp"
#include "checked_result.hpp"
#include "checked_default.hpp"
#include "checked_integer.hpp"
#include "checked_result_operations.hpp"
#include "interval.hpp"
#include "utility.hpp"

namespace boost {
namespace safe_numerics {

struct automatic {
private:
    // the following returns the "true" type.  After calculating the new max and min
    // these return the minimum size type which can hold the expected result.
    struct defer_stored_signed_lazily {
        template<std::intmax_t Min, std::intmax_t Max>
        using type = utility::signed_stored_type<Min, Max>;
    };

    struct defer_stored_unsigned_lazily {
        template<std::uintmax_t Min, std::uintmax_t Max>
        using type = utility::unsigned_stored_type<Min, Max>;
    };

    template<typename T, T Min, T Max>
    struct result_type {
        using type = typename std::conditional<
            std::numeric_limits<T>::is_signed,
            defer_stored_signed_lazily,
            defer_stored_unsigned_lazily
        >::type::template type<Min, Max>;
    };

public:
    ///////////////////////////////////////////////////////////////////////
    template<typename T, typename U>
    struct addition_result {
        using temp_base_type = typename std::conditional<
            // if both arguments are unsigned
            ! std::numeric_limits<T>::is_signed
            && ! std::numeric_limits<U>::is_signed,
            // result is unsigned
            std::uintmax_t,
            // otherwise result is signed
            std::intmax_t
        >::type;

        using r_type = checked_result<temp_base_type>;
        using r_interval_type = interval<r_type>;

        constexpr static const r_interval_type t_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr static const r_interval_type u_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        constexpr static const r_interval_type r_interval = t_interval + u_interval;

        constexpr static auto rl = r_interval.l;
        constexpr static auto ru = r_interval.u;

        using type = typename result_type<
            temp_base_type,
            rl.exception()
                ? std::numeric_limits<temp_base_type>::min()
                : static_cast<temp_base_type>(rl),
            ru.exception()
                ? std::numeric_limits<temp_base_type>::max()
                : static_cast<temp_base_type>(ru)
        >::type;
    };

    ///////////////////////////////////////////////////////////////////////
    template<typename T, typename U>
    struct subtraction_result {
        // result of subtraction are always signed.
        using temp_base_type = intmax_t;

        using r_type = checked_result<temp_base_type>;
        using r_interval_type = interval<r_type>;

        constexpr static const r_interval_type t_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr static const r_interval_type u_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        constexpr static const r_interval_type r_interval = t_interval - u_interval;

        constexpr static auto rl = r_interval.l;
        constexpr static auto ru = r_interval.u;

        using type = typename result_type<
            temp_base_type,
            rl.exception()
                ? std::numeric_limits<temp_base_type>::min()
                : static_cast<temp_base_type>(rl),
            ru.exception()
                ? std::numeric_limits<temp_base_type>::max()
                : static_cast<temp_base_type>(ru)
        >::type;
    };

    ///////////////////////////////////////////////////////////////////////
    template<typename T, typename U>
    struct multiplication_result {
        using temp_base_type = typename std::conditional<
            // if both arguments are unsigned
            ! std::numeric_limits<T>::is_signed
            && ! std::numeric_limits<U>::is_signed,
            // result is unsigned
            std::uintmax_t,
            // otherwise result is signed
            std::intmax_t
        >::type;

        using r_type = checked_result<temp_base_type>;
        using r_interval_type = interval<r_type>;

        constexpr static const r_interval_type t_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr static const r_interval_type u_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        constexpr static const r_interval_type r_interval = t_interval * u_interval;

        constexpr static const auto rl = r_interval.l;
        constexpr static const auto ru = r_interval.u;

        using type = typename result_type<
            temp_base_type,
            rl.exception()
                ? std::numeric_limits<temp_base_type>::min()
                : static_cast<temp_base_type>(rl),
            ru.exception()
                ? std::numeric_limits<temp_base_type>::max()
                : static_cast<temp_base_type>(ru)
        >::type;
    };

    ///////////////////////////////////////////////////////////////////////
    template<typename T, typename U>
    struct division_result {
        using temp_base_type = typename std::conditional<
            // if both arguments are unsigned
            ! std::numeric_limits<T>::is_signed
            && ! std::numeric_limits<U>::is_signed,
            // result is unsigned
            std::uintmax_t,
            // otherwise result is signed
            std::intmax_t
        >::type;

        using r_type = checked_result<temp_base_type>;
        using r_interval_type = interval<r_type>;

        constexpr static const r_interval_type t_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr static const r_interval_type u_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        constexpr static r_interval_type rx(){
            if(u_interval.u < r_type(0)
            || u_interval.l > r_type(0))
                return t_interval / u_interval;
            return utility::minmax(
                std::initializer_list<r_type> {
                    t_interval.l / u_interval.l,
                    t_interval.l / r_type(-1),
                    t_interval.l / r_type(1),
                    t_interval.l / u_interval.u,
                    t_interval.u / u_interval.l,
                    t_interval.u / r_type(-1),
                    t_interval.u / r_type(1),
                    t_interval.u / u_interval.u,
                }
            );
        }

        constexpr static const r_interval_type r_interval = rx();

        constexpr static auto rl = r_interval.l;
        constexpr static auto ru = r_interval.u;

        using type = typename result_type<
            temp_base_type,
            rl.exception()
                ? std::numeric_limits<temp_base_type>::min()
                : static_cast<temp_base_type>(rl),
            ru.exception()
                ? std::numeric_limits<temp_base_type>::max()
                : static_cast<temp_base_type>(ru)
        >::type;
    };

    ///////////////////////////////////////////////////////////////////////
    template<typename T, typename U>
    struct modulus_result {
        using temp_base_type = typename std::conditional<
            // if both arguments are unsigned
            ! std::numeric_limits<T>::is_signed
            && ! std::numeric_limits<U>::is_signed,
            // result is unsigned
            std::uintmax_t,
            // otherwise result is signed
            std::intmax_t
        >::type;

        using r_type = checked_result<temp_base_type>;
        using r_interval_type = interval<r_type>;

        constexpr static const r_interval_type t_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr static const r_interval_type u_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        constexpr static r_interval_type rx(){
            if(u_interval.u < r_type(0)
            || u_interval.l > r_type(0))
                return t_interval / u_interval;
            return utility::minmax(
                std::initializer_list<r_type> {
                    t_interval.l % u_interval.l,
                    t_interval.l % r_type(-1),
                    t_interval.l % r_type(1),
                    t_interval.l % u_interval.u,
                    t_interval.u % u_interval.l,
                    t_interval.u % r_type(-1),
                    t_interval.u % r_type(1),
                    t_interval.u % u_interval.u,
                }
            );
        }

        constexpr static const r_interval_type r_interval = rx();

        constexpr static auto rl = r_interval.l;
        constexpr static auto ru = r_interval.u;

        using type = typename result_type<
            temp_base_type,
            rl.exception()
                ? std::numeric_limits<temp_base_type>::min()
                : static_cast<temp_base_type>(rl),
            ru.exception()
                ? std::numeric_limits<temp_base_type>::max()
                : static_cast<temp_base_type>(ru)
        >::type;
    };

    ///////////////////////////////////////////////////////////////////////
    // note: comparison_result (<, >, ...) is special.
    // The return value is always a bool.  The type returned here is
    // the intermediate type applied to make the values comparable.
    template<typename T, typename U>
    struct comparison_result {
        using temp_base_type = typename std::conditional<
            // if both arguments are unsigned
            ! std::numeric_limits<T>::is_signed
            && ! std::numeric_limits<U>::is_signed,
            // result is unsigned
            std::uintmax_t,
            // otherwise result is signed
            std::intmax_t
        >::type;

        using r_type = checked_result<temp_base_type>;
        using r_interval_type = interval<r_type>;

        constexpr static const r_interval_type t_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr static const r_interval_type u_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        // workaround some microsoft problem
        #if 0
        constexpr static r_type min(const r_type & t, const r_type & u){
            // assert(! u.exception());
            // assert(! t.exception());
            return static_cast<bool>(t < u) ? t : u;
        }

       constexpr static r_type max(const r_type & t, const r_type & u){
            // assert(! u.exception());
            // assert(! t.exception());
            return static_cast<bool>(t < u) ? u : t;
        }
        #endif

        // union of two intervals
        // note: we can't use t_interval | u_interval because it
        // depends on max and min which in turn depend on < which in turn
        // depends on implicit conversion of tribool to bool
        constexpr static r_interval_type union_interval(
            const r_interval_type & t,
            const r_interval_type & u
        ){
            //const r_type & rl = min(t.l, u.l);
            const r_type & rmin = static_cast<bool>(t.l < u.l) ? t.l : u.l;
            //const r_type & ru = max(t.u, u.u);
            const r_type & rmax = static_cast<bool>(t.u < u.u) ? u.u : t.u;
            return r_interval_type(rmin, rmax);
        }

        constexpr static const r_interval_type r_interval =
            union_interval(t_interval, u_interval);

        constexpr static auto rl = r_interval.l;
        constexpr static auto ru = r_interval.u;

        using type = typename result_type<
            temp_base_type,
            rl.exception()
                ? std::numeric_limits<temp_base_type>::min()
                : static_cast<temp_base_type>(rl),
            ru.exception()
                ? std::numeric_limits<temp_base_type>::max()
                : static_cast<temp_base_type>(ru)
        >::type;
    };

    ///////////////////////////////////////////////////////////////////////
    // shift operations
    template<typename T, typename U>
    struct left_shift_result {
        using temp_base_type = typename std::conditional<
            std::numeric_limits<T>::is_signed,
            std::intmax_t,
            std::uintmax_t
        >::type;

        using r_type = checked_result<temp_base_type>;
        using r_interval_type = interval<r_type>;

        constexpr static const r_interval_type t_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr static const r_interval_type u_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        constexpr static const r_interval_type r_interval =
            t_interval << u_interval;

        constexpr static auto rl = r_interval.l;
        constexpr static auto ru = r_interval.u;

        using type = typename result_type<
            temp_base_type,
            rl.exception()
                ? std::numeric_limits<temp_base_type>::min()
                : static_cast<temp_base_type>(rl),
            ru.exception()
                ? std::numeric_limits<temp_base_type>::max()
                : static_cast<temp_base_type>(ru)
        >::type;
    };

    ///////////////////////////////////////////////////////////////////////
    template<typename T, typename U>
    struct right_shift_result {
        using temp_base_type = typename std::conditional<
            std::numeric_limits<T>::is_signed,
            std::intmax_t,
            std::uintmax_t
        >::type;

        using r_type = checked_result<temp_base_type>;
        using r_interval_type = interval<r_type>;

        constexpr static const r_interval_type t_interval{
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::min())),
            checked::cast<temp_base_type>(base_value(std::numeric_limits<T>::max()))
        };

        constexpr static const r_type u_min
            = checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::min()));

        constexpr static const r_interval_type u_interval{
            u_min.exception()
            ? r_type(0)
            : u_min,
            checked::cast<temp_base_type>(base_value(std::numeric_limits<U>::max()))
        };

        constexpr static const r_interval_type r_interval = t_interval >> u_interval;

        constexpr static auto rl = r_interval.l;
        constexpr static auto ru = r_interval.u;

        using type = typename result_type<
            temp_base_type,
            rl.exception()
                ? std::numeric_limits<temp_base_type>::min()
                : static_cast<temp_base_type>(rl),
            ru.exception()
                ? std::numeric_limits<temp_base_type>::max()
                : static_cast<temp_base_type>(ru)
        >::type;

    };

    ///////////////////////////////////////////////////////////////////////
    template<typename T, typename U>
    struct bitwise_and_result {
        using type = decltype(
            typename base_type<T>::type()
            & typename base_type<U>::type()
        );
    };
    template<typename T, typename U>
    struct bitwise_or_result {
        using type = decltype(
            typename base_type<T>::type()
            | typename base_type<U>::type()
        );
    };
    template<typename T, typename U>
    struct bitwise_xor_result {
        using type = decltype(
            typename base_type<T>::type()
            ^ typename base_type<U>::type()
        );
    };
};

} // safe_numerics
} // boost

#endif // BOOST_NUMERIC_AUTOMATIC_HPP

/* automatic.hpp
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
*/