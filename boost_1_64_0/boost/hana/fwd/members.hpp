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
B82C4DBQkb7cHDiN/QxqEnaAvhXdtjtZwoeQjCeQmxian/czmW8QhTaOqDDBsUquvMVEHPl1y7x0juTT0pA4GJ9xWU6JyEcXIAbq2povFM8iMmMK2E7Tj3kf5HCrSZIeGBa2vrA8Q3b7Ix1NSV7znfCaCvX2t3voGbNtIj1UqT2P/NPVjYmpHlKM3TBuYuAY6bt09dOTbYGncN/yby7GKYQ/lhCZU6myp8GflVfn4h0kbfKTYQgnXMImiMdCJmrjHROEywyNaop6DykxEXqS/g92B5AF0jNeMAn4oM3S+Fo7htuqz1LuMgQb0o3AoLnQBcrttpoRUC9uLenPEr3Zpnh5Zhw6VMqN+M7ZCIvWwJaV1yCM6vE+XFf+o40Dcf8/NvVfFtAJ4FIc98fA5eQd9eiN9dxWfziisM+BxLCFrU96BYkNWrFfUtUNHQsOKshGAV9yKH2rZnQmYReZWxYGAv2CvCbTGPsAM6lOVn/mskzKIu1liTWIYWw94CYHQmvfnNCqR4uTF1E1+5nOEWYnohpqNpXxgZwQ7KnncHtySPbBF5BGgB9y69Olfw==
*/