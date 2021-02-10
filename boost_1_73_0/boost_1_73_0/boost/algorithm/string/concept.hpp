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
NCtoSPIoCSgLCvnQuxmQbZqR1YEm4Blwwb+/klcMWzNeIHcwEt67vxQthUOLVRHng9F/GDGF58LqkdmWvKVH5uExx2j4JIy2W5rRpCDo0bMf/KBJyKgwwEX2RnJaVJGr42Tlx6igOXl+E6KKHSUZzQ8Y2J/YfDnGfiaoRXgw2kCW+HvgTLeM50eSviZV8Lk5JKQQ4hDFpokYXVRfmlfs/MIS8SOvPlhxjOICBx5yo0c2uygn8B8c8IuC7g8MFUd5oWjjdoBNZ2flkFrW+bOfw7CD2u/lMGNo64C/vr72UsDkedxLs5cq8JgMl33/cMj7whk+ghcwrzAJMTLR9g192h/jIjrEVLGjA4E++JlfUAzLnmdVkMZgyfnTp6cLZucZjlI5BIQPgWU9Lb/M593F3fWTaLrTCTTX9pUAYovDZnfOpGvf2qJ757jYG5XdaffOdbtN6NqdNKGOmdgxUU9QSGUP9lQC5hsO8U+I4v/Qv/+6zRPHLZOXT4htlu7J+rM9Gt6MO4T+XohELp0Dd4BnMByXWhx3eH2jDoBCUMMUOjRYpxMwmc4xCXRMEh2TSKcpEwOhesABFQXPU8e5MwfmanAzbAkMMqleqxC0RYE4TSJHp0Lz6i4z7n7lbhTjWuxBuo9XXfwz/ij+PHHw
*/