/*!
@file
Defines `boost::hana::insert`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_HPP
#define BOOST_HANA_INSERT_HPP

#include <boost/hana/fwd/insert.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Set, typename ...Args>
    constexpr decltype(auto) insert_t::operator()(Set&& set, Args&& ...args) const {
        return insert_impl<typename hana::tag_of<Set>::type>::apply(
            static_cast<Set&&>(set),
            static_cast<Args&&>(args)...
        );
    }
    //! @endcond

    template <typename T, bool condition>
    struct insert_impl<T, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename S>
    struct insert_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename N, typename Element>
        static constexpr auto apply(Xs&& xs, N const& n, Element&& e) {
            return hana::concat(hana::append(hana::take_front(xs, n),
                                             static_cast<Element&&>(e)),
                                hana::drop_front(xs, n));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INSERT_HPP

/* insert.hpp
svCctTQ5SfO1Nz6oxgAqqVurs36DU5C/ZGTkLyHy5Rv6lKSMYt/4jSUJ7YuVFPc2nlrh4pErVC7vYla4lxXO9lV4mbNLuvUXdmtvlVvy1mS3ZrNbs0/rVqF2i74RY0C5Xh7SgkaGdY9AuSdeMh+Ox5oa9iDp1wE+sqvKZHS6MyhNZpNc98iTxhsVlyiVNCuO/F3zMgAUipVEMOsudiq+h2IT9cGeZ/cpWg61wL2rNTSOElhF
*/