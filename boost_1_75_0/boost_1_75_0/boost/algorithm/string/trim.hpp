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
UXMfDoWhiK63qWc0AjdmaMpw22y3U+ompA9XmGip8VwyY+ekQOmt6IeqEF/yIoaydxamQ3VRsSoSMLmg2Fqxkv/SO9AGSLHbofIp8MQb/ElSafGmVSc6JNI1su7CtSOM769HbOrV3xo8ZG4H8RLcE5HcEDRh3u18mreSb6W4pA4ZOVI72ZKfVtfHf6wxIRi9Su7+8z06nZKLpx3kIGtNQYTwh4rgDwb6hZ6A95M0l0x7vYGPLSRRXeMxZ86kJbRB9THA6Ki+z305SZSz3a6XwItHmRr/tNzCSRWN6EAPSUA/eQrOdaxDY12oLsjx7S0un5FLxcsaDyNlDG7dj0u+x2sGLiLeEGEqYARO0CgXq5nQzsliIJFk89Suztns0tckssU9bfhHl3kIITu0/jDIBNpytfr5e2m9aFWd6eOiOlc6h2XaSxUO18kd+yybogW0jvmAzm/qMks0YxZtOxaTgrz3SgmudFIcU5x3pCOqXpn29F447nvYFL/91V6vN47hTEs7FV9R14YrNa4VXwdTHWXiC/h/PT+wSOtFV/1ajWfg7W4OawpAR4LauVc9GbysdsZcJfe7V3p1wk4ixS+KXCuuyYD9PU6utmuQW+ebBpdVZGam2z2WwvL+P98hZDvy00U36gtiohV9/7V/7pmoEpxSMtV8iKf8U+2ecY2ihzqoUo4EKPhdNvbf+uHCPd2thKRXyEsv5qfbRAji
*/