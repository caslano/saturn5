/*!
@file
Forward declares `boost::hana::comparing`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_COMPARING_HPP
#define BOOST_HANA_FWD_COMPARING_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a function performing `equal` after applying a transformation
    //! to both arguments.
    //! @ingroup group-Comparable
    //!
    //! `comparing` creates an equivalence relation based on the result of
    //! applying a function to some objects, which is especially useful in
    //! conjunction with algorithms that accept a custom predicate that must
    //! represent an equivalence relation.
    //!
    //! Specifically, `comparing` is such that
    //! @code
    //!     comparing(f) == equal ^on^ f
    //! @endcode
    //! or, equivalently,
    //! @code
    //!     comparing(f)(x, y) == equal(f(x), f(y))
    //! @endcode
    //!
    //! @note
    //! This is not a tag-dispatched method (hence it can't be customized),
    //! but just a convenience function provided with the `Comparable` concept.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and a Comparable `B`, the signature is
    //! @f$ \mathtt{comparing} : (A \to B) \to (A \times A \to Bool) @f$.
    //!
    //!
    //! Example
    //! -------
    //! @include example/comparing.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto comparing = [](auto&& f) {
        return [perfect-capture](auto&& x, auto&& y) {
            return equal(f(forwarded(x)), f(forwarded(y)));
        };
    };
#else
    struct comparing_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    constexpr comparing_t comparing{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_COMPARING_HPP

/* comparing.hpp
2OMP+OtgUZ2VF6vlWaGEBlWbKU+ENpYGJud/6MXOhWHCva7cq/MEvQwgVoh94Z4p4zCO4K/rw0KbvbAvllGCHrXwCdJjLL0Fw7JkngIElHdRMXhXBlHEMH9ZknpgkSEqWEQaiG1njcbGVqCiUDUj05nxcfPmeAB6I0YHHTOEclQ88t3A+dt4JfZrIAbTrgzTgWsk7naM8QN7ayb2Pclzk3JrFhn3aDDcRTJcEmyi/cWMONlooL82nd7BpQz9LxKtKHQ0kWbOhe4rvOfEZX3L8qcJbIaXOt7lAs4C6WIGrFafqoR9m0DyY2rDCCZnDIkMHld3mdKikg1rclvn4Zoamd+10MxrCkz/UQ+cebYyOVq/1JY7QbTo73KZSqR8GnQexxBEgPz7LImVcwQrnLpFVMnxRYwuYu6wxK6vs+ZK0GQKygL7AProUaTjoF/aTt9c3aQHsKY3N5GI7gYPWsqg10GJjf8yevc7TVC4N4V3r6bj9zaeOqsPxynLP+ncYsnsnzwspoTeOpprlGBTcGqF5ORrSCD9Hvf+Fj5GbJZPJIHwcUeJB4mYZRSZVA==
*/