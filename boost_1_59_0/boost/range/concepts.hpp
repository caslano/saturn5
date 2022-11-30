// Boost.Range library concept checks
//
//  Copyright Neil Groves 2009. Use, modification and distribution
//  are subject to the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  Copyright Daniel Walker 2006. Use, modification and distribution
//  are subject to the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_CONCEPTS_HPP
#define BOOST_RANGE_CONCEPTS_HPP

#include <boost/concept_check.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/detail/misc_concept.hpp>
#include <boost/type_traits/remove_reference.hpp>

#include <iterator>

/*!
 * \file
 * \brief Concept checks for the Boost Range library.
 *
 * The structures in this file may be used in conjunction with the
 * Boost Concept Check library to insure that the type of a function
 * parameter is compatible with a range concept. If not, a meaningful
 * compile time error is generated. Checks are provided for the range
 * concepts related to iterator traversal categories. For example, the
 * following line checks that the type T models the ForwardRange
 * concept.
 *
 * \code
 * BOOST_CONCEPT_ASSERT((ForwardRangeConcept<T>));
 * \endcode
 *
 * A different concept check is required to ensure writeable value
 * access. For example to check for a ForwardRange that can be written
 * to, the following code is required.
 *
 * \code
 * BOOST_CONCEPT_ASSERT((WriteableForwardRangeConcept<T>));
 * \endcode
 *
 * \see http://www.boost.org/libs/range/doc/range.html for details
 * about range concepts.
 * \see http://www.boost.org/libs/iterator/doc/iterator_concepts.html
 * for details about iterator concepts.
 * \see http://www.boost.org/libs/concept_check/concept_check.htm for
 * details about concept checks.
 */

namespace boost {

    namespace range_detail {

#ifndef BOOST_RANGE_ENABLE_CONCEPT_ASSERT

// List broken compiler versions here:
#ifndef __clang__
    #ifdef __GNUC__
        // GNUC 4.2 has strange issues correctly detecting compliance with the Concepts
        // hence the least disruptive approach is to turn-off the concept checking for
        // this version of the compiler.
        #if __GNUC__ == 4 && __GNUC_MINOR__ == 2
            #define BOOST_RANGE_ENABLE_CONCEPT_ASSERT 0
        #endif
    #endif

    #ifdef __GCCXML__
        // GCC XML, unsurprisingly, has the same issues
        #if __GCCXML_GNUC__ == 4 && __GCCXML_GNUC_MINOR__ == 2
            #define BOOST_RANGE_ENABLE_CONCEPT_ASSERT 0
        #endif
    #endif
#endif

    #ifdef BOOST_BORLANDC
        #define BOOST_RANGE_ENABLE_CONCEPT_ASSERT 0
    #endif

    #ifdef __PATHCC__
        #define BOOST_RANGE_ENABLE_CONCEPT_ASSERT 0
    #endif

// Default to using the concept asserts unless we have defined it off
// during the search for black listed compilers.
    #ifndef BOOST_RANGE_ENABLE_CONCEPT_ASSERT
        #define BOOST_RANGE_ENABLE_CONCEPT_ASSERT 1
    #endif

#endif

#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
    #define BOOST_RANGE_CONCEPT_ASSERT( x ) BOOST_CONCEPT_ASSERT( x )
#else
    #define BOOST_RANGE_CONCEPT_ASSERT( x )
#endif

        // Rationale for the inclusion of redefined iterator concept
        // classes:
        //
        // The Range algorithms often do not require that the iterators are
        // Assignable or default constructable, but the correct standard
        // conformant iterators do require the iterators to be a model of the
        // Assignable concept.
        // Iterators that contains a functor that is not assignable therefore
        // are not correct models of the standard iterator concepts,
        // despite being adequate for most algorithms. An example of this
        // use case is the combination of the boost::adaptors::filtered
        // class with a boost::lambda::bind generated functor.
        // Ultimately modeling the range concepts using composition
        // with the Boost.Iterator concepts would render the library
        // incompatible with many common Boost.Lambda expressions.
        template<class Iterator>
        struct IncrementableIteratorConcept : CopyConstructible<Iterator>
        {
#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
            typedef BOOST_DEDUCED_TYPENAME iterator_traversal<Iterator>::type traversal_category;

            BOOST_RANGE_CONCEPT_ASSERT((
                Convertible<
                    traversal_category,
                    incrementable_traversal_tag
                >));

