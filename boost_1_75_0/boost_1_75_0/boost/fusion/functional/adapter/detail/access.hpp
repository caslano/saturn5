/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED

namespace boost { namespace fusion { namespace detail
{
    // const reference deduction for function templates that accept T const &
    template <typename T> struct cref               { typedef T const& type; };
    template <typename T> struct cref<T&>           { typedef T const& type; };
    template <typename T> struct cref<T const>      { typedef T const& type; };

    // mutable reference deduction for function templates that accept T &
    template <typename T> struct mref               { typedef T      & type; };
    template <typename T> struct mref<T&>           { typedef T      & type; };

    // generic reference deduction for function templates that are overloaded
    // to accept both T const & and T &
    template <typename T> struct gref               { typedef T const& type; };
    template <typename T> struct gref<T&>           { typedef T      & type; };
    template <typename T> struct gref<T const>      { typedef T const& type; };

    // appropriately qualified target function in const context
    template <typename T> struct qf_c          { typedef T const  type; };
    template <typename T> struct qf_c<T const> { typedef T const  type; };
    template <typename T> struct qf_c<T &>     { typedef T        type; };

    // appropriately qualified target function in non-const context
    template <typename T> struct qf            { typedef T        type; };
    template <typename T> struct qf<T const>   { typedef T const  type; };
    template <typename T> struct qf<T &>       { typedef T        type; };
}}}

#endif


/* access.hpp
T/R8QdPixfPkbN8iHLprU5qtHCECp8MgV3rPnBAD6FnCIV+o5B73n869LHHF0ta0f8z0Ro8gTMtMtInwtkqhuAlZ1Z2gYldh0X0vJssxRhfLicKN1ht26iT7xaT7z4JuKDO6oYy7QW2HZ9mpq5YZaZbJNNIOaBynWWykWSy7E8+OBpqhT5yFw6wWwyqDzJNxiGnH0E4kXw9TEyoPz3M74ZzaAsalFxHtlLbGGMWJK+5E+5a9oEh8ex0dVlbbKPdQRtB0BrwDkU1Y1QEx+9A/WeSdsJ3KiF/QmlLM4RRYAbDdRPfylePRVGlLiudLCJ36ynoqfAajtGgWyU9d6DDVR5mnaF0gZjcUuZmK7vhNa7zGhfFUgbJSWTtllHm+nMpsJMqsKmLdVEA3YVf691XBWvr0YBh9hQ2v4IbP/ycNX869/gycqceLvTi4gYi1zpHm2SHoG8vbaWxCHwgjeyjYBJtTzOEUY7hK6bq7CtZvK9fv8dZavSJlvdZRkOKdRtUac9WahtF3wXoXQ16nsvG38enLPJyHrVpllumV2caVeVKvjJ0rg4F3Mba1zPAh7vAF1tB1QRgA1lgYX7YQVaHzvNushg4KZnH/loF+MTr2jMngXRBiw5YONZn9XHROXkCvyNYN+FTxWZseunf3BX52VxE+17oLyCpqjbK8kiog7bSQjPdhcepzCBUw5UEVMBO70cIznq/RsBB552wg
*/