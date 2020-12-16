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
yjJ2EN5EM3eruhkO+iiWwXM8rYDJUE0gTSZCXKzGoPauR2/Pp8P3bk5UDmTqGUMz+ahkjyllOqMOgGEkbym62NvMP5a8vePs/mn914dD7ykvY9uVs3+05buXlc+PteWrCt57vnrI9l5VAf7NtvzP7i2f/7Qtf1EF+PNs+T1zyuePseW/M658foYt//oK6m9py28NoldO/1Xy2VcWkVQUMqM3GlW1+6tK6q8VPsioWH8/U24exhVOWntd2ZbTqQ5gjXLUJs5gKu0i7rCr/o1DoWY51TN4jiLDP3DR9BmN8sRVk8yIPh0MfyYKaSAvnd1O1/INRfb4u2zZV/qAqdLzybf1RKXHJI0LWPCRyU8L8jxL+zlWlZJBDkjtpyKIwAVfCSmVsXSDS9Yqox/9RZj1V5lZnwXGmySpyrjT8pcETfh+0wndZm2MyiQ+na3yLYzfQDCoTeHu0hjfsjBOIIydGWPJAEihnWyCSPKz6ipwP6G2wrSzKeFKFhoxsu4aWZGFbCIh+zqPkcXy/rdYIagi3PNncdIXdXai+v7G/ZaIbAItukR9V8tYZVrLuI0AqRlDwQpi13YGkuFtgdXaNj3PdmdOPoxyg445Q9RCsVjCAnTHWS9C79M9YqbcIy59nu4Rz0KQUqxKF/DU0OFKZYz9bBy1Z4WoL5kepkr+lvcNqN6vz9WKWu/ke8mnrIMHceRhumB8eq1UqY2knJYh4mdUeCFMYnhL5Hc2v1FvSIXLhZM7hRnOuS5MwdVsQwPn4T9X5ebwNGpj7NrLTavko5h8kPh693ACAWwjZwh+d6wqBNtgPjN9QzdQMhm22EcPUfNs2lBDz8Kjw2n8QT99Cb9/rzA33w0l4Zsvd4YzirQeu1oxhFfJZOWvpsl6mj0Y9cqlybKv0K+f4hVKyMkbXewPILNlNxZvqQccvKVY4fwRwdwemDlqcnPaVSWPl9lLTlBc2UHXg9+h20PXrb75xgFJexaTZjJwZMnd51q5NVxrjndg8Fn0zoXxW8P3v/vN8bvgUD174KzcN5gmJRJXVSrEjOW5OVWwqoZ4+dEanHkquTgYSfkirGGSJuHDWOScs8eVJBPCHXMlCX9ZSEVcdWNcdfvEqSnjLE4hFDxr9JM8D9TIMyETaYPp/aVgJNCqfsvNPvYIWH1MRA6Ln1jBvGUtFmIEvCTy4mZIBAG6GIxFEJ10ej3xujKAJEus/OrdzewU3NqN18truCyC1s/Q8irA8qqjvpzHtOBe1lbMcpJuxFDtGMZD9cI7YBq3w80mlF6kp1I6LtfpRqoo/A8jhf93l5HkCzh4Aw/VG/i1xawxIEp8I0Us9OFkc1NPMnhTn3xMeOxXcsw7BR8suX8Wyj2WKfd4WbO3qUukxRu4VbvIfWE2DeERJOM3Lu3v3MHeTBbdh+TuF8VgQdSJbX0iiLFwuBaex3qHtUcAdzD+2b834CeavKpIpecO/yQEa1rAbyoZhBsbA3ah5gKCsB8MrVa9bnGPfoFABhYQy7/9Q3j5xHEd+mnmIqwt/pRlpS7EXV2tHU7DsstyogI9CFZWsa5/av01gr4YSTKj/cmbg3dUtMcY4FQtn5bsZ6L0g4y+5ExS63Il5x59VVy8TC9dDmVgLQUtXmr6p1qofBNWg/pwDhjuUTQKNATzTHNn2ziIs7930H1WsY6hQyH4Ho1fG+x7C/Xt+AROYN/4NBYaDtu5hJrvqQ4te+VJQ/v0KjPMVSarTwxXeLdhF/Bug+I27zbaLiR9/y+/PJ3Bn53/ZFagy1IxwmZ5rdabSyZ/qE/JvmjF+yLblNeeOzv01m5AQCmnHctoX5ET8hIUnqMLt4sywz3xtpqsDt5eUXGOtLyf30Y=
*/