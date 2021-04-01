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
fDMhlCyG7uvB3u1i2Li0n5UwNeZ1LCbw5m+VMx0NR/5p7gHXA7t7OzczQ3u/j7D/+DFx/2JV0Wcl5X1KaX0pbmcvDwLBawufFh2K+uLOS5QD2QutzsZ2P15AmgjTM0sOlkU4f5Swhk6iOTRzUMtrf0CwqV7L79/g4gXUUoPMeWWDBqaK1FRN2XCqysvE2UiXZhF7HPG5ARKiLtJR0Lc+Kb+zZHSWi8D13m0yPGxzxyt/D48DiNKhIh2+U9VaROVctmOAUP9kiMvJl2eH+uhKYahsLjxSAPNUxz41GmG1orzDAn/a62uvQ8n2XuIoCGFddGmlYVoYav7NOme8pMkxeohs1M4SCDwxbw/+5FNu4R5+FVKiP26/Bq6ddzWThkqpvUHRTdCpqaDx3N4sKXCeRLEzDxan46bqHedyW5bAPdOGneVSRFmWy1dyXvUfPZjr+qRJqOuwAo0zjnl7WPNaU/OiMkTQUjrh3C03p4f1PsZOtkDp22XOHx+oElSQL/pmj9lyfI8me48sPhXun84X/afTL4FCp52DQPGQKkbMdduOYXNdHXyNsaD9Zw==
*/