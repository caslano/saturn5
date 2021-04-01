//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_DEFINITIONS_
#define _BOOST_UBLAS_DEFINITIONS_


namespace boost { namespace numeric { namespace ublas {

    namespace detail {
        /* Borrowed from boost/concept_checks.hpp
           "inline" is used for ignore_unused_variable_warning()
           to make sure there is no overhead with g++.
         */
        template <class T> inline
        void ignore_unused_variable_warning(const T&) {}
    } // namespace detail

    // Borrowed from Dave Abraham's noncopyable.
    // I believe this should be part of utility.hpp one day...
    namespace nonassignable_  // protection from unintended ADL
    {
        class nonassignable {
        protected:
            nonassignable () {}
            ~nonassignable () {}
        private:  // emphasize the following members are private
            const nonassignable& operator= (const nonassignable &);
        }; // nonassignable
    }
    typedef nonassignable_::nonassignable nonassignable;


    // Assignment proxy.
    // Provides temporary free assigment when LHS has no alias on RHS
    template<class C>
    class noalias_proxy:
        private nonassignable {
    public:
        typedef typename C::closure_type closure_type;

        BOOST_UBLAS_INLINE
        noalias_proxy (C& lval):
            nonassignable (), lval_ (lval) {}
        BOOST_UBLAS_INLINE
        noalias_proxy (const noalias_proxy& p):
            nonassignable (), lval_ (p.lval_) {}

        template <class E>
        BOOST_UBLAS_INLINE
        closure_type &operator= (const E& e) {
            lval_.assign (e);
            return lval_;
        }

        template <class E>
        BOOST_UBLAS_INLINE
        closure_type &operator+= (const E& e) {
            lval_.plus_assign (e);
            return lval_;
        }

        template <class E>
        BOOST_UBLAS_INLINE
        closure_type &operator-= (const E& e) {
            lval_.minus_assign (e);
            return lval_;
        }

    private:
        closure_type lval_;
    };

    // Improve syntax of efficient assignment where no aliases of LHS appear on the RHS
    //  noalias(lhs) = rhs_expression
    template <class C>
    BOOST_UBLAS_INLINE
    noalias_proxy<C> noalias (C& lvalue) {
        return noalias_proxy<C> (lvalue);
    }
    template <class C>
    BOOST_UBLAS_INLINE
    noalias_proxy<const C> noalias (const C& lvalue) {
        return noalias_proxy<const C> (lvalue);
    }

    // Possible future compatible syntax where lvalue possible has an unsafe alias on the RHS
    //  safe(lhs) = rhs_expression
    template <class C>
    BOOST_UBLAS_INLINE
    C& safe (C& lvalue) {
        return lvalue;
    }
    template <class C>
    BOOST_UBLAS_INLINE
    const C& safe (const C& lvalue) {
        return lvalue;
    }


    // Dimension accessors
    namespace dimension {

        // Generic accessors
        template<unsigned dimension>
        struct dimension_properties {};
        
        template<>
        struct dimension_properties<1> {
            template <class E>
            BOOST_UBLAS_INLINE static
            typename E::size_type size (const vector_expression<E> &e) {
                return e ().size ();
            }
            template <class E>
            BOOST_UBLAS_INLINE static
            typename E::size_type size (const matrix_expression<E> &e) {
                return e ().size1 ();
            }
            // Note: Index functions cannot deduce dependant template parameter V or M from i
            template <class V>
            BOOST_UBLAS_INLINE static
            typename V::size_type index (const typename V::iterator &i) {
                return i.index ();
            }
            template <class M>
            BOOST_UBLAS_INLINE static
            typename M::size_type index (const typename M::iterator1 &i) {
                return i.index1 ();
            }
            template <class M>
            BOOST_UBLAS_INLINE static
            typename M::size_type index (const typename M::iterator2 &i) {
                return i.index1 ();
            }
        };
        template<>
        struct dimension_properties<2> {
            template <class E>
            BOOST_UBLAS_INLINE static
            typename E::size_type size (const vector_expression<E> &) {
                return 1;
            }
            template <class E>
            BOOST_UBLAS_INLINE static
            typename E::size_type size (const matrix_expression<E> &e) {
                return e ().size2 ();
            }
            template <class V>
            BOOST_UBLAS_INLINE static
            typename V::size_type index (const typename V::iterator &) {
                return 1;
            }
            template <class M>
            BOOST_UBLAS_INLINE static
            typename M::size_type index (const typename M::iterator1 &i) {
                return i.index2 ();
            }
            template <class M>
            BOOST_UBLAS_INLINE static
            typename M::size_type index (const typename M::iterator2 &i) {
                return i.index2 ();
            }
        };

        template<unsigned dimension, class E>
        BOOST_UBLAS_INLINE
        typename E::size_type size (const E& e) {
            return dimension_properties<dimension>::size (e);
        }

        template<unsigned dimension, class I>
        BOOST_UBLAS_INLINE
        typename I::container_type::size_type
        index (const I& i) {
            typedef typename I::container_type container_type;
            return dimension_properties<dimension>::template index<container_type> (i);
        }


        // Named accessors - just syntactic sugar
        template<class V>
        typename V::size_type num_elements (const V &v) {
            return v.size ();
        }
        template<class M>
        typename M::size_type num_rows (const M &m) {
            return m.size1 ();
        }
        template<class M>
        typename M::size_type num_columns (const M &m) {
            return m.size2 ();
        }
        template<class MV>
        typename MV::size_type num_non_zeros (const MV &mv) {
            return mv.non_zeros ();
        }
    }


}}}

#endif

/* definitions.hpp
rjivQF2eFAsD52gMRt2z5p80QazwYCWaTQXUgNZoTh2bdW0Gj6wQtrYxyR0i2vnjiqecuRfdU3eeN8bYs/t06CLcBnRzwIFXFJgQYiVF7qFi7M/OsQ8G1TipV6h61OglbvwbPFhqnxYrd/vWuIOnNPvBD+9y4xlyRiX4fVV96Y9vEHbhY70z/wNIhjlSKJc2YeFmWRRPl6+CA0QqJOFrocS6shAoTUuA6tBmlhIFXpF7d6PT01L2JKiFkzGNW0rajLQcLsv46K6plii1QP5VMAJ0fkGg1+V+4llz/CrymPjsUINC2HaupRzOvGQq+LGfXt4Lo9oJnTKh3u+Sx3NHaP5/2YOVGw4YnulW+AkQ6qB9SsEC2TWUvE13p7QSsBshB2OILjbwqSlbr1FymnQnsDslwtLVJWY+5kZQn6Z4NqzozkPWpjqafeuNt1J4/Iw0NMZsgp1OOHqUJBtGrYI3p01tbSLpIGphztFlaMn6o01mV+RnzYIRJLMLXIEwr6bsJMJMyQ8izTGIV077USvzvhU1P/lJzT9lxGsDPrQ8dRyauxCgjr7bDQCt/Q==
*/