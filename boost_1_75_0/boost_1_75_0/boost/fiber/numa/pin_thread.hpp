
//          Copyright Oliver Kowalke 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_NUMA_PIN_THREAD_H
#define BOOST_FIBERS_NUMA_PIN_THREAD_H

#include <cstdint>
#include <thread>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace numa {

BOOST_FIBERS_DECL
void pin_thread( std::uint32_t, std::thread::native_handle_type);

BOOST_FIBERS_DECL
void pin_thread( std::uint32_t cpuid);

}}}

#ifdef BOOST_HAS_ABI_HEADERS
# include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_NUMA_PIN_THREAD_H

/* pin_thread.hpp
yOs+tbXK6i49aDWtFFZ3F1a02iqyQLO6k2DMD7xvsLqTGlnduWCXHZ9GmLOwKcNUNr/stI5deR3Emwt/n2xgvPXJ9ZP+EPZk8fUPqfe2+iHqfXL9nX9oNmc36crcpqvbTVemJ93rbcGKeYS28SIMI2MnCsWzQvHMPygNTf3akanf/veARUbc1UQ8wUuv1mOwkwyJcU+TYQpM2q0rQ1FY2RMFJs+jwL0zrPhEscnThq1RsbJ3C2zrIdhDCxHdkjywWPJFBdi2ilNx3U8rWoPrJk1tHGhwLWTUU17cKZjXBTsThA1SvLBQHdJLHQ07wc8ErTe+C5DjdrB3/d+xEV/CqBnbtSTV2HNtCrtEpl8HgQ6s73RJ4fTI6n/x+HFB67H/WEUAjG3PUITSHJJZwXC6rtDPT46YnzvEVEDUem2xhP3ne2IO0vX2n9ockP2nR2Tu9m5xieG/tAMGrdllqhToiKtaXMep7/F+tmN7CryDMg4HInFRsL+3w3oOsaweWFLkw2QXt77XmmWqcotoMppFG/Xz5HaxTMr2xjJpkkdzOcPLVxrkDJbVYD8WtM5YDvTlKb54c5bS4pXA4g2gxUu4BhfPew0u3rEUWrwS5ewyWrySoPW65XzxSpT2lYkmHqx1eGohjPHed60Uwc6N8UQL8+QLuZmPFlgq3sP8yo+XFHmDQUuFC2WnwwpJnX/Xp4xecvo+5HpmUuuD+RHp
*/