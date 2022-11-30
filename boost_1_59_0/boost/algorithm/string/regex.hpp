//  Boost string_algo library regex.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_REGEX_HPP
#define BOOST_STRING_REGEX_HPP

#include <boost/algorithm/string/config.hpp>
#include <boost/regex.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/as_literal.hpp>

#include <boost/algorithm/string/find_format.hpp>
#include <boost/algorithm/string/regex_find_format.hpp>
#include <boost/algorithm/string/formatter.hpp>
#include <boost/algorithm/string/iter_find.hpp>

/*! \file
    Defines regex variants of the algorithms. 
*/

namespace boost {
    namespace algorithm {

//  find_regex  -----------------------------------------------//

        //! Find regex algorithm
        /*!
            Search for a substring matching the given regex in the input.
            
            \param Input A container which will be searched.
            \param Rx A regular expression
            \param Flags Regex options
            \return 
                An \c iterator_range delimiting the match. 
                Returned iterator is either \c RangeT::iterator or 
                \c RangeT::const_iterator, depending on the constness of 
                the input parameter.

              \note This function provides the strong exception-safety guarantee
        */
        template< 
            typename RangeT, 
            typename CharT, 
            typename RegexTraitsT>
        inline iterator_range< 
            BOOST_STRING_TYPENAME range_iterator<RangeT>::type >
        find_regex( 
            RangeT& Input, 
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            iterator_range<BOOST_STRING_TYPENAME range_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            return ::boost::algorithm::regex_finder(Rx,Flags)(
                ::boost::begin(lit_input), ::boost::end(lit_input) );
        }

//  replace_regex --------------------------------------------------------------------//

        //! Replace regex algorithm
        /*!
            Search for a substring matching given regex and format it with 
            the specified format.             
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Rx A regular expression
            \param Format Regex format definition
            \param Flags Regex options
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input   

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template< 
            typename OutputIteratorT,
            typename RangeT, 
            typename CharT, 
            typename RegexTraitsT,
            typename FormatStringTraitsT, typename FormatStringAllocatorT >
        inline OutputIteratorT replace_regex_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            const std::basic_string<CharT, FormatStringTraitsT, FormatStringAllocatorT>& Format,
            match_flag_type Flags=match_default | format_default )
        {
            return ::boost::algorithm::find_format_copy( 
                Output,
                Input,
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::regex_formatter( Format, Flags ) );
        }

        //! Replace regex algorithm
        /*!
            \overload
        */
        template< 
            typename SequenceT, 
            typename CharT, 
            typename RegexTraitsT,
            typename FormatStringTraitsT, typename FormatStringAllocatorT >
        inline SequenceT replace_regex_copy( 
            const SequenceT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            const std::basic_string<CharT, FormatStringTraitsT, FormatStringAllocatorT>& Format,
            match_flag_type Flags=match_default | format_default )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::regex_formatter( Format, Flags ) );
        }

        //! Replace regex algorithm
        /*!
            Search for a substring matching given regex and format it with 
            the specified format. The input string is modified in-place.

            \param Input An input string
            \param Rx A regular expression
            \param Format Regex format definition
            \param Flags Regex options
        */
        template< 
            typename SequenceT, 
            typename CharT, 
            typename RegexTraitsT,
            typename FormatStringTraitsT, typename FormatStringAllocatorT >
        inline void replace_regex( 
            SequenceT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            const std::basic_string<CharT, FormatStringTraitsT, FormatStringAllocatorT>& Format,
            match_flag_type Flags=match_default | format_default )
        {
            ::boost::algorithm::find_format( 
                Input,
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::regex_formatter( Format, Flags ) );
        }

