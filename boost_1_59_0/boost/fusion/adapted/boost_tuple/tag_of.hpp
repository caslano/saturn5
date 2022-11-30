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
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
*/