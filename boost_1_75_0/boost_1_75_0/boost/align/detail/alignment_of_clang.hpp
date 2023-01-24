/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP
#define BOOST_ALIGN_DETAIL_ALIGNMENT_OF_CLANG_HPP

#include <boost/align/detail/integral_constant.hpp>
#include <cstddef>

namespace boost {
namespace alignment {
namespace detail {

template<class T>
struct alignment_of
    : integral_constant<std::size_t, __alignof(T)> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* alignment_of_clang.hpp
WYvHhVDvUzcvUQkuDeTMFCEms1Wdua7LKSUhmqM5pKpy4NJmpZzK8Bx1aBP4WGuK3wOPw2rxiKQJrlXFIFJwhDNhbqH8HtTXShEVsZqgcKsM3Ylsjz87vnhQ1YLEaccfNM689YMei7BgaWyZnRAbga/xcZFj/p+ScECIQSNrymS8ARESDCsDoYYX5mKCxIDmD8fMwRLWxYKFbNgQC+c/j7VeBqE2hCjcp3Njq3yMbFm/ssNClCXZNCOOplzLod7g3rfjT8crT8b4mGTduZeaTboUxVPxp9yMycsJKE9zAAzOnMAqqTyWGMvHFTXFpWj84jQhdwhbQoKeafHtkVWnywy1ExfR/VvYV5btgT1kVIEOOfL2itTh+e0CneaWxjCoMqnP8GwvU/gl2cgB4wIV1TxkdX2OaesVlTIJgV3TXbigi8+8eRpNSGxzvEgufXEY/uFyZH2KastmTmqTKRQroZgTNyQMJrYhr8h+dtXJBIlsWe+4KKTb+PPkS3ngI7kFgaJsvzqvdtA70KV4oD6MQ/H+jHwc/fmsqH+RY3iMiAU1vPce73zHTMiHeVeVikaTZxym2cFrWd7vbQNUoi8fGet93zwYoMrMo8gKCck0AhUWXA5hjSRTQaY6aP3athyB5MMrdiOI08nPdGr8usZ+uqZxmUHdEh2Vt7F9WmOSlfZr7EdVcjCzGrDCpFNWLDVBHj/NepO81hO7OF1a
*/