//  replace_all_regex --------------------------------------------------------------------//

        //! Replace all regex algorithm
        /*!
            Format all substrings, matching given regex, with the specified format. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Rx A regular expression
            \param Format Regex format definition
            \param Flags Regex options
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input     

              \note The second variant of this function provides the strong exception-safety guarantee
        */
        template< 
            typename OutputIteratorT,
            typename RangeT, 
            typename CharT, 
            typename RegexTraitsT,
            typename FormatStringTraitsT, typename FormatStringAllocatorT >
        inline OutputIteratorT replace_all_regex_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            const std::basic_string<CharT, FormatStringTraitsT, FormatStringAllocatorT>& Format,
            match_flag_type Flags=match_default | format_default )
        {
            return ::boost::algorithm::find_format_all_copy( 
                Output,
                Input,
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::regex_formatter( Format, Flags ) );
        }

        //! Replace all regex algorithm
        /*!
            \overload
        */
        template< 
            typename SequenceT, 
            typename CharT, 
            typename RegexTraitsT,
            typename FormatStringTraitsT, typename FormatStringAllocatorT >
        inline SequenceT replace_all_regex_copy( 
            const SequenceT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            const std::basic_string<CharT, FormatStringTraitsT, FormatStringAllocatorT>& Format,
            match_flag_type Flags=match_default | format_default )
        {
            return ::boost::algorithm::find_format_all_copy( 
                Input,
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::regex_formatter( Format, Flags ) );
        }

        //! Replace all regex algorithm
        /*!
            Format all substrings, matching given regex, with the specified format. 
            The input string is modified in-place.

            \param Input An input string
            \param Rx A regular expression
            \param Format Regex format definition
            \param Flags Regex options            
        */
        template< 
            typename SequenceT, 
            typename CharT, 
            typename RegexTraitsT,
            typename FormatStringTraitsT, typename FormatStringAllocatorT >
        inline void replace_all_regex( 
            SequenceT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            const std::basic_string<CharT, FormatStringTraitsT, FormatStringAllocatorT>& Format,
            match_flag_type Flags=match_default | format_default )
        {
            ::boost::algorithm::find_format_all( 
                Input,
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::regex_formatter( Format, Flags ) );
        }

