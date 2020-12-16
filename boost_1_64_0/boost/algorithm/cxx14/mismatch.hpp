/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  mismatch.hpp
/// \brief Find the first mismatched element in a sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_MISMATCH_HPP
#define BOOST_ALGORITHM_MISMATCH_HPP

#include <utility>      // for std::pair

#include <boost/config.hpp>

namespace boost { namespace algorithm {

/// \fn mismatch ( InputIterator1 first1, InputIterator1 last1, 
///                InputIterator2 first2, InputIterator2 last2,
///                BinaryPredicate pred )
/// \return a pair of iterators pointing to the first elements in the sequence that do not match
/// 
/// \param first1    The start of the first range.
/// \param last1     One past the end of the first range.
/// \param first2    The start of the second range.
/// \param last2     One past the end of the second range.
/// \param pred      A predicate for comparing the elements of the ranges
template <class InputIterator1, class InputIterator2, class BinaryPredicate>
BOOST_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2> mismatch (
                    InputIterator1 first1, InputIterator1 last1,
                    InputIterator2 first2, InputIterator2 last2,
                    BinaryPredicate pred )
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
        if ( !pred ( *first1, *first2 ))
            break;
    return std::pair<InputIterator1, InputIterator2>(first1, first2);
}

/// \fn mismatch ( InputIterator1 first1, InputIterator1 last1, 
///                InputIterator2 first2, InputIterator2 last2 )
/// \return a pair of iterators pointing to the first elements in the sequence that do not match
/// 
/// \param first1    The start of the first range.
/// \param last1     One past the end of the first range.
/// \param first2    The start of the second range.
/// \param last2     One past the end of the second range.
template <class InputIterator1, class InputIterator2>
BOOST_CXX14_CONSTEXPR std::pair<InputIterator1, InputIterator2> mismatch (
                    InputIterator1 first1, InputIterator1 last1,
                    InputIterator2 first2, InputIterator2 last2 )
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
        if ( *first1 != *first2 )
            break;
    return std::pair<InputIterator1, InputIterator2>(first1, first2);
}

//  There are already range-based versions of these.

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_MISMATCH_HPP

/* mismatch.hpp
iPLydrIWfwJv1Oqjf+M+JyvoA/xYTTv3TAyU4S74l7F3Cd+vH3hRa+WHaKXRHhJylE+nsVbEzm0J368jE9YU+6kTfFdxJ7jwbgc4Q4Um6gni18p+V/i/Efix87Fv3Uwwf51kEMx0ktHSlVW0Y/daKGUcoZMnyGiezGQ0xAWgjsrMF1izwEZe/eQOBNAo9iC/I09dnZTp0xnArlHiDoLIfyOcEicSJc5ZpFMij3l4cACXPjQ/SxxsTf/7grF+MAG/AWRa35+J3msvyoidGa6U4d8e5cCjupN3W8mH2pWibDDvPG8bw+sLe0l7UXPncpryyL2UfYWV819AsrvXH2wlHAl42MrQbXw/Ela9Sqkl83lEOPUljuQ/QfQ+p8yjlNh7dL5FF8E7MBmhxz/zco87hLOi7VWmNgDmF9iPZWFor7Qqg0oZBnyy0mornUSyulyJ8ZlC4/MlLPOy0MBGsQHdgPr4BsXtaAJ0B5NmijHLzZOrmtzOTxfbTPgUqd706/404zeDmf8/HzZWWXvesSMRWgDJdlUjtmmv8c2NcjB+MmDCtCTvPgtFYAjw67x55LemjZl6enyYo53bpFWxmp3ZVFzWIEMycVFjqhJLe3cZTzQ9kt0FVaTnujPGaqpLhMptmU/s22Flr18bZ++TYA+CYjrypTgOimJzQuuAD0rlKcJMavXj7I2HPVHKwV/ZW6Sx/j8X2n+ANzXf/4Tlty1uYf+zMJS/sIXy68Ly981rYf8Tlv8S1D8t89tZAgpqO962bovUhWL1Vz5dxX3/D9qdZoDb0r27BfCeKjEnVoY+gvuQjTGeSs7CWC0X8G9ooJfWGKAZGuj8KksC6OkU9aZsVKfdWXjnWV30YFSvXyk2/fjs2L8SCY4koHlQAsNPmjCfvRLpNAGLkXhityywaU8PtnCfpL/4NvbvpIc4lmDSsMi3OavhhI/84D4GY9Jq1i/OMu6WhLX9BL8fKa9sWBAatG/xJRK8thFz+RJ7aq3X1UehF5H9ykDx9dNaUq1fyzGTwYQ+vYdHbE9IS1xlibOfytho+EbY/y4IyYfwH3TYYkLdniwHjKCBhJVX94+wHea4eA/GQEihZGBPbVEOYXOfU4UQwyAhObHoCCFme+g0vNlKrsBvhPh78EvgXHwkZmbX4iMWW8lGE73F2kprzBylT7gVCfMvO4gcybMqmG6vK9NoK17AH1/B7AR56JmKthyhb8c/Uk0uvj+FPB1nxiyILRcVykdGTn+E3Lye0MgxEwV6UpXXrCKKgcNM/ckSWAnfhMSFwxJYdvdJLozt0xZm7WoglOyprUvIzb7YVjoUy0iVxdISvnRdRa7BRLI9sOJHUjmLwno9fTLRcpTj+qbdXny0je2BMsAhjkW1VLxvlq2E1kSJemjOYjyhnHdKNy7qxNTqLn/glANh8fcD+63ea7uJDyTWMBzeOVbH53L/bjn9u999M/xsS5ZAXRuE5Mejt383Pn9g1MGyGfGrLYodiOf072Z74Mhxapw1nAeEi5BUrMJKpOOYLvztVFMBppssfyR0zj122wMvAqDu46LaNgApvLK41mwreRwV4KHwqeIjZk+1wyeZtbnx3EYrToZ8ghctIVJvhulY7M65Faiv+QC4kOtA06UMv5A+XRYybXaLRWrsBWhiaQcgFKq0yhKPilC1WUlEYSplfC1RaVzGBS+qsvB5wZ4fVIYQXSBBkD286zfNmh2C6AII/fI1Q0F2+TkC+f/4TzN++eT8MH4JLqTM+SONvdmTp4+sCyMBVx3KxKUki26hQ1wX+A9EnJeRogX/7CAIMJKPhlaxE9r9nQC+Xz0pVI9HIWidg10pSHbeQ3QIZlfOHxsSb58hPm0=
*/