//  Boost string_algo library find_iterator.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_ITERATOR_DETAIL_HPP
#define BOOST_STRING_FIND_ITERATOR_DETAIL_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/function.hpp>

namespace boost {
    namespace algorithm { 
        namespace detail {

//  find_iterator base -----------------------------------------------//

            // Find iterator base
            template<typename IteratorT>
            class find_iterator_base
            {
            protected:
                // typedefs
                typedef IteratorT input_iterator_type;
                typedef iterator_range<IteratorT> match_type;
                typedef function2<
                    match_type, 
                    input_iterator_type, 
                    input_iterator_type> finder_type;
                
            protected:
            // Protected construction/destruction

                // Default constructor
                find_iterator_base() {}
                // Copy construction
                find_iterator_base( const find_iterator_base& Other ) :
                    m_Finder(Other.m_Finder) {}
                
                // Constructor
                template<typename FinderT>
                find_iterator_base( FinderT Finder, int ) :
                    m_Finder(Finder) {}

                // Destructor
                ~find_iterator_base() {}

                // Find operation
                match_type do_find( 
                    input_iterator_type Begin,
                    input_iterator_type End ) const
                {
                    if (!m_Finder.empty())
                    {
                        return m_Finder(Begin,End);
                    }
                    else
                    {
                        return match_type(End,End);
                    }
                }

                // Check
                bool is_null() const
                {
                    return m_Finder.empty();
                }

            private:
                // Finder
                finder_type m_Finder;
            };

       } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_FIND_ITERATOR_DETAIL_HPP

/* find_iterator.hpp
yrNLYL78zT1zqUvQhpPtRG3QuoqVGydvsonzADG4ARyrTEr0RDMmxVneEIPSKzCDEv3nV+C46utUq0uGyiOW+ngehFA6bqkZ8prBwUzbOE4rrNpyGRp1saNBTydEmA64d7FIOPZDja3CWOgDqufR/4m9nVXIDcPyOyF56+5XX/8VmN2tI2PyMjY+pfWTcmxiYqV++aDf3DOvXpxLtq06HlM0VvJbURwxo8jUpIEWKbyQcbacrw73zA9+25iHHhym+xojKdvGGenayJy7lmlxLKMgATSMbCYRQj4g42jDm6nC+J3qi9S7164NUU+kuR/6ooAFdTcL8mNZRXPOPsTacr1jfRqxcsbkX28e8jbRPXOi408kKY9fSn5r07dwQlKafhT5znXwK78PPInBcUDDFnZn7iBix5I0XLCy/1YV/u2Q4Y/biR2At6x3fPV2Zt4WTBds4Ed2NICf3rIxGVyNmKYdnJatjMbHnqSYvtRRKqmpsQDPsqHedRu6xydk4YSKrrlOOuuh4yYl58ndsSx7KFuGx5fukN7OioY/n+sVpW9PTmKrJL1J7VqeO9hkair2kg1XC8ZOvCRr4iaZ7fAWmNoMqxm8PIeEMZYK9RoY6y56gSEbV5y6svtFwZt9LGU5tt9Sn2q8zsfKpNa9
*/