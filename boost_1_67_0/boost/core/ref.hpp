#ifndef BOOST_CORE_REF_HPP
#define BOOST_CORE_REF_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <boost/core/addressof.hpp>

//
//  ref.hpp - ref/cref, useful helper functions
//
//  Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//  Copyright (C) 2001, 2002 Peter Dimov
//  Copyright (C) 2002 David Abrahams
//
//  Copyright (C) 2014 Glen Joseph Fernandes
//  (glenjofe@gmail.com)
//
//  Copyright (C) 2014 Agustin Berge
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/core/doc/html/core/ref.html for documentation.
//

/**
 @file
*/

/**
 Boost namespace.
*/
namespace boost
{

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, == 1600 )

    struct ref_workaround_tag {};

#endif

// reference_wrapper

/**
 @brief Contains a reference to an object of type `T`.

 `reference_wrapper` is primarily used to "feed" references to
 function templates (algorithms) that take their parameter by
 value. It provides an implicit conversion to `T&`, which
 usually allows the function templates to work on references
 unmodified.
*/
template<class T> class reference_wrapper
{
public:
    /**
     Type `T`.
    */
    typedef T type;

    /**
     Constructs a `reference_wrapper` object that stores a
     reference to `t`.

     @remark Does not throw.
    */
    BOOST_FORCEINLINE explicit reference_wrapper(T& t): t_(boost::addressof(t)) {}

#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, == 1600 )

    BOOST_FORCEINLINE explicit reference_wrapper( T & t, ref_workaround_tag ): t_( boost::addressof( t ) ) {}

#endif

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
    /**
     @remark Construction from a temporary object is disabled.
    */
    BOOST_DELETED_FUNCTION(reference_wrapper(T&& t))
public:
#endif

    /**
     @return The stored reference.
     @remark Does not throw.
    */
    BOOST_FORCEINLINE operator T& () const { return *t_; }

    /**
     @return The stored reference.
     @remark Does not throw.
    */
    BOOST_FORCEINLINE T& get() const { return *t_; }

    /**
     @return A pointer to the object referenced by the stored
       reference.
     @remark Does not throw.
    */
    BOOST_FORCEINLINE T* get_pointer() const { return t_; }

private:

    T* t_;
};

// ref

/**
 @cond
*/
#if defined( __BORLANDC__ ) && BOOST_WORKAROUND( __BORLANDC__, BOOST_TESTED_AT(0x581) )
#  define BOOST_REF_CONST
#else
#  define BOOST_REF_CONST const
#endif
/**
 @endcond
*/

/**
 @return `reference_wrapper<T>(t)`
 @remark Does not throw.
*/
template<class T> BOOST_FORCEINLINE reference_wrapper<T> BOOST_REF_CONST ref( T & t )
{
#if defined( BOOST_MSVC ) && BOOST_WORKAROUND( BOOST_MSVC, == 1600 )

    return reference_wrapper<T>( t, ref_workaround_tag() );

#else

    return reference_wrapper<T>( t );

#endif
}

// cref

/**
 @return `reference_wrapper<T const>(t)`
 @remark Does not throw.
*/
template<class T> BOOST_FORCEINLINE reference_wrapper<T const> BOOST_REF_CONST cref( T const & t )
{
    return reference_wrapper<T const>(t);
}

#undef BOOST_REF_CONST

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

/**
 @cond
*/
#if defined(BOOST_NO_CXX11_DELETED_FUNCTIONS)
#  define BOOST_REF_DELETE
#else
#  define BOOST_REF_DELETE = delete
#endif
/**
 @endcond
*/

/**
 @remark Construction from a temporary object is disabled.
*/
template<class T> void ref(T const&&) BOOST_REF_DELETE;

/**
 @remark Construction from a temporary object is disabled.
*/
template<class T> void cref(T const&&) BOOST_REF_DELETE;

#undef BOOST_REF_DELETE

#endif

// is_reference_wrapper

/**
 @brief Determine if a type `T` is an instantiation of
 `reference_wrapper`.

 The value static constant will be true if the type `T` is a
 specialization of `reference_wrapper`.
*/
template<typename T> struct is_reference_wrapper
{
    BOOST_STATIC_CONSTANT( bool, value = false );
};

/**
 @cond
*/
template<typename T> struct is_reference_wrapper< reference_wrapper<T> >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

#if !defined(BOOST_NO_CV_SPECIALIZATIONS)

template<typename T> struct is_reference_wrapper< reference_wrapper<T> const >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

template<typename T> struct is_reference_wrapper< reference_wrapper<T> volatile >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

template<typename T> struct is_reference_wrapper< reference_wrapper<T> const volatile >
{
    BOOST_STATIC_CONSTANT( bool, value = true );
};

#endif // !defined(BOOST_NO_CV_SPECIALIZATIONS)

/**
 @endcond
*/


// unwrap_reference

/**
 @brief Find the type in a `reference_wrapper`.

 The `typedef` type is `T::type` if `T` is a
 `reference_wrapper`, `T` otherwise.
*/
template<typename T> struct unwrap_reference
{
    typedef T type;
};

/**
 @cond
*/
template<typename T> struct unwrap_reference< reference_wrapper<T> >
{
    typedef T type;
};

#if !defined(BOOST_NO_CV_SPECIALIZATIONS)

template<typename T> struct unwrap_reference< reference_wrapper<T> const >
{
    typedef T type;
};

template<typename T> struct unwrap_reference< reference_wrapper<T> volatile >
{
    typedef T type;
};

template<typename T> struct unwrap_reference< reference_wrapper<T> const volatile >
{
    typedef T type;
};

#endif // !defined(BOOST_NO_CV_SPECIALIZATIONS)

/**
 @endcond
*/

// unwrap_ref

/**
 @return `unwrap_reference<T>::type&(t)`
 @remark Does not throw.
*/
template<class T> BOOST_FORCEINLINE typename unwrap_reference<T>::type& unwrap_ref( T & t )
{
    return t;
}

// get_pointer

/**
 @cond
*/
template<class T> BOOST_FORCEINLINE T* get_pointer( reference_wrapper<T> const & r )
{
    return r.get_pointer();
}
/**
 @endcond
*/

} // namespace boost

#endif // #ifndef BOOST_CORE_REF_HPP

/* ref.hpp
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
*/