/*!
@file
Forward declares `boost::hana::fuse`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FUSE_HPP
#define BOOST_HANA_FWD_FUSE_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Transform a function taking multiple arguments into a function that
    //! can be called with a compile-time `Foldable`.
    //! @ingroup group-Foldable
    //!
    //!
    //! This function is provided for convenience as a different way of
    //! calling `unpack`. Specifically, `fuse(f)` is a function such that
    //! @code
    //!     fuse(f)(foldable) == unpack(foldable, f)
    //!                       == f(x...)
    //! @endcode
    //! where `x...` are the elements in the foldable. This function is
    //! useful when one wants to create a function that accepts a foldable
    //! which is not known yet.
    //!
    //! @note
    //! This function is not tag-dispatched; customize `unpack` instead.
    //!
    //!
    //! Example
    //! -------
    //! @include example/fuse.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto fuse = [](auto&& f) {
        return [perfect-capture](auto&& xs) -> decltype(auto) {
            return unpack(forwarded(xs), forwarded(f));
        };
    };
#else
    struct fuse_t {
        template <typename F>
        constexpr auto operator()(F&& f) const;
    };

    constexpr fuse_t fuse{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FUSE_HPP

/* fuse.hpp
aWxkY2FyZC5jVVQFAAG2SCRgrVRtb9s4DP6eX8F1wCEJvHjbfbmtu+GyJNsFK5IiSVF0KGAoFl3rYEuGJDcN1v33I+U4L8O2fpkCWxb5kM8jUlHc/32jA314ciThSWjQHCIurfkPU/9jdJI8QvOjqFuanyKJ4RDymPTg6ZBH6IaQZMfyjr+T5CmiW9bGr5gjbxP+JAuFceTIVFur7nIP3VEPXr158xe8gNcvX7+MYCy0wgKWHvUa7V0E72Sw/JOLh4eBw/cRoAdRDHapVrly4EzmN8Ii0HehUtQOJQgHEl1q1ZoWSoPPETJVIIzmlzfT2acINrlKc06yNTW43NSFhFzcI1hMUd03OSphPZiMwim5VM5TwtorowfEjeDRlo5zML0onAFxL1Qh1kQkPOTeV+5tHKe1LUh9LE3q4rTd/iD35X4nNySiFFswlQdvoHYYASMjKI1UGc9UEDJW9bpQLo8OaohKy9hYcFgUnIviFLpGNsJyV56IYVCRYuV5ckY7ptrkpjwBUh05S1ZbTURUBwJJQ2WOoNYSbQCHnbcUu5qGAv+0NQe9EowmMXA2XMJ0eQZr4ZSL4Hq6+nd+tYLr4WIxnK1uYP4RhrMbTvZ5OhtT6xWRWcCHyqIjcguqrAqFcsf5+0bc6TxXOi1q
*/