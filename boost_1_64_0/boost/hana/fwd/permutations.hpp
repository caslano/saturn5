/*!
@file
Forward declares `boost::hana::permutations`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PERMUTATIONS_HPP
#define BOOST_HANA_FWD_PERMUTATIONS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return a sequence of all the permutations of the given sequence.
    //! @ingroup group-Sequence
    //!
    //! Specifically, `permutations(xs)` is a sequence whose elements are
    //! permutations of the original sequence `xs`. The permutations are not
    //! guaranteed to be in any specific order. Also note that the number
    //! of permutations grows very rapidly as the length of the original
    //! sequence increases. The growth rate is `O(length(xs)!)`; with a
    //! sequence `xs` of length only 8, `permutations(xs)` contains over
    //! 40 000 elements!
    //!
    //!
    //! Example
    //! -------
    //! @include example/permutations.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto permutations = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct permutations_impl : permutations_impl<S, when<true>> { };

    struct permutations_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr permutations_t permutations{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PERMUTATIONS_HPP

/* permutations.hpp
Hcx9S/gwIo2hR+VZ8rJck+D63DMLouu0YSxB53ELaGu8ToNf+qqiu1zZn4XpDhFffMitIqwqzo1G+e2Xzryh1qqJ7sq+UUN/74fnJ7wQMtfZhImn3kJKHRszuqRby8iqmg8YNWVJHM4cFT6OUL4arYH+9TSxoPHJCFJavoYtJ0dJWj9OOEFn6QVMCw2+JXU8rIFGqaf2qAn3YG4oSAJ6ARbaFQeCc7tJOcAaqVGWoR2XDY3m5rsxWNzuk04wv6pI2rp4eSRI80fJ+9YjiHzEbazZPKczHRY/SYojM2GZi20KWp+xi/4Zwypa5sALGY79IJeGr0o8BtNQxMCK7qt+3XPY4Snf+6pEcO3RTZiBrI6xY/YcVvzkTEq1wB3A6/0VRMlll896dwskHaIk5ZyNgF0/YBjQxZg7pwluS1l7ewc9n5DLcRF0PqxTXncGMej8C29QkzQlPbslDiYtWOigAsh+hvp6csHwcd5l0CAP4m05PfH7B7YXCpQtVT49TkRuhxN2Iy8CPlAq17nFCBm81ZSCoE6To2TvYyDBiYHcNsHChv0QUdJZx6wDFQ==
*/