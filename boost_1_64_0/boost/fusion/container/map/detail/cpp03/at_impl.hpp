/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Brandon Kohn

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP)
#define BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template <typename Tag>
        struct at_impl;

        template <>
        struct at_impl<map_tag>
        {
            template <typename Sequence, typename N>
            struct apply
            {
                typedef typename
                    mpl::at<typename Sequence::storage_type::types, N>::type
                element;
                typedef typename detail::ref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& m)
                {
                    return m.get_data().at_impl(N());
                }
            };

            template <typename Sequence, typename N>
            struct apply<Sequence const, N>
            {
                typedef typename
                    mpl::at<typename Sequence::storage_type::types, N>::type
                element;
                typedef typename detail::cref_result<element>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence const& m)
                {
                    return m.get_data().at_impl(N());
                }
            };
        };
    }
}}

#endif //BOOST_FUSION_MAP_DETAIL_AT_IMPL_HPP

/* at_impl.hpp
xgCcgyPxdYkn1UXqPaU+1EP6SSZJ/8cP5XtnLTbHj7AtZkt5b8L+RZ558QjmYCxulfL4GFNxG6bhdnwNP8F/4i78EHdjNu7BbbgXD+DneBFzUfk8foGVcD964pfYAr/CrngIB+NhfASP4Bg8ihPwGCbicXwRv8Y5eALfxVP4IZ7GbDyD98izLlriOQzA8zgY/4XD8TscjRfQgPn4FH6P0/EHfBN/wkV4yfq7X+pccZSN4/wt2Z8ZWB8XYXN8G9viYuyPS3AoLsNQzETz503qVbGl6XtB+3n7XLVcqizXuITlshyM76KDy+n33ng5Zez1nN7upvGU8lDXh2d9E/wJoYRkwlzCekIeQdfXvcRxl/z6ut+WsZeCidcy/tKBjuVv+xhMntvc/qPjMHlnlm4sJnvjMMWxHUXHYjJQltMImYS9hHxClX6Mo00IIRgJswnZhPMEt/7uOl9CECGOMIuQRThMuEbwCeTZ8AQjYRZhDeEA4RrB+353XXdCBCGZsICQQzhPcHuAcaAIgYQYwizCSkIu4TKh5gCOJUIYYRphJeHAAOf9wc7JOTkn5+ScnJNzck7OyTk5J91/aPy/+EfpZBaWNDo8ITFSGQXg1sYAUO7RT6MiIsZ0XzpRKl2H46JN8+/0oP7srnLUy5v6u4fHxxpM96jPVD0vIEjqme6Sev+qhG+Iz2OZuX/3oP73D+pr6n42ZGgvneN9E9c2M/V30/SPzZK0fKS/ZyPC3aSlL5aWIXpM5MQ4U5ql7FPqLffcjyBUl/aFGeQlQpNGQvSjsYlJ0QlKAiX3v7X0qfusRvFtmi3p9ZJt6k74lG3KtZ0eoz46nqa3Kk3Nfa1yb39DQmWpvz2plGOmOs3EUu8zS1q1pT/pJ6Z9qBxT46KTYrR9nWeVs1PO2jxo96UD9wbYL2smt+LPtthPmrmaNCfGq/euI32S5f4XS5raPpKSZkPZv3UtfaDNfYnMn2bSVO9hR9O19HHL5RjqWos4Xe5O+lfzZUvfr565sef+oz/o8u31ybLXl83eeJG3v4+bnfEx7fR9szd+pb2+b/bGG7XXh85enzV7fQPt9a2z12fNXp87e33fSt8Xr7R94uz0hbTTR89en0r7434eMpi2t9xV1xUz7m69rFXKvRsHHP665OcfmL5H5Pslw7X4c8vLYwBWxV4o68l3AsvaWK+LtPF1xUbYTdUmEyHrjZD11G0y9aQOvz42RC8cjI0wBL0lHn9CrsTTS+JxQz+Jp6mk3wz12By7o691fTkXY0Mb6/eVNqV+6In9sQEGqrcj0/52tJTt8JPtaCXboZftaKsqx1yJx9dGOXpIPNWwKVZXrcf5TfJffL1asv21sS7WwRwWmB1EnWuQu0PPW7A1jquM4WoauzVbM26r9jmfaTd+1qeM1cr8CcTH67Ae2md/biePdp7/qRmjtQMhhJDH8tcIPgN55qg8G3QuylisxZ4RmifPCdUF8D56o7Q/MP6q/WeGZhZ/bqiMv2r7+aEBA2WcVb1lnFV7zxMtNraqjKuqfr4ogfjy9ZbxVNVjqaqeM9H7xm0cgb2JD+OI6wymoYytqm73sI6xuj6ZPLGMelzVTH152kNIXylvPNNb+4zS4D4lP6fUo2/hs0r7oDyvVD3GqrVNJY90VOOs2n2GacwT5H8QbRAEe88zTWOedpzV4s839eJ1OvpjCMEyhmo24ZqN8VMLsABrBhZtr0HmSXsN46XKWKnyHFQZK5U2HLblSdIi30mEBYQcwnmC+2DacQghg53tJM7JOf2V1/+R8QalAuCWrv/ryfV/qPn6nyilAoDJUgfgaaMOYKqqDiDYRh3AceLMW1ysDqDXoD6OX0/aqgNYY6c=
*/