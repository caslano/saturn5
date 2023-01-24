/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_IS_ALIGNED_HPP
#define BOOST_ALIGN_DETAIL_IS_ALIGNED_HPP

#include <boost/align/detail/is_alignment.hpp>
#include <boost/assert.hpp>

namespace boost {
namespace alignment {

inline bool
is_aligned(const volatile void* ptr, std::size_t alignment) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return (reinterpret_cast<std::size_t>(ptr) & (alignment - 1)) == 0;
}

inline bool
is_aligned(std::size_t alignment, const volatile void* ptr) BOOST_NOEXCEPT
{
    BOOST_ASSERT(detail::is_alignment(alignment));
    return (reinterpret_cast<std::size_t>(ptr) & (alignment - 1)) == 0;
}

} /* alignment */
} /* boost */

#endif

/* is_aligned.hpp
eKrE+lj4QH7m6YOHPGqDhI9+VyIR5MnWaSfEujWNu89lsB7McilRDwvhkro3O3IBdyiBPmQRNgtTARdLDLwSANjdnHh7dR4uhK8PBqiC47H02aDoRLoRmu8Qebt+USng5Qx3Taw/6N4SGc06wCVRm0G2qsoraokTR/agPIuzfdijEkJNGlroU2Omq7KuK/ghQsKXsq3HbROOe3yvHvBdnzjRhySgkaJYk3v6Lh2ZJmySL0RP+SEn+jpQz640p5aKwTf2Juf+Q3y1+aNikOPuM92NpVd8pOBKcx8pzaFm4mfeuxc0c1R8AUuFeGyD7VumeZbaXUC+mjPw9XMjYJJzfBr3rDeKl3om+XGlLf4fkfCcHmiSOhPeUip0FUI8dGVCXJ0H/fycVcKeHPGx4nZTM+CE2Dl4UT4MRDsUn+AMDDDbXqN1b4T7Lm6Bqqx2LjGKRyPYhD4kVj78HwAKLPXTAMBglSjPkepCP6n+KlARX9KKItDTt9gpZLsci1H3A/hJluvQCcb72KmMJf1RtwaOkejZ2TESFxj6EVZdOIQ3Y71oO2jIE9GBmEC4lWW+c6WYiTZJwjRRiABlrrSC6InLgVl/KvkIpS5ilNSlzlIq/0olfpgJ3X/A+6Ny4yygAjwsxa5MjxBDrgTq5oli/cT6AkOyWaAPp5IL8G1GR6E9dbX6Qq2pKWahAsDDOlbbwW0xS+ozeCUNV+hZV+IK
*/