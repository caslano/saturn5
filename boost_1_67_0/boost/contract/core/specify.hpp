
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