/*!
@file
Defines `boost::hana::union`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNION_HPP
#define BOOST_HANA_UNION_HPP

#include <boost/hana/fwd/union.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto union_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Union = BOOST_HANA_DISPATCH_IF(union_impl<S>,
            true
        );

        return Union::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct union_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNION_HPP

/* union.hpp
2rWw687ZWzR2/GD9pWWsIm6ozAuL2wEySwsVGppD8Tn05YYcbV1p2Sju1HCLrFLUdUTr1idSN2sjAzpcusyeTTsTCkyPdW8XV0vgw6W1Nu/GySTOVZuXN36iV+9lERAzP/6d/8gl6iDAgjGTHT7wkdJUtoppNL7B3eB50RHc7O6G6je8b9hdv530alZitVfNluS3vOEEHjTJvM1FlX0eb4rYBk7P9ky6TSf78DBam2SdKn0G3Snr6C7TFEENxR03xU2/x/DvBjdVkDSn3GgTGI9hkzEWmdHz0lc+YifWSp1FFoAuoEcBoR4bOuaWf/K7bQ8Ya5/OtW10h9RG9XkLIhLUiWiwFEY58wd1ZlSpVBwuqz6xF3ccall/6fX+IX2v0vN5/Q7B1j040U+FHHugOdb4tNW9QHhvqztARu5VZeReASMflDNyL8/IPcXIn8vH43I+/rX8Vb/8FfQUWd2TgQMjA+Nf+7UeycAY/vsV/ut7zHeghUUKcn36OnvZlNMH40UMTaV+rVSqX6mU7eE8EanS1yo9rdLPxb00zEP/h+rMss/aOiioirC8y6/uB+9AJq4risR1XiLelQrEdU4erv8fiIMrcPBOCcN1uSy8U6JwXSAJc9jyuoocXFcRg+sqUnBdLAQLZSDfzQrt
*/