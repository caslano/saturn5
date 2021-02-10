/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_TAG_OF_09262006_1900)
#define BOOST_FUSION_TAG_OF_09262006_1900

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of_fwd.hpp>

namespace boost { namespace tuples
{
    struct null_type;
    
    template <
        class T0, class T1, class T2, class T3, class T4, 
        class T5, class T6, class T7, class T8, class T9
    >
    class tuple;

    template <class Head, class Tail>
    struct cons;
}}
    
namespace boost { namespace fusion 
{
    struct boost_tuple_tag;
    struct fusion_sequence_tag;

    namespace traits
    {
        template <
            class T0, class T1, class T2, class T3, class T4, 
            class T5, class T6, class T7, class T8, class T9
        >
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct tag_of<tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>, void >
#else
        struct tag_of<tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
#endif
        {
            typedef boost_tuple_tag type;
        };

        template <class Head, class Tail>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct tag_of<tuples::cons<Head, Tail>, void >
#else
        struct tag_of<tuples::cons<Head, Tail> >
#endif
        {
            typedef boost_tuple_tag type;
        };

        template <>
        struct tag_of<tuples::null_type>
        {
            typedef boost_tuple_tag type;
        };   
    }
}}

namespace boost { namespace mpl
{
    template<typename>
    struct sequence_tag;

    template <
        class T0, class T1, class T2, class T3, class T4,
        class T5, class T6, class T7, class T8, class T9
    >
    struct sequence_tag<tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <
        class T0, class T1, class T2, class T3, class T4,
        class T5, class T6, class T7, class T8, class T9
    >
    struct sequence_tag<
        tuples::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> const
    >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <class Head, class Tail>
    struct sequence_tag<tuples::cons<Head, Tail> >
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <class Head, class Tail>
    struct sequence_tag<tuples::cons<Head, Tail> const>
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <>
    struct sequence_tag<tuples::null_type>
    {
        typedef fusion::fusion_sequence_tag type;
    };

    template <>
    struct sequence_tag<tuples::null_type const>
    {
        typedef fusion::fusion_sequence_tag type;
    };
}}

#endif

/* tag_of.hpp
h6p4AbKlOStRA7BBdWhjY1l6T2tIF5E7OdpbltF4ADbE9J+OoY7QBdv3Gb954sb6kHZ8h+5fUWw/ZRuGng+kRR2OiRUcQRuuhiGDhXyhtO2r0C3QfMYBwrGhgJRYuMZQelMPHmPMTWNiz5SUqE7oOVXr1sb5pmlI4mgkVAdqflaAhH0ZqtfvD+0jezydc2fup0Yw9/1+I4rDNJyFfmI4da1tD7D3NOmCK57zWvZW7l/OVeS7ht2UxiCMXtG/P5INa5iaoAZYOdGbe/CvAV+rSm88qAkXC8ztlKS3BDuX2jlfT01EetH98UEiDpLwXW7bc0RXlJX4Lt8H/ZuS5oKqwRtvdkjB6YpqXQ+M7MLnNSVN125f/WfYJeu5dj45nu988HwvXRhOUQz/Ysf220P7XW8Qu+k8DuCT489dI6YoB5zfOkE3Cy+BDWN4VKWeuF3bcoGNZI1G8+AyCK+DLOybVDugMC2cnMYIMk+z8Dy7cq/CeDHioeI2RMtNdmXJcoY9BxUlLbYayemgLTNxXXD8JMQ59iH+5imBiU2DnD17FlsD439QSwMECgAAAAgALWdKUpqD0RWVBAAATQoAADQACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1RMU0FV
*/