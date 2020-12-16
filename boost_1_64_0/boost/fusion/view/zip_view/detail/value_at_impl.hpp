/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_IMPL_20060124_2129)
#define FUSION_VALUE_AT_IMPL_20060124_2129

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/config.hpp>

namespace boost { namespace fusion {
    
    struct zip_view_tag;

    namespace detail
    {
        template<typename N>
        struct poly_value_at
        {
            template<typename T>
            struct result;

            template<typename N1, typename Seq>
            struct result<poly_value_at<N1>(Seq)>
                : mpl::eval_if<is_same<Seq, unused_type const&>,
                               mpl::identity<unused_type>,
                               result_of::value_at<typename remove_reference<Seq>::type, N> >
            {};

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename Seq>
            BOOST_FUSION_GPU_ENABLED
            typename result<poly_value_at(Seq)>::type
            operator()(Seq&&) const;
#endif
        };
    }
    
    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<zip_view_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename result_of::transform<
                    typename Sequence::sequences, 
                    detail::poly_value_at<N> >::type values;
                typedef typename result_of::as_vector<values>::type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
POujXbpS79L6BFdGyxV2+GdrE1qBtHKaG5TLV3Mr9VETjKaWVqF1G7QAYf8WW5yIFiTtUcEPNK2wD83mxVPW0lY+KYoWK2yA9skrtARp8+etQUsEs2Xmr+hd+DoobKnfi91oycIGHV5L9yVN2MMNZXrT/MAcmUUYvdvT/ITF9+hAs80V5lLx4WSan7Cg5/Mpa5tv5r+7nZ2y5ByaCozXlehyo/C1FcyO2a37bZujBYo1k5uubEKzFWtWfn/eSLMF82U23DT3AVocmCuzlZYP9DSj/3Jx53Ex91scwKfVVFNN+7So7NEia1kbe/bs2bP0FKG0kD17sjQ8lkhkH2tFCKEnW7JljywhZB97CPfcco4z33tf95/7vuf7/Z7P+fX7/WbqPmB8fld+byihGYFZMvNR56xBSweTMcs4v+4qWg6YnJld28AcmgOYglnm/IUBlLVwzpM9XI9Qnj+096uuLO5JeYLxPJMPBmRTnmB8v52uHw+jBQh19WvotkYLEurCtlx8iRYn1H0vfkwzUgl1XZTLp1BmQt36/+oupsyEugtxetXR7oHxa+LLkhbBaCWCBW58NQ7ttWBtHcY8R/sk2GujI2/RygVbc2dRMpp+ubY1yx+4Ak0m2Puytr3RrAUb/mrFYJofGO99+B33RDQlmCmzXx5TN9D8wPTZmqeVuSq0QDApqytOON0ILRTMiZnLofFxND+h7v42ZzO0VMEahXspaLaCnR8xej3NFozPPaVPDXu0AsGGScwaohUL5tLAxh1NI1pCihWa5Ke2XRi6mq4JuWBSs2OdaA6CdfZLHYbmLVj1mGg/mpFgo9qH16YZCbatWeOzaEGCubsYBqNFCFbazb0HWpxgO2d4D6D5CZbrU9KU5ifYXMPf9Wl+gl012OlI8xMsq98JyqxAMK9mDtVofoKlurjNofkJZjD98USa3y/tz7fJ7V7RmnLBAuVnjWl+gtW/88WI5ifY64Si6jQ/wX5faVKP5ieYZEBuM5qfYKf031nS/ATbphqnS/MT7OySdrdofoI1s848Q/MTbGjS2Ms0P8FaPQxsT/MT7MCN8Hc0P8HeSBTjaX6CefVp0pHmJ5hh8tXjNL/f2nYmr3w1zU8w3fZXLtL8BPt5z/chzU+w1ok2n2h+gnl0DR1K8xPsnaLDJJqfYPeOHJtD8xOsRrVuy2l+gmUNNHxD8xPsUnzYZ5qfYA3l65/R/ASLyfk9neYnWEKgNJzmJ1j95z45ND/BCmblXKf5gdkxu2xXbwrNSGKgZd1inLrSHARb/GSoPmUtWP61jlUpT8GMZoc1pcwE80+PqE+5CLZwT6maehfsbMrHDOoPTMGsz8cnW6g/HW2zzC07Sv0JdnX5TZp7ABjPs2zmuPFoQWCWzM6lq7PRYsHMmdWZ2OU19Q7Ge1h9R9mXegez4HWNG1qh5YE5MDtlb2WOVgpmxizcrqAJWhkYfw9RLZpujybR1a5Tz14+lTID43UDXFr1R1OA8XM2LSjrR3kKtmvH6C9o/oK5x9+tSXmKZqw7jfIUbP2NLqGUp2CHZ2woRFMLJtly6wJajthDb1djtELBZi8Jpcw0gjmt2RyIJtXTtt2dX3ZFcxUsrrj1DzRfwXxaTypFCxBM50pcXbRQwQ5Z5DVHiwOzZDb2m/41tCTBktdYLkRLFyzyqLM7Wp5gc29IZ6IVC/bqcFQGWplgDneCS9Dk+tpWo+1ZPTQ3wa55FNA1qBSshc6972iBguWH56ehRQi2WZYRhBYvWJ+RO5qgpYLxrLe6RVuiZQlm9aWlDlqBYL7DSymXUsESZ6duRpMYaNuRiP6j0BSCme1zjkDzAOPfBe2zmzcLzRfMkdUFSyzmU2Y=
*/