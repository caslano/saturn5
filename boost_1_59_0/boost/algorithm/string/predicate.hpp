//  Boost string_algo library predicate.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_PREDICATE_HPP
#define BOOST_STRING_PREDICATE_HPP

#include <iterator>
#include <boost/algorithm/string/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/as_literal.hpp>
#include <boost/range/iterator_range_core.hpp>

#include <boost/algorithm/string/compare.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/detail/predicate.hpp>

/*! \file boost/algorithm/string/predicate.hpp
    Defines string-related predicates. 
    The predicates determine whether a substring is contained in the input string 
    under various conditions: a string starts with the substring, ends with the 
    substring, simply contains the substring or if both strings are equal.
    Additionaly the algorithm \c all() checks all elements of a container to satisfy a 
    condition.

    All predicates provide the strong exception guarantee.
*/

namespace boost {
    namespace algorithm {

//  starts_with predicate  -----------------------------------------------//

        //! 'Starts with' predicate
        /*!
            This predicate holds when the test string is a prefix of the Input.
            In other words, if the input starts with the test.
            When the optional predicate is specified, it is used for character-wise
            comparison.

            \param Input An input sequence
            \param Test A test sequence
            \param Comp An element comparison predicate
            \return The result of the test

              \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T, typename PredicateT>
            inline bool starts_with( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range1T>::type> lit_input(::boost::as_literal(Input));
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range2T>::type> lit_test(::boost::as_literal(Test));

            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<Range1T>::type Iterator1T;
            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<Range2T>::type Iterator2T;

            Iterator1T InputEnd=::boost::end(lit_input);
            Iterator2T TestEnd=::boost::end(lit_test);

            Iterator1T it=::boost::begin(lit_input);
            Iterator2T pit=::boost::begin(lit_test);
            for(;
                it!=InputEnd && pit!=TestEnd;
                ++it,++pit)
            {
                if( !(Comp(*it,*pit)) )
                    return false;
            }

            return pit==TestEnd;
        }

        //! 'Starts with' predicate
        /*!
            \overload
        */
        template<typename Range1T, typename Range2T>
        inline bool starts_with( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::boost::algorithm::starts_with(Input, Test, is_equal());
        }

        //! 'Starts with' predicate ( case insensitive )
        /*!
            This predicate holds when the test string is a prefix of the Input.
            In other words, if the input starts with the test.
            Elements are compared case insensitively.

            \param Input An input sequence
            \param Test A test sequence
            \param Loc A locale used for case insensitive comparison
            \return The result of the test

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline bool istarts_with( 
            const Range1T& Input, 
            const Range2T& Test,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::starts_with(Input, Test, is_iequal(Loc));
        }


//  ends_with predicate  -----------------------------------------------//

        //! 'Ends with' predicate
        /*!
            This predicate holds when the test string is a suffix of the Input.
            In other words, if the input ends with the test.
            When the optional predicate is specified, it is used for character-wise
            comparison.


            \param Input An input sequence
            \param Test A test sequence
            \param Comp An element comparison predicate
            \return The result of the test

              \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool ends_with( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range1T>::type> lit_input(::boost::as_literal(Input));
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range2T>::type> lit_test(::boost::as_literal(Test));

            typedef BOOST_STRING_TYPENAME
                range_const_iterator<Range1T>::type Iterator1T;
            typedef BOOST_STRING_TYPENAME
                std::iterator_traits<Iterator1T>::iterator_category category;

            return detail::
                ends_with_iter_select( 
                    ::boost::begin(lit_input), 
                    ::boost::end(lit_input), 
                    ::boost::begin(lit_test), 
                    ::boost::end(lit_test), 
                    Comp,
                    category());
        }


        //! 'Ends with' predicate
        /*!
            \overload
        */
        template<typename Range1T, typename Range2T>
        inline bool ends_with( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::boost::algorithm::ends_with(Input, Test, is_equal());
        }

        //! 'Ends with' predicate ( case insensitive )
        /*!
            This predicate holds when the test container is a suffix of the Input.
            In other words, if the input ends with the test.
            Elements are compared case insensitively.

            \param Input An input sequence
            \param Test A test sequence
            \param Loc A locale used for case insensitive comparison
            \return The result of the test

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline bool iends_with( 
            const Range1T& Input, 
            const Range2T& Test,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::ends_with(Input, Test, is_iequal(Loc));
        }

//  contains predicate  -----------------------------------------------//

        //! 'Contains' predicate
        /*!
            This predicate holds when the test container is contained in the Input.
            When the optional predicate is specified, it is used for character-wise
            comparison.

            \param Input An input sequence
            \param Test A test sequence
            \param Comp An element comparison predicate
            \return The result of the test

               \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool contains( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range1T>::type> lit_input(::boost::as_literal(Input));
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range2T>::type> lit_test(::boost::as_literal(Test));

            if (::boost::empty(lit_test))
            {
                // Empty range is contained always
                return true;
            }
            
            // Use the temporary variable to make VACPP happy
            bool bResult=(::boost::algorithm::first_finder(lit_test,Comp)(::boost::begin(lit_input), ::boost::end(lit_input)));
            return bResult;
        }

        //! 'Contains' predicate
        /*!
            \overload
        */
        template<typename Range1T, typename Range2T>
        inline bool contains( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::boost::algorithm::contains(Input, Test, is_equal());
        }

