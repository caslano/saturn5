/* boost random/random_device.hpp header file
 *
 * Copyright Jens Maurer 2000
 * Copyright Steven Watanabe 2010-2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 * Revision history
 *  2000-02-18  Portability fixes (thanks to Beman Dawes)
 */

//  See http://www.boost.org/libs/random for documentation.


#ifndef BOOST_RANDOM_RANDOM_DEVICE_HPP
#define BOOST_RANDOM_RANDOM_DEVICE_HPP

#include <string>
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/random/detail/auto_link.hpp>
#include <boost/system/config.hpp> // force autolink to find Boost.System

namespace boost {
namespace random {

/**
 * Class \random_device models a \nondeterministic_random_number_generator.
 * It uses one or more implementation-defined stochastic processes to
 * generate a sequence of uniformly distributed non-deterministic random
 * numbers. For those environments where a non-deterministic random number
 * generator is not available, class random_device must not be implemented. See
 *
 *  @blockquote
 *  "Randomness Recommendations for Security", D. Eastlake, S. Crocker,
 *  J. Schiller, Network Working Group, RFC 1750, December 1994
 *  @endblockquote
 *
 * for further discussions. 
 *
 * @xmlnote
 * Some operating systems abstract the computer hardware enough
 * to make it difficult to non-intrusively monitor stochastic processes.
 * However, several do provide a special device for exactly this purpose.
 * It seems to be impossible to emulate the functionality using Standard
 * C++ only, so users should be aware that this class may not be available
 * on all platforms.
 * @endxmlnote
 *
 * <b>Implementation Note for Linux</b>
 *
 * On the Linux operating system, token is interpreted as a filesystem
 * path. It is assumed that this path denotes an operating system
 * pseudo-device which generates a stream of non-deterministic random
 * numbers. The pseudo-device should never signal an error or end-of-file.
 * Otherwise, @c std::ios_base::failure is thrown. By default,
 * \random_device uses the /dev/urandom pseudo-device to retrieve
 * the random numbers. Another option would be to specify the /dev/random
 * pseudo-device, which blocks on reads if the entropy pool has no more
 * random bits available.
 *
 * <b>Implementation Note for Windows</b>
 *
 * On the Windows operating system, token is interpreted as the name
 * of a cryptographic service provider.  By default \random_device uses
 * MS_DEF_PROV.
 *
 * <b>Performance</b>
 *
 * The test program <a href="\boost/libs/random/performance/nondet_random_speed.cpp">
 * nondet_random_speed.cpp</a> measures the execution times of the
 * random_device.hpp implementation of the above algorithms in a tight
 * loop. The performance has been evaluated on an
 * Intel(R) Core(TM) i7 CPU Q 840 \@ 1.87GHz, 1867 Mhz with
 * Visual C++ 2010, Microsoft Windows 7 Professional and with gcc 4.4.5,
 * Ubuntu Linux 2.6.35-25-generic.
 *
 * <table cols="2">
 *   <tr><th>Platform</th><th>time per invocation [microseconds]</th></tr>
 *   <tr><td> Windows </td><td>2.9</td></tr>
 *   <tr><td> Linux </td><td>1.7</td></tr>
 * </table>
 *
 * The measurement error is estimated at +/- 1 usec.
 */
class random_device : private noncopyable
{
public:
    typedef unsigned int result_type;
    BOOST_STATIC_CONSTANT(bool, has_fixed_range = false);

    /** Returns the smallest value that the \random_device can produce. */
    static BOOST_CONSTEXPR result_type min BOOST_PREVENT_MACRO_SUBSTITUTION () { return 0; }
    /** Returns the largest value that the \random_device can produce. */
    static BOOST_CONSTEXPR result_type max BOOST_PREVENT_MACRO_SUBSTITUTION () { return ~0u; }

    /** Constructs a @c random_device, optionally using the default device. */
    BOOST_RANDOM_DECL random_device();
    /** 
     * Constructs a @c random_device, optionally using the given token as an
     * access specification (for example, a URL) to some implementation-defined
     * service for monitoring a stochastic process. 
     */
    BOOST_RANDOM_DECL explicit random_device(const std::string& token);

    BOOST_RANDOM_DECL ~random_device();

    /**
     * Returns: An entropy estimate for the random numbers returned by
     * operator(), in the range min() to log2( max()+1). A deterministic
     * random number generator (e.g. a pseudo-random number engine)
     * has entropy 0.
     *
     * Throws: Nothing.
     */
    BOOST_RANDOM_DECL double entropy() const;
    /** Returns a random value in the range [min, max]. */
    BOOST_RANDOM_DECL unsigned int operator()();

    /** Fills a range with random 32-bit values. */
    template<class Iter>
    void generate(Iter begin, Iter end)
    {
        for(; begin != end; ++begin) {
            *begin = (*this)();
        }
    }

private:
    class impl;
    impl * pimpl;
};

} // namespace random

using random::random_device;

} // namespace boost

#endif /* BOOST_RANDOM_RANDOM_DEVICE_HPP */

/* random_device.hpp
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
*/