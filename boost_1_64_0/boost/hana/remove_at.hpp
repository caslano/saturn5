/*!
@file
Defines `boost::hana::remove_at` and `boost::hana::remove_at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_AT_HPP
#define BOOST_HANA_REMOVE_AT_HPP

#include <boost/hana/fwd/remove_at.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto remove_at_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using RemoveAt = BOOST_HANA_DISPATCH_IF(remove_at_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::remove_at(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::remove_at(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::remove_at(xs, n) requires 'n' to be non-negative");

        return RemoveAt::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename S, bool condition>
    struct remove_at_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...before, std::size_t ...after>
        static constexpr auto
        remove_at_helper(Xs&& xs, std::index_sequence<before...>,
                                  std::index_sequence<after...>)
        {
            return hana::make<S>(
                hana::at_c<before>(static_cast<Xs&&>(xs))...,
                hana::at_c<after + sizeof...(before) + 1>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            static_assert(n < len,
            "hana::remove_at(xs, n) requires 'n' to be in the bounds of the sequence");
            return remove_at_helper(static_cast<Xs&&>(xs),
                                    std::make_index_sequence<n>{},
                                    std::make_index_sequence<len - n - 1>{});
        }
    };

    template <std::size_t n>
    struct remove_at_c_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const
        { return hana::remove_at(static_cast<Xs&&>(xs), hana::size_c<n>); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_AT_HPP

/* remove_at.hpp
CGW6wQzp1PYEa0UbhtTPx96J6kRNXYNGxjm2v3dmCfU3GMfnnvTbhvsXXBq1S/uxd1FaPe2RIWI8/fucVEtEo05tGn6Yr9XG32wsZzDzcPnsqlTvaHyNVp32cTbvu7q7sU3RfMKFC5dS7MA+rvkLI3u6Svvd1LKTUCoJBHDZp/sqbfPSO+lYlX2lPFopOw9KQLwn49qjdQnOGlN1sisVvZ/7gjAZAcrodJiMsBzgHreaxZd+cNZmzSqrXKOD5wDXyyFyNobe3z43hDlamkBmk7/NvOuemW9H4ZQVBZuA2Wpuz3Y+q88yBbfTGg46sInxA7sbFh0sIjLmk2j7msfsy/j0TPnIE7zusf+wFJAHtHjEBs/Ns/fK53Vvm1o1AFkF7zMbwwZ5t921LbzHYj9oOS6ZNY5rYyq8S0Z8wKhXRXZ+MJeJPfDbLozupJXHvdI16/fPnUpq+7VVEJ7jO9zGJIZ6Cpyzu/Xlv5f7Lje1qarKDrjNmaX7JMb7C2vHg6PubngbNzIXGeV1Uadgfyrb1q8fYDPJz586q7dlTSWV0NyhPPDvqw714n5MeVkPFe+BQoUXDsC4YSXE8E62gej/ndWvWaPqzke0m561sRiIBuH6AeITarwfNvQ73aGZ9XIkdHMqR3Ypb+cS0/s1rKrTZ3cXujulu+zX8F0imJdU4d0+PvSteJhxgEo5vbCe7lT3DfdtWzYre+f3FgPgCOJmfOub6S4ugneqf5rTYIoDWZvpzvbk/J3j1Co8hQCTvcTjeZiPmC4DdAPwiHdIkIvm0/jOLRDsiV/ndACGEPQDa6mu38/Nh+YQnJrrfWtMM1gspPyX/GCcD8YPAOuS2vrXmTrCAMMVJuAwIN3Cd2foHkLpEJskp4vTa8OP8lpq0y2xzYSGYNFcD3nQNgW7krV0p7/J/PZgfQCws5rmxMt/gG8+XoLw1h84Pq+d5sHhPJv/xmk+Xzaz+W8N+WuLGyvIw1/kMf9dP0h6ljw/te0pX6P1h+9/KpW99Jcxz0d2SaYoONYfG7WdAJis41xE/kgTN+yAHIS8fj2iI29jW4nXZ/L64PX0Liure3u7K6cg1IYWOFe+dDCdX5U4Nt/I6KLhyfp5bFP59bz/YCSz641I9rf2EEtEjcYIKot0sVEEy+UC1jeijQ2ja/OJgW/vQVHCxIrbK7btyV/N87fCsbKy7jFy07f91Fc8zRC0KSK04Bj9Etty37uCId3JNFIrW95ObWEv8XCLXj8WnmTDB4Oke6c2Hrko5MFHCms6KddwnR3+KujOvG1bNr2n+c/8Cs2H6R3zUff2fcgPe3a43y+ncudR9+Zf42A+Dxzwm/z5B2MdGmkC3CH8OCNm0Kwej6IQ3S/RHZ+t0yGg2cLC/VAP/r1cfuGuhVttWzK+SkOWD/sEHmC5GutOSYYzmR6+crJuRVkwPH3WRj5VlB7ohGh8iIsmSJpTOOPJGMvv0Pfzt9JG6dJDo4TnphW8Pmd1HYYytK620A2IODI+sGKpcV0vrfN3Z6fqUuqCRZgiGrejwHtSnfv7ub7lRQmV6q0oMT1kc/vUKpjnD1yG8B/RR49N/bqO5P00pXKtaDsv/MyMTqqb0TK881jyXVmKNr0HG7Cww7vvWCYide9QPjAteNfz1pX4LYmu4OFN0hVkdXMmjW2ldY5R7Ss6AIIEGb1lJme9gHqEeR59eu/PeLVMlKppuWnYxt5gKjCZSlGrAcsVUBBzV/zAUCWZ9BEjXwnFRa+VYQjzl5S08y3ym/Q2l80jy6q60kILwarB5BUt0yQ/CAvnSJ/0tlkfFSvLRlkhXc4rehoNvYorj7AmPhGHfzDShwUvU4O2AJRtO20RR7zprHw=
*/