/*=============================================================================
    Copyright (c) 2006 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_IS_SEGMENTED_03202006_0015)
#define FUSION_IS_SEGMENTED_03202006_0015

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion 
{
    // Special tags:
    struct sequence_facade_tag;
    struct iterator_range_tag;

    namespace extension
    {
        template <typename Tag>
        struct is_segmented_impl
        {
            template <typename Sequence>
            struct apply
              : mpl::false_
            {};
        };

        template <>
        struct is_segmented_impl<sequence_facade_tag>
        {
            template <typename Sequence>
            struct apply : Sequence::is_segmented {};
        };

        template <>
        struct is_segmented_impl<iterator_range_tag>;
    }

    namespace traits
    {
        template <typename Sequence>
        struct is_segmented
          : mpl::bool_<
                (bool)extension::is_segmented_impl<typename traits::tag_of<Sequence>::type>::
                    template apply<Sequence>::type::value
            >
        {
        };
    }
}}

#endif

/* is_segmented.hpp
4TUTmSlsp8f2Nep7YIK91hdaycOiT7/FQmqw6lh6sZ3pkYuk7qRDdA2SBNCNwn2jC6QZ20YD+INlUj6G9QJBFtJTr9txpGMhmKKW00IS26yHL6qa6MOeNd53xpW36F+uMMvGHEQXQbXW/cpRdmV5N+z6VTDeE2OZ3K9aXltL6SvGk2cr01YnnZVYZ0k8py0RifU0O9Dex4yMw65CHJimVcZelizz2+Gb0f7AZTk1zefMrpmKTfU70oFh9Vgf+RViKWOkYpwn5a5eeRxwstvzlIjNOH3gGZe8XDKEBJbyw37zR0V7+56XUtlkZoD07lSeZAAFsJ9oDj331N5Hr65zdHHdVZhuVAHf2U1jXHGyE6hEQgzHarLGw4PfDPh6oOcGfngDtEEp43V1BUmfCtaoCPKhK6kJ8DvMTq5JQI9NpnX4gtr4Ldm+gnOZxaDqFh8PAqbiysgNqMT2kYiCQ7ldcwYZaduuFmPawiH8hkJftujO/UREFsLJfd5veX3hlGr+FcMBg2GoXjswtWIESP7RQ7RNnEYHq4IE2bdf0heLU8o3qfH1K00LApi4YA==
*/