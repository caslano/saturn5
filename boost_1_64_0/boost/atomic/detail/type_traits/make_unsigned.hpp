/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/type_traits/make_unsigned.hpp
 *
 * This header defines \c make_unsigned type trait
 */

#ifndef BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
// Some versions of libstdc++ don't consider __int128 an integral type. Use Boost.TypeTraits because of that.
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
#include <type_traits>
#else
#include <boost/type_traits/make_unsigned.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_BASIC_HDR_TYPE_TRAITS) && !defined(BOOST_HAS_INT128)
using std::make_unsigned;
#else
using boost::make_unsigned;
#endif

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_TYPE_TRAITS_MAKE_UNSIGNED_HPP_INCLUDED_

/* make_unsigned.hpp
rnmhN6jpnXpWoT5z1Yc25Xp8Wu7S9gzUggYQ3qaflrS2x/aRjNDR4zntsmnOGpvXvPqMYlXAvFYh6f099Q/2FdnV9FODb5/0Qt3znVfg8qxlNDiZtq5vratQROUhi/xAGG94r+iTuKmv5u9r5euzq7skfgq0zN486cMfvMoxXgwn94gtdp6upow379I4qseOtIwBKUaW0Vrg8Osl73WRmeQ/K5JhfZLg5v0O0vF4R6seU2ZZ+Enhr19Qty4p3BHcfO/K+iqaInXvC26SsvMjL2OJaZEeMo730KenMG6vQ4+pa6bhfH84Izmte1j/PSNlDAjtv+ckvY/6vV+Uk24Jv9eEl+yQAL/XGXO0m/7VPok5t1J+m90jesAnonJo3/XEj74rNn6Nxr+R1xr/pif9fU98xBYTN5zclg9x3/pgLmcYJ7fjfkGDuaVhnNwwjmrH/YKGcUUHib/QUye/vXdb4XlX/fWs035ctOCSN8I4p2Hc0jBubBgHNozLHMaNDeM4h3F7w7iuYZzlMK50GCc3jMsczll+r813oMwFZRHx3Sj39xr+XsTf/fTvJvvepn9v5O8C/XuTfW/Qv39KeIc4txV9xyHvZiQtC1yu17pV+Z63gYPA28FCcBs4CrxDeax3gSeCW8CF4D1gDfh18ArwG+DnwGbwalve8E31/YP+XePmmyqP18aFYG+N54OLwMHgOco7PVf5rOe59+XWctO1XPf+2ku03KVgGljhqk9zWH2UXzoQ3AhOBq8HjwVvVF7yDeBM8EtanxtNufqcGbwyoNwVqt+Llfe6UstpUP7ravBssBG8UOLazhR9RqvPf+1yp9vt1PdFLL6kv/qAI8B88HiwHzgdLATPAYvAzWAluB2sAl8GLwLfBFeAfwJXgf8APwFGuNZlYB54OVgAfhIcCF4JjgA/A5Zo/CTwc+Bc8CqwDLwRvAC8CYyCXwbXgbeB14BbwBvBe8DN4FawGWwGvwluA78L3g+2gN8EXwAfAN8AHwIPgDvBv4DfAf8GIiN+VXeBmeBj4CDwcXA4+ANwDPgkOAF8FpwG1oELwWPB88HjwCWaHgWrwUvBWvATYBF4Azgc/AY4CnwQHAv+EBwH/gScAP4WnAj+HTwGjNCfJ4Jp4FSwOzgDHArOBo8B54LHgfPAUvAUcCbYHzwbfBa8AJwMXq7xd4QPrs8UwbVqj93Bc9UeL1N/uk3KX1+j432t2vmVYLnysT8KfhZcrHzsevDzYKPG3wFvdJ6hAW/q9bLBq1z7xheA05QfPwM8AZwFTgNPBueAs8FF4BzwfHAuWAHOAy8ATwXrwPngOvA0cCO4APwSWK688DLwJY3rvvj6vAndE2o8++LfovPgJnA4+BVwvMadffGbVD43grxnX/xfoPe+4D6wAHwVHA3+FhwPvguWga+DF4B/AC/X+E7wTR1/b4N/0/xab35rh9ebsSD1/ik4HPyZXo848jIP6m9L8qp8N7Bc5R/UeWk7OBJ8GJwA7gSXgo+Al4OPgk3g98H14GPgHonrPOX89gF7BszH1TofLwN7uPy3ziYsUTnmXbnvZYAnqNxelXsRTAF/pvL0rej7ZXAA+HMtr9T8ZpDfHlKPYkvGnRw/Jl8v8Dm19xfAieBPwXK93llgT3vca/kXa/mrwX2qh1+CnwZ/AX5Wz1+j528AfwM+AL4GPgz+HnwFfB3cp+X/FnyL+O/BP4LpEfod7AP+GRwPvg9OAf8CTgVpGH6nAfBWMBW8B0wDnwTTwafBDPA1sBuITcn1/gR21fnQPt8X7AkOAbPA0Rq3DtP3A//P3w78J3430NlvBhL9XuA/8VsBz3cCCX0j0FE/t4fzu4DOfBMQ9j1Av58=
*/