/*!
@file
Forward declares `boost::hana::one`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ONE_HPP
#define BOOST_HANA_FWD_ONE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of the `Ring` multiplication.
    //! @ingroup group-Ring
    //!
    //! @tparam R
    //! The tag (must be a model of `Ring`) of the returned identity.
    //!
    //!
    //! Example
    //! -------
    //! @include example/one.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename R>
    constexpr auto one = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename R, typename = void>
    struct one_impl : one_impl<R, when<true>> { };

    template <typename R>
    struct one_t {
        constexpr decltype(auto) operator()() const;
    };

    template <typename R>
    constexpr one_t<R> one{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ONE_HPP

/* one.hpp
OYHeYlI9cRy1tNDWiJTS6ocX1V+pPksfZJ4rbzBMLp9J60xoX+/gW1qjCf/nDP/mGHztORWnLcETR89X0T8UlYwPnjSZN3umh8sdwf7aQ6pUv3jqfaYuToIHLnBDMqZPNOv0ipJMOXOpci3dFnQEegp/nbTkplSUd262VzuA+lfae/H9q7+cgOd56vyeKI21SXIFy4VjvJdu06fZcLQuXjPxZR98ccLtRLUf7VRW5CxUs1/gVEWveUDY+a8YCCNOJNUA3LhlK4UNaIigb8FKqC1GMV5x7VtMJjQoTy90DK5yBq3hKocykWL2TiqBePoTSoVpxcILA/myoMu4oE9ell1yAs7AoZmf/WGq23n3098xyCSv7Hw8MERSlCwqnO9BI99JyLd0m7wnm2/Efv11yvoAg9kH+1h4BIWni2nvGFPKqj4kQAbAtv2sMgFc9xGQb6g26QxlZa1CDpGqC5pVOSfg5zp4xTtbpDili+WLAhfF4+0oo1rLLdQc5mdx5TqjnIX3BsbJxFM48Z82ycQVSOznpHl3m1U6n12RIKCqnEmVx4WrnB7My6gyXUHiDJYpXUTkl6hJoSsX6YJ5Xgax/kNV2ukQsVMHl7srJwfmcbGYRdEEqgidVs7PnQqsKAAgohm+GUhDhGO6fbdd0W2QFkKZ8aQ7ZZPBI02/IKoEZdwcjuuq4pp/jipfKbrcTJSQsiGM1PE4+7hRpR0jmzDwQdWEdI1EdTzOnjATn6CPsIUGRStBkLOl6GocYTPnqGFqIBg+KUiF9tVuQVg8EqRR1tlY6KQsLLY5mnjFLzJlLJ+ZFjyGtNy4fvDGu7IfIGmWEK+z2M4zL+tGgkeNBK/9732M8QSn6IauwpX5jtA8e1IwpTEpmUgC20oTjecJ+sqx0Ad4bSgLV/e72LREKyrEgUoBnn+PsgbZyDbrE7/E8AmeXiZ5aAHJ/w3Mp5D/B8c6r0RZQiIpWBASycEzaY3nBG03qsfQmE34dmTALNygBg0s6vACQehVqY2FAaVp5hFoEj3Yj0xKarc8NmSE9lvnDoxmRvKqusCxBVn+2h156WHbxgNRfvB0Q5kWLxeTbhSjpVhVvW6mej0o6/XoS6peU1Z8eXUX5zf42gD5yKqObQJMHztWfFKJSnnuhtB+i/Hs4uW91unRyZKDfbQhCkeB+VpYVuRksyIAwJj12nD2YRc9zx624N2BF5uezM9Ojhhm4xcXXo7Wh5HlJEVPCluaUxotxrKjG1FuGdVNz0NyOW+W8YdguDHtG3z+4WbupK7Q4ORgpvaYJdaSGtmSCQ3cEl5f4ktzzrPpcrHfzqcC2jIbgQhjDutIkpal6IAIAr1i6m9YXHXqlgeJzyTwXA+zFgs0Xdbi3fWxWgClxkTCJko3yolE+/BAn8+SYvCuk/CWrjfpU4KGjKRb2LuQU1Uy3h3yxckvTvliDydLFHdY/z5al7j6Xy/L62mWRz1XNsDJXzTiRoy2HaOI7a+Did/Gx/HbCgn/6XoFX9LHHs7nK6mxdi2r3R48qm/vuPreIOFd1hqeqxPt1+Piperl9GzzQ0MddY+hoR4TPDpwnCzsch42m+6l0byQ9QmaytyBV2lhT1vaD8/kmR76zplWfTReQt+506qT+CEj2EP71Kz4nKYJeF7XC1JB1H9ACs6yHTSZQpmkAg1EpCj6iMJn7DAmfOH5mPOlVR9jYaV9QFKjFWgF+4lV71G6kZRurI0S4rzjIhvENVT8JmPnSzEZlDc/Yy6UvMXhrCFlhYucSE9PjanUL8LTXdEBIutWA56Dr53KtyGNPtLO3Z1cpy3yHc85iISMj/pE8dOMNS9uohfnrZDzzAa2ga/raQXqeqA3rHM=
*/