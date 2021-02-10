/*!
@file
Defines `boost::hana::if_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_IF_HPP
#define BOOST_HANA_IF_HPP

#include <boost/hana/fwd/if.hpp>

#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/eval_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Cond, typename Then, typename Else>
    constexpr decltype(auto) if_t::operator()(Cond&& cond, Then&& then_, Else&& else_) const {
        using Bool = typename hana::tag_of<Cond>::type;
        using If = BOOST_HANA_DISPATCH_IF(if_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::if_(cond, then, else) requires 'cond' to be a Logical");
    #endif

        return If::apply(static_cast<Cond&&>(cond),
                         static_cast<Then&&>(then_),
                         static_cast<Else&&>(else_));
    }
    //! @endcond

    namespace detail {
        template <typename T>
        struct hold {
            T value;
            constexpr T&& operator()() && { return static_cast<T&&>(value); }
        };
    }

    template <typename L, bool condition>
    struct if_impl<L, when<condition>> : default_ {
        template <typename C, typename T, typename E>
        static constexpr auto apply(C&& c, T&& t, E&& e) {
            return hana::eval_if(static_cast<C&&>(c),
                detail::hold<T&&>{static_cast<T&&>(t)},
                detail::hold<E&&>{static_cast<E&&>(e)}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_IF_HPP

/* if.hpp
K3cr2USaiFfzAOAtzBFl7+/KgDCTfnp3kl7eFKJU4UmLqbaxIw44w1MLnW9E/m0H3A1ceN25Pegp3q2LLEANZxonTkpGB+41q+mZ3gU3cZGlkSrYeqRoICUCyAgfDvzTHnGVUWdrnYxDd2oPkZSCNjn26X+m9zpT1ZdMageBWvtiIQRHzri5MFx0cGSP0QloFWm+AQ1YlVIk0LyOhCDRzhTgqTcynFT2aIzSUr3Kg1xwZ1oHrBrdRna0NVxvORyuI/HGpg/6Rm0vwmZ7op++J/KSyLBxLPpVG9JRBmagnyuFYUh3DztFCKaxxwsfGgb6Yp8BYjWxE9f12ZTvpR6xkco/atP01K7HL4z4FDV05eNrTL+Rjn1zNtfrXqXBoWfbFubb6iRTlzNlhFM9riMhSo2kO4W5Mvjpi3FAsoBJVLFaQSz0dmO3rWlC7b4xt9pKchmNt38R1bZ+UxvtE1gLMXp6GjYIYytQl3fW/uDteodXyuWzTKQ0nPKN3SIN7zCttM5n5VwlTDhjXgp5i6opaIxaqVSVaJliQnMHZpgzrZWlSVyDQUke8NDLjKKu0C3YVXJBz7Nh2yjVuJCFkBzl5WTMFabgGvg/964uzvzTi17rPRutXbn0GJjULwGccMc1lc5MhwtIp9YsHAN+
*/