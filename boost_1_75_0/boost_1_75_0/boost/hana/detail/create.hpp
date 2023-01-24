/*!
@file
Defines `boost::hana::detail::create`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_CREATE_HPP
#define BOOST_HANA_DETAIL_CREATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Implementation of the generic `std::make_xxx` pattern for arbitrary
    //! `xxx`s.
    template <template <typename ...> class T>
    struct create {
        template <typename ...X>
        constexpr T<typename detail::decay<X>::type...>
        operator()(X&& ...x) const {
            return T<typename detail::decay<X>::type...>{
                static_cast<X&&>(x)...
            };
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_CREATE_HPP

/* create.hpp
w9gGNAssE7rOC4Gk0Nf0gt9ZSJ/+3SGMhXz18V3YgGcbDiy0e0ctdHnNC+/3Ji/cyKc1OOVwUm2NrOO2BevauLoRekqH392FlQQ2AhS4bfYLwEvIUHMoQ/3HXQoFoGWROmOUZn30Lm2z/gsEEaIplTMePJGC+Rk7t5x3pet0T4yEnKeoOYdfeacAgP9i3pjVsUI1q7dray7ovIb+Ew32QeiTY5HAtlnUtVEZruwXUpIxkgYfQFMKFn+x2XbOu772CVnHJ9xpO8f/Az4LFERnbjn/eliWH58DNFXOO0LbGPO439t71dpsNnuSw9M8SeHJLHKNyWMOX5V1TpxsDYibTZBoeyB8vcdQGp4p8z1+LF4qdkkfcXg2QAvJGcnWg9aVaSTcQR16/EH7ToelvgfikiZhJM4xLbi81kmWAkOclJKgduVsDBR9OdTrRae4dz5VSBaiBeRUyOPTVSySx4xmk+bvVGzL/K2cFEXx4Ktnzuotzci/5bYjniyor8h31yeWwhcuEraDEnRY+m/Mg7SXi0XRcuEcCKD7QO+FN5BAa9gbiKDb2BvIoPkjkLM92auBaxui9TUyZMYXkmrqjOIAeSJdcq7CZbIAbkyOF6Kl3nRyHtfK1pdjOUVRa6AhGp5CDlCRNJUVLtacJOcRg4YaaBmR7yR8N8xRGjo92aK9SwiaS0WnhAhf7XpDXwaZhQriSNs+8P4d4nuyS61t
*/