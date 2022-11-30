
#ifndef BOOST_CONTRACT_DETAIL_INLINED_EXCEPTION_HPP_
#define BOOST_CONTRACT_DETAIL_INLINED_EXCEPTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// IMPORTANT: Do NOT use config macros BOOST_CONTRACT_... in this file so lib
// .cpp does not need recompiling if config changes (recompile only user code).

#include <boost/contract/core/exception.hpp>
#include <boost/contract/detail/static_local_var.hpp>
#include <boost/contract/detail/declspec.hpp>
#include <boost/thread/lock_guard.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/config.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>

namespace boost { namespace contract {

BOOST_CONTRACT_DETAIL_DECLINLINE
exception::~exception() BOOST_NOEXCEPT_OR_NOTHROW {}

BOOST_CONTRACT_DETAIL_DECLINLINE
bad_virtual_result_cast::bad_virtual_result_cast(char const* from_type_name,
            char const* to_type_name) {
    std::ostringstream text;
    text
        << "incompatible contracted virtual function result type "
        << "conversion from '" << from_type_name << "' to '"
        << to_type_name  << "'"
    ;
    what_ = text.str();
}

BOOST_CONTRACT_DETAIL_DECLINLINE
bad_virtual_result_cast::~bad_virtual_result_cast() BOOST_NOEXCEPT_OR_NOTHROW {}

BOOST_CONTRACT_DETAIL_DECLINLINE
char const* bad_virtual_result_cast::what() const BOOST_NOEXCEPT_OR_NOTHROW {
    return what_.c_str();
}

BOOST_CONTRACT_DETAIL_DECLINLINE
assertion_failure::assertion_failure(char const* const file,
        unsigned long const line, char const* const code) :
    file_(file), line_(line), code_(code)
{ init(); }

BOOST_CONTRACT_DETAIL_DECLINLINE
assertion_failure::assertion_failure(char const* const code) :
    file_(""), line_(0), code_(code)
{ init(); }

BOOST_CONTRACT_DETAIL_DECLINLINE
assertion_failure::~assertion_failure() BOOST_NOEXCEPT_OR_NOTHROW {}

BOOST_CONTRACT_DETAIL_DECLINLINE
char const* assertion_failure::what() const BOOST_NOEXCEPT_OR_NOTHROW {
    return what_.c_str();
}

BOOST_CONTRACT_DETAIL_DECLINLINE
char const* assertion_failure::file() const { return file_; }

BOOST_CONTRACT_DETAIL_DECLINLINE
unsigned long assertion_failure::line() const { return line_; }

BOOST_CONTRACT_DETAIL_DECLINLINE
char const* assertion_failure::code() const { return code_; }

BOOST_CONTRACT_DETAIL_DECLINLINE
void assertion_failure::init() {
    std::ostringstream text;
    text << "assertion";
    if(std::string(code_) != "") text << " \"" << code_ << "\"";
    text << " failed";
    if(std::string(file_) != "") {
        text << ": file \"" << file_ << "\"";
        if(line_ != 0) text << ", line " << line_;
    }
    what_ = text.str();
}

namespace exception_ {
    enum failure_key {
        check_failure_key,
        pre_failure_key,
        post_failure_key,
        except_failure_key,
        old_failure_key,
        entry_inv_failure_key,
        exit_inv_failure_key
    };

    template<failure_key Key>
    void default_handler() {
        std::string k = "";
        switch(Key) {
            case check_failure_key: k = "check "; break;
            case pre_failure_key: k = "precondition "; break;
            case post_failure_key: k = "postcondition "; break;
            case except_failure_key: k = "except "; break;
            case old_failure_key: k = "old copy "; break;
            case entry_inv_failure_key: k = "entry invariant "; break;
            case exit_inv_failure_key: k = "exit invariant "; break;
            // No default (so compiler warning/error on missing enum case).
        }
        try { throw; }
        catch(boost::contract::assertion_failure const& error) {
            // what = "assertion '...' failed: ...".
            std::cerr << k << error.what() << std::endl;
        } catch(...) { // old_failure_key prints this, not above.
            std::cerr << k << "threw following exception:" << std::endl
                    << boost::current_exception_diagnostic_information();
        }
        std::terminate(); // Default handlers log and call terminate.
    }
    
    template<failure_key Key>
    void default_from_handler(from) { default_handler<Key>(); }

    // Check failure.

