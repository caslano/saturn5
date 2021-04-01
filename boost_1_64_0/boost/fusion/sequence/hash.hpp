/*=============================================================================
    Copyright (c) 2014 Christoph Weiss

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HASH_23072014_1017)
#define FUSION_HASH_23072014_1017

#include <boost/functional/hash.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace hashing
    {
        struct hash_combine_fold
        {
            typedef std::size_t result_type;
            template<typename T>
            inline std::size_t operator()(std::size_t seed, T const& v)
            {
                boost::hash_combine(seed, v);
                return seed;
            }
        };

        template <typename Seq>
        inline typename
        boost::enable_if<traits::is_sequence<Seq>, std::size_t>::type
        hash_value(Seq const& seq)
        {
            return fold(seq, 0, hash_combine_fold());
        }
    }

    using hashing::hash_value;
}}

#endif

/* hash.hpp
kkd5Psg7E92b9zpjSivQrvsguZW6sPa5hBFGztOIpcH0Gbvn6og2a3VsfKU3Zr+gOBaSW8c8CI/Y+kVfoRIaZWzcegROhl9aMl6AoZ802XN7fyamKt/CNPC6tsgiKC6Z06ROOvCsoXIJt8zvMUCvSNIoZ+PzvIy8c5LnV39oSm/raoMUCjm6nOaPGKzngEmYOnrqFaShmCxQ9kWKe60VpIhJ8M7BIUUhO/2csVnOFjm1iboLE8NoLKrNuDoYd55IBHVzidClaZ7gMKmB6xhRZ+XsD1nkHDnNCPEcm9uN7DT4Jldg+VLN2x/hvQwHt3sCdfOcy3ShQoXad8ySbXhuIcUXv4ue75RSrZ7pwbhS5GjvDSf5sbI5/jkAu98s+8klYJLnIDUyMGi2mAuXJfuCc6SwGwqgqCTU3NyFnAUUwtJEHN18G5m9sq576bvvX37dQQVOqyggAQ/lNcKiGh9sZmmYPtwbO08qL6WqNrjOANgMTiD1zuvLurd/wR6wNTtS1pbX554M3SoFcPNDtFh+9M2+DH1KIi6peXBHDghx3oIQb+BH8bjhrm2PaQ==
*/