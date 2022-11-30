//  Boost string_algo library classification.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CLASSIFICATION_HPP
#define BOOST_STRING_CLASSIFICATION_HPP

#include <algorithm>
#include <locale>
#include <boost/range/value_type.hpp>
#include <boost/range/as_literal.hpp>
#include <boost/algorithm/string/detail/classification.hpp>
#include <boost/algorithm/string/predicate_facade.hpp>


/*! \file
    Classification predicates are included in the library to give 
    some more convenience when using algorithms like \c trim() and \c all(). 
    They wrap functionality of STL classification functions ( e.g. \c std::isspace() )
    into generic functors. 
*/

namespace boost {
    namespace algorithm {

//  classification functor generator -------------------------------------//

        //! is_classified predicate
        /*!
            Construct the \c is_classified predicate. This predicate holds if the input is
            of specified \c std::ctype category.

            \param Type A \c std::ctype category
            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate 
        */
        inline detail::is_classifiedF
        is_classified(std::ctype_base::mask Type, const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(Type, Loc);
        }

        //! is_space predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::space category.   

            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate
        */
        inline detail::is_classifiedF 
        is_space(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::space, Loc);
        }

        //! is_alnum predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::alnum category.   

            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate 
        */
        inline detail::is_classifiedF 
        is_alnum(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::alnum, Loc);
        }

        //! is_alpha predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::alpha category.   

            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate 
        */
        inline detail::is_classifiedF 
        is_alpha(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::alpha, Loc);
        }

        //! is_cntrl predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::cntrl category.   

            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate 
        */
        inline detail::is_classifiedF 
        is_cntrl(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::cntrl, Loc);
        }

        //! is_digit predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::digit category.   

            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate 
        */
        inline detail::is_classifiedF 
        is_digit(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::digit, Loc);
        }

        //! is_graph predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::graph category.   

            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate 
        */
        inline detail::is_classifiedF
        is_graph(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::graph, Loc);
        }

        //! is_lower predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::lower category.   

            \param Loc A locale used for classification
            \return An instance of \c is_classified predicate 
        */
        inline detail::is_classifiedF 
        is_lower(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::lower, Loc);
        }

        //! is_print predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::print category.   

            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate 
        */
        inline detail::is_classifiedF 
        is_print(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::print, Loc);
        }

        //! is_punct predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::punct category.   

            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate 
        */
        inline detail::is_classifiedF 
        is_punct(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::punct, Loc);
        }

        //! is_upper predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::upper category.   

            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate 
        */
        inline detail::is_classifiedF 
        is_upper(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::upper, Loc);
        }

        //! is_xdigit predicate
        /*!
            Construct the \c is_classified predicate for the \c ctype_base::xdigit category.  

            \param Loc A locale used for classification
            \return An instance of the \c is_classified predicate 
        */
        inline detail::is_classifiedF 
        is_xdigit(const std::locale& Loc=std::locale())
        {
            return detail::is_classifiedF(std::ctype_base::xdigit, Loc);
        }

        //! is_any_of predicate
        /*!
            Construct the \c is_any_of predicate. The predicate holds if the input
            is included in the specified set of characters.

            \param Set A set of characters to be recognized
            \return An instance of the \c is_any_of predicate 
        */
        template<typename RangeT>
        inline detail::is_any_ofF<
            BOOST_STRING_TYPENAME range_value<RangeT>::type> 
        is_any_of( const RangeT& Set )
        {
            iterator_range<BOOST_STRING_TYPENAME range_const_iterator<RangeT>::type> lit_set(boost::as_literal(Set));
            return detail::is_any_ofF<BOOST_STRING_TYPENAME range_value<RangeT>::type>(lit_set); 
        }

        //! is_from_range predicate
        /*!
            Construct the \c is_from_range predicate. The predicate holds if the input
            is included in the specified range. (i.e. From <= Ch <= To )

            \param From The start of the range
            \param To The end of the range
            \return An instance of the \c is_from_range predicate 
        */
        template<typename CharT>
        inline detail::is_from_rangeF<CharT> is_from_range(CharT From, CharT To)
        {
            return detail::is_from_rangeF<CharT>(From,To); 
        }
        
        // predicate combinators ---------------------------------------------------//

        //! predicate 'and' composition predicate
        /*!
            Construct the \c class_and predicate. This predicate can be used
            to logically combine two classification predicates. \c class_and holds,
            if both predicates return true.

            \param Pred1 The first predicate
            \param Pred2 The second predicate
            \return An instance of the \c class_and predicate     
        */
        template<typename Pred1T, typename Pred2T>
        inline detail::pred_andF<Pred1T, Pred2T>
        operator&&( 
            const predicate_facade<Pred1T>& Pred1, 
            const predicate_facade<Pred2T>& Pred2 )
        {    
            // Doing the static_cast with the pointer instead of the reference
            // is a workaround for some compilers which have problems with
            // static_cast's of template references, i.e. CW8. /grafik/
            return detail::pred_andF<Pred1T,Pred2T>(
                *static_cast<const Pred1T*>(&Pred1), 
                *static_cast<const Pred2T*>(&Pred2) );
        }

        //! predicate 'or' composition predicate
        /*!
            Construct the \c class_or predicate. This predicate can be used
            to logically combine two classification predicates. \c class_or holds,
            if one of the predicates return true.

            \param Pred1 The first predicate
            \param Pred2 The second predicate
            \return An instance of the \c class_or predicate     
        */
        template<typename Pred1T, typename Pred2T>
        inline detail::pred_orF<Pred1T, Pred2T>
        operator||( 
            const predicate_facade<Pred1T>& Pred1, 
            const predicate_facade<Pred2T>& Pred2 )
        {    
            // Doing the static_cast with the pointer instead of the reference
            // is a workaround for some compilers which have problems with
            // static_cast's of template references, i.e. CW8. /grafik/
            return detail::pred_orF<Pred1T,Pred2T>(
                *static_cast<const Pred1T*>(&Pred1), 
                *static_cast<const Pred2T*>(&Pred2));
        }

        //! predicate negation operator
        /*!
            Construct the \c class_not predicate. This predicate represents a negation. 
            \c class_or holds if of the predicates return false.

            \param Pred The predicate to be negated
            \return An instance of the \c class_not predicate     
        */
        template<typename PredT>
        inline detail::pred_notF<PredT>
        operator!( const predicate_facade<PredT>& Pred )
        {
            // Doing the static_cast with the pointer instead of the reference
            // is a workaround for some compilers which have problems with
            // static_cast's of template references, i.e. CW8. /grafik/
            return detail::pred_notF<PredT>(*static_cast<const PredT*>(&Pred)); 
        }

    } // namespace algorithm

    // pull names to the boost namespace
    using algorithm::is_classified;
    using algorithm::is_space;
    using algorithm::is_alnum;
    using algorithm::is_alpha;
    using algorithm::is_cntrl;
    using algorithm::is_digit;
    using algorithm::is_graph;
    using algorithm::is_lower;
    using algorithm::is_upper;
    using algorithm::is_print;
    using algorithm::is_punct;
    using algorithm::is_xdigit;
    using algorithm::is_any_of;
    using algorithm::is_from_range;

} // namespace boost

#endif  // BOOST_STRING_PREDICATE_HPP

/* classification.hpp
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
*/