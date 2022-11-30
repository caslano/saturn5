
#ifndef BOOST_CONTRACT_SPECIFY_HPP_
#define BOOST_CONTRACT_SPECIFY_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Specify preconditions, old values copied at body, postconditions, and exception
guarantees

Preconditions, old values copied at body, postconditions, and exception
guarantees are all optionals but, when they are specified, they need to be
specified in that order.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/decl.hpp>
#if     !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
        defined(BOOST_CONTRACT_STATIC_LINK)
    #include <boost/contract/detail/condition/cond_base.hpp>
    #include <boost/contract/detail/condition/cond_post.hpp>
    #include <boost/contract/detail/auto_ptr.hpp>
    #include <boost/contract/detail/none.hpp>
#endif
#if     !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
        !defined(BOOST_CONTRACT_NO_EXCEPTS)
    #include <boost/contract/detail/debug.hpp>
#endif
#include <boost/config.hpp>

// NOTE: No inheritance for faster run-times (macros to avoid duplicated code).

/* PRIVATE */

/* @cond */

// NOTE: Private copy ops below will force compile-time error is `auto c = ...`
// is used instead of `check c = ...` but only up to C++17. C++17 strong copy
// elision on function return values prevents this lib from generating a
// compile-time error in those cases, but the lib will still generate a run-time
// error according with ON_MISSING_CHECK_DECL. Furthermore, on some C++98
// compilers, this private copy ctor gives a warning (because of lack of copy
// optimization on those compilers), this warning can be ignored.
#if     !defined(BOOST_CONTRACT_NO_CONDITIONS) || \
        defined(BOOST_CONTRACT_STATIC_LINK)
    #define BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(class_type, cond_type) \
        private: \
            boost::contract::detail::auto_ptr<cond_type > cond_; \
            explicit class_type(cond_type* cond) : cond_(cond) {} \
            class_type(class_type const& other) : cond_(other.cond_) {} \
            class_type& operator=(class_type const& other) { \
                cond_ = other.cond_; \
                return *this; \
            }
    
    #define BOOST_CONTRACT_SPECIFY_COND_RELEASE_ cond_.release()
#else
    #define BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(class_type, cond_type) \
        private: \
            class_type() {} \
            class_type(class_type const&) {} \
            class_type& operator=(class_type const&) { return *this; }

    #define BOOST_CONTRACT_SPECIFY_COND_RELEASE_ /* nothing */
#endif

