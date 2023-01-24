
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_BARRIER_H
#define BOOST_FIBERS_BARRIER_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/mutex.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class BOOST_FIBERS_DECL barrier {
private:
    std::size_t         initial_;
    std::size_t         current_;
    std::size_t         cycle_{ 0 };
    mutex               mtx_{};
    condition_variable  cond_{};

public:
    explicit barrier( std::size_t);

    barrier( barrier const&) = delete;
    barrier & operator=( barrier const&) = delete;

    bool wait();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_BARRIER_H

/* barrier.hpp
cxQuzFSCi9Pz/P6/MD1tYKf7I8GmJ+MHMSnX/UCTcgRJWuD4RHSZFP61VVV3NaKfnAayxbC5H04kw5B/1DAem50BC7NZ8ao9wGOXJMKZGtjsReiHMPLV65DNnnw9stn98fEwFlKu/Rg4bXrxmnNrkNnmecNeB357RyKexD2P4hPmZ/UnpG9I11tsNeqgO/BmSd1ZhisyQ0RDzMVoiMdNJTPZjzwL2eywOsG7l9PzJqyfXXZKXFEUUmEro5VGGvsijUqa1oztBJE7kOFgQ5AuZ0OQ9ytlb8ZKlmrk+yJ6oikJeYIz1yX0QbORO6kAGHxkgOYpa7kGmwxLdHhonljp23Lh5HuAwOMTbGlcglNeSXYph5UNo897Qc8Fst/tRHa418yLlkTay53AsmBZUoiptAwP4mbv0D5YqnODVmoVqr6G9/2Q1ghkIQ64tT2g/O1nuHIaeumyeIzKB1aWFuJmSYwFMR1BNhReMRRX0P58PK4gVKHM3YMypovqSMZUADKmhDqUMZFCmE1+NJH82IEYYjacdZ1yRCJsjAJUBjsgRE0NpMwjmDSvubyGdMIOQyRCcKjC6NhP6JlXdPI9fSedsol1MpQ6+eLfdJ2s/hA7WVSr6+Ti2qCdrPrtL3SyuZo6eR1qxPIGl70KAiXz0URahzsPaesQF04ruPjWaEluEamdwwk8GiV6wm3rVvC8qMTAlnaz/zOM7C8qrzoj
*/