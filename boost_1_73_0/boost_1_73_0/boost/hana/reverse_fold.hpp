/*!
@file
Defines `boost::hana::reverse_fold`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REVERSE_FOLD_HPP
#define BOOST_HANA_REVERSE_FOLD_HPP

#include <boost/hana/fwd/reverse_fold.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/fold_right.hpp>
#include <boost/hana/functional/flip.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename S, typename F>
    constexpr decltype(auto) reverse_fold_t::operator()(Xs&& xs, S&& s, F&& f) const {
        return hana::fold_right(static_cast<Xs&&>(xs),
                                static_cast<S&&>(s),
                                hana::flip(static_cast<F&&>(f)));
    }

    template <typename Xs, typename F>
    constexpr decltype(auto) reverse_fold_t::operator()(Xs&& xs, F&& f) const {
        return hana::fold_right(static_cast<Xs&&>(xs),
                                hana::flip(static_cast<F&&>(f)));
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REVERSE_FOLD_HPP

/* reverse_fold.hpp
5LElkelVNEfEAsb5p0imOzpFOdsIOBZ6mKpAQFrzo0botgAlfMa9WK7CUIpMDDlM2qAR6X+Hm6BsH65qIH+fa5fyVecewjPU7cpZU6kzbBAaQMi7NnwIAlf84N/namL+RV/SC9ogcc1bvgPfSmFkgNQgPcTvvwV/0O2XLOybXC19jO/w1R9Nh9qW5ljs1GxxlzORF26/OVn9Y6Mobx/UrHps51nPmWL22qYNpnSu3Omk/oBu/f+DqWTN3ouvNun1FEyg8KYBtR5Q4Fkpxx8ZuydubzL5/qvX4/HF4U4uFvB1mq6UIPyCT0RdLKjZyqG+QP6odKEQNgV9TkD/01dpj01+GlrvdKOnQ1Ul97zbLw8OB4wGnQCuQN+hOANUnySPnKxRBVp2aLZCAKBwFTqleFBuAkSZyBtlc8PQnOzHnk8A90n4wl2CWwSlfiOSrJKImVfj19sjp91qZ1GBHxw1tLDNuHdKGwZ+C6S18FZNYtK51qt4hzU8VZA5R9nIxfK1xTB2No3io3H0rnY2kWqKiUPy4RBLjMQ7KlG1LC4XBELNqOR2BZII/jDwK4qPEXNb6qNM2jCsYdsbWQwzqphYjLC+WwgRZ+ebLEM29MPMAlxmnbILtwvG7aJ9zK5xkDMwlxbNrHAVFkCz4KFY
*/