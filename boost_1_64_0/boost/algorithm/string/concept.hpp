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
CYBq5mlgZm74w7kb0Nv/Hd2B85ZRaHuQQWjRcB1izKEW6GrPFEHgmdgQhSKFwuKkAZqz0kNSoFGUUe1FLLrKeHJuHFgohhuDqi1GkBt27Bh7b8gHNj+MuM+ZEpZkYg9myjOS0E/e9eol3E0fipi3fd2qXEuO4RE4Q+k6WhLIJWyWRBxqL509/OGj2US9JzL2rRC71aiwkyeNicJ7dygf0QhI/6JlDgKK92dKzhDqn/Vpi4N50AM0+ipeFAXim9Fj9K6+DewZHaBYzRXrM+rfusgXrRwcGEDIKYeIv2XKEDPBUvcy67KJfsQx7wcWQQEv7CFCJx5CibzaHSLrx2a+szTSKoyTds7Qg0dNc3VsF4UAdiQIvinIQGvLTJdXMwPxxjZiSqe5ktTjGuE8CVDGm8t1D58vezXiYPOdFtZsJlLPQo88ZFIOvmcIhSt00yaD3ZsDZZQyku0h8x0GIZFjlG/qOtgnvHDmgsTt+DBrjTVZrmS8ufPX7VRE21eKOOVjy+a01b963jgdQ0OYlF6FywkcaUpnjbGoAWGABY17dWlNAXhAMg1Yb94oRg==
*/