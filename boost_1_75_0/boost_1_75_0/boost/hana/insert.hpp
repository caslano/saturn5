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
kaO/BrLEIhsLd7QMSOA9g9ZdnneRgmSjQudGb7l069LZjAJGv+qJGAQbWjcSYxT6/YzG5BPQwMTLQeoeKlDzzCIfhZfqERz7o4ilTb5YL98JN08kMJRGlNrTRdnve4CQR6+4AskRPlwrHkK8YCgmkr/Qu8yfnclEEl0EWrpEPFs+b2Zm2zdULrGeSyszoDGMuREXGsgacdFko5TGmI6I26JkMEi0NmowsHqbTiz/SEyd+jOCxc8jcczOE9fKeTfUldCLA0oEVWnxvPFcG74/I8LzK1+nBMFY/cx8ZyOYKgeMP47XY215PWve0WdknfgqF64c/RLCIK5E9XL2NitZzLWIXiZRwXBrajB4llqXPxDc8MHCmiVn/tUfPkWQujSR/+3PxnYolT8XnH4XNoQh9myTbok8zBNacotf4erYV40cfEDj7r2N+pPlqMDz0DfyS3N0/8TL8SnuLZNmUlarNDsO4hYvBBDq567QMwTYE4Iu4PFLYnpd6zEJmYbNaGCsnvFKtjmwYdA//yRzzv4L4ensPiQkS/MHet831Qv6XzijAwtL/Aybn8pKfi7TTPKKud5mtYhPngOjOMWThCazEM2yg53tZKb+AiQs29NG6ixuPiPXHSAnhiqoxt4zG9JwyMLoK/WBlDrWthlyxrAG4A+lEupFE/4yIJwW0jXx9DAVkkIH71EKOE2GB9Ccw+0F/0C3jj/TyepGr3gL
*/