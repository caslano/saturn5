//
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// based on boost.thread

#ifndef BOOST_fiber_errorS_H
#define BOOST_fiber_errorS_H

#include <future>
#include <stdexcept>
#include <string>
#include <system_error>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class fiber_error : public std::system_error {
public:
    explicit fiber_error( std::error_code ec) :
        std::system_error{ ec } {
    }

    fiber_error( std::error_code ec, const char * what_arg) :
        std::system_error{ ec, what_arg } {
    }

    fiber_error( std::error_code ec, std::string const& what_arg) :
        std::system_error{ ec, what_arg } {
    }

    ~fiber_error() override = default;
};

class lock_error : public fiber_error {
public:
    explicit lock_error( std::error_code ec) :
        fiber_error{ ec } {
    }

    lock_error( std::error_code ec, const char * what_arg) :
        fiber_error{ ec, what_arg } {
    }

    lock_error( std::error_code ec, std::string const& what_arg) :
        fiber_error{ ec, what_arg } {
    }
};

enum class future_errc {
    broken_promise = 1,
    future_already_retrieved,
    promise_already_satisfied,
    no_state
};

BOOST_FIBERS_DECL
std::error_category const& future_category() noexcept;

}}

namespace std {

template<>
struct is_error_code_enum< boost::fibers::future_errc > : public true_type {
};

inline
std::error_code make_error_code( boost::fibers::future_errc e) noexcept {
    return std::error_code{ static_cast< int >( e), boost::fibers::future_category() };
}

inline
std::error_condition make_error_condition( boost::fibers::future_errc e) noexcept {
    return std::error_condition{ static_cast< int >( e), boost::fibers::future_category() };
}

}

namespace boost {
namespace fibers {

class future_error : public fiber_error {
public:
    explicit future_error( std::error_code ec) :
        fiber_error{ ec } {
    }
};

class future_uninitialized : public future_error {
public:
    future_uninitialized() :
        future_error{ std::make_error_code( future_errc::no_state) } {
    }
};

class future_already_retrieved : public future_error {
public:
    future_already_retrieved() :
        future_error{ std::make_error_code( future_errc::future_already_retrieved) } {
    }
};

class broken_promise : public future_error {
public:
    broken_promise() :
        future_error{ std::make_error_code( future_errc::broken_promise) } {
    }
};

class promise_already_satisfied : public future_error {
public:
    promise_already_satisfied() :
        future_error{ std::make_error_code( future_errc::promise_already_satisfied) } {
    }
};

class promise_uninitialized : public future_error {
public:
    promise_uninitialized() :
        future_error{ std::make_error_code( future_errc::no_state) } {
    }
};

class packaged_task_uninitialized : public future_error {
public:
    packaged_task_uninitialized() :
        future_error{ std::make_error_code( future_errc::no_state) } {
    }
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_fiber_errorS_H

/* exceptions.hpp
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
*/