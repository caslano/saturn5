
#ifndef BOOST_CONTRACT_CHECK_HPP_
#define BOOST_CONTRACT_CHECK_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
RAII object that checks contracts.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/check_macro.hpp>
#include <boost/contract/core/specify.hpp>
#include <boost/contract/core/exception.hpp> // For set_... (if always in code).
#if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
        defined(BOOST_CONTRACT_STATIC_LINK)
    #include <boost/contract/detail/condition/cond_base.hpp>
    #include <boost/contract/detail/auto_ptr.hpp>
    #include <boost/contract/detail/debug.hpp>
#endif
#include <boost/contract/detail/check.hpp>
#include <boost/config.hpp>

/* PRIVATE */

/** @cond */

#if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
        defined(BOOST_CONTRACT_STATIC_LINK)
    #define BOOST_CONTRACT_CHECK_CTOR_DEF_(contract_type) \
        : cond_(const_cast<contract_type&>(contract).cond_.release()) \
        { \
            BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
            cond_->initialize(); \
        }
#else
    #define BOOST_CONTRACT_CHECK_CTOR_DEF_(contract_type) {}
#endif

/** @endcond */

/* CODE */

namespace boost { namespace contract {

/**
RAII object that checks the contracts.

In general, when this object is constructed it checks class invariants at entry,
preconditions, and makes old value copies at body.
When it is destructed, it checks class invariants at exist, postconditions, and
exception guarantees.
This object enforces the following (see
@RefSect{contract_programming_overview, Contract Programming Overview}):

@li Postconditions are checked only if the body does not throw an exception.
@li Exceptions guarantees are checked only if the body throws an exception.
@li Constructor entry never checks class invariants.
@li Destructor exit checks class invariants only if the body throws an
exception (even if destructors should usually not be programmed to throw
exceptions in C++ and they are implicitly declared @c noexcept since C++11).
@li Static invariants are always checked at entry and exit (and regardless of
the body throwing exceptions or not).

When used this way, this object is constructed and initialized to the return
value of one of the contract functions @RefFunc{boost::contract::function},
@RefFunc{boost::contract::constructor}, @RefFunc{boost::contract::destructor},
or @RefFunc{boost::contract::public_function}.
In addition to that, this object can be constructed from a nullary functor when
it is used to program implementation checks.

@see    @RefSect{tutorial, Tutorial},
        @RefSect{advanced.implementation_checks, Implementation Checks}
*/
class check { // Copy ctor only (as move via ptr release).
public:
    // NOTE: Unfortunately, Apple compilers define a `check(...)` macro that
    // clashes with the name of this class. In the following code,
    // BOOST_PREVENT_MACRO_SUBSTITUTION is used to workaround these name
    // clashes. In user code, `check c = ...` syntax is typically used also
    // avoiding clashes.

    /**
    Construct this object for implementation checks.

    This can be used to program checks within implementation code (body, etc.).
    This constructor is not declared @c explicit so initializations can use
    assignment syntax @c =.
    
    @b Throws:  This can throw in case programmers specify contract failure
                handlers that throw exceptions instead of terminating the
                program (see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).

    @param f    Nullary functor that asserts implementation checks. @c f() will
                be called as soon as this object is constructed at the point it
                is declared within the implementation code (see
                @RefSect{advanced.implementation_checks,
                Implementation Checks}).
    */
    template<typename F> // Cannot check `if(f) ...` as f can be a lambda.
    // f must be a valid callable object (not null func ptr, empty ftor, etc.
    /* implicit */ check
    /** @cond **/ BOOST_PREVENT_MACRO_SUBSTITUTION /** @endcond */ (
            F const& f) {
        BOOST_CONTRACT_DETAIL_CHECK({ f(); })
    }

    /**
    Construct this object copying it from the specified one.

    This object will check the contract, the copied-from object will not (i.e.,
    contract check ownership is transferred from the copied object to the new
    object being created by this constructor).

    @param other    Copied-from object.
    */
    check /** @cond **/ BOOST_PREVENT_MACRO_SUBSTITUTION /** @endcond */ (
            check const& other)
        #if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
                defined(BOOST_CONTRACT_STATIC_LINK)
            // Copy ctor moves cond_ pointer to dest.
            : cond_(const_cast<check&>(other).cond_.release())
        #endif
    {}

    /**
    Construct this object to check the specified contract.

    This checks class invariants at entry (if those were specified for the given
    contract).
    This constructor is not declared @c explicit so initializations can use
    assignment syntax @c =.
    
    @b Throws:  This can throw in case programmers specify contract failure
                handlers that throw exceptions instead of terminating the
                program (see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).

    @param contract Contract to be checked (usually the return value of
                    @RefFunc{boost::contract::function} or
                    @RefFunc{boost::contract::public_function}).

    @tparam VirtualResult   Return type of the enclosing function declaring the
                            contract if that is either a virtual or an
                            overriding public function, otherwise this is always
                            @c void.
                            (Usually this template parameter is automatically
                            deduced by C++ and it does not need to be explicitly
                            specified by programmers.)
    */
    template<typename VirtualResult>
    /* implicit */ check
    /** @cond */ BOOST_PREVENT_MACRO_SUBSTITUTION /** @endcond */ (
        specify_precondition_old_postcondition_except<VirtualResult> const&
                contract
    )
    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(
                specify_precondition_old_postcondition_except<VirtualResult>)
    #else
        ;
    #endif
    
