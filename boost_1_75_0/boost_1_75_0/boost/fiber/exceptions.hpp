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
a+se3tZGaGu0Ce+P4DClZGSxc2tDJpxasluxxYsd0WREEQ1Krfsd0LAMeUtAZF+nrLNSfjZU9WQIdntjwG2z5F1t2+i26jV3xeu3TZXYNlW6bVMltk1VkG1zbTRJzUuPUw8QSSB9orYl3rbT5rN9duf7tI1bJ96mcTMRDtlVgdUBM+PbdAi1vCMKZu88On/wGa7nHWjyVPPNNh9mJi4csQTbsHpWpo8PKwNMVKMNBXAsme9XI9+uIfQtY92iQJTJSiSLdrtCu2bWbvMkltxCjbawRvfdSWiiFdCEF5ttEWiiRY8mXKw+Bvss1cKHy9CEV6CJViuM+AuAF8bmgKOXGLvcCZXk0OnDbd0JR3gBR3TWHEfYuxOOoP2OSc+aUHbgE7TdF2VA9V1E9VFoJ+pKsnnGZdCwGARmb2QZ2C5W1sZdHiHgTl7zn5tBhsHAdbsUIUmVUiQ7XC9NDTVlNljkvVslBjCWXaA9m5m2NNWUubtbAzsJU1xsBiOMTyQFR7YQsBkTTCX3hIK7JNyXrxgQ2pIAMi2ehd5MEEllw3G4SomuOect1xJqlOQPQDoAjLaaCkKNl6AcvzVeWoV358RsJmnWWFGsz01gukaoCdnMZDyH5PITx/Tu1KlkU8m3XbnYmzjR8uW8yCE2+qbtYOnIpqo3lUjCEkW8xFZWovkSONcje3ppd4numbKT+KlZwhRrkj/quYejnv3a4ba2
*/