        //! 'Contains' predicate ( case insensitive )
        /*!
            This predicate holds when the test container is contained in the Input.
            Elements are compared case insensitively.

            \param Input An input sequence
            \param Test A test sequence
            \param Loc A locale used for case insensitive comparison
            \return The result of the test

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline bool icontains( 
            const Range1T& Input, 
            const Range2T& Test, 
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::contains(Input, Test, is_iequal(Loc));
        }

//  equals predicate  -----------------------------------------------//

        //! 'Equals' predicate
        /*!
            This predicate holds when the test container is equal to the
            input container i.e. all elements in both containers are same.
            When the optional predicate is specified, it is used for character-wise
            comparison.

            \param Input An input sequence
            \param Test A test sequence
            \param Comp An element comparison predicate
            \return The result of the test

            \note This is a two-way version of \c std::equal algorithm

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool equals( 
            const Range1T& Input, 
            const Range2T& Test,
            PredicateT Comp)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range1T>::type> lit_input(::boost::as_literal(Input));
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range2T>::type> lit_test(::boost::as_literal(Test));

            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<Range1T>::type Iterator1T;
            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<Range2T>::type Iterator2T;
                
            Iterator1T InputEnd=::boost::end(lit_input);
            Iterator2T TestEnd=::boost::end(lit_test);

            Iterator1T it=::boost::begin(lit_input);
            Iterator2T pit=::boost::begin(lit_test);
            for(;
                it!=InputEnd && pit!=TestEnd;
                ++it,++pit)
            {
                if( !(Comp(*it,*pit)) )
                    return false;
            }

            return  (pit==TestEnd) && (it==InputEnd);
        }

        //! 'Equals' predicate
        /*!
            \overload
        */
        template<typename Range1T, typename Range2T>
        inline bool equals( 
            const Range1T& Input, 
            const Range2T& Test)
        {
            return ::boost::algorithm::equals(Input, Test, is_equal());
        }

        //! 'Equals' predicate ( case insensitive )
        /*!
            This predicate holds when the test container is equal to the
            input container i.e. all elements in both containers are same.
            Elements are compared case insensitively.

            \param Input An input sequence
            \param Test A test sequence
            \param Loc A locale used for case insensitive comparison
            \return The result of the test

            \note This is a two-way version of \c std::equal algorithm

            \note This function provides the strong exception-safety guarantee
        */
        template<typename Range1T, typename Range2T>
        inline bool iequals( 
            const Range1T& Input, 
            const Range2T& Test,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::equals(Input, Test, is_iequal(Loc));
        }

// lexicographical_compare predicate -----------------------------//

        //! Lexicographical compare predicate
        /*!
             This predicate is an overload of std::lexicographical_compare
             for range arguments

             It check whether the first argument is lexicographically less
             then the second one.

             If the optional predicate is specified, it is used for character-wise
             comparison

             \param Arg1 First argument 
             \param Arg2 Second argument
             \param Pred Comparison predicate
             \return The result of the test

             \note This function provides the strong exception-safety guarantee
         */
        template<typename Range1T, typename Range2T, typename PredicateT>
        inline bool lexicographical_compare(
            const Range1T& Arg1,
            const Range2T& Arg2,
            PredicateT Pred)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range1T>::type> lit_arg1(::boost::as_literal(Arg1));
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<Range2T>::type> lit_arg2(::boost::as_literal(Arg2));

            return std::lexicographical_compare(
                ::boost::begin(lit_arg1),
                ::boost::end(lit_arg1),
                ::boost::begin(lit_arg2),
                ::boost::end(lit_arg2),
                Pred);
        }

        //! Lexicographical compare predicate
        /*!
            \overload
         */
        template<typename Range1T, typename Range2T>
            inline bool lexicographical_compare(
            const Range1T& Arg1,
            const Range2T& Arg2)
        {
            return ::boost::algorithm::lexicographical_compare(Arg1, Arg2, is_less());
        }

        //! Lexicographical compare predicate (case-insensitive)
        /*!
            This predicate is an overload of std::lexicographical_compare
            for range arguments.
            It check whether the first argument is lexicographically less
            then the second one.
            Elements are compared case insensitively


             \param Arg1 First argument 
             \param Arg2 Second argument
             \param Loc A locale used for case insensitive comparison
             \return The result of the test

             \note This function provides the strong exception-safety guarantee
         */
        template<typename Range1T, typename Range2T>
        inline bool ilexicographical_compare(
            const Range1T& Arg1,
            const Range2T& Arg2,
            const std::locale& Loc=std::locale())
        {
            return ::boost::algorithm::lexicographical_compare(Arg1, Arg2, is_iless(Loc));
        }
        

//  all predicate  -----------------------------------------------//

        //! 'All' predicate
        /*!
            This predicate holds it all its elements satisfy a given 
            condition, represented by the predicate.
            
            \param Input An input sequence
            \param Pred A predicate
            \return The result of the test

            \note This function provides the strong exception-safety guarantee
        */
        template<typename RangeT, typename PredicateT>
        inline bool all( 
            const RangeT& Input, 
            PredicateT Pred)
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_input(::boost::as_literal(Input));

            typedef BOOST_STRING_TYPENAME 
                range_const_iterator<RangeT>::type Iterator1T;

            Iterator1T InputEnd=::boost::end(lit_input);
            for( Iterator1T It=::boost::begin(lit_input); It!=InputEnd; ++It)
            {
                if (!Pred(*It))
                    return false;
            }
            
            return true;
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::starts_with;
    using algorithm::istarts_with;
    using algorithm::ends_with;
    using algorithm::iends_with;
    using algorithm::contains;
    using algorithm::icontains;
    using algorithm::equals;
    using algorithm::iequals;
    using algorithm::all;
    using algorithm::lexicographical_compare;
    using algorithm::ilexicographical_compare;

} // namespace boost


#endif  // BOOST_STRING_PREDICATE_HPP

/* predicate.hpp
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
*/