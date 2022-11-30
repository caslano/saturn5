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
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
*/