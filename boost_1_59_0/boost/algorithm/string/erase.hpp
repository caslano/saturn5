//  Boost string_algo library erase.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2006.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_ERASE_HPP
#define BOOST_STRING_ERASE_HPP

#include <boost/algorithm/string/config.hpp>

#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/const_iterator.hpp>

#include <boost/algorithm/string/find_format.hpp>
#include <boost/algorithm/string/finder.hpp>
#include <boost/algorithm/string/formatter.hpp>

/*! \file
    Defines various erase algorithms. Each algorithm removes
    part(s) of the input according to a searching criteria.
*/

namespace boost {
    namespace algorithm {

//  erase_range -------------------------------------------------------//

        //! Erase range algorithm
        /*!
            Remove the given range from the input. The result is a modified copy of 
            the input. It is returned as a sequence or copied to the output iterator.
    
            \param Output An output iterator to which the result will be copied
            \param Input An input sequence
            \param SearchRange A range in the input to be removed
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<typename OutputIteratorT, typename RangeT>
        inline OutputIteratorT erase_range_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            const iterator_range<
                BOOST_STRING_TYPENAME 
                    range_const_iterator<RangeT>::type>& SearchRange )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::range_finder(SearchRange),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase range algorithm
        /*!
            \overload
        */
        template<typename SequenceT>
        inline SequenceT erase_range_copy( 
            const SequenceT& Input,
            const iterator_range<
                BOOST_STRING_TYPENAME 
                    range_const_iterator<SequenceT>::type>& SearchRange )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::range_finder(SearchRange),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase range algorithm
        /*!
            Remove the given range from the input.
            The input sequence is modified in-place.

            \param Input An input sequence
            \param SearchRange A range in the input to be removed
        */
        template<typename SequenceT>
        inline void erase_range( 
            SequenceT& Input,
            const iterator_range<
                BOOST_STRING_TYPENAME 
                    range_iterator<SequenceT>::type>& SearchRange )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::range_finder(SearchRange),
                ::boost::algorithm::empty_formatter(Input) );
        }

//  erase_first  --------------------------------------------------------//

        //! Erase first algorithm
        /*!
            Remove the first occurrence of the substring from the input.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for 
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input
            
            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT erase_first_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase first algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT erase_first_copy( 
            const SequenceT& Input,
            const RangeT& Search )
        {
            return ::boost::algorithm::find_format_copy( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase first algorithm
        /*!
            Remove the first occurrence of the substring from the input. 
            The input sequence is modified in-place.

            \param Input An input string
            \param Search A substring to be searched for. 
        */
        template<typename SequenceT, typename RangeT>
        inline void erase_first( 
            SequenceT& Input,
            const RangeT& Search )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

//  erase_first ( case insensitive ) ------------------------------------//

        //! Erase first algorithm ( case insensitive )
        /*!
            Remove the first occurrence of the substring from the input. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            Searching is case insensitive.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for 
            \param Loc A locale used for case insensitive comparison
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT ierase_first_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase first algorithm ( case insensitive )
        /*!
            \overload
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT ierase_first_copy( 
            const SequenceT& Input,
            const RangeT& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy( 
                Input, 
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase first algorithm ( case insensitive )
        /*!
            Remove the first occurrence of the substring from the input. 
            The input sequence is modified in-place. Searching is case insensitive.

            \param Input An input string
            \param Search A substring to be searched for
            \param Loc A locale used for case insensitive comparison
        */
        template<typename SequenceT, typename RangeT>
        inline void ierase_first( 
            SequenceT& Input,
            const RangeT& Search,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

//  erase_last  --------------------------------------------------------//

        //! Erase last algorithm
        /*!
            Remove the last occurrence of the substring from the input. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for.
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT erase_last_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase last algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT erase_last_copy( 
            const SequenceT& Input,
            const RangeT& Search )
        {
            return ::boost::algorithm::find_format_copy( 
                Input, 
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase last algorithm
        /*!
            Remove the last occurrence of the substring from the input. 
            The input sequence is modified in-place.

            \param Input An input string
            \param Search A substring to be searched for 
        */
        template<typename SequenceT, typename RangeT>
        inline void erase_last( 
            SequenceT& Input,
            const RangeT& Search )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::last_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

//  erase_last ( case insensitive ) ------------------------------------//

        //! Erase last algorithm ( case insensitive )
        /*!
            Remove the last occurrence of the substring from the input. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            Searching is case insensitive.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for
            \param Loc A locale used for case insensitive comparison
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT ierase_last_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::last_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase last algorithm ( case insensitive )
        /*!
            \overload
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT ierase_last_copy( 
            const SequenceT& Input,
            const RangeT& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy( 
                Input, 
                ::boost::algorithm::last_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase last algorithm ( case insensitive )
        /*!
            Remove the last occurrence of the substring from the input. 
            The input sequence is modified in-place. Searching is case insensitive.

            \param Input An input string
            \param Search A substring to be searched for
            \param Loc A locale used for case insensitive comparison
        */
        template<typename SequenceT, typename RangeT>
        inline void ierase_last( 
            SequenceT& Input,
            const RangeT& Search,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::last_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

//  erase_nth --------------------------------------------------------------------//

        //! Erase nth algorithm
        /*!
            Remove the Nth occurrence of the substring in the input.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
            

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for
            \param Nth An index of the match to be replaced. The index is 0-based.
                For negative N, matches are counted from the end of string.
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT erase_nth_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            int Nth )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase nth algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT erase_nth_copy( 
            const SequenceT& Input,
            const RangeT& Search,
            int Nth )
        {
            return ::boost::algorithm::find_format_copy( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase nth algorithm
        /*!
            Remove the Nth occurrence of the substring in the input.
            The input sequence is modified in-place.

            \param Input An input string
            \param Search A substring to be searched for. 
            \param Nth An index of the match to be replaced. The index is 0-based.
                For negative N, matches are counted from the end of string.
        */
        template<typename SequenceT, typename RangeT>
        inline void erase_nth( 
            SequenceT& Input,
            const RangeT& Search,
            int Nth )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth),
                ::boost::algorithm::empty_formatter(Input) );
        }

