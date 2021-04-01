/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_NVIEW_VALUE_AT_IMPL_SEP_24_2009_0234PM)
#define BOOST_FUSION_NVIEW_VALUE_AT_IMPL_SEP_24_2009_0234PM

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>

namespace boost { namespace fusion 
{
    struct nview_tag;

    namespace extension
    {
        template<typename Tag>
        struct value_at_impl;

        template<>
        struct value_at_impl<nview_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename Sequence::sequence_type sequence_type;
                typedef typename Sequence::index_type index_type;

                typedef typename result_of::at<index_type, N>::type index;
                typedef typename result_of::at<sequence_type, index>::type type;
            };
        };
    }

}}

#endif

/* value_at_impl.hpp
DA9g1Vo+/f07INb9dKOrqxzVqtViByeMEfo0j98EZSR4WNL20M93jdqcg0Zr12BXbz5zXwo1t5iXPp5H4qBIUtt8CK3XIqVfRpusZSCnVXIVR6wOxh0qcDT3lUJ7Soko9r/C4p/IcwwIR5OKvg6wGXcQmDBrtuQnhRlOYO/aqq1rup49iHHsmvbUtl5GDZdPqAUWEczQdpNJwjEmlVZdauKB+EwWx8WdWYreQeSQy6+zq/Gv1LG7VxKjlMEKohTbgXmdTuw8nFCapWKz464JAgLm/cDwIOZz19nWA8vBB7dmcY41/pGil8BtnLFCqWAzyPnvcT6LU5tqrnt/895uGjptokgee7OsGVMjIcv9F5nStqqk0Kp6755kD+rgbo8Ft425OknD8kReV6/EL605PELfSx7Mag3a0FCk3VzVF2W3OXXgpNu/vaXM04vdjObGUvh3U19igQj3v5HR0fuWOnXxsk6lv+flBgDKdoLKMC1FXslTEORD2ct+irWh4VzTR1yYPHma0irZsDlaZaWdg84aHGkBZCoGg0hyXPSlIjmg1lf3XlyPVhAaFw==
*/