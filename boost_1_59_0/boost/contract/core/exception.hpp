
#ifndef BOOST_CONTRACT_EXCEPTION_HPP_
#define BOOST_CONTRACT_EXCEPTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Handle contract assertion failures.
*/

// IMPORTANT: Included by contract_macro.hpp so trivial headers only.
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/declspec.hpp> // No compile-time overhead.
#include <boost/function.hpp>
#include <boost/config.hpp>
#include <exception>
#include <string>

// NOTE: This code should not change (not even its impl) based on the
// CONTRACT_NO_... macros. For example, preconditions_failure() should still
// all the set precondition failure handler even when NO_PRECONDITIONS is
// #defined, because user code might explicitly call precondition_failure()
// (for whatever reason...). Otherwise, the public API of this lib will change.

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
// Needed for `std::` prefix to show (but removed via `EXCLUDE_SYMBOLS=std`).
namespace std {
    class exception {};
    class bad_cast {};
}
#endif

namespace boost { namespace contract {

/**
Public base class for all exceptions directly thrown by this library.

This class does not inherit from @c std::exception because exceptions deriving
from this class will do that (inheriting from @c std::exception,
@c std::bad_cast, etc.).

@see    @RefClass{boost::contract::assertion_failure},
        @RefClass{boost::contract::bad_virtual_result_cast},
        etc.
*/
class BOOST_CONTRACT_DETAIL_DECLSPEC exception {
public:
    /**
    Destruct this object.

    @b Throws: This is declared @c noexcept (or @c throw() before C++11).
    */
    virtual ~exception() /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;
};

#ifdef BOOST_MSVC
    #pragma warning(push)
    #pragma warning(disable: 4275) // Bases w/o DLL spec (bad_cast, etc).
    #pragma warning(disable: 4251) // Members w/o DLL spec (string for what_).
#endif

/**
Exception thrown when inconsistent return values are passed to overridden
virtual public functions.

This exception is thrown when programmers pass to this library return value
parameters for public function overrides in derived classes that are not
consistent with the return type parameter passed for the virtual public function
being overridden from the base classes.
This allows this library to give more descriptive error messages in such cases
of misuse.

This exception is internally thrown by this library and programmers should not
need to throw it from user code.

@see    @RefSect{tutorial.public_function_overrides__subcontracting_,
        Public Function Overrides}
*/
class BOOST_CONTRACT_DETAIL_DECLSPEC bad_virtual_result_cast : // Copy (as str).
        public std::bad_cast, public boost::contract::exception {
public:
    /**
    Construct this object with the name of the from- and to- result types.

    @param from_type_name Name of the from-type (source of the cast).
    @param to_type_name Name of the to-type (destination of the cast).
    */
    explicit bad_virtual_result_cast(char const* from_type_name,
            char const* to_type_name);

    /**
    Destruct this object.

    @b Throws: This is declared @c noexcept (or @c throw() before C++11).
    */
    virtual ~bad_virtual_result_cast()
            /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

    /**
    Description for this error (containing both from- and to- type names).

    @b Throws: This is declared @c noexcept (or @c throw() before C++11).
    */
    virtual char const* what() const
            /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

/** @cond */
private:
    std::string what_;
/** @endcond */
};

/**
Exception typically used to report a contract assertion failure.

This exception is thrown by code expanded by @RefMacro{BOOST_CONTRACT_ASSERT}
(but it can also be thrown by user code programmed manually without that macro).
This exception is typically used to report contract assertion failures because
it contains detailed information about the file name, line number, and source
code of the asserted condition (so it can be used by this library to provide
detailed error messages when handling contract assertion failures).

However, any other exception can be used to report a contract assertion failure
(including user-defined exceptions).
This library will call the appropriate contract failure handler function
(@RefFunc{boost::contract::precondition_failure}, etc.) when this or any other
exception is thrown while checking contracts (by default, these failure handler
functions print an error message to @c std::cerr and terminate the program, but
they can be customized to take any other action).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}
*/
class BOOST_CONTRACT_DETAIL_DECLSPEC assertion_failure : // Copy (as str, etc.).
        public std::exception, public boost::contract::exception {
public:
    /**
    Construct this object with file name, line number, and source code text of
    an assertion condition (all optional).

    This constructor can also be used to specify no information (default
    constructor), or to specify only file name and line number but not source
    code text (because of the parameter default values).
    
    @param file Name of the file containing the assertion (usually set using
                <c>__FILE__</c>).
    @param line Number of the line containing the assertion (usually set using
                <c>__LINE__</c>).
    @param code Text listing the source code of the assertion condition.
    */
    explicit assertion_failure(char const* file = "", unsigned long line = 0,
            char const* code = "");

    /**
    Construct this object only with the source code text of the assertion
    condition.
    @param code Text listing the source code of the assertion condition.
    */
    explicit assertion_failure(char const* code);
    
    /**
    Destruct this object.

    @b Throws: This is declared @c noexcept (or @c throw() before C++11).
    */
    virtual ~assertion_failure()
            /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

    /**
    String describing the failed assertion.
    
    @b Throws: This is declared @c noexcept (or @c throw() before C++11).
    
    @return A string formatted similarly to the following:
      <c>assertion "`code()`" failed: file "`file()`", line \`line()\`</c>
            (where `` indicate execution quotes).
            File, line, and code will be omitted from this string if they were
            not specified when constructing this object.
    */
    virtual char const* what() const
            /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

    /**
    Name of the file containing the assertion.

    @return File name as specified at construction (or @c "" if no file was
            specified).
    */
    char const* file() const;
    
    /**
    Number of the line containing the assertion.

    @return Line number as specified at construction (or @c 0 if no line number
            was specified).
    */
    unsigned long line() const;
    
    /**
    Text listing the source code of the assertion condition.

    @return Assertion condition source code as specified at construction (or
            @c "" if no source code text was specified).
    */
    char const* code() const;

/** @cond */
private:
    void init();

    char const* file_;
    unsigned long line_;
    char const* code_;
    std::string what_;
/** @endcond */
};

#ifdef BOOST_MSVC
    #pragma warning(pop)
#endif

/**
Indicate the kind of operation where the contract assertion failed.

This is passed as a parameter to the assertion failure handler functions.
For example, it might be necessary to know in which operation an assertion
failed to make sure exceptions are never thrown from destructors, not even
when contract failure handlers are programmed by users to throw exceptions
instead of terminating the program.

@see @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure}
*/
enum from {
    /** Assertion failed when checking contracts for constructors. */
    from_constructor,
    
