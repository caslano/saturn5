
#ifndef BOOST_CONTRACT_OLD_HPP_
#define BOOST_CONTRACT_OLD_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Handle old values.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/virtual.hpp>
#ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
    #include <boost/contract/detail/checking.hpp>
#endif
#include <boost/contract/detail/operator_safe_bool.hpp>
#include <boost/contract/detail/declspec.hpp>
#include <boost/contract/detail/debug.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/is_copy_constructible.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/static_assert.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/config/config.hpp>
#include <queue>

#if !BOOST_PP_VARIADICS

#define BOOST_CONTRACT_OLDOF \
BOOST_CONTRACT_ERROR_macro_OLDOF_requires_variadic_macros_otherwise_manually_program_old_values

#else // variadics

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/config.hpp>

/* PRIVATE */

/** @cond */

#ifdef BOOST_NO_CXX11_AUTO_DECLARATIONS
    #define BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value) /* nothing */
#else
    #include <boost/typeof/typeof.hpp>
    // Explicitly force old_ptr<...> conversion to allow for C++11 auto decl.
    #define BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value) \
        boost::contract::old_ptr<BOOST_TYPEOF(value)>
#endif

#define BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_2( \
        v, value) \
    BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value)(boost::contract::make_old(v, \
        boost::contract::copy_old(v) ? (value) : boost::contract::null_old() \
    ))

#define BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_1( \
        value) \
    BOOST_CONTRACT_OLDOF_AUTO_TYPEOF_(value)(boost::contract::make_old( \
        boost::contract::copy_old() ? (value) : boost::contract::null_old() \
    ))

/** @endcond */

/* PUBLIC */

// NOTE: Leave this #defined the same regardless of ..._NO_OLDS.
/**
Macro typically used to copy an old value expression and assign it to an old
value pointer.

The expression expanded by this macro should be assigned to an old value
pointer of type @RefClass{boost::contract::old_ptr} or
@RefClass{boost::contract::old_ptr_if_copyable}.
This is an overloaded variadic macro and it can be used in the following
different ways.

1\. From within virtual public functions and public functions overrides:

@code
BOOST_CONTRACT_OLDOF(v, old_expr)
@endcode

2\. From all other operations:

@code
BOOST_CONTRACT_OLDOF(old_expr)
@endcode

Where:

@arg    <c><b>v</b></c> is the extra parameter of type
        @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
        from the enclosing virtual public function or public function
        overrides declaring the contract.
@arg    <c><b>old_expr</b></c> is the expression to be evaluated and copied into
        the old value pointer.
        (This is not a variadic macro parameter so any comma it might contain
        must be protected by round parenthesis and
        <c>BOOST_CONTRACT_OLDOF(v, (old_expr))</c> will always work.)

On compilers that do not support variadic macros, programmers can manually copy
old value expressions without using this macro (see
@RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}).

@see @RefSect{tutorial.old_values, Old Values}
*/
#define BOOST_CONTRACT_OLDOF(...) \
    BOOST_PP_CAT( /* CAT(..., EMTPY()) required on MSVC */ \
        BOOST_PP_OVERLOAD( \
  BOOST_CONTRACT_ERROR_macro_OLDOF_has_invalid_number_of_arguments_, \
            __VA_ARGS__ \
        )(__VA_ARGS__), \
        BOOST_PP_EMPTY() \
    )

#endif // variadics

/* CODE */

