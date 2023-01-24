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
OUQMyP/xtaLVAsz3zK8VjZihSs0G1Iqa9qkVJPzdKcFrBxReCz53NV5b/mqC17YYkCLTK3UGoMjcNNQBl0qirNASydsrGK5wB5/nF27NlGkO+U3IlHxX3Vv/G5kS/aAXNDNr6IEmDQvu9eskZ93iRZGCulrnAVzbLIIKrjXXOhu0NNzD7NEoBU/QyDyWxTfJuKMfXOURYzjw3mE+36WeN7KCaKSkmbVBsBfyRUrqmA4kNnmVGUGYXVJwL0wyLI4OaoVKVZQvffZqXPToa0SavQyJsAORDsvrzB62n2uhqZQawCr0t1F+n15Vd9/Uig5sUgwACzrhjRR2HVLGwyYhQaRwGy7qnRa89Bpuh3eS9MJxXPz4fCgkfkSbPElx8eMUqWqthVkjz3VdxB0XbBp5rYFIlDVDrwX6mG6NtgzQqvdnfvxL3DudZ0lsKz0rNqKVwl5KFPbSFQtTJZofJ7JEwl20rP+IlvhdKUv8K2RLQWtkoqSRVywpstbMDnl4M3AvMwn0PInThEWAY/I4IfIM7iBtQ8JBFh8KEnz2RVp7KnoHB/nSvbjXhlDyWQTJzedDyFZt4uJDQJs4iqX7c3jZkxZ+N3jExdap4l6KHMjuMNqCgz1enqVRFnx9vMAs6McBXQQUVrPaWFwBEwAdLOLT7gimw2jXD7P0EYA2TCUNt2+KCpOXbkOjNQmfcy65/1FkCiMpL9K28eNP03mJ
*/