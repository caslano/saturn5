#ifndef BOOST_NUMERIC_SAFE_INTEGER_LITERAL_HPP
#define BOOST_NUMERIC_SAFE_INTEGER_LITERAL_HPP

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cstdint> // for intmax_t/uintmax_t
#include <iosfwd>
#include <type_traits> // conditional, enable_if
#include <boost/mp11/utility.hpp>

#include "utility.hpp"
#include "safe_integer.hpp"
#include "checked_integer.hpp"

namespace boost {
namespace safe_numerics {

template<typename T, T N, class P, class E>
class safe_literal_impl;

template<typename T, T N, class P, class E>
struct is_safe<safe_literal_impl<T, N, P, E> > : public std::true_type
{};

template<typename T, T N, class P, class E>
struct get_promotion_policy<safe_literal_impl<T, N, P, E> > {
    using type = P;
};

template<typename T, T N, class P, class E>
struct get_exception_policy<safe_literal_impl<T, N, P, E> > {
    using type = E;
};
template<typename T, T N, class P, class E>
struct base_type<safe_literal_impl<T, N, P, E> > {
    using type = T;
};

template<typename T, T N, class P, class E>
constexpr T base_value(
    const safe_literal_impl<T, N, P, E> &
) {
    return N;
}

template<typename CharT, typename Traits, typename T, T N, class P, class E>
inline std::basic_ostream<CharT, Traits> & operator<<(
    std::basic_ostream<CharT, Traits> & os,
    const safe_literal_impl<T, N, P, E> &
){
    return os << (
        (std::is_same<T, signed char>::value
        || std::is_same<T, unsigned char>::value
        ) ?
            static_cast<int>(N)
        :
            N
    );
}

template<typename T, T N, class P, class E>
class safe_literal_impl {

    template<
        class CharT,
        class Traits
    >
    friend std::basic_ostream<CharT, Traits> & operator<<(
        std::basic_ostream<CharT, Traits> & os,
        const safe_literal_impl &
    ){
        return os << (
            (::std::is_same<T, signed char>::value
            || ::std::is_same<T, unsigned char>::value
            || ::std::is_same<T, wchar_t>::value
            ) ?
                static_cast<int>(N)
            :
                N
        );
    };

public:

    ////////////////////////////////////////////////////////////
    // constructors
    // default constructor
    constexpr safe_literal_impl(){}

    /////////////////////////////////////////////////////////////////
    // casting operators for intrinsic integers
    // convert to any type which is not safe.  safe types need to be
    // excluded to prevent ambiguous function selection which
    // would otherwise occur
    template<
        class R,
        typename std::enable_if<
            ! boost::safe_numerics::is_safe<R>::value,
            int
        >::type = 0
    >
    constexpr operator R () const {
        // if static values don't overlap, the program can never function
        #if 1
        constexpr const interval<R> r_interval;
        static_assert(
            ! r_interval.excludes(N),
            "safe type cannot be constructed with this type"
        );
        #endif

        return validate_detail<
            R,
            std::numeric_limits<R>::min(),
            std::numeric_limits<R>::max(),
            E
        >::return_value(*this);
    }

    // non mutating unary operators
    constexpr safe_literal_impl<T, N, P, E> operator+() const { // unary plus
        return safe_literal_impl<T, N, P, E>();
    }
    // after much consideration, I've permitted the resulting value of a unary
    // - to change the type in accordance with the promotion policy.
    // The C++ standard does invoke integral promotions so it's changing the type as well.

    /*  section 5.3.1 &8 of the C++ standard
    The operand of the unary - operator shall have arithmetic or unscoped
    enumeration type and the result is the negation of its operand. Integral
    promotion is performed on integral or enumeration operands. The negative
    of an unsigned quantity is computed by subtracting its value from 2n,
    where n is the number of bits in the promoted operand. The type of the
    result is the type of the promoted operand.
    */
    template<
        typename Tx, Tx Nx, typename = std::enable_if_t<! checked::minus(Nx).exception()>
    >
    constexpr auto minus_helper() const {
        return safe_literal_impl<Tx, -N, P, E>();
    }

    constexpr auto operator-() const { // unary minus
        return minus_helper<T, N>();
    }

