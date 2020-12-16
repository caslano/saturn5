//  Boost string_algo library trim.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_TRIM_HPP
#define BOOST_STRING_TRIM_HPP

#include <boost/algorithm/string/config.hpp>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/as_literal.hpp>
#include <boost/range/iterator_range_core.hpp>

#include <boost/algorithm/string/detail/trim.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <locale>

/*! \file
    Defines trim algorithms.
    Trim algorithms are used to remove trailing and leading spaces from a 
    sequence (string). Space is recognized using given locales.

    Parametric (\c _if) variants use a predicate (functor) to select which characters
    are to be trimmed.. 
    Functions take a selection predicate as a parameter, which is used to determine 
    whether a character is a space. Common predicates are provided in classification.hpp header.

*/

namespace boost {
    namespace algorithm {

    //  left trim  -----------------------------------------------//


        //! Left trim - parametric
        /*!
            Remove all leading spaces from the input. 
            The supplied predicate is used to determine which characters are considered spaces.
            The result is a trimmed copy of the input. It is returned as a sequence 
            or copied to the output iterator

            \param Output An output iterator to which the result will be copied
            \param Input An input range
            \param IsSpace A unary predicate identifying spaces
            \return 
                An output iterator pointing just after the last inserted character or
                a copy of the input

               \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<typename OutputIteratorT, typename RangeT, typename PredicateT>
        inline OutputIteratorT trim_left_copy_if( 
            OutputIteratorT Output,
            const RangeT& Input,
            PredicateT IsSpace)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_range(::boost::as_literal(Input));

            std::copy( 
                ::boost::algorithm::detail::trim_begin( 
                    ::boost::begin(lit_range), 
                    ::boost::end(lit_range), 
                    IsSpace ),
                ::boost::end(lit_range),
                Output);

            return Output;
        }

        //! Left trim - parametric
        /*!
            \overload
        */
        template<typename SequenceT, typename PredicateT>
        inline SequenceT trim_left_copy_if(const SequenceT& Input, PredicateT IsSpace)
        {
            return SequenceT( 
                ::boost::algorithm::detail::trim_begin( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    IsSpace ),
                ::boost::end(Input));
        }

        //! Left trim - parametric
        /*!
            Remove all leading spaces from the input. 
            The result is a trimmed copy of the input.

            \param Input An input sequence
            \param Loc a locale used for 'space' classification
            \return A trimmed copy of the input

            \note This function provides the strong exception-safety guarantee
        */
        template<typename SequenceT>
        inline SequenceT trim_left_copy(const SequenceT& Input, const std::locale& Loc=std::locale())
        {
            return            
                ::boost::algorithm::trim_left_copy_if(
                    Input, 
                    is_space(Loc));
        }

        //! Left trim
        /*!
            Remove all leading spaces from the input. The supplied predicate is 
            used to determine which characters are considered spaces.
            The input sequence is modified in-place.

            \param Input An input sequence
            \param IsSpace A unary predicate identifying spaces
        */
        template<typename SequenceT, typename PredicateT>
        inline void trim_left_if(SequenceT& Input, PredicateT IsSpace)
        {
            Input.erase( 
                ::boost::begin(Input),
                ::boost::algorithm::detail::trim_begin( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    IsSpace));
        }

        //! Left trim
        /*!
            Remove all leading spaces from the input.
            The Input sequence is modified in-place.

            \param Input An input sequence
            \param Loc A locale used for 'space' classification
        */
        template<typename SequenceT>
        inline void trim_left(SequenceT& Input, const std::locale& Loc=std::locale())
        {
            ::boost::algorithm::trim_left_if( 
                Input, 
                is_space(Loc));
        }

    //  right trim  -----------------------------------------------//

        //! Right trim - parametric
        /*!
            Remove all trailing spaces from the input.             
            The supplied predicate is used to determine which characters are considered spaces.
            The result is a trimmed copy of the input. It is returned as a sequence 
            or copied to the output iterator

            \param Output An output iterator to which the result will be copied
            \param Input An input range
            \param IsSpace A unary predicate identifying spaces
            \return 
                An output iterator pointing just after the last inserted character or
                a copy of the input

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<typename OutputIteratorT, typename RangeT, typename PredicateT>
        inline OutputIteratorT trim_right_copy_if( 
            OutputIteratorT Output,
            const RangeT& Input,
            PredicateT IsSpace )
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_range(::boost::as_literal(Input));
         
            std::copy( 
                ::boost::begin(lit_range),
                ::boost::algorithm::detail::trim_end( 
                    ::boost::begin(lit_range), 
                    ::boost::end(lit_range), 
                    IsSpace ),
                Output );

            return Output;
        }

        //! Right trim - parametric
        /*!
            \overload
         */
        template<typename SequenceT, typename PredicateT>
        inline SequenceT trim_right_copy_if(const SequenceT& Input, PredicateT IsSpace)
        {
            return SequenceT( 
                ::boost::begin(Input),
                ::boost::algorithm::detail::trim_end( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    IsSpace)
                );
        }

