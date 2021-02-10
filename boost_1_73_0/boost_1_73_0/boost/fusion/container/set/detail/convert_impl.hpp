/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_IMPL_09232005_1341)
#define FUSION_CONVERT_IMPL_09232005_1341

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/set/detail/as_set.hpp>
#include <boost/fusion/container/set/set.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion
{
    struct set_tag;

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<set_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef detail::as_set<result_of::size<Sequence>::value> gen;
                typedef typename gen::
                    template apply<typename result_of::begin<Sequence>::type>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return gen::call(fusion::begin(seq));
                }
            };
        };
    }
}}

#endif

/* convert_impl.hpp
R6wl4q7OpgSbHTYGubLXSRk0wX4qdo8SFEDtHaUqFYISMclKFfpJfW24KY/xYHpHVQD43zNg8J/IXBY/9A6/a30mD37WzACacNsKZMu2VZnFKb/PDzsUFrhVYLOBu9uv6riWrV03qrN4emKfyYIWliAfedjGG6Ji6fGW6Nie5TnoSPvaRRX7zsHtxAaxdoLAaomJBJyvjJGBE57y1gS1ATzVbI1Y81DAMPgUb4LImNHRineIjNX5Ter316MRG2v1M3tAq0or+Dz0J4HnOcAR0MpZ06DztbOjoEnLZiW40Vbaq9ykUob0j9YlSPHosDgxSbBqdYAOS1oBV7jkJXAFvDnEcIv8ZwXPFI3Hc2FB3MpyDRki+olhOUfhkmGpqJRRo49YFrYWXOocjofEDSKAR9wpg5jHbJT5tIkCiEN7+z4zDYhDafGCUqkuB6r0iCLHg8rZhKMNzFMQocWh1LO/GCaalAuiBhXIdOAmrjoo+byex+F2MdRydouD/opH91hHyNcOIWeOMlmc1nhso2Mbrjpro9nXpDXlJ3mR+UmQVFcKW7vgXLiDqUFduiLWsHe169168A7lz3yRcn8NswnxW54ptTPlYX3QxSOlLElFksa+kBIPA+YyX29kxuaiDNlqHKrl0B3AAQruja1r
*/