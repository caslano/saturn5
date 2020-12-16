
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_MUTEX_H
#define BOOST_FIBERS_MUTEX_H

#include <boost/config.hpp>

#include <boost/assert.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {

class condition_variable;

class BOOST_FIBERS_DECL mutex {
private:
    friend class condition_variable;

    using wait_queue_type = context::wait_queue_t;

    detail::spinlock            wait_queue_splk_{};
    wait_queue_type             wait_queue_{};
    context                 *   owner_{ nullptr };

public:
    mutex() = default;

    ~mutex() {
        BOOST_ASSERT( nullptr == owner_);
        BOOST_ASSERT( wait_queue_.empty() );
    }

    mutex( mutex const&) = delete;
    mutex & operator=( mutex const&) = delete;

    void lock();

    bool try_lock();

    void unlock();
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_MUTEX_H

/* mutex.hpp
nIXsj0oApc/qKW1s7HXZSe8Z/fzTds3jCXk/q4lMdOkKeU5kqDxR0RXVl6pDKAOrUrU/F6orcld7+Q15irgKmjr0lLL9Hltb+HvE+ArAAJHEeQkh+lcRAjBNTVqtZBS/6Yc9leyeLZ+KQTXMl0Jck0+tf55dyGYCu6KnDNn8C2BOpo3qRdcdZm0Rjo0igynuQjocvnld8i7g7dZv2TZVv9ADXD9oIzfXb0aPWP38qn7+Dut3U4/4+l3Wk+pXuJnrF6PYc7fUz3Z+N7CmDz+nLA0rns/S78vge2/nbbGZ6dbTzJL1DhvZL+dx6NL1MNNtTtEuHMGKjH1czOJVx5pSTxKp/iqBdCMhffJtmqBNSP2I9IIU3T5IJmIPYEAbgb5JWySV3f48NhcZnvvNDnyC4lNE8RRB8RIzxXvRUrrLpe3+1zgUshlvkkJdLvFsIzypAk+pGc+5iOcB3tpf+S4NyimPiEG5EHT2IXIPXOb8YSPnZBG5zyGHAoocKO8BKJcXLN4gLacnmbdv/Np61lt/nVOtTrO8OMJ462c6NRsRmZ/5FgnEO2SxxLuLQe+UPFTqnmIG1TvzLZv2m7gO6r1ewAMUSvpQT/UBOAGBSZnJ8db53L93w8HvcHHNEqHd8CainWBG6wW0KJsijMYZFJC70LhVHrk8BZZH8Kl4Q/x4ZfQ/BNdBf2xh1+gpVCuDNhjKoE5ljtmC+DdEfKggnmkmfuNajfhb0gWhTN04RSQfXSpJbqDo2uRB/MkbXmnYHQ5uFtqnCih7Dlun75CHQGqksp2mKEYuFHGBlIpaGtK01XIPUV/xO1GhsWKFOXsIVijdLSpU+QZW6CJzhZpBY2H0HnxyshC0LhMW6Hz9Xo+yHW3/z/d6JPvTppLyZjHAKgf22Mg+ChRwGWk+IMPD5WbP7IV/+ta6Imk8iXgULE4myY395H9tF/+vqc18HSWrl5cbb6fxlOZU6XQ0oidQF2GhceQRc1bBHfGRAP8qlwsBVkCzQaVQdy8HjOKVQtnFWGjhx+B/drMkg14MzFA8qZAIrKxlHQtYBW1Cm/IYdf3oBjFsBqulEvfqb9uiZqZrb4+Pm3c0FgmY8N+ZRlNud8LTCHigYI9IWng0dvsvfoz+S3eI/Ds/6y2U3z3B/g9P8aw9Rx3YY1/L768Wh9jwQCCnvQaNoK4fuohWE6fu4Fm8gUeG+x4QXwthOIJ4sbrZ28hc1MYX0EwhLB6BpYsZyziBJXJO7JpIZuS0O2MoqgjFs6/YMPIzQtGXAT96UwC6ba+PXP1C209wfaQ1/uPj4nPQVQqxI/rvrqZVSuz2kZGbpQTiB0HhemZ+Uqcqrfrpd1sFQdIfu74oTc4cWLWbMfQtIk0n8LpgB4scwgFQBQsEnP9bAg6oe3c+fywpjpLQLyvEV95qPp7FW1Rq1lHG5mHrzfqZDJS1jU2VQ+6X1uiGBOen3GK+dbj4ZBBCHfW6gDpEi6l83ktedTJoPkvZpvtAWxnCmFGFGk8TNrSqnyzk0LxCV0KWEfeUhyVHfxeU76Foeg5AT227dI6N5ryKmHj3RRJ1ExMFyMT9jqSYYLt/kWGsE3wMUSq7cOkmMlcIMl3MZF68Fww5I8RkzyrYeGjARwVM6rEAg2JEtmiP4YUvQy8cf44UOngkBlbAJgttwPcp2bSVmuHbF6gZikFnID1iL7Ya6fYdPlm4eLPdyUKrDPNRQxHa6i+vxB8snOXEC1NIJH61Vpdyyj+HRfzJtWqXJoGIp5CIO00iPnpHTMQn02ef+TyLeD1/9jdBNw6/IJRW68XtfJAP8f1lneTiTkGtmr7nIYCS1ilPz7LxnqghwimCcImZ8BggHDkzAVVNji8=
*/