        //! Right trim
        /*!
            Remove all trailing spaces from the input. 
            The result is a trimmed copy of the input

            \param Input An input sequence
            \param Loc A locale used for 'space' classification
            \return A trimmed copy of the input

            \note This function provides the strong exception-safety guarantee
        */
        template<typename SequenceT>
        inline SequenceT trim_right_copy(const SequenceT& Input, const std::locale& Loc=std::locale())
        {
            return 
                ::boost::algorithm::trim_right_copy_if( 
                    Input, 
                    is_space(Loc));
        }

            
        //! Right trim - parametric
        /*!
            Remove all trailing spaces from the input.
            The supplied predicate is used to determine which characters are considered spaces.
            The input sequence is modified in-place.

            \param Input An input sequence
            \param IsSpace A unary predicate identifying spaces
        */
        template<typename SequenceT, typename PredicateT>
        inline void trim_right_if(SequenceT& Input, PredicateT IsSpace)
        {
            Input.erase(
                ::boost::algorithm::detail::trim_end( 
                    ::boost::begin(Input), 
                    ::boost::end(Input), 
                    IsSpace ),
                ::boost::end(Input)
                );
        }


        //! Right trim
        /*!
            Remove all trailing spaces from the input. 
            The input sequence is modified in-place.

            \param Input An input sequence
            \param Loc A locale used for 'space' classification
        */
        template<typename SequenceT>
        inline void trim_right(SequenceT& Input, const std::locale& Loc=std::locale())
        {
            ::boost::algorithm::trim_right_if(
                Input, 
                is_space(Loc) );
        }

    //  both side trim  -----------------------------------------------//

        //! Trim - parametric
        /*!
            Remove all trailing and leading spaces from the input. 
            The supplied predicate is used to determine which characters are considered spaces.
            The result is a trimmed copy of the input. It is returned as a sequence 
            or copied to the output iterator

            \param Output An output iterator to which the result will be copied
            \param Input An input range
            \param IsSpace A unary predicate identifying spaces
            \return 
                An output iterator pointing just after the last inserted character or
                a copy of the input

             \note The second variant of this function provides the strong exception-safety guarantee
        */
        template<typename OutputIteratorT, typename RangeT, typename PredicateT>
        inline OutputIteratorT trim_copy_if( 
            OutputIteratorT Output,
            const RangeT& Input,
            PredicateT IsSpace)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_range(::boost::as_literal(Input));

            BOOST_STRING_TYPENAME 
                range_const_iterator<RangeT>::type TrimEnd=
                ::boost::algorithm::detail::trim_end( 
                    ::boost::begin(lit_range), 
                    ::boost::end(lit_range), 
                    IsSpace);

            std::copy( 
                detail::trim_begin( 
                    ::boost::begin(lit_range), TrimEnd, IsSpace),
                TrimEnd,
                Output
                );

            return Output;
        }

        //! Trim - parametric
        /*!
            \overload
         */
        template<typename SequenceT, typename PredicateT>
        inline SequenceT trim_copy_if(const SequenceT& Input, PredicateT IsSpace)
        {
            BOOST_STRING_TYPENAME 
                range_const_iterator<SequenceT>::type TrimEnd=
                    ::boost::algorithm::detail::trim_end( 
                        ::boost::begin(Input), 
                        ::boost::end(Input), 
                        IsSpace);

            return SequenceT( 
                detail::trim_begin( 
                    ::boost::begin(Input), 
                    TrimEnd, 
                    IsSpace),
                TrimEnd
                );
        }

        //! Trim
        /*!
            Remove all leading and trailing spaces from the input. 
            The result is a trimmed copy of the input

            \param Input An input sequence
            \param Loc A locale used for 'space' classification
            \return A trimmed copy of the input

            \note This function provides the strong exception-safety guarantee
        */
        template<typename SequenceT>
        inline SequenceT trim_copy( const SequenceT& Input, const std::locale& Loc=std::locale() )
        {
            return
                ::boost::algorithm::trim_copy_if(
                    Input, 
                    is_space(Loc) );
        }
     
        //! Trim
        /*!
            Remove all leading and trailing spaces from the input. 
            The supplied predicate is used to determine which characters are considered spaces.
            The input sequence is modified in-place.

            \param Input An input sequence
            \param IsSpace A unary predicate identifying spaces
        */
        template<typename SequenceT, typename PredicateT>
        inline void trim_if(SequenceT& Input, PredicateT IsSpace)
        {
            ::boost::algorithm::trim_right_if( Input, IsSpace );
            ::boost::algorithm::trim_left_if( Input, IsSpace );
        }

