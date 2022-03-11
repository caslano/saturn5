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