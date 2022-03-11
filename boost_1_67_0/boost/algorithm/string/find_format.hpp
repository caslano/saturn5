//  Boost string_algo library find_format.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_FORMAT_HPP
#define BOOST_STRING_FIND_FORMAT_HPP

#include <deque>
#include <boost/detail/iterator.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/as_literal.hpp>

#include <boost/algorithm/string/concept.hpp>
#include <boost/algorithm/string/detail/find_format.hpp>
#include <boost/algorithm/string/detail/find_format_all.hpp>

/*! \file
    Defines generic replace algorithms. Each algorithm replaces
    part(s) of the input. The part to be replaced is looked up using a Finder object.
    Result of finding is then used by a Formatter object to generate the replacement.
*/

namespace boost {
    namespace algorithm {

// generic replace  -----------------------------------------------------------------//

        //! Generic replace algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.
    
            \param Output An output iterator to which the result will be copied
            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template< 
            typename OutputIteratorT,
            typename RangeT,
            typename FinderT,
            typename FormatterT>
        inline OutputIteratorT find_format_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            return detail::find_format_copy_impl(
                Output,
                lit_input,
                Formatter,
                Finder( ::boost::begin(lit_input), ::boost::end(lit_input) ) );
        }

        //! Generic replace algorithm
        /*!
            \overload
        */
        template< 
            typename SequenceT, 
            typename FinderT,
            typename FormatterT>
        inline SequenceT find_format_copy(
            const SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            return detail::find_format_copy_impl(
                Input,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));
        }

        //! Generic replace algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input. The input is modified in-place.

            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
        */
        template<
            typename SequenceT,
            typename FinderT,
            typename FormatterT>
        inline void find_format( 
            SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter)
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT(( 
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            detail::find_format_impl(
                Input,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));
        }


//  find_format_all generic ----------------------------------------------------------------//

        //! Generic replace all algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input. Repeat this for all matching
            substrings.
            The result is a modified copy of the input. It is returned as a sequence 
            or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
            \return An output iterator pointing just after the last inserted character or
                a modified copy of the input

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template< 
            typename OutputIteratorT,
            typename RangeT,
            typename FinderT,
            typename FormatterT>
        inline OutputIteratorT find_format_all_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            FinderT Finder,
            FormatterT Formatter)
        {
            // Concept check
            BOOST_CONCEPT_ASSERT(( 
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));
            BOOST_CONCEPT_ASSERT(( 
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type>
                ));

            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            return detail::find_format_all_copy_impl(
                Output,
                lit_input,
                Finder,
                Formatter,
                Finder(::boost::begin(lit_input), ::boost::end(lit_input)));
        }

        //! Generic replace all algorithm
        /*!
            \overload
        */
        template< 
            typename SequenceT, 
            typename FinderT,
            typename FormatterT >
        inline SequenceT find_format_all_copy(
            const SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            return detail::find_format_all_copy_impl(
                Input,
                Finder,
                Formatter,
                Finder( ::boost::begin(Input), ::boost::end(Input) ) );
        }

        //! Generic replace all algorithm
        /*!
            Use the Finder to search for a substring. Use the Formatter to format
            this substring and replace it in the input. Repeat this for all matching
            substrings.The input is modified in-place.

            \param Input An input sequence
            \param Finder A Finder object used to search for a match to be replaced
            \param Formatter A Formatter object used to format a match
        */
        template<
            typename SequenceT,
            typename FinderT,
            typename FormatterT >
        inline void find_format_all( 
            SequenceT& Input,
            FinderT Finder,
            FormatterT Formatter )
        {
            // Concept check
            BOOST_CONCEPT_ASSERT((
                FinderConcept<
                    FinderT,
                    BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));
            BOOST_CONCEPT_ASSERT((
                FormatterConcept<
                    FormatterT,
                    FinderT,BOOST_STRING_TYPENAME range_const_iterator<SequenceT>::type>
                ));

            detail::find_format_all_impl(
                Input,
                Finder,
                Formatter,
                Finder(::boost::begin(Input), ::boost::end(Input)));

        }

    } // namespace algorithm

    // pull the names to the boost namespace
    using algorithm::find_format_copy;
    using algorithm::find_format;
    using algorithm::find_format_all_copy;
    using algorithm::find_format_all;

} // namespace boost


#endif  // BOOST_STRING_FIND_FORMAT_HPP

/* find_format.hpp
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
*/