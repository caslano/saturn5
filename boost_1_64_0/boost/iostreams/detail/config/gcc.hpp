// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from <boost/config/auto_link.hpp> and from
// http://www.boost.org/more/separate_compilation.html, by John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp> // BOOST_INTEL.

#if defined(__GNUC__) && !defined(BOOST_INTEL)
# define BOOST_IOSTREAMS_GCC (__GNUC__ * 100 + __GNUC_MINOR__)
# define BOOST_IOSTREAMS_GCC_WORKAROUND_GUARD 1
#else
# define BOOST_IOSTREAMS_GCC_WORKAROUND_GUARD 0
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_GCC_HPP_INCLUDED

/* gcc.hpp
knQPxvYJuboHwz4++a67dudaEXPbXoltI7Hu2Y4vh04F7lfE/xsdbhHnrwd2kVR+vaWLRwYle1zAuKijhIdSacqhZRWg2ErkYw5VAK3zk401Z52JHBw/nNn5Dyq5QWvwwOChbHRGQnGBz2OD6JNKG668eBB5ADygwJGV193LVeNgtrAdaj1qOTkeEClkIa6j4Y/+3kYgHFSn3vu/rbYzmPUVjZkluipeyG/xaYXGZp0HApTj/kCCdnKqZnasZb0hcuyXU4ukp6cBO5JqwEMxtAUc9Rw0q0tir+imymn+lmPTxO2kMAEwTUsuzDTBdjIrhs7McELjv4aDvDbe2wpagnTQx74ij+t0lv3KlnjyKiPapA430UIglCa99V8h3vt1jrnkCpzQlV8URe1RpWuBx0gXxw086MqSNrVGkjAkFJZLc6JPKSZagQuqBeZ5erywthg0+Maa1sFtgbezhmjCbQM4B1GEs9gj6KbHl1MLJlo8eZqsmjh0eBvKRtCt9FX0WnRzw5iwrR0cYmS/gr2hQY58Bg7vjy3esSn7FcVb1vT9mfbe/lrfrEVFTQ==
*/