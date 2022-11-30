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
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
*/