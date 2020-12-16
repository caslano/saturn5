//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_GETENV_HPP
#define BOOST_COMPUTE_DETAIL_GETENV_HPP

#include <cstdlib>

namespace boost {
namespace compute {
namespace detail {

inline const char* getenv(const char *env_var)
{
#ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable: 4996)
#endif
    return std::getenv(env_var);
#ifdef _MSC_VER
#  pragma warning(pop)
#endif
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_GETENV_HPP

/* getenv.hpp
cSrUGRD8pDHjDNKcUqNJh8CnXDtci5uRokSVHhNWXK1nTlChRZcxGw4+LW+OSVOmw5rAZ8TmZmTJU6LHhDkrIp/VBw6JU6RClwFjwn194Zg0BZqMWLD3OW1xRIoSDdoMudrnxSdJjhZdBsxYcvAFfeEM0hRo0mdKYGD+cDOOiJIiT4M2Q+ZsCX1R3zjkbiQp0mLAhoMv6RMxCnSYsiDwZf3iclyLE7JUGbLiUkO1I06GIgM2BL+iP5xBjFPK9JkS+KrxJ8oJWUo06LHlUl+TP0nqdBkwZsmG643MWQrUGLFm7+vic0SKPFWGzFkR+YY2uBFxMtQZsCT8TX0gRpoafQJjeXNCijwlekyIfEtM7kaSCmOC31YPEpTpMyXwHTXmZkTJkqdEmzkrtkQmakKcJDnqDFgS/K6akCBNkxFTAt9TE27GCVmq9JgT+r68OSRHhQ0HU3XgDI45pUyfKQv2f6AP3IwsDXoMmXO1H4pLnCItBiwJ/kjOxEhwSpM+C/Zm4nMtslRpMGRL5MdqTZE6LbqMCf5E/pzBMWlqLNj7qXw5IkqKEkMmzInM1YS7EadCixnBn6kLxxQo02HKmr2fy5koWUpU6TFhzpbQL9SHDC0GzAgu5M71SFCmRp8pawK/VBuOOCFPiQmhX8mfq5EkQ4UuA5aEf60NrkeCUwo0mbJmf6kfHBElS4khKy71G2NLnAotugwYsyH8W7UiRpoaIxbc7HdqT5Uhc0IreZMkR4UWM4K/ly/HxKgE/O2UKVsOlCXGmA03IhPAtkOZgzP7+z7Ns/ibK53dfbSbO58r0LvTuf57/2GB0oG/BVP3eGTbs13Zbs/mb7Rn97bMmoOQGN88V+BmB9pmsLv3cHJWx5I6m1h0uNI5/D2aAg1G3OicziNHg+V/7ou5i7h3OVegaa310Z/VRV5Dj/cu6W/aXO5c4lAg+wdjLvfan9TQGlT7/t/VgbU1Rrv7aQt7frV5Xnmd/3/3bxYuoR2W4izs27uAvhNuqy0L/w9nvLuf9VLn+9/9qhmvVxmwiKjXBeXAIQlyVOkyYUtF3uHwmf3d0DGs2L+wv3vTILvvGLocXsRnEyiw+dq5AunXmoss5Rm7lPr9wN/B+f/nYS7HMWnKdJkT/JE/BxHldPdZmCFrQj/1I2t3d08pQXEP9S9FkSZDlrt7dePkaHA9/Y5yEDF32Hf+GRwc2K+OLYYs73Cu/95PWuJm4l/t5v/7XU2JFXt+JzNVk9JF9Ycj/Rv+xxXVh8iVzAfWVzFfri3eX7xPWPfvxJrROfVrElW7HBXj3qVgzJtMPV7api5p7Flb93BAxbqRWS5Fl2OmVM7p/YQllX94v/B/1SLXcr1zzH9+194iFjAf/I+e7jXlzoak1ws0uJZj7saYmzk2Q8fxK9LH//s9/fWsjRphEFMH9u8rdxa73xdfjRv5PwMN/9PujKD6Mf0PNdrw37/Fq/Xexc3JS/3vft8mIbW7mm2RiPWtb0Tq4vbZ39zdL75m/9zGiyQlmozZcKnzGAeSzsm4Tsp0mRHc3ft9RMl7xYgDeaW42lldV6Qp0+ZyZ3MsU+7mvSFLjeOQ2FToMSd4Dm2yYf+cct3dGx86l/00dvfCn0GCtBwr9Fjs7mG/Gumw9mlzYm7mqTPg0HwZMzJfNlxqd7928CJypcWYDQfqfEiS4PO9V3FMmhIt8mtjzpAV+3/y9ZUEeXrMCf3ZvCBKhjYr9v9inIlzqb/62sH23Gc2BmcOHJKkRIcpW27k/SxOjgZDllzNdXREmhJtqv73Yo+w/117NRIckaNG9UrnCizpM62Zr8R3vzuo0mXD/pvlyd3OIT49awHNiF/etXc3Y/se1zXl3ec=
*/