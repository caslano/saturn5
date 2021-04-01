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
y9knoVzZzO7JJSH6HTVsn2cR/WesN7mYIdMAk1Egt0posn6NcNPtaDV7tf8qFHo2WbwiL4G24bprdMCzjAMVNc9RuhDhoEG70q1kkDZqr3n8trQZ4BXXEuY4q7dgdY+KzfIaGphhb5XDToIw7NfjEw319+cqGdl8+UNfs4PyNodfeSFEvLt/CmYu1mkNkd/IHffkGmsYDv9xS30jnYCa6/cE/ehfnSpY3+S0UJeF0yCoeOYpeAHCu1L240MxV2pNw764oMd8H4w9WITSc8cCUGsJvpOCNty2ANFB+ywWdcmbzwMJguvClFNcpXTyF7lSLc3MKzyDgWwqA72f89GqtdHNZJxDPPtSkkW+tE7RA+ae4APE/vfGW/Tvu8jpFoZWSp/vesLnZi8+W2hnB8DOkpYs6KLof7VbT9YEGCbKdCSRTuklN5DFNnFH+uIrrk4Ok/iuqdC39Ueoes8vgFsOEfa6ty6itu4ll6TzN8LIOc3Slv2jGhBjlIks7PHQqx+WBIo5XKUNJe/OTdh7FW6EoF09p9giCZUilUKoJGAe60hWcC//JyGGLGkg3w==
*/