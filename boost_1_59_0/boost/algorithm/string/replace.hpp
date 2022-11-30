//  Boost string_algo library replace.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_REPLACE_HPP
#define BOOST_STRING_REPLACE_HPP

#include <boost/algorithm/string/config.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/const_iterator.hpp>

#include <boost/algorithm/string/find_format.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/formatter.hpp>
#include <boost/algorithm/string/compare.hpp>

/*! \file
    Defines various replace algorithms. Each algorithm replaces
    part(s) of the input according to set of searching and replace criteria.
*/

namespace boost {
    namespace algorithm {

//  replace_range --------------------------------------------------------------------//

        //! Replace range algorithm
        /*!
            Replace the given range in the input string.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            
            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param SearchRange A range in the input to be substituted
            \param Format A substitute string
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

              \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT replace_range_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const iterator_range<
                BOOST_STRING_TYPENAME 
                    range_const_iterator<Range1T>::type>& SearchRange,
            const Range2T& Format)
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::range_finder(SearchRange),
                ::boost::algorithm::const_formatter(Format));
        }

        //! Replace range algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT replace_range_copy( 
            const SequenceT& Input,
            const iterator_range<
                BOOST_STRING_TYPENAME 
                    range_const_iterator<SequenceT>::type>& SearchRange,
            const RangeT& Format)
        {
            return ::boost::algorithm::find_format_copy(
                Input,
                ::boost::algorithm::range_finder(SearchRange),
                ::boost::algorithm::const_formatter(Format));
        }

        //! Replace range algorithm
        /*!
            Replace the given range in the input string. 
            The input sequence is modified in-place.

            \param Input An input string
            \param SearchRange A range in the input to be substituted
            \param Format A substitute string
        */
        template<typename SequenceT, typename RangeT>
        inline void replace_range( 
            SequenceT& Input,
            const iterator_range<
                BOOST_STRING_TYPENAME 
                    range_iterator<SequenceT>::type>& SearchRange,
            const RangeT& Format)
        {
            ::boost::algorithm::find_format(
                Input,
                ::boost::algorithm::range_finder(SearchRange),
                ::boost::algorithm::const_formatter(Format));
        }

//  replace_first --------------------------------------------------------------------//

