/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_10022005_1442)
#define FUSION_CONVERT_10022005_1442

#include <boost/fusion/support/config.hpp>
#if BOOST_WORKAROUND(BOOST_GCC, < 30500)
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#define BOOST_FUSION_WA_GCC34(type1, type2) \
    boost::lazy_disable_if<boost::is_const<Sequence>, type1, type2>
#else
#define BOOST_FUSION_WA_GCC34(type1, type2) type1, type2
#endif

namespace boost { namespace fusion
{
    namespace extension
    {
        template <typename Tag>
        struct convert_impl;
    }

    namespace result_of
    {
        template <typename Tag, typename Sequence>
        struct convert
        {
            typedef typename
                extension::convert_impl<Tag>::template apply<Sequence>
            gen;

            typedef typename gen::type type;
        };
    }

    template <typename Tag, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename BOOST_FUSION_WA_GCC34(result_of::convert<Tag, Sequence>)::type
    convert(Sequence& seq)
    {
        typedef typename result_of::convert<Tag, Sequence>::gen gen;
        return gen::call(seq);
    }

    template <typename Tag, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::convert<Tag, Sequence const>::type
    convert(Sequence const& seq)
    {
        typedef typename result_of::convert<Tag, Sequence const>::gen gen;
        return gen::call(seq);
    }
}}

#undef BOOST_FUSION_WA_GCC34
#endif

/* convert.hpp
bN8bCLhgSeb9D7ro1thQvaxaEvB7ko5YCR0n7JG6IPLqnUXJTpKeXsaxBsEgHqDJPYDnacRn1i5tIc2O4VKztRXUz3vRzLgRxiVUlEi0So2YkNrOjReLUD4XnSQY5j9nU6IoS/Vby288KuGW5u/97fJFhL9LRIoDp0wPhmZ5WVM8bYNHERq1PAWN8bEJHrD8wA16LrImAwb4VJK4JtsgL4i7NY/tgDyOI2GaBuLOEhD1CakEHpHCL5dXUB1RRpCPXHiU2UMFra8MS6+NDIRMOisVSt6ujy8znK7EHyQ7TwMdeKXJycaLf2IO3WhBFNuv2OdbTPfKY7XhtL8fuEDvVak7spRJLqikn/74jLx7Wc/ysVSLSR966n3tLrEqVLiP9Fu3oNgRgZWrLuaczFLGw8C6pgbd/7AMsGh42s60DOZuUecCYmeoJ5ax67zieLiHBtrqhzSIpnaZxWmppee10Fz49D8ZuRxVWIveJJRsSo9AX0oc5FfUpPP1JnE13StoFzBnsxB7hi3s+nHX/1mSvQbDyqCdDEUe64eEFBoFqxPbtrxkczdP4eeuGA==
*/