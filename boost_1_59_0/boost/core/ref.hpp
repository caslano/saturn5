#ifndef BOOST_CORE_REF_HPP
#define BOOST_CORE_REF_HPP

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/enable_if.hpp>

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

namespace detail
{

template< class Y, class T > struct ref_convertible
{
    typedef char (&yes) [1];
    typedef char (&no)  [2];

    static yes f( T* );
    static no  f( ... );

    enum _vt { value = sizeof( (f)( static_cast<Y*>(0) ) ) == sizeof(yes) };
};

struct ref_empty
{
};

} // namespace detail

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

    template<class Y> friend class reference_wrapper;

    /**
     Constructs a `reference_wrapper` object that stores the
     reference stored in the compatible `reference_wrapper` `r`.

     @remark Only enabled when `Y*` is convertible to `T*`.
     @remark Does not throw.
    */
    template<class Y> reference_wrapper( reference_wrapper<Y> r,
        typename enable_if_c<boost::detail::ref_convertible<Y, T>::value,
            boost::detail::ref_empty>::type = boost::detail::ref_empty() ): t_( r.t_ )
    {
    }

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
#if defined( BOOST_BORLANDC ) && BOOST_WORKAROUND( BOOST_BORLANDC, BOOST_TESTED_AT(0x581) )
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