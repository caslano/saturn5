/*!
@file
Forward declares `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DIFFERENCE_HPP
#define BOOST_HANA_FWD_DIFFERENCE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note: This function is documented per datatype/concept only.
    //! @cond
    template <typename S, typename = void>
    struct difference_impl : difference_impl<S, when<true>> { };
    //! @endcond

    struct difference_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&&, Ys&&) const;
    };

    constexpr difference_t difference{};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DIFFERENCE_HPP

/* difference.hpp
5rTX9TsvlndeTO93oXCLhHPLzwE1uAlYxpeokKxcFDECfukaLC1xoyeP42DQ+gxiuLo8UIIWwL8TQq8cvY1hSYalVkWoTLmsuLDw/1GAUpK2K04MA18rxqOL5qC1QyUoPC55IJisuOScol/fNHl906TEnCYlJnP+gvTDTPCYscwKWslMXeSh0r+mbR403qw9xvi36DRW6lXXvqX4Owx1J4qy5+D6XajbSvVVRJXm8hU51zmP+/Pib4aig++gblQ=
*/