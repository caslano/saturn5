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