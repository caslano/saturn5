/*!
@file
Adapts `boost::fusion::vector` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_BOOST_FUSION_VECTOR_HPP
#define BOOST_HANA_EXT_BOOST_FUSION_VECTOR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/ext/boost/fusion/detail/common.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/length.hpp>

#include <boost/fusion/algorithm/transformation/pop_front.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/support/tag_of.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace boost { namespace fusion {
    //! @ingroup group-ext-fusion
    //! Adapter for Boost.Fusion vectors.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! A Fusion vector is a model of the `Sequence` concept, and all the
    //! concepts it refines. That makes it essentially the same as a Hana
    //! tuple, although the complexity of some operations might differ from
    //! that of a tuple.
    //!
    //! @include example/ext/boost/fusion/vector.cpp
    template <typename ...T>
    struct vector { };
}}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace boost { namespace fusion {
        struct vector_tag;
    }}}

    template <typename T>
    struct tag_of<T, when<
        std::is_same<
            typename ::boost::fusion::traits::tag_of<T>::type,
            ::boost::fusion::traits::tag_of<
                ::boost::fusion::vector<>
            >::type
        >::value
    >> {
        using type = ext::boost::fusion::vector_tag;
    };

    namespace detail {
        template <>
        struct is_fusion_sequence<ext::boost::fusion::vector_tag> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // Iterable (the rest is in detail/common.hpp)
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct drop_front_impl<ext::boost::fusion::vector_tag> {
        template <std::size_t n, typename Xs, std::size_t ...i>
        static constexpr auto drop_front_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<ext::boost::fusion::vector_tag>(
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
    struct make_impl<ext::boost::fusion::vector_tag> {
        template <typename ...Xs>
        static constexpr auto apply(Xs&& ...xs) {
            return ::boost::fusion::make_vector(static_cast<Xs&&>(xs)...);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_BOOST_FUSION_VECTOR_HPP

/* vector.hpp
V2vxSem9DkvvpschQtn5JP7d7/M2wm9gIFMJUCME1BJM+psBTnApsw/CadzKQauewhLMqsLUPT5M9Zg3+Zn+epH66j44ppuCvq2vY1/cDP1bXt6bk0duwz6tJPd9Cvun9zFIoz49xeRF2EMSME0s1vcUqhuiFYVv5xwICZtarvU9dTmEYOE2foGmuy88AkdqzmNc2eZ9DEOAlW/rwxCyfyh4UZBn61AaMjCTvSEDoQnez/FeLMDLwxY4l3gRM+Bg/UAho/yjz/s8RvoDX5qLfFu3ICLqI9iAwn6sEXuHKxV2QgdthuBQl8/7MPyKpmKYzh1oUhRQXcZCCsS36WX4K/zOL59e0+j9Ow0HICzhI5B44jPO9jd0CF50K93gF7yfwa9ndaX9wGqLcsCnYmFlr099BkWEpyNCAy4j5aTqxZYomxC1/JMqv8VHm2Hfu/rn9q/X8Mp8JDpwqLC3rEljLVSKRnCtTaeYTt+JeCu0TYeIoiKihz5TaC1pbb4GFaFfxwreAOcuVj+rA3XkLAodA+1XCm2dQruI3c6rO+mI+b9+qW4ntpb7+z7obTEN38j10kI23yb6m2/z0zQn9N5phH45vd3BkXKy9lU4yapHmOvWF+jYQufyK4p9NI9PpaXUW0dofr3YbSO02ExWbOBWINvRES5SQvHx3cLG9ysY352vx8e38iPI/zBtXKk+zsLOjn8xzJn2QgrLt+mZ
*/