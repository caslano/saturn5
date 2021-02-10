/*!
@file
Forward declares `boost::hana::members`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MEMBERS_HPP
#define BOOST_HANA_FWD_MEMBERS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Sequence` containing the members of a `Struct`.
    //! @ingroup group-Struct
    //!
    //! Given a `Struct` object, `members` returns a `Sequence` containing
    //! all the members of the `Struct`, in the same order as their respective
    //! accessor appears in the `accessors` sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/members.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto members = [](auto&& object) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct members_impl : members_impl<S, when<true>> { };

    struct members_t {
        template <typename Object>
        constexpr auto operator()(Object&& object) const;
    };

    constexpr members_t members{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MEMBERS_HPP

/* members.hpp
x/M6zWXZig0UJ9m6ME2jLcIdxCmrQCaqpz4zwGuKYI94gJaaisPovKam9MnCfDGsFZSkTn9NEIcrsTHnyRuwmIRyLlUTQLGFa/ESVBsrZP89b9TCpBKLLC6PCM/ma3FS46vxSfMpZ5WhHpeo+AN20YyFSp3Gr5I+y0ICBZTClEzpEhdVA0FIM8kmLCSSfgb30oST7unxGiEFrSELcpsWVg13vgX2hDdTvF9vgwicHUmcfIo1wlYcxpKoi46RPPIML4/Td6G3gZgQ+XajKZcXdMK3q0GQodbtVj75WNV+74AMVUkQ3tC5nU74j+Df55cVod3uGaXsr5zavXdofQ8U1yvWdLgmxHmxRss8h6Wx5LKW7OprvNDxSKVKmZWa5ib1h2o/txqwo63ktdZqrjo4X2egzEuOhncYxwJVFrdOnZKes0NFlKKY0lAMFale7cvmto16qD60k37HPNVpFHKsQwrVGJ6MhDIo1OMCXLJLiZgjQ8zw5SQVCNPTTnf/MAtMG1glx+ipjfarftSU4spTfegG/NhC5h009vGBFSHmzddiUFWmVQ24eC1Lv8VXVestPhclXlFxvKrT/1tKYf4DUEsDBAoAAAAIAC1nSlIZAAfK6gIAAOkFAAAZAAkAY3VybC1tYXN0ZXIvbGli
*/