// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_remove.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_remove
        : is_std_list<T>
    {
    };
}

#endif

/* has_remove.hpp
ECfh15iCv2AqVqZOJ6MvTsFwTMM2OBUHYzqORyNOx2n4MGbiMszGbTgd9+AMfB9n4xf4MF7BOVjV9Owl9MJ5GIgLMAoXYiw+huNwESbik5iBT+ESzMfV+DTuwGdwHz6Lh/A5PIxL8Qtcgafwz+hGe1qJPvg8+uEqjMbV2BNfxKH4Eo7Gl9GAr2IOvoaL8HV8CtfJcXN1Zcs1XPM13dFMD+ffS9D0epv3heBuDMc9GIHvYDt8D/viPozFAzgNP8CX8EPcgIdwE36Mm/EI7sLP8G94DN/FL/FXLJYxAL/FGvgdtsWT2AlPYV88jePxDObhP/Ax/AGX4Y9YgOfxTfwnHsGf0Y0yXkIvvIz98DeMxas4BatwvMrGqjgXq+Fz6Ieb0R8LMRh3Ywi+h3WwCtsvHD2wEYZjJMZgFA7EaByG7XAidsIp2BlnYxesXpX9FutiN+yNMZiKPXAm9sTZ2AfXYV98F/vhIRyAp3EQnsNh+DsORx93zmOxKd6DHTAOe+K92BtHYl8chSPxPhyN4zALx+N8jMclOAE3YAJuxiTciQb8ACfhEUzDbzEDz6IRf8JM/BmzkHbKNT+5fmz+zZx2aj5mRyAvrs1TDszBhjgdm+EMbIWzsDfmyZihc3A8zsUpOA9n4gKcj4/iM/gYrsLHcQM+gXswHz/Cp/EEPov/wD/hr/icjNG3FD1wOQbiCmyMKzEKn8ch+ALeh6twPL6Ek/FlfArX4J/xFVyNa3EDvo4f4zr8Ctfjd1iA53ETelJHb2AN3Iy1cBt2xkKMwR04GHfiNNyFs/FtfAT34JP4Du7C9/B93IeH8H38Ag+gZxX2e6yBh7AWfoJh+CkOw89wLB7F+/EYxuNxTMPPcRZ+hfPxa1yH3+A2LMZC/DvuwtN4HM/gSfwHnsKzqPz+4ybjf5M4L7X5fhIk1xGC0RdDUPm+LMst1Dl/JU+WI15sjF9jR/wGB2ExjsZvMRG/wwfwe1yAf8em7k6MqUhyPH4h6ctKt3UMw2LSQdIl0uB+7I/lGMOw6on/nXEMT9R0u+1jGTY8YTue4YWabuUe01D/uW+kWm4uj2sYUcutYmzD/8DYhjHUe21Mwnmk1aQi0kmSNzdwRZJGk3JJa0iHSVdItRlAujcpjbSEVEQ6Q/Kt41apCymFtIy0n3SJVJsLMTGkCaSFpALSCVKlemx3Uhwpl7SadJhUNYz5pFjSTNJK0l7SSZJHfbdKbUjjSHmktaSDpHMkbwawjiDFkfJIG0hHSFdIEQ0oCymXtIZ0mHSJFMhg1h1Io0m5pNWkvaSTpCsNK8Z4rHhVvP6dr9s7/l9mVsItev7/OtXz/yLlMBEj53jdSK1M/QO28P3BOtZGTpYhPjYzdTrdfwYZZrlwz6X0EVDuO23HUsYprMJu7Adf+W4yg+RDyiK1DuHP1jLiiO9xz9DWN74vXP0cKdNjqEDuAbXtw+Ar/VSTVGMR+pO401ju87Ud5+wK07yf+zas99A6Kl9VKpcXv+2QB/bHaMq3uszyJbPNnBn/zN3v823me37TkxzX/TZWYl6j9LuyrxMp01n+R6r0L7qgKrO6DiY7UeYCKfNB2ab7SW0pc8x2TZlH3NND3bzK3welFxfw2VPsx6VzGKv0zeMeGbnHRmLNILU3xVpYVqzSBF3o42ofr7q9+brQ3iz9FaS8NmUxuuu3tcNllkWam1Pj7fFMvLf+/e1NU2b1eF8yft5i2X4LSR0ps/EtTZlNg0qlJqcmUmhn7qfX325tiHmmfV+m6Xbj2UhMUyWmVFJnYgrbUVZMpS2q3O0/W9qP9nimP06jlMNm7I9YnTH6uhJ3QdlxJ6YwJqqpDZVnrC6dNmM7ZoGHgzY=
*/