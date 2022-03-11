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