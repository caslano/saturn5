/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_BEGIN_OF_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_BEGIN_OF_IMPL_01062013_1700

#include <boost/fusion/adapted/std_array/std_array_iterator.hpp>

namespace boost { namespace fusion {

    struct std_array_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<std_array_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef std_array_iterator<Sequence, 0> type;
           
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
ANk2gMaQhViVvK1SYjucjFD4P6OADu5GADXbxXI6oU53jH6SsrJcs/QazXbG+lLcNcAhwMNsGYd7nH3uGG4zfRjKInTAznWN+5TfMmwQ7qZyM8pEM9JyVPEtbRx7bwI5uDdjFj7U0rS6GUVMmZVH2RqCPDhJNJEcKLJENeneXESjr2fCsArNWwfVpeuRQ/AfDy0HjEAi8zzRxzmh701OMcIGFw4+Mxs9oxWObx3I0B9uqOk4vvzIMvvuseV+8HY8emn9Y7m5MDT0PnhB6L0JwiC+srxyy3bKnC/8eLmYwgcvXPrWgmt8G1DGZT+ZvTMSduT74IXRDLfZm8U+HBogNjYZVu6LPBsePlB6nIO90L9QSwMECgAAAAgALWdKUmfaBtPMBAAAYAoAADkACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1VQTE9BRF9CVUZGRVJTSVpFLjNVVAUAAbZIJGCtVV1v2zYUfdevuPAe6hSqXKdD125dMcVxGqGuZVh2uwwGBEqiLDYSqZFUE2/df98lKSdO2qJ5qPMh+Yr3nPt1roLNAB7/sI8XGDj47ie1fyl+8Lp3Wkjxkeb66w5p+hncDzpu8PoAqhHcen1Oj+BBXp9haL3SnuuVuU/T
*/