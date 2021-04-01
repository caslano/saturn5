/*!
@file
Forward declares `boost::hana::empty`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_EMPTY_HPP
#define BOOST_HANA_FWD_EMPTY_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of the monadic combination `concat`.
    //! @ingroup group-MonadPlus
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{empty}_M : \emptyset \to M(T) @f$.
    //!
    //! @tparam M
    //! The tag of the monadic structure to return. This must be
    //! a model of the MonadPlus concept.
    //!
    //!
    //! Example
    //! -------
    //! @include example/empty.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto empty = []() {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct empty_impl : empty_impl<M, when<true>> { };

    template <typename M>
    struct empty_t {
        constexpr auto operator()() const;
    };

    template <typename M>
    constexpr empty_t<M> empty{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_EMPTY_HPP

/* empty.hpp
MCiByvyt1rNlEFBE3KxIJ++VUlIgglbzaY08ATaGNYdXvBbKSILFFC8u4wGCv3QqvTFjF8htbi+fByaTZel4zlMRFT8QSv9PPgyWq5zZf+NkuYffjFGMgN1dbE4ZpsTa7QKfII4aCraCF0jaE5Fut1kCovUwTR1jDeZefBvpDl64LyAMFTvOTofP2v2i1tbGz2X2Vc2nLQ0UFguv5548qKeI1mIcYqKUGZKH+Kc47gAPcpwdvRJv+MuBh5dRcJ2lyCzmgOgAbEYyYRGwa40Qd7cx36QLCpQaElXtklyb01CIydhVsoC5uhcYj4Z7HfdktsrrYiIhnushXMR5aeks21Kv5rX0VvOqMWqpQgyOBhtFDuLAJGvB+vYnnHuSnHjCiUxLib2lbeRREEk45stISUWF/T60WA2Un1OKulB6OUP7PGBzIw/BN8qpL1bIJsaJzh859vFvgno4AMFZMTMx5SvLr5Arw7XLx++ceR4g9RtZACEjuUJN+Xu6eBFMeNLKiwReg0gIj2AalI9Syy+ag5+NKs6XJWQEQ/6/tCTehX7BzJNVGhTuVb8g3w==
*/