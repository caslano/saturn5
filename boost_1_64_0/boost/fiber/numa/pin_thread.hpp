
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
XYIlgqSNLGe8KmcoriUFbjmVQmBjoVvCrIHe17F11vkNw+KsZ+AcYrAUwAFDnEaFldaJOQcft/3HvoAXFnsb51l/QVBmR02WrPhdRA68vlvAfHykcfDdu2syjrURtdm+A7Pphz4DdGhf5689in/Qn71h2ukvxOdsMqWoQb60KAtnmZZWWtMtlz7AP3yFYxL5BF6JvNIFMtD84VdQ45BMYRWi8z+UP7vZg4tTeSvpTXdJrnHJMl8lz54VEdJMW6S/ClHZt52IKMU0BoHoYO/c1Mzg4V15Tq8BobU9IXb8yr0HS1ySEf8pNuvVD/tumk4G8v/N8VSEUbrjAAdSmDRnNN/nBtsus1tTnucHteyxQscBO5zA1TSRZwCyxH2rsjj232XV9LIivtgQfIpLIO+iJJE2Zuz5f3SbBOyxzxURGoqIL9Z2KpQetJ597FKLb7ESKGyA8dev73EQYo0sYR7eR8vkjXaUU5/B3kOBfQY1bm5NFdwz75luEayhKl11VzJlBl/zi+MYOsQyGTOSCYMOzXH/wnsZ4DhkirdNVLOvy9KCNlbduy6KL0jS5Q==
*/