    /** Assertion failed when checking contracts for destructors . */
    from_destructor,
    
    /**
    Assertion failed when checking contracts for functions (members or not,
    public or not).
    */
    from_function
};

/**
Type of assertion failure handler functions (with @c from parameter).

Assertion failure handler functions specified by this type must be functors
returning @c void and taking a single parameter of type
@RefEnum{boost::contract::from}.
For example, this is used to specify contract failure handlers for class
invariants, preconditions, postconditions, and exception guarantees.

@see @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure}
*/
typedef boost::function<void (from)> from_failure_handler;

/**
Type of assertion failure handler functions (without @c from parameter).

Assertion failure handler functions specified by this type must be nullary
functors returning @c void.
For example, this is used to specify contract failure handlers for
implementation checks.

@see @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure}
*/
typedef boost::function<void ()> failure_handler;

/** @cond */
namespace exception_ {
    // Check failure.

    BOOST_CONTRACT_DETAIL_DECLSPEC
    failure_handler const& set_check_failure_unlocked(failure_handler const& f)
            BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    failure_handler const& set_check_failure_locked(failure_handler const& f)
            BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    failure_handler get_check_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    failure_handler get_check_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    void check_failure_unlocked() /* can throw */;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    void check_failure_locked() /* can throw */;
    
    // Precondition failure.

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_pre_failure_unlocked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_pre_failure_locked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_pre_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_pre_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    void pre_failure_unlocked(from where) /* can throw */;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    void pre_failure_locked(from where) /* can throw */;
    
    // Postcondition failure.

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_post_failure_unlocked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_post_failure_locked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_post_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_post_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    void post_failure_unlocked(from where) /* can throw */;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    void post_failure_locked(from where) /* can throw */;
    