        //! Replace first algorithm
        /*!
            Replace the first match of the search substring in the input 
            with the format string. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            
            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input

              \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT replace_first_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format)
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace first algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT replace_first_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace first algorithm
        /*!
            replace the first match of the search substring in the input 
            with the format string. The input sequence is modified in-place.

            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void replace_first( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

//  replace_first ( case insensitive ) ---------------------------------------------//

        //! Replace first algorithm ( case insensitive )
        /*!
            Replace the first match of the search substring in the input 
            with the format string. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            Searching is case insensitive.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
            \param Loc A locale used for case insensitive comparison
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT ireplace_first_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace first algorithm ( case insensitive )
        /*!
            \overload
        */
        template<typename SequenceT, typename Range2T, typename Range1T>
        inline SequenceT ireplace_first_copy( 
            const SequenceT& Input,
            const Range2T& Search,
            const Range1T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace first algorithm ( case insensitive )
        /*!
            Replace the first match of the search substring in the input 
            with the format string. Input sequence is modified in-place.
            Searching is case insensitive.

            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
            \param Loc A locale used for case insensitive comparison
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void ireplace_first( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

//  replace_last --------------------------------------------------------------------//

        //! Replace last algorithm
        /*!
            Replace the last match of the search string in the input 
            with the format string. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for
            \param Format A substitute string
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input            

              \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT replace_last_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace last algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT replace_last_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace last algorithm
        /*!
            Replace the last match of the search string in the input 
            with the format string. Input sequence is modified in-place.

            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void replace_last( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

//  replace_last ( case insensitive ) -----------------------------------------------//

        //! Replace last algorithm ( case insensitive )
        /*!
            Replace the last match of the search string in the input 
            with the format string. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            Searching is case insensitive.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
            \param Loc A locale used for case insensitive comparison
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input  

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT ireplace_last_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::last_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace last algorithm ( case insensitive )
        /*!
            \overload
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT ireplace_last_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::last_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace last algorithm ( case insensitive )
        /*!
            Replace the last match of the search string in the input 
            with the format string.The input sequence is modified in-place.
            Searching is case insensitive.

            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
            \param Loc A locale used for case insensitive comparison
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void ireplace_last( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::last_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

//  replace_nth --------------------------------------------------------------------//

        //! Replace nth algorithm
        /*!
            Replace an Nth (zero-indexed) match of the search string in the input 
            with the format string. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for 
            \param Nth An index of the match to be replaced. The index is 0-based.
                For negative N, matches are counted from the end of string.
            \param Format A substitute string
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT replace_nth_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            int Nth,
            const Range3T& Format )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace nth algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT replace_nth_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            int Nth,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace nth algorithm
        /*!
            Replace an Nth (zero-indexed) match of the search string in the input 
            with the format string. Input sequence is modified in-place.

            \param Input An input string
            \param Search A substring to be searched for 
            \param Nth An index of the match to be replaced. The index is 0-based.
                For negative N, matches are counted from the end of string.
            \param Format A substitute string
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void replace_nth( 
            SequenceT& Input,
            const Range1T& Search,
            int Nth,
            const Range2T& Format )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::const_formatter(Format) );
        }

//  replace_nth ( case insensitive ) -----------------------------------------------//
        
        //! Replace nth algorithm ( case insensitive )
        /*!
            Replace an Nth (zero-indexed) match of the search string in the input 
            with the format string. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            Searching is case insensitive.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for 
            \param Nth An index of the match to be replaced. The index is 0-based.
                For negative N, matches are counted from the end of string.
            \param Format A substitute string
            \param Loc A locale used for case insensitive comparison
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input            

            \note The second variant of this function provides the strong exception-safety guarantee
       */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT ireplace_nth_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            int Nth,
            const Range3T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::nth_finder(Search, Nth, is_iequal(Loc) ),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace nth algorithm ( case insensitive )
        /*!
            \overload
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT ireplace_nth_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            int Nth,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::nth_finder(Search, Nth, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace nth algorithm ( case insensitive )
        /*!
            Replace an Nth (zero-indexed) match of the search string in the input 
            with the format string. Input sequence is modified in-place.
            Searching is case insensitive.

            \param Input An input string
            \param Search A substring to be searched for 
            \param Nth An index of the match to be replaced. The index is 0-based.
                For negative N, matches are counted from the end of string.
            \param Format A substitute string
            \param Loc A locale used for case insensitive comparison
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void ireplace_nth( 
            SequenceT& Input,
            const Range1T& Search,
            int Nth,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

//  replace_all --------------------------------------------------------------------//

        //! Replace all algorithm
        /*!
            Replace all occurrences of the search string in the input 
            with the format string. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input 

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT replace_all_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format )
        {
            return ::boost::algorithm::find_format_all_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace all algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT replace_all_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_all_copy( 
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace all algorithm
        /*!
            Replace all occurrences of the search string in the input 
            with the format string. The input sequence is modified in-place.

            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void replace_all( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format )
        {
            ::boost::algorithm::find_format_all( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::const_formatter(Format) );
        }
        
//  replace_all ( case insensitive ) -----------------------------------------------//

        //! Replace all algorithm ( case insensitive )
        /*!
            Replace all occurrences of the search string in the input 
            with the format string. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            Searching is case insensitive.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
            \param Loc A locale used for case insensitive comparison
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input 

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T,
            typename Range3T>
        inline OutputIteratorT ireplace_all_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const Range3T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_all_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace all algorithm ( case insensitive )
        /*!
            \overload
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline SequenceT ireplace_all_copy( 
            const SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_all_copy( 
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace all algorithm ( case insensitive )
        /*!
            Replace all occurrences of the search string in the input 
            with the format string.The input sequence is modified in-place.
            Searching is case insensitive.

            \param Input An input string
            \param Search A substring to be searched for 
            \param Format A substitute string
            \param Loc A locale used for case insensitive comparison
        */
        template<typename SequenceT, typename Range1T, typename Range2T>
        inline void ireplace_all( 
            SequenceT& Input,
            const Range1T& Search,
            const Range2T& Format,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format_all( 
                Input, 
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::const_formatter(Format) );
        }
        
//  replace_head --------------------------------------------------------------------//

        //! Replace head algorithm
        /*!
            Replace the head of the input with the given format string. 
            The head is a prefix of a string of given size. 
            If the sequence is shorter then required, whole string if 
            considered to be the head. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            
            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param N Length of the head.
                For N>=0, at most N characters are extracted.
                For N<0, size(Input)-|N| characters are extracted.
            \param Format A substitute string
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input  

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT replace_head_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            int N,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace head algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT replace_head_copy( 
            const SequenceT& Input,
            int N,
            const RangeT& Format )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace head algorithm
        /*!
            Replace the head of the input with the given format string. 
            The head is a prefix of a string of given size. 
            If the sequence is shorter then required, the whole string is 
            considered to be the head. The input sequence is modified in-place.

            \param Input An input string
            \param N Length of the head.
                For N>=0, at most N characters are extracted.
                For N<0, size(Input)-|N| characters are extracted.
            \param Format A substitute string
        */
        template<typename SequenceT, typename RangeT>
        inline void replace_head( 
            SequenceT& Input,
            int N,
            const RangeT& Format )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

//  replace_tail --------------------------------------------------------------------//

        //! Replace tail algorithm
        /*!
            Replace the tail of the input with the given format string. 
            The tail is a suffix of a string of given size. 
            If the sequence is shorter then required, whole string is 
            considered to be the tail. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param N Length of the tail.
                For N>=0, at most N characters are extracted.
                For N<0, size(Input)-|N| characters are extracted.
            \param Format A substitute string
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input   

              \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT replace_tail_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            int N,
            const Range2T& Format )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace tail algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT replace_tail_copy( 
            const SequenceT& Input,
            int N,
            const RangeT& Format )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

        //! Replace tail algorithm
        /*!
            Replace the tail of the input with the given format sequence. 
            The tail is a suffix of a string of given size. 
            If the sequence is shorter then required, the whole string is 
            considered to be the tail. The input sequence is modified in-place.

            \param Input An input string
            \param N Length of the tail.
                For N>=0, at most N characters are extracted.
                For N<0, size(Input)-|N| characters are extracted.
            \param Format A substitute string
        */
        template<typename SequenceT, typename RangeT>
        inline void replace_tail( 
            SequenceT& Input,
            int N,
            const RangeT& Format )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::const_formatter(Format) );
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::replace_range_copy;
    using algorithm::replace_range;
    using algorithm::replace_first_copy;
    using algorithm::replace_first;
    using algorithm::ireplace_first_copy;
    using algorithm::ireplace_first;
    using algorithm::replace_last_copy;
    using algorithm::replace_last;
    using algorithm::ireplace_last_copy;
    using algorithm::ireplace_last;
    using algorithm::replace_nth_copy;
    using algorithm::replace_nth;
    using algorithm::ireplace_nth_copy;
    using algorithm::ireplace_nth;
    using algorithm::replace_all_copy;
    using algorithm::replace_all;
    using algorithm::ireplace_all_copy;
    using algorithm::ireplace_all;
    using algorithm::replace_head_copy;
    using algorithm::replace_head;
    using algorithm::replace_tail_copy;
    using algorithm::replace_tail;

} // namespace boost

#endif  // BOOST_REPLACE_HPP

/* replace.hpp
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
*/