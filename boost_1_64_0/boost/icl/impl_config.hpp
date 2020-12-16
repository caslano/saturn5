/*-----------------------------------------------------------------------------+
Author: Joachim Faulhaber
Copyright (c) 2009-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef  BOOST_ICL_IMPL_CONFIG_HPP_JOFA_091225
#define  BOOST_ICL_IMPL_CONFIG_HPP_JOFA_091225

#include <boost/icl/detail/boost_config.hpp>

/*-----------------------------------------------------------------------------+
| You can choose an implementation for the basic set and map classes.          |
| Select at most ONE of the following defines to change the default            |
+-----------------------------------------------------------------------------*/

//#define ICL_USE_STD_IMPLEMENTATION                // Default
//#define ICL_USE_BOOST_MOVE_IMPLEMENTATION         // Boost.Container
//        ICL_USE_BOOST_INTERPROCESS_IMPLEMENTATION // No longer available

/*-----------------------------------------------------------------------------+
| NO define or ICL_USE_STD_IMPLEMENTATION: Choose std::set and std::map from   |
|     your local std implementation as implementing containers (DEFAULT).      |
|     Whether move semantics is available depends on the version of your local |
|     STL.                                                                     |
|                                                                              |
| ICL_USE_BOOST_MOVE_IMPLEMENTATION:                                           |
|     Use move aware containers from boost::container.                         |
|                                                                              |
| NOTE: ICL_USE_BOOST_INTERPROCESS_IMPLEMENTATION: This define has been        |
|     available until boost version 1.48.0 and is no longer supported.         |
+-----------------------------------------------------------------------------*/

#if defined(ICL_USE_BOOST_MOVE_IMPLEMENTATION)
#   define ICL_IMPL_SPACE boost::container
#elif defined(ICL_USE_STD_IMPLEMENTATION)
#   define ICL_IMPL_SPACE std
#else
#   define ICL_IMPL_SPACE std
#endif

/*-----------------------------------------------------------------------------+
| MEMO 2012-12-30: Due to problems with new c++11 compilers and their          | 
| implementation of rvalue references, ICL's move implementation will be       |
| disabled for some new compilers for version 1.53.                            |
+-----------------------------------------------------------------------------*/
#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#   define BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//#elif defined(__clang__)
//#   define BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
//#elif (defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ >= 7))
//#   define BOOST_ICL_NO_CXX11_RVALUE_REFERENCES
#endif

#include <boost/move/move.hpp>

#endif // BOOST_ICL_IMPL_CONFIG_HPP_JOFA_091225



/* impl_config.hpp
z3TqHNDdxhCSp+V/mu42xqNcXVaEMnIuqaYVKGO2wdCGf2wDzTITp+vmmVDnAb0dVTrfcK4kKcVkL3HekQYgp5WqvdxIg9H16FCGnGdJKOsW1IUurZphuj0z3EiLVu2Yx86g942lvb+MPLK/qjw9rfacpsmjpwvRJtVU5RZUXyHKWX8j8RGDRKlfflHPYdQHcDH0vYp684VXhiLhIPJspKmm1aZh6raKIXK5pKFiqthO9Ls3NNTfScWvmX7J9Qr7rduO42b+9fVqFvKo9p6o1Y6LkNe8kbrNkDBNzV+KtqKmN2D6b22PFDuOa5FmnPpFaCDDN0EKAXn4pb878eSi56oHFxcl8pUH/TzcWk7FtFl4Lqa+/XQxZpFfPDWLlGx7O7lLlp0oy8G4aueagkutXqcB2fYRqjfb9B/nUI/j1NIi8P0Vn4f3GDFR3UK9kEP677pFRPaMoOdjR9H97fi0h+2vfjVARQikrqpOnJi871RIqK8atDv7jSvqoBdKRBHCqshNU7MMlMWon9F1V6Ga15hNEqvSZEg6gCuSWSUDmzFN+nMr/aNgzV8Es9Wj6opmmkra6R/7+yxybPAvF1+dqI8Oec6loghfuj9Q9ZyLnKo955Ll4cr1jzyDkHmSZIJ/eB58Q6Q1D7uSRK4v/3B7SGWa/kzSZxUQg65oP2Oqz0bdKcemPhqsOO040dGR0V54TUl9UYeeqz52if3ULyKN1ds32JhyNZSajhOj04JPgmL6Ax47TTWqDqhFdsHSMYtWHvFAxn044VGxvbBFVKI8OlDbxqb75dn09tLHD/14pD86Oo5DOyO11fOJqC8AlNgI8hUE8Uz/nY9xldtKzle3lfY9gJkKF9LXKvPKngtVZRaVlJWqyupXUvZTVdaokjKzRXRZg0rK7FVlVpWUearKGlZSFqsqa1xJmUhV1rSSsnGqsmqVlC1SlVWvpGyNquwn9fcbzPZUlVH/MNMxlFWj9t1X76/+duGKqizKHv8wykpVZdUd/rrsq2p9zDdP5UgmiystI9ONKy8jqS3KKo0bjGAOZdr58Zimnr/U6wxZgHkZ5fra9z5G/SyqPqP8TzFLjqqMLI/5PK4qM67seKnKDCqLTxdXLd74dybyDS7jpQLJY7zs0qmvecmllUe9ZGPmqV8qMPM1LwIr//sEnXUxXshp8hkv/XTmoV7oMeur/pCR+a0zmfaP6KUZ14REzHZgqd5ZxUSF+feKxS1BNY23GXh904vZfup3B5o202TQ010Y09QLIvUX3+ovxpnbRDZUJz+WZFW2DFU95jfjZJrxToLxvfk/cM9UKtTdbMw0LY+OYfW0HpEWIQ8+Nc+2hnm6sdkaTBtqX+8w7Z2k5R/T2usooqb/kLS/INF8QMdSfYvsHxaMF2669agHPZ3yGDLNvCZM+tqQvh8s+evrxQaUUftmS8o0Ce8Cg8nb8UAyUsVYLQv9QUkSndZlru8G1kdNS5eS9THLSF5WJWVfVfPl/KGM3L/+sEwD6thWXkb2fV7lyyTzrai8jMy3Yek/dq3EKd3OjXqmIiNkmvwZS5xqpDfJx6+6AhLy6DK6UtWPA76a1/2ba7w5pH+V5BdTdhhj7pvtt4ZmOG2Hh+STfWOWkbwoUlaRwiJpgL2pkaptH/XJmM55Qr3YrOK+6cRozMTsYyPf+yzT7WMrytc1bIty5mLob8VoW/i/WAhmlr/CPCbeuuv5iLzOWn2ELpiuWA/Sct31WGC62AVVzbS2dbnu9ptQz4HI69eyYrkKLNdA65nHffnfPw8RWpLImq+OJrX71RDD+geq+r6kaTw+/a5M84cf6jdBzHlCmc8c2I4yJ902WUHyKrY9aLlum2zR2XY=
*/