            BOOST_CONCEPT_USAGE(IncrementableIteratorConcept)
            {
                ++i;
                (void)i++;
            }
        private:
            Iterator i;
#endif
        };

        template<class Iterator>
        struct SinglePassIteratorConcept
            : IncrementableIteratorConcept<Iterator>
            , EqualityComparable<Iterator>
        {
#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
            BOOST_RANGE_CONCEPT_ASSERT((
                Convertible<
                    BOOST_DEDUCED_TYPENAME SinglePassIteratorConcept::traversal_category,
                    single_pass_traversal_tag
                >));

            BOOST_CONCEPT_USAGE(SinglePassIteratorConcept)
            {
                Iterator i2(++i);
                boost::ignore_unused_variable_warning(i2);

                // deliberately we are loose with the postfix version for the single pass
                // iterator due to the commonly poor adherence to the specification means that
                // many algorithms would be unusable, whereas actually without the check they
                // work
                (void)(i++);

                BOOST_DEDUCED_TYPENAME std::iterator_traits<Iterator>::reference r1(*i);
                boost::ignore_unused_variable_warning(r1);

                BOOST_DEDUCED_TYPENAME std::iterator_traits<Iterator>::reference r2(*(++i));
                boost::ignore_unused_variable_warning(r2);
            }
        private:
            Iterator i;
#endif
        };

        template<class Iterator>
        struct ForwardIteratorConcept
            : SinglePassIteratorConcept<Iterator>
            , DefaultConstructible<Iterator>
        {
#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
            typedef BOOST_DEDUCED_TYPENAME std::iterator_traits<Iterator>::difference_type difference_type;

            BOOST_MPL_ASSERT((is_integral<difference_type>));
            BOOST_MPL_ASSERT_RELATION(std::numeric_limits<difference_type>::is_signed, ==, true);

            BOOST_RANGE_CONCEPT_ASSERT((
                Convertible<
                    BOOST_DEDUCED_TYPENAME ForwardIteratorConcept::traversal_category,
                    forward_traversal_tag
                >));

            BOOST_CONCEPT_USAGE(ForwardIteratorConcept)
            {
                // See the above note in the SinglePassIteratorConcept about the handling of the
                // postfix increment. Since with forward and better iterators there is no need
                // for a proxy, we can sensibly require that the dereference result
                // is convertible to reference.
                Iterator i2(i++);
                boost::ignore_unused_variable_warning(i2);
                BOOST_DEDUCED_TYPENAME std::iterator_traits<Iterator>::reference r(*(i++));
                boost::ignore_unused_variable_warning(r);
            }
        private:
            Iterator i;
#endif
         };

         template<class Iterator>
         struct BidirectionalIteratorConcept
             : ForwardIteratorConcept<Iterator>
         {
 #if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
             BOOST_RANGE_CONCEPT_ASSERT((
                 Convertible<
                     BOOST_DEDUCED_TYPENAME BidirectionalIteratorConcept::traversal_category,
                     bidirectional_traversal_tag
                 >));

             BOOST_CONCEPT_USAGE(BidirectionalIteratorConcept)
             {
                 --i;
                 (void)i--;
             }
         private:
             Iterator i;
 #endif
         };

         template<class Iterator>
         struct RandomAccessIteratorConcept
             : BidirectionalIteratorConcept<Iterator>
         {
 #if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
             BOOST_RANGE_CONCEPT_ASSERT((
                 Convertible<
                     BOOST_DEDUCED_TYPENAME RandomAccessIteratorConcept::traversal_category,
                     random_access_traversal_tag
                 >));

             BOOST_CONCEPT_USAGE(RandomAccessIteratorConcept)
             {
                 i += n;
                 i = i + n;
                 i = n + i;
                 i -= n;
                 i = i - n;
                 n = i - j;
             }
         private:
             BOOST_DEDUCED_TYPENAME BidirectionalIteratorConcept<Iterator>::difference_type n;
             Iterator i;
             Iterator j;
 #endif
         };

    } // namespace range_detail

    //! Check if a type T models the SinglePassRange range concept.
    template<class T>
    struct SinglePassRangeConcept
    {
#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
        // A few compilers don't like the rvalue reference T types so just
        // remove it.
        typedef BOOST_DEDUCED_TYPENAME remove_reference<T>::type Rng;

        typedef BOOST_DEDUCED_TYPENAME range_iterator<
            Rng const
        >::type const_iterator;

