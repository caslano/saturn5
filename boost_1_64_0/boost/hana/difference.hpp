/*!
@file
Defines `boost::hana::difference`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DIFFERENCE_HPP
#define BOOST_HANA_DIFFERENCE_HPP

#include <boost/hana/fwd/difference.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/erase_key.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Ys>
    constexpr auto difference_t::operator()(Xs&& xs, Ys&& ys) const {
        using S = typename hana::tag_of<Xs>::type;
        using Difference = BOOST_HANA_DISPATCH_IF(difference_impl<S>,
            true
        );

        return Difference::apply(static_cast<Xs&&>(xs), static_cast<Ys&&>(ys));
    }
    //! @endcond

    template <typename S, bool condition>
    struct difference_impl<S, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DIFFERENCE_HPP

/* difference.hpp
TWTcTs9ZbYPgLGs4ueI17nTs/5ffKp3UnXBQiX9jF9fKb1C2Z4fKleS1nXjdfToXu9OgG9leCRMuvPGtdsWXlMGUUgbxW7VXb/JmEmgZEkddXMpu2Uc78zxbzE17QsRCzAjXH5SR4b/988DSa2WL9HpZb3PMK4nq3pzOcXIRFWNAe85T4190Pjo/y3c8F44n60aA9wiRSdBez0WTPcmJZFkDFUa8ZHsUy79X3d+HSXnTc5yGAWY4PDf6wGwVqnLNLLsVtQlMw0ma55M3Y2TNYuSMv/6zAR7esTYBStd6kTtoETXAZwwYlcyoIu7Wd1RdpuFuSHYY8hJdTa3Rb9ayQzkpMMM0OQ+ojjlwDA3u9pEqvlvFUQX3NgPjllxHOBsKv52Y9XJbaZaV5wJdto+wqxqXRnL8i0cFXeE5wgVEaBZ/TdwG575Y8mkKJHMkjjZt715QcVyp0VCay+ez8XhZ3zVHV1O8iWFOYYHASzWsrGwVuqUgMpr/LeJVhqU3ECfVDpALvNBgHlTghiVv/fvOOQxf3aGubRqYS3EoiKIFXzCZmfisUd62h6braA==
*/