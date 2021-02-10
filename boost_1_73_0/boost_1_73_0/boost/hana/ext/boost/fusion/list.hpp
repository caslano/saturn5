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
OY+H8q3e+Xjco8u2t6DvWF/SbSJA35BejjHClrOpgRKk26OHOhiNpu0O1JZQQswclKkNY7BgP3r6I9KCdshoUhJq6JEBoOc8MmpX+C2WRDiqU+r4UGkYhan3OdWUOdoixD0nEW0FrwID/Owyf3Ymm9/Ni0c4hRK8reUfM7kbnRI+IyjNDmnlj/2Zx7/HKRSk43btrn6hpSZ3tqfUIt4p4kYfFpST5hf4xV3qKJg54wvCmhID6BZZFsmGbkTPIuqAuA3t873can2iAuNK9DrwYXdOFBJL8C/c7sfHJ96tLCqu6jwq1smwjPUeFu4/tEDwfrawvplt9LAjLTBe7bCsSTvMdErx1Qpba+CqBFNfBU/VWKo+Di2V9Ixh3OKNvQlHSADeqK5kA2+l22zowJg68r1DxR1Riu10UGh67bEDO/oqUYifbz/hbTcP3YkCun2DbMYN8U5g4E99EiIfo6VWytMt8yK3sFYJbVWJWyiRzf0r6XBTf462n192Te0UhgbDosd/1qFRa5uJebCUu3qRi55xX/C7Gvg/aQE+7g/1Dz/tup/JWhpQ6s0P9bp7E8VXc2+yGGLtJ2/M50jP0nSnTAFWxkVcnVKl7WoItZgHcyiUZGYdAnz9pAagmHjjhapZ0TKqLt0C17QLUB/N
*/