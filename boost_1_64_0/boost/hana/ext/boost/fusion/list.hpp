/*!
@file
Adapts `boost::fusion::list` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_LIST_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_LIST_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/ext/boost/fusion/detail/common.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/length.hpp>

#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/container/generation/make_list.hpp>
#include <boost/fusion/container/list.hpp>
#include <boost/fusion/container/list/convert.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/version.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace fusion {
    //! @ingroup group-ext-fusion
    //! Adapter for Boost.Fusion lists.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A Fusion list is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of a tuple.
    //!
    //! @include example/ext/boost/fusion/list.cpp
    template <typename ...T>
    struct list { };
}}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace boost { namespace fusion {
        struct list_tag;
    }}}

    template <typename T>
    struct tag_of<T, when<
        std::is_same<
            typename ::boost::fusion::traits::tag_of<T>::type,
            ::boost::fusion::traits::tag_of<
                ::boost::fusion::list<>
            >::type
        >::value
    >> {
        using type = ext::boost::fusion::list_tag;
    };

    namespace detail {
        template <>
        struct is_fusion_sequence<ext::boost::fusion::list_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Iterable (the rest is in detail/common.hpp)
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct drop_front_impl<ext::boost::fusion::list_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<ext::boost::fusion::list_tag>(
                hana::at_c<n + i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return drop_front_helper<n>(static_cast<Xs&&>(xs),
                    std::make_index_sequence<(n < len ? len - n : 0)>{});
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Sequence
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<ext::boost::fusion::list_tag> {
        template <typename ...Xs>
        static constexpr auto apply(Xs&& ...xs) {
            return ::boost::fusion::make_list(static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_LIST_HPP

/* list.hpp
TFwzGl8g7szR3yNZQdzXBSv47zG/owMXwfPR+TfGiHcBcL7checfYzx4Xc9acB17GqKRe1uJ/bFPG7H7lu2RWwm2JD438wlrRWe/vtC4z9A+FF1Mxg8HI9djYt3BfEcQe3oAua9HJnXgxiZsHB7TdjO5OTCsAp8/iHjvC3xjTXPugu5HVx8SPhA8bKBNODh8Fv74KvZ6t5EjCHoQG/2Y8yxsa8BE7NfKWQz51gb4dsQqsAuudk1L8jbM6zpiB20r53dgQXEnzu6iiTtf0fSzh1zsfpL4LBu6n8Aep8D7xHuvr8KfbSF3NZK5Fk43QYzQIZFHaIZeEJ8NOY9zlxRxZ4/PntwILhcRU4DpRdy1TEX/FsLDOh0Wn42h7VH2dJH4DC06wz22iPvAXdab9bq4v4scwFXXTnhBHHfh7+ZZeHrYKzx3G7hiAZew4YfF57iW4XN+Eu+Ygqvcy56NJ3dxHZz+CDlQ4h8rfnzhKJ7Fb05hn94sADfA+0eWgeHR5OJHkUt+DhlNCuZcAT0oQl93I0eeW9rLiDFz4C4FrfiZTdwA/7m5P/bjgmdhP5fYiZWIPTdg/+9lY2f83e5r4rIgeENbOA578S1zvXEytrof/wPmlmxAhtcG6d8HZ8aPfg1mf/QOcQOcYH8vOCs4tD2dPYGLfs/aXuNcqM9Z7OQD4sxc7oEsxAdxv+Od63mevMOJrsRBTs5liW17ESt9Ny9Yvz88ZTLriIkLyhx+OeyHmGzp/MzvW28ZvfaTmWPPpH03oStl/TId1VMyxNsp+olXYXi0fh53ab8K/Q3WJeKb1/U3P4XwI3ropBn/C+enpfwJkWXN5b8fj+0fJJ7JddbZ3QV8z3UuX5kuXjEu3wHgK8921sgq7zsA/HUZ1cV8C/g0uybKg/3l8svajb6C1fbTiivF+5xS+Y7/5vI7/k3Er+JFAXnWxOT8jHF8IbY1N89sMWcnm+VX/TddKd6j9ITvPQb5udZkXiqQxAsJaJGRkyeapmekpWv6epquz87Jy0rM9K6r6TaZOePlOpquz8gel5iZkfKXbZJzCrLz9XeJKutuJtbdVHO56qaqxJo3yzXjtXKSrDlJo/n2c2u2Od+al5hvZqjs/LycTKs5OzEp08yYcm1/1TYrsdCalJidMj4jJd+QV7O/bJ9iSc615iemGWtu8ZdtdeFYUzMT0yzI+UrW30yuPyRM+6sn5TO6LP62mZDLrU3JJSOnSbFImfx5O0s+8kjMzMk2W8flZBZkmeX+Bjzzp0v9wVhrsFxraJjW+Ml/Z6lNtjLec9E72LvW5Jws/fvljVprBlPOnCDXF1DXPz4pIz/PPLaAL8yX+trsj89bMzOS8hLzjD5CA+stzCQ7LTsxy2zJSMumG0O/wgLbZSdirWarmZlPyM3hq+7leLO0P845Pw8VTzEnFaSlJOYnarLdn8wf608157EA3xrzrOPMeZaMnGz0eLT4K56xmq6T7xtpVJ6RLctD9fIUc6ZZvKBELNGaac5Oy09njf76cflCgdISc9UWEmPkovMn5Jp1m0pO8trfOfEsws0y56fnpFgtYnstQI9he2LZlowrzV7sNRbNE8wu3Wo8kzcu0YtTAfXmdH9daEBdEv0mJ/GqlTGyb2UNhjylrNTyhAG+8mZqeWpeThavd8lKzGaIFCmzP6235pnzEzOyrYm5uSk5WfyXVxZh6jPJugxyLPkIPg/hSb2MVtZhTswfbc1PL8geY9WFJOq1Zrp8MxMtFn0fZN+yPBd94mmj5mQedthR2mFL7DDP7qos5j0fyU53uk28PcbudvB+KN4JYvcYNvhXLbzvmQkKc2n+9zi1DjPeOROhBenvTg4O0XjfkPg=
*/