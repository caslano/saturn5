/*!
@file
Defines `boost::hana::count`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_COUNT_HPP
#define BOOST_HANA_COUNT_HPP

#include <boost/hana/fwd/count.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/count_if.hpp>
#include <boost/hana/equal.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto count_t::operator()(Xs&& xs, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using Count = BOOST_HANA_DISPATCH_IF(count_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::count(xs, value) requires 'xs' to be Foldable");
    #endif

        return Count::apply(static_cast<Xs&&>(xs), static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename T, bool condition>
    struct count_impl<T, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& value) {
            return hana::count_if(static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<Value&&>(value)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_COUNT_HPP

/* count.hpp
tAbMFFdgKF2t8RrlVs6E3EW8N5jzFs3q2A+/ftaec98IvDeSnjumjruLffG7pcuO9G7FIubADAaDwWAwGAzG/xLxi/8PF4BeegegWzqAI8gHIEgHkBSmA3j4QkX4AITpACioftd6AKqbhL4KBM/vUh+QGVUfsHd28KukXmDTn4G+o7/ZNGL1/Y+fetNtW3f/N+zgOQqdY7puuWG8fSLx9kmQ64m3p1o72avjwtd7YqcO4uU9ineQh7lUIM23MjdnMBgMBoPBYDAY8UE89v93eWwOMv/HnfdPOuL/G/uvnXhwXoXGGysg5yE1VUT2427FcYrLLe3Dbcin2uJj494TztwTvjzOxjyZwWAwGAwGg8FgMHqCeNj/HQ1ua8DltzoCHt++egdg82DEWdFj85H9H9TceBdgIDj00F16DADMwgqDvDV4pFbhCVCJWHMx9zPTbfgZe2DDXy5t+FvzLF/PTrv5y2XfnTlrWvNr/eF7MEgcz149f+Wwu6a+ucZ6bX6fje7z938dhRYPiM49XZPcsHhAA8i2PxBSXKtBkLSvQSc9xoo46ivW20xx1VnsYp0Fg8FgMBgMBoPB+AcRT/4vIuztK/7/VTf4/4DI/J9G2nP+vyc+/Jsl/3/g0dumHzDz1WUrdrZPqvulwPTf4fkDIvJ8Ix5/o8735TUJ4vmNlfvel7+p0hQXnt9ayTyfwWAwGAwGg8Fg/PuQjFTVy/y/1haoUX0+q0MNqHKbp16IASA4/qdBHN9MHL8/zaMfUuMQ8M4Qju/0W+v8qs+qj8jrU/2qG/S22xzfjJQxQnLe7bfc3PTSsmXV750zePmA5gqD81KfNJYwzjuIOO/htLeLGVLu+WI3KQE780QGg8FgMBgMBoPBYOwbxMP+X4dCHeR/7/cAFNy/zawY+7unRuH+x/8axv21gbhcsO8LPYDSQ95fLnm/vyHx7ZEBS+UDB20o3pjVMtrg/eiv57x/Bzj/UAfzfgaDwWAwGH+zdy1gURVReHgsooCwiIAvRCKjMqW0QrPS0NIiJCNFpdaVXYVYdnFZEtTEyvoqrdSoyCywJ5WWpZWZGqWWJamVJSWVpb3MEs0HFD3+mT277CIbUJB9X+f3O/7M7Nx538ecc+5cBoPBYDD+XbTL9/8sOTnwp8+xGIzOPQC9/sHa/3KX7/v7N9rb3xsySDqUH1Nrf+XVn2fTW235uTqXerRq3X+fWvdvnxQ8JTG0+8XXRZs7vDtyepxz3U9loQ5NrPs707o/GCzrFgL2BZt4zc9gMBgMBoPBYDAYjJMIX4i5jdf/BuNUfb7JpjNZ8Eo9VuOGLIvOkit9AfL+sT4gFHsB7ENtU64Zf3XqWF0iqt3s/gDy98IYIZr4WTduoH3/gA+hYxhHOoZi0jH0oP4Jh/SDjuHAcTf/AuwZkKU3Zc006v6iwXadwEStN3gMXoC/CSJ1EXEt0EUM8/a0L4Dnb+Cnd5Xx797oN81vWcn+CQ+unPfMym1pnt7b97xPwTalAwksit35Rf3GOd5zvvN++AzNJ572KfS8H8FMVc/7K6K+21fRY+HkXveem5DwQ62nfQ0871/QT7Vrdd3hjMI+GvOwESsG7H//x3ohFoXJ+OxFn9yi39f/93uOGkuT9p+LjwRuUOk3Jc0Z/NMFQ5KPreoTVaHtVC7ERpXekJj19dEvTEGzN4y6bPcdXT8SYoWq5/jo+VWGoiPrZxWP7lId9Xudp/0d2m4/hYgz1Lhcl/XwoQ1VpZWV24O2b1qIPQ+sqp9jE3d3q958617/Y0HPH+yVhD0Rhqv0hYujtvps3myO2zV9Re2i4CrsK6HaGz805al1i5N29l37aGBReLd+dp1VgqC5S3M=
*/