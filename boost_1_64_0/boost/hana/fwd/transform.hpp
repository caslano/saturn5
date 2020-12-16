/*!
@file
Forward declares `boost::hana::transform`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TRANSFORM_HPP
#define BOOST_HANA_FWD_TRANSFORM_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Map a function over a `Functor`.
    //! @ingroup group-Functor
    //!
    //!
    //! Signature
    //! ---------
    //! Given `F` a Functor, the signature is
    //! \f$
    //!     \mathtt{transform} : F(T) \times (T \to U) \to F(U)
    //! \f$
    //!
    //! @param xs
    //! The structure to map `f` over.
    //!
    //! @param f
    //! A function called as `f(x)` on element(s) `x` of the structure,
    //! and returning a new value to replace `x` in the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/transform.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto transform = [](auto&& xs, auto&& f) {
        return tag-dispatched;
    };
#else
    template <typename Xs, typename = void>
    struct transform_impl : transform_impl<Xs, when<true>> { };

    struct transform_t {
        template <typename Xs, typename F>
        constexpr auto operator()(Xs&& xs, F&& f) const;
    };

    constexpr transform_t transform{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_TRANSFORM_HPP

/* transform.hpp
+bghPJyRheAyzpTO0gACbklldyCgG2MFujuV4y5LxP3HMBmXwBBC/DaV2JRSfjmJ31kQG4exqPIxiyTBgkAd0qvlLVPTTiOkbrB7usw1X95NET/joM7HjkvE/sGhYsP/CzKmg+DpAfEtPWYm3+giTA0C+QdGtlDgyQEWBole5hRtj6UjxiI9sxFHIPUh0wBS33TIDMcS96/iP+84NLHXmwYQ+yc97ncRl/e7it6fOQ5Pb4GeBoJdrvJW8VVl1ToOT/++FJ1+3K7W41uS42dT+QfGb5a7l/hyL5sT/HMK19iUeatv+6wZ2llJXVo8DgVKTXZoOgCxagGa2ou0Cgs+hVqFFZ98rcKGT55W4WAeosJJq5pW4WJOpMKNj1er8CCZR6RFLE8dpEqV0EJHenh0KGTTZpFgu1FrdOEzS2t0UyDKY7m0gtXowXl5tJV3XjNgPCkTiIUyrcCMJzJnvJsJuXRkhhy0mcQbzHg5E8tDaMYuwkwHZiFjmr0NM5q9jZnRZXJjhT4E3E06rhlwRbtl+F5aZIoAuEn61W45jta2vQ2wawovCeYMAwZe03UvBncRQC4NBZfh3Hv7zD1alx7aC/ca3Z3Ni78KHtFi8MujBGjS18MU6rBHh0uNDLDKEKEN0k4kyHTAK4u9mKZpw6RXJXmRpG6auV/3KpKhQoZHvvQImPu1GHkxof1MhoSyGfLoUB5Dk3WokKEGHSplyI26ZAKG8DLdyntiftBzfQqg2yRUQbEBthG4H9LB5eyEbyW4ls7M/UQHXGvA4ExjKAsQhhi7s+GOaQs5MfbIkawOu/PYXcPufHZ72F3E7gC7S+EGZRwdnMao2L5RhAWjtC8qKWFOgzkGdBcSGIDBpJyjC6WAgO4JvKOh4xHJJkCc/ztEtg7VMJSlQx6GcnQowFCeDk1mKF+HQgwV6lADQ0U61MhQKUNrMt/RSWdQ1mXm21TtJuqzxEXKtQm9Ue8s9dpa7j1GV6nPXJvoO83SQ/WcPjBU9ebN7FGkuslmZDSXMlpLRQWIKmB3Nrtr2J3Hbg+7C9k9md2lcEuSZLbEsoJV5RCuzHVR5MfkR6XxcuQJPptIpz0R+Mj9TJokHoQBVIQ1Mmh055AO5hhkG13CK2mT/Uinbb9BcwPciuZZcCual3JXIQYezDt8qKsciN7Kc6PRTe41ukkeiH2Hakr16c3cd99J1JnsHOzmbqPqT3YTSaPsFigKdbRAoi5ll2A3dxamcY22jKkxeoVO5dugci5TqbPNEXQMooP2bJQj06faS9EUkG2q2s6gKcRuVVdrJX3cMdcm1dtanT45JzPIJKLVpfQNDT8qFh9l9CZu++k0U8n2R2Wh5ef9lThevdJ9q0Yv56Fn7ucZhuTvfdQfuGAmVP9iWf361EgtoPrHMqaDK9LoIo0MGl0kpINZyT3Gk9Rik1UrGYMyT5YWbllyuc6oBuHxKbeUMi2tj9sCxU/sShx6s8huXqk3SSCRqWoSVfWKANUkqFFUPhETTpGdLJypql8RlBh5ixVYweBtCqyUjYOaHhU7MAqpPqO9y5sok9aFGk3sjB8hbc6FPHHO28HbkRitc6OlbNNM+yNn5ipa2tDQK+ElN2s09QOjxdTGy80LRSoFVxsvOS+ovVcrDybzQp7U5B5sooUkwsChkHLDM9Gqy0jh2a0HspGYmAM5eDs10cGJ8wBG6GVGHv3z/kYxaCzOe518zDi2UFusa516bekZuUi8zGQtouzWRCe6p/peiZZ4plwU/ab3W/NWL/mscXj//32WflI+eBbpjkK2Ul37aAk0o3DzZO/OIBmxxkxXbNu7sw7uPCySxc69O8M04oq0LVqxGwAxwhUQwxR7H6I=
*/