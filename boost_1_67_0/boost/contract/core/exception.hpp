
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