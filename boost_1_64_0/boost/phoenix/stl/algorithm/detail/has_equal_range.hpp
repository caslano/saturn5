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
// has_equal_range.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_EQUAL_RANGE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_EQUAL_RANGE_EN_14_12_2004

#include <boost/mpl/or.hpp>
#include "./is_std_map.hpp"
#include "./is_std_set.hpp"
#include "./is_std_hash_map.hpp"
#include "./is_std_hash_set.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_equal_range
        : boost::mpl::or_<
            boost::mpl::or_<
                is_std_map<T>
              , is_std_multimap<T>
              , is_std_set<T>
              , is_std_multiset<T>
            >
          , boost::mpl::or_<
                is_std_hash_map<T>
              , is_std_hash_multimap<T>
              , is_std_hash_set<T>
              , is_std_hash_multiset<T>
          >
        >
    {
    };
}

#endif

/* has_equal_range.hpp
wW+II4Y45JpQr7jR8QlJSaUHE3k2irqvi+NnSHmbtkX2TFX+TKOjvi4Nda5ZFUp8z5N8SMtJ3wbz50t1fOYH71gizJI68nWijoiRPKWO0J9EXEpM/F6q9C+6wPQB8s422j3/6w7t/v8d7ztsG2Ppcy3TUg3pYMjkz0QXtqXUpU2+a+/QPv/se/It1uabmp6coTxU05U2JPnatJkQuX5fQ/INIP09mD8nNPmanleUkePCM9dSddrASp3n+n3DRJhtfhxgM6YbLI2gHGW0b6fqGGjwmm18yrSf2MZgyry04CQ2sOsxqPOcp5PnafKMdZBnumFGufO0tKkSnTzPkOcE/Tyl0svflpV7CnWe5XeWfI06+WbdRP1atvEy+ZxQx1C1mjaGc8SQrxfDTdS3JYZnJAZ1/S/WieE8MRToxXCT9W+J4086cQR6aeO4YDqm2cVxK45pljheUsXRV+JYLXHMlTjmkC4GE0vZcRjSJ/GYspuIZSPTBlTHEuGtrZNLwcT4lTaWjIwpqQZaabohMyH7JrfPKzrbZ4tOLL8QS5GjWOQhoERS7jjW6sTRRe4p8ZM47iJdIY5iuzhuxWeQJQ555prNZ9JBiSOS5EOKIP0WzJ+vNXHIZ5Iz97U4d45gmk6zu8+svzzH77Lca/MTXiOeGOKx66ObnGkwON1/uPQcKcuad+kzSe0+q3ZW17aN38m7qFiTN4fRyPjEVGOKIdP57VEUrH0ubJu7tHle533FDvJM4Rl86QlTXXoerV6+OyXf2pJvrdITFNK3+vmmJrE/pGcbZrpwTkK+Nttfvmva1Hmkr7b8biHMdxCH0WBw6VnAeufG+33tv2shecbq50nDT5xiKEe5zd/Hmc9SrIN9V75vqetC/fxnP21dVCWuPN242B5TjZl8nrFtXI9NXR97Jd9Qybcm6Q7yXa2fr2HmDb/7l90OSve9JNtz497++u3xsG4MFNmFNuCoHao/o4r8tb953BnCn+908+dJudkZiRlppk8H01mzy7Gon00dE6Dd7h7k7auft6kpQVpqssF0SI5PYaiCcuWvPP9b8g+R/INInkxEOsp/qvPPpNZrbw0D9fOL1eRXvu9CenkuC7T7nJPta9TmmZKQJXXs1D2cOvUqv2+F1DC/8UUp5yrSEj/qW5MnG5Of5vixwOkyar97qcsszwGW/N3kmSx/SP50AtfJX86JXXi2tm4Mdp/nHkGyreXzPBCrmfbrk5oY+FrgXH0rv3lk2bbjlZLX/VLfY0ne5BV5SpMX5zOtXTpukp/NMcTHNM0K/FW/rzIdrzmmB+vHVKAfU7k+Zy2x+dvGFs+2sfn9V+bF238GH5EY60mMdUjVTfV2WhtjeY7/xKd3/Gea2OS3xoTMSTbbMo78eZGHOabaJF/mTdCJydVjEvHonpeq6+S45B8m+deV/PN18i/PMcpRDOo6GF3TvGCeHLNySX7EUKSNIcfI3pssxytvZ/N3cD7czlIHkv9IyX8Eyd+0Dc4o+U+izVp+OXJq35VnT5N3GmVW7csGorHLv3ct7ediAPkftsnfkr3zdZ8s+avz2it5PS55PUZ6mv9zwZpXVnnysn+2vKWsrMS2D12oeeEIyb8ZqQZlXf0PvfwxMbP0lxxXzoUtsYRLLE3JOTstS2+l2n1T/RtHbfPKr0usJaT5nEMU68cq5ysc0soRa5ApVomDNciRh/qU+Fhn6Xz787mC2tr6DKY+w34oO8by1qnyGSjfse3rT/25PK6OeUWTZb9KJpXw5gnm2JIMydYfQCRAPhec+2xUt+/qquuBLG/9rGJaPqqYZx2Lio2fOQvVsRbX0f5mXZN6vGCONS1FfZGFDp5phmzOIJy/Lvg=
*/