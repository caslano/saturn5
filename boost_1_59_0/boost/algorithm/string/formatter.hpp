//  Boost string_algo library formatter.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FORMATTER_HPP
#define BOOST_STRING_FORMATTER_HPP

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