/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ENABLE_COMPARISON_09232005_1958)
#define FUSION_ENABLE_COMPARISON_09232005_1958

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>

namespace boost { namespace fusion { namespace traits
{
    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_equality
        : mpl::and_<traits::is_sequence<Seq1>, traits::is_sequence<Seq2> >
    {};

    template <typename Seq1, typename Seq2, typename Enable = void>
    struct enable_comparison
        : mpl::and_<
            traits::is_sequence<Seq1>, traits::is_sequence<Seq2>
          , mpl::equal_to<result_of::size<Seq1>, result_of::size<Seq2> >
        >
    {};
}}}

#endif

/* enable_comparison.hpp
OVrDlvuVLK6Z0EHf7UM16NHh58MOihvJ/AxnAqYPrkt4EL2yBYUDQPSSsKttBnM848MiROKGLN67V66JbKKULDM5uheaoWBa11tO8hJ3Y0/UAyF2kvubUyFeHJN5LGelNq9wnv8gRFgwmD51SBJSUI3kOzQSQh2hPUNccGeEwyhQ+XRYiOcTNdC4ssGQ91d/VhCQKUmx+L1c8mS73OjqwTCa3Sq8ouinP4oy6u58Efx7U53tEox+qO22Ko6TNa5/+ZALBttAixnagNd09mUGS4DqVugDcnWWViBJt8cE8ylPM6syqmi5KerWIbNmJ4hsor7n5cjSEZ8hssDbNIf3IyJlefvt4okMB8lzonTUpdZTFBaWvDuJTdtDwHIwaqxL7aC9T8mRNT009Oo0HJbK8s6l75e1XNa3Ws/kGLmp5T4W+OIKo7sdW1aounUGUZbKzqBANwkxg0SconZX3dirrHxTd+24ZPFdMLZHbJ483vnI1iADE4OaXQbTBY4wlYVYFqBCWM99OZ2C/HfPSqA9kdac1xFoSx1Xh4tJc+2g9KgMceGS/yY/ni95WQ==
*/