        typedef BOOST_DEDUCED_TYPENAME range_iterator<Rng>::type iterator;

        BOOST_RANGE_CONCEPT_ASSERT((
                range_detail::SinglePassIteratorConcept<iterator>));

        BOOST_RANGE_CONCEPT_ASSERT((
                range_detail::SinglePassIteratorConcept<const_iterator>));

        BOOST_CONCEPT_USAGE(SinglePassRangeConcept)
        {
            // This has been modified from assigning to this->i
            // (where i was a member variable) to improve
            // compatibility with Boost.Lambda
            iterator i1 = boost::begin(*m_range);
            iterator i2 = boost::end(*m_range);

            boost::ignore_unused_variable_warning(i1);
            boost::ignore_unused_variable_warning(i2);

            const_constraints(*m_range);
        }

    private:
        void const_constraints(const Rng& const_range)
        {
            const_iterator ci1 = boost::begin(const_range);
            const_iterator ci2 = boost::end(const_range);

            boost::ignore_unused_variable_warning(ci1);
            boost::ignore_unused_variable_warning(ci2);
        }

       // Rationale:
       // The type of m_range is T* rather than T because it allows
       // T to be an abstract class. The other obvious alternative of
       // T& produces a warning on some compilers.
       Rng* m_range;
#endif
    };

    //! Check if a type T models the ForwardRange range concept.
    template<class T>
    struct ForwardRangeConcept : SinglePassRangeConcept<T>
    {
#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
        BOOST_RANGE_CONCEPT_ASSERT((range_detail::ForwardIteratorConcept<BOOST_DEDUCED_TYPENAME ForwardRangeConcept::iterator>));
        BOOST_RANGE_CONCEPT_ASSERT((range_detail::ForwardIteratorConcept<BOOST_DEDUCED_TYPENAME ForwardRangeConcept::const_iterator>));
#endif
    };

    template<class T>
    struct WriteableRangeConcept
    {
#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
        typedef BOOST_DEDUCED_TYPENAME range_iterator<T>::type iterator;

        BOOST_CONCEPT_USAGE(WriteableRangeConcept)
        {
            *i = v;
        }
    private:
        iterator i;
        BOOST_DEDUCED_TYPENAME range_value<T>::type v;
#endif
    };

    //! Check if a type T models the WriteableForwardRange range concept.
    template<class T>
    struct WriteableForwardRangeConcept
        : ForwardRangeConcept<T>
        , WriteableRangeConcept<T>
    {
    };

    //! Check if a type T models the BidirectionalRange range concept.
    template<class T>
    struct BidirectionalRangeConcept : ForwardRangeConcept<T>
    {
#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
        BOOST_RANGE_CONCEPT_ASSERT((range_detail::BidirectionalIteratorConcept<BOOST_DEDUCED_TYPENAME BidirectionalRangeConcept::iterator>));
        BOOST_RANGE_CONCEPT_ASSERT((range_detail::BidirectionalIteratorConcept<BOOST_DEDUCED_TYPENAME BidirectionalRangeConcept::const_iterator>));
#endif
    };

    //! Check if a type T models the WriteableBidirectionalRange range concept.
    template<class T>
    struct WriteableBidirectionalRangeConcept
        : BidirectionalRangeConcept<T>
        , WriteableRangeConcept<T>
    {
    };

    //! Check if a type T models the RandomAccessRange range concept.
    template<class T>
    struct RandomAccessRangeConcept : BidirectionalRangeConcept<T>
    {
#if BOOST_RANGE_ENABLE_CONCEPT_ASSERT
        BOOST_RANGE_CONCEPT_ASSERT((range_detail::RandomAccessIteratorConcept<BOOST_DEDUCED_TYPENAME RandomAccessRangeConcept::iterator>));
        BOOST_RANGE_CONCEPT_ASSERT((range_detail::RandomAccessIteratorConcept<BOOST_DEDUCED_TYPENAME RandomAccessRangeConcept::const_iterator>));
#endif
    };

    //! Check if a type T models the WriteableRandomAccessRange range concept.
    template<class T>
    struct WriteableRandomAccessRangeConcept
        : RandomAccessRangeConcept<T>
        , WriteableRangeConcept<T>
    {
    };

} // namespace boost

#endif // BOOST_RANGE_CONCEPTS_HPP

/* concepts.hpp
+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
*/