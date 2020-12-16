// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_FLAGS_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_XML_PARSER_FLAGS_HPP_INCLUDED

namespace boost { namespace property_tree { namespace xml_parser
{

    /// Text elements should be put in separate keys,
    /// not concatenated in parent data.
    static const int no_concat_text  = 0x1;
    /// Comments should be omitted.
    static const int no_comments     = 0x2;
    /// Whitespace should be collapsed and trimmed.
    static const int trim_whitespace = 0x4;

    inline bool validate_flags(int flags)
    {
        return (flags & ~(no_concat_text | no_comments | trim_whitespace)) == 0;
    }

} } }

#endif

/* xml_parser_flags.hpp
xCuT9e5t+2+qVUZqfXhM5lrUVFNbVRura4pm1tefrK96X32WharG2vJYvDz6kHOdXZ3nzuxOo8Qcumyw1JdaYzLnbm1jY1VFVVVTcnj3Mt8/zNu6r76yaG2soine5MHBcY01Xtav6KMz501FaU2jJbYqHM693E+4T7JN8qbrKY2W1dTVxWtqyw+Mo2r2H4dnM9t3uLquujxWXV4fbTvT0r43NY1d8ng4f2Bf1cca6iobyquSdSQ2MjVbWlt72hwIlpi2xP9rw3Ki9wjLWSvKaOv94vGy+tL6euPX19LT1+q4CvO3JMfw4r56K6L1laX1ddUm9EPa1NrZ1VfWZqe1Jdaeto7W/f3L2bfOWGVKm+piNdG2ztZ0Tcl6JvfVE4vWlpYnpmOqmtLH9xnCzFrS60oQ37ee1dU21jXEyqLd/T3dXb1t+9fQuX31xM3B6oqaitJYchy7+v3vVFtPX/vj20/trjNhMb37+3Zp375rrK6sraxtrInqWJjTOThZ5/q+OhuildUNFRUxO7Gsq8+BlRzBls7WY4fDfmaWk6pz8ExmP8trK8orYrGq6Jmu1v6O/jB38lgbWwj2H2tNTQ315bHaZD/7TqvxyoeUhutoZhmp+hY+kXkMVNWVl8ZjNTHj+jjb7GZNX2dE4pl9rIqWNdXEa8qrGvfOTckKbdrRfkqdye0Lk+vX1KODzPWrvr60pj5WUxt9fHvnVW093YlGJ4fjVHJc8zPrLC+PVlXU1tZUN1Vm9PHAvkyXljmu0fi+fVlX3VRe7xzR0tHektqXqTUsvn+tLiurqI01mNWJfl42dzKLSF9ndBcGGfWVNdY0lpfFq6KdXakzddCTrK91X31Of43VjfFKB0hjl8m6V2fJscNP6O9Vt6O4r//y+o5HMsq4T01TvKKutDFRX6KtB/bjwIH9WNlQUdNYWlquvgN9S1SebG/6fDsSz6yrvLG6tFLXuk71drcnj9v25LXFaGZep9nyiiZLYF1qfW4qf0h839mnNzxD2LE6Gw38S65rK5llHSmrtnyUVcV3K27u72lPjklLsu61+P5jsslSWFrhWmpf3Ve29XZ3dbYmjsiHXlmfWFXTi2q67uDB++qOV1Y01rj67OuxU9K7NH1tky1/5nVcXVNZbWVZUyw1h1p0MbFxW+u+MQ8LKk3WW7yv3kaHpyvW+uipjp7drS873x/ZV299tL6hKd5YWWngO9paelTb0ZGq+D+te8eVkXENV1tXWlPj2lGdbWf3akyve4+WN/PasanCNK+uLsuo78CcUkZbZ2/ijVBmP8/v62d5fVm5I7Qh6ly3r589qevkzPxOkbHqirqmmoaK6HHZDx6iJtTugF/V/uS2zkSvo6n9Op1Zzv1qdLW6pjamXufY9NVGej2a21dvdbSxOuZkWVMfvTKR/X9VnK53fV9/Gyrqq2PO0a5Z+/atJ+3JY3brwfuP2fq62tqmmvKYk+d/XpBsn7qmyjxPH6qpbdBus7G15Vyqrscnj5vsK/cfs/F4RX1dVbmL5a6nHDvc0dV5lSnUbsfal93tPeesE49XrcO1/arOttZ9x2x1ZllHDG1dvK7KXDrdduqJLhKSdXckx/f4vrqro1XeJiVW32h5Yotjh59yus3K0JOx8IetSCwc7elz49CV+9fUyni8oTJeEYtWnG23yRUyP16DuxILq/88cQVy4D3U8ssyz8UNtWW18XLvTRO9dHLbfy4ez6zPab+y0XSsr4rbPx2JimyTbO5T2vtOG66eq/ZKSI/VbGYZ9yurrqtoKq+riJ712UGfq4cn7eVPHwMLV+4/BlzjxOsqY3XpNSZjZvjoQQuUYomV1BVNvwePjGa+N62qdv1XW1M=
*/