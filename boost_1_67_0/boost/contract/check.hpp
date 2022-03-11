
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