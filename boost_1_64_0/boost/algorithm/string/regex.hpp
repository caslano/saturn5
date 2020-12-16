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
jgCyXi05mjfErrYKYnU76KkjVJzHd/DoPBAdi/K/kPM/J5f8jZ4hys/ze0Xm+o+2avK3iie8CAHnO6tuwFYDuh3a2Gt+tJ71np9OuF1cZF0EopnzUV/mCHxA8cLxGk4IAzQl81w2l+tQoIMTn0EC8M0WF5NC66l2239P2r7qdEs8bTd7g7TWQzgthY5r3NeDGGLyS1e1cQ3SeFOOSPrcnwDFXNaP2VQ4/HQcCarKI4XcxRWYJfaaXWVyoP4F8DBsErwHoeUD+DKzidkl7GoOtojJNG+B5g4dpG7316OO/f/3efspNruVUrpVp0VtGIRn95HtRJG1bTzp6gOH4Kyb7LN/ouUxiNtO97IHtn2iS/4/6ZJ/hsr/pbbPyb/04PPfx778Xr6lmZuv5VkTaKhZw9/kfuoT1ezZvjLlGmJWnsJXlfcTcO8ANoAG+BbsXrSE+LxMr/wyeUl/kycvL8+/RfWKRrXf/lTqFfegV3jMyl1t+9veyU6PxpXK/PclOOaGICbHLeZ5qJ7W1/7Zn1r/yUu6/3ldW9f1nyT4k0d1c/9zEvz773WNPzsJ/rDWzfpPEnzZ2m7Wf5Lgwzd1hR+TBN/0bld4RhJ8Sjfpv5ebtP71YTflT4I/eWQ35Re4kZfXD/dRXQ4ZZ91HtedYvoHqr5De+JpRyl+/zz6Qq4a63Od4tqLCmLUBn2ozNE0d6m920ZqzI5CAktfhmVosOm9sHoUGtI55HnqWNXqrP36Kfd7QBubYnQSV+3I95mN8EDPMV7TLmHdHFlSKDkHpvOmx5Yb1bV9EcoeMhT7cuXYI/nqpa9nw2rPz1aNefdFZ1aIyIfBQXNHWm69ow0eh9VLAL3o0ugCI+D4cWEdYwMOslyILq1GwjgJWXwt4pPXSx8KijYQVUUcF9mj4sVoLUDoiaOGNbgvVoV7SVZRgAQIzgZSVhJRhvTjxcsweJMqoRQjpAdScJNRs68WVgtoHIflAdSeh5lkvuYxnEVBcEWUW+Brmbt3bM9T+v2zFj/OIGF4i2ww5Tl50hgVmxfma/leI9UJlOwPa0uCQt903/VwWD03nxEy4FOU+EPu1MOISMKLbPMKBpLSPgmVvB4zd4Q/cgbL1gfBuz5Tegg3FSC0KbWPebqXcegViv6Q0xCRiPvmjTNi6XiGi9rmQgu+9lIsPa81ZhBZz9g1Ef06orctf+xJ+cztS2wWXOvakOx11h1ETNz3xzUURPT1ygWahuOdcAH7TNXSCnBp8ONxzsvmd/ovXdi8PfDQJDuA/V5J3MxnJjnCJJNKL4E/HZ+h9DNNnXFDsN9p9RjDXb+zyGYdhemxcUGBMdxpXuXzGj9EDP0qPb0n3a+16vC1dM/3armhBqS8q5z+D4T0e9023sBeUJQHOOXZeJrn8KiKt3EWTcU8In/2D8Q+dKMse95xvf4pOH3T48JWBQmUHwbmB+DuuQM7qIAqG4N2B+CYrCJ+71KuO5tUQ4AgR2+sJiiive9VrABhxszikNWJmqhHEGcqp9hvNVIuUOL7wmq5eg0Y8BPW2SOJUG/X4D2YCYCC7Jr9BmWeBFvrCa6Z6xQ29FCOgNRlyuhdvcAmD6RQFazeXRmiioJlQDNzPbTPqdOPToPu5at1YH0AtGvX4qOW3BrzV4C1goKrcz30a4M8O3ajGG5QBvIPEoIRS6RFRN96iD/dz6AL1QkYHxfdI5NUSodZvLMUHJxwUAFLFW9yPa1rczw0oRYjf/RyM7A2ciOD2p0RQcZxgsPO9iOhX7y5KHu+ddY0s6Q0l1o0V8GsY3rAnvjldQwXW+WJ9TgHhZTXeGt27PAf/1cbNvlqHsaqsydvkbchp8q6Kb+4bG3S4UU9I3pU=
*/