namespace boost { namespace contract {

/**
Trait to check if an old value type can be copied or not.

By default, this unary boolean meta-function is equivalent to
@c boost::is_copy_constructible<T> but programmers can chose to specialize it
for user-defined types (in general some kind of specialization is also needed on
compilers that do not support C++11, see
<a href="http://www.boost.org/doc/libs/release/libs/type_traits/doc/html/boost_typetraits/reference/is_copy_constructible.html">
<c>boost::is_copy_constructible</c></a>):

@code
class u; // Some user-defined type for which old values shall not be copied.

namespace boost { namespace contract {
    template<> // Specialization to not copy old values of type `u`.
    struct is_old_value_copyable<u> : boost::false_type {};
} } // namespace
@endcode

A given old value type @c T is copied only if
@c boost::contract::is_old_value_copyable<T>::value is @c true.
A copyable old value type @c V is always copied using
@c boost::contract::old_value_copy<V>.
A non-copyable old value type @c W generates a compile-time error when
@c boost::contract::old_ptr<W> is dereferenced, but instead leaves
@c boost::contract::old_ptr_if_copyable<W> always null (without generating
compile-time errors).

@see    @RefSect{extras.old_value_requirements__templates_,
        Old Value Requirements}
*/
template<typename T>
struct is_old_value_copyable : boost::is_copy_constructible<T> {};

/** @cond */
class old_value;

template<> // Needed because `old_value` incomplete type when trait first used.
struct is_old_value_copyable<old_value> : boost::true_type {};
/** @endcond */

/**
Trait to copy an old value.

By default, the implementation of this trait uses @c T's copy constructor to
make one single copy of the specified value.
However, programmers can specialize this trait to copy old values using
user-specific operations different from @c T's copy constructor.
The default implementation of this trait is equivalent to:

@code
template<typename T>
class old_value_copy {
public:
    explicit old_value_copy(T const& old) :
        old_(old) // One single copy of value using T's copy constructor.
    {}

    T const& old() const { return old_; }

private:
    T const old_; // The old value copy.
};
@endcode

This library will instantiate and use this trait only on old value types @c T
that are copyable (i.e., for which
<c>boost::contract::is_old_value_copyable<T>::value</c> is @c true).

@see    @RefSect{extras.old_value_requirements__templates_,
        Old Value Requirements}
*/
template<typename T> // Used only if is_old_value_copyable<T>.
struct old_value_copy {
    /**
    Construct this object by making one single copy of the specified old value.

    This is the only operation within this library that actually copies old
    values.
    This ensures this library makes one and only one copy of an old value (if
    they actually need to be copied, see @RefMacro{BOOST_CONTRACT_NO_OLDS}).

    @param old The old value to copy.
    */
    explicit old_value_copy(T const& old) :
            old_(old) {} // This makes the one single copy of T.

    /**
    Return a (constant) reference to the old value that was copied.
    
    Contract assertions should not change the state of the program so the old
    value copy is returned as @c const (see
    @RefSect{contract_programming_overview.constant_correctness,
    Constant Correctness}).
    */
    T const& old() const { return old_; }

private:
    T const old_;
};

template<typename T>
class old_ptr_if_copyable;

/**
Old value pointer that requires the pointed old value type to be copyable.

This pointer can be set to point an actual old value copy using either
@RefMacro{BOOST_CONTRACT_OLDOF} or @RefFunc{boost::contract::make_old} (that is
why this class does not have public non-default constructors):

@code
class u {
public:
    virtual void f(..., boost::contract::virtual_* v = 0) {
        boost::contract::old_ptr<old_type> old_var = // For copyable `old_type`.
                BOOST_CONTRACT_OLDOF(v, old_expr);
        ...
    }

    ...
};
@endcode

@see @RefSect{tutorial.old_values, Old Values}

@tparam T Type of the pointed old value.
        This type must be copyable (i.e.,
        <c>boost::contract::is_old_value_copyable<T>::value</c> must be
        @c true), otherwise this pointer will always be null and this library
        will generate a compile-time error when the pointer is dereferenced.
*/
template<typename T>
class old_ptr { /* copyable (as *) */
public:
    /** Pointed old value type. */
    typedef T element_type;

    /** Construct this old value pointer as null. */
    old_ptr() {}

    /**
    Dereference this old value pointer.

    This will generate a run-time error if this pointer is null and a
    compile-time error if the pointed type @c T is not copyable (i.e., if
    @c boost::contract::is_old_value_copyable<T>::value is @c false).
    
    @return The pointed old value.
            Contract assertions should not change the state of the program so
            this member function is @c const and it returns the old value as a
            reference to a constant object (see
            @RefSect{contract_programming_overview.constant_correctness,
            Constant Correctness}).
    */
    T const& operator*() const {
        BOOST_STATIC_ASSERT_MSG(
            boost::contract::is_old_value_copyable<T>::value,
            "old_ptr<T> requires T copyable (see is_old_value_copyable<T>), "
            "otherwise use old_ptr_if_copyable<T>"
        );
        BOOST_CONTRACT_DETAIL_DEBUG(typed_copy_);
        return typed_copy_->old();
    }

