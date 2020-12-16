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
OAIMCQnK15iAkpHkSi1syimx6JC6g2WT5ca+MN50yV8RNw31jJyeAVWAEDhY3/0qQqyQCPHn7wkh7gVCHBDJe3HJcA/atbpzzNbSldJd5UGUEFl/ZVFDM5qZhzQC8kcUAUTvIe/gHoDoCRDiXRaba61rtBUaLr6p0VcIxHbldp77DF23hrTDFZzWMSevit1jkbRPJkFy9158mNbwIpkgJtHPl7GKHHJ7DbpD0DiQhsmBuFrWwjPmud5BvyEH/dZxbdDHRRr1uIhmz+064YBBjVn86j0aLMQwkDbRxla+i5Y9F6f/KsXy4QxqsBl+uVp4MSlmr3hDFuiKAnTLkS4zTZx5VanMbMqhSAYYLaua2fBpspZ/ZsZ/MdvwI8wWU4bfcbaYtbCHJgZlWUa39/gBNo4fHxE/LKO1nzIV/9xRbEuaKT6p4MnlrnK/0VlqcbDaX4qfw6cVO2WKWkxh0O5/9bosP8cYpPu3vikzRxkvpvv5fdSu51+vr8T7ciW6fKetxCfiD7uwEqcNft10oJsO5SMO6IaRSWU9Da83JWXyRSEzXtXaCYZNzELNBgNj+zK1ubfV98X/Qc0V8cLfQM3RdSsEu97Z7lG1fMvF2OgeFAlBIhs3DM1IZDC7GzoKyzvXtHM3ZDmipgULEoXl4TUWd38SJArLwyBLIAaVLWP73HZ6q2Wy1UF6q9+L93C2qWnBvST4kQK4SxfyW771sMTOfP6Ht2rhJrVH0l9D1CapbT7bOVSR370a/TAN2wwUJE/8P/rhpfyp758KqV9VroAbAi3rdYg6MtdFq3cz+8kvIoQslgu59Bgt5FLh+YB2Tla4Fp5KmBtNpfNQumab1bKqscM9CIRhdLqHmVSasBpBD/wlrPyzhJi1fVhfGMeqQm4kn7DqSVTuH4V/Bpmz8S2GKq+3ogKlRxOE9fQtFum2mHIq11CmNNLzLAS+HB2Is5ZQB8LRJPpyhdaPMMsqh4n7Un4ggQONxGwsMS89SapEy/3k/GhVjH2gUMSvVvhFExKvxVyYL2MNzK8+DCOtnJImWnSa9J8G4fjoPELqjpZ8pW6QGJRq4JIuJW43xiCNZZJZv0cJ06RSuSacmUByfSbwdq2XCXTfoa5k5rgKugEvrGA2MM1Gc3PpbCBj79zk+lzAVuvlAmu2e5vlblMjMeKtbzwemSjWHJVfL/3+LFh8rJGls2g6Uw9q8kbbXrr6PBcP9h6mLTYdenPExIoTR/9B0nVcfkf0/r6jcsffTuRQhH8QCQuFFohvt7Fi+ytVsZ0OXTHL5hxguHcDVzfonDtSzUlU8z45F+lHaS4K2aj1rxIAxRR5m+NXdOsd6TpSeNooq031qWbUqx0TC2S1W1BF+bhgYVKvMCjgUY57OVOW335EK39UDJblu6r9HGBTzlhW5ScNlHr+r8wxtdCRU042/6BvNv1b/5j1Xu2/r+KfThT5E5aepINY/lD8pu2uO//u5tOfB2V/rHp/joi3t3J/nkOOlaVYGnESFaZK1RS5QaZj/mIpeRElvw3Scw+J5IA4+M3o6QGJ7gd2zm/m7j2/5ip3b4mdCUiMcM8n5BzAh935jJy958mbg7tysIyyd/tk7144TL1bxmeD1tw7jgEjlfWqzg9rylsUbT+v1/Kl0CzEewHxbMVWdQsgsIUYx+KcJmJXsrJTM83rj2wOqcY45CM1vroFm+IYqOSdHOREavdn4wCXUZXfTu/ml7KbP3zD3WTyvYsqtmHTfrhkK7uk1fKcat5SFxA1KcJaekTeZFSgooMUkifQKz7SIv5Di/8U9f4F/2BfmMrvnx/QeCXMJXOUPU5le+GpuDlpcA4ugNNlbycF9rYWwnMuuT5ZPlc=
*/