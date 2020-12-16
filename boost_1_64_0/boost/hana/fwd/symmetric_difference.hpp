/*!
@file
Forward declares `boost::hana::symmetric_difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP
#define BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct symmetric_difference_impl : symmetric_difference_impl<S, when<true>> { };
    //! @endcond

    struct symmetric_difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr symmetric_difference_t symmetric_difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SYMMETRIC_DIFFERENCE_HPP

/* symmetric_difference.hpp
ROOYygcl/A2VcNP9vfciGEpvDgr/q0bcX8opH1aMuJw1tPP7OTh6uhH7I/46xA/xpRRFE/KkEuEusbhMuvNxi1hcxLS4ohMcdOE4UkKXjCOFIDkfQ2kythxD+UKhCVC9DpUCKvVOQxh3XftCnvUmYf4/l+f/PqtalbQG9CYxh7uYpVY8Bn6B2c6zpMXBAOobT8mQAFt/nSeO6WHe6s1H33z9//eZ/62kHi3W7Uzml5ZJfqmDPgt51aP7rPBZLZ05cK6XzkpNsle0/odyt+pcFl5UUgEa4fWazmL1SC+P1hUT5jqIUWpwWNPAdh3z8VeKvwrgp4niJ5h1yX4oVd57zaNR9nwaT8o0Dj8/7wBpRjSlib9jDupzzjuwXYJ3dzOLObqH47sCYnSfLh5DzJoohl3BZGvkhILJtshxBbcyrc3T5u8MXUgTRulbzGLVgqRskYLxyltAeoOYBBhsUksGEK9KJoZ4HuJyxoMyojBXUliEAZlRC17nqnGSE9v0EDFeyi6gHaFEzz+YwlJeoYYSJzYBpzu14sKVPDhdmhDl0ummmhXjJODh6vmiBLxoKn7d6mQJZxGvKhwA5G1yJzNZFl6La+TxIx0xfUma2iH2/fSCR7gO7Av/bpZLUTVbj3y0gAnv3QRfKSt4+M/YotD5pbgXLuoDNGu0cpNSmzUExLoX5fTvFq7Esv43mUKRwZ9ozTyrVuhSzfjLzOrV6MFXIDjdeIU2VvmzBoMnmQx+c4If7wIQQIg5ZmORny05jpz2iLcZ+/Vp49fi/kjMt8q8e/za60/WVvlixBzQgmCOIbL4a34GCd8akC1V3NwT5s6tPDFuujAoYr0G7WNknXhBfym902b/WQcvb7xm5otH0WByzRwLm77oqXSOeyo4g9DvVE+B1t/scDou99qw6JDIEOF7h0ueuJ56SR349UA+VzbJPoi9Coq+lwwSfpcq2aug2JTw/EmqLGxuXG+A3A2xHeaKvW9D+BHQdqOXTweveVKdXsW3JmLWpeoVGRDHSXYgNw6q2+7Rz6hz90DDm/obuIRhl0h+y+LSea1/DG6CSeDmTUYTvG+SRlbz9ACQkwsjYzI7GASPdSCxaD4pFc8ricd6pNPwXm6ShStvtzydopPFj6CHxjd7p9t/9B1ivVBC5NSgobx1IrDCYBmupo0bfCN1Itpr+H4bvqx4UCeqExmdr3MRMIh8vxH0bOnpqK2TfVSUrja4lFHAiTc3yU5eVCsu22ukFac5jzL2QkMk4S1S9IzFlk6D+eJQYZPRkbJFpF91pIDUmady6U1bHtueSs06vt++8POSBSuifvYguLBQ3OhnjXo/W/JSop/dncqsSmqduGWLYdaBkyZ+6lS9IB4esb/ao0KcQ8UnssgffBrktkqW7G6Rs0XK9aOZW3OJ1WvVKeNwNtKZhywfMulzNickM6gU8bdVBps04PR1AvI01FNbR4oa322y72gx6kgxYQUcBdy20LsAH/GoqtvIIj3lQgoovtdv1DmZt4VNgsmoFUZdmEB9g1BmfR4IMDYvgR1P2JQB2N3/MLAnA0tNqeNxtHLT3wxkikSWUgBlQMVLHVR87lmDJ916gANNFlduV8xoQK8G2PE6XSx6TvKlLoyHZR2JkwRE04NRxRXL1XDWonmQA6ICf/iIMpC6UudMuUst3ZzYZCAAOMFCk6xv2prwc1tl1vEiMhw22lGOWrGNc2TVyjIb8FkSuZ6RqxTSBnUS8Qj8kEm9+IPy1q+Y7PtnPA71Mrh2wcWbLHxRpAjKmhrNh2sWkUrbCJJnUXmi1r4hsNv5TDwUSNU7c7VogO4AsbcoQQEmykhm6EKFDIgLgGStoshxteLu+3Smtvc=
*/