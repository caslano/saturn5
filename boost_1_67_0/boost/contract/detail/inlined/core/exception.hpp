
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