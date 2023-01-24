/*!
@file
Defines `boost::hana::for_each`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FOR_EACH_HPP
#define BOOST_HANA_FOR_EACH_HPP

#include <boost/hana/fwd/for_each.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr void for_each_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ForEach = BOOST_HANA_DISPATCH_IF(for_each_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::for_each(xs, f) requires 'xs' to be Foldable");
    #endif

        return ForEach::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        template <typename F>
        struct on_each {
            F f;
            template <typename ...Xs>
            constexpr void operator()(Xs&& ...xs) const {
                using Swallow = int[];
                (void)Swallow{0, ((void)(*f)(static_cast<Xs&&>(xs)), 0)...};
            }
        };
    }

    template <typename T, bool condition>
    struct for_each_impl<T, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr void apply(Xs&& xs, F&& f) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            hana::unpack(static_cast<Xs&&>(xs),
                         detail::on_each<decltype(&f)>{&f});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FOR_EACH_HPP

/* for_each.hpp
LOJYnIGREjMqM8B0DTRlquDc4PtI98b1/QbJP3bbAtwkbDPnvI9E5fDKf/HWIbNtDrACWIKb+631aIvmSprdPY5KotTgFal5S9XsJSlzdScdhGqJVt26/kjUJ2MblLPOG4tLyZyxZNdXFLCftRhhjGKhf8sQZK094RGqOnzM/eH99p7a+eozI/ZhXQmZyv/sgwU7+Z8vPCn/3MN28Vx4G5/WHnTjTiV4L7rHqfOiFnvgUadgXNRshUZawsj4pmUty++ekcRnVExh+p27USsAb1GZtpYRib8/jQsq3Jw4VeRKhuLxVKmhSwC5mZKfm91ld0iTBhExB2TPEYJ7vKFj4aAMRUIk3z5v6E/JBhzJLg52mwCj3PxcbHyrG8WHwOQ8NpHgnOybygrUfO51pr25ggBkmx/CcFHL7iMupE7BiLpU2M3XhNcEVxLG4fz7SLMQxhzjsZcsXwLrTV0XxI4IZmsn/CYQ/zX97sadd+nrZEddya3gFDpsaGNXvabG0Xska7F0fWkr+JGV2Nwa43QLEdxRlEZCSOLMv1OGr77vj3aFExsu0yjL1PH4NaHXaEPXH9YIAwgQvzjeBz1HIiAU1n1ztpFjIMqO8QjXaTajZZhGYF3cXXmFDcrQzV4wap1Rbol0CG8QdvH3rMCovGoOYZFKSvdvZv3xVUn1mE8RM+MbHl0IEKCkvZnoq2acoJqu1E38/ts+Ze3gIjNy
*/