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