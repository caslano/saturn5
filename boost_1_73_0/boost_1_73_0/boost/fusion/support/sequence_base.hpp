/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SEQUENCE_BASE_04182005_0737)
#define FUSION_SEQUENCE_BASE_04182005_0737

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end_fwd.hpp>

namespace boost { namespace fusion
{
    namespace detail
    {
        struct from_sequence_convertible_type
        {};
    }

    template <typename Sequence>
    struct sequence_base
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Sequence const&
        derived() const BOOST_NOEXCEPT
        {
            return static_cast<Sequence const&>(*this);
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        Sequence&
        derived() BOOST_NOEXCEPT
        {
            return static_cast<Sequence&>(*this);
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        operator detail::from_sequence_convertible_type() const BOOST_NOEXCEPT
        {
            return detail::from_sequence_convertible_type();
        }
    };

    struct fusion_sequence_tag;
}}

namespace boost { namespace mpl
{
    // Deliberately break mpl::begin, so it doesn't lie that a Fusion sequence
    // is not an MPL sequence by returning mpl::void_.
    // In other words: Fusion Sequences are always MPL Sequences, but they can
    // be incompletely defined.
    template<> struct begin_impl< boost::fusion::fusion_sequence_tag >;
}}

#endif

/* sequence_base.hpp
F0nFs2jyUPAtUJYVHWGBgGdkd7JgDMaHjmPJScKOGgxEPg8iBw5U6KOG5SSJ5ZC/E9yWptdGmu6fVY5vyS6M2eiyASY4dJJecAL097z35ury/es39Zy1nBDy7uOno421JFe6+g2C6w7foLMQvhcVmSQMhyUBN9bSk2mfvjL35DEP8oPCHcXsTBNctqVmPozQV9mMLOYt8lJG88nNX2O3Y3YDePWs3gK8aPFxZVvOgH1Wmgk6bTpaW9WLo7C11d3GFQ7XVwrb5WhD8S+jqsyMF2J+IB0wvRtmYkMdKBFY5pYfCv/fVAM/WlQ/t/5pqGDRQ4tqLWlA2QqRazit/NqBuLyCdt2gyrPvWjdpn3qtXYqC2UjZwEhoYqP1yoBhJcOGRl1gNjxSrTrNu68k7bQfTm3EzlUcPj/MImIBSk+5SYs4Bcx1ORI9cKO11HasYoTdgbnWJTYsEcwK84+W9CLsfT7SLHt+TpHlbw/sD+IGeD6LEtjscyC4WSatMG4kDFICBNlNwiCloW4GvSlo1IrKcWC7NHWNskaj4vHYtIolcmZAbY/L3s/qualKmJ3cCj280QAA8pR5zGc+OMUdT6YqBBoS8VUNaACeas3garp+zSCktK4YGA9tlRrYTzkYQmGQepAi1rWcNP+7/62k
*/