    /**
    Construct this object to check the specified contract.

    This checks class invariants at entry and preconditions (if any of those
    were specified for the given contract).
    This constructor is not declared @c explicit so initializations can use
    assignment syntax @c =.
    
    @b Throws:  This can throw in case programmers specify contract failure
                handlers that throw exceptions instead of terminating the
                program (see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).

    @param contract Contract to be checked (usually the return value of
                    @RefFunc{boost::contract::function},
                    @RefFunc{boost::contract::constructor},
                    @RefFunc{boost::contract::destructor}, or
                    @RefFunc{boost::contract::public_function}).

    @tparam VirtualResult   Return type of the enclosing function declaring the
                            contract if that is either a virtual or an
                            overriding public function, otherwise this is always
                            @c void.
                            (Usually this template parameter is automatically
                            deduced by C++ and it does not need to be explicitly
                            specified by programmers.)
    */
    template<typename VirtualResult>
    /* implicit */ check
    /** @cond */ BOOST_PREVENT_MACRO_SUBSTITUTION /** @endcond */ (
            specify_old_postcondition_except<VirtualResult> const& contract)
    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(
                specify_old_postcondition_except<VirtualResult>)
    #else
        ;
    #endif
    
    /**
    Construct this object to check the specified contract.

    This checks class invariants at entry and preconditions then it makes old
    value copies at body (if any of those were specified for the given
    contract).
    This constructor is not declared @c explicit so initializations can use
    assignment syntax @c =.
    
    @b Throws:  This can throw in case programmers specify contract failure
                handlers that throw exceptions instead of terminating te
                program (see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).

    @param contract Contract to be checked (usually the return value of
                    @RefFunc{boost::contract::function},
                    @RefFunc{boost::contract::constructor},
                    @RefFunc{boost::contract::destructor}, or
                    @RefFunc{boost::contract::public_function}).

    @tparam VirtualResult   Return type of the enclosing function declaring the
                            contract if that is either a virtual or an
                            overriding public function, otherwise this is always
                            @c void.
                            (Usually this template parameter is automatically
                            deduced by C++ and it does not need to be explicitly
                            specified by programmers.)
    */
    template<typename VirtualResult>
    /* implicit */ check
    /** @cond */ BOOST_PREVENT_MACRO_SUBSTITUTION /** @endcond */ (
            specify_postcondition_except<VirtualResult> const& contract)
    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(
                specify_postcondition_except<VirtualResult>)
    #else
        ;
    #endif
    
    /**
    Construct this object to check the specified contract.

    This checks class invariants at entry and preconditions then it makes old
    value copies at body, plus the destructor of this object will also check
    postconditions in this case (if any of those were specified for the given
    contract).
    This constructor is not declared @c explicit so initializations can use
    assignment syntax @c =.
    
    @b Throws:  This can throw in case programmers specify contract failure
                handlers that throw exceptions instead of terminating the
                program (see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).

    @param contract Contract to be checked (usually the return value of
                    @RefFunc{boost::contract::function},
                    @RefFunc{boost::contract::constructor},
                    @RefFunc{boost::contract::destructor}, or
                    @RefFunc{boost::contract::public_function}).

    @tparam VirtualResult   Return type of the enclosing function declaring the
                            contract if that is either a virtual or an
                            overriding public function, otherwise this is always
                            @c void.
                            (Usually this template parameter is automatically
                            deduced by C++ and it does not need to be explicitly
                            specified by programmers.)
    */
    /* implicit */ check
    /** @cond */ BOOST_PREVENT_MACRO_SUBSTITUTION /** @endcond */ (
            specify_except const& contract)
    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(specify_except)
    #else
        ;
    #endif
    
    /**
    Construct this object to check the specified contract.

    This checks class invariants at entry and preconditions then it makes old
    value copies at body, plus the destructor of this object will also check
    postconditions and exception guarantees in this case (if any of those were
    specified for the given contract).
    This constructor is not declared @c explicit so initializations can use
    assignment syntax @c =.
    
    @b Throws:  This can throw in case programmers specify contract failure
                handlers that throw exceptions instead of terminating the
                program (see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).

    @param contract Contract to be checked (usually the return value of
                    @RefFunc{boost::contract::function},
                    @RefFunc{boost::contract::constructor},
                    @RefFunc{boost::contract::destructor}, or
                    @RefFunc{boost::contract::public_function}).

    @tparam VirtualResult   Return type of the enclosing function declaring the
                            contract if that is either a virtual or an
                            overriding public function, otherwise this is always
                            @c void.
                            (Usually this template parameter is automatically
                            deduced by C++ and it does not need to be explicitly
                            specified by programmers.)
    */
    /* implicit */ check
    /** @cond */ BOOST_PREVENT_MACRO_SUBSTITUTION /** @endcond */ (
            specify_nothing const& contract)
    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        BOOST_CONTRACT_CHECK_CTOR_DEF_(specify_nothing)
    #else
        ;
    #endif

    /**
    Destruct this object.

    This checks class invariants at exit and either postconditions when the
    enclosing function body did not throw an exception, or exception guarantees
    when the function body threw an exception (if class invariants,
    postconditions, and exception guarantees respectively were specified for the
    enclosing class and the contract parameter given when constructing this
    object).

    @b Throws:  This can throw in case programmers specify contract failure
                handlers that throw exceptions instead of terminating the
                program (see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).
                (This is declared @c noexcept(false) since C++11.)
    */
    ~check /** @cond */ BOOST_PREVENT_MACRO_SUBSTITUTION /** @endcond */ ()
        BOOST_NOEXCEPT_IF(false) /* allow auto_ptr dtor to throw */
    {}

/** @cond */
private:
    check& operator=(check const&); // Cannot copy outside of `check c = ...`.

    #if !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
            defined(BOOST_CONTRACT_STATIC_LINK)
        boost::contract::detail::auto_ptr<boost::contract::detail::cond_base>
                cond_;
    #endif
/** @endcond */
};

} } // namespace

#endif // #include guard


/* check.hpp
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
*/