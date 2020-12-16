// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_FSTREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_FSTREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/config/wide_streams.hpp>
#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# include <fstream>
#else
# include <fstream.h>
#endif 

#ifndef BOOST_IOSTREAMS_NO_STREAM_TEMPLATES
# define BOOST_IOSTREAMS_BASIC_IFSTREAM(Ch, Tr) std::basic_ifstream<Ch, Tr>
# define BOOST_IOSTREAMS_BASIC_OFSTREAM(Ch, Tr) std::basic_ofstream<Ch, Tr>
# define BOOST_IOSTREAMS_BASIC_FSTREAM(Ch, Tr) std::basic_fstream<Ch, Tr>
# define BOOST_IOSTREAMS_BASIC_FILEBUF(Ch) std::basic_filebuf<Ch>
#else 
# define BOOST_IOSTREAMS_BASIC_IFSTREAM(Ch, Tr) std::ifstream
# define BOOST_IOSTREAMS_BASIC_OFSTREAM(Ch, Tr) std::ofstream
# define BOOST_IOSTREAMS_BASIC_FILEBUF(Ch) std::filebuf
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_FSTREAM_HPP_INCLUDED

/* fstream.hpp
49zvf0wt++1N1la7Nfaem5Mqn0l3tuSTtc96vVC6x3L3Tbq9nilMu71AwlY3a6TOkXLsTzuoH/7uTJph6b5xvSW9tt2EntWba78HQ+kZrenxeB4x/aOqXOf3/iesU8jXOGuGfb31nf17s//iXMnDhby3mOtL0fVdtSTMm/4R/kqETI367m+XpK2VFVqLHZDy/zAwkXbu2k/MPO/0knift1+wJtKCpqs7q7gkDU3tiYwChdYqr2ce0/76SJ670iJTI8vBrEs+QDqINbCI9Hs8C0k8BaN1TZu77PMWmPqqKnkL6Dn9Xc4ryzUOO2U0XMooMIK8lpZPflGBU3e6ZixT8nWNrzX5WkPfaOYTXV27KOtPzfXQNc9m+SjckBp6Nlt6PPLZrJHqPJ2q96D2suE8d3Eruj2hSpz3PWgo3kOE+Tz4TDXL3INGxNuknl47sGKEc28bGJ0QT7Se8aZomOH1NN64FRey5swycUdcf149fe6rvKIoms7qevq8lrB8d+Tz2n2ct4t4XuOe2DAOqYw0RxbTSMekBnk6XAJb4T4Cht77Zuk9RQvcN8CxnL+v8bbG7UZYFY4rfdcs4dZHvEfuo/FsVKmmaQo9NzYo457jopGxvffxeo4cmYab/samuO/T9ffT3HMYdwYZdUuNuA/BTdou7Rk32nPEWuhMzUgTzUBjpInzrm+M3Js4N/LBF4fT5X7S3F9yDzA36vu+MSfsk5Q30+tds6fujILZnu+Zja6Zj7qatjWeDE8ox15KTtrraNoj9lIijZHv3khLRHnNaehdXtml5TUzb3ZuYVE5yiu7HOWVXY7yyvYor+uS/zXlNVDLawsFJNS83o20aE1aguUl30yn57DP+PTc4rzCIr5/avlZsb1bJp6wZyXb9ayUAu8T/5XcX7T0LM/I8Bbh+eUw90K/F/+LeffaUt1sjXOmVQVXr+8St4r/Wr55+aP+9iXDX4neBmuJXr+76C0spADM70iz0/W5Tn+3vpQw9eWbxTza4rFGod+VWgn20JO8s1D9BtTHAdn/svMJ7whTVGdw49CY3izBX8U6YexP4zzOCo7NnZOCY+IZFNbEGJ7HTjYWnqrPX1bEfuXTtLNxTcNc3nfnS9ksLZyrM9bHjxg2Zsi46SPGDD1d9zXm/q3ZSfuexmG7yyLmfb+IW/tGeJvPanpiemeju/Qk6V00Y975GMiKKc3EEzEGyMa7Xu3b6Jo6/IH5C+/7XC+ijnZ55DnN6ecmz5P5rjd9wOhhp4+bviD3Aipo3jx0zDuHGNLlvt72ZiderwHX2+h1vfyF+dNnFeRSvjGNx8RhnuP6JTm6TmBn1YVnGRv90vceZefFY3w17yG4Jm7mmmH5ntP8xHwfpr9ujcj3hAnjRgw8Y8IQ6Qia73cbnzzfW39EXyBuzUf4foQJLU5M75NccFdYeqV29L3EydO4KyKNR8uRxu1a1pH2YIo80vgQF9wblkbTasvdZkNlkdryxOvs5DolEdehxqQsHq5z8rIo+RH1Rdye9XXcI4331yHu8DTmn184J6b6IlzEfB/uQb3HKqNrvg2VIz/bPe5TuJ7nPe+BVifm8TEnEVlhedQhOba6sLJiH5OtrB8+Jj9cp+wx+Sjc7iu/LYdo+0G+JeuWev+tTesJX1105ZZhU1IPVb7m0uj7QY6o4bg//vLkj++cV//g92s2Dn6j+f1H+H2v6bhvfffMpuuy76p6ebU9dspXd+zgvbHEX5R21ZfLxq6fcnnbSb9MzKhyIPq6qBV+x/3WiU8Gql/xze+abXutWZtfjuwb3RbFBFlP9vNPJvb/vP1dTa8+dsdvzt94d2L0fSi916tFX3/mva7rn79vpff+keU=
*/