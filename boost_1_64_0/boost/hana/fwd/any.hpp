/*!
@file
Forward declares `boost::hana::any`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ANY_HPP
#define BOOST_HANA_FWD_ANY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether any key of the structure is true-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a true-valued key must appear at a finite "index" in order for
    //! this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/any.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto any = [](auto&& xs) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct any_impl : any_impl<S, when<true>> { };

    struct any_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr any_t any{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ANY_HPP

/* any.hpp
cM4CHLw657tqEiCgBCxBF6opy+YuP7k73ImFEtmPGS1zg17j+xwMyqbBaIwipGM/qf8GFHFLVr2NNOjiEvCJdYP7ioqtVNNpWIawBbaBeQ07MIayH3cfsvk0I+sIqaPN3EkywycPqMB7g9R3PckiKVc/rvMtbycs0l1hP71XW2LCV0Xdn85rwQimx1KdJuT8OmVHoDlOdVM8CI9ShNGSXrRnGlM2F3f8pqxk+C5htlM7PCfspFom8/xD9vSQ3d0I4KSA+dybaDFUbtY74Gmj/EFkcS1H4A9GqfLii/LNRmXH/2NhDitRRlU2zWSLMD6i8Hv/FJINrXahBTbUlaI9B/YE7/818JbI7RL/fuzcwUue+/DwouwurW/iprh3hmNqy5OE2601g0k/JR4vLZMP52MjcPsm5PqASzoO51oepoOF16EFTFigljvEFck9OG8Ot8VdFcP3bc+/Zxnko6Avt6NB3IOR1aA/fbHkwdjGAkfvpvb96xfkPLhdsl1iaEskQmOqucBAE2wmyR7i70h7bKVBD4lNd4UYLrTd5eREEcGAg43XJJePGRhFBA==
*/