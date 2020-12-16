/*!
@file
Defines `boost::hana::detail::wrong`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_WRONG_HPP
#define BOOST_HANA_DETAIL_WRONG_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-detail
    //! Equivalent to a type-dependent `std::false_type`.
    //!
    //! This is useful for making a static assertion that would otherwise
    //! always fire up dependent on some template parameters.
    //!
    //!
    //! Example
    //! -------
    //! @include example/detail/wrong.cpp
    template <typename ...>
    struct wrong : std::false_type { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_WRONG_HPP

/* wrong.hpp
m6MstpzVDAOuzySgZdPI/ly/SrY1dMD4L/zn03e+/YCT9oHvy2Lj9PjbiHh3tkV5EO/rjvZ1H8u/xJ5tjxfjC7ApffA/UuRfybaX+W8CjDJTxIf7Q8pMNwMH7Y4+SM7yNYDJ/jgBYXnX/ESEGYc80uezrQxjXigf7ohVuKey/0tLtM2p/R6DeDneT5dzH/Ho/1Tdt4k5g3YJ6rLPSNoHOIdvnzpBE3kijcaBX17R54hn+cU9W/73YxZ93ujbUNcDd8wRln7aG5fLMlh8XYadqm3XqPAOP0cYVjyvUrVlu+BTiPO+efTbGR2i7igbxyR1RXHbifuAlOV02bqD9ydjrkeNuV2qTXa78jIOcM5h6v5D867QfpjH/pMypSe7Ovq5yfKqOj7V5S3eGpB89GliTM0SfX/sctMWuu8Loz2C3s+WHirz7XflEvQkndIVvJMs6BiY5gX7RTz4NHDS8WcBFr7zqfdLwico+ymcLrwfMn09JPp6WK35pjwHAHPfiFpTD5JPjDKdXPMeL3w9mPbV795OACb3l/qN6zIV3oxwTbhNJob6jHdct3ESYdTR0Dh/laVx6zHRPbfNSFaJyxAtEAV30gZQ+CHwUUJWxTihArHn5blCXqzTFYo4nY6y550aXsS8OmvrmjOQU28V8udnoO6mFtZKe0dbUz3dxiggmsrb1ESSL+DvAtnvDIf3w4P7e8eMKjfbiIsj5jQR98ghUMotnw06cn25iPzjKrWfeg7H2fkJL8JvoYsn3OvwEX4+y/w87kUuIY0HStO4lwJ+RYnQ/QD3hWJ+gg4+dcfYrRGMl/ZeL0niUA7l21TEXariXo6wLP/zVPlf4eKZFmVNlflK1u9y10b4fZlql1ch/GrSvYh0XyPoXol2eF0p75Yx/nWC513ueajIn7z49aJur1Tvkr9B7a3z0XgT6/BmVe63IKz1YdcS9xqF+7YA7tsBk74Utvl3+zieSQvjTtCya9S7ESdpvce3X/jd1M7lym6RtD/AcnL/oPQ6tsw8W6MP0u3yYdL4SIDPblT38t6HsLSdm6PCBQhvi98XPypbOypbOypbOxLZ2jqsr9XO9mBVbNW0jzK0+KdZSyVPWBep+9+cz5izaZ6A393gj6m0ytfCdXK9weweWGlpfVHxwQ/QL61Mez3Tfn+p4INiL/8DwGV6vf/9KtN/SNhoS3zA0/eZJe9keomP7FLx30rOdIi39dd+ar6jaGhbve+qeN32N3Pf+cnS5F7zzTPaEya6qzlpvaLYBz6+uynTJfZ+XWanhrC3L8ggTWcmdYe5tr1ji/TJsEXcDUned5qv7oAscO/1oVjSRuaHq6Yn86X8iPsw+41I/0X81ud9+3Vh9ONV6bfJtnKc7RJ3eqSvoSsC/XzLKokT8pkHvij2HLvUXdfblQzuOPSzfN+0BOH5c2bS73aPrvseCq/OtP0CINS1zXVhwVcLA29q8c5ls4QVWVitgIX8GvEOaDIWyCaFnrprV5sxX1E6anhY66Gu1N8Z6jSZSb20Wc3aAFL66KYufYcd1AyQaUuJRyjvEXkYwk733Nzi1t3ljEcpxD0iYOPsk37zzBSyvc7NnTLXxgA5vHJlw1Oh3nlaFXh7a7W6n1ppcTrdPmMN+wMYPp8qxQ+qlS3R2oAPgXUBe6L1hPFJrRj2sICu+uEBnfaGgK762IBOe2Pgjuzx5BW/niavSNlRzknsa6xMfax3ELogFy6KBsZzozjDU19z5yppX4POstd8eYZ34al87o2c3Td2SnZkdGAyvlk/IN5qCEVRd9LIMmamKCPDKBdSD+aG9o3vjwzsxYCVRSOje41vVt7z+r2oRzXqsbOhsUZVRYJod48ykF4=
*/