    /**
    Structure-dereference this old value pointer.

    This will generate a compile-time error if the pointed type @c T is not
    copyable (i.e., if @c boost::contract::is_old_value_copyable<T>::value is
    @c false).

    @return A pointer to the old value (null if this old value pointer is null).
            Contract assertions should not change the state of the program so
            this member function is @c const and it returns the old value as a
            pointer to a constant object (see
            @RefSect{contract_programming_overview.constant_correctness,
            Constant Correctness}).
    */
    T const* operator->() const {
        BOOST_STATIC_ASSERT_MSG(
            boost::contract::is_old_value_copyable<T>::value,
            "old_ptr<T> requires T copyble (see is_old_value_copyable<T>), "
            "otherwise use old_ptr_if_copyable<T>"
        );
        if(typed_copy_) return &typed_copy_->old();
        return 0;
    }

    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(old_ptr<T>,
                !!typed_copy_)
    #else
        /**
        Query if this old value pointer is null or not (safe-bool operator).

        (This is implemented using safe-bool emulation on compilers that do not
        support C++11 explicit type conversion operators.)

        @return True if this pointer is not null, false otherwise.
        */
        explicit operator bool() const;
    #endif

/** @cond */
private:
    #ifndef BOOST_CONTRACT_NO_OLDS
        explicit old_ptr(boost::shared_ptr<old_value_copy<T> > old)
                : typed_copy_(old) {}
    #endif

    boost::shared_ptr<old_value_copy<T> > typed_copy_;

    friend class old_pointer;
    friend class old_ptr_if_copyable<T>;
/** @endcond */
};

/**
Old value pointer that does not require the pointed old value type to be
copyable.

This pointer can be set to point to an actual old value copy using either
@RefMacro{BOOST_CONTRACT_OLDOF} or @RefFunc{boost::contract::make_old}:

@code
template<typename T> // Type `T` might or not be copyable.
class u {
public:
    virtual void f(..., boost::contract::virtual_* v = 0) {
        boost::contract::old_ptr_if_copyable<T> old_var =
                BOOST_CONTRACT_OLDOF(v, old_expr);
        ...
            if(old_var) ... // Always null for non-copyable types.
        ...
    }

    ...
};
@endcode

@see    @RefSect{extras.old_value_requirements__templates_,
        Old Value Requirements}

@tparam T Type of the pointed old value.
        If this type is not copyable (i.e.,
        <c>boost::contract::is_old_value_copyable<T>::value</c> is @c false),
        this pointer will always be null (but this library will not generate a
        compile-time error when this pointer is dereferenced).
*/
template<typename T>
class old_ptr_if_copyable { /* copyable (as *) */
public:
    /** Pointed old value type. */
    typedef T element_type;

    /** Construct this old value pointer as null. */
    old_ptr_if_copyable() {}

    /**
    Construct this old value pointer from an old value pointer that requires
    the old value type to be copyable.
    
    Ownership of the pointed value object is transferred to this pointer.
    This constructor is implicitly called by this library when assigning an
    object of this type using @RefMacro{BOOST_CONTRACT_OLDOF} (this constructor
    is usually not explicitly called by user code).

    @param other    Old value pointer that requires the old value type to be
                    copyable.
    */
    /* implicit */ old_ptr_if_copyable(old_ptr<T> const& other) :
            typed_copy_(other.typed_copy_) {}

    /**
    Dereference this old value pointer.

    This will generate a run-time error if this pointer is null, but no
    compile-time error is generated if the pointed type @c T is not copyable
    (i.e., if @c boost::contract::is_old_value_copyable<T>::value is @c false).
    
    @return The pointed old value.
            Contract assertions should not change the state of the program so
            this member function is @c const and it returns the old value as a
            reference to a constant object (see
            @RefSect{contract_programming_overview.constant_correctness,
            Constant Correctness}).
    */
    T const& operator*() const {
        BOOST_CONTRACT_DETAIL_DEBUG(typed_copy_);
        return typed_copy_->old();
    }

    /**
    Structure-dereference this old value pointer.

    This will return null but will not generate a compile-time error if the
    pointed type @c T is not copyable (i.e., if
    @c boost::contract::is_old_value_copyable<T>::value is @c false).

    @return A pointer to the old value (null if this old value pointer is null).
            Contract assertions should not change the state of the program so
            this member function is @c const and it returns the old value as a
            pointer to a constant object (see
            @RefSect{contract_programming_overview.constant_correctness,
            Constant Correctness}).
    */
    T const* operator->() const {
        if(typed_copy_) return &typed_copy_->old();
        return 0;
    }

