//  Boost string_algo library formatter.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FORMATTER_HPP
#define BOOST_STRING_FORMATTER_HPP

#include <boost/detail/iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/range/as_literal.hpp>

#include <boost/algorithm/string/detail/formatter.hpp>

/*! \file
    Defines Formatter generators. Formatter is a functor which formats
    a string according to given parameters. A Formatter works
    in conjunction with a Finder. A Finder can provide additional information
    for a specific Formatter. An example of such a cooperation is regex_finder
    and regex_formatter.

    Formatters are used as pluggable components for replace facilities. 
    This header contains generator functions for the Formatters provided in this library.
*/

namespace boost {
    namespace algorithm {

// generic formatters  ---------------------------------------------------------------//

        //! Constant formatter
        /*!
            Constructs a \c const_formatter. Const formatter always returns
            the same value, regardless of the parameter.

            \param Format A predefined value used as a result for formatting
            \return An instance of the \c const_formatter object.
        */
        template<typename RangeT>
        inline detail::const_formatF<
            iterator_range<
                BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> >
        const_formatter(const RangeT& Format)
        {
            return detail::const_formatF<
                iterator_range<
                    BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> >(::boost::as_literal(Format));
        }

        //! Identity formatter
        /*!
            Constructs an \c identity_formatter. Identity formatter always returns
            the parameter.

            \return An instance of the \c identity_formatter object.
        */
        template<typename RangeT>
        inline detail::identity_formatF<
            iterator_range<
                BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> >
        identity_formatter()
        {
            return detail::identity_formatF<
                iterator_range<
                    BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> >();
        }

        //! Empty formatter
        /*!
            Constructs an \c empty_formatter. Empty formatter always returns an empty
            sequence. 

            \param Input container used to select a correct value_type for the
                         resulting empty_container<>.
            \return An instance of the \c empty_formatter object.
        */
        template<typename RangeT>
        inline detail::empty_formatF< 
            BOOST_STRING_TYPENAME range_value<RangeT>::type>
        empty_formatter(const RangeT&)
        {
            return detail::empty_formatF<
                BOOST_STRING_TYPENAME range_value<RangeT>::type>();
        }

        //! Empty formatter
        /*!
            Constructs a \c dissect_formatter. Dissect formatter uses a specified finder
            to extract a portion of the formatted sequence. The first finder's match is returned 
            as a result

            \param Finder a finder used to select a portion of the formatted sequence
            \return An instance of the \c dissect_formatter object.
        */
        template<typename FinderT>
        inline detail::dissect_formatF< FinderT >
        dissect_formatter(const FinderT& Finder)
        {
            return detail::dissect_formatF<FinderT>(Finder);
        }


    } // namespace algorithm

    // pull the names to the boost namespace
    using algorithm::const_formatter;
    using algorithm::identity_formatter;
    using algorithm::empty_formatter;
    using algorithm::dissect_formatter;

} // namespace boost


#endif  // BOOST_FORMATTER_HPP

/* formatter.hpp
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
*/