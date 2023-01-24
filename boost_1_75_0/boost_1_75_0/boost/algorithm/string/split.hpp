//  Boost string_algo library split.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_SPLIT_HPP
#define BOOST_STRING_SPLIT_HPP

#include <boost/algorithm/string/config.hpp>

#include <boost/algorithm/string/iter_find.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/compare.hpp>

/*! \file
    Defines basic split algorithms. 
    Split algorithms can be used to divide a string
    into several parts according to given criteria.
    
    Each part is copied and added as a new element to the
    output container.
    Thus the result container must be able to hold copies
    of the matches (in a compatible structure like std::string) or
    a reference to it (e.g. using the iterator range class).
    Examples of such a container are \c std::vector<std::string>
    or \c std::list<boost::iterator_range<std::string::iterator>>
*/

namespace boost {
    namespace algorithm {

//  find_all  ------------------------------------------------------------//

        //! Find all algorithm
        /*!
            This algorithm finds all occurrences of the search string
            in the input.
            
            Each part is copied and added as a new element to the
            output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            \param Result A container that can hold copies of references to the substrings
            \param Input A container which will be searched.
            \param Search A substring to be searched for.
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& find_all(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            Range1T&& Input,
#else
            Range1T& Input,
#endif
            const Range2T& Search)
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::first_finder(Search) );        
        }

        //! Find all algorithm ( case insensitive ) 
        /*!
            This algorithm finds all occurrences of the search string
            in the input. 
            Each part is copied and added as a new element to the
            output container. Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            Searching is case insensitive.

            \param Result A container that can hold copies of references to the substrings
            \param Input A container which will be searched.
            \param Search A substring to be searched for.
            \param Loc A locale used for case insensitive comparison
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename Range1T, typename Range2T >
        inline SequenceSequenceT& ifind_all(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            Range1T&& Input,
#else
            Range1T& Input,
#endif
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc) ) );        
        }


//  tokenize  -------------------------------------------------------------//

        //! Split algorithm
        /*! 
            Tokenize expression. This function is equivalent to C strtok. Input
            sequence is split into tokens, separated by separators. Separators 
            are given by means of the predicate.

            Each part is copied and added as a new element to the
            output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>
    
            \param Result A container that can hold copies of references to the substrings          
            \param Input A container which will be searched.
            \param Pred A predicate to identify separators. This predicate is 
                supposed to return true if a given element is a separator.
            \param eCompress If eCompress argument is set to token_compress_on, adjacent 
                separators are merged together. Otherwise, every two separators
                delimit a token.
            \return A reference the result

            \note Prior content of the result will be overwritten.

            \note This function provides the strong exception-safety guarantee
        */
        template< typename SequenceSequenceT, typename RangeT, typename PredicateT >
        inline SequenceSequenceT& split(
            SequenceSequenceT& Result,
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            RangeT&& Input,
#else
            RangeT& Input,
#endif
            PredicateT Pred,
            token_compress_mode_type eCompress=token_compress_off )
        {
            return ::boost::algorithm::iter_split(
                Result,
                Input,
                ::boost::algorithm::token_finder( Pred, eCompress ) );         
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::find_all;
    using algorithm::ifind_all;
    using algorithm::split;    

} // namespace boost


#endif  // BOOST_STRING_SPLIT_HPP


/* split.hpp
3crgmjZ2Uo/TyAaX0hmQkJk5drLiOWp6KdpS9cXj7GG7DuVC3STLm23Yuu7jcnaCFzJ7Ic+a3tG+KWwZdMKrUYe3YHLmAPPNIDCV+jwKYQcaEQgdUkd2dGXkgyYMIRab3wmkVo1zTLw9iG+hduJKhc9FawZ0Dz6T3ilE0QnYq85/lPk2c4uhbCYez+B9W7zUm+NZO+kykTI//M5YFB698GdwhVSqpZb5xhF9cKKyppeeXXwv6QAqkzxo2dqPH27uPU+LF7p5e9/Jc7jb0aPnAreyXdRJvD/GvpL37GXmyhT+pKsHiBFjp3EtJrx94p3Psvh62RgwhXX1W7QuKI+7nT23d6Im53eVOpHg09dMMeoXD1/HV43uqiJWKM4l3KjfHjgfVB/prMCJm6pM6yE8ZqhKz39ROo5dlTgMEM+228yttrrZtmuztdl23cxNm43NtutmuzbbtuvW8/8Kz5s5Z34zZ84sPE9w9YaXx/Rw+KXNj9CeVoL4VyDuL8DI3hOIr+gIRdSlnIGeUj1/NsSCt/ugnz2V7WFmGn45X/dgPj4LsCtvLiBIb5+HD5dg3+3ZtuvctGB6EFR/fQOpZ6d/gZ3RB0FBAyj/qJCEEb3b8oyGV8CoPkozcuOvclXPikol8SvbgbX7gauecKLxzI3WGfMwzbmsqzzo9V83rq9KHg5QyzO8FDd/EiLmU/zZ2TKNF+44bRj0EAMkYhkt
*/