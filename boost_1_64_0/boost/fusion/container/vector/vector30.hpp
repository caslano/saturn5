/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR30_11052014_2316
#define FUSION_VECTOR30_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector30.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector30.hpp
s3uepWvpV0j6Vkl/LKFSSf9H+vT9e5/CDnf6ktZgSStY6ttvJzQmBBGeYtnI9z3SYjCASFuKw2GzpzhT3P0d4LrpNsV+hnQHSLplkm6QpNuCsItlrSbp5vJKuxtJ072tX5hs69Ms66iVpi0115aTZ7elFzu+hHSdDWunu5tly2unm8YxWehMV+qx6p+uu4wvm6S7h2WraqebQcVdQeYNbKs7zaRGtffrXpY9a5JmdsqcAn/2q7dj+Fwj8+28WitNabCjFrDP6Rq3dZika21cO91nWDb4vPd01a5Dvm+zMe3+kvbpxubbHFk7baVOtt7pua9JCdJO4gQhRMag3aecr57p5aYv8P2aqLZ9cJ3dhne7uQ6NOq9dlyRPnQi3EjoSDrBs7I898lRQ32uXPt0Q5gWjvIdQ1ma4pkn7gq2EtoTNhEOsw1ErP31d1zR/+o3p8yJlpS8/7T1SDlf+nDkOSUBfXu2a1i6v55Rj5iee+avv9U+fx1Apr2GuebrVGfJ0yCRPVcRJNuSpvtdGszwNcs3Tr85zP0Y3q52nw8QpN+SpPtdNs2NqgGuerMqQl9OSlw6EZoRQQnVX5hvycqPXU2VesOH80++nhFvNy+SqIR/1vcaa7CcpF/3qPK+/V03ydIw44T/1zNONXH/1+eok+RrhmmdYpeH67LzNvLyshrz5e3022WdSTq7VaG0yMhv435bCvI7ce1sN87YU3ttAmNe1e2sj4n9bB3/bNPjb9iLYocyPavJO+/wrrzuWf1E+KGT5eea76jQscn8g9w1W/nMb2nVjBrXCntgHe2N/vAfH4r2Yg5FYjH3xYbwfH8P++BI+gKcwGuVdCXJfQJqSrv5dCV0k3a4Yit0wCrtLundqY9vLb368XdajH9t8Bss1xpkYhEm6eFaJF2QSb6DEi8EWOEgXz3Gd9Eol3jJJb7n+nRLXiTdf4uVLvAJdvKrrxKuQeI9LvCd08c5eZ/smSjyrbN8kXbyr10kvXeJlSHpzdPGCz3uPt1vi7ZF4e/X77zrxNkq8TRJvM7qPW6vEO2Fy3N7OciEYjPdhKxyAd+BIbIPpGIIObIsLsD1uwjA8jB2xGjtJuhy/8juNeZJuI+wt6dpY7lZMxnaYgh0xFd39kx0Sf6vE1/dPjpW2JEPxfhyOAzEObTgC0zAel+BoXIdjcTOO0+Uz8ife87la8rlG8rlW8rlOFz/5OvEXSPxiib9Q4i/SxS+/TvwdEn+nxH9S4lfq4p+W+B1M4iewXDN8CNvgVAzFabr4V6+T/lxJf56kny3p59TE5/vYe/wDEv+gxD8k8Z/VxbdeJ/4Wif+oxN8q8bdJG5Xwff6Nr6avr2xaUy8p9ZC1+4gnSP3iNdTXG75GqJI6QeoCqfer3bc7ieDu022XOrrPCMbxy6S+zVi/pvXLziZo/bDN+19r9V/jvPexps6KZZYynh0hlmAnlBEOEc4RrhHaPczfCNmEDYR9hDcJVwitS8kzIZlQSthHOFcaqM8KTIEpMAWmwBSYAlNgCkyB6f9hugn1/9lZqTc+/l8n+l8r9V4Rx5RnJvb0jJTCbKdNHtHm2V3tA2ZyU9xHnu1GSf18D6mfDyeUEv/s6+5nu6lZzgLf36s/pKv5GP3HJZ3u8uy/G2E5y1rekHRcXfHz1Qf/fjz31/oHen/ur20rt8zSJ4BlsQhXkIdILQ9KM4S6xwIIIp1YLe181+dwLd0sV7/dd9V1WpZ09SyHQ5KHVlLXqcwsY5ngNyUPajOB9Nw5Wbnp9SwHfV1nfENZWJ6lDSWsVrbZIz3/6qG0fayr91npmkePXmVVMr9dzXx6ISt/8MzbJclbMqE1wUZYy/LlnnlzzJ9Tv7w=
*/