    /*   section 5.3.1 &10 of the C++ standard
    The operand of ~ shall have integral or unscoped enumeration type; 
    the result is the ones’ complement of its operand. Integral promotions 
    are performed. The type of the result is the type of the promoted operand.
    constexpr safe_literal_impl<T, checked::bitwise_not(N), P, E> operator~() const { // invert bits
        return safe_literal_impl<T, checked::bitwise_not(N), P, E>();
    }
    */
    template<
        typename Tx, Tx Nx, typename = std::enable_if_t<! checked::bitwise_not(Nx).exception()>
    >
    constexpr auto not_helper() const {
        return safe_literal_impl<Tx, ~N, P, E>();
    }

    constexpr auto operator~() const { // unary minus
        return not_helper<T, N>();
    }
};

template<
    std::intmax_t N,
    class P = void,
    class E = void
>
using safe_signed_literal = safe_literal_impl<
    typename utility::signed_stored_type<N, N>,
    N,
    P,
    E
>;

template<
    std::uintmax_t N,
    class P = void,
    class E = void
>
using safe_unsigned_literal = safe_literal_impl<
    typename utility::unsigned_stored_type<N, N>,
    N,
    P,
    E
>;

template<
    class T,
    T N,
    class P = void,
    class E = void,
    typename std::enable_if<
        std::is_signed<T>::value,
        int
    >::type = 0
>
constexpr auto make_safe_literal_impl() {
    return boost::safe_numerics::safe_signed_literal<N, P, E>();
}

template<
    class T,
    T N,
    class P = void,
    class E = void,
    typename std::enable_if<
        ! std::is_signed<T>::value,
        int
    >::type = 0
>
constexpr auto inline make_safe_literal_impl() {
    return boost::safe_numerics::safe_unsigned_literal<N, P, E>();
}

} // safe_numerics
} // boost

#define make_safe_literal(n, P, E)  \
    boost::safe_numerics::make_safe_literal_impl<decltype(n), n, P, E>()

/////////////////////////////////////////////////////////////////
// numeric limits for safe_literal etc.

#include <limits>

namespace std {

template<
    typename T,
    T N,
    class P,
    class E
>
class numeric_limits<boost::safe_numerics::safe_literal_impl<T, N, P, E> >
    : public std::numeric_limits<T>
{
    using SL = boost::safe_numerics::safe_literal_impl<T, N, P, E>;
public:
    constexpr static SL lowest() noexcept {
        return SL();
    }
    constexpr static SL min() noexcept {
        return SL();
    }
    constexpr static SL max() noexcept {
        return SL();
    }
};

} // std

#endif // BOOST_NUMERIC_SAFE_INTEGER_LITERAL_HPP