//  erase_regex --------------------------------------------------------------------//

        //! Erase regex algorithm
        /*!
            Remove a substring matching given regex from the input.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.                        

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Rx A regular expression
            \param Flags Regex options
            \return An output iterator pointing just after the last inserted character or
                       a modified copy of the input    

             \note The second variant of this function provides the strong exception-safety guarantee
       */
        template< 
            typename OutputIteratorT,
            typename RangeT, 
            typename CharT, 
            typename RegexTraitsT >
        inline OutputIteratorT erase_regex_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        //! Erase regex algorithm
        /*!
            \overload
        */
        template< 
            typename SequenceT, 
            typename CharT, 
            typename RegexTraitsT >
        inline SequenceT erase_regex_copy( 
            const SequenceT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            return ::boost::algorithm::find_format_copy( 
                Input, 
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        //! Erase regex algorithm
        /*!
            Remove a substring matching given regex from the input.
            The input string is modified in-place.

            \param Input An input string
            \param Rx A regular expression
            \param Flags Regex options
        */
        template< 
            typename SequenceT, 
            typename CharT, 
            typename RegexTraitsT >
        inline void erase_regex( 
            SequenceT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::empty_formatter( Input ) );
        }

//  erase_all_regex --------------------------------------------------------------------//

        //! Erase all regex algorithm
        /*!
            Erase all substrings, matching given regex, from the input.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Rx A regular expression
            \param Flags Regex options
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input                        

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template< 
            typename OutputIteratorT,
            typename RangeT, 
            typename CharT, 
            typename RegexTraitsT >
        inline OutputIteratorT erase_all_regex_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            return ::boost::algorithm::find_format_all_copy(
                Output,
                Input,
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        //! Erase all regex algorithm
        /*!
            \overload
        */
        template< 
            typename SequenceT, 
            typename CharT, 
            typename RegexTraitsT >
        inline SequenceT erase_all_regex_copy( 
            const SequenceT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            return ::boost::algorithm::find_format_all_copy( 
                Input, 
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        //! Erase all regex algorithm
        /*!
            Erase all substrings, matching given regex, from the input.
            The input string is modified in-place.

            \param Input An input string
            \param Rx A regular expression
            \param Flags Regex options
        */
        template< 
            typename SequenceT, 
            typename CharT, 
            typename RegexTraitsT>
        inline void erase_all_regex( 
            SequenceT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            ::boost::algorithm::find_format_all( 
                Input, 
                ::boost::algorithm::regex_finder( Rx, Flags ),
                ::boost::algorithm::empty_formatter( Input ) );
        }

//  find_all_regex ------------------------------------------------------------------//

        //! Find all regex algorithm
        /*!
            This algorithm finds all substrings matching the give regex
            in the input.             
            
            Each part is copied and added as a new element to the output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>

            \param Result A container that can hold copies of references to the substrings.
            \param Input A container which will be searched.
            \param Rx A regular expression
            \param Flags Regex options
            \return A reference to the result

            \note Prior content of the result will be overwritten.

             \note This function provides the strong exception-safety guarantee
        */
        template< 
            typename SequenceSequenceT, 
            typename RangeT,         
            typename CharT, 
            typename RegexTraitsT >
        inline SequenceSequenceT& find_all_regex(
            SequenceSequenceT& Result,
            const RangeT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            return ::boost::algorithm::iter_find(
                Result,
                Input,
                ::boost::algorithm::regex_finder(Rx,Flags) );         
        }

//  split_regex ------------------------------------------------------------------//

        //! Split regex algorithm
        /*! 
            Tokenize expression. This function is equivalent to C strtok. Input
            sequence is split into tokens, separated  by separators. Separator
            is an every match of the given regex.
            Each part is copied and added as a new element to the output container.
            Thus the result container must be able to hold copies
            of the matches (in a compatible structure like std::string) or
            a reference to it (e.g. using the iterator range class).
            Examples of such a container are \c std::vector<std::string>
            or \c std::list<boost::iterator_range<std::string::iterator>>
    
            \param Result A container that can hold copies of references to the substrings.          
            \param Input A container which will be searched.
            \param Rx A regular expression
            \param Flags Regex options
            \return A reference to the result

            \note Prior content of the result will be overwritten.

               \note This function provides the strong exception-safety guarantee
        */
        template< 
            typename SequenceSequenceT, 
            typename RangeT,         
            typename CharT, 
            typename RegexTraitsT >
        inline SequenceSequenceT& split_regex(
            SequenceSequenceT& Result,
            const RangeT& Input,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            return ::boost::algorithm::iter_split(
                Result,
                Input,
                ::boost::algorithm::regex_finder(Rx,Flags) );         
        }

//  join_if ------------------------------------------------------------------//

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING

        //! Conditional join algorithm
        /*!
            This algorithm joins all strings in a 'list' into one long string.
            Segments are concatenated by given separator. Only segments that
            match the given regular expression will be added to the result

            This is a specialization of join_if algorithm.

            \param Input A container that holds the input strings. It must be a container-of-containers.
            \param Separator A string that will separate the joined segments.
            \param Rx A regular expression
            \param Flags Regex options
            \return Concatenated string.

            \note This function provides the strong exception-safety guarantee
        */
        template< 
            typename SequenceSequenceT, 
            typename Range1T,             
            typename CharT, 
            typename RegexTraitsT >
        inline typename range_value<SequenceSequenceT>::type 
        join_if(
            const SequenceSequenceT& Input,
            const Range1T& Separator,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            // Define working types
            typedef typename range_value<SequenceSequenceT>::type ResultT;
            typedef typename range_const_iterator<SequenceSequenceT>::type InputIteratorT;

            // Parse input
            InputIteratorT itBegin=::boost::begin(Input);
            InputIteratorT itEnd=::boost::end(Input);

            // Construct container to hold the result
            ResultT Result;


            // Roll to the first element that will be added
            while(
                itBegin!=itEnd && 
                !::boost::regex_match(::boost::begin(*itBegin), ::boost::end(*itBegin), Rx, Flags)) ++itBegin;

            // Add this element
            if(itBegin!=itEnd)
            {
                detail::insert(Result, ::boost::end(Result), *itBegin);
                ++itBegin;
            }

            for(;itBegin!=itEnd; ++itBegin)
            {
                if(::boost::regex_match(::boost::begin(*itBegin), ::boost::end(*itBegin), Rx, Flags))
                {
                    // Add separator
                    detail::insert(Result, ::boost::end(Result), ::boost::as_literal(Separator));
                    // Add element
                    detail::insert(Result, ::boost::end(Result), *itBegin);
                }
            }

            return Result;
        }

#else  // BOOST_NO_FUNCTION_TEMPLATE_ORDERING

                //! Conditional join algorithm
        /*!
            This algorithm joins all strings in a 'list' into one long string.
            Segments are concatenated by given separator. Only segments that
            match the given regular expression will be added to the result

            This is a specialization of join_if algorithm.

            \param Input A container that holds the input strings. It must be a container-of-containers.
            \param Separator A string that will separate the joined segments.
            \param Rx A regular expression
            \param Flags Regex options
            \return Concatenated string.

            \note This function provides the strong exception-safety guarantee
        */
        template< 
            typename SequenceSequenceT, 
            typename Range1T,             
            typename CharT, 
            typename RegexTraitsT >
        inline typename range_value<SequenceSequenceT>::type 
        join_if_regex(
            const SequenceSequenceT& Input,
            const Range1T& Separator,
            const basic_regex<CharT, RegexTraitsT>& Rx,
            match_flag_type Flags=match_default )
        {
            // Define working types
            typedef typename range_value<SequenceSequenceT>::type ResultT;
            typedef typename range_const_iterator<SequenceSequenceT>::type InputIteratorT;

            // Parse input
            InputIteratorT itBegin=::boost::begin(Input);
            InputIteratorT itEnd=::boost::end(Input);

            // Construct container to hold the result
            ResultT Result;


            // Roll to the first element that will be added
            while(
                itBegin!=itEnd && 
                !::boost::regex_match(::boost::begin(*itBegin), ::boost::end(*itBegin), Rx, Flags)) ++itBegin;

            // Add this element
            if(itBegin!=itEnd)
            {
                detail::insert(Result, ::boost::end(Result), *itBegin);
                ++itBegin;
            }

            for(;itBegin!=itEnd; ++itBegin)
            {
                if(::boost::regex_match(::boost::begin(*itBegin), ::boost::end(*itBegin), Rx, Flags))
                {
                    // Add separator
                    detail::insert(Result, ::boost::end(Result), ::boost::as_literal(Separator));
                    // Add element
                    detail::insert(Result, ::boost::end(Result), *itBegin);
                }
            }

            return Result;
        }


#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING

    } // namespace algorithm

    // pull names into the boost namespace
    using algorithm::find_regex;
    using algorithm::replace_regex;
    using algorithm::replace_regex_copy;
    using algorithm::replace_all_regex;
    using algorithm::replace_all_regex_copy;
    using algorithm::erase_regex;
    using algorithm::erase_regex_copy;
    using algorithm::erase_all_regex;
    using algorithm::erase_all_regex_copy;
    using algorithm::find_all_regex;
    using algorithm::split_regex;

#ifndef BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    using algorithm::join_if;
#else  // BOOST_NO_FUNCTION_TEMPLATE_ORDERING
    using algorithm::join_if_regex;
#endif // BOOST_NO_FUNCTION_TEMPLATE_ORDERING

} // namespace boost


#endif  // BOOST_STRING_REGEX_HPP

/* regex.hpp
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
*/