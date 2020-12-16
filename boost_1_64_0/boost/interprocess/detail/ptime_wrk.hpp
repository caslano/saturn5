//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PTIME_WRK_HPP
#define BOOST_INTERPROCESS_PTIME_WRK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//workaround to avoid winsock redefines when using date-time

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifndef WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#include <boost/date_time/posix_time/ptime.hpp>

#ifdef _WIN32
#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#undef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#endif   //#ifndef BOOST_INTERPROCESS_PTIME_WRK_HPP


/* ptime_wrk.hpp
l7dHwQ1LHwyLnLsA7wSdvFNdezaW14GPZM9GgGwAPzZTXAvLyqqkYOJ7vP0lWBXw0nMzzuwe/hM+Vg1g2/YQCL+HpBHUQ+s5FsL1/a6LxZmbrXCzheufZXE2KJuz3fpZjm7f388NkK1+yj6DF9CPri3lwXGyx4D3hEj6cD6wXtIB8yzLyx+ML+myPS7Gi/JrMufXDs6vQn5xgbeG+RAvv8gAiTHiqyfwXRD/Dhz/la60MQ06HfK9aYDlUA1rRWcCxou9i9aeSlgb42Zo/bw6Jxvle9Od9sTwO/chIMJG2hp4joTy/CC9c3EsHsFGCSDchzS8l1t+ov7ZJ7uQ94WlTLMf8N9xED73ZedCqM4DOR/kApALQS4CuRjkxyCXgKwCuRRkNchlIJeDXAFyJchVrThTpSes1/zgULQh1kfrIWswT6icQdihjES1+jyF17jP4nUtR4O8DPFPDsX4Y8NaHYlQdUa/vPNmyG8z3uyW6/IruEAGuJBbXl3etXfvXi/P1kBsfsLxCsm0mTmY9kfl7AF3fdBfjA+fDwN+U11Cf+F9qOP3YVyP8vba8Jr2Uo7rZM8er8e1rjqV9uM7wN1zBGn0EcjVwO2wf+fMrJyeWR3AAz0OwbSRuvAp+t+txfRw9yS1JQ3cdbh/RH8h/L31eO7gNdyHATjA7Zfg+QZwpgyTeLq9LV54XoudWqBfkrDPRzfZlnxm/7hdzcV64foKecF14yTEMzMOgotKVjj7m+24+MH7zXCFGYUIebQX8XbkPAFrSbMpjanG1kW5L9kJacL9APzQuV8/f4Nus8CvWTkjIP+f7wZrMiGRs4Y1v9sXdDPg783dOG+b/4CZ29p8HTy8dfnqygB+/5fwrrX4roe7D4O39YO/g30N8kHnNt3Xwt/XgVwPcoMrbWyHvxkm7TAGkX9dWlG/lLGBv3/Rzec+mM+ow7THekj5geVy+TAql+/0pr+fDPw9cLiUW7Ut3gz/xz0I7vlH/Iy7Y4vhSrlNN9QF2mL7eGJ4sM+HoaxtLCFc9LMncmP+HtBnR7jYaeDPiW65Rvws1E3MGOm85wzM6GaOOVQ//fO2kuZ4Q+XhflgcxyCvt8LrbcYHfg1R97mA68ivEN/QIRdS9CqQLSB/clMX9v8OBjkdZAPIn0GyMmG+AKQJ5BqQ+0F+AbILpHeHTOcwkCUQaK9NcLgMzOU6NeAw910ndSiGlF4Jsg7k5yC/BRkL+4QXgqwHeQEkI7OjMxqkFGQJyAUgd4H8AuRDkEEdOnvjXPil65Ncf/py+o/GtN4NYXkc/O/l7/U9HvU94L98LLe98O8lGOZ6bEQTjWkKM6blERjmog4T3B3aIJeA3APyEsgg2Ac8A2QVyEMgn4H8MLODMwmkHKQB5CcgT4BsA8nq0An7hQ+7Q3vSg+vzAL862+sz87/0+MuRP+D7+EP2Y/65+S22F1eC7iC3zsLfN4GsA1kPcnPgeQs/N3Bbci3/vZaf18qTeabuVnqyiNvbVH0r2ykvn9/H8ju6Q1enHGr0c5l9NbfyzejVy9eRPw3q0HBs22QcBPXP2NOSRWOdw8ENj5E+HYn/hj0tueMd1r0kunGe7nzRjfF0cdHleroS0Y32dMNEN8rTfTDC04323/sz0fnvPU10/nv/fpivQ/96gO53vm4i/v20//cE/Hud//d4/Ptc/+9xxrhQ26NO7SVysG1DXQz/zvbP4Eu6f2P9+gT3PNdi+34AvcP5HAB1rLmqp7/2H3B6z1+BkzxCbd+b8Bo8gMwxCbc/jchP2MeeLgb/HQD1oTP3nzcEpVXjaLMPVPuqpl5ETrKjBMgXwM0epcclHj010I5KGf4RcqugvA7F9uRySJ8=
*/