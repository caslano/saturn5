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
5hCvszMHKKIlsjW79k/fPdyewEqOPdGgpt5W1nNAAjYgOaR40BCn5Vol7q4EGgCITmychg724aPSmO/J3itw3qN8TiClY/+SIxPTgM+S22S2ilNalNTuvFJd2OWA0/aijtiLsglnueIOon+DIJpu9qlUXb/c20L+vuN4zE69bt/zxeJpheTHRRGDu5fnmnoXxMNbJ5+6taO2JcPrzqZB4iM5gPRHRsuvr9b5p+S4agX+hsYru7fn7QjtnC9fQWTFIq5stA0WYrUAtciaPbxBt7nwniixE7OjE3T6t22BPWyzlHVYi3aRG/UFze2gXcwIwVZLWWDk4Gd/pzHYlnlhGxY11hM6I/eErja5GMOqnq3SdI/1Km0Q4/WI2XWLNbJclTeGnVEqW72XdTrFVy6ADHm2FYBrLafxRKYPB6PubwemFkaCwBtXfkjIudV8VS1XVYvQZyk5of4JBnXjD4+eoYU6rW4nqgrkP5V0nSrQFFcwdZ/BAvjMdAN/cigPnz+n4s+HKprNdNorlhiZkVl+vLX9xdfV0fyixmjHaApWr7K8FmXGVTqMuKeI74ndfyuf7/aE7hzj4/uKCB0f9OwkYBHRFa4YtZvIuix3VTN8z9FjbuR3ly9feoyqZ0dZt+bj4h0G5g4hDSBzmPyF
*/