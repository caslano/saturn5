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
/YR20GWAe29kLqB5Xp2e0ohIuOZ1K30fPye2/UEL3broF98jZz1uOdQ32LUCXiId03RA3QMaqk5tRL16aOt//Bp+H60+67z5ulJov/XY2FDW6oBWklum82Pqr0EapWPlj6+34+w6wuk7bUi2Z4e39vfEkxpjW+tFGvct9IxI4+6nbgxkUc6xxU/0ce8NuE2EO2v+igb0dooog91bmLs+ujDzNkkgi3IudEsl5XUBTbgLZsvrkeh03Q3NVonGu2OwTaRhrxj00J9CR2600sM++IX3UZ8j0el+b3gNSzRs31CmTGcHG1OmLJv6ftkyd6XSUO8DfTxfouOPAcTMkcv0PhpYlxfOQU8SmHE1F9BRtwD5RgI8Eu0oH9IFdlQMaQI7Gg9pRDsqSXRoR+n8RDuaCOkCOyqHNJIdyXRoR+myBXZUCWlEOzo9pBPtSC4z3Y6ikB7tyKwRbKRvXlXhanIGcm06lNOFzb1mvsFR/LfkH/5JXIueJrl1nsH+7aVZMy6eodJHJiO6CkW3pyu1Qi6qFvOlsVI+/liaNcu9Jn/8BgCx0GupL6P02aP1e71TvP74ck47XKU1uv44G38NhXWre0V/7TX8XdiV66b3Zzd3dT/bjW9xfoDbb0tSp9cRDY0C8QljVSn87iw/wtzr1lu4s2T8BbWuBPEPgjLc7+wbQ5wGE72HkvC4IKSJiuCjXajxmUqpEANmT4a0Yd91bXHeH+SnVBiO1ydZvTln3vbWoGw76ce3agsVyF+qw7s3iMlv5mxfQTTT5fJedXoF0k9N0nVxQjqpqsH5iFpFoF+5EdWvAp/0wKXOvA3WMvaw3+2vCV6YYFUCeTw26y6I8eoSr82YOpzDNP5Zn1dSOi1T5WKsoA5xWj2fBxhPs+N9trdTG11xtL4rV21wryrRR1XUxxNEffyHZTZDKdj5Ax6mrQBiV6yx657w+LzB/7yA18cUEyE2xR8R52+kWZ9FzIsPcuBCxFQ7wfoHYmbCYfG/Il/4Zimdv5vqcxvr/PQGxy/W+Ui4hrloqbTHfAnrjPVs1qlZ3FlpX+D9nMfMacr2XYjLGfP3iK/g9NgWG+xP6h7P7pI6BS19X5aI9vPBNfquF7sSDc/VdVn66kw4V1+6tNm1CeZHp9ol2ZeLst99KMteqapvXsPvFXFZFVn2FfsreySfxV0l2tGOY9QclvyPSI8XH6V2mE9pm9S3nb/HH6e0J1PafE5b1YgsZEZhnU4Q9fcJ4p/EU6O1/9lSHc9WGSw4W/VZyhd/L1Rh9tm0CvpLn0MaMnpDRx/sEdXfoRz1KihuuPl7apXRF0v7cSgjSgFvDKIMHIFWfvM5nY6/jCJPL6rtvnkyHfNcLPOM9k7l4VsdYOZbLedXmxXk40EbJ20LPD16ZsljWsiTbjaMlcYJBx4hzlyIRuLBr4fmR6qlFpePRvg5OYLZBjCOsMwnaBuBrrCXtsdLNKZg26TTJXWYkyd3vX3yZLqGeFJoI/BlRd0wSaweKDeVV0PtUSuo7gf8UmmM3a2S+EmvATrv7++DlrnLsk5VuAsRT7QLkcbwakvjxeacygfNmesg8RGqob9Bhu++6X3baDs0ZWzVl/9T+vyZtKiL/dvHTP/W52hoTHgpfVeWEe1sg37SRGFs9x76FX5bni9+376o/Bfa5cax/MuclsvO0vJ13jmHeL3FqsoeQx+UCgcfFHxJwD1fEjHBl5yHOKy5gA8LOCmzwTvwRK1+Uu76FEFfuj2+SXX/yDH6nOKZDc4VVBm0s9dJG/dCm+xxymj3dZlkxDgtqE+k8eZRB3k46rUd9Io0km5voDobmPosfnvu8uRk3ct5B/Rzp0qPN1L6HcdQrYnmLPY=
*/