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