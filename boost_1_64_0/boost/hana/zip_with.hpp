/*!
@file
Defines `boost::hana::zip_with`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZIP_WITH_HPP
#define BOOST_HANA_ZIP_WITH_HPP

#include <boost/hana/fwd/zip_with.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/fast_and.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename F, typename Xs, typename ...Ys>
    constexpr auto zip_with_t::operator()(F&& f, Xs&& xs, Ys&& ...ys) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(detail::fast_and<
            hana::Sequence<Xs>::value, hana::Sequence<Ys>::value...
        >::value,
        "hana::zip_with(f, xs, ys...) requires 'xs' and 'ys...' to be Sequences");
    #endif

        return zip_with_impl<typename hana::tag_of<Xs>::type>::apply(
            static_cast<F&&>(f),
            static_cast<Xs&&>(xs),
            static_cast<Ys&&>(ys)...
        );
    }
    //! @endcond

    template <typename S>
    struct zip_with_impl<S, when<Sequence<S>::value>> {
        template <std::size_t N, typename F, typename ...Xs>
        static constexpr decltype(auto) transverse(F&& f, Xs&& ...xs) {
            return static_cast<F&&>(f)(hana::at_c<N>(static_cast<Xs&&>(xs))...);
        }

        template <std::size_t ...N, typename F, typename ...Xs>
        static constexpr auto
        zip_helper(std::index_sequence<N...>, F&& f, Xs&& ...xs) {
            return hana::make<S>(transverse<N>(f, xs...)...);
        }

        template <typename F, typename X, typename ...Xs>
        static constexpr auto
        apply(F&& f, X&& x, Xs&& ...xs) {
            constexpr std::size_t N = decltype(hana::length(x))::value;
            return zip_helper(std::make_index_sequence<N>{},
                              static_cast<F&&>(f),
                              static_cast<X&&>(x), static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZIP_WITH_HPP

/* zip_with.hpp
LR4lco7nLR/P4ecQplRdLtUWaS+zWIslfqGwSDoy1jPZN9AEiOzEj9fzaUUpRvrp2ZrP4hhG/DQy4ZTMFIo8x7h+wLHjLmtl5vcyVa8zxeXi2eXFdLWwmDOzEziuB/eBnLcn1Hc+U8ZOK5pWMjRPIWOvGTcWGjf7SIULr+3P05gf2hhyPlhv8TIusKbclzxKYIPz7znROYBxjWja1QjUZ5cmM/+A++EeieuRu0e7OxoACNk7Ge3pUGBkosQ2I/ZlEjL/espweqnU6qsoijrlCc1Qhgc5jyZSoXlUZVtmoRnf7+6zcZVLA7IBVsm3ID1YoGsr9S/W788k4VpMl0/n4CZC9Rd6d2FM/WEjPMll+ZtXukHj/BCkJx+1d2ecWgef/rDaO6bL2cxCLZPPZc5gObL3+7nwXhl9f2055e6nsVmy1gTUSW6sZLWi+n/ziTvv4Uy//ZD+ziaVrfkdPbFzfzyP+213dYRtS6WiBnat3RzUhnysG4tBimCciamhwJi3xHEH+QGl5/TToWQEbq+rhy+bux7n44R7+okd6kqY4zvWlTDhurJem6IyCktpku3F5XSW3YILp2vZQjmXURsoVrDHd8bROJD+DGIyy1k9ccqFKu3CeE9A/Mb0kZE7fX5uXurUhpsUDUNBQ9Ix4YVajo9G50b1mBh7+IU/iGTqD8d35qv09i8Jp4j4nU2aVKaQ38quytR2H7tMrSb8tjw53BZ8YLdlZ76mLaVoYKqLtDKnFxfn05kzVlvKuypT+1fovRzhpfF6uEFh5SnRln2yLe0Bv/xqcHi1TM/19SO74RvV9wb9vX5XfPUdheQ7YuY0z9qqfepb6MPn/8OqL6DAcT13wy+q51fpLxPkZ5d7+Z9cLvV8dNk36qkt9FabGq8yk4LfdfrLj8G9UvP7y79kO2A5QJeqo7rKb9Nsd2EzfaUug7ZvqdL/+e3zrPXE/qqj1uhNXvf76sL3eWIMl8djIUc9XlO055X8pNW52O53O9FJg/Cin5Z2gTf9/9N/uf3Pbiu6V+3+LyTjYPe7xvJBSnao1BnfC4T7h/7JCdHjyKraRnQ6o2+iMm/SX3GX3zzFkifMHJbb4S7mrbHPfJn+TovvjyfLKZn4o+YfF330ujAG4+nywUVzJF3o0BeKeXRmF3i818U68bU1VtnsYFfrd7vk/EewubkXrwiC/i0d36WJM1gBnV5ZJBehPJWIsfwly8xr/YkC1nNzb0yfO/cmWkbUOv3Ch029gtXifeY8YUoVtubkc+lsrmzsGvR7jcx81cI8+cZkNsnPP9uicsnvHHblv/iYdL9fj2Kwif7YE4bOtDy9E64sWZcko+cJu+NiakzThM328XputjbUXCBpJDcWaR98MtORXUyxwLdHIpoiKhUu5DWi/4nXD701UMeITr1PLt/KJeqiXGfuRzjUFEBXPxg78r8hf/qb4AeYT8/+N/gPqZpo2/Pt32vU7s4TNe3XXKfWtsrpaX6bifDqR/CYjftnTYtxx9Beo/uHbn9UmxuSlrVpFxXN1HdfRGuoguj/XjS/v07/zjWg3816UeLfkcvFmlxqOCnlHH1hbSv2vEx/e/1v9ppJDzcoH0V9u4ADYnurvq7adsGsFXN/Fd/VG28ftfstzG4qmQppGWz2vsDq8D4Xa3TUu8HXll36v5CrDclv1LFRKs+nxt1O4NXtcHdwI8ls0TZlv/+fdl/Q4ZRa3VSCL9b6ME+yNamyhzPGdi9wLB0jYz2qtYzlRM84zKdZuX9Zqw+G6vSu/P40/ey/xXyKBjlSoNR/Rq7eAnmM9bahrULm1L6DSSj7LXzXt1VvdzLlaiUam5Qo+67eC5I/U6/VUO8NY9lqIXc=
*/