#ifndef BOOST_CONTRACT_NO_PRECONDITIONS
    #define BOOST_CONTRACT_SPECIFY_PRECONDITION_IMPL_ \
        BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
        cond_->set_pre(f); \
        return specify_old_postcondition_except<VirtualResult>( \
                BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#else
    #define BOOST_CONTRACT_SPECIFY_PRECONDITION_IMPL_ \
        return specify_old_postcondition_except<VirtualResult>( \
                BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#endif
        
#ifndef BOOST_CONTRACT_NO_OLDS
    #define BOOST_CONTRACT_SPECIFY_OLD_IMPL_ \
        BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
        cond_->set_old(f); \
        return specify_postcondition_except<VirtualResult>( \
                BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#else
    #define BOOST_CONTRACT_SPECIFY_OLD_IMPL_ \
        return specify_postcondition_except<VirtualResult>( \
                BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#endif
            
#ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
    #define BOOST_CONTRACT_SPECIFY_POSTCONDITION_IMPL_ \
        BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
        cond_->set_post(f); \
        return specify_except(BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#else
    #define BOOST_CONTRACT_SPECIFY_POSTCONDITION_IMPL_ \
        return specify_except(BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#endif
        
#ifndef BOOST_CONTRACT_NO_EXCEPTS
    #define BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_ \
        BOOST_CONTRACT_DETAIL_DEBUG(cond_); \
        cond_->set_except(f); \
        return specify_nothing(BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#else
    #define BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_ \
        return specify_nothing(BOOST_CONTRACT_SPECIFY_COND_RELEASE_);
#endif

/* @endcond */

/* CODE */

namespace boost {
    namespace contract {
        class virtual_;
        
        template<typename VR>
        class specify_precondition_old_postcondition_except;
        
        template<typename VR>
        class specify_old_postcondition_except;
        
        template<typename VR>
        class specify_postcondition_except;
        
        class specify_except;
    }
}

namespace boost { namespace contract {

/**
Used to prevent setting other contract conditions after exception guarantees.

This class has no member function so it is used to prevent specifying additional
functors to check any other contract.
This object is internally constructed by the library when users specify
contracts calling @RefFunc{boost::contract::function} and similar functions
(that is why this class does not have a public constructor).

@see @RefSect{tutorial, Tutorial}
*/
class specify_nothing { // Privately copyable (as *).
public:
    /**
    Destruct this object.

    @b Throws:  This is declared @c noexcept(false) since C++11 to allow users
                to program failure handlers that throw exceptions on contract
                assertion failures (not the default, see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).
    */
    ~specify_nothing() BOOST_NOEXCEPT_IF(false) {}
    
    // No set member function here.

/** @cond */
private:
    BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(specify_nothing,
            boost::contract::detail::cond_base)

    // Friends (used to limit library's public API).

    friend class check;

    template<typename VR>
    friend class specify_precondition_old_postcondition_except;
    
    template<typename VR>
    friend class specify_old_postcondition_except;

    template<typename VR>
    friend class specify_postcondition_except;

    friend class specify_except;
/** @endcond */
};

/**
Allow to specify exception guarantees.

Allow to specify the functor this library will call to check exception
guarantees.
This object is internally constructed by the library when users specify
contracts calling @RefFunc{boost::contract::function} and similar functions
(that is why this class does not have a public constructor).

@see @RefSect{tutorial.exception_guarantees, Exception Guarantees}
*/
class specify_except { // Privately copyable (as *).
public:
    /**
    Destruct this object.

    @b Throws:  This is declared @c noexcept(false) since C++11 to allow users
                to program failure handlers that throw exceptions on contract
                assertion failures (not the default, see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).
    */
    ~specify_except() BOOST_NOEXCEPT_IF(false) {}

    /**
    Allow to specify exception guarantees.

    @param f    Nullary functor called by this library to check exception
                guarantees @c f().
                Assertions within this functor are usually programmed using
                @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a
                call to this functor indicates a contract assertion failure (and
                will result in this library calling
                @RefFunc{boost::contract::except_failure}).
                This functor should capture variables by (constant) references
                (to access the values they will have at function exit).

    @return After exception guarantees have been specified, the object returned
            by this function does not allow to specify any additional contract.
    */
    template<typename F>
    specify_nothing except(
        F const&
        #if !defined(BOOST_CONTRACT_NO_EXCEPTS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            f
        #endif // Else, no name (avoid unused param warning).
    ) { BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_ }

/** @cond */
private:
    BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(specify_except,
            boost::contract::detail::cond_base)

    // Friends (used to limit library's public API).

    friend class check;

    template<typename VR>
    friend class specify_precondition_old_postcondition_except;
    
    template<typename VR>
    friend class specify_old_postcondition_except;
    
    template<typename VR>
    friend class specify_postcondition_except;
/** @endcond */
};

/**
Allow to specify postconditions or exception guarantees.

Allow to specify functors this library will call to check postconditions or
exception guarantees.
This object is internally constructed by the library when users specify
contracts calling @RefFunc{boost::contract::function} and similar functions
(that is why this class does not have a public constructor).

@see    @RefSect{tutorial.postconditions, Postconditions},
        @RefSect{tutorial.exception_guarantees, Exception Guarantees}

@tparam VirtualResult   Return type of the enclosing function declaring the
                        contract if that is either a virtual or an
                        overriding public function, otherwise this is always
                        @c void.
                        (Usually this template parameter is automatically
                        deduced by C++ and it does not need to be explicitly
                        specified by programmers.)
*/
template<typename VirtualResult = void>
class specify_postcondition_except { // Privately copyable (as *).
public:
    /**
    Destruct this object.

    @b Throws:  This is declared @c noexcept(false) since C++11 to allow users
                to program failure handlers that throw exceptions on contract
                assertion failures (not the default, see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).
    */
    ~specify_postcondition_except() BOOST_NOEXCEPT_IF(false) {}

    /**
    Allow to specify postconditions.

    @param f    Functor called by this library to check postconditions
                @c f() or @c f(result).
                Assertions within this functor are usually programmed using
                @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a
                call to this functor indicates a contract assertion failure (and
                will result in this library calling
                @RefFunc{boost::contract::postcondition_failure}).
                This functor should capture variables by (constant) references
                (to access the values they will have at function exit).
                This functor must be a nullary functor @c f() if
                @c VirtualResult is @c void, otherwise it must be a unary
                functor @c f(result) accepting the return value @c result as a
                parameter of type <c>VirtualResult const&</c> (to avoid extra
                copies of the return value, or of type @c VirtualResult or
                <c>VirtualResult const</c> if extra copies of the return value
                are irrelevant).

    @return After postconditions have been specified, the object returned by
            this function allows to optionally specify exception guarantees.
    */
    template<typename F>
    specify_except postcondition(
        F const&
        #if !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            f
        #endif // Else, no name (avoid unused param warning).
    ) {
        BOOST_CONTRACT_SPECIFY_POSTCONDITION_IMPL_
    }
    
    /**
    Allow to specify exception guarantees.

    @param f    Nullary functor called by this library to check exception
                guarantees @c f().
                Assertions within this functor are usually programmed using
                @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a
                call to this functor indicates a contract assertion failure (and
                will result in this library calling
                @RefFunc{boost::contract::except_failure}).
                This functor should capture variables by (constant) references
                (to access the values they will have at function exit).

    @return After exception guarantees have been specified, the object returned
            by this function does not allow to specify any additional contract.
    */
    template<typename F>
    specify_nothing except(
        F const&
        #if !defined(BOOST_CONTRACT_NO_EXCEPTS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            f
        #endif // Else, no name (avoid unused param warning).
    ) { BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_ }

/** @cond */
private:
    BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(
        specify_postcondition_except,
        boost::contract::detail::cond_post<typename
                boost::contract::detail::none_if_void<VirtualResult>::type>
    )

    // Friends (used to limit library's public API).

    friend class check;
    friend class specify_precondition_old_postcondition_except<VirtualResult>;
    friend class specify_old_postcondition_except<VirtualResult>;
/** @endcond */
};

/**
Allow to specify old values copied at body, postconditions, and exception
guarantees.

Allow to specify functors this library will call to copy old values at body, 
check postconditions, and check exception guarantees.
This object is internally constructed by the library when users specify
contracts calling @RefFunc{boost::contract::function} and similar functions
(that is why this class does not have a public constructor).

@see    @RefSect{advanced.old_values_copied_at_body, Old Values Copied at Body},
        @RefSect{tutorial.postconditions, Postconditions},
        @RefSect{tutorial.exception_guarantees, Exception Guarantees}

@tparam VirtualResult   Return type of the enclosing function declaring the
                        contract if that is either a virtual or an
                        overriding public function, otherwise this is always
                        @c void.
                        (Usually this template parameter is automatically
                        deduced by C++ and it does not need to be explicitly
                        specified by programmers.)
*/
template<typename VirtualResult = void>
class specify_old_postcondition_except { // Privately copyable (as *).
public:
    /**
    Destruct this object.

    @b Throws:  This is declared @c noexcept(false) since C++11 to allow users
                to program failure handlers that throw exceptions on contract
                assertion failures (not the default, see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).
    */
    ~specify_old_postcondition_except() BOOST_NOEXCEPT_IF(false) {}
    
    /**
    Allow to specify old values copied at body.

    It should often be sufficient to initialize old value pointers as soon as
    they are declared, without using this function (see
    @RefSect{advanced.old_values_copied_at_body, Old Values Copied at Body}).

    @param f    Nullary functor called by this library @c f() to assign old
                value copies just before the body is executed but after entry
                invariants (when they apply) and preconditions are checked.
                Old value pointers within this functor call are usually assigned
                using @RefMacro{BOOST_CONTRACT_OLDOF}.
                Any exception thrown by a call to this functor will result in
                this library calling @RefFunc{boost::contract::old_failure}
                (because old values could not be copied to check postconditions
                and exception guarantees).
                This functor should capture old value pointers by references so
                they can be assigned (all other variables needed to evaluate old
                value expressions can be captured by (constant) value, or better
                by (constant) reference to avoid extra copies).

    @return After old values copied at body have been specified, the object
            returned by this function allows to optionally specify
            postconditions and exception guarantees.
    */
    template<typename F>
    specify_postcondition_except<VirtualResult> old(
        F const&
        #if !defined(BOOST_CONTRACT_NO_OLDS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            f
        #endif // Else, no name (avoid unused param warning).
    ) {
        BOOST_CONTRACT_SPECIFY_OLD_IMPL_
    }

    /**
    Allow to specify postconditions.

    @param f    Functor called by this library to check postconditions
                @c f() or @c f(result).
                Assertions within this functor are usually programmed using
                @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a
                call to this functor indicates a contract assertion failure (and
                will result in this library calling
                @RefFunc{boost::contract::postcondition_failure}).
                This functor should capture variables by (constant) references
                (to access the values they will have at function exit).
                This functor must be a nullary functor @c f() if
                @c VirtualResult is @c void, otherwise it must be a unary
                functor @c f(result) accepting the return value @c result as a
                parameter of type <c>VirtualResult const&</c> (to avoid extra
                copies of the return value, or of type @c VirtualResult or
                <c>VirtualResult const</c> if extra copies of the return value
                are irrelevant).

    @return After postconditions have been specified, the object returned by
            this function allows to optionally specify exception guarantees.
    */
    template<typename F>
    specify_except postcondition(
        F const&
        #if !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            f
        #endif // Else, no name (avoid unused param warning).
    ) {
        BOOST_CONTRACT_SPECIFY_POSTCONDITION_IMPL_
    }
    
    /**
    Allow to specify exception guarantees.

    @param f    Nullary functor called by this library to check exception
                guarantees @c f().
                Assertions within this functor are usually programmed using
                @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a
                call to this functor indicates a contract assertion failure (and
                will result in this library calling
                @RefFunc{boost::contract::except_failure}).
                This functor should capture variables by (constant) references
                (to access the values they will have at function exit).

    @return After exception guarantees have been specified, the object returned
            by this function does not allow to specify any additional contract.
    */
    template<typename F>
    specify_nothing except(
        F const&
        #if !defined(BOOST_CONTRACT_NO_EXCEPTS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            f
        #endif // Else, no name (avoid unused param warning).
    ) { BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_ }

/** @cond */
private:
    BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(
        specify_old_postcondition_except,
        boost::contract::detail::cond_post<typename
                boost::contract::detail::none_if_void<VirtualResult>::type>
    )

    // Friends (used to limit library's public API).

    friend class check;
    friend class specify_precondition_old_postcondition_except<VirtualResult>;

    template<class C>
    friend specify_old_postcondition_except<> constructor(C*);

    template<class C>
    friend specify_old_postcondition_except<> destructor(C*);
/** @endcond */
};

/**
Allow to specify preconditions, old values copied at body, postconditions, and
exception guarantees.

Allow to specify functors this library will call to check preconditions, copy
old values at body, check postconditions, and check exception guarantees.
This object is internally constructed by the library when users specify
contracts calling @RefFunc{boost::contract::function} and similar functions
(that is why this class does not have a public constructor).

@see    @RefSect{tutorial.preconditions, Preconditions},
        @RefSect{advanced.old_values_copied_at_body, Old Values Copied at Body},
        @RefSect{tutorial.postconditions, Postconditions},
        @RefSect{tutorial.exception_guarantees, Exception Guarantees}

@tparam VirtualResult   Return type of the enclosing function declaring the
                        contract if that is either a virtual or an
                        overriding public function, otherwise this is always
                        @c void.
                        (Usually this template parameter is automatically
                        deduced by C++ and it does not need to be explicitly
                        specified by programmers.)
*/
template<
    typename VirtualResult /* = void (already in fwd decl from decl.hpp) */
    #ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
        = void
    #endif
>
class specify_precondition_old_postcondition_except { // Priv. copyable (as *).
public:
    /**
    Destruct this object.

    @b Throws:  This is declared @c noexcept(false) since C++11 to allow users
                to program failure handlers that throw exceptions on contract
                assertion failures (not the default, see
                @RefSect{advanced.throw_on_failures__and__noexcept__,
                Throw on Failure}).
    */
    ~specify_precondition_old_postcondition_except() BOOST_NOEXCEPT_IF(false) {}
    
    /**
    Allow to specify preconditions.

    @param f    Nullary functor called by this library to check preconditions
                @c f().
                Assertions within this functor are usually programmed using
                @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a
                call to this functor indicates a contract assertion failure (and
                will result in this library calling
                @RefFunc{boost::contract::precondition_failure}).
                This functor should capture variables by (constant) value, or
                better by (constant) reference (to avoid extra copies).

    @return After preconditions have been specified, the object returned by this
            function allows to optionally specify old values copied at body,
            postconditions, and exception guarantees.
    */
    template<typename F>
    specify_old_postcondition_except<VirtualResult> precondition(
        F const&
        #if !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            f
        #endif // Else, no name (avoid unused param warning).
    ) {
        BOOST_CONTRACT_SPECIFY_PRECONDITION_IMPL_
    }

    /**
    Allow to specify old values copied at body.

    It should often be sufficient to initialize old value pointers as soon as
    they are declared, without using this function (see
    @RefSect{advanced.old_values_copied_at_body, Old Values Copied at Body}).

    @param f    Nullary functor called by this library @c f() to assign old
                value copies just before the body is executed but after entry
                invariants (when they apply) and preconditions are checked.
                Old value pointers within this functor call are usually assigned
                using @RefMacro{BOOST_CONTRACT_OLDOF}.
                Any exception thrown by a call to this functor will result in
                this library calling @RefFunc{boost::contract::old_failure}
                (because old values could not be copied to check postconditions
                and exception guarantees).
                This functor should capture old value pointers by references so
                they can be assigned (all other variables needed to evaluate old
                value expressions can be captured by (constant) value, or better
                by (constant) reference to avoid extra copies).

    @return After old values copied at body have been specified, the object
            returned by this functions allows to optionally specify
            postconditions and exception guarantees.
    */
    template<typename F>
    specify_postcondition_except<VirtualResult> old(
        F const&
        #if !defined(BOOST_CONTRACT_NO_OLDS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            f
        #endif // Else, no name (avoid unused param warning).
    ) {
        BOOST_CONTRACT_SPECIFY_OLD_IMPL_
    }

    /**
    Allow to specify postconditions.

    @param f    Functor called by this library to check postconditions
                @c f() or @c f(result).
                Assertions within this functor are usually programmed using
                @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a
                call to this functor indicates a contract assertion failure (and
                will result in this library calling
                @RefFunc{boost::contract::postcondition_failure}).
                This functor should capture variables by (constant) references
                (to access the values they will have at function exit).
                This functor must be a nullary functor @c f() if
                @c VirtualResult is @c void, otherwise it must be a unary
                functor @c f(result) accepting the return value @c result as a
                parameter of type <c>VirtualResult const&</c> (to avoid extra
                copies of the return value, or of type @c VirtualResult or
                <c>VirtualResult const</c> if extra copies of the return value
                are irrelevant).

    @return After postconditions have been specified, the object returned by
            this function allows to optionally specify exception guarantees.
    */
    template<typename F>
    specify_except postcondition(
        F const&
        #if !defined(BOOST_CONTRACT_NO_POSTCONDITIONS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            f
        #endif // Else, no name (avoid unused param warning).
    ) {
        BOOST_CONTRACT_SPECIFY_POSTCONDITION_IMPL_
    }
    
    /**
    Allow to specify exception guarantees.

    @param f    Nullary functor called by this library to check exception
                guarantees @c f().
                Assertions within this functor are usually programmed using
                @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown by a
                call to this functor indicates a contract assertion failure (and
                will result in this library calling
                @RefFunc{boost::contract::except_failure}).
                This functor should capture variables by (constant) references
                (to access the values they will have at function exit).

    @return After exception guarantees have been specified, the object returned
            by this function does not allow to specify any additional contract.
    */
    template<typename F>
    specify_nothing except(
        F const&
        #if !defined(BOOST_CONTRACT_NO_EXCEPTS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            f
        #endif // Else, no name (avoid unused param warning).
    ) { BOOST_CONTRACT_SPECIFY_EXCEPT_IMPL_ }

/** @cond */
private:
    BOOST_CONTRACT_SPECIFY_CLASS_IMPL_(
        specify_precondition_old_postcondition_except,
        boost::contract::detail::cond_post<typename
                boost::contract::detail::none_if_void<VirtualResult>::type>
    )

    // Friends (used to limit library's public API).

    friend class check;
    friend specify_precondition_old_postcondition_except<> function();

    template<class C>
    friend specify_precondition_old_postcondition_except<> public_function();

    template<class C>
    friend specify_precondition_old_postcondition_except<> public_function(C*);
    
    template<class C>
    friend specify_precondition_old_postcondition_except<> public_function(
            virtual_*, C*);

    template<typename VR, class C>
    friend specify_precondition_old_postcondition_except<VR> public_function(
            virtual_*, VR&, C*);

    BOOST_CONTRACT_DETAIL_DECL_FRIEND_OVERRIDING_PUBLIC_FUNCTIONS_Z(1,
            O, VR, F, C, Args, v, r, f, obj, args)
/** @endcond */
};

} } // namespace

#endif // #include guard


/* specify.hpp
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
*/