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