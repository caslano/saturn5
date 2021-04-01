/*!
@file
Defines `boost::hana::max`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MAX_HPP
#define BOOST_HANA_MAX_HPP

#include <boost/hana/fwd/max.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/if.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) max_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Max = BOOST_HANA_DISPATCH_IF(decltype(max_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::max(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::max(x, y) requires 'y' to be Orderable");
    #endif

        return Max::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct max_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            decltype(auto) cond = hana::less(x, y);
            return hana::if_(static_cast<decltype(cond)&&>(cond),
                static_cast<Y&&>(y),
                static_cast<X&&>(x)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MAX_HPP

/* max.hpp
c2AFc2c92dXzQpNTztslO/YUv3ivvvsWBk9B6AXTkwAm0HdMhJWIiWYplxup8RmQdDWGU6Jk1NnjjcEXHPintoDmh+Nk3gJOcQ8j5/1+W7N7TPNLXlmNOlOPoZsVq9jodSVPBioyhj9oiFlvrQaZC08f/OWT5nz11gTlTNDcGAcvyW/dNd3ADiqoFbIbkU+Ibx/pEyxIPuD9+GNG33CViveJz8ZtaLE2sm6JU6mppyLUtaquBbHNruiIbuDbfXe0osTTfXWBLx1LJRMMv+IP16UTtmoVXpJy+mdhzcTT6b75VIj7f56kR20wZlFXuC+8t9DM1UhZ1I7nKeWd+dekgO/SIlnRO4toqeluHo3YaI4H9GeGBiGwIjy+GDZyVElX43z8m29wBOE68g2v3fIf0FVLSOrDZIS+kcC2O21AJxeoxLYovnD01C6RsrarCx9mkARGazCRjxiIPvExVeg6SWEMP9XZRPgxjFE2HJaqWb69viS4TnHc8/TdcteKPVxC7U2k1WErLw79dPB9reyzOVk5v2bhS4GwwpIc04bQ7t8Fktdue/pLBNullg==
*/