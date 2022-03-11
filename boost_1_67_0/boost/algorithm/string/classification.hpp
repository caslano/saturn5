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