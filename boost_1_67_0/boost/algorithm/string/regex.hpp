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