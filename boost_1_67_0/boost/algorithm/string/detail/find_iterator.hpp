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