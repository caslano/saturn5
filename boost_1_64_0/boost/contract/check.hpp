
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
zr8H3yeCb3FpMc23IC5SYM4hQtzt4zUO/CfgHgX8HjC+YlVx9t1B3wD9Tslx9+e3RMa7gfa58H0jfP8Yvi+D79vg+1eoR/EbuI55CvFzPt7B8V2xKSODMJ+/AppnwfcP4fsS+P4BfP9Wvs+Utpv3wwX7P4UPP7uZdLeFBe8w03ZxH5yGFXtH+HOFRCMiZy3w/vyoS+PhO0rZ+0CH8v1xjq6/74PyOORs6AdUD3D/ttoW2oSTS8/GvwF7Z8+Dvsw1oJur4PtK+dY7ybhNd/us9dy63p8J7xiQHfH7U24XKrxXAHuv/UfwFL4XvGOg9CIhbxZEQ94smJrjzYLZ9s0CeYPqR6hT6vvA1Zvc7dnxmwX9p+E6MAnbEvsWTa53aIZ5F0/q/15ne/fBpepDYV8tnuU8Q9aeLzN40cJwvCsmha/R495c+uY2/adAE3EVr0f6DFdBnqYM4D7Xq8Ef4Z0PuJ57rfijDrDTZvhuhe+N8N0p35rH8+TuT3zTAfstN03Cu1LD97Deom2H4Ni9vLcZGmF7dO8gHLwv5tvi32ZMCGR/XGRfkN6/vKZq5sxpc3R3soPlKUx3M78je5YVTma6pKbeq4K9yr8m3vGWzbxhPNGju5UBIvuVdc/OmXtTIrenkKKxbkZ4X6IDUl3TdRKoa1GQgatNEOznzYT+0zh/9rtJgT+71/RLn3BlNiKwo3tMv/Q+saPfSTq0iw7ZI7xxZHa6B1xfUPTRx7CWrtYY+3gYgzKMx+AKK2QYvbaJb30yzN//r+O/P2WM/2rql9TV0/vYyxfRXXCL69X3GzDu06gebd5JkDvdXdzD4PMf2FPwwBb/OcHHe0zweiWfj1AY32l7lMe267a4Q5J8/nAc549OlHb36XsGjxNOsZ6H5DRsJ8l4X2uit7k77dt7x/JdKCl6oTup9ysXuHUP0MNUz6XIuCw2AEDe9xkV5O/QCRl9az4L8iTRfIp+9h2Bv4gtPD2pv7sGk8lO5U6fyDc20vKiXw5ezwuvFyb1d9dOX4c5DxMAgO9fhQbwZVt7ieDaj6N6wHxfFr6voL1LGrhXmcsS7f01Sfc3sJ1n5Tt8Tp7KsmUDiRlbM3PqnGBWKRuczsc/gHZZEdx9JPL9neLfoN/9+/hvOrw5CfIIZ0b+KbK+JfTmyb7xc7hOdrbHpN400DWKsda+rq4tvEUxLKIfv9SbbM4wRQhLH+DpouxyeTeHPbwnMr8vMsv7BDpW4bh/SdzSHPqO+UecYlIDYx2peBeLFh6V9p8fgv/8z6SgvfnIzPN8PMn9zHteIven6FNGZOc7Lxqe7yFRP/3QaNA/fQfk2SnaT/0YkD/IKxwWDegNj/Zjs4P2s3mFuwDtXYX2Jxl3RnWQj4M2AeZkCwi/MG1HPqxE7vUGGL8tF9G3UomXnHHju4cQtnM0w0eyT84n2GyvpaOHNukm9b5j0m813efbFk+mFPbMJD6PqIftkirziwRv8OF86JEjJc1Dk/j+bqLSm9gCsMPkHiwNt5t7sF4nWI8X3E/+KoU3873ZMelABPBjBM6dDeGxneAn+HDywGTTHXF3Cj7eKzx3ozyfLu3s+u7g3ohzzT0S53skeV9LKkZDMZzDvtCj05EC1vN4l5vzeM6mr3HnIDd56fBNXnd8c8o/n0dJhuwexTUPqYFiUukQ3xvaf33uoRttOVEmSO4AZVsjf819kHUuH84/5HlkkMB/+Gf0DzK3oXOeXFeLotAGwPuVowiO/mJ01P+hvxgj9X1PoPGh+A71PzgnOFbS7xX1ZRgn6cdHM/FcPMq6t+DtE023AYGOP0MboHouYTn8BItFz6WoZ6LdnHTuBwmxlsMimPbc/tpPRWcSBiY=
*/