    struct check_failure_mutex_tag;
    typedef boost::contract::detail::static_local_var<check_failure_mutex_tag,
            boost::mutex> check_failure_mutex;

    struct check_failure_handler_tag;
    typedef boost::contract::detail::static_local_var_init<
        check_failure_handler_tag,
        failure_handler, 
        void (*)(),
        &default_handler<check_failure_key>
    > check_failure_handler;

    BOOST_CONTRACT_DETAIL_DECLINLINE
    failure_handler const& set_check_failure_unlocked(failure_handler const& f)
            BOOST_NOEXCEPT_OR_NOTHROW {
        check_failure_handler::ref() = f;
        return f;
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    failure_handler const& set_check_failure_locked(failure_handler const& f)
            BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(check_failure_mutex::ref());
        return set_check_failure_unlocked(f);
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    failure_handler get_check_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW {
        return check_failure_handler::ref();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    failure_handler get_check_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(check_failure_mutex::ref());
        return get_check_failure_unlocked();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    void check_failure_unlocked() /* can throw */ {
        check_failure_handler::ref()();
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    void check_failure_locked() /* can throw */ {
        boost::lock_guard<boost::mutex> lock(check_failure_mutex::ref());
        check_failure_unlocked();
    }
    
    // Precondition failure.

    struct pre_failure_mutex_tag;
    typedef boost::contract::detail::static_local_var<pre_failure_mutex_tag,
            boost::mutex> pre_failure_mutex;

    struct pre_failure_handler_tag;
    typedef boost::contract::detail::static_local_var_init<
        pre_failure_handler_tag,
        from_failure_handler,
        void (*)(from),
        &default_from_handler<pre_failure_key>
    > pre_failure_handler;

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_pre_failure_unlocked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        pre_failure_handler::ref() = f;
        return f;
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_pre_failure_locked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(pre_failure_mutex::ref());
        return set_pre_failure_unlocked(f);
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_pre_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW {
        return pre_failure_handler::ref();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_pre_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(pre_failure_mutex::ref());
        return get_pre_failure_unlocked();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    void pre_failure_unlocked(from where) /* can throw */ {
        pre_failure_handler::ref()(where);
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    void pre_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(pre_failure_mutex::ref());
        pre_failure_unlocked(where);
    }
    
    // Postcondition failure.

    struct post_failure_mutex_tag;
    typedef boost::contract::detail::static_local_var<post_failure_mutex_tag,
            boost::mutex> post_failure_mutex;

    struct post_failure_handler_tag;
    typedef boost::contract::detail::static_local_var_init<
        post_failure_handler_tag,
        from_failure_handler,
        void (*)(from),
        &default_from_handler<post_failure_key>
    > post_failure_handler;

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_post_failure_unlocked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        post_failure_handler::ref() = f;
        return f;
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_post_failure_locked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(post_failure_mutex::ref());
        return set_post_failure_unlocked(f);
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_post_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW {
        return post_failure_handler::ref();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_post_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(post_failure_mutex::ref());
        return get_post_failure_unlocked();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    void post_failure_unlocked(from where) /* can throw */ {
        post_failure_handler::ref()(where);
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    void post_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(post_failure_mutex::ref());
        post_failure_unlocked(where);
    }
    
    // Except failure.

    struct except_failure_mutex_tag;
    typedef boost::contract::detail::static_local_var<except_failure_mutex_tag,
            boost::mutex> except_failure_mutex;

    struct except_failure_handler_tag;
    typedef boost::contract::detail::static_local_var_init<
        except_failure_handler_tag,
        from_failure_handler,
        void (*)(from),
        &default_from_handler<except_failure_key>
    > except_failure_handler;

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_except_failure_unlocked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        except_failure_handler::ref() = f;
        return f;
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_except_failure_locked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(except_failure_mutex::ref());
        return set_except_failure_unlocked(f);
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_except_failure_unlocked()
            BOOST_NOEXCEPT_OR_NOTHROW {
        return except_failure_handler::ref();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_except_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(except_failure_mutex::ref());
        return get_except_failure_unlocked();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    void except_failure_unlocked(from where) /* can throw */ {
        except_failure_handler::ref()(where);
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    void except_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(except_failure_mutex::ref());
        except_failure_unlocked(where);
    }

    // Old-copy failure.

    struct old_failure_mutex_tag;
    typedef boost::contract::detail::static_local_var<old_failure_mutex_tag,
            boost::mutex> old_failure_mutex;

    struct old_failure_handler_tag;
    typedef boost::contract::detail::static_local_var_init<
        old_failure_handler_tag,
        from_failure_handler,
        void (*)(from),
        &default_from_handler<old_failure_key>
    > old_failure_handler;

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_old_failure_unlocked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        old_failure_handler::ref() = f;
        return f;
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_old_failure_locked(from_failure_handler
            const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(old_failure_mutex::ref());
        return set_old_failure_unlocked(f);
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_old_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW {
        return old_failure_handler::ref();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_old_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(old_failure_mutex::ref());
        return get_old_failure_unlocked();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    void old_failure_unlocked(from where) /* can throw */ {
        old_failure_handler::ref()(where);
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    void old_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(old_failure_mutex::ref());
        old_failure_unlocked(where);
    }
    
    // Entry invariant failure.

    struct entry_inv_failure_mutex_tag;
    typedef boost::contract::detail::static_local_var<
            entry_inv_failure_mutex_tag, boost::mutex> entry_inv_failure_mutex;

    struct entry_inv_failure_handler_tag;
    typedef boost::contract::detail::static_local_var_init<
        entry_inv_failure_handler_tag,
        from_failure_handler,
        void (*)(from),
        &default_from_handler<entry_inv_failure_key>
    > entry_inv_failure_handler;

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_entry_inv_failure_unlocked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        entry_inv_failure_handler::ref() = f;
        return f;
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_entry_inv_failure_locked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(entry_inv_failure_mutex::ref());
        return set_entry_inv_failure_unlocked(f);
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_entry_inv_failure_unlocked()
            BOOST_NOEXCEPT_OR_NOTHROW {
        return entry_inv_failure_handler::ref();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_entry_inv_failure_locked()
            BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(entry_inv_failure_mutex::ref());
        return get_entry_inv_failure_unlocked();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    void entry_inv_failure_unlocked(from where) /* can throw */ {
        entry_inv_failure_handler::ref()(where);
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    void entry_inv_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(entry_inv_failure_mutex::ref());
        entry_inv_failure_unlocked(where);
    }
    
    // Exit invariant failure.

    struct exit_inv_failure_mutex_tag;
    typedef boost::contract::detail::static_local_var<
            exit_inv_failure_mutex_tag, boost::mutex> exit_inv_failure_mutex;

    struct exit_inv_failure_handler_tag;
    typedef boost::contract::detail::static_local_var_init<
        exit_inv_failure_handler_tag,
        from_failure_handler,
        void (*)(from),
        &default_from_handler<exit_inv_failure_key>
    > exit_inv_failure_handler;

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_exit_inv_failure_unlocked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        exit_inv_failure_handler::ref() = f;
        return f;
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler const& set_exit_inv_failure_locked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(exit_inv_failure_mutex::ref());
        return set_exit_inv_failure_unlocked(f);
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_exit_inv_failure_unlocked()
            BOOST_NOEXCEPT_OR_NOTHROW {
        return exit_inv_failure_handler::ref();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    from_failure_handler get_exit_inv_failure_locked()
            BOOST_NOEXCEPT_OR_NOTHROW {
        boost::lock_guard<boost::mutex> lock(exit_inv_failure_mutex::ref());
        return get_exit_inv_failure_unlocked();
    }

    BOOST_CONTRACT_DETAIL_DECLINLINE
    void exit_inv_failure_unlocked(from where) /* can throw */ {
        exit_inv_failure_handler::ref()(where);
    }
    
    BOOST_CONTRACT_DETAIL_DECLINLINE
    void exit_inv_failure_locked(from where) /* can throw */ {
        boost::lock_guard<boost::mutex> lock(exit_inv_failure_mutex::ref());
        exit_inv_failure_unlocked(where);
    }
}

from_failure_handler const& set_entry_invariant_failure(
        from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

from_failure_handler const& set_exit_invariant_failure(
        from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

BOOST_CONTRACT_DETAIL_DECLINLINE
from_failure_handler const& set_invariant_failure(
        from_failure_handler const& f)  BOOST_NOEXCEPT_OR_NOTHROW {
    set_entry_invariant_failure(f);
    set_exit_invariant_failure(f);
    return f;
}

} } // namespace

#endif // #include guard


/* exception.hpp
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
*/