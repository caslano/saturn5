/*!
@file
Forward declares `boost::hana::is_disjoint`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_DISJOINT_HPP
#define BOOST_HANA_FWD_IS_DISJOINT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether two `Searchable`s are disjoint.
    //! @ingroup group-Searchable
    //!
    //! Given two `Searchable`s `xs` and `ys`, `is_disjoint` returns a
    //! `Logical` representing whether the keys in `xs` are disjoint from
    //! the keys in `ys`, i.e. whether both structures have no keys in common.
    //!
    //!
    //! @param xs, ys
    //! Two `Searchable`s to test for disjointness.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_disjoint.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_disjoint = [](auto const& xs, auto const& ys) {
        return tag-dispatched;
    };
#else
    template <typename S1, typename S2, typename = void>
    struct is_disjoint_impl : is_disjoint_impl<S1, S2, when<true>> { };

    struct is_disjoint_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ys) const;
    };

    constexpr is_disjoint_t is_disjoint{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_DISJOINT_HPP

/* is_disjoint.hpp
9Y8X+1X7NRM9AxXZbHXpJuMYyhFFq1rWQqg1wiNOmAfjdTzphj2NvvVxjZNNVXVdDgGDdxFn8pX3QbVjCXUHa+ZNZCtdBgMivcO/hZqtSCto+inPlQfSwlMJWBEFLwqPEdc/eZRIKpS0iipo9V8LskNfjdqE3/GT1ngMADvfVI8CTRZHmsSaGprUne97Q5qXHL0BPuqWjI969x0cChczZIfQ4fOfcQUJfXaX5O0UmBRR9J7rNqJvwCRMKUe6EE3tRCFkjwmJiQtLt5osTMOJ9GE2daPFvoAXGyH7NpskYzLD/NCz1/H2JdAQaJDS6cSNyj7HlbW2y+IZqXuHYM3WGDNAoGMFbGduEbIIr35lfVYMYBcdIen4Mzs0O+ghYJUqFF9CXRMKNY3XwmxYwINnbtHuoe2Z7EEy78PHMAwq8OEwRt26MZxnXP21BYTGRaiu2deEo19tqM/tvA9ZS3wXzr4WUF8jgJyIdkCGW7ZbQXUXHPV1CUQnaltvmb7tceqtR0/rR0g4ThV5trxHzU/NN08Jl/LmoprtkxvZEoeoQCRqw+y+Iqy85CspOtjMjeIlKzgNdfQALjfBlcmwStbKnW3OjOXFPv1u1zXL5zHfN6tsfbndViHD3YPihBUy7TuqwxI0a9TmgvGCam9DjBlOX/c0bAVs6WxTtUpy31w8vqn0jvCsurbdwxwzNRBhSTVnTfiU0Ke88AmhY6Zj
*/