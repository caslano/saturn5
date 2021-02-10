/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BACK_09162005_0350)
#define FUSION_BACK_09162005_0350

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/iterator/prior.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct fusion_sequence_tag;

    namespace result_of
    {
        template <typename Sequence>
        struct back
            : result_of::deref<typename result_of::prior<typename result_of::end<Sequence>::type>::type>
        {};
    }
    
    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::back<Sequence>::type
    back(Sequence& seq)
    {
        return *fusion::prior(fusion::end(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::back<Sequence const>::type
    back(Sequence const& seq)
    {
        return *fusion::prior(fusion::end(seq));
    }
}}

#endif

/* back.hpp
cnmvn6flYWAaaCR4tyz1IKH0JnyahYaFVuK2UM5wWt6gClB+7uXVYfKvSgVk2M1VsuMaQeKVU3qrDaQGwkaPkFuGjAw75qm6CT/3OZwL/RkMrAMj+92zdrr52MsUkvgbzdzF2Rho6dHrUDSAlYothqrEFUbQzL/RryEkFGvvSqN+dCamvsnuZGfZqCOL2qnleNDzMW/3KfK6pQrQOSMvHwaciHtFbT+sSbDagJbYT/IqoxJpGp8E32h2LBquPZCggJreNzoU7RuViq1vqBJX3xCacXIXi0LrEe0Ezhapj61Kj+peySJ1W2qDZjOkCB129OSzL+2s5Z9xC4tOKNbU9ZykFUlXz0hUQYXGozDWPFaYy1+l0byaYGM3MnQ0aMlxT1pcif+cMJuZ9Rk5tT2b7s+jrRn0GbkznjWfmy+Xeuxe37/KMD47VDrW6UEVOeeHiFNfvKsz0yZcCXcWn8beQLznEKV6ESQJ3sMarRijx0720ItgHyc25hq7EzjY5iGF7XjC1uz15jEMjDc2LFJHCaxHHGcdbqDHGmcdaHRKECM21UMgizALDFIJxW8J4FukarMcUPHkveJPEZzJ5xS1wB3btErxjoajMTMNVDhW32la7h7alzirZEqpCaJi7lgbo8xPoafmTNyvSoZk
*/