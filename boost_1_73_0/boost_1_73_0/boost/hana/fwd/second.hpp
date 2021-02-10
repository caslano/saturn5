/*!
@file
Forward declares `boost::hana::second`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SECOND_HPP
#define BOOST_HANA_FWD_SECOND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the second element of a pair.
    //! @ingroup group-Product
    //!
    //! Note that if the `Product` actually stores the elements it contains,
    //! `hana::second` is required to return a lvalue reference, a lvalue
    //! reference to const or a rvalue reference to the second element, where
    //! the type of reference must match that of the pair passed to `second`.
    //! If the `Product` does not store the elements it contains (i.e. it
    //! generates them on demand), this requirement is dropped.
    //!
    //! Example
    //! -------
    //! @include example/second.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto second = [](auto&& product) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename P, typename = void>
    struct second_impl : second_impl<P, when<true>> { };

    struct second_t {
        template <typename Pair>
        constexpr decltype(auto) operator()(Pair&& pair) const;
    };

    constexpr second_t second{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SECOND_HPP

/* second.hpp
l80zz3imB/dm3DNnusfAubn/+9VXd0tqfVRJPdjey5IFrJJUeqskvVXqVn//qLtf975PvL8G7L8B+UX+pBVOF7N/paPSLDwY/JXw/5FK/yR/erp4mjQ1/hqsJ94afyVrrMZA9PE3+vfBwNPNP6li9P+e0or/HNC/kp/c+57U25/Nvy6yT5dlsra/nmz9+OPL5HGyvbm9uZEcDPMsnSb9Ms0v0sWnjeRvY/aT/3U5/PLlSZH+fSNJy2Q4fcIaOr/MiqSYTcrPw0WakL9Ps1GaF+k4GRbJOC1Gi+yC/CPLk/IyTSbZNE32T04/HB6/3Ug+X2ajS9LG19kyKS5ny+k4uRxep8kiHaXZNW9iPlyUyWxCapO2x1lRkvaWZTbLn5Cu06RMF1cFaYJ2PpwWs2R4PcymwwvSzbBMLstyXvz09OlouZgSzZ+OZ6Pi6aga+pPL8kqM4gPR4Gr4NZnNy6ScJcsi3Uio3EZyNRtnE/ongYL8cL68mGbF5UajCukoHz+dLZIinU5JU6RalhZc5TTpC2Q2qFQyJ9pmJf2jmOUF7enz5exKESQQkkYmy0VOuiEQEJnxjAC8kSzzcbpgsmzQVQ8CTQatxSSNruNklhNNkvt7/eSwfz+5GBZZsZH8fnj+y8n78+T3vbOzvePz
*/