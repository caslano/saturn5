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
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
*/