    // Except failure.

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_except_failure_unlocked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_except_failure_locked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_except_failure_unlocked()
            BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_except_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    void except_failure_unlocked(from where) /* can throw */;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    void except_failure_locked(from where) /* can throw */;
    
    // Old-copy failure.

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_old_failure_unlocked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_old_failure_locked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_old_failure_unlocked() BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_old_failure_locked() BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    void old_failure_unlocked(from where) /* can throw */;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    void old_failure_locked(from where) /* can throw */;
    
    // Entry invariant failure.

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_entry_inv_failure_unlocked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_entry_inv_failure_locked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_entry_inv_failure_unlocked()
            BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_entry_inv_failure_locked()
            BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    void entry_inv_failure_unlocked(from where) /* can throw */;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    void entry_inv_failure_locked(from where) /* can throw */;
    
    // Exit invariant failure.

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const& set_exit_inv_failure_unlocked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler const&set_exit_inv_failure_locked(
            from_failure_handler const& f) BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_exit_inv_failure_unlocked()
            BOOST_NOEXCEPT_OR_NOTHROW;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    from_failure_handler get_exit_inv_failure_locked()
            BOOST_NOEXCEPT_OR_NOTHROW;

    BOOST_CONTRACT_DETAIL_DECLSPEC
    void exit_inv_failure_unlocked(from where) /* can throw */;
    BOOST_CONTRACT_DETAIL_DECLSPEC
    void exit_inv_failure_locked(from where) /* can throw */;
}
/** @endcond */

} } // namespace

/** @cond */
#ifdef BOOST_CONTRACT_HEADER_ONLY
    // NOTE: This header must be included in the middle of this file (because
    // its impl depends on both from and assert_failure types). This is not
    // ideal, but it is better than splitting this file into multiple
    // independent ones because all content in this file is logically related
    // from the user prospective.
    #include <boost/contract/detail/inlined/core/exception.hpp>
#endif
/** @endcond */

namespace boost { namespace contract {
    
// Following must be inline for static linkage (no DYN_LINK and no HEADER_ONLY).

/**
Set failure handler for implementation checks.

Set a new failure handler and returns it.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@param f New failure handler functor to set.

@return Same failure handler functor @p f passed as parameter (e.g., for
        concatenating function calls).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{advanced.implementation_checks, Implementation Checks}
*/
inline failure_handler const& set_check_failure(failure_handler const& f)
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::set_check_failure_locked(f);
    #else
        return exception_::set_check_failure_unlocked(f);
    #endif
}

/**
Return failure handler currently set for implementation checks.

This is often called only internally by this library.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@return A copy of the failure handler currently set.

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{advanced.implementation_checks, Implementation Checks}
*/
inline failure_handler get_check_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::get_check_failure_locked();
    #else
        return exception_::get_check_failure_unlocked();
    #endif
}

/**
Call failure handler for implementation checks.

This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on implementation check failures (not the
            default).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{advanced.implementation_checks, Implementation Checks}
*/
inline void check_failure() /* can throw */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        exception_::check_failure_locked();
    #else
        exception_::check_failure_unlocked();
    #endif
}

/**
Set failure handler for preconditions.

Set a new failure handler and returns it.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@param f New failure handler functor to set.

@return Same failure handler functor @p f passed as parameter (e.g., for
        concatenating function calls).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.preconditions, Preconditions}
*/
inline from_failure_handler const& set_precondition_failure(from_failure_handler
        const& f) /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::set_pre_failure_locked(f);
    #else
        return exception_::set_pre_failure_unlocked(f);
    #endif
}

/**
Return failure handler currently set for preconditions.

This is often called only internally by this library.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@return A copy of the failure handler currently set.

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.preconditions, Preconditions}
*/
inline from_failure_handler get_precondition_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::get_pre_failure_locked();
    #else
        return exception_::get_pre_failure_unlocked();
    #endif
}

/**
Call failure handler for preconditions.

This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on contract assertion failures (not the default).

@param where    Operation that failed the contract assertion (when this function
                is called by this library, this parameter will never be
                @c from_destructor because destructors do not have
                preconditions).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.preconditions, Preconditions}
*/
inline void precondition_failure(from where) /* can throw */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        exception_::pre_failure_locked(where);
    #else
        exception_::pre_failure_unlocked(where);
    #endif
}

