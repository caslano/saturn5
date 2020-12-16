/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   utility/manipulators/auto_newline.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains implementation of a stream manipulator for inserting a newline, unless there is already one inserted.
 */

#ifndef BOOST_LOG_UTILITY_MANIPULATORS_AUTO_NEWLINE_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_MANIPULATORS_AUTO_NEWLINE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/formatting_ostream_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * Stream manipulator for inserting a newline character, unless the last character
 * inserted into the stream is already a newline.
 */
struct auto_newline_manip {}
const auto_newline = {};

/*!
 * Stream output operator for the \c auto_newline manipulator
 */
template< typename CharT, typename TraitsT, typename AllocatorT >
inline basic_formatting_ostream< CharT, TraitsT, AllocatorT >& operator<< (basic_formatting_ostream< CharT, TraitsT, AllocatorT >& strm, auto_newline_manip)
{
    typedef basic_formatting_ostream< CharT, TraitsT, AllocatorT > stream_type;
    typedef typename stream_type::char_type char_type;
    typedef typename stream_type::string_type string_type;
    if (BOOST_LIKELY(strm.good()))
    {
        string_type* str = strm.rdbuf()->storage();
        if (BOOST_LIKELY(!!str))
        {
            strm.rdbuf()->pubsync();
            if (str->empty() || *str->rbegin() != static_cast< char_type >('\n'))
                strm.rdbuf()->push_back(static_cast< char_type >('\n'));
        }
    }

    return strm;
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_MANIPULATORS_AUTO_NEWLINE_HPP_INCLUDED_

/* auto_newline.hpp
a610NXw6s7z3wpUu0yzvVZ+urdI959OZx7jdpzPPd2a4ndc3yafzna9PZ9bv4QhTZ5aX5Utn1rlmuH1/lvTIP4a/lwrdMfMewLpOJvM4lvsD6iPtevO+OEvdY5xCGV1UGbwfuT3Cej+xKsJ6P7I3wnq/8mWZ+LcrWfP/4Atb9yeJM+2GEt+H9yNZUX7Xd6EtOt+PdJd0PQPej2SZz5194kfFwi4Y6537nhhPPfzrhfvISrglstyv+L4TGtx3Lm33L37PCAeY80xmSIf0RhuU+t9vgeaYM6V4ek7BjPyi8ULvMa87Ll537OcmZVjutVZW4FttRtlJUra1P9bL/z67dX32h+bXH0KFC/J7cpLP/uxiXguqSnySeQ6r4oI/h0D7mexPcP5G53K/e0ZS5YL6TifylfudzhVhAb7TKXnL/07n82GBv9O5Ksz6nc77K/CsPCWI73Sq9kpM8hZQyeW1t/9Izlm226+9hHZmvcdWXNfLJN2b4KfEO7UfygnMPUsGTpL4/bARx9nbUPIHzz3zT1tdxlthfn6R71k4EJfpQ8k3yDZOE/gc8TeJ3w1ORqxfXxqflJSy5bmuNvqpkvGcjH56ADKce0auyfBymR4Eln2mjKvgM2UwHDX17GmcfxLPP8Hy7Cn1lnX5Ojkv8Dy4l8luhgdy3U4Ls753Uutaz2QfT1EnT7EA9UyvYhkz0/Itrz6ceYv1JM8w3q+pMvKwqqdYxpHo7WuJ2YcNJX6I870nyx4vaWoE4XNgaftA11VpI5RpudZdWsX52XtrivcAz5Lb8ozi/+l+bSYUQOd2ukjSPeY8x/QKcAD1CnAA9fL3c/mbxDfFedY3++EB0Y2z9xPn0nCJ38R+UnOUY5LlXiNporzcQoy1o9W888idD25hYnRmhBaYT/isbn0v+7WEPWgnXcqbi7IOQ+S9bFHExe6GEZ7o8DCTB5ysDZX2XSXPBEF9l/fcU+UiDtet83A6w/9keCnDgznGturmvJSw213m/TDHXHSq+a09zeibHEhTlLHcO0+NO4+86UVF+VOLZY7KuGss9x3F5rh7UtLmOIw7VY7rpN7DvS95G1new31UxfoezmjzNOd52ivQeon6G3PUaGupQ6KEpV6GTsptLjqpk7Tf9irW92u7qqj3a39t7ucO4X6OOvj38C4j79rxTo0eNda9uycmxP0MhvvZigP1HnI8N0HW8O+0Suhr/t0Ufy/h32MrkQeqbGZio7PzNptU0mZrkte758NQYDPgMGBz4IXA1hL2423ShtTdgcdWXcqTegkPsCEwVpPxIjzOmsBkYH1gN+pVuaM8gfmg88ljuxUYR/5lEvfMSCYPs6Hlm7N+ewZ5AvNBbyCf70byQW9ivlJlLxG7jITFNvMZ820nL+9FYD3yEduQT5hDPuEU7uVTwL18ridP9m6jHO6t9CVwL8NHGD7KPX6O8Zuz4Tj+N8AI4LfASOABYBT3+kngXj+J3OunGvAHYHXu8VMDeAyYCfwd2BnocqF+QB04CxjjIu9TvXuXd/t23uej7IcN5BNuJO9zG3mfm8jLfIz8xcfJM3wC2Ai4xagHeaZnSz7vcb/S1ftfeTcvxx0K2Uc7LWygwh9cBuwIXA3sCnyAe8ms4d4sKW4vX7E6cBTwIX57dz2wCPgI8FLjPICXM/1VTD/HqC/011J/A/U3GfWG/jbq7xS9tx9fgH4t9Y9Qv8FA3fvN3VTg67Lme/s7DbiP6T9h+k+BmdB/zfC3wFYIH2S6n6n/BXg29Og7rb0u/S3x1V0SL/3cAfq6wI7ABoxvx/hzgEIHBHYDZgO7AwcAewBHMX0+048D9oZ+BvV/o/4K4EDorwNeCHwGOBj4BvA=
*/