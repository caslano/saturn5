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