/**
Set failure handler for postconditions.

Set a new failure handler and returns it.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@param f New failure handler functor to set.

@return Same failure handler functor @p f passed as parameter (e.g., for
        concatenating function calls).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.postconditions, Postconditions}
*/
inline from_failure_handler const& set_postcondition_failure(
    from_failure_handler const& f
) /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::set_post_failure_locked(f);
    #else
        return exception_::set_post_failure_unlocked(f);
    #endif
}

/**
Return failure handler currently set for postconditions.

This is often called only internally by this library.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@return A copy of the failure handler currently set.

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.postconditions, Postconditions}
*/
inline from_failure_handler get_postcondition_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::get_post_failure_locked();
    #else
        return exception_::get_post_failure_unlocked();
    #endif
}

/**
Call failure handler for postconditions.

This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on contract assertion failures (not the default).

@param where    Operation that failed the contract assertion (e.g., this might
                be useful to program failure handler functors that never throw
                from destructors, not even when they are programmed by users to
                throw exceptions instead of terminating the program).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.postconditions, Postconditions}
*/
inline void postcondition_failure(from where) /* can throw */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        exception_::post_failure_locked(where);
    #else
        exception_::post_failure_unlocked(where);
    #endif
}

/**
Set failure handler for exception guarantees.

Set a new failure handler and returns it.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@param f New failure handler functor to set.

@return Same failure handler functor @p f passed as parameter (e.g., for
        concatenating function calls).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.exception_guarantees, Exception Guarantees}
*/
inline from_failure_handler const& set_except_failure(from_failure_handler
        const& f) /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::set_except_failure_locked(f);
    #else
        return exception_::set_except_failure_unlocked(f);
    #endif
}

/**
Return failure handler currently set for exception guarantees.

This is often called only internally by this library.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@return A copy of the failure handler currently set.

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.exception_guarantees, Exception Guarantees}
*/
inline from_failure_handler get_except_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::get_except_failure_locked();
    #else
        return exception_::get_except_failure_unlocked();
    #endif
}

/**
Call failure handler for exception guarantees.

This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on contract assertion failures (not the default),
            however:

@warning    When this failure handler is called there is already an active
            exception (the one that caused the exception guarantees to be
            checked in the first place).
            Therefore, programming this failure handler to throw yet another
            exception will force C++ to automatically terminate the program.

@param where Operation that failed the contract assertion.

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.exception_guarantees, Exception Guarantees}
*/
inline void except_failure(from where) /* can throw */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        exception_::except_failure_locked(where);
    #else
        exception_::except_failure_unlocked(where);
    #endif
}

/**
Set failure handler for old values copied at body.

Set a new failure handler and returns it.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@param f New failure handler functor to set.

@return Same failure handler functor @p f passed as parameter (e.g., for
        concatenating function calls).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{advanced.old_values_copied_at_body, Old Values Copied at Body}
*/
inline from_failure_handler const& set_old_failure(from_failure_handler const&
        f) /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::set_old_failure_locked(f);
    #else
        return exception_::set_old_failure_unlocked(f);
    #endif
}

/**
Return failure handler currently set for old values copied at body.

This is often called only internally by this library.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@return A copy of the failure handler currently set.

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{advanced.old_values_copied_at_body, Old Values Copied at Body}
*/
inline from_failure_handler get_old_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::get_old_failure_locked();
    #else
        return exception_::get_old_failure_unlocked();
    #endif
}

/**
Call failure handler for old values copied at body.

This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on contract assertion failures (not the default).

@param where    Operation that failed the old value copy (e.g., this might
                be useful to program failure handler functors that never throw
                from destructors, not even when they are programmed by users to
                throw exceptions instead of terminating the program).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{advanced.old_values_copied_at_body, Old Values Copied at Body}
*/
inline void old_failure(from where) /* can throw */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        exception_::old_failure_locked(where);
    #else
        exception_::old_failure_unlocked(where);
    #endif
}

