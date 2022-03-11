//  Boost string_algo library predicate.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_PREDICATE_HPP
#define BOOST_STRING_PREDICATE_HPP

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
            typedef BOOST_STRING_TYPENAME boost::detail::
                iterator_traits<Iterator1T>::iterator_category category;

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