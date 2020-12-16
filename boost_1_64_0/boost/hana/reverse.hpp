/*!
@file
Defines `boost::hana::reverse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REVERSE_HPP
#define BOOST_HANA_REVERSE_HPP

#include <boost/hana/fwd/reverse.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto reverse_t::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Reverse = BOOST_HANA_DISPATCH_IF(reverse_impl<S>,
            hana::Sequence<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::reverse(xs) requires 'xs' to be a Sequence");
    #endif

        return Reverse::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename S, bool condition>
    struct reverse_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...i>
        static constexpr auto reverse_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<sizeof...(i) - i - 1>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return reverse_helper(static_cast<Xs&&>(xs), std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REVERSE_HPP

/* reverse.hpp
LgqjSzYdn8GdN2KJLCYZkbbDsIqrUpXcMReLEdmn6JNsCGWyd762cVVf9f/lHTOMEyNr9O/ZPJSus0XXVuyW47ezhY9TOmN5ZXug8GR4n0j9ujyl7Vin2raz3IaVnw/FwiZiVdEyMAZV0drayJreUeFFcCvhmOLQRsDaVHed2eJICUul5SZ+2YsymWrD44x+Dc7PCx/xZQB1YWXRh3sMZ/w3UH46WZQGsERj2mUjniYINyfgkB9oUaYq3PJdQNbxaShP3SXSJLusYL4Z09A2tDAnEy+0Cz0pdB9khU9d/8C1hGfj/S8BfsXeN3ggwXR2WZ9+bu3YsATwnP3UlSGdrhvqx/2B7M1cCOUxD4IlxF2EXE7f+xJpbjzzHXTMtSiaHj4fGw74qAtKtNd7Z3bWdZpbH85ncg5B7qa0v/nAiG/VmEqxc5NTEFIn8sX3Lkq71JTGOttWEG5hb3J6dWcd25zm/aU/SG1/VG1rBTs5g2WT2whdntId1QXsvyDmn93b28npDmX8KuFKXrnSx+bP/T1+eqlpPL8Nf1NZ3536gpC8vW3A34Y8xPu8ZBYHMMWU30llX53HCdzb3p/GsfvHhfTWFJ3gV4K0mJ648E3i0t87kG4lwG/6b5Ni8B9MCy6cuzsQnxX5Hvo3tGvrO3tngQZjGh5MG3T8K5sgqWzC3Eux+v8N/R7MKf8smWhvfgAtPKrBk8Y2uJ0+Ctt82wP5wrPL2e3JHhm3O/072nVYXJtT2qP/jnZjx78e4He7+wG0m9vbD9vfWVhJdArpwJ9z2dkT4SXRvxBOQlg0xAe92J+VsHms7Hvgb3wDWNhL6YOd08owu9BP6PBlFiB/dQdaFzAxKD7jjbL10ZhOaOMVnuvnZ2NZ3zKjlbJ2qiuAVt5fJlrECT1CaXnDdOdExws1PaOpI20ex2kArj0Hxi0DHP3O+rmM94Mz3hXz8aMr2df/D+9tj21EYztT3sdV4WrF2yLpSejxA3He0v6Z70UtqLbLRjB4DRrZK2Z0vBIFiAvc78s53fNyOtOZplOWwTDkdC/K9ywLR67RPYMA+DndSzO6vq+ckz6SOWzuGd3LM7raB1gH8YTB5TK/g7w6GyMOtVagSwqa3ER6HOOrIS36D7q2Aeqxfw96lOIo5364Iz7c8brrmmYOn7UgbFI+NP5Sxsewpqt43Que+EStUT5Fgs0g5I3isvw9Ww8O5HpTdgylFJSr7pvOog+N8QhbXvTazMqtEVAwn7nhSriacDrh7Ex8j2R8O1Y2pXKFbf8nvlte0wvmfBQr/0P5mMvWqEZIMuYYJM+F3feAMT+f8dFMNlw5Y+UcPvHooYxyHLNnZn2tmTCFUHUhKC8E4M9ctiJzeJPo0/34QyM/YCPapnbFbLtQfQD78UzjjqG/COW3WBZF2TamDHHFEGN3Od0Dsn5UTNha1sYR3a6NtkhQOCTRsAR7gFEe5sIjgOlG4rnw4dwvoatsCTPsYJ4YNGI1wppin9D+73DGs2EdXJZhvZC9dgAdJza6kJiPUGofo7y4YGXVVG1N50EIOIYAUxtTW+eR6n/K82zGUzJR9bzTRTefJ6pXxkzDGXDfNMcynhWrYLYKIVrSZxjEu8FE3YAA3YicO1pXGGubPTDNt4yvtw3sC1Hrcma+/TuO0493nJEz8cKIN9ddW/PKjHnjufhf8F5O+9ZH8jci2zSirbpmdl7tpz14GydavlZ4OmtuS3netSwMVy2whibmZ9IdMzpRuKI1VcdgsuVn0hFKd1zWSveFcox6L+xgzHxKe5GR1hpVagZTYxZfklHao13htJNtQGgzoOLM21pnbW1K7TpuOAO6nKfJeFa2dZWFfcLLdDMy10k=
*/