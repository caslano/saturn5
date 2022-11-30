/*=============================================================================
    Copyright (c) 2014-2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR_11052014_1625
#define FUSION_VECTOR_11052014_1625

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/container/vector/detail/cpp03/vector.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/detail/and.hpp>
#include <boost/fusion/support/detail/index_sequence.hpp>
#include <boost/fusion/container/vector/detail/at_impl.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/fusion/container/vector/detail/begin_impl.hpp>
#include <boost/fusion/container/vector/detail/end_impl.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <cstddef>
#include <utility>

namespace boost { namespace fusion
{
    struct vector_tag;
    struct random_access_traversal_tag;

    namespace vector_detail
    {
        struct each_elem {};

        template <
            typename This, typename T, typename T_, std::size_t Size, bool IsSeq
        >
        struct can_convert_impl : false_type {};

        template <typename This, typename T, typename Sequence, std::size_t Size>
        struct can_convert_impl<This, T, Sequence, Size, true> : true_type {};

        template <typename This, typename Sequence, typename T>
        struct can_convert_impl<This, Sequence, T, 1, true>
            : integral_constant<
                  bool
                , !is_convertible<
                      Sequence
                    , typename fusion::extension::value_at_impl<vector_tag>::
                          template apply< This, mpl::int_<0> >::type
                  >::value
              >
        {};

        template <typename This, typename T, typename T_, std::size_t Size>
        struct can_convert
            : can_convert_impl<
                  This, T, T_, Size, traits::is_sequence<T_>::value
              >
        {};

        template <typename T, bool IsSeq, std::size_t Size>
        struct is_longer_sequence_impl : false_type {};

        template <typename Sequence, std::size_t Size>
        struct is_longer_sequence_impl<Sequence, true, Size>
            : integral_constant<
                  bool, (fusion::result_of::size<Sequence>::value >= Size)
              >
        {};

        template<typename T, std::size_t Size>
        struct is_longer_sequence
            : is_longer_sequence_impl<T, traits::is_sequence<T>::value, Size>
        {};

        // forward_at_c allows to access Nth element even if ForwardSequence
        // since fusion::at_c requires RandomAccessSequence.
        namespace result_of
        {
            template <typename Sequence, int N>
            struct forward_at_c
                : fusion::result_of::deref<
                      typename fusion::result_of::advance_c<
                          typename fusion::result_of::begin<
                              typename remove_reference<Sequence>::type
                          >::type
                        , N
                      >::type
                  >
            {};
        }

        template <int N, typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename result_of::forward_at_c<Sequence, N>::type
        forward_at_c(Sequence&& seq)
        {
            typedef typename
                result_of::forward_at_c<Sequence, N>::type
            result;
            return std::forward<result>(*advance_c<N>(begin(seq)));
        }

        // Object proxy since preserve object order
        template <std::size_t, typename T>
        struct store
        {
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            store()
                : elem() // value-initialized explicitly
            {}

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            store(store const& rhs)
                : elem(rhs.elem)
            {}

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            store&
            operator=(store const& rhs)
            {
                elem = rhs.elem;
                return *this;
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            store(store&& rhs)
                : elem(static_cast<T&&>(rhs.elem))
            {}

            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            store&
            operator=(store&& rhs)
            {
                elem = static_cast<T&&>(rhs.elem);
                return *this;
            }

            template <
                typename U
              , typename = typename boost::disable_if<
                    is_base_of<store, typename remove_reference<U>::type>
                >::type
            >
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            store(U&& rhs)
                : elem(std::forward<U>(rhs))
            {}

            using elem_type = T;
            T elem;
        };

        // placed outside of vector_data due to GCC < 6 bug
        template <std::size_t J, typename U>
        static inline BOOST_FUSION_GPU_ENABLED
        store<J, U> store_at_impl(store<J, U>*);

        template <typename I, typename ...T>
        struct vector_data;

        template <std::size_t ...I, typename ...T>
        struct vector_data<detail::index_sequence<I...>, T...>
            : store<I, T>...
            , sequence_base<vector_data<detail::index_sequence<I...>, T...> >
        {
            typedef vector_tag                  fusion_tag;
            typedef fusion_sequence_tag         tag; // this gets picked up by MPL
            typedef mpl::false_                 is_view;
            typedef random_access_traversal_tag category;
            typedef mpl::int_<sizeof...(T)>     size;
            typedef vector<T...>                type_sequence;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            BOOST_DEFAULTED_FUNCTION(vector_data(), {})

            template <
                typename Sequence
              , typename Sequence_ = typename remove_reference<Sequence>::type
              , typename = typename boost::enable_if<
                    can_convert<vector_data, Sequence, Sequence_, sizeof...(I)>
                >::type
            >
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            explicit
            vector_data(each_elem, Sequence&& rhs)
                : store<I, T>(forward_at_c<I>(std::forward<Sequence>(rhs)))...
            {}

            template <typename ...U>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            explicit
            vector_data(each_elem, U&&... var)
                : store<I, T>(std::forward<U>(var))...
            {}

            template <typename Sequence>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            void
            assign_sequence(Sequence&& seq)
            {
                assign(std::forward<Sequence>(seq), detail::index_sequence<I...>());
            }

            template <typename Sequence>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            void
            assign(Sequence&&, detail::index_sequence<>) {}

            template <typename Sequence, std::size_t N, std::size_t ...M>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            void
            assign(Sequence&& seq, detail::index_sequence<N, M...>)
            {
                at_impl(mpl::int_<N>()) = vector_detail::forward_at_c<N>(seq);
                assign(std::forward<Sequence>(seq), detail::index_sequence<M...>());
            }

        private:
            template <std::size_t J>
            using store_at = decltype(store_at_impl<J>(static_cast<vector_data*>(nullptr)));

        public:
            template <typename J>
            BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename store_at<J::value>::elem_type& at_impl(J)
            {
                return store_at<J::value>::elem;
            }

            template <typename J>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename store_at<J::value>::elem_type const& at_impl(J) const
            {
                return store_at<J::value>::elem;
            }
        };
    } // namespace boost::fusion::vector_detail

    template <typename... T>
    struct vector
        : vector_detail::vector_data<
              typename detail::make_index_sequence<sizeof...(T)>::type
            , T...
          >
    {
        typedef vector_detail::vector_data<
            typename detail::make_index_sequence<sizeof...(T)>::type
          , T...
        > base;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_DEFAULTED_FUNCTION(vector(), {})

        template <
            typename... U
          , typename = typename boost::enable_if_c<(
                sizeof...(U) >= 1 &&
                fusion::detail::and_<is_convertible<U, T>...>::value &&
                !fusion::detail::and_<
                    is_base_of<vector, typename remove_reference<U>::type>...
                >::value
            )>::type
        >
        // XXX: constexpr become error due to pull-request #79, booooo!!
        //      In the (near) future release, should be fixed.
        /* BOOST_CONSTEXPR */ BOOST_FUSION_GPU_ENABLED
        explicit vector(U&&... u)
            : base(vector_detail::each_elem(), std::forward<U>(u)...)
        {}

        template <
            typename Sequence
          , typename = typename boost::enable_if_c<
                vector_detail::is_longer_sequence<
                    typename remove_reference<Sequence>::type, sizeof...(T)
                >::value
            >::type
        >
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector(Sequence&& seq)
            : base(vector_detail::each_elem(), std::forward<Sequence>(seq))
        {}

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector&
        operator=(Sequence&& rhs)
        {
            base::assign_sequence(std::forward<Sequence>(rhs));
            return *this;
        }
    };
}}

#endif
#endif


/* vector.hpp
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
*/