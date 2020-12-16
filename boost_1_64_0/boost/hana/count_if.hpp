/*!
@file
Defines `boost::hana::count_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_COUNT_IF_HPP
#define BOOST_HANA_COUNT_IF_HPP

#include <boost/hana/fwd/count_if.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto count_if_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using CountIf = BOOST_HANA_DISPATCH_IF(count_if_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::count_if(xs, pred) requires 'xs' to be Foldable");
    #endif

        return CountIf::apply(static_cast<Xs&&>(xs),
                              static_cast<Pred&&>(pred));
    }
    //! @endcond

    namespace detail {
        template <typename Pred>
        struct count_pred {
            Pred pred;
            template <typename ...Xs, typename = typename std::enable_if<
                detail::fast_and<
                    Constant<decltype((*pred)(std::declval<Xs&&>()))>::value...
                >::value
            >::type>
            constexpr auto operator()(Xs&& ...xs) const {
                constexpr bool results[] = {false, // <-- avoid empty array
                    static_cast<bool>(hana::value<decltype((*pred)(static_cast<Xs&&>(xs)))>())...
                };
                constexpr std::size_t total = detail::count(
                    results, results + sizeof(results), true
                );
                return hana::size_c<total>;
            }

            template <typename ...Xs, typename = void, typename = typename std::enable_if<
                !detail::fast_and<
                    Constant<decltype((*pred)(std::declval<Xs&&>()))>::value...
                >::value
            >::type>
            constexpr auto operator()(Xs&& ...xs) const {
                std::size_t total = 0;
                using Swallow = std::size_t[];
                (void)Swallow{0, ((*pred)(static_cast<Xs&&>(xs)) ? ++total : 0)...};
                return total;
            }
        };
    }

    template <typename T, bool condition>
    struct count_if_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr decltype(auto) apply(Xs&& xs, Pred&& pred) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            return hana::unpack(static_cast<Xs&&>(xs),
                detail::count_pred<decltype(&pred)>{&pred}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_COUNT_IF_HPP

/* count_if.hpp
uoDmNX4GGnRUWnAQOBQcTvs1VNL+DJ72ZvBP1dD+DI69Gdz3ZVjqI/dmaH5fhp7Ix+M3I5rYk6HCx31PhqE43nVPhiSEG+/LsIN1cAwGg8FgMBiM/zna4/1/g9FsseZgJZxhMdusFhO9/v+P1v1yjb66W8M7AGGNv/FPa3T6xr/r6rxxdVrlCzBTrbc0XUSvdWu23nOrvlpb9Eni2ia/WQ/QN+vdfQGc66sEI68/GAwGg8FgMBgMBoNxctAe/v9G8w3K6b6t1v2Puuz7F9KE//9y2F1z6+y2+bxMS77J4Lr8R22yrBZzTuv3/Vuj1v6TpvepPydkWfSuVwJfzqw6GOh8DwBltv49gGLWATAYDAaDwWAwGAwG4ySgPdb/U7FydyoA2mD9f/WJ7/8j3g4Nvf+/8/iJ7/8769HKdf9Pat1vu9+n4roXf02JvWnJ2R0+XXKjc91PZaEOTaz7g11s/hqwltb9B3jdz2AwGAwGg8FgMBiMkwhfyMS2Xv+bbNht3/CP3/WXa/+zIu11DJvK62cGg8FgMBgMBoPBYDD+Ltpj/78s8w1wvTfocvVWfY4R+egy9WYDVvRt5A/wLPwBkskfIK7l+wB4rFZrvwt46plqb7wE3a63di/as3a29Y1nMwO+admeAOQf4PQLmMx6DQaDwWAwGAwGg8Fg/AtoD/t/jt6WabRa28T+Pwxr/f601k9o4t3/X2Mavv1H5WL/8ou0dTFyDa7TTVVb/8n38YdrL/dypPVB3iO0/i1Y94cLrUon8xvj5czPqQ+Ih5iUPqB21ae7SsP2hS/d+qQ2eugd73naK79l3xHsSnqCcNo/IAIs67Ec+oKdrDNgMBgMBoPBYDAYDEYr0R7v/5uNM9p0/7/0v/n9f0c9WmvfX6bW8xPL7ourO/7b1ssOF9U+Unb0gpat27W0bg+ldXsXsvOHTOM1O4PBYDAYDAaDwWAwTh58IVPaeP1vy7Qa9Qb71/Dbag9Ao8s3AMJaoQNwq4vSBrROF7BL6QLmRUxZd72t7/NHO4x8Z0ll7jUt0wUEkC4gkHQBQaQLMLAugMFgMBgMBoPBYDAY/zLaw/5vM2eYjHpzfm4brP1Dhb92H2qXcs34q1PH6hKVLR9x5VGIS03RJQ5PSrpkeOIVupHJ40aPHZPs+L0Q/vpN/KwbN1AofcID0CdcQvqEXC/nN/sUOtAeAtX0TQFdHlrtupOArTDXiPBUS/O6hM5isHYvfS8gJLZBt1CLiA1dpW5hU9KcwT9dMCT52Ko+URXaTuVCLAqT8dmLPrlFv6//7/ccNZYm7T93pBC/dZHxG3c989w983Ujpn9RetnO+qhvhdgUKuPnjv7ghe+7RCx7r8OAiI3dHkL7j5wq4xOuj3nWkPxgSfTbbw7Ydu1LNvR+hIzP7zgwePx6Q/VDZWUTVm6ccjV8FvrJ+JLLIwusKceP7UgxZ7/xW+EiIbbHyvizFg9d/9UVaw5H/N7xieNVd5wuxECVvzb149JJfVO6mXtvHDN80NfZ6JO+Mn7xrVfXru22YGH8y7plAdkXfoA+Ve1dXXc4o7CPxjxsxIoB+9//sV6IdBX/7o1+0/yWleyf8ODKec+s3JYGXYrK//Syvctj9miOv50yY9eMXun5+Iaiij9/zvAjn35Td1F5t9UHt8eU+gsxU5V7f0XUd/sqeiyc3OvecxMSfqiFvkWlvzQ5o/vetCP9Oub23FN0bu3rQryu4p94YOrY1b4/frb+sb5/LCm+/TEhVqh8xkfPrzIUHVk/q3h0l+qo3+uEyFT98MGsD9/54+g9Rwrn945YtWASPgLxuOrPWGNZdu+U9/quuO7tD4Ke3H2hEOdHqv5Pr7nr6QE=
*/