/**
Set failure handler for class invariants at entry.

Set a new failure handler and returns it.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@param f New failure handler functor to set.

@return Same failure handler functor @p f passed as parameter (e.g., for
        concatenating function calls).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.class_invariants, Class Invariants},
        @RefSect{extras.volatile_public_functions,
        Volatile Public Functions}
*/
inline from_failure_handler const& set_entry_invariant_failure(
    from_failure_handler const& f
)/** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::set_entry_inv_failure_locked(f);
    #else
        return exception_::set_entry_inv_failure_unlocked(f);
    #endif
}

/**
Return failure handler currently set for class invariants at entry.

This is often called only internally by this library.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@return A copy of the failure handler currently set.

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.class_invariants, Class Invariants},
        @RefSect{extras.volatile_public_functions,
        Volatile Public Functions}
*/
inline from_failure_handler get_entry_invariant_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::get_entry_inv_failure_locked();
    #else
        return exception_::get_entry_inv_failure_unlocked();
    #endif
}

/**
Call failure handler for class invariants at entry.

This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on contract assertion failures (not the default).

@param where    Operation that failed the contract assertion (e.g., this might
                be useful to program failure handler functors that never throw
                from destructors, not even when they are programmed by users to
                throw exceptions instead of terminating the program).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.class_invariants, Class Invariants},
        @RefSect{extras.volatile_public_functions,
        Volatile Public Functions}
*/
inline void entry_invariant_failure(from where) /* can throw */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::entry_inv_failure_locked(where);
    #else
        return exception_::entry_inv_failure_unlocked(where);
    #endif
}

/**
Set failure handler for class invariants at exit.

Set a new failure handler and returns it.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@param f New failure handler functor to set.

@return Same failure handler functor @p f passed as parameter (e.g., for
        concatenating function calls).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.class_invariants, Class Invariants},
        @RefSect{extras.volatile_public_functions,
        Volatile Public Functions}
*/
inline from_failure_handler const& set_exit_invariant_failure(
    from_failure_handler const& f
) /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::set_exit_inv_failure_locked(f);
    #else
        return exception_::set_exit_inv_failure_unlocked(f);
    #endif
}

/**
Return failure handler currently set for class invariants at exit.

This is often called only internally by this library.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@return A copy of the failure handler currently set.

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.class_invariants, Class Invariants},
        @RefSect{extras.volatile_public_functions,
        Volatile Public Functions}
*/
inline from_failure_handler get_exit_invariant_failure()
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        return exception_::get_exit_inv_failure_locked();
    #else
        return exception_::get_exit_inv_failure_unlocked();
    #endif
}

/**
Call failure handler for class invariants at exit.

This is often called only internally by this library.

@b Throws:  This can throw in case programmers specify a failure handler that
            throws exceptions on contract assertion failures (not the default).

@param where    Operation that failed the contract assertion (e.g., this might
                be useful to program failure handler functors that never throw
                from destructors, not even when they are programmed by users to
                throw exceptions instead of terminating the program).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.class_invariants, Class Invariants},
        @RefSect{extras.volatile_public_functions,
        Volatile Public Functions}
*/
inline void exit_invariant_failure(from where) /* can throw */ {
    #ifndef BOOST_CONTRACT_DISABLE_THREADS
        exception_::exit_inv_failure_locked(where);
    #else
        exception_::exit_inv_failure_unlocked(where);
    #endif
}

/**
Set failure handler for class invariants (at both entry and exit).

This is provided for convenience and it is equivalent to call both
@RefFunc{boost::contract::set_entry_invariant_failure} and
@RefFunc{boost::contract::set_exit_invariant_failure} with the same functor
parameter @p f.

@b Throws: This is declared @c noexcept (or @c throw() before C++11).

@param f New failure handler functor to set for both entry and exit invariants.

@return Same failure handler functor @p f passed as parameter (e.g., for
        concatenating function calls).

@see    @RefSect{advanced.throw_on_failures__and__noexcept__, Throw on Failure},
        @RefSect{tutorial.class_invariants, Class Invariants},
        @RefSect{extras.volatile_public_functions,
        Volatile Public Functions}
*/
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
from_failure_handler const& set_invariant_failure(from_failure_handler const& f)
        /** @cond */ BOOST_NOEXCEPT_OR_NOTHROW /** @endcond */;

} } // namespace

#endif // #include guard


/* exception.hpp
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
*/