    #ifndef BOOST_CONTRACT_DETAIL_DOXYGEN
        BOOST_CONTRACT_DETAIL_OPERATOR_SAFE_BOOL(old_ptr_if_copyable<T>,
                !!typed_copy_)
    #else
        /**
        Query if this old value pointer is null or not (safe-bool operator).

        (This is implemented using safe-bool emulation on compilers that do not
        support C++11 explicit type conversion operators.)

        @return True if this pointer is not null, false otherwise.
        */
        explicit operator bool() const;
    #endif

/** @cond */
private:
    #ifndef BOOST_CONTRACT_NO_OLDS
        explicit old_ptr_if_copyable(boost::shared_ptr<old_value_copy<T> > old)
                : typed_copy_(old) {}
    #endif

    boost::shared_ptr<old_value_copy<T> > typed_copy_;

    friend class old_pointer;
/** @endcond */
};

/**
Convert user-specified expressions to old values.

This class is usually only implicitly used by this library and it does not
explicitly appear in user code.

On older compilers that cannot correctly deduce the
@c boost::contract::is_old_value_copyable trait used in the declaration of this
class, programmers can manually specialize that trait to make sure that only old
value types that are copyable are actually copied.

@see    @RefSect{extras.old_value_requirements__templates_,
        Old Value Requirements}
*/
class old_value { // Copyable (as *). 
public:
    // Following implicitly called by ternary operator `... ? ... : null_old()`.

    /**
    Construct this object from the specified old value when the old value type
    is copy constructible.

    The specified old value @c old is copied (one time only) using
    @c boost::contract::old_value_copy, in which case the related old value
    pointer will not be null (but no copy is made if postconditions and
    exception  guarantees are not being checked, see
    @RefMacro{BOOST_CONTRACT_NO_OLDS}).

    @param old Old value to be copied.

    @tparam T Old value type.
    */
    template<typename T>
    /* implicit */ old_value(
        T const&
        #if !defined(BOOST_CONTRACT_NO_OLDS) || \
                defined(BOOST_CONTRACT_DETAIL_DOXYGEN)
            old
        #endif // Else, no name (avoid unused param warning).
    ,
        typename boost::enable_if<boost::contract::is_old_value_copyable<T>
                >::type* = 0
    )
        #ifndef BOOST_CONTRACT_NO_OLDS
            : untyped_copy_(new old_value_copy<T>(old))
        #endif // Else, leave ptr_ null (thus no copy of T).
    {}
    
    /**
    Construct this object from the specified old value when the old value type
    is not copyable.

    The specified old value @c old cannot be copied in this case so it is not
    copied and the related old value pointer will always be null (thus calls to
    this constructor have no effect and they will likely be optimized away by
    most compilers).
    
    @param old Old value (that will not be copied in this case).
    
    @tparam T Old value type.
    */
    template<typename T>
    /* implicit */ old_value(
        T const&
        #ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
            old
        #endif // Else, no name (avoid unused param warning).
    ,
        typename boost::disable_if<boost::contract::is_old_value_copyable<T>
                >::type* = 0
    ) {} // Leave ptr_ null (thus no copy of T).

/** @cond */
private:
    explicit old_value() {}
    
    #ifndef BOOST_CONTRACT_NO_OLDS
        boost::shared_ptr<void> untyped_copy_; // Type erasure.
    #endif

    friend class old_pointer;
    friend BOOST_CONTRACT_DETAIL_DECLSPEC old_value null_old();
/** @endcond */
};

/**
Convert old value copies into old value pointers.

This class is usually only implicitly used by this library and it does not
explicitly appear in user code (that is why this class does not have public
constructors, etc.).
*/
class old_pointer { // Copyable (as *).
public:
    /**
    Convert this object to an actual old value pointer for which the old value
    type @c T might or not be copyable.

    For example, this is implicitly called when assigning or initializing old
    value pointers of type @c boost::contract::old_ptr_if_copyable.
    
    @tparam T   Type of the pointed old value.
                The old value pointer will always be null if this type is not
                copyable (see
                @c boost::contract::is_old_value_copyable), but this library
                will not generate a compile-time error.
    */
    template<typename T>
    /* implicit */ operator old_ptr_if_copyable<T>() {
        return get<old_ptr_if_copyable<T> >();
    }
    
