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
LIq11bpZg4XGbETbRwUpTL/ZLhz4DCw8wO6T0V3YYFAODvBRQpv/PQlaajRFL0fG7jcnHUyMk+l4g7H9IlTqH3Q4pysv3k18UDgDMykQ537t3sSMzbl112edxv8Ii/JV7VRXrtjK9+Vp4vIpj8RodYjn4zIRxxH0j8lQjAlBcH6puOt6P1o+jXjVFTiojcJYYg57rtDjWshJNVe+rsCkcGlxMjQkEZBPA9dRs2mLJ5cdyKelafGKOwpaB9SbVdLdNrVTWY/fO/lYJ7fobPr/7N8omGDOf4fwfzMMG40wkkDsSL0phhkhelhrqtL+9Yt1r0Ytz8Zhn/DtzhxXC4wejYktnJ3+sT/n4CMxgvqFXW46aNuN3CLFD5jn/lfNv8NIr8QyM2J0k+EV7lBr8qbdq5vt1TA8wOmkR55DvGLZvR/N42x29p7kOxI+R/bf/641OqVsjXkmV02Q0rWWNinQvwLmVuVEIXsr0vbB+xzkeXWbQt4wTjIYw5P70FU0hDmegTWIPSb9hm4geJKmCZdiREwlu9GKPSFoiCtjlN2pez2BJ2t6np7EzMffMtsqWTehniePpUz5ozSmPaeQDAFPp+gHpeQGHms7rttAUsDB0XPDXIvqIDhJloxpmfgvPGEq0uJ2IqVSrl7Rye2dgD94CFptBpxAeRc/7YLjdyR7DVeA6pM6H3okVp+E7ZmTnyax0fV5UsJBUeHjOV2Z
*/