//  erase_nth ( case insensitive ) ---------------------------------------------//

        //! Erase nth algorithm ( case insensitive )
        /*!
            Remove the Nth occurrence of the substring in the input.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator. 
            Searching is case insensitive.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for.
            \param Nth An index of the match to be replaced. The index is 0-based.
                For negative N, matches are counted from the end of string.
            \param Loc A locale used for case insensitive comparison
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT ierase_nth_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            int Nth,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::nth_finder(Search, Nth, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase nth algorithm
        /*!
            \overload
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT ierase_nth_copy( 
            const SequenceT& Input,
            const RangeT& Search,
            int Nth,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_copy( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth, is_iequal(Loc)),
                empty_formatter(Input) );
        }

        //! Erase nth algorithm
        /*!
            Remove the Nth occurrence of the substring in the input.
            The input sequence is modified in-place. Searching is case insensitive.

            \param Input An input string
            \param Search A substring to be searched for. 
            \param Nth An index of the match to be replaced. The index is 0-based.
                For negative N, matches are counted from the end of string.
            \param Loc A locale used for case insensitive comparison
        */
        template<typename SequenceT, typename RangeT>
        inline void ierase_nth( 
            SequenceT& Input,
            const RangeT& Search,
            int Nth,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::nth_finder(Search, Nth, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }


//  erase_all  --------------------------------------------------------//

        //! Erase all algorithm
        /*!
            Remove all the occurrences of the string from the input. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
                        

            \param Output An output iterator to which the result will be copied
            \param Input An input sequence
            \param Search A substring to be searched for. 
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT erase_all_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search )
        {
            return ::boost::algorithm::find_format_all_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase all algorithm
        /*!
            \overload
        */  
        template<typename SequenceT, typename RangeT>
        inline SequenceT erase_all_copy( 
            const SequenceT& Input,
            const RangeT& Search )
        {
            return ::boost::algorithm::find_format_all_copy( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase all algorithm
        /*!
            Remove all the occurrences of the string from the input. 
            The input sequence is modified in-place.

            \param Input An input string
            \param Search A substring to be searched for. 
        */
        template<typename SequenceT, typename RangeT>
        inline void erase_all( 
            SequenceT& Input,
            const RangeT& Search )
        {
            ::boost::algorithm::find_format_all( 
                Input, 
                ::boost::algorithm::first_finder(Search),
                ::boost::algorithm::empty_formatter(Input) );
        }

//  erase_all ( case insensitive ) ------------------------------------//

        //! Erase all algorithm ( case insensitive )
        /*!
            Remove all the occurrences of the string from the input. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator. 
            Searching is case insensitive.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param Search A substring to be searched for
            \param Loc A locale used for case insensitive comparison
            \return An output iterator pointing just after the last inserted character or
                    a modified copy of the input

              \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename Range1T, 
            typename Range2T>
        inline OutputIteratorT ierase_all_copy(
            OutputIteratorT Output,
            const Range1T& Input,
            const Range2T& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_all_copy(
                Output,
                Input,
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase all algorithm ( case insensitive )
        /*!
            \overload
        */
        template<typename SequenceT, typename RangeT>
        inline SequenceT ierase_all_copy( 
            const SequenceT& Input,
            const RangeT& Search,
            const std::locale& Loc=std::locale() )
        {
            return ::boost::algorithm::find_format_all_copy( 
                Input, 
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

        //! Erase all algorithm ( case insensitive )
        /*!
            Remove all the occurrences of the string from the input. 
            The input sequence is modified in-place. Searching is case insensitive.

            \param Input An input string
            \param Search A substring to be searched for. 
            \param Loc A locale used for case insensitive comparison
        */
        template<typename SequenceT, typename RangeT>
        inline void ierase_all( 
            SequenceT& Input,
            const RangeT& Search,
            const std::locale& Loc=std::locale() )
        {
            ::boost::algorithm::find_format_all( 
                Input, 
                ::boost::algorithm::first_finder(Search, is_iequal(Loc)),
                ::boost::algorithm::empty_formatter(Input) );
        }

//  erase_head --------------------------------------------------------------------//

        //! Erase head algorithm
        /*!
            Remove the head from the input. The head is a prefix of a sequence of given size. 
            If the sequence is shorter then required, the whole string is 
            considered to be the head. The result is a modified copy of the input. 
            It is returned as a sequence or copied to the output iterator.
            

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param N Length of the head.
                For N>=0, at most N characters are extracted.
                For N<0, size(Input)-|N| characters are extracted.
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename RangeT>
        inline OutputIteratorT erase_head_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            int N )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        //! Erase head algorithm
        /*!
            \overload
        */
        template<typename SequenceT>
        inline SequenceT erase_head_copy( 
            const SequenceT& Input,
            int N )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        //! Erase head algorithm
        /*!
            Remove the head from the input. The head is a prefix of a sequence of given size. 
            If the sequence is shorter then required, the whole string is 
            considered to be the head. The input sequence is modified in-place.

            \param Input An input string
            \param N Length of the head
                For N>=0, at most N characters are extracted.
                For N<0, size(Input)-|N| characters are extracted.
        */
        template<typename SequenceT>
        inline void erase_head( 
            SequenceT& Input,
            int N )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::head_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

//  erase_tail --------------------------------------------------------------------//

        //! Erase tail algorithm
        /*!
            Remove the tail from the input. The tail is a suffix of a sequence of given size. 
            If the sequence is shorter then required, the whole string is 
            considered to be the tail. 
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input string
            \param N Length of the tail.                 
                For N>=0, at most N characters are extracted.
                For N<0, size(Input)-|N| characters are extracted.
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input
            
             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<
            typename OutputIteratorT,
            typename RangeT>
        inline OutputIteratorT erase_tail_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            int N )
        {
            return ::boost::algorithm::find_format_copy(
                Output,
                Input,
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        //! Erase tail algorithm
        /*!
            \overload
        */
        template<typename SequenceT>
        inline SequenceT erase_tail_copy( 
            const SequenceT& Input,
            int N )
        {
            return ::boost::algorithm::find_format_copy( 
                Input,
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

        //! Erase tail algorithm
        /*!
            Remove the tail from the input. The tail is a suffix of a sequence of given size. 
            If the sequence is shorter then required, the whole string is
            considered to be the tail. The input sequence is modified in-place.

            \param Input An input string
            \param N Length of the tail
                For N>=0, at most N characters are extracted.
                For N<0, size(Input)-|N| characters are extracted.
        */
        template<typename SequenceT>
        inline void erase_tail( 
            SequenceT& Input,
            int N )
        {
            ::boost::algorithm::find_format( 
                Input, 
                ::boost::algorithm::tail_finder(N),
                ::boost::algorithm::empty_formatter( Input ) );
        }

    } // namespace algorithm

    // pull names into the boost namespace
    using algorithm::erase_range_copy;
    using algorithm::erase_range;
    using algorithm::erase_first_copy;
    using algorithm::erase_first;
    using algorithm::ierase_first_copy;
    using algorithm::ierase_first;
    using algorithm::erase_last_copy;
    using algorithm::erase_last;
    using algorithm::ierase_last_copy;
    using algorithm::ierase_last;
    using algorithm::erase_nth_copy;
    using algorithm::erase_nth;
    using algorithm::ierase_nth_copy;
    using algorithm::ierase_nth;
    using algorithm::erase_all_copy;
    using algorithm::erase_all;
    using algorithm::ierase_all_copy;
    using algorithm::ierase_all;
    using algorithm::erase_head_copy;
    using algorithm::erase_head;
    using algorithm::erase_tail_copy;
    using algorithm::erase_tail;

} // namespace boost


#endif  // BOOST_ERASE_HPP

/* erase.hpp
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
*/