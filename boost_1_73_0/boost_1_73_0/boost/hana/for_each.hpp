/*!
@file
Defines `boost::hana::for_each`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FOR_EACH_HPP
#define BOOST_HANA_FOR_EACH_HPP

#include <boost/hana/fwd/for_each.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr void for_each_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ForEach = BOOST_HANA_DISPATCH_IF(for_each_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::for_each(xs, f) requires 'xs' to be Foldable");
    #endif

        return ForEach::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        template <typename F>
        struct on_each {
            F f;
            template <typename ...Xs>
            constexpr void operator()(Xs&& ...xs) const {
                using Swallow = int[];
                (void)Swallow{0, ((void)(*f)(static_cast<Xs&&>(xs)), 0)...};
            }
        };
    }

    template <typename T, bool condition>
    struct for_each_impl<T, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr void apply(Xs&& xs, F&& f) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            hana::unpack(static_cast<Xs&&>(xs),
                         detail::on_each<decltype(&f)>{&f});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FOR_EACH_HPP

/* for_each.hpp
ZNcvZO27KItQXLG+ixyN00vKqTbUqEGciPe/7O6q5zDfvyl/GN0e5D78r4a/NbztXfxz2n7b6W5L9PGNITbhXAtakdcctjodWyejAbDur1gwvIlQH6NkFUO+AuOenv8aGwrZE/pQCpdVrdLKVjZhPU+go4f44gV9L0fZ7p5tG7DE51XQ9ummM41CUFlh22VFziLCju5Q+xwB5Oaod+q3khiUuLyZjaNolNgSk0dR1XFJ0hproeA55nnKWqMnCpGVGGrelTDYIDMA0YhncrHqDdFnazaSkaEVYviqou1mm8PGA1stf1aJ5E/hQ+V9s8xfxOdIfQOx5hxJ5m/yap+EnxuCzaEfn+Wl++KgAcwxX4hBS2dW+sdhsS/YwksHXWEH330DP9P08blbIXXCyg3ZaDC/3mYnuv6g8wFOc/77NuwDcjwNT88CcDLD0Z426AdEPuU1fYEK88IwDuxdXo/ty1obvHXqUHKobHVfedImw9Y9nHnEbTclOiWYsL6u0c8MfgzQL0PcVUqFGGaKhftl78z/OYhyOGM14wfCp32HN8g6bqKBu7LaNaEl42dbOPGxHAO96WTyLpqGZNkny3bRdcOVFGW2Emet5hLGG+d8RmIWFGuvQarQsA3qVn/U6XVrONnojXQ/MS4Limjo
*/