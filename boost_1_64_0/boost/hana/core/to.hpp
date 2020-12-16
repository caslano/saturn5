/*!
@file
Defines `boost::hana::to` and related utilities.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_TO_HPP
#define BOOST_HANA_CORE_TO_HPP

#include <boost/hana/fwd/core/to.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/wrong.hpp>
#include <boost/hana/unpack.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // to
    //////////////////////////////////////////////////////////////////////////
    //! @cond
    template <typename To, typename From, typename>
    struct to_impl : to_impl<To, From, when<true>> { };
    //! @endcond

    namespace convert_detail {
        struct no_conversion { };

        template <typename To, typename From, typename = void>
        struct maybe_static_cast : no_conversion {
            template <typename X>
            static constexpr auto apply(X const&) {
                static_assert(detail::wrong<to_impl<To, From>, X>{},
                "no conversion is available between the provided types");
            }
        };

        template <typename To, typename From>
        struct maybe_static_cast<To, From, decltype((void)
            static_cast<To>(std::declval<From>())
        )> {
            template <typename X>
            static constexpr To apply(X&& x)
            { return static_cast<To>(static_cast<X&&>(x)); }
        };
    } // end namespace convert_detail

    template <typename To, typename From, bool condition>
    struct to_impl<To, From, when<condition>>
        : convert_detail::maybe_static_cast<To, From>
    { };

    template <typename To>
    struct to_impl<To, To> : embedding<> {
        template <typename X>
        static constexpr X apply(X&& x)
        { return static_cast<X&&>(x); }
    };

    //! @cond
    template <typename To>
    template <typename X>
    constexpr decltype(auto) to_t<To>::operator()(X&& x) const {
        using From = typename hana::tag_of<X>::type;
        return to_impl<To, From>::apply(static_cast<X&&>(x));
    }
    //! @endcond

#define BOOST_HANA_DEFINE_EMBEDDING_IMPL(TO, FROM)                          \
    template <>                                                             \
    struct to_impl<TO, FROM> : embedding<>                                  \
    { static constexpr TO apply(FROM x) { return x; } }                     \
/**/
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(long double, double);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(long double, float);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(double     , float);

    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long long, signed long);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long long, signed int);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long long, signed short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long long, signed char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long     , signed int);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long     , signed short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed long     , signed char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed int      , signed short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed int      , signed char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(signed short    , signed char);

    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long long, unsigned long);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long long, unsigned int);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long long, unsigned short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long long, unsigned char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long     , unsigned int);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long     , unsigned short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned long     , unsigned char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned int      , unsigned short);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned int      , unsigned char);
    BOOST_HANA_DEFINE_EMBEDDING_IMPL(unsigned short    , unsigned char);
#undef BOOST_HANA_DEFINE_EMBEDDING_IMPL

    namespace detail {
        template <typename T>
        struct copy_char_signedness {
            using type = typename std::conditional<std::is_signed<char>::value,
                std::make_signed<T>, std::make_unsigned<T>
            >::type::type;
        };
    }

    // If `char` is signed, we define an embedding from `char` to any signed
    // integral type. Otherwise, we define one from `char` to any unsigned
    // integral type.
#define BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL(TO)                           \
    template <>                                                             \
    struct to_impl<detail::copy_char_signedness<TO>::type, char>            \
        : embedding<>                                                       \
    {                                                                       \
        static constexpr detail::copy_char_signedness<TO>::type             \
        apply(char x)                                                       \
        { return x; }                                                       \
    }                                                                       \
/**/
    BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL(long long);
    BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL(long);
    BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL(int);
    BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL(short);
