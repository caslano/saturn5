//  Copyright (c) 2000-2011 Joerg Walter, Mathias Koch, David Bellot
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef _BOOST_UBLAS_EXCEPTION_
#define _BOOST_UBLAS_EXCEPTION_

#if ! defined (BOOST_NO_EXCEPTIONS) && ! defined (BOOST_UBLAS_NO_EXCEPTIONS)
#include <stdexcept>
#else
#include <cstdlib>
#endif
#ifndef BOOST_UBLAS_NO_STD_CERR
#include <iostream>
#endif

#include <boost/numeric/ublas/detail/config.hpp>

namespace boost { namespace numeric { namespace ublas {

    /** \brief Exception raised when a division by zero occurs
     */
    struct divide_by_zero
#if ! defined (BOOST_NO_EXCEPTIONS) && ! defined (BOOST_UBLAS_NO_EXCEPTIONS)
        // Inherit from standard exceptions as requested during review.
        : public std::runtime_error 
    {
        explicit divide_by_zero (const char *s = "divide by zero") :
            std::runtime_error (s) {}
        void raise () {
            throw *this;
        }
#else
    {
        divide_by_zero ()
            {}
        explicit divide_by_zero (const char *)
            {}
        void raise () {
            std::abort ();
        }
#endif
    };

    /** \brief Expception raised when some interal errors occurs like computations errors, zeros values where you should not have zeros, etc...
     */
    struct internal_logic
#if ! defined (BOOST_NO_EXCEPTIONS) && ! defined (BOOST_UBLAS_NO_EXCEPTIONS)
        // Inherit from standard exceptions as requested during review.
        : public std::logic_error {
        explicit internal_logic (const char *s = "internal logic") :
            std::logic_error (s) {}
        void raise () {
            throw *this;
        }
#else
    {
        internal_logic ()
            {}
        explicit internal_logic (const char *)
            {}
        void raise () {
            std::abort ();
        }
#endif
    };

    struct external_logic
#if ! defined (BOOST_NO_EXCEPTIONS) && ! defined (BOOST_UBLAS_NO_EXCEPTIONS)
        // Inherit from standard exceptions as requested during review.
        : public std::logic_error {
        explicit external_logic (const char *s = "external logic") :
            std::logic_error (s) {}
        // virtual const char *what () const throw () {
        //     return "exception: external logic";
        // }
        void raise () {
            throw *this;
        }
#else
    {
        external_logic ()
            {}
        explicit external_logic (const char *)
            {}
        void raise () {
            std::abort ();
        }
#endif
    };

    struct bad_argument
#if ! defined (BOOST_NO_EXCEPTIONS) && ! defined (BOOST_UBLAS_NO_EXCEPTIONS)
        // Inherit from standard exceptions as requested during review.
        : public std::invalid_argument {
        explicit bad_argument (const char *s = "bad argument") :
            std::invalid_argument (s) {}
        void raise () {
            throw *this;
        }
#else
    {
        bad_argument ()
            {}
        explicit bad_argument (const char *)
            {}
        void raise () {
            std::abort ();
        }
#endif
    };

    /**
     */
    struct bad_size
#if ! defined (BOOST_NO_EXCEPTIONS) && ! defined (BOOST_UBLAS_NO_EXCEPTIONS)
        // Inherit from standard exceptions as requested during review.
        : public std::domain_error {
        explicit bad_size (const char *s = "bad size") :
            std::domain_error (s) {}
        void raise () {
            throw *this;
        }
#else
    {
        bad_size ()
            {}
        explicit bad_size (const char *)
            {}
        void raise () {
            std::abort ();
        }
#endif
    };

    struct bad_index
#if ! defined (BOOST_NO_EXCEPTIONS) && ! defined (BOOST_UBLAS_NO_EXCEPTIONS)
        // Inherit from standard exceptions as requested during review.
        : public std::out_of_range {
        explicit bad_index (const char *s = "bad index") :
            std::out_of_range (s) {}
        void raise () {
            throw *this;
        }
#else
    {
        bad_index ()
            {}
        explicit bad_index (const char *)
            {}
        void raise () {
            std::abort ();
        }
#endif
    };

    struct singular
#if ! defined (BOOST_NO_EXCEPTIONS) && ! defined (BOOST_UBLAS_NO_EXCEPTIONS)
        // Inherit from standard exceptions as requested during review.
        : public std::runtime_error {
        explicit singular (const char *s = "singular") :
            std::runtime_error (s) {}
        void raise () {
            throw *this;
        }
#else
    {
        singular ()
            {}
        explicit singular (const char *)
            {}
        void raise () {
            std::abort ();
        }
#endif
    };

    struct non_real
#if ! defined (BOOST_NO_EXCEPTIONS) && ! defined (BOOST_UBLAS_NO_EXCEPTIONS)
        // Inherit from standard exceptions as requested during review.
        : public std::domain_error {
        explicit non_real (const char *s = "exception: non real") :
            std::domain_error (s) {}
        void raise () {
            throw *this;
        }
#else
     {
        non_real ()
            {}
        explicit non_real (const char *)
            {}
        void raise () {
            std::abort ();
        }
#endif
    };

#if BOOST_UBLAS_CHECK_ENABLE
// Macros are equivilent to 
//    template<class E>
//    BOOST_UBLAS_INLINE
//    void check (bool expression, const E &e) {
//        if (! expression)
//            e.raise ();
//    }
//    template<class E>
//    BOOST_UBLAS_INLINE
//    void check_ex (bool expression, const char *file, int line, const E &e) {
//        if (! expression)
//            e.raise ();
//    }
#ifndef BOOST_UBLAS_NO_STD_CERR
#define BOOST_UBLAS_CHECK_FALSE(e) \
    std::cerr << "Check failed in file " << __FILE__ << " at line " << __LINE__ << ":" << std::endl; \
    e.raise ();
#define BOOST_UBLAS_CHECK(expression, e) \
    if (! (expression)) { \
        std::cerr << "Check failed in file " << __FILE__ << " at line " << __LINE__ << ":" << std::endl; \
        std::cerr << #expression << std::endl; \
        e.raise (); \
    }
#define BOOST_UBLAS_CHECK_EX(expression, file, line, e) \
    if (! (expression)) { \
        std::cerr << "Check failed in file " << (file) << " at line " << (line) << ":" << std::endl; \
        std::cerr << #expression << std::endl; \
        e.raise (); \
    }
#else
#define BOOST_UBLAS_CHECK_FALSE(e) \
    e.raise ();
#define BOOST_UBLAS_CHECK(expression, e) \
    if (! (expression)) { \
        e.raise (); \
    }
#define BOOST_UBLAS_CHECK_EX(expression, file, line, e) \
    if (! (expression)) { \
        e.raise (); \
    }
#endif
#else
// Macros are equivilent to 
//    template<class E>
//    BOOST_UBLAS_INLINE
//    void check (bool expression, const E &e) {}
//    template<class E>
//    BOOST_UBLAS_INLINE
//    void check_ex (bool expression, const char *file, int line, const E &e) {}
#define BOOST_UBLAS_CHECK_FALSE(e)
#define BOOST_UBLAS_CHECK(expression, e)
#define BOOST_UBLAS_CHECK_EX(expression, file, line, e)
#endif


#ifndef BOOST_UBLAS_USE_FAST_SAME
// Macro is equivilent to 
//    template<class T>
//    BOOST_UBLAS_INLINE
//    const T &same_impl (const T &size1, const T &size2) {
//        BOOST_UBLAS_CHECK (size1 == size2, bad_argument ());
//        return (std::min) (size1, size2);
//    }
// #define BOOST_UBLAS_SAME(size1, size2) same_impl ((size1), (size2))
     // need two types here because different containers can have
     // different size_types (especially sparse types)
    template<class T1, class T2>
    BOOST_UBLAS_INLINE
    // Kresimir Fresl and Dan Muller reported problems with COMO.
    // We better change the signature instead of libcomo ;-)
    // const T &same_impl_ex (const T &size1, const T &size2, const char *file, int line) {
    T1 same_impl_ex (const T1 &size1, const T2 &size2, const char *file, int line) {
        BOOST_UBLAS_CHECK_EX (size1 == size2, file, line, bad_argument ());
        return (size1 < size2)?(size1):(size2);
    }
    template<class T>
    BOOST_UBLAS_INLINE
    T same_impl_ex (const T &size1, const T &size2, const char *file, int line) {
        BOOST_UBLAS_CHECK_EX (size1 == size2, file, line, bad_argument ());
        return (std::min) (size1, size2);
    }
#define BOOST_UBLAS_SAME(size1, size2) same_impl_ex ((size1), (size2), __FILE__, __LINE__)
#else
// Macros are equivilent to 
//    template<class T>
//    BOOST_UBLAS_INLINE
//    const T &same_impl (const T &size1, const T &size2) {
//        return size1;
//    }
// #define BOOST_UBLAS_SAME(size1, size2) same_impl ((size1), (size2))
#define BOOST_UBLAS_SAME(size1, size2) (size1)
#endif

}}}

#endif

/* exception.hpp
kpxA/+ySYYHeuGOr01lP7NO1ulCxpYBuYAN9myqFXBFo1ekiywrnZKm5JFzRLdiK+9DP6X7WGirJCd2YAs6brhCydvLETCTw7KEBqLrVfzGuKk2msaYT2B8uQXEJY6lgfyYeWIsAzfclCGT9WopR0f105IYT68Agqu1FaJ0HvgSYfwbjgXT8muRQvRhlBVx6SR+tliU1wptdMi2QLkwoW20ldIn1uZlyCL8/QsnkJF6D0FDJNG9mWNzHxdsotFKuMKGSOd5QHZ0MxMaNRuSP5XIVTyPn7+cV0+r1QU3UJtfBiTLJYk7SVx/JHCqyjmbNQXrGC77suhzinMk5Uol8+EH1+yj0Re/aNVFd67Vavygd/wTVl6rXRYuNXsNEo4aWMTIM8BPOGYVgRxJziePPZpPWueJQXTKSRi0sCU25U6lQlG0z0cBkYG+gAHQkzn897lIBDNBdHhiIZjB7lo01DlB6zsaIRUsmMUhUfIxFyyu6oQYtmRPJrJwsi5MlkrB4CgLjtBoC98JDUbRtUbWZ4fBVk31i3J1SXlCye53jw9D2UizYJDTQa4K8MEBZsTj1oJnT1abvVA78v/Un+ehzgq1OPzQcnON3qOPoa2LDIbQ2vB/eQtcUY+MQj23g/atBnA0o6oQkH99f8TG3W3gB4NtF25KY+EudG5ffnWa18+3Lssj7sNj18PY6Hd+BTNYWXr3CxupVZ+A5/Z7c3kviMBtdwGHuG2ByPtFyJpCcvk8u6S8jip2IeD8JEf2BAqm5GaSsFRDqqCKWqhtWgciXNtcCBtqO0IvXAC2MZNgYl3lTgrGcBKN4891kIuRnlI78jGLkZ7uOGjXB4UUOC6V6SVsiHjW1mVaOYMlUE+3aDZskJ0wuf7A+9MGSkM6LhPS19hB33kAEFLq8xpQU8esh5xknbnpMwzxKfKjOGmkgtQ3IxT/ZuxbwKKorvLOzJJsHzIIRo0SNEjAQwEjQBhY0D0giIiws2UWBJCriuCJi2OUhGBI2wE7GqK3aUttqW1uLbW2tbSGiRUKUAFaLWhWLbbWt7aSp9c1Dhe1/zp2Z3QRQfLS1j823mztzH3Pn3HPPPffc88i1excuwE/kHK2iEPCgSANDiU0xIUFZA2224ZIOSjrtZNFW/N9/udPzhStwBoLvs1f862R5n8V+zj5vzRrb4KrPCcbPIzN+oxJH09L5GOphDS6uedT4PsewN2EbjCqXd9di6oLkKdjFGsPHtK+KwgosPFCHnwM399XNZePO+GRX722QHQ/FM7beVZ/FljbpZgVp9LB6l1AD7f1+hFsDsSgPUTaOqyrzdtbn6LvkFwo6tYEacig65jJXrdnMh7tR4HjN2HSucOlF0bizvkjZODD6OrpeIUW3O9v/4M7Y7X2v/lSSaOlPyW8VvKetcGlF0Jl2az7XcWzdzXhYLmf9UA4Tm6ls9KBVrb+eAmdtUsY2cySjKc5ohevwR2q9mvGDXHL9uXoqA44b9GgD9VR2uPGKO2OX1o8uSpwZ7VqKaD1Vjla6DkGqQiKYXx5H+676Mrt9d/sr2aJJn4RHZTxtPsyZ/DA56WEuPOyD43hY7/Ef0XSYMR1EtdtDwNKdFqJfT6cZmdJovjoKXvSUR4CPEK7/e6Jgx7HWD5cXiMfYTaX1tI8oj8JjS11c3mdaXP/5/l52I73HfzGvFL1xoKYHEnR8yHijPqD5McYc8P+w8RXtfdIx7t14L3oB+PgEfATtWvquzjEZjkm27E9ve3S2P+O4MOqGFznedbhVYgGzut66yQJlo/hW8t2upbAcGiEJ9PZj4Ic7Xih+jZO/KPWWonB8qrHEfzeAlUjEgXRFelz6wvLRAz3Se0JGCZQ=
*/