/* safe_integer_literal.hpp
IkRgcwuILEvBkVuEFBl8AXy/o5sPs1BuxojBk2m3BeGCwOc+wd5NXMTh64FpeZ9TAIXThNtqWjQzswecDMzAfP0Je8YzZmCD94HHAP4t4+Mma4Jl/ijIhzv9idDmmN0+sCkzM7UdruKvNrUEJDsXRZSmxDs2xbgZNDoztQkmbCV4WYSGMCXM/XlTPxE8mxGhd9ioJAlGJDHYtu8TBV8w4dkgeARYWMBfiRCGWFxPK+ojCYEDGUjyIzmqmPoWMMVQJcfNaGJIZJrAMsD2Fl79CF2DZvQjBz1BlM8HoPHwup8IAu3Q/7wzVYAgBQA+CsT42UMQlAfgHoAnANoBpACYArAFgA7Q8QBAg7ALgEEA1tt/gUldDoIsAXgACAEQD+AsgDwA8gAqADQA6AGAA7ABQAQAHwAGACQAFGQhaB7AZwADAF4CuA8gF8B5ACcAxAIIA+AGwBKADoBiOaIMEkCWwwB4ADAA+CkPQbMAxgD0AXgJoApAEYArAE4DOA4gBIATABUAsgBEAHACMJEn8tU10rTQDwpHuwYEQFpKDvG6RlpSkjKyEpbGpiBNC9pJQwJarWBMgAcSvvvwDfJF+7oG+MZ4giCBgPAxsgQSsvC08MGgPYIjg0zDfCN8Azy9PSGL6HC0ZyBS28goHOkeHBaGCUEjg8OQgb7h4b5B3kSju7ZnYPBfeIUjg4MCoglXLMFBSLSPJ8gaGIJBe4bBkWhkpGcYQIV5uqI9PQAFzEXPNcgjwFMHHQLCOqBomzBfNPwesbZvuL9pGMiNJoRDAlyjdcNcQ3x83cMhqxAPwMECMPIMguWw8Q33NHb1JYR/19czCh3m6o5GwqmSUsT365HoYMLnEweQWuZaSI9gz3ACaSD8brwEoXxkONxAnlEhnu5ASFWhAI8DRFSYJxoTFkREAcEdiH/+h+BoQL8YSULQxz9wBqC/3wIc8g+cBBirTADH9AcuFh7r/+JO5j/z4b83H/6rrzb+6+9AikidAwLCPT39oWIQAgPT46/fhviRGGMCtH0j4O86dD3Rlp6BIfAgMXEN9ASpkzBu+2ugX98MAfzrHVpTV7SPxl+/MDEnAVJuizMF6QSHgbFn7Bke7uoNcywlUrqiQdgX5mLkGo5GhYUFh0FQCZAwkjA7yiFUlC/89YY7yAilkQIRUFGe7pASnGP7k6Sd1FEYt/19Evy1STgJ/OkJXAkImoNgMYx83cJcw6KhyzAlnE3DwyMMzgrpAVldPbbTgUR3gASE2QvdhkPwRy7QXRAKDoHnIQbObxzsgQHT+XcbRf7GEqc6wFER5AwODAQII98ggKIitfAk1tMY/mDpb9/a4CGYPsAXVMscNDK0n8TcM8DTNdxTWwuig3kB/zRYjbyIfUGoAwQpk1h4Bnn8bltSEtPgcLQZxnenvaELCP2gCOJfZfAkMIZeQqggD1OwlIDwE0g7zDXSEiwjGhA9pOnp7Ru0nTKC2OagGQxalB1I4+0LVsswwhvcoKQaBNxuoCPCg8M0oHpCTN89GAyoGCAT2tI3EP7apo6EuI4RhQbqNZy2XYNg0PrnSSx8giN3Ul0gLcK6SYzDPfmJMAq2hx8q6l9+kTSMAMNQMwANX4USeVgEgzprhmHCgfp4BrRbgCfa84ibH6EFTEjgGh/BwCNQhSAtiGoFB8AjkB2Oa/oTuogBhANAjp18BiQWaLBEuvto62v6osMhxe2ydIKDACt/Qi95Rvi6e2q5hoRDSwhzT8JWZOoKCocXfMZtfjsI1Hb+nXghzMECDWbtTom62jsfTfFAGh5+mHC0ZbC/5+8tLBwyBi0f7I8J+YUifISlARUj4DmwPUMImaB/8xXWf9z/G27nbwbCrwowQ7//NAN8lwG/A04NEf9UBPx6ADkAWoj4OgH8pypIAcBvt8GHWQaI+K0cIwFPBmgpQH4qkJ8G5KEHeGaIBeKAuKE9kAAkBslAypAWZAG5Q+FQMlQANUPjEAnM4J84xPY/ku1/pNv/yLb/kW//gwA3dwI9ybYMlKB8elDybmgvJAVpQK5QEvQUQiCSEAgSBCmCDEGBoELQIZgQnAgkQhKhjnD5s8ydsnbKoCDUCa4VXC+4ZnDdaEFb0IFSCO/5Eb5bYwR1VIMSwBqKR+BJ8ZR4RvwevBo+AW7pnfa8NXEtDHID+ypQEv5PcMRXRMgIfQqORolwf4LzYSI8LtKAzwn8vD++/yPSUxD6vBrg4THwFvhwfhzwCekICH5dCeIEPlxnScTf8yMI38Xp/RM8zNflX+Cj/gke/g7x7B/j50983r/A3/8X+KZ/gX/7L/Af/wV+/l/g//yQcQcPO/hvWSDNwQkJNP5nYgL00gXEqX7HQ3zB2ZT8d3wArKM+FL/j6hjQ/iS/4yJRxPeFduKm0RBkB/2O3wPxXLLfcb14CHr6B70IRDwqu0CwlFQEXOLf/h7MjsNv4gmvL66trUFrS2vQ3Nwc1NLcAs1Nz0ETExNQ7pVcaGJ8Aiq8WQj5+/pD7q7uUNb5LKivuw/qfN0J8oJ8myDf0hxUWVUJnTp9Cko5kQKNjI5A/oH+UGlZKZR1MQuamJ6ARsZHIHytAYR/4w/h10oh/EQhhB9KgfCjp0A4C8L3HwPyAF6Adg6UPQfKHQFldL5ugTofVkITgGdnawvUAsqpv10KoBCqh8NlAIB8lQAmXhdCpddzoRZAXwpkKY0+BlVGp0AttfVQKUjvbAB+BsCDOkwAeU6FhkNZQM41IP8aqHvl6SwoF+QpBHk7QTuYGxtApaANWgDP3OMpUGFcClQP8wZ1sjMzh+qLS6EWwLMF+IWAZwuQqQXUuRL4lSDPKUc7QJsLFYK8ldcBDvAqBOVXAqgHdC3N9VDhiVMAUqA+UF4fqF8pkOEUaOdKwHNkqA+0dec/77z/uP+4//scBS0b1+5/R/TbsWqY7+ZkZ2en/i/yaHrb2praasDB3Ta+VAhuCnY6kIX9n5ajoWGkZmjoiFLUtNV3g1SYqQ6QwE57PwMhD+1vStgZO6r6+fr6+Yl6ilkYojT12bV9OUhItUiZYecr4ULH/hdyA1EakQO+vox+HhKqFrKGVig6KlEOBKmWljZwWsxazIf+Qm9Ds4+K6gANoPeUUBdVtXI0NFYXPYAA1JSUlFRUVOrMZn+hVwdobhoadd8Dnqp+EhJihs5G6qK+pNrkMLU6cMyyf9LLUlKykIE0Hg5fVQ9VKysLQI8U9dXSBtQ0gPrAgT0qf9KbaWuRIkjIKGlofCU8rAyBczYG9ICcQHzAV26P/F/rS4pAIEgBvZ+FGMoZ5axkaCwn6kdJCZP7iorKye05Av01g7aoL6gCj7KFoRLsUBpycn6UMPUBQC0nh1Sjo/tLF3iglAzFfH2tDZ0J9M7GcnKiMD2BGtAf0afj5GTn+kWvqmQoZ4UC1JrempqaSh7ygB6WhUgO+OtrOGlwcv4aGB7OvLx8coYoJVvYKWmxEei3qQG9rr6ppq4B5y+RLAA9cHvlUEpg0CkhLGH6X+RyAjC9vSP9L3pDIj2hECVbFMJJTs7jN7kcv5e+t46ijv5v+m1yQhZDJUNAL3rggLrodqa9Cvp0Rl5Gpv+UHs6iKSi2X4uEBAHaiMBfR19fw1L3lzzWf6PnNd5ryM5K4QsPNyScwcJbn9PS8jf9jvi8fHwEz1tdVl9f31vDyczMAojDx8dnyqlrSbdDLwb48wHabcfr7K1lY6pvCrKAJ723rpycqT69ERs99TY9kOcXMUzvLYf0ZXWRNdbwBhPaVJ+T8gAFA70lm+k2vZ4VkU4QdsA3kJNTJyFhZt4jJ+es667jTS9/gIbd0oaLbntA6BkSiPcSHMhiqGmvSWvmKSqHRPID2dX0TU29jRwOctGxEek9DYnk/LCDs/DxOUu4uNDKs+kYWPMZcroZ6Wjo2Btr6GsQ6VUt+ARhYgGC44czOCtLKCsrm5tQszmxs5ofkjVQc7I3/k0PMxcQQBKcACgD8D8kAXKY6+mZu+oxMZlLSBxSVabfnjSqcoA7oN4DOyRchJzzoUNScAZVPXNzcz8/cVc9PT+/nVXIAtDvkBMy8FsYSpscOgQXoaqs7Lp/v565nqev7059j5qBIQvImbczIAUMzcxcTExAEcrKEhKu+/3E9cQ9fRl36GnddHXtDkrIIfeA1Y9QgqEFyOBiInVIQvmQhCuTH9N+Jj/1HXpw6DRzsNN1c9M9aqYnB4vF7+xykJABSHRIwpyJ0c+P0ZfmlzwEp+xic1TN3dgADCzz0x5laA261cwGzgAqIWEi5crE6OvrS0N54C/0sJOwBquzvbGSkqKZrCyhBOlDLlLmfr4cvhxULOqcDL9Jic5G1sFBFqwqxpIOsjZmhBJcTGB6DnVhrX9CL6/mpWbn4CAjKXtUVlZSEi7CzMXcj4eKm5tUiOof6Q283LzU1NSO2Bk4HgU5bEAZsjA9NzflLgQV3T/Qq+gauTlZHrE7onbkiJ2dAZznqI8rIwcHDxWL1oGd8fCHUwDrm469u5qumq6TpaXlEYOjBmbm+/UOmUioinro/wN/gpM4JKmmpgPvlmBt1NFRc1A9qGB/2MtKzPTfbcienhJmkrqOfnrwaPXwc/k35P9XuJ1ff/jt/2Qk+luE72rwTVEQI/B/wn93BvjrIA/sz2/7H//mN/3Nh+mg7XyQ2rbPuO1T/vf9+X/jf/xf5A9s+/gdf37bX/83/ta2j2/a9kFOxn/Wvn/1YT0VCRE/MPmlp27rsH93cAZYV12bI+qpsL46AfS1kX6gE77uI+iqsO46MjQCHQP6Wz3Q92C9NRzod/VV9QR9FdZp8Xj4c71Ogr7a198HhWPCoWNxx6DON0DPfNMC4ceBLjoE9NBpoJtuAv12OhfCL5US9VRYRx0HsAnoJmB8JYSfA3RrgOccoNksJeqysC4NZJkAsowAvrBuWl8LdNTiLIBvIeqtZds6LNAJYX2yEuh/lXAc6HywjjoxBHTIK1lEHRHUpZOgF54i6Jqw/joB9MKW4hSoE6TBOiWsY8L68UhZOEFf7bxJ1FVzMURdFtaJYR20D+SZ6y8k6NC5oG0Kz5+C+m4fA/rwKWhtNAvqLAN0MC3QZUdagS598RQ0UgXkgPVXUI+sQMAfyAzrsLD+DOvmsA7eB+vpoE6wng7rrLDu3gfqPtENZHyYS9RzgV4L690joN1h/ZmgD4OyKuE6gnywvg3rwrC+W/kQrjeMq4dGQN+VgvaBdeS1N+FQJcgL68mdzbkEO8F/3H/cn46T83f4l0uUNTlibS0LDvwO3qaMjBx/pVEJj4xW0fVPMXFn1AgkJ6GW8uBkZGT8RaOgYhBoQJmoohItaS6BIgPHawS5OJfWL4JEGmoGg8RE3URdv2OqKHFycdjxIRw4iMkapDSku6hpD6roKvuZqKJBWmBgoIwMnw0dMR0iJUEc2MWg4W9vbGzilBgIJ0vIqAoe2c4PQeISJ3dRx0u6urrC6YEoCQlVS0sRa8addMhVUiXV3hikH3FRDZSRkAEnAkuk++8qHE22sHeFnbOLKmANJzvxgvRtDn5A1UtOtnB1d3dzcSLmdnLZ485ofYzIQBKkgv/Jhq6aFk6qlk5OTi4uLtzujO7bBdjDiQTnetRJIlAiUdWJkL4jgPFOcrKxoQ4VNTk5n4ylk53tr/Sjv9JNVE0YGd1NZaXtXQwNf1XgF3tDd5koa5gvcLpOdNvpaiCdh2fvXh4eHUNLEsDcxTnpCCMnyoeTkdDEISCVm1tAgJvbUEfHUVk5xCU4ORkUY2JObAD75L1i/Ht4effwc+819LfyUTDjtDHx0VJTjvYkpLvwcAvxiiKFkfv4BQz9o62s1FW0Qnd7J2ig4ghdpBNst28/i6CgCJJX6Gi0ggIgUNfy9g7VMIgilO9o4yx9QlWGj5VFeI8FOBUqWMVbqXPF+gYFEtMhiMkjzNT2cIiTpZ0x0B7Uoq0U1IPQ7AHicX+MU+VDKUlJroqySsrKctFq9LsDaL3Iff5Ij8DoRURLRrq5ySqrqSlLxXpR0yCk/kg38wwLxxjp6UVGuMnKu/kwU1OwIaR2hiDsrN2PmBw7dvyYqSNGz8zHN0ZLQ8Ls9xDbccp6tsfMzU00dSO0w/30Hf4h/X+5I54X1PDrdKT4j6CzmyBoDwyJ2z7A7QFHFUoYQJj0n0HTvwCQhxT/JyQC+AngDwefU+A7FST0+5yi/i/uvXbs6PDZAz6TwOcR2J5eCPa6Y2Avhs8msP0ctqtXwvs+YW/vhFLA/gqfSWC7OXwugW3mLWCPg88nhHMHfAaBzxzd4cTzBnweGSfazNfGCwn74tp0PTQ3VAn2xBFobrSPaEcHez3Rlg5w0yOEvRze19daw7f30BbCeaMSnIHgcwV8liDsv4QzCjiPPCSeSQg2b9i+DeRtKSuE+sqOEc4eLcVwncIJZ48scM4YeQPOAg9Ttm3mx8C+XgqNNOQSzi+d4JzRB3ATrSng/ALb8UuhiYfhIA/Y46tSCGeSuYZwwrmgsxicL/rBWQLs8SOvS0EdOqGWK/BZApxRGgrBmQA+I3VCx8AZ5j/uP+7/TAfvUpTEzYoQJSU/IMHogEAgROhgBAkJqTgjo72g8D6kHZEAdtb8ApZCtoz0EMRgfET/oKSVjZDQfgtGGpBsJrZH7Kioocl+UT3GwyAO22yUGRlVNHQ0Ganh+G7e3dqMKEZGRyNGNhDn5uFkN2CUU1IFbMG6xcjOwcXByXjIVFFXVxrwA9sn114+RvlDpuLSaiw7EkvJyMuyMjMRLXqwQApa5hS7yNT/rNROjf7iYJ2uiZJ4oQwDfCeb+F/A/Db8RBDz/vXeclsRpCB6/1gWnqDPwXeNv+4U4TVx515x+04RXlPgOzj4DhC+y4PvB/8nHKnMH+8k/uFUHsn8LaW9faYJIm1kZpb5M4Wueah+uH2clnB7ABK232ikf8fPX1dX92R8Dz//XmZm7kfbeICG8XXde2Aj415mbiKeln8bP7xngWCo3MYjmEFkE6C7iXj+bfwDIr5+uPvMIgF/bAfPDOOHh4fPEOgPxm2Xy8y8i1+sHuDxBEsoPo6UiEfgmfkBm+EPBDwen7ldNdrhOn6YzTB+EUbjM8eJCbRDm0PD7e0E/EEYP6NCqDJtD2oTxrPgF2E0PnmmuZuI19YOHm7vAHjCzlsw0z6yg9d2rgf4RgL+2g4evlXRRtU/2i43cEb18G+8traD/0NQE5i+mYCv28Yb+0sD+c/gN9tlCPh6GGmlrW3EPTvTXNe4auXQLEOkt7QCzvID9yzsmvE7fFBWBPybM8r17Z2d48wyBDxtpZWVtZeXlSOemZkD3z3c2cWiLEPEe8HOv6O5Dp920WpktrmOiLf28s3JATle16mqDtnLqHYMdzbBeK+cK8XFd708X4NOlpFRrhtWHYHxVV5XitLSMnIIeKJrgPms5hSdjIzMKL5BxD8Uq3soQMBfSYuMjIwqvvqLnohv3DgZBhLS7m1jt+lJZVTr1sP4I6N+4/lhPERbLyMz1HgyMncbD4YcAQ9aov5D++vGrW38QfwOHqTUfWhv3y50cfE3nhYgfuF/8QFzYHh4m0vdQ35+ZpZfeBl4YA39A55WRkYVTiHg9zLz7eChD2C8qYLEIThPY8MvPCwsGHTtHcPAH/oT
*/