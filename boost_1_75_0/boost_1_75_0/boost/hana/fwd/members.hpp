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
J7DKQzd1OMzcxt+eKMjVCrfhDLsp/oAZUYNeHaXiNauHvB4LajK6WGgdAzaHxZpAGf1aFC4hiRcK/pNiFnWy6YxStJGtYArdn6aRTzxN+/ufgmjIcy60taRzwvBxXvqJa/X7xHG8yUIFtzjQe9gtcmmJLy/QH7YZHpJQ7BwiJxP1O7a59k10OAFjcdjW1ZqOE6yN5vHpLaYq47GjJkz3rDOQ8cwE/F0mga3uxLAb8eW+eNEjp12Fk5l9meDGnLufr3IG3gWtPXRtk1K7ShvegI1fh+KSPQqYh+GNSUYzJXmUszXh4p8HMhmDxbBzAjO65RGf3S3MgnFpLzRpX82G1h1vOOxqksLatjJ96TMrptEgq98DmTKx9kXbjOYZl9VBPKm3NqKGm+eje177YohKX5bMnJ+AejDvIY+axs9XF+N2dlbn62MVTK8p3pLU1zDyjPq7lM8m4UIoeLYVqRKK0FJLPhd0Y4Iq/hkSF8KOZF3pa6W9AZKYZqMN1lTzjMKi7IX6vQm7xL6lI6lFSd0vp7YutNXKbT9gCz+y3hcms1soL5vw57PbEZ30ZDXVMkmiB/b/3rdmj5okRc5A1keiQjJGol3Fbm1GwvfldpgYYnkPYWnOXqhrOnWSFDIe4Jcs9pwXiDPrfSBBmjpotCTa7KDcQps3RVn6lJndM3xJXja7UDjygCfSuvY+PEPwATnDOEuvzTURSLM2ItoL
*/