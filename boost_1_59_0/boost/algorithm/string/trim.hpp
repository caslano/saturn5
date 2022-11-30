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
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
*/