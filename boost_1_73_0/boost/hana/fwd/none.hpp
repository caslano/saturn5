/*!
@file
Forward declares `boost::hana::none`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NONE_HPP
#define BOOST_HANA_FWD_NONE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all of the keys of the structure are false-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a true-valued key must appear at a finite "index" in order
    //! for this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/none.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto none = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct none_impl : none_impl<S, when<true>> { };

    struct none_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr none_t none{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NONE_HPP

/* none.hpp
83uFs0VAH9bEJPUr2HwB7h2382Rjp3sCw1Q0H637TH5vigiJP7iTsMuExL8WECdIknElMzYE/YjEjHCxCulakudJ1zodpH9vJY6T/ue5nSlrnuySUf2EMAt5Z0f1ePqxx+1HCfHzCbcfNUxr4e0Sire/XAaUVD9h2cRSdQGXYwgG9VK1SFydMomyrVEun3R6gLRzR7ELl36ZDuAsP/tEADl9JF+ubd6FCk7+rafKlRJzcq5b
*/