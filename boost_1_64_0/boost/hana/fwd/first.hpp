/*!
@file
Forward declares `boost::hana::first`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_FIRST_HPP
#define BOOST_HANA_FWD_FIRST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the first element of a pair.
    //! @ingroup group-Product
    //!
    //! Note that if the `Product` actually stores the elements it contains,
    //! `hana::first` is required to return a lvalue reference, a lvalue
    //! reference to const or a rvalue reference to the first element, where
    //! the type of reference must match that of the pair passed to `first`.
    //! If the `Product` does not store the elements it contains (i.e. it
    //! generates them on demand), this requirement is dropped.
    //!
    //!
    //! Example
    //! -------
    //! @include example/first.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto first = [](auto&& product) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename P, typename = void>
    struct first_impl : first_impl<P, when<true>> { };

    struct first_t {
        template <typename Pair>
        constexpr decltype(auto) operator()(Pair&& pair) const;
    };

    constexpr first_t first{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_FIRST_HPP

/* first.hpp
3S4b3caUHIvd5pz+aJpsTZIKVybRKBJHWbW1owepfq2IXrUijKP4IodoNe56PJ0lxsrAhMeeJnqaHgCgc3c2MRXQoeZ83aErEhOCvLxfada8+/YJRS/1xk47nbRdGTxLXZo4Y7QsvOJ1P6IafXhs9MkVoNXE9gYevv+HfFU03c++Dq21nNiZqoEQH7PD8berriqcSiPWfpHdIfKY1fr3aLhgWgar8O+fuC3LW0IyDvRg0Ie/esn9cjqxYnQeurjcRNuvw6op45hDcVN+58Z7a/6tLWOZkWMQCuivhAbFFHWwqdQAGS8D+4nypgEyTRVJKoxkOJf/Ifft0hJg8n4tVv8WEWe9SdxyeiihCB9k3mBktDxltnPOEwOmejgcMqIzLOqjTRlX82fuGHbmICDVB/dKEDrpM/bZfCcWzpept48rdd7JdfhmGStMeiG+x4VCQpSP2rPvHdEVeBHVjd9OrBg7Fu4+perBRMoiS38IDKes47TlYp7i2nNmPa9ZSXkzDC9Dtb83f4RV2DvLBb08D7rAk/n5JHArp1ksYjIAGwqAtjc3t/XIWEyiRQ==
*/