        //! Trim
        /*!
            Remove all leading and trailing spaces from the input. 
            The input sequence is modified in-place.

            \param Input An input sequence
            \param Loc A locale used for 'space' classification
        */
        template<typename SequenceT>
        inline void trim(SequenceT& Input, const std::locale& Loc=std::locale())
        {
            ::boost::algorithm::trim_if(
                Input, 
                is_space( Loc ) );
        }

    } // namespace algorithm 

    // pull names to the boost namespace
    using algorithm::trim_left;
    using algorithm::trim_left_if;
    using algorithm::trim_left_copy;
    using algorithm::trim_left_copy_if;
    using algorithm::trim_right;
    using algorithm::trim_right_if;
    using algorithm::trim_right_copy;
    using algorithm::trim_right_copy_if;
    using algorithm::trim;
    using algorithm::trim_if;
    using algorithm::trim_copy;
    using algorithm::trim_copy_if;

} // namespace boost

#endif  // BOOST_STRING_TRIM_HPP

/* trim.hpp
UfydTElE+bc4v090xjjl36KxNFMcW4SEGbA1xvaAFDjAfW0H+uPqrO2NHnKRuv+8jutbdGHsrhNdHrMqOuUSkdVk2eR1FYuEa4zpubTQNJkqe2IIIXD5PN3lozOFZOEagJdB1A5iH/FjOo7NBjTUXlTq9Btrseat3Mut12n66/Cu52XJtdphWOnkoHR4QpAlUD0e78FBmt+7BtM1DqqRoAxdWy1zNvJawUGZyA3vvLoXr83hsCztbYroXUeI2P/Fgdk+7W28VJbm+rS1su4avYu35DO4h5V7bT5/5/i09UgEBlSEUiFDHJyH1UJE9i7HclGtEJWvrcLz+lIPDKxIBIAaNwPcutbMK0hErZODespCGIjgz168FMavh+B/dAu/Ueunl2Kft4bLUAu4lVOhT6vnIhTALoGU/MbinHbUfQFDD/V5F8nSVbxaku/t1ygRv7eRiJI0DvNpSymqtijHRFVncODhPm0xld9YlmPSkM2BR/i9TRy7mTCrJfqRPm0lVZ62HJ/jSvvA4VfOarSPNMZRuvcTsqlryxFotWNf3bsL6Wif5qyODijloG/o2m5ZgYw3ZHHI0RpwPMZOBNHmKA4rkeVIHzivVPdu5bBjdO82VBAUNO1jPHEmSdvGfFZqtDFn2LxyrLBEfTZ/9dO1diTn/QhBDYJwnO7dTGyobfGhSS5C+1Ho8bpmMksN8BnrqU68bwMcrxPOKtO1Fm6WtyiwXhI6AQzFVbpGGCiPQ0/0IxRFehuB1FPO5NCTvG8RV3nXITReJ/FP1sFqRMhaH9pJ8d8pFObBJgxhnz4c6IV3DirFcoQGwwsGgePoXJZPW0X7PZ7kTnwXP1EEVBoYR5jxHIdGg+y1LhxVIVK9tVgIBnMRCE5j6pGV8NYUJwAUqvmMRbJejEQogJdAFRudk2kxWiZ9Zfm0OovPfFiV7k+B2T7vYq6V15jhyymsh097nVkezJFFATl+bXEwXJNL3QQL2kI72JBcp4L9iO3Af+A5sBR2XEAioH2zwX1IAJC15GLCW4Ou6tPW0QFklNiF1tBLauF9JOO+6Td9R6tFr6zJ0jXhDIN8m1C9lNQgomD4Sgt8WjVDgEKFQvfCmhe+GUHXFsC/CcFJOFHXIbqwOGYlcDOLER+yMBApjozy/EwikCiWSqXBp60WgnVIKiIT2SWT6ixFEoqObFC8D50NqVRmJVEpxchNItMNMoVEybyeyENFgDCiHgNOH6E2mUxJxpVMZ25XOoHi6STUnUqowItSSc3uQqozidScrjVan1yZQnMqlXXJNOal0igFrqMUanei8XNBYQ5T93DrmiuknqqRIfKNE+VGDeJitTOHCGQcbqtGEIBQEIbM84jGnLhKQ9EXJ3BNpkUe5VFt5VHABNYQRm2W0AcMpk9heBSB0kvzU4mUtgZQKg+RU8irs8kT0phKm7xkhhQa3aAxlT6n0EfjHVMXRw3sS2OtXYUu1cgp1ehSNEob54HMJBrBzEk0ZnahkTuV0EeZI+uMfWisS6rB3G5rsMimL6sLfeB4Jg+5IuE4UgV3eKmlM958+YjbVBUJiYoHkTJzGKIIEjWSEIm8c0EesVuJ6jQKpS61HiFcSoQrVUZgJQgg7iXAIrCSQHYWLovO/G7otJtaunRXGlFOm8Ts7km0mZGlY/dELiAis/dPZO5nEanV2jRmdFuPDTaJmd2TWP85BEpjI/p+KAS3fVZr2wKHmS0XbCpkMoXnf3rhH6SOmoRdURHgUyGUoURnp1xkhnSDU4VSoEsaiiGlR2SAU0Eriycb7AGN0uUhfHJqhFA7em0nhZldKUQ7JxHosgkEtp2+M4nAvK4EghVt+nK70lefRF2GRZ2ApLM=
*/