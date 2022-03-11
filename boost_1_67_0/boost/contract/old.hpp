
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