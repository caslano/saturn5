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
PeYpMLpBIg8nao6l9/DQ04lShJ2BZ6Wb7FQ9Om1e3uoDJFS1f1J+bsqv5h3Ob2Ul8pvzDue3sFLyW1RJ+TXwk/KTWwMyXiLw55vcykeTNi2unpZ2tClXT6+E7MF8IiwcPjwH0QaUzYnCPw4vSCOPxwFeokoULj6rIM0/e8tMKWzL95w8JsvYjEXpRkr4xx/KziqSs7cDQY9VJHgg29kS35VuLErUxFv6aotiBVFtWQB76KbSSLsL3P0RZKWZmW6z9eapogech0TADA1TRRGYywoAhJJcJsFijPSSyebzYFEx7GMcBLb5MAWU9WIl4XYERDMeoOAT9rahV1yB1zT9ZSqIL3rMdHxV5Zo7sT8fXxfiy8iYNJUMmiRZh+ANNI3Zgf23r2FxCeyb9wT2yOvuO+tJ9RlIK7glE3T3FXVQqaC+jWsEylYSwWmIOs2Ft1N3TKHyVJ70Et1zyvLf3X8lauD3x8BDUAGz/Y5EIlj2ZtUHSK4yC3S0TmGl5Gl+5D3Dj9XoROvwFjKG3koBWgPJ4smkeZUbec0Iwtvl4JVpU0RPGRUc0jAtF06Zdu4MRAsvR2gi4/v4vyHjximqv/V5hyvtB/g23Rj45/VA6ITb9fCnPfzG333uiq3+so/MpZAUnR77EqhovoAqnfgOGxPSKs+2h2FxNhh/XVAuA0onKECg3yuQj2I3gLkABA5Vg+1z8CaFU5wSvZxAP1KgDICM3QjRyxLhhh7QOLxze8hguvSqXmllDQFtOXkBPE3hryBNAioHlhliQ58BBjZzt/bE+8N411XUgiFmlsJ/XBQIm6QBDRIek/Dg+JW6gaZO0hdGia4QHLI+6B62OjBk0Q09KPg7kcxAoh66RCD8SY/rV3IFoye5b7uXuL5qe3LNPr5GMunv6FLuK18TUJ6jS21dpEBkOkRb3jsZbfkQ2sichlVQC7fwYQQT9rEKe66YpQH5hYIE6wFRu4FMbSMzxnmU2A6o1ISwHnWD9h6YVpmBKWbraXgflFZ1ou0wY7es0rYdrVboq80pGC+Qw5El6DFYEN6VS9tBQqJYIE/Vpw30Zf5WAsUQgUJqx0RSOz5wsF9Lkl40gaWNyHnPXwnCLgVhdu6OdNkfgNyRNRagHjE/hlWfywzCW39uY2YI5ggb8y1zocLc8xov5F71Ne2r+1/9zXWk2pNxDUR3959va7PWpwKJY4rKC9JS4RkCN/LecoMZqjd1rk+95uYVqYI2Zr+35Suzre2LrE/Z5z+xIVDNgIuNte7+fES/Xy0CxeFHeRFrARDpvO8+0cQLniSai9UZnc8+H3W2pC/Ho5bWSLpHsONl2gu3z0GpQGJDuPFzffap9b92S3+8X2P98XXIOvN36DSW/nhVqv5o5D2KELkm97srqUcceQsFYCbhF73y6hz7EuK+fGVCj3bSWH4ALLUp5lSQa74CQWb+5kXeSQmwn8GIjxx0ouEx2suXrNsFokM9ALSuee2gfsn12daWVJ8z4531WXzw9Zmc/m3J6fdV6WOnVRo9sxQPpCb42e2P9OS8NRrqY1H0SyF2cepgWwdJZGOV2194KELggOk42vZzMi1k3i6bxYvo/U8ue9d0IX2fjb1F+zgbz5tHAjP6BvJC+7SIrvT4lWxp+jWBemKM5xgHc0TTtn99lFSWflKWsZR6f5TEC29RKEkI32QoUr4KiLYTCGXLcqYpm95nrOL3QrzDsLLtCtFWQOpuvJoTtquOfGDODjrtX1uYOvMnr0qjedh7BLnsEhGz0dLfP7v9VSqFVMnE/JeBJiRnrHffXWsmVnHaCB6L4HL33Q0lu7lajYYD5K+TVPovrFLpJyYlpf+gnX7HpJT0o0M/ntTrQNs=
*/