#undef BOOST_HANA_DEFINE_CHAR_EMBEDDING_IMPL

    template <typename T>
    struct to_impl<T*, decltype(nullptr)> : embedding<> {
        static constexpr T* apply(decltype(nullptr)) { return nullptr; }
    };

    //////////////////////////////////////////////////////////////////////////
    // is_convertible
    //////////////////////////////////////////////////////////////////////////
    template <typename From, typename To, typename>
    struct is_convertible : std::true_type { };

    template <typename From, typename To>
    struct is_convertible<From, To, decltype((void)
        static_cast<convert_detail::no_conversion>(*(to_impl<To, From>*)0)
    )> : std::false_type { };

    //////////////////////////////////////////////////////////////////////////
    // is_embedded
    //////////////////////////////////////////////////////////////////////////
    template <typename From, typename To, typename>
    struct is_embedded : std::false_type { };

    template <typename From, typename To>
    struct is_embedded<From, To, decltype((void)
        static_cast<embedding<true>>(*(to_impl<To, From>*)0)
    )> : std::true_type { };

    //////////////////////////////////////////////////////////////////////////
    // Conversion for Constants
    //////////////////////////////////////////////////////////////////////////
    template <typename To, typename From>
    struct to_impl<To, From, when<
        hana::Constant<From>::value &&
        is_convertible<typename From::value_type, To>::value
    >> : embedding<is_embedded<typename From::value_type, To>::value> {
        template <typename X>
        static constexpr decltype(auto) apply(X const&)
        { return hana::to<To>(hana::value<X>()); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Foldable -> Sequence
    //////////////////////////////////////////////////////////////////////////
    template <typename S, typename F>
    struct to_impl<S, F, when<
        hana::Sequence<S>::value &&
        hana::Foldable<F>::value
    >> : embedding<Sequence<F>::value> {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::unpack(static_cast<Xs&&>(xs), hana::make<S>); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_TO_HPP

/* to.hpp
+mCeZM/3X9olc4DxTj87N/em7AqsKtmUCg1DlQXWMX7v7mnaeLXMAeZD1ni0o488J4yfJc/nlsw9DVaRbOLpxBHSaxg/Z7HQ5/skL3WN39dnBk7Ol17DLMl8eq30lCzBKpE12F7tV2WRMH+ywgke0yVLsACyC+lzC0sNMN7p6E72xZVlwzjz1iOnZEpego1/rno8cmlXZe4wL7KOhwrdl7zAnMjOm7QukJ2GlSbL2HNruew0jGu/tbKb1JcKK8v7cGjIDalBe5ZmPlmS+QKthqJ7D8s59x9MTZrRu+djUoORkhcY57pDVct20msY79iSn/aVV5YM4ywNiPqeswyYK1n2hw0XJUvaudqXfLorM9Qzto2/Zl1QFgTzJWv3aMw/pdcwP7LbId2+76Z2zQ+PQ05LXmC8R7Ynf+ypLB9mRubbu+tZ6TXMg2xYn3ktpNf1jT9vA3sGOkteYLxj3bsXe6gsDsazrdxhQ4b0WrO0basvSa9hnOveZ6pny3PCypFtKeleRJ4zxDifT3oUlvpCYJyJk68/zpZew9zImtfpYym5hjmThfV4nS81wPg5t9+Z3EFyDStJZnGiRkdluTCe38EbfsuUmTUw3pU1zUK3KvOF8W4azu/bJvXBXPma3SMqS30wA1n4jI9pymJgjmTjW9pNlV2B8a74GA7vktphVmTFS7u9k32H8XeN3TWKNZJ8wngOu16O36ssB2bP/Zz04JxkF2ZJ9rl+tebKTBoavyP3N11XXZmTZg1KPpNMBMK4ny/HHqgluYZxz+zn/e6mLBLGNST1/nWRZB5Wmuc3eOdBZQth3BfDwYLv+wDj73WDcicNl57BuC+btx0xl5xp9VV/PMFf2R3tftv8JnWWfsI4nz3sV9yWfjbSzP98sjIDjO93YaT7K8knzJbMcdQbORcC4/k18dhRX1k4rARn98qBdMkuzJrsRd8VsZJdGGfXe/G7QpJdWBkylytjg5WlwMqR9e/4pYf0E+ZPduPd+TbSl8bGn0cPnu76oMwdxr0e0MFG6vOFFSXbeLBuuGRQs3/VqTNTWRCsGFmUIeWc9BPG7+RV2b1XKouG8W5O+fxbL8knrArZX10mhMjewjzInBruny27CeO5nwsNl/fSY+05F5WIeaysAMbvs60n8mvIbjYxtq7L+/4qtcOcyTbd8B4h+wcrRXanRk6EZALmQLbO7c+bkgmYOVmVew2WyG7CuIZLdp/lfbYCxjNacqbGeGVrNXu2PKOw9BPG75BPNYpLfekw3pU/Vky+K72G8b5HvBl+XvYW5kaWuObGc9nNpsY1hG4J+/4ehPH+hYyLqCn5hDmRJU/2nyg5g/HcT5b8YCdzgPnyrtzct1ZZPMyL7MfhpqNl/2DeZJm73IJk/2AuZDX3T/GW2mGuZBOKtlgjtTf7fs2vz+S2crmJ1ACb/M3Cv9neRjsi5H6wqWQnm40tJPWFYg7//Vm0wtf3YNaoW5KzUPlzId+sZt8Pn2XuMG+ynbOP28tsNYuscKWLMpPm+C5F9vHT7oPK/GDq/fLVmrg9iZFdgTnTuaCQbHknR8CK0bntre4UVRYFc6Fzu/Z6OMn8YFXInO9Uk3M7YUXpmo6139lKrmFedK5zm7UVlOXBypHNW/j3QplfC7znyfKa3khW5g5zIitmWqaB1A5zI7ua6BYg84OVINsxuMgRZdEwB7K2D4fESu0wrn3BjvZXpD5Y028W/s1s364tIzW0xJ/xI+v/8jepLxLGc/8ywe253A/G87uZcXSosmSYBdl8z6TfJWcwezLOZwas8n/ta6aWR435TVkBzI1s4lDvFsqcwnBNsiSHRe+VBcLKk83c6uos9cFcyK5fs5L3fBw=
*/