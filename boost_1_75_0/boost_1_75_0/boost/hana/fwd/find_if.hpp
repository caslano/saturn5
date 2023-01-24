/*!
@file
Forward declares `boost::hana::find_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIND_IF_HPP
#define BOOST_HANA_FWD_FIND_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Finds the value associated to the first key satisfying a predicate.
    //! @ingroup group-Searchable
    //!
    //! Given a `Searchable` structure `xs` and a predicate `pred`,
    //! `find_if(xs, pred)` returns `just` the first element whose key
    //! satisfies the predicate, or `nothing` if there is no such element.
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning whether `k` is the key of the element
    //! being searched for. In the current version of the library, the
    //! predicate has to return an `IntegralConstant` holding a value
    //! that can be converted to `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/find_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto find_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct find_if_impl : find_if_impl<S, when<true>> { };

    struct find_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr find_if_t find_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIND_IF_HPP

/* find_if.hpp
Cqol8sJQ2nk76+h9Tm9wps9X1lqEspS6HqCucbua6QyNkEqVoffQ/Iu0eOWtLy/md/1CUFKfwn7oc+FTbnCfyHnff8q5gi+c42MKnSPnrjldzg11upwbcLKYJsq5zsW3MuZW4n+Tf8xdyBVF9Sf+P+W4wuR87I5srANemZwbUUMnTstfs1tqBBlTbiPOdMJ5gHBGfdpMMGQiDzY2i6FmW++m+Kd5sxpURlJlJMmiZmeLyrZUeSoSlV82ryQ7+v0d/wDV75BFEY6NzZuREZU1NttBzVYRtsUtsa1vbPYcNZtM5E7Y2WK63VSpJRymnbS/rfHeP7911Xvwncb4j/qcHkj872zhcyIbm/V8x7+A/7CDLyuvdeQz8VJHcbPYsfVFtfptP+3fIle0dhBw/GNH40blrXnXxI/jeQd2vCZ+wM7bh2XZbYyuLMtuj4S0HGJlDjfiRxtHyaFRkkjntTu4Hg6dx/XQPE8M9UI55YPmcT/6bjr7YIT39fSWOrUZGPu87ZdCGOHeQriririeBq9iZ/17nel80Z3SCg4KI4+95aevErmiCBL42iK+MJZ4eN++6Tyc7ZHOcXZmabW3XSs4KRh4shHnIsI5YABwRhdx3v49iy+2Tg/HtXsWx/XZrNZxmRtxKQnXGqLvwnY+031F+paKOBbO4jgfaQUXzfiZjX5cp5Ar2kR0bdrOfYW1Q+u+YGdjny3UJ4G0xEU3
*/