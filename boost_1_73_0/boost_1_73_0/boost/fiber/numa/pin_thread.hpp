
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
BV1TUNHr94XYeRmr3Jf8iZbdx14AbzAqMJ0EvMSEFZFMWnDlpefhPIUrJ46dIF1AeAZOsBjxLrzgFLnB0KsAum0FlRiFALZua0aLPec/ddINOz2H2Tz2wyjNojj8sshSP3Hm6XkWOUlyFcan8BrM4zcQ8BvN8jcmmDVbaRrAW/uXV/ZLFOinjBJ5m0mqdMPxi9ySCJ+cQ+BcusYTPpZHSFEpN1wUI1ugxPxbwbe3gNpAOqxNo1hONHKPmyyCMEq8xHjBmrzuCgonOpCBotUHo/eZc5R/Hd9Ev4HDCslTI4cejw1pWxEBh+2mOPitd3zqJrPYi1IvDIwIowYyqoyTRtYUeTQO524kW86afhI0s5quro8011hDNGV2uRsPctd632aOU6MqXoBsac5K5AZskDVa2ViW3vczSReRO3l9sCyjsTE2xPTvjiHL0BCH+1HreeLGuoV7CMOGWFEcUWUbht4hpEWujkEWHKEbroZFhEn9RWnbZ6THpLnGJcNx6ICUWASNobRQLydjjHAs9Jkz91MjmPt+L8DI0nAW+onh6M2AEveLcxn5rmE3pTF0tafm7w96zhqmJtg6Vk608AD+MeBbSmjBPRXwsMDcLT26JTiI1M75emoi0pPmfQUfAPQ8fr7lXucQJomjHzDe
*/