    /**
    Convert this object to an actual old value pointer for which the old value
    type @c T must be copyable.

    For example, this is implicitly called when assigning or initializing old
    value pointers of type @c boost::contract::old_ptr.
    
    @tparam T   Type of the pointed old value. This type must be copyable
                (see @c boost::contract::is_old_value_copyable),
                otherwise this library will generate a compile-time error when
                the old value pointer is dereferenced.
    */
    template<typename T>
    /* implicit */ operator old_ptr<T>() {
        return get<old_ptr<T> >();
    }

/** @cond */
private:
    #ifndef BOOST_CONTRACT_NO_OLDS
        explicit old_pointer(virtual_* v, old_value const& old)
            : v_(v), untyped_copy_(old.untyped_copy_) {}
    #else
        explicit old_pointer(virtual_* /* v */, old_value const& /* old */) {}
    #endif
    
    template<typename Ptr>
    Ptr get() {
        #ifndef BOOST_CONTRACT_NO_OLDS
            if(!boost::contract::is_old_value_copyable<typename
                    Ptr::element_type>::value) {
                BOOST_CONTRACT_DETAIL_DEBUG(!untyped_copy_);
                return Ptr(); // Non-copyable so no old value and return null.
        #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
            } else if(!v_ && boost::contract::detail::checking::already()) {
                return Ptr(); // Not checking (so return null).
        #endif
            } else if(!v_) {
                BOOST_CONTRACT_DETAIL_DEBUG(untyped_copy_);
                typedef old_value_copy<typename Ptr::element_type> copied_type;
                boost::shared_ptr<copied_type> typed_copy = // Un-erase type.
                        boost::static_pointer_cast<copied_type>(untyped_copy_);
                BOOST_CONTRACT_DETAIL_DEBUG(typed_copy);
                return Ptr(typed_copy);
            } else if(
                v_->action_ == boost::contract::virtual_::push_old_init_copy ||
                v_->action_ == boost::contract::virtual_::push_old_ftor_copy
            ) {
                BOOST_CONTRACT_DETAIL_DEBUG(untyped_copy_);
                std::queue<boost::shared_ptr<void> >& copies = v_->action_ ==
                        boost::contract::virtual_::push_old_ftor_copy ?
                    v_->old_ftor_copies_
                :
                    v_->old_init_copies_
                ;
                copies.push(untyped_copy_);
                return Ptr(); // Pushed (so return null).
            } else if(
                boost::contract::virtual_::pop_old_init_copy(v_->action_) ||
                v_->action_ == boost::contract::virtual_::pop_old_ftor_copy
            ) {
                // Copy not null, but still pop it from the queue.
                BOOST_CONTRACT_DETAIL_DEBUG(!untyped_copy_);

                std::queue<boost::shared_ptr<void> >& copies = v_->action_ ==
                        boost::contract::virtual_::pop_old_ftor_copy ?
                    v_->old_ftor_copies_
                :
                    v_->old_init_copies_
                ;
                boost::shared_ptr<void> untyped_copy = copies.front();
                BOOST_CONTRACT_DETAIL_DEBUG(untyped_copy);
                copies.pop();

                typedef old_value_copy<typename Ptr::element_type> copied_type;
                boost::shared_ptr<copied_type> typed_copy = // Un-erase type.
                        boost::static_pointer_cast<copied_type>(untyped_copy);
                BOOST_CONTRACT_DETAIL_DEBUG(typed_copy);
                return Ptr(typed_copy);
            }
            BOOST_CONTRACT_DETAIL_DEBUG(!untyped_copy_);
        #endif
        return Ptr();
    }

    #ifndef BOOST_CONTRACT_NO_OLDS
        virtual_* v_;
        boost::shared_ptr<void> untyped_copy_; // Type erasure.
    #endif
    
    friend BOOST_CONTRACT_DETAIL_DECLSPEC
    old_pointer make_old(old_value const&);

