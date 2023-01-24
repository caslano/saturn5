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
ODJd48jX7yWOzG3LkYYNUmPHEr6LrE0YT3bT2ZFOLXA7JHSpTnc8d7ntbdy19sjDuiMYlkrcKcuhAMmgVGNa1eUmTFePzuMmECglJFBK+Ldd3kduwBCR6LJSXuu/nZyu2V7V/svzms53Mz1CRyvJnV/r65XbnboLrv3HaaDDFe8sPJ+Kkyee19jLG3js3ej0vAFrPIU2VJp1AEpl4dtaN63QtNayEs2Nwtxq8uH22nZjd+1v1FnFFPHJeq9d76wCCyobjdw/H8ZsVlyMJtJAfrktyjNrcTq56rAbiUfKiif4XkNUW1EeW4uDiXSU96I6yp1rcT7+loT8xs5QcR5Mr9OxTwt5gY3vGn0KHFleK5TXkmVnu4qzC0xLn6NCU8X9/jNH6bMSP6m5T6leS1GZy3mg1xP4wb8iiZJahaXvxtJVGoCozvyBSvuncH9HtCqROqOJQpivntO0xVu0ZEXolwFcf7kzt08s1+Ow0Xneie76tRKnZPXGeLPGz7i8RzoeBVkEQGl6EnSD8slbMXoS9ZWylj9qMBvdqqx6SyM2kgeJveJuIjKSr/2YaOVb0XpUzLokdlRgSNCWdqPib29ijiyPPMQiaaPC13pUmPmMXCJ3vSl/94xLs3fz737DgYvyZlI9HxVflO/xCWybaj+5ErqyKlxNTeKpDnslPCG/o0phES4w8bv80IxcudAcW+XbHVTpf0+rY45Rh28q
*/