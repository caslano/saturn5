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
3QkgmTLTeAbeGQnYla87Djm6pTG7xQOjCGChY4N6NHKwPVCFIwwOa1hZEnY/2ryIaipi1S+tqatV3amp7maHCugHAm1CWOm+RFyUSb+Yj5dMJ6i2NC4tJMcRSg5ak4GtAJtRrAfuOzjIJ8c2xloAZ4Ewhrh9nnhYXstP7F6fQd3yWqq8aFSTc/1lHnRTE+MccFH9jOSBMtA6QDYAsSHOLsEn4f+Ee7JCHQ3V2S2wb8xEBCunkBe4ohf9OiZJ8WfsoJQ4iKL5fwBL1YnifZOpWhaG7RNlfsYGLBWeegklfgEDf1SJz32DJX6Rw2gp/chvwnyluYrB8N/RffgH1ZGfC6NFCpmVRJwyvbvZq7fQMLmROZLyIs2aLkmqt+q1nrE/zdr6tQUbBq/b8YfyBrm2BxfDnhbkwLM+2+nERyKvcqAfQUylH8BrUqObShMi+JLgg8hYRCp3tMdXoXwRVPMPDj9481hZKX2rV+pAKv4CRYrY43OZcC2kqyTXpoToAk6FdG/kGPJtRCewFvnpP32TIccnXYEQKxSmJ12M56DcVEN9z8eHkmvf/rS7LhYlq9zJNzgXaElC4NuTD3kEf6e8DT9koc1WiAuUKsjzXBwWS3c2ZeiqT+0bwqRYvTaGhzYij0YkTEr92jNXAOwr1OqPIN4N4X7byl8sy5SIT/v+WtxlUrPlABUai2XWb3/Zet+XHUClVvX8s3/UHmHKTgy6YcmhZpDsBrfeS3KjvOIC4OGehtJSQ/mUjKWYFUh2IngVB5qLoEH4YMmLQIubeNW8AmInkt5EXGfgUSyFqgoxOgFfwCDRJV/74xiPiKYfmr/+rgM4PCPGQ+Yfk3gG7MD/Fm+6ZwM/bXmfBqeRZhkBLfix8Ttog+PF91B4sNYPo2Dc5d4/eBnXNbIYaReBVDKxNEMuQEJPHAn2C5yF84ro9/SbH02WZ4YtaXTmveCWCPWKrMkqsyvfH+oVU7+SCePZ9Zmj/MXHDXH5GRqO3AGZtUvU4JyYdEgkGG1ggMKRYNdP9YIOJF0hOQXyeuK9C+qAh0cjkT9yks107OR830AuJpfSwyxBzzXndXP6YStLjOKZspVm4c5e/1svLWr4bFuR5ePJNvWFXjepbnzaenEnFyN+LWSp09m6WvovD2wlzPCCGrWkIpForrPBwr2wmAYtN2jMHfqM6RPMX7lNAIh+AFXYxdNFAq0FdlxVvyiIIYolzxBglMElMXB5Y21J1AX5yt7GoVUNC7WlD1Kp5tW7TAekepqlFACqw7lkmHazcaHKi2GDgrJMHbglcKt2bCMe/Typ6oXmV+BVnKPy2HJ1luTt7mvyTPYWSksiWEE/gbOck1EthMedjRezAf6LhO2TtQnHNW6nEYtFpnL0dpD7rSmO5ZH3Tb0R5HcLwzHsAwDPHp3bNgu3j5ITvh66TPOCN7Bw+rqdKp+O98ilj+BxHpmxA3lyxVJbGAGFXmNXNzIxe19Ex+ja1nRzh2iPFMPlE5ueK7P8TjRaLjnwixmwPiW/NxXv5/NU3grEHTxbXN351AEkj52gF3WGyITJIRSAIjL44MfzqJrnOKBIJvoJ+nH+pPa68OAn/nbQ1Ie7+Ui1ZGEK0psyLvQM+xzcceHK8gxb4kfQG9vQ0mI7YeVar0DlUgh5FfClYeV6voOgW/hS1L9AuJJGsK6JfzpudViWEyqky9J+O9Q7Dc1sGa8LEFmoTrnf7PrM8HyuJf7nsD0CqKuQJHRUjbiau2haQtYzxABkK9LikOWF7BvUsunzPFsk51QCFfTlNKZqvkUOZSx1dSx0o+F69rqRr9UXVud01GV435Tvi+5W0RTwGxWuDtFdN7TvqYW6Jfban+UEmDnudhNvJr9Tda3GUPumfVis5w3kdmOrIVuvYCMaxSJVeQuglk7BNqsKi01NpuXWwKh27J9dZtO7bJP9ARcdWYle0mY7yvHL2uaYyg42xo0drKzOC5DIOI17ZaQNjJOF5k2JB4nKNXtLikFR6er0ZbRyJzuTz+Raenr0nszVtGL9p/zW0umFipQVNGjmE2czf48PInEdyfvGCXic4u8bQZPIXQtvrH/bqe7798t/yvI7xqV9ia4iduwtNgK1a51rvgefrMzSYlI22GnbKCOgofKbLbELvhLntQqcwcfbLhDxr1Ygo/QFmkuRXhdTYTnFMludx6/kgkOzx3SCWgd06veQX8MWvik/BswfUPqj1fkvyw9+3zJdd36f5zdm37ykzk0VVC56VY5u2bU6LYcny/4O7vzZMt71r8qGSdgwtbwP2lRg91VLFppiNdI9N8Uz2iwBYhVcGuVoz7NcWkqN3XS2/3ocxeRae4EDi9HhhEVPN2+Xyj1fk8ww+B/IbN4acYi6LZWTu4YuELdGbX9lTDYcU6Y8VGPxD1paTU4EW0veVZtbqi7bVLodfMw/L+TEfr6o9mc/Ml31ipwAnt3dVdmLWFQGsCNDT3Yhdpc+3nd7K4y123y4RJli6fodsnGG1Wocv5cfNxla3lFgYnt4vYZdohJwcxcfB2zzi/8bRG4xHHt8c99kAPDw0piZbc7dxsScPqdfuAeprVB4bCkIlZrD83OW+4XNRnWWAfGAOkv2JQ6/r0pUzAwmqdmxiO8B/S3p48P7WtzPFakzgfzd/m1YfKaqu7cpKt7icME8lWJ1KD0ICoCWvA+9c7ow8Ksdsb3sOwtZQLt1/zDiEo8VeulkOOKsEvlZsNTnuAmIVmXsYaQNl5bxdiWy10JRlAzmXga7rAe5rN96Ia2i0NEY4gR9Yah0WGRsik7J+7RHPJSKSOiSqYNYvTw2+4UriIBGbFnQmlMZCGhhbM7bp2j2IMip7Ssh8uYwDJyUCChZkNo6SwuaRG4A6dBC8giBe22LQkUI0POt8vWoro9y79HHlKp86q3XwbRc3gBLqo+MnSydbp6ItFSWa7Pwtef7CNxSrOOPG1DvrT+wJip03OS92MbLAbBcCRZc+NnfVbRcgVJrBDOf9vCYULdcMb0YbDJhkdBQPMlI1ipsIo1dAeGQbCpxx7xExZU7w/s0L+6gWmt6/uHTK7q3MK0qd4St1DGm9/x0lFJdz60UTZ4NjHclNbrFwpheacEuputXjsPhA9qQYAhIOM78vIdVQQFn9H3DnDQHdbEN4XSFu+UL4fbku/dxYtpgjVrTTJ+9EYHjOdc5mosbRnQZ6sr+uHCVmyDdkdZVa64DhpeK4zgYRqovrDAFt2ihB/QWWlp/jNRc9d7c+QS5r5ns9SWijxnnkoMM4a4hgXaPh3eTNyqEV7uMdTPyjv1p2yWGO7k0cCaIaOwmH0Kp1+m9AuMmnW/ptt6XJ4qoT0C9aZ9bbD9B+1Tj8/scgaAIvoYhUs6r5joRtx4MteSyLy9Wvp+WTSAXCCpKGWh173ttJwKvAy4bGYTmpo/6hVuaj8478fh55bTRsu115NmuvQdknPnPP/zez4DrLg4ici+Ds9cax+jKsrHghxgE/2o7YNAqGpRTf08F9mydXeHE70DukH7FzhERYCcd5AG0q2Z/+lsjsYKluaedD5Jppu0zlGMK7rvTuY3wJ6AKBI/pH1xTck88Xr8OmYvTUQyT221fdm+xf+QZn9KjnvNWzKqg31ugKijCvMq73/WFr/JMjUUR1uW4+rNvD9H1xBvO+idLFHBO73AMYYxvIN89Npwv9wvLDbs3yBmRrmHotO7rXK0aXARd1JhZW/cjO6xzBKdeBffCIHwXdz+ATUGJT3rLztdPs62GLeMs8qiW7HvsemEr9eI2H94sxjZcgyUOfS5NxLNV4NP5IWYRfIHJ6siFfW02u2ALpjs1umzg+evcLgPbO/i+stNzfC/oLcz1r+3djc+bbb/n+OwP3YDnIl9DDo5hpLVZwLneJc4aXNM9ryL3mvj+WdWrUO9eK/2hfJrU76SQBB8ZAsfKQEazWPYUmuIqmm4sq2fV/ADaG6sv/82urkiuqGMgTupd4yKwUPeNzyAwFJr3mHo/lxsA1v8BJ4DYfz7Rd1KdFrldsoQvQXcu7Cckx92UNM0wbcvXbpK0igJtcREII1A+i3IdYnvHmTH/TXyg1QPhI3GkhRRQ6CCrf/SzlINXyvrRzmqp660/hVEdhVFNJM0VE+GZ0ep3xwMLRJwFNew1gPp9eK0XYDXy2hRIOIK1swnUdfjV011mCZ+T7LjXo9XO3ests2avcDun4bnYK5ERK9sTOWqRvfO6Jm/KkWtL2nO1WjS+ozsL/jZK/jH/FTJI+eSnf4ukIxv/uyT9z5Aztz+PpdlT3fTTDHuqf6Q/n7SU6e5xO4PWNbe1W03rGie3rkHftZmmdc3YvgCZSNAXQIExPTdGEheoG4EkDPKZ337LLes6StTC+f/yL21rVP/81g3qGvWc+eqNq9eFrwAx/YeojB6NL4LX676k1+/Ca8VX9Dp3fusPb1qvnj9/9Q/DYRAMD+ov8zyz4PW7Z+hVgtfVp+k15yUCE2O4pFvlkEp7XOyi+cxr+t4zdPPQ1hzcFizN79mQY1FtPZvKLGpuZBNMPEdk9ILw6/Q6kZTIzYBsVDLaAo1Q/NIRbrCn5jatxC+wt+/bH57YtDJa/i7+9uufN3Anl3AeHm7zXNGggqJkZE+BH+q4d5iU3D9gr+j7fObBCh05NSr4/ekPE4l4BRnahPECJUdjHSbX/BWSi8jwJoxX6Tga6zH5z6jZnc4NcRypSg6OckA7zwMQYUvjcEb2ePROAzge8m45kBLBZ6yvaBFIN1VgICOvkwxdx9i0okHr1i0nyGwwpAzldsH6PgRzFOUJ7zIM8qH//o/cXHhM+CKyr9qCtju8FEbEUPRtp4k4h+gDv/WGmyLjx1vNj6Z/aUaNsI8t92jlc4fKufBf7tbKS7TyeVp5gVZexBYa3gjvpLefy/0TvGWstpIFoGMuBn2rdbNaRQsUsEAD2vQCQwnMaxocU/zVyAY0RLyqf9CoWkz7Rvad6EsPjcDQi03RCvIp4x0ms09t533Jjj3w5ZheB/URwy1zC7fgRusImodYSxDtMzf+wWpW51f0peR/6yRfa8OUi22+hwtZgpbFNmNjmTZZ48P3QAq+h5LwjZ4ag/igvtCE74FvgC/2e6tZHcD35KFx4HsgDb6HzoIPVihWvgIXqeIjxYni47g4tC3sEOhuw/JV7IchZPCo6Df06apbYrsG3s4tLfLg9PGIxSflgXCurLrdqguPFE7Lp9uOdeTKMFfaDmP8gz8jwNz1haweOwVI1STSr9vGCpzIf31fp/v/3JfpzwDf9wHrGsp9gLvmDI71/8H0kZyvDQNZaj2ty3SLUYNblF9WL0NTHIokU3pl2B4r9wyXF/ADmXJ1QmSgTH45/F+xo2wAiHJgMB2+B9L9LRZnwscv18UoL8i+3LGVzsCxj4LDKz3FCfaJtlHSNjq0jQVvva1tLMJTnRvYEjRlYk0r6GynexU6EUU+kNhujQxBB97NRW9W2Ptlv+XXFDGo+Wx6CbLgfTDQ8iv23v0wDQuHBkZzH6TTGDSPPjUSp4BSOoXj6EXdI51zwyazCNU4pTtxD9LW1iGWPoJyV1uI1a4y9TPeUKk1fDErL3kwe2ga1FbaaGvzdOSUVoltGMClqIKNYiNYFxt8ENF0P9W2t2OKTDuc9hcpMGJR5LR1o51MYlNeAHSeE61IPFiP+qOer2lV6Mulu3tEraoIr+1BBEnxfDQTaBTpBvm6esjsNzIf407mxIvZKOqJuldhUIcBrvNFpcVSh1ZbE6v28B3S8P5j+2MrPQY6wja2VNCWFLGlorakAAssKcECS+bBu1zrC4vwS66tUYvYvkkvq2sj/YnIkYTZUBLFPO8wzxv+veYtg/aO7tezj1gtyLUDDcNLPTD4qVaDAvpuVEMvJWrVxYIOrdFd3J/CDvmmmtPFOHQz6UnkcWigyuLjxz4KAEEFgZ5WStpKh7YS6Wkl0dPFyGydjSgqyKftvajALfSuQupgR2HICPj41YBsQG/JIztRw5Frf2zAmt3P73XHYRk5zTGNClw03mOnU1jG3qBZzdJ8dmjSYTUX16mzcc2qBRhMjuKenTvJGSv38Lqiw+sKejYusLCgpDWWsGqHVjVPnaY1GbgbOmTiLjkUQYccqFE9JGe+Mmmf2hkZTEQOJUyIqEf4LSjJgbThwEbCqYpvPpQ5KOljkQae4/C6jKExzwDFsUMjZpyHOvgQ8cBa7liTs/jDmNfDjsG0f2OEILwZ/ndoNxdoNxdxKz8Py4ZRCsAo7ZMPhO1pVTtQurl9VXJCO1AHGS/teWEnn5wiyINpI+bAEXtFv4Z29uHnCE+3Iw9xsn0Df8rNfk0+oD6KEj67TP0XtngFHnQUH4/0W6f9Tv5dx51teTLsPOyR24mhUAGzzdLLwkdLrnepv0MKQN5IhyWxgAc6aEJTLqjyYZ0cchysXDysx79zD84ae+8cvJaOz5yzqo31bHBZ1Nfjv0oW1LyS5i1Ae/ZACSt3sJfZoWZ07al1aQG3MQgOA+fozxAZFcJ4wYZgf9Zqf7aOLq3aBS/JS6t20aVVsAJGRrPD+Wk5IUPWmAxZsOsbUxW324Yky9n22jgTaVJUCI32ZwsDbL0YbGSnFNq7Vrrd+nLUpFZI7ec0a+tt2npnGhFFbQXywY565ney221o34rnufDHWoOHpVloViJpfmfUUZD9JTwKP9Vut8mft89AA0iSSBX9axCkoRp2OJ4dDVjlP7a/RIe86x0gHHehPr1CbMRbgOsYotypHyAJPvtjea1b6lgO7VF4BujqpGxoNFgX2SsE9M59Vgv0BZuJ2q6IOq6wNrgLCgcw1tgXZFa8p/1cisCEMNTrG6hO5MHZHwMYIaust/8yfbKk46vOcMBxsg6B3SK2CMXHAxQPqhn+t+mXQ11ytdQuabc4tVtspgko4MonyAc65t/D4Y0qgjXofB7W/UThIfhkXWrLfj+q5gqRr4X2qbjtaIF+vA1LBHwEmJZY5QPtu1O1Zd4/GCP/4eFzuSkRj4sII00ORzjwzCf2bJhtCU/B8RkwfqmfD5r29cz8jPatA/yXetLwhzF/54LAqomDbGrPbZB3JlvEC3nYYeNV/VyD7V2dQN+nMlHOC0/ScKuHCerHRiNZWuYWFeqXqESZWeN5RhN2iu8Lk4d+qiexcV4ZbO9FeZGYXv1HZrUwiRX9TmY1rj9Df3OBLQCJ1aO1iczT0z0b/YACAmsTtFaBLRSa5DoBaioXNElbICC7WiTIU8N5mtVMwOiYxqtRX1aAtYraVfD4hvpsWJ8ipiqsEzFNTKZB7ebrGH+HcnE+qoHbZlJYe/3Fu0gcCz2FfoZLd1stZX6oB7+RDbpWJQDKrzou7wpLWgu+a3MABVpIjM8ugWmtTtaAEQlyVvgcbU58CqTjrwUiwNwiov3InpIbXPa++/C2qyCNv4JdkWfY+0gAaRdLmlzh/L0LXNa9XpcVv9YLW29wsTIB/h+pxWBBUNu1bBdsZdhVWis8SppmQ/VegbUKWpvAbhVkrxDOARzFp0CSnBsWtBlxwJmoZaELkCJg7ama6YVdxbpF7Vp4lDRjbUGB3SZo3QLbIMhBHK8OASqg81T4IAeRGDpETCIHyWvw7dfkCP434d+GzhdZ4XkAvsTaRM0Dj28G347ge0X8IcaztBnaAvGbOwDUdp12GzzG7UAOdADQAaDPBHRcA+gA6Gdge4qAI9KrktsDQ3tIso3VClbuhS3q8gxjEeRH+LGnc7alkY2oeaHdSCbhXVaLP8COBtEPFldsAAIs/dP9flSOTKJZmsNuF+NO4KtYSBXYqfgk4sedojwYvqln02wLWy8AwMDeqoTSZQhqpxCfVHoBwHkdwNktspUCmyQDjwpPx+xQx974xKD+nxQhTtCy8Tseg/rFcBtlmMD2ahVi/F+C+s1GHvgVRKu5SZooV4hhgZ2In0dNt/KmtevYYgp448dJgnZB1yMg5YizxULpuQCLFWCBibAYo+Pc5Xfd5XNtVVxbF6OxmPS0tWQZUDWegEFZeYNg78XbjZG+S5rhwxt0ZZ88Gv4+SCA9nS7gKFuXuQLsANCIRd+PqiEv4SfcxiQYDpDcfCJKD838L2S/waVA9jLI/j7PfletayvA0ATjD9zmAGTQe+BL/Faqf2pa/TuwQC5VPw0yY/0XMKp2JlaIs/IMaxfk2wR7H8ZTjX+bf52a1ujFVEeqTclociWkb212cd7Rs8WK+xBAeHPTcgw27dOqRGYYNWviyuvR8YtWM4mQf4x9gRGYRRTB3kMR6uqgPm8L8R/kc+yM+g5UlMmyTHt9mx+KVyC1IpUF2ImnrMGtAEX4+rsaJVZlY5/0HlEvjZVJw9dLfJ2awC9EyCru7+2339ePmXvxaHxi3BUrl4aXGdny2MSnrPgxPvEqygTrEBHyr9gZ3PxBGRmoQL4yfClrtNUHWqyolcYu/AYVfyJuxMS9ZYIVQEdDbIpX4dDd6AiLosYSG7RWZ5glwuqJ+7BAffx5fUGfiT2tpLkJarAY5TP1NTygg8CWCT23A44+w1DQIogr+r+hWHG1X/+yN4XBN9V3cC8BzAeeFnoVh6rJXxLAG0zJY2T0ivcmMa8QjN4khc/zA7QupcUa1I8h6EN8myWiEgI+yCXhwli1NLzSQt2w99kAuX4cWjcW+R9jigDpe4CUY1UWcziMSQFSn7+uBS3F9bYxZdKqD9fi5RyAfbc+/AVped2RAakRTXnXfkFqycvRbhSIGxdnPzto7701QfiGHliC+swxVTdGqyXcqV3BC/uTtb/5BdltuoEFqw60LMfYqBPTm1hKxEBNHAeE8x5DE8+MZjbRYvGTyQOUX/g10QUwPdTbiEaGjPucVYwHa4tZY06UenziYBq/pbvVPoFxwVkki+FZ8iEQhw7qn1LAWoFqtmli0/WI55fVdQgfOxyuhZWd5vz5bB+z0ttklG+MHyDfQHXxAuD49G2Wob+QfWLYzvbhR1iwKOcHKMPWQ29E7M3pU1zNDgzZEb43re30+C4F7JT+vTvwwAHdmgT5hDoX1QZTcOcIsstSZNjONZrXVR/1SkpkaHJQqxX1E8YtXkakFyEV6YW8FM79s3W8KC+//bPVMpY/sEYx8oHTQBtnEUE2CqhIxLKSDCEHcB2HBYlNpPn9Z7lbUG1Idefx79fEskh9ElsB0/ZgMg7HeUBZSpA=
*/