//  Boost string_algo library concept.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CONCEPT_HPP
#define BOOST_STRING_CONCEPT_HPP

#include <boost/concept_check.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

/*! \file 
    Defines concepts used in string_algo library
*/

namespace boost {
    namespace algorithm {

        //! Finder concept
        /*!
            Defines the Finder concept. Finder is a functor which selects
            an arbitrary part of a string. Search is performed on
            the range specified by starting and ending iterators.

            Result of the find operation must be convertible to iterator_range.
        */
        template<typename FinderT, typename IteratorT>
        struct FinderConcept
        {
        private:
            typedef iterator_range<IteratorT> range;
        public:
            void constraints()
            {
                // Operation
                r=(*pF)(i,i);
            }
        private:
            range r;
            IteratorT i;
            FinderT* pF;    
        }; // Finder_concept

        
        //! Formatter concept
        /*!
            Defines the Formatter concept. Formatter is a functor, which
            takes a result from a finder operation and transforms it
            in a specific way.

            Result must be a container supported by container_traits, 
            or a reference to it.
        */
        template<typename FormatterT, typename FinderT, typename IteratorT>
        struct FormatterConcept
        {
        public:
            void constraints()
            {
                // Operation
                ::boost::begin((*pFo)( (*pF)(i,i) ));
                ::boost::end((*pFo)( (*pF)(i,i) ));
            }
        private:
            IteratorT i;
            FinderT* pF;
            FormatterT *pFo;
        }; // FormatterConcept;

    } // namespace algorithm
} // namespace boost




#endif  // BOOST_STRING_CONCEPT_HPP

/* concept.hpp
zjRuy+WjNrPnP8Daxz98NDK6WcI9dB/XSH6KuG+UfEkjHM9Env0DbiNdf6uVppvV1pPtsuBdnGY/JLcKj05KU7YU3bbeW6gspfctFAZnu0Ry706UH6lRi0ca3g12kZ57ezdyanDltYGz1Vb/vlgIOlW+Xt3U0Nhfe8kc1mvsDCcgZyZ0Yf4eLeU/8z4onPy7XuouFeTlnRUXV0V6W+xgFN76S+zxMU5tF5zZKvJpQPf9zEtJ3LBxOV6iAuE+Q7WL6ozWVgS+cqMFvC7GgMLnUoXontzr2SDBefDnTLkeNzbppngxnbNNfc8+2t1mfb3W+3pJddfQzhf+q/84z3ROunFsu/udQ7A5NtVWB+1bdQM1Dba5yqAr2k1lmykLxIwJJamL2Lbujp4IBedGYdfwzjfHXp3pJivYv8muWS9gfVxH1HXUaiMvrcq/uUZ09iGjw+dzaqqrtlgaZ+knnF6IWOnoZGwP7gy8PQ93sKK5uMpkaopLv5my9O/cPgqja6+sCc9vG9iYPie+PzAaM11detrxWvDfMBmchLrdk0XvkHl/qu4DUfSFM9vKpDDk17/eyIP2pGmhGEJvf0XrrxN40jjCsIyNLKmErRSSlaE/F/Na/VUA3QOwkh3Ku14NvVh+hHASo9ug4HWPL9G6zf0KeQviXQzpUnoezhf3CVXc4jgLLIpI47OfzrNCgksG1/Ku8S8fcc17FvSWbF2H
*/