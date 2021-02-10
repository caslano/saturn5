/*!
@file
Forward declares `boost::hana::minus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MINUS_HPP
#define BOOST_HANA_FWD_MINUS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Subtract two elements of a group.
    //! @ingroup group-Group
    //!
    //! Specifically, this performs the `Monoid` operation on the first
    //! argument and on the inverse of the second argument, thus being
    //! equivalent to:
    //! @code
    //!     minus(x, y) == plus(x, negate(y))
    //! @endcode
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! The `minus` method is "overloaded" to handle distinct data types
    //! with certain properties. Specifically, `minus` is defined for
    //! _distinct_ data types `A` and `B` such that
    //! 1. `A` and `B` share a common data type `C`, as determined by the
    //!    `common` metafunction
    //! 2. `A`, `B` and `C` are all `Group`s when taken individually
    //! 3. `to<C> : A -> B` and `to<C> : B -> C` are `Group`-embeddings, as
    //!    determined by the `is_embedding` metafunction.
    //!
    //! The definition of `minus` for data types satisfying the above
    //! properties is obtained by setting
    //! @code
    //!     minus(x, y) = minus(to<C>(x), to<C>(y))
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/minus.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto minus = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct minus_impl : minus_impl<T, U, when<true>> { };

    struct minus_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr minus_t minus{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MINUS_HPP

/* minus.hpp
L2F4X2NvbXBpbGVfY2hlY2tfc2l6ZW9mLm00VVQFAAG2SCRgrVd/T+PGFv0/n+I+gbROlTWwfXqtgEX1CwaihiR1kt3SCPk59iQe4Xjc8ZiQ/fQ9M2MnYRfKW6lIKIk999zf9545oI//4F/rgChVqihPj47W67W7zCtXyOVRKRZqHUl2FFVKxCJfvI9knPJHPHgKY7EqeMbCOGXxQ1jyL0ws3FStMqD9s8YBcHw3GI7GvbH5QeT9HnaHt6Ne3w+7N37313Dc+8MfXjmTu5FPsw7d+N6lH4z1V//3SeCZ92PXde/v2wbi0h93g95o0hsOashJyktaRbEUZDwqaSEkqZSRdo3Eggx4VfJ8SbXv9ckO5UKRrHIDZJ+5dCcqiqOcyqoosg2xJyWjrWFKUCbEA/FcCddoMWK05llG8SbOmMFSqRTVMqUT+kD/pp/p5D8U5Qn+N/t+GfmqZNLq4gzaewuK4I6KU+KlwVqIKk86xJVVcpCwBc8Z2ciF/9PevdN2qTRS9BhlFXNpCGS55iVrxAwSW+FXRLog+LKSjBRfMWJSImA8T3gcKR2k/djp72pTwE1RZYmJ19y6mDDF5AqWJO42EzgrOaKBjBhrutZkLRVlmVhTUsFNqAFeBOOyaM4yOP051UlROpO10/CD
*/