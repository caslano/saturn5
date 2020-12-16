/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_DEREF_DATA_IMPL_HPP
#define BOOST_FUSION_VIEW_REVERSE_VIEW_DETAIL_DEREF_DATA_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/deref_data.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_data_impl;

    template <>
    struct deref_data_impl<reverse_view_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::deref_data<typename It::first_type>::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::deref_data(it.first);
            }
        };
    };
}}}

#endif

/* deref_data_impl.hpp
2jDT5Ty5iuZuirgXDzQ3aPzQ2jJ7vH3uGhqHxnhGYfapx8EF1J9ouZilrbI7IAyamKEhs1qBXTuoTLQGzLoNyFydckcrxazq0pnTqK+bhrZld93Gv1F/ohXSSNNPSBhMfdbcDHdA2tscWag+W4vQPquRoVoTmkto8cw6dB5F88zaMrSdLV8Pr035oWVhxvdIN1ohZnyv86uYoZWZPn//Di285833lENrMxzQSku4X3oM7T2JeHYDabrPL2pQW9qF2t4xF8rTftbeDKuZ5Yha1IvmdYdQy3S1rovmYEczrGA2sMDDUpRDEl77mdkb/0ZletBaa6QtT37SmurrbIZ/mL37ftlnmi9dzFAZpM3fmaUQ9UtXnNcs7vsRafbQnO8m74Hyos0d8G6SMEd3M1g10hZ9GSyvOT3oeosWer019DTDj8wKdnVlpzmB1oyZ/JstzAFtCLOsmc/3pHHohXOCmf7SF2qnDy2J2eq7u2jd2p1mmMKs69skee1HO8fs4195/xMGfcwwjVmjy793pPrQTjA7f336KrK+eJ3muffc1IbKTA6N85d/+oCsX+pxdjQHz103/CatTbRDzLQVZl8i62+GknyMKv4WpNzRYrnVqdCI5ssAM1RitmDdfuoXF9pLZm9s3d5QfQNTzyGIplcsH9qI0zXkvjQIr8XM6H1yaLYUNjayVX2an2h2jbShCdH3aS4NNkNNZr/u2deDchhqhvLMSkz8fS21ZbhyfVCshs02hcYBLQ+z7UvGHqB5ncLi7sevpzWNplEsf4r7FS9aWsUKoG3eu/k6zSU0PbPMK0utpPzQcjCb3Sl3H8phhBl0zOi99WhWtB7MKi7+oRK1Ba0Js4POCV0pzoX3olpplrHT5bVjtBkua6Q5sm3LQ309xgyJIC02YX6EMBhrhvbMfks3Tcah1WCWY26DGpQ7Wk9m28rdGE/jMM4Mo5l1L/TDXMphPO4hzPh1JRGtFDP6uzM0r4rBBBx3Zvysb0NLrT6ninlVLIgWy4zfB9gmqtSnYl601HIIoGVhxq/hMCn1Mu1oqbXThTZIsYJojXZ3X0JjNBnP7MwyXLmzldY72iNu98pPovym4FphRu/6QHOjhWukJUUtbEr5TTVDHEgbXyEuSDlMC21nn8XWWIpLYSWLfqQyXW7cQ5jRuzDQvGgxzCpZR8vrEVo8M37/njgdr0fMbtu3DKM+mxFaX5XojL2oz9A+MPuq6bGC+uVXHHdmfNx9aLHM+PjBTJl7DFoDsGenvQ6tADM+fn40vTT23R/MHS2OGR8Hx6zQ+hp1KLKF4tCimdE7UNCss0PjMl36+wzlhxbDjI8DzOFl8v7cGGabI3OI1WyU3+1Fc6DlY/bLjucjhbnQmjNbmHlsIWFBtDhpLHcscy62hZl85wqWicbLnLxiTDoqEy1GGssPc5gXWibPL3Ge7LPv0RbM6V5UGMzHsZXGxhbLRNMzk+/AxBzQ4pjx/LxovL597ccfobgFofb5omM35YcWzYzeLYlmXYi5M+O5J6LxOJ67e6HMoRCa/B4gthMtHzM+tgG05sx2jC98l3JYhLlLC80dLZqZfL8NlonGy1xZodhnKnMx5seM5+dG42Xy/HyLZX6F0eR31rE+tHzMeH6G37AtzA7UmXqY5iBaHDOeXwAtmpl8dxGW6Qktc9M/U+5TmWgxzHh+PjReJs8v6JHzpQiac9qlTNQvS3DuMuNz14emZybfg4U5oMUx4/nZl4bW9+m3R20pLoXtKVYxD+W3DHNgRu+CQvOixTDjuQfRpjGb2OWX1xS3nJcZ2i+B5TK/omj0XVQ0WIHjzoyPuw2tObMFq59YhXnQ4pjxfoGV2BZm8v1SWCY=
*/