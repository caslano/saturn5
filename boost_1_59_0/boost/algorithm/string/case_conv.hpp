//  Boost string_algo library case_conv.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CASE_CONV_HPP
#define BOOST_STRING_CASE_CONV_HPP

#include <boost/algorithm/string/config.hpp>
#include <algorithm>
#include <locale>
#include <boost/iterator/transform_iterator.hpp>

#include <boost/range/as_literal.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

#include <boost/algorithm/string/detail/case_conv.hpp>

/*! \file
    Defines sequence case-conversion algorithms.
    Algorithms convert each element in the input sequence to the
    desired case using provided locales.
*/

namespace boost {
    namespace algorithm {

//  to_lower  -----------------------------------------------//

        //! Convert to lower case
        /*!
            Each element of the input sequence is converted to lower
            case. The result is a copy of the input converted to lower case.
            It is returned as a sequence or copied to the output iterator.

            \param Output An output iterator to which the result will be copied
            \param Input An input range
            \param Loc A locale used for conversion
            \return 
                An output iterator pointing just after the last inserted character or
                a copy of the input

            \note The second variant of this function provides the strong exception-safety guarantee
                
        */
        template<typename OutputIteratorT, typename RangeT>
        inline OutputIteratorT 
        to_lower_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::detail::transform_range_copy( 
               Output,
               ::boost::as_literal(Input),
               ::boost::algorithm::detail::to_lowerF<
                    typename range_value<RangeT>::type >(Loc));
        }

        //! Convert to lower case
        /*!
            \overload
        */
        template<typename SequenceT>
        inline SequenceT to_lower_copy( 
            const SequenceT& Input, 
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::detail::transform_range_copy<SequenceT>(
                Input,
                ::boost::algorithm::detail::to_lowerF<
                    typename range_value<SequenceT>::type >(Loc));
        }

        //! Convert to lower case
        /*!
            Each element of the input sequence is converted to lower
            case. The input sequence is modified in-place.

            \param Input A range
            \param Loc a locale used for conversion
        */
        template<typename WritableRangeT>
        inline void to_lower( 
            WritableRangeT& Input, 
            const std::locale& Loc=std::locale())
        {
            ::boost::algorithm::detail::transform_range(
                ::boost::as_literal(Input),
                ::boost::algorithm::detail::to_lowerF<
                    typename range_value<WritableRangeT>::type >(Loc));
        }
        
//  to_upper  -----------------------------------------------//

        //! Convert to upper case
        /*!
            Each element of the input sequence is converted to upper
            case. The result is a copy of the input converted to upper case.
            It is returned as a sequence or copied to the output iterator

            \param Output An output iterator to which the result will be copied
            \param Input An input range
            \param Loc A locale used for conversion
            \return 
                An output iterator pointing just after the last inserted character or
                a copy of the input

            \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<typename OutputIteratorT, typename RangeT>
        inline OutputIteratorT 
        to_upper_copy(
            OutputIteratorT Output,
            const RangeT& Input,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::detail::transform_range_copy( 
               Output,
               ::boost::as_literal(Input),
               ::boost::algorithm::detail::to_upperF<
                    typename range_value<RangeT>::type >(Loc));
        }

        //! Convert to upper case
        /*!
            \overload
        */
        template<typename SequenceT>
        inline SequenceT to_upper_copy( 
            const SequenceT& Input, 
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::detail::transform_range_copy<SequenceT>(
                Input,
                ::boost::algorithm::detail::to_upperF<
                    typename range_value<SequenceT>::type >(Loc));
        }

        //! Convert to upper case
        /*!
            Each element of the input sequence is converted to upper
            case. The input sequence is modified in-place.

            \param Input An input range
            \param Loc a locale used for conversion
        */
        template<typename WritableRangeT>
        inline void to_upper( 
            WritableRangeT& Input, 
            const std::locale& Loc=std::locale())
        {
            ::boost::algorithm::detail::transform_range(
                ::boost::as_literal(Input),
                ::boost::algorithm::detail::to_upperF<
                    typename range_value<WritableRangeT>::type >(Loc));
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::to_lower;
    using algorithm::to_lower_copy;
    using algorithm::to_upper;
    using algorithm::to_upper_copy;

} // namespace boost

#endif  // BOOST_STRING_CASE_CONV_HPP

/* case_conv.hpp
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
*/