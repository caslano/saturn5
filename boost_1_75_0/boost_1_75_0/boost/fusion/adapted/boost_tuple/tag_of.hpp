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
rCJ3WvM9NydaEOgal+Z21km0ilV2qLUHj2nYIY4k0/n6bHR9AgfJ6v5DxzQ/fHzDp4Qd26urS5kT41h0P6vXVdnKGCs639ihTkBGO5WtXCb7JiSptQeArSfY1Q3sx7pkbJU69dY3WjX8tOgzWYnnwajKWQQ7gvnopMbumNnkYAnZOmwy7yy7A1ozS2nBTmtyX+5iBaMn0O3q17iCPCXzgieIgseYCz6yslXDcjdTAYxVpm0y++OAWVSzvW9BV7Roomh7lV469D6rVJpiKv1iqkwxVaYY0uHFOQe7d7I4uGazzhZj1lmzUHdTizqkR5wpP7m8s/qwP4n9RbM/DdwLOnzzB4VlQu9mH1CP9m/TysHVYSYp7oBsjX/7FCi9L9jLhv8B4R1vLrebKE/mpo4zcS9oOMjL4OHj9XAJw3N4+FV6eB8ML+PhF1J4lu9JPPqBKDuP+gMWKXeI25Q8CIrB1IbD20IIPBEmAiWEaYK1OYQ36+F9MHwlD99D4XqRAgRsKwh476zD2b71dH4C9kiZg5JcwMwuJbuPS3FKILhRbu0fDiPLfTg7bYhUohtVPEOdcRk4nfc6dzsqCR1n8m41mm30WO4D8aAa5vWBWo4dUUyo2FaaecG2aRkYTaqjVseyBfkS3VSbTe6t2XBb5tSylD4wfCorYy3CuyKTgvvCSQoO5JPBF+EJWCJOsbf9hLLTzzFjez9sAfYxYjpa
*/