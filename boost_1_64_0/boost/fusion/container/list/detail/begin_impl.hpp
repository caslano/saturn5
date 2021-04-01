/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_07172005_0824)
#define FUSION_BEGIN_IMPL_07172005_0824

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    struct cons_tag;

    template <typename Car, typename Cdr>
    struct cons;

    template <typename Cons>
    struct cons_iterator;

    namespace extension
    {
        template <typename Tag>
        struct begin_impl;

        template <>
        struct begin_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef cons_iterator<Sequence> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& t)
                {
                    return type(t);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
lDJr/GM3C7wmZPP+h898+Fpc7aVaGQqWSu3eSNtkMqQ/3Civocq2zxBUqgiG3KLM88QKlflp2I+U9odAIDbtLZpKcxzctojzcDFU52xzKPEDA10oVXtS19CZZwnbdwQ2qFoTNBQUiEKIZUKRdEwtnrhcCvFml/eVDt5ksaJWIGZ7JAiUyNjNqMzSG+/j/I25CUJMYZHpKxBsEGJ5j0N0WxaK+7iC4NqU8bp6+dBClGJdQr8BSk+EeiMji3vbMsMuSY8LF5DD4HKqSqKXk3shPvpXr70k4L6oYgbUlRvUfgqZJUDtAgwBejUrgWaBYiCGwGBtlmCLExQRt2lG8LgjKDT7bitesSnBOQoEaFVRPM275IGBg7HZvs8gLLl1ineR8raZ/0wk4ZD9qgbcL1uHshlniNqb4kgrYLzMwEbUT32WCqLcYVATudMEHPBT0QHGxj1mE8bN+yBS8y9ObimasXSiKvDtpnm2F3MiHdC1En6nGerDoj00giovlCFBfiHOe+8XqsQnh89zgYLQRu4ke6moDg/DJ0Ece3DsORgnIWNQODk6jPY2+QBGDg==
*/