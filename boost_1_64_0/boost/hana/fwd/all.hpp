/*!
@file
Forward declares `boost::hana::all`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ALL_HPP
#define BOOST_HANA_FWD_ALL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all the keys of the structure are true-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a false-valued key must appear at a finite "index" in order
    //! for this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/all.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto all = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct all_impl : all_impl<S, when<true>> { };

    struct all_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr all_t all{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ALL_HPP

/* all.hpp
gUZS/SVJgOvGqik1pWtT49EfZYh0XjEFtgdi2MembnWbrhrSQLoNFt/3CvPpS3acXDbhc7snKcYj2O7QCeFNse9cSFyAGQDDSA7fm6LRXZtml/+wLEOalhqr5ZaEz2ZnSyozOwRoaOzUB4Ao9lFZ1UdN91Peu2UPYr2YuT5e/TTUKYW6YSZrKdq74QFf1G8CDesl+nK/Jz0o3WTJtv1qSMIDCaCXrc2pIXcQJmZCUaeVY94B962Xs88/cpewP0Ev4CQKYDe61zde+Sm5jS1GNVAq0QCFFCanPJcloKl7rZsInZfXgGlQU4h9kt+OIZnwTbPhTv5zpz4EHhSlBmQ/ycpJBt+5B3tOtfc1fnbpL9JylQI+4nWLlx5pPdsHl/Qg6+0sVfSEHBcNAURYkYWs2IH55YixIBqGS9eqptxe5lxxBQefETB1qw4FAQETF/56daecJvwC+Iz79grXH8HwsDu9wgVCKCd9/xhcdFaYRp5Ra2QF2RfKh8NGCshzQqaHEn40/MDSQcfHqXy80NJUfjStnSk2i6nd4U5Csc6PR7rLthvaBe2yKXVS2Q==
*/