    friend BOOST_CONTRACT_DETAIL_DECLSPEC
    old_pointer make_old(virtual_*, old_value const&);
/** @endcond */
};

/**
Return a "null" old value.

The related old value pointer will also be null.
This function is usually only called by the code expanded by
@RefMacro{BOOST_CONTRACT_OLDOF}.

@see @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}

@return Null old value.
*/
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
old_value null_old();

/**
Make an old value pointer (but not for virtual public functions and public
functions overrides).

The related old value pointer will not be null if the specified old value was
actually copied.
This function is usually only called by code expanded by
@c BOOST_CONTRACT_OLDOF(old_expr) as in:

@code
boost::contract::make_old(boost::contract::copy_old() ? old_expr :
        boost::contract::null_old())
@endcode

@see @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}

@param old  Old value which is usually implicitly constructed from the user old
            value expression to be copied (use the ternary operator <c>?:</c>
            to completely avoid to evaluate the old value expression when
            @c boost::contract::copy_old() is @c false).

@return Old value pointer (usually implicitly converted to either
        @RefClass{boost::contract::old_ptr} or
        @RefClass{boost::contract::old_ptr_if_copyable} in user code).
*/
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
old_pointer make_old(old_value const& old);

/**
Make an old value pointer (for virtual public functions and public functions
overrides).

The related old value pointer will not be null if the specified old value was
actually copied.
This function is usually only called by code expanded by
@c BOOST_CONTRACT_OLDOF(v, old_expr) as in:

@code
boost::contract::make_old(v, boost::contract::copy_old(v) ? old_expr :
        boost::contract::null_old())
@endcode

@see @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}

@param v    The trailing parameter of type
            @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
            from the enclosing virtual or overriding public function declaring
            the contract.
@param old  Old value which is usually implicitly constructed from the user old
            value expression to be copied (use the ternary operator <c>?:</c>
            to completely avoid to evaluate the old value expression when
            @c boost::contract::copy_old(v) is @c false).

@return Old value pointer (usually implicitly converted to either
        @RefClass{boost::contract::old_ptr} or
        @RefClass{boost::contract::old_ptr_if_copyable} in user code).
*/
/** @cond */ BOOST_CONTRACT_DETAIL_DECLSPEC /** @endcond */
old_pointer make_old(virtual_* v, old_value const& old);

/**
Query if old values need to be copied (but not for virtual public functions and
public function overrides).

For example, this function always returns false when both postconditions and
exception guarantees are not being checked (see
@RefMacro{BOOST_CONTRACT_NO_OLDS}).
This function is usually only called by the code expanded by
@RefMacro{BOOST_CONTRACT_OLDOF}.

@see @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}

@return True if old values need to be copied, false otherwise.
*/
inline bool copy_old() {
    #ifndef BOOST_CONTRACT_NO_OLDS
        #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
            return !boost::contract::detail::checking::already();
        #else
            return true;
        #endif
    #else
        return false; // No post checking, so never copy old values.
    #endif
}

/**
Query if old values need to be copied (for virtual public functions and public
function overrides).

For example, this function always returns false when both postconditions and
exception guarantees are not being checked (see
@RefMacro{BOOST_CONTRACT_NO_OLDS}).
In addition, this function returns false when overridden functions are being
called subsequent times by this library to support subcontracting.
This function is usually only called by the code expanded by
@RefMacro{BOOST_CONTRACT_OLDOF}.

@see @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}

@param v    The trailing parameter of type
            @RefClass{boost::contract::virtual_}<c>*</c> and default value @c 0
            from the enclosing virtual or overriding public function declaring
            the contract.

@return True if old values need to be copied, false otherwise.
*/
#ifndef BOOST_CONTRACT_NO_OLDS
    inline bool copy_old(virtual_* v) {
        if(!v) {
            #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                return !boost::contract::detail::checking::already();
            #else
                return true;
            #endif
        }
        return v->action_ == boost::contract::virtual_::push_old_init_copy ||
                v->action_ == boost::contract::virtual_::push_old_ftor_copy;
    }
#else
    inline bool copy_old(virtual_*
        #ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
            v
        #endif
    ) {
        return false; // No post checking, so never copy old values.
    }
#endif

} } // namespace

#ifdef BOOST_CONTRACT_HEADER_ONLY
    #include <boost/contract/detail/inlined/old.hpp>
#endif

#endif // #include guard


/* old.hpp
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
*/