/*!
@file
Defines `boost::hana::members`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MEMBERS_HPP
#define BOOST_HANA_MEMBERS_HPP

#include <boost/hana/fwd/members.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/concept/struct.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Object>
    constexpr auto members_t::operator()(Object&& object) const {
        using S = typename hana::tag_of<Object>::type;
        using Members = BOOST_HANA_DISPATCH_IF(members_impl<S>,
            hana::Struct<S>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::Struct<S>::value,
            "hana::members(object) requires 'object' to be a Struct");
        #endif

        return Members::apply(static_cast<Object&&>(object));
    }
    //! @endcond

    namespace struct_detail {
        template <typename Holder, typename Forward>
        struct members_helper {
            Holder object;
            template <typename Accessor>
            constexpr decltype(auto) operator()(Accessor&& accessor) const {
                return hana::second(static_cast<Accessor&&>(accessor))(
                    static_cast<Forward>(object)
                );
            }
        };
    }

    template <typename S, bool condition>
    struct members_impl<S, when<condition>> : default_ {
        template <typename Object>
        static constexpr auto apply(Object&& object) {
            return hana::transform(hana::accessors<S>(),
                struct_detail::members_helper<Object&, Object&&>{object}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MEMBERS_HPP

/* members.hpp
YipsDQGAU7H8gD4gAE0AfQHVgH6AXQH9AVEuawD2B3dNwGjAWoApgAGAYwEDAVEHUgcwD9x1AR2A9QBdgPUB5wA2AFwMiAK3ArAhPof0G6E/YGPA9eDfBHAzYFNMF7AZ4AnAFoCXAFsC3gBsBXgH8BG8lmYSyANeKQP4KGBrwMcAgwHx+pregHh9TThgW8AEwHaAIwHbA+oB8coaK2BHf74vWdUJcCZgEGApYGfAMsAugGsBHwfcCNgVcCdgCOAFwG6A1wF7At4G5FfcTGaqPoB1AfsCtgDsB9gBsD9gd8AnAAcCDgCMA3wSMB1wEGAWoAbQBBgOWAwYATgDMApwPiBekbMKMAZwA2AsYAXgYMADgPGAZwDxipxrgEMBbwImAN4FTAIMmAJyhPIAmILyAJiK8gA4HOUAcATKAeBopA/QgPwDzMd6BzQhXYDTkC5AH+hAXgP0B8T+rhbgKnAHAm4ArA1YAVgX8AAgdjhnABsDXgNsAngTsBngXcBWuCFsKtQzoBqwK2BXwCcBowEHAaYARgGOBcwHdAD6QEc1A9AfcD5gLcDXAAMBVwHWBtwAWBewArAV4AFMF/AapgN4E9PhHRqkA1gXsBZgC8BAwA6AtQG7A9YFHAjYCjAO8EnAdEAf6PD0GB/QivEBJ2F8wJkYH7AU4wOWYXzAtRgfcCfGh47xBIYHvIThAW9geMA7GB7QfxqEB2wN6AMd
*/