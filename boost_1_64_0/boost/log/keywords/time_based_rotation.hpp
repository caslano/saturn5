/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/time_based_rotation.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c time_based_rotation keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass time-based file rotation predicate to the file sink backend
BOOST_PARAMETER_KEYWORD(tag, time_based_rotation)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_

/* time_based_rotation.hpp
qSL8F6b/I/lG7/8XjbABiMzG7f8XmQ3f/y8yG77/35JNUbJVFVNn1tSOGTdzvHA6BxAW/8ywMwMZSpbXS8PWhC/N2H32iD97ZiAdvDTFCym3Oss9M8J5ghqya2ycfMz5X3+8bcKN3S/Yvun2H77jtWZVbvQzhzXjJLZrJAP3BqZEOE8w1rVfuOSSSy655JJLLrnkkkt/E+1Z/X/3nf+/zqb/b9bq6//PmOv/GWH6/x84/1+S0XD9vySjcfp/SUbD9f+SjIbr/yUZDT//D1mHvQjOej/LKr2/5T/8rgDW98P3Mah+087j3G/qHPpNsNc0rN/UNaLf1DWy39Q1ot/UNaLf1DWi39Q1ot/UhfWbJf8ge9Ef6Tdjfc79Zk39flPU2H6zphH9Zk0j+82aRvSbNY3oN2sa0W/WNKLfrAnrNxf/S/uNZV+8luyL1SvzxsxpkrTs2YnJFQUdj3te2Rfxfo1sX0xh+2Ia2xfTgVa4ul2Ey+ZwrTic/QzMml2Ea8fh9uZw7YEZDvbMhbBn3ga3wbVruuSSSy655NK/hvas/j+uYnfp/zfY9v9fr6nzvgqfK8I8Nmw+juQbtf8/oRFzcSVrn4tHmIcnNGIentCIeXiC49zaeR7OsupcQU4q5oa7UZ9PCp9f/4G5daR59Ds0j2578t1337whbfXXRWOb9tw3OTMwjy5SZeP+wG3ZIeyMdhLQx+cMknexXr/dnde65JJLLrnkkksuueSSS/8R2mP6P/+xO/T/dBGb2AyHyw/ZbOqFSr0f0nfwcJEEv+eL4EdfPhvS/4CD+5C94CbbfoGFbC9oDmfhowhT970RYi8oraJS9K2eWjGZ1mDUd+egu/adWDuQV40c138pLmm7+21adfnEmtqqObXOa8A2+S/TOY2h5eOqqyKsAUM+dI9/xcRpR1dNpwQi2BIQptF3Daazvl8L1yys3Cnw8ytbgCqfWltDOcBX5aC4EpSub8sv6/d9rfaJEUQPIPJWwHuAZvss30X7jDkMO/0rZ9jaaML08prKAJe/yYhkOY5p9rYCT9Ul2qp+Xcbzd/5uJbnHKS6/CvdI6J2Gu2jHeL7z726SaU7xxKowT4S0r4pHta+qXxXP87+YMmc7tbUKH8/5EMhHTWUwDy+Qv5/y8DO+ZfcyPS/0B7/hN6OzAOWw/OYfTP9OXlhFZAfZVo7QFsh39DbS69lL5nD9ZOwwZb73pIoUWSpr5FNaovxWT5IZnjXqW4JlFE9rtLdP3UG4lXiGL1es9lp1Mp5423y2/OTb83PydtO/F/KTKzvLVnKYdjLykyujPdkyi/OzkGRe9qaKcm2xVoa8NJOZninSysuPVOZ0yksKeGlmn6MyHOHJlJrYV76uU32Bs+lHk+9BfUFOPaeJJO5XCZTfg/y3a5kyOljn6p7GOyitDv5mSM1WpgJ7/3qJ2jNX1VX2Dyp/JJNi/haI18KHdOkbhIX0vJd/grettMWbZ/9+41rK60XGJFGtW+V8j/Jzj8+Me6M2TSZxn76Zyr/Sc7ks1oLxjanNt91ZOZTS/EFvLjboVhqXEa+Z0VNcpVtxjSPePGOFKNPtcXW2xfUlybyjG+JV3eoPJxKvxBgv5oSEy7OVaSLJJBqdxdIQGVSo+i7nwySTYBwsztYjlWUHyXyix4rnVVm6bA/E3c1WFp14NcbiXZSlbnv9sqQTr7cxTsyMWJbXKA/djKPE8RHLctj2QFkKxdURy3L29vpledKhLEsaUJbkHfXLcmvgN2dUilkRyzJ5+++X5ZMGlKXVjvplGbWjflnaE2+ksUCMiFiW60nmPd0rNqiy9N3B7bKLPvZrA8pyLMWTbAwWZ0Ysyz0kswllWa/K8h0=
*/