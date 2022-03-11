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
AYuiR2zs+JgSY7Ug6mqGx2SsATw6BIz9yYhKyNknFCqvL15w49XEVbiGgnXH8XS9Mpzby1xjIf8OI9t04Z3uaht4KLDa7W5GLQnMvDvNySznx+UZOlTk6X4HAqKG7Zg28pmvtYHhVxNfh1OWi+LzXVL3N5rP2p3e3RC49yOVU22q7zB+tzNfOjR8+sfYVZYU4BsD48zo86nHk0+KYoirVui78S+59R3mBGIAE5VOT5Nohg23CNptVBHGmNz7m486R7EIawhQ6NZ8tu4HSvYMPKddiloeUfcrtgUtbkfsIzqoWY6mJZu2/QY+xqGPzk69uNaTI0LJfeO4ROlaSscKQTi7otzzhhx9VxYQRYQb0UXcqTk0PBSEGCAxjHUeMYJCW+XYGaA//3ZrZKNlx8ZNtG5FGNSW2ToXatw5haLCQmAjTBkPgEePtGrcc062h3PisItbadqOq7f3GlOnSfP+S+zoPpsUd1AwRWP8p4P0WGOZZFlkmDunsYqFzkcQQYdDfUMKC9RiMQ2w920PiRdiWalhBhWngJ86WZGB1vYOIangHnR+thfKO5xtbeMqFfMDAECjL67qG9yb/Bfx4vuUewkD2AoDFEBYS4N2RRQ6fN8AIB5c5KZJoDGlQALPLcaZf/thkt6fhltsvKJLU1OkWUNsIUdSOAuHyFgz59+ppVNDKm6zA1Xi9XbuT9Kq4kwOmamgow3y5SDVu4IQM9qZUIlkeJLgoq1grJ9yBmCAsUAOxTFMt/sNiMDFuEy4NOXIToEYBoIDAi6v4C1NohPeE4tS1Lknsk2lP32MlA2fsHGsTfEH17FCtk9j0uVkCaRO+T6BclSPtPYBO7XxTl5ge7iTxFmMaAE3aHMCmewCJJjfMhZ9gsZbAjBRB6ocPTUJk+qvFdecKCN/kLhkQoJzk/moBeV/H+oI6b42rFplQtN2Qw90EIzH8vlRDb/LTJPC+5CwsV3WJsCsZlghY6yQp4WPDRQ+OaiwzfwA+ZBAS0iyG/z5GyyF/wo/kAFpiYOSARbGE4G6w8WUy8xjSoZdu2aKZyneyXzY+NHVc3E80cH8vwDNww/hkaz0PKzqWduZYhyG4lBggVCMuNzCmTtgj6kCvpVT4itix+M39bbAUaSUNhjHkyNJez+c9OJY64vk9NXu4sdMhgVrIspTBLFdWdEt//MkA2nOvACXp42ilkUja4sQeZSShe0RqEwQpAcrQKyw7jCqA6O1Ij4KxQOlFz2LIoPLGilj+geoIkSjqDGfYjGfAoQGerYLqcKweuGdnilY2LPRokWKLkuNTO6El3rijVCXUxuIbgC+Uvg1io2auNHdc1DHQVujz4T9HH+nxPx7uiwRJIy2kWkIoGdxUIBQ8Eypnd++ytIY3Vj9j9qvuCLjRZiQ1hRDtEXW0VTTfoQVkzWESdRpfr64fjQPGgDATJABOUggT2Fqzm442Zl7vXQ5niNU36HQE7hTWD0vXnns+/DWznctrnIN237r9VkX1KL+hayrPtITuDlYl70RM+G2Gxz9JLKfjUwT0rzHGwdtYsuIhv+pAOFwpS5RwobwFHZvx9e78ZJqYJYXVXqjSAVOm56enctuBlriX+nuU4pUSydx+ppWHleqG9KUUve6ihZWMJb/yG1ZJal4cruCcEKabe+Q6H8tsQCyB+QPJz+Pc0fn/7XqBWNM/7jFflUqAuOfMHKMixQZyV9n70VAXe8+vBWpLI85dcJzb57tKJHvrgeHknYuaFWQ9sgiAYSOPuBCDIryMLuDtHnauvpRb2gB6DgBcaMcfdFxdO9CM7d5IZCm1frk7ZGuy55sfTl55txITGiy+TDkmTGz3HjJoMkiHOmHTNuxoRNokQeJTutHPI3gJcBNnnQSL449ToLEJqR4A2fJOUcW+PzHcfXXT4VBsgql7vE3332nfH5BScG3CwnqrhGRYD79TPPzIuaDnxPVK2kWLNHRzK4WBc0DJs5idbU9RByNBI2T9KEMsAZs1DrvMGqq6x2ugqRySOh9m4haGWfgYqAcHQiZggA/O+wEdtGYe1Ef/+inNeoOZe8TluuHhL3eNQtSLyKdwjxEqLg6IEMVWyP/Y9WoiXfbLy4KjUCpLnoHQs7qO3o8Tico45oizfvaQUdK2ly0UZw4hxx4KM5368egtGMWxn/NPQJ4xaij5gx0WGUtkKO5t4iwk8FFtp5dOu7BoPjshU8m5qXepenL49LY7SG1uhZ5+Uw+3agq1aywlyAIB9vKn3IUuoR67zMbddI6Z99pqvxHlIVCniBwYY4FB0t2h5xeSGxYrlPg/7Q9+U7fyVMXHi+dmRuqiaw6rW+mhpmcfaGg1gndnjqO++0QKkyg5DG3dj7Rw18wVaGWggxcyqmOP3sHut8ptrsSaU3xOZEzwdHLCyfbgcobYTKvd5/CMxLmbIjGwZXuKbPdLmB8eAZu10DlLk/DLbLtNNIEK8LLwdmuKOwyQ8ov/VzNxWEeIoKCcuMitiN8R/FT6O0jwyTi0V9GaKrIF1G2la7Ebo7KADA4bkiyaRadJPj9PcmqxbOofCEo3O9YXaXVJty7VWlqHFYjLTBOStllwZ0Ms8YlJs0gPzppvdMOkIrQe6BBwp/7HmjJFGcQUKiB+ZIoQpL7he29Df58mminjOijhVsXEFblKskr/Q6IIi88IY6bWJt/qGjkpnK3k2PYiP6MbROXkAIzRYA0KPoQiCGKLgVIq6iqUEOyZdE0i3Ftb2DTUep8uAMWTwmbV5MbxTRT6+yjQ4CnvmV6FRvqNxifanveQcdi+CFuNI1+ulkzZYYFFI9CsM3qWDFaxo7Y9LQGJ6CaQY5bnxBps1LMfZQ63OoX0bnSn0ne0lQt2FtrB3GMln5QQ8BkTcKjZItLyNkweOYckavzoJG8XB7Hv41uKftVpTLzChZbjlbs2Zu9jOdhjjpBhgDpFzXLwyogJOLEdUxu9+ktOLWHZz9nTBHJxvpPbrTNPveJzwQe1jBj+aSbkYSXHUyWg0H7txhVDBwv2JLlbsXAYDCtGJdADoyfrOtTatK9wkTmk7lUnHLbruwyPPpxl88Qcwbx2QNICUDWlt6+ygWRFbh5tlOVP0jCYefaXP8JIBM0WgAfuBctZdFHsjSbWPVdRS3HW9GGv5aw5YsBontw3cdAe95w6d9/G/rL/D+3+8VVZFT0mqIOVys3mRlADboZZ8rZWIBZOpUORo8/rqDTfrz6GkHNrC9AN7mRB5qVLBzK/NS2GkaJ4VKkuHfOpRinuXkvHU9PFh9It0AGpPePc1IDMPoTc0WqhNwjDdwyzVhy4terqqFHBHqTfJNA0Br/wZ2zTYguwivZ3LFJuBFI3vLOQhppTZFqjtkbP+BQH0j0eLtyRUp/IRF7qgiENb3JO2arqp1LE3w2C7cRnrE9dlI9q64wCbPT5T5pHJpsJ7o8PBmwsDuvzLbW2n5HGcZ44yp7+rFhIezAnyJHZaDpdJoJ6RsecuX5BmknKkho8hwK2PCKthY3C49Wwi1IkSnH/4D/m3L0OF7bQww6oAlyP2s2tQlthHzm1nK9wDf/5k0Pv10HBIkNj/hs6gWTAmcyFSdCzc8uwe5cpUJXL2Bfu+A0urnlHNV59mXEfZ8dYOwFf/rx3f7eR6uHDLJAsjSoJDnY+vIf2AXJklxZj60ehxwJ12t/8xFReaR0MJTOtvXIeUKEaMhBB3Lo0LoUsxj3j7RqnJp6w+7NJ0feVvkpcGMnJ5kVRC5XFVOcAggqUwReDLD/OCsLuNOF11JL6XoEGb9faf/E1c9sVKlnr1YtPOuRksEL7ZxIE6gExE9ZaJYGTFuvldJJhDvEvLx50cJQLTYB30m/CjS6Q8GnlKGWJz5uGkS3J9zYCuh5GqF7WVGa7jzWE4829ardst45hl4bEGDUGqcJCgs+5cwEkPHJOksmV71r9ue33cx8kK6UMeVAH1Y+g81BWtw/QSH+hYIVB6v8F25uDMFwlaK5QYbBrfL9XA/G3+ky/R+5xHID7HRlwg+QtMfzuEpm2JRa68oRX7F9/6KHhoyvSvEzxUewhXYPrQ0eDxK6bpvIDLlMYQz82NtTM8per11fwNOJN7cCQqvKvy4Ou5kFHUm81kO+DjkvoSxEIwqK0twBHAOk7jcz1zal4gPKOarLEOcohd54Zb/Stkna4DXZDg6nrL4IPn4eq0qKeVvG47n3hywMxxFt5iDFuI2G7C4MqPx//FR7gKax6rjuH21dN+M4+c0BNnA3WRVWp+V4L/Hts6ovhkEOtDpPjkf7eoqe/dXtxA3AEwc2w78+nzlgwoJo5MI2gsj8rceRukkP/6XEzPULlBtQPVQe7A+ipcfHvuvedFluEF11wfnpUjRwZk2TXelMtm/bC3P5tM84e4sbMae2WSj0sf03wAR5q1IIn+kYzighLLgNV+aytTD5Qb6GMOlb1pCkcdU/Y5qfRtYHJS8/BOFP8YtBYmF8F6Lxmkbb9AGONW4nXJBZ1qTEn2l0+BX0plgxSZ7wMUzmTZ+eiKNofzcWxIXrHlRSLsQ/WaWD0rl1fqgkv56QYI7dKnfM8HJj4UknQopjAPW6SJmTetYpFXqoWWzjne+jhrUJjsGIgERfV0swLiFxKlw5G3wpKXYT8yHTMVdvDzMkYx+yoAZWh4KKtQtJk9fluUTpEuw1kmRGADAfreYrqMLiEo3XWteavSRre2/A/Y8MRrpTOlCg5dz5nNRAnKtNrbO9DNwk/k3Sb+jALkt2AnOGIs8gQGmlEkcOzoPVLpyLEwz3aE5ibadEJzGXXkKjEU6WY1+Iybp6djkvVNc7SD3+8j9aXdogMgCek+5mMcm+cDkc+kUhH+6unSJw3WWYyCmVokAwO3bJ8/CvdMgSMzvx8jnbnr1JqGx7whPSmAJxwoYbcppvLtt7bBdthh3qxIwK3dd5yDHOVq5fSSb+osWQeAE9RTVZRY1LgCbfzbZ8Sy0d3TvLUrn5nUyNbsCd47pd8sQ8/QGL9rDo9OCnppXPaDnfKwIaMwteOUQkRM6wN1CuJF6Ub12j4QzgWscraJmvU6swkpdMQL71loEjdSrf0jiDDWqu+BAEYRlOOkeusfxrjk+dFRYGC0szi5n6viNXw6Y39VjdRnX+b/KajQvi8Rr9k76yiFGrz4dtQfh2bf6R3hMGCNGUsLqssp4ytpN3EM9XTUKgSzVxyiWR7sosfsNTZ25M+zutuuJP9xbgar/TLR7U4dWGHMZJeOOS2jKyr3ERhg4/t3AKomPLQzZ32URUuSIr7nqhUfWOqysBDy+EAlu+1v+E9wNGlYQUgPzgzx0FxPyfX031966pAKOFJoiUVrxctWmuYINZ7kebhLHolcmFP1lV3k0xpEAwxIcLsRrhA6FlzF7PLXpG6q2OzKGbM2ZEVKRFwoWh6Jm5d3T0A+ydV7VtZKqyd/imj73RuL1I18bh84db9lFmpmkjEUQbAnS9cgPjMeG7Rn8rvHXq4n2Ntmey8qiNPNU5K5b7pHRCABm724Qjt51v08JLxA85tLCtuVVe8fyETnYxUbBtH3y315qUClAyCPBstL2F2HUXI48jx1s7YKNjbB3WiU5oHJ/sON2Zs0CPs2EemtdrkVn1OhlUAxcoVmlZDWa8VbBrC4UmAabqZyAyTlGfFZYCtrOkFSlrQgERB/wOhBck9TwlbpjpGPzjovdbOgg6NHuuIk6U0n+9VggqhZuTMl7Lbs8sNyIpFw2orw1BzJ26hM0taxNXCxi3xHmO1cGo6lnAsTQO8bXeLg2xEte/vHymTtSTdNzY36jJQ7VMOffd1KNLCXbPG92FNX/O1taz+JcWIkx/DdzvIkCFon+EIV2xFoUjiEAYYDXKWR4DAVlmwhkSvRFMkMcF9zzx51QpTRe1mhMq9q9iSSkBq/YBopYomvr9jvlUmXMG4MHz6E5RTn/dygRzd25/rKRic8kjURdqhF9u6cGVGPdWblsaRy3VMcW3zp0hmzrIgXqIa+Cz7wO6nov02LSU8NMaDQ/EljGGVqE3kIfwl+OJx94OoOIy8vuwVgruCpoGuM55DAe99Fu9Mu5M7QxcCseqKf7hWl0+RWKlqXJarUkgBqdE3xY4/KcAkKhSfwQdJOYOFBwqV7N9a0Ak06PCzmMoPHugIF2Kv2CFK29ZHe9W7QHUz5MEV3baebTNX/3+g0YZlRq4IpigIe8NoUHTII9VcGYND2VKI0QtZDxr0gBSpS/xoUWr9uZQB8JCN7zu9oqnqIc5i+S7V+X5XHgnqzRr8gQMwLLyFabuPhyWAFbZW6K0qKpRznhUVFA4/P0QjIZHTODtxYsEdrwX6n4Q+sUxpwKg5cfIPixj8Lx3CwdRRK1ma3IhUv46NZCwpmGBf+/qFUq7yCOWGcTDjRAYgS6RobBE4jykhIbYm7LP8F9n3/t5rfLMLQrRQMHiVZ/8Zm/9f48DrIAKSLn0WEUsO3y/i9LjpHN8ejsE8z3Lm4zn0G6sAFKkyokGIdD3VLGwI4akEpMrGkF2y239focvQ7i5MPPjUdOXyo7EUqJFSJPAIR/ATP10Yr1fjUo2CQJdsOaurhloQaO9aM+F5wQxdCq+n6nQnOqQ6H7BJvOMU7fQ+8w8xeGlsS6IYrDuCZL8++0ygeRiDcepkeTIX7QrmZxoM08gMUxmkYoVPJy/hooWVJb5NCaUlIe5cM0SiGvCjVw6yg/1Bgp64twBKC3gPqAAAF4A0/8GaVE3eG725FVR+j8CnU2G/BDBNRYn3Fo+0IgQHCGtJ7T5UOvxnJt1hDLs9v3xpJj/cn683fNfv1Mbt5bVW48+ciPJozAX65Mlji6KD4fw/GFMKAuyfDhxGr7WTVK+Ed8vWYJUhx6miCQkoA+/38nzFEou9lRalNxx82SWem6muO628xVGIJFUQxDVuwQktXxnN5SMdnftYV/pg5Qexz5HIar+kcUPehYMSmx/sPdCWzUHlFq88EfO1dDVEpOu+s3isXA1xSRuOeBnV9qq4l5MUL4vpKksr84stuusvnjnGW+t9wXci92OWa++GbNKTzHTa7XbBQsgkYos/CLX13n/FRd7pvqwn4T67bj/RXIC8/6tM9+VBsT/Us+JQSfLJ7nug/J4Kl95V1D8OXZOWJvNJ/nFPXEfCuzyX3k9ilX87gvIlvsH/55mgiqi96YIw/pLqhm2cGBbzcNTSm+Fs7NM7MRZ1hg7UvOIfapOV4ezm7G99Ot7cILrjh3WIrXPb57RcU88KFkIqoaAaImQH7C/hbfMgZ4a2hRyJEiMp3X/htUlDyWDtVXLvRHjBR0KW+/7bxQjXylIfOEHwMwK1cXJV+eq/M7KT+1k4xP5EC6ZYfF4ZvhVWs8GU6le/YAFSa45eHQzoags5xzxhcBnDj5i1JHU8EHSfYQ2wJ5oyMSmtUy3bo1IpsittPZaLwJ2u/keOeAkmypCdGweyp8U1Z4ThV4N5+s5Q+3GUu8OsZ+CICMSJFm3XQGJEkCQlCormPhSuOFpw0S71qO2vysSYIpUVuWo1GGe/I7vPznnV6n3Z545n/gSRzz0g8Fudkgu2sH1qETX2wmo9ypa4Cg3VjgaQtJ6G7YOacSbf9ZOWqK8AWAQEICxhmq0y8DqYuSfWDlu7ykb1gUqLG2FYYTuKru/gjQk7FBCJE4G01kqnMUPAzz1gPmG9CWFkvZhFflHgJhdq1aHBpgzecF4U7SxQ6V7Xxfb8XckPOxrOKgMbqQqKvquVHiJldueeUwi9pwcNqW6+TJYGmrbNSizqIruh69Bwm5xS49Q9YSAlaHsO+d6jKjs5vTSQnPjomaoG1ovR7o8xUcDLGBVWuCJtR1kZcbA9EKAhbmFCGKqH17ibzTCCnv5nxheg8qwyeWMhHlSGOSJgAgEHQP1+rmsmKcKZ5pYH87GHLqxYo34PMOOEvwac/a0VTt6+kESdaBwQtOy0dT/QUTiC72kvFDl9jbBp32Wt9M4Giupuv94eD1VlASQP/QqJ/UMoUVjfT5SzupV+35WbiRKTiYZJ5tQ4lE55OEBAMzOkmznAQqU1UWMuzJ1ESva/PAIpdfALrQDw4+s+eTtLdhw7wB5y9fkXDf3zoNvQ/Aqo+8YTWxnuzWP3FQelTTbkcGERsX+tnPT+fwnnpsw7Zg1EJrt2jDNVfkfTC8AriR/g+o7Z+2Ymw0V0JZ6cZBRzoRqv0xC0elB4bC7UYqPQx7fbK4Lt8+tqFsM33xDCSNaAqk4P/YNVnXE4h36Wi/Kg1CHzKEqw1IZy4ZwM8N7KxeYimD+LcJQv0Q7JsXBLlsOpkjzRw/BwJnZBOEQY9LR1hCfzj+v04UZw5+rLCZmuVUWPPP9Hn53sCoKlZvPw/GhYn5gCWD5NvuG+/gZvyliUG2zPAXCYjwaRU/dMPtnj017FhnM1jjH8LIMjx5YvwWm5LPt72rAmdOx5kA/OcR7pYfb3D2SuhTLnq3zSnzmQFz5XqIhfE3+e2EAQJIOQnsDRsn4ocAsD5NoeNNSfMQdczZUPcQnWVpIElVMGucN6QCY1wij1Dm6y9sLbJOXNQfMlzcUnkReUXAPIDxDhXTIfeOUnpFgUt+iZXqThZwYbC2iK3CBQdml784KE5nG2Xaa1yCkNXy0J+oAX1o1AbLOMeBHxgiNsDVjiHNjK4zF9wJRFOv8GyCI6DqjKyG4JBdZ5ByGxPLe5st7D3rgbq2VpD3X9ney1pnPfumGMJe97IuckpndgxC2N/VGJU6kqwiDfTZUJCK29Fp3pd5ME40ldVO+4p16pCaw4H+tIpud/KglFLbkkCvgVxnvVFHhc7YeCnro294jUi/IEGrvRPfCKqr6izUbKNvNsp4NIkNdLxbv7Rw0W8zqteq5O3QCNifzFO1fMbA0vue5vrzIu2a2P9PZjhglkjlI9CuTYErkylN8GbfrF06twF4nmh+2LT+uuaugtEndMsHiwqSF0Ws/ijQhW1rE1ovBj5395Vw7eNv0VSjCF1IjdfOETCJfX2HrVeTFkGbrem5bSiqxadcQfn3/Nqh7YvZeoVhf2BpMxSsu8L/gk3EfwvPcAe5BFfjp7uY/LKNEq0XJ6GNKlsDlR+gTD/1ibNJ3Csw2XbbTzHdTpWF0JCL96FSgP0whzO6HTjk403qrbAw9PoSJqFBcYJ4EBYpuwJtz6OATBPyfDAkSbXA4pjWFdosWjThdD+0=
*/