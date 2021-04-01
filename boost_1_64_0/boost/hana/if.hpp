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
cLnYJmGaFAJOTkfEXMkasxlI8JOtoYrRladiEShI+/0h46SBnmY4DsL8sF6mhYJpl1+o6eHK4MnSH6jQ0rEx/66uAsx3/rbxm0hDoRRaX0U5iG76h4vRe778JEzzfvb2FJd1VHnk0KHcH941UTzs5SzHYq3n3m90mUuIx/tcPpD42su2GyOlb9EfhKmAioout9m0+B9wACSSDVTOm2yn28QW9JnQyni7r4bfCkK5aYSkCHaegGNlBlvp3wR+EfY1ArLzdGeVo1yp2MS8zE5YxlvQ0IyGHUK/u08kuVUMqwxGtv5DIunr0CJuKPbu/KZIruxaAl7XAw+6dK4zF3pWC4/3j4JtKG8nNIv0LXFRTkFm6/0gftY7x4l79KwPVHJLWcqtDkvn1QShegfxHbYHOo1n/I24D/pH+pJW2X/BHXQz5taIKiqzeQtnakQSvK0jo6vm5JmzHsqN4GK8PuFj3+XnJSA8U414DXWvq/HOQAS6v6b0h52KineJVWGVFLkSAKjdRwBys15oFTdqV72/FYsM46SIadK9bN0TZ/VrLKbXN55h4kmUQmMJ7A==
*/