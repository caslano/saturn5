/*!
@file
Defines `boost::hana::extend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXTEND_HPP
#define BOOST_HANA_EXTEND_HPP

#include <boost/hana/fwd/extend.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/duplicate.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_, typename F>
    constexpr decltype(auto) extend_t::operator()(W_&& w, F&& f) const {
        using W = typename hana::tag_of<W_>::type;
        using Extend = BOOST_HANA_DISPATCH_IF(extend_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::extend(w, f) requires 'w' to be a Comonad");
    #endif

        return Extend::apply(static_cast<W_&&>(w), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename W, bool condition>
    struct extend_impl<W, when<condition>> : default_ {
        template <typename X, typename F>
        static constexpr decltype(auto) apply(X&& x, F&& f) {
            return hana::transform(hana::duplicate(static_cast<X&&>(x)),
                                   static_cast<F&&>(f));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXTEND_HPP

/* extend.hpp
xPJzQoILarMJqNJyghWU7U1mXCfRNcSavYw1J55f7mB/o1Wodw8eTc2kGfd418A3nufLGvCSM7ELK1VhifK0q5Ah2p7Zs/JRlj/HXFzoZheilbO4X2irC1UL34yaPxbCinWrIT6lToUvGNQutrIEn1R5hy+OStlu70HCPA1/3x8S+ZLYub2Dvksf1Q+UNs0QHShNUyeX4ebHNMn90rvsszJSYJ/Ra1UvxoYQ6XjlUl7hWeZ9D2hPjmx+W1GFkauMg8gKAUrU4larh06oe5xczfLMnd80hL57DcILmerb6CBrOfrL7BpOMx9xM5StIFcyhcMYVahLXiVEJ7bLteI0/IyXsp2WMGpngbIqf12kV7HLkKcH0EvXyBe595e23ZIcV88ykgmAXLV1qk1ciO2n1DTh8ttV9h+XhzwuwDY+SmakP9QTToLlzHI0G5sipavqnebEc4t2wUJuvDaZsfUfNpT/cM/71fTrLSx7fPAIpCxwDd4oZYIlXBr59/ZJfqHA8aV69LM1CPqGc6kxl5lVjPDKB3Zrq+G74P6NcLsIioNJAzAcILgvwTUQ3N0Z3CV4CO7urrO4QyC4u7u7/LhbcLcgAwzuM7O+h62t3WP3oav7+FS/n9DtHj9d8Dba49FgHzwO4lb1XuLHnDIA7nW+4PMu6nUZvJVd2UyKWvcZh7VhGjun0gyXe5ue0+xEqnF8Wrqh6tR0tAFd29TC
*/