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
2kzMV9zGN8rdSujh7JC9ylPjmPvwdh6bKv4npc3V1StgOtPpxIJ6KAwt1MM1tbtTaR8ELESTtvLpgcnjxD4J6uOWfATGw3qDWM6F8RJw4zni1YYDIlV1u4yWAo6XNnPpUomFwA731KTz2dKN67idzmcAsxtoTf4+yOQjvR37gkCLgCxJzQT9Z0ebYlsysqXYlpB/o8AKvqb8Avyo7K05tYgjU0UTyMlkVb0rTiAzkASuLfeXRr6bTdMb6v7avuHdf6SG7r64x0Yqt43v4irmIsvmhaeOU7mdPFmH0iT7T3RVg0unaYl8KxjQtyIGtWVvPginkZ+i6T9fERfnu6XQUSWKG+/pYhlQ12VhXQzf6sYHxoCLQnl2EAAk4Axj1IdY9oUkGUICebsFA2A/cVBVASC0f6YiWkHtwCa52ZEZjfdX7WloZf+6yYUDtjQXlC1uWuV7DZAOy2+TWLe0Hs3WLUTa6E7xe29+///j88JuscieE44NMk8N9UyY5wSY4WNiv2etyJS9bN5tHiRsAwdrsZRvmH/lI6Wlv/84Wk47WUjQk0IwLJ7Fh4p6Oo3p/DsxdOl104EyTm+dj4QQ3jjL9DVQV00X4Mf4UMjkQ4FdR4/rQzvenT+3FpP+TVGa4j+pKf5t9F8SyL64JY92mGS/pFcmdpPpm4D7UTI7k8n2JGytsXw19Roj4ckr28ndI5ZtDCH5FsXFHTS3mN7HZnJL1d7LQbLXMgcoVJeud4hiCCT9Q0hYHHeE2rBO2jDOycT4fic7muCg/OQ0MpHJXQf294YkNWi05UMjWV30LbsKvAEZYPKLEpnJ389KopbLtIYW9C/fMHRHzkcbXAsepNHzNRdG8sPeYhFqevxogEy6nQUag9hxmcAnOlRhqlwLhMnde4NIATqM5E/y3f3E9fyVyW5AbtmrPFpiA0E0ES50qoE0LFvd2E2OjXlM5Bn9NtP6BTWB1IdsgP6WJbCDTFgWjSr/IEnuHkqGCFGQSJtHhjh3NVcjcSFTN6a9J3eWM8pXT3W7WATkTIxplunKxyhV6+vlKvOB3L4xPdlNeXo6in9HpKlXbmBHRdwqGtVL60dFUVVPSRlM03lNeZp2i/dFtH1wSwkWEptp/FpSMxPJoJ2vQijNx/q9XBDkPNcj5LwFkfMh0TQwgBvi5lPLpZ7qJNNYH5xTSSOafg+HauLbQ12+PcxtbjEHl6s3Wgj8FxkcOUunN6C6++A1iUOLjWehfZsyF4nPRopVb20JicZPBhSy/KSHnsNoT4b7Obn9OvFz8n/fx6f1x5YxRJG1uHZ8P1NHDBrA4oGXY6iA9LhvEzbaF0Nila5+z3fYuCOUp6v5uDZWHLdi4Isyc2ckRvk6WN42ZspTxUkfR15gLj+uwnJMcckVEikh49KPlVuawUsypx6zZp/zrwRXnoRR7ZXoZct8cL5sYkzBznvio56qI/rcFptxj7AZNwcWiyNJ9jC+n5bWHY1Lg6aI+T6BqllyS2EVzWA0rC+vTFtGsKS/tdWpB6RTF1mdekx17SKwwSuxWrvTt5/wzcuB+7VY67YMZLWg8rkxRN2niMMTRvVxDqNSP3aWscEYsGMo6uPIsKH6T3Ej5ntmrywrnrE/uz6Zfb3a1Qxp3CZThzRWL8aLwL2qac+SZtoAVfq990Nv6KH+GHAW0g0ET5bKkWw9og6w/PWLXHGXyBWnq4euMR8Gcnzqh+v1+xoa2nVLTn9q6vUgpIyRW9veepQoYA/NfGG6heZnrsxPj6k0P0+oQakVPSjz1/DYIYTmKkaTTqfwazt+7585/kV99LAMSzYj/3XqYk7A6t5hMaUvalAarMz7/kQT5wHjOLP8t/XkvVb2fd8=
*/