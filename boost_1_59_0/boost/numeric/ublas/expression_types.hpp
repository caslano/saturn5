//  Copyright (c) 2000-2013
//  Joerg Walter, Mathias Koch. David Bellot
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//
#ifndef _BOOST_UBLAS_EXPRESSION_TYPE_
#define _BOOST_UBLAS_EXPRESSION_TYPE_

#include <boost/numeric/ublas/exception.hpp>
#include <boost/numeric/ublas/traits.hpp>
#include <boost/numeric/ublas/functional.hpp>


// Expression templates based on ideas of Todd Veldhuizen and Geoffrey Furnish
// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

    /** \brief Base class for uBLAS statically derived expressions using the the Barton Nackman trick
     *
     * This is a NonAssignable class
     * Directly implement nonassignable - simplifes debugging call trace!
     * 
     * \tparam E an expression type
     */
    template<class E>
    class ublas_expression {
    public:
        typedef E expression_type;
        /* E can be an incomplete type - to define the following we would need more template arguments
        typedef typename E::type_category type_category;
        typedef typename E::value_type value_type;
        */
        
    protected:
        ublas_expression () {}
        ~ublas_expression () {}
    private:
        const ublas_expression& operator= (const ublas_expression &);
    };


    /** \brief Base class for Scalar Expression models
     *
     * It does not model the Scalar Expression concept but all derived types should.
     * The class defines a common base type and some common interface for all statically 
     * derived Scalar Expression classes.
     *
     * We implement the casts to the statically derived type.
     *
     * \tparam E an expression type
     */
    template<class E>
    class scalar_expression:
        public ublas_expression<E> {
    public:
        typedef E expression_type;
        typedef scalar_tag type_category;

        BOOST_UBLAS_INLINE
        const expression_type &operator () () const {
            return *static_cast<const expression_type *> (this);
        }
        BOOST_UBLAS_INLINE
        expression_type &operator () () {
            return *static_cast<expression_type *> (this);
        }
    };

    template<class T>
    class scalar_reference:
        public scalar_expression<scalar_reference<T> > {

        typedef scalar_reference<T> self_type;
    public:
        typedef T value_type;
        typedef const value_type &const_reference;
        typedef typename boost::mpl::if_<boost::is_const<T>,
                                          const_reference,
                                          value_type &>::type reference;
        typedef const self_type const_closure_type;
        typedef const_closure_type closure_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        explicit scalar_reference (reference t):
            t_ (t) {}

        // Conversion
        BOOST_UBLAS_INLINE
        operator value_type () const {
            return t_;
        }

        // Assignment
        BOOST_UBLAS_INLINE
        scalar_reference &operator = (const scalar_reference &s) {
            t_ = s.t_;
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        scalar_reference &operator = (const scalar_expression<AE> &ae) {
            t_ = ae;
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const scalar_reference &sr) const {
            return &t_ == &sr.t_;
        }

    private:
        reference t_;
    };

    template<class T>
    class scalar_value:
        public scalar_expression<scalar_value<T> > {

        typedef scalar_value<T> self_type;
    public:
        typedef T value_type;
        typedef const value_type &const_reference;
        typedef typename boost::mpl::if_<boost::is_const<T>,
                                          const_reference,
                                          value_type &>::type reference;
        typedef const scalar_reference<const self_type> const_closure_type;
        typedef scalar_reference<self_type> closure_type;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        scalar_value ():
            t_ () {}
        BOOST_UBLAS_INLINE
        scalar_value (const value_type &t):
            t_ (t) {}

        BOOST_UBLAS_INLINE
        operator value_type () const {
            return t_;
        }

        // Assignment
        BOOST_UBLAS_INLINE
        scalar_value &operator = (const scalar_value &s) {
            t_ = s.t_;
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        scalar_value &operator = (const scalar_expression<AE> &ae) {
            t_ = ae;
            return *this;
        }

        // Closure comparison
        BOOST_UBLAS_INLINE
        bool same_closure (const scalar_value &sv) const {
            return this == &sv;    // self closing on instances value
        }

    private:
        value_type t_;
    };


    /** \brief Base class for Vector Expression models
     *
     * it does not model the Vector Expression concept but all derived types should.
     * The class defines a common base type and some common interface for all
     * statically derived Vector Expression classes.
     * We implement the casts to the statically derived type.
     */
    template<class E>
    class vector_expression:
        public ublas_expression<E> {
    public:
        static const unsigned complexity = 0;
        typedef E expression_type;
        typedef vector_tag type_category;
        /* E can be an incomplete type - to define the following we would need more template arguments
        typedef typename E::size_type size_type;
        */
 
        BOOST_UBLAS_INLINE
        const expression_type &operator () () const {
            return *static_cast<const expression_type *> (this);
        }
        BOOST_UBLAS_INLINE
        expression_type &operator () () {
            return *static_cast<expression_type *> (this);
        }

#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
    private:
        // projection types
        typedef vector_range<E> vector_range_type;
        typedef vector_range<const E> const_vector_range_type;
        typedef vector_slice<E> vector_slice_type;
        typedef vector_slice<const E> const_vector_slice_type;
        // vector_indirect_type will depend on the A template parameter 
        typedef basic_range<> default_range;    // required to avoid range/slice name confusion
        typedef basic_slice<> default_slice;
   public:
        BOOST_UBLAS_INLINE
        const_vector_range_type operator () (const default_range &r) const {
            return const_vector_range_type (operator () (), r);
        }
        BOOST_UBLAS_INLINE
        vector_range_type operator () (const default_range &r) {
            return vector_range_type (operator () (), r);
        }
        BOOST_UBLAS_INLINE
        const_vector_slice_type operator () (const default_slice &s) const {
            return const_vector_slice_type (operator () (), s);
        }
        BOOST_UBLAS_INLINE
        vector_slice_type operator () (const default_slice &s) {
            return vector_slice_type (operator () (), s);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        const vector_indirect<const E, indirect_array<A> > operator () (const indirect_array<A> &ia) const {
            return vector_indirect<const E, indirect_array<A> >  (operator () (), ia);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        vector_indirect<E, indirect_array<A> > operator () (const indirect_array<A> &ia) {
            return vector_indirect<E, indirect_array<A> > (operator () (), ia);
        }

        BOOST_UBLAS_INLINE
        const_vector_range_type project (const default_range &r) const {
            return const_vector_range_type (operator () (), r);
        }
        BOOST_UBLAS_INLINE
        vector_range_type project (const default_range &r) {
            return vector_range_type (operator () (), r);
        }
        BOOST_UBLAS_INLINE
        const_vector_slice_type project (const default_slice &s) const {
            return const_vector_slice_type (operator () (), s);
        }
        BOOST_UBLAS_INLINE
        vector_slice_type project (const default_slice &s) {
            return vector_slice_type (operator () (), s);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        const vector_indirect<const E, indirect_array<A> > project (const indirect_array<A> &ia) const {
            return vector_indirect<const E, indirect_array<A> > (operator () (), ia);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        vector_indirect<E, indirect_array<A> > project (const indirect_array<A> &ia) {
            return vector_indirect<E, indirect_array<A> > (operator () (), ia);
        }
#endif
    };

    /** \brief Base class for Vector container models
     *
     * it does not model the Vector concept but all derived types should.
     * The class defines a common base type and some common interface for all
     * statically derived Vector classes
     * We implement the casts to the statically derived type.
     */
    template<class C>
    class vector_container:
        public vector_expression<C> {
    public:
        static const unsigned complexity = 0;
        typedef C container_type;
        typedef vector_tag type_category;
 
        BOOST_UBLAS_INLINE
        const container_type &operator () () const {
            return *static_cast<const container_type *> (this);
        }
        BOOST_UBLAS_INLINE
        container_type &operator () () {
            return *static_cast<container_type *> (this);
        }

#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using vector_expression<C>::operator ();
#endif
    };


    /** \brief Base class for Matrix Expression models
     *
     * it does not model the Matrix Expression concept but all derived types should.
     * The class defines a common base type and some common interface for all
     * statically derived Matrix Expression classes
     * We implement the casts to the statically derived type.
     */
    template<class E>
    class matrix_expression:
        public ublas_expression<E> {
    private:
        typedef matrix_expression<E> self_type;
    public:
        static const unsigned complexity = 0;
        typedef E expression_type;
        typedef matrix_tag type_category;
        /* E can be an incomplete type - to define the following we would need more template arguments
        typedef typename E::size_type size_type;
        */

        BOOST_UBLAS_INLINE
        const expression_type &operator () () const {
            return *static_cast<const expression_type *> (this);
        }
        BOOST_UBLAS_INLINE
        expression_type &operator () () {
            return *static_cast<expression_type *> (this);
        }

#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
    private:
        // projection types
        typedef vector_range<E> vector_range_type;
        typedef const vector_range<const E> const_vector_range_type;
        typedef vector_slice<E> vector_slice_type;
        typedef const vector_slice<const E> const_vector_slice_type;
        typedef matrix_row<E> matrix_row_type;
        typedef const matrix_row<const E> const_matrix_row_type;
        typedef matrix_column<E> matrix_column_type;
        typedef const  matrix_column<const E> const_matrix_column_type;
        typedef matrix_range<E> matrix_range_type;
        typedef const matrix_range<const E> const_matrix_range_type;
        typedef matrix_slice<E> matrix_slice_type;
        typedef const matrix_slice<const E> const_matrix_slice_type;
        // matrix_indirect_type will depend on the A template parameter 
        typedef basic_range<> default_range;    // required to avoid range/slice name confusion
        typedef basic_slice<> default_slice;

    public:
        BOOST_UBLAS_INLINE
        const_matrix_row_type operator [] (std::size_t i) const {
            return const_matrix_row_type (operator () (), i);
        }
        BOOST_UBLAS_INLINE
        matrix_row_type operator [] (std::size_t i) {
            return matrix_row_type (operator () (), i);
        }
        BOOST_UBLAS_INLINE
        const_matrix_row_type row (std::size_t i) const {
            return const_matrix_row_type (operator () (), i);
        }
        BOOST_UBLAS_INLINE
        matrix_row_type row (std::size_t i) {
            return matrix_row_type (operator () (), i);
        }
        BOOST_UBLAS_INLINE
        const_matrix_column_type column (std::size_t j) const {
            return const_matrix_column_type (operator () (), j);
        }
        BOOST_UBLAS_INLINE
        matrix_column_type column (std::size_t j) {
            return matrix_column_type (operator () (), j);
        }

        BOOST_UBLAS_INLINE
        const_matrix_range_type operator () (const default_range &r1, const default_range &r2) const {
            return const_matrix_range_type (operator () (), r1, r2);
        }
        BOOST_UBLAS_INLINE
        matrix_range_type operator () (const default_range &r1, const default_range &r2) {
            return matrix_range_type (operator () (), r1, r2);
        }
        BOOST_UBLAS_INLINE
        const_matrix_slice_type operator () (const default_slice &s1, const default_slice &s2) const {
            return const_matrix_slice_type (operator () (), s1, s2);
        }
        BOOST_UBLAS_INLINE
        matrix_slice_type operator () (const default_slice &s1, const default_slice &s2) {
            return matrix_slice_type (operator () (), s1, s2);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        const matrix_indirect<const E, indirect_array<A> > operator () (const indirect_array<A> &ia1, const indirect_array<A> &ia2) const {
            return matrix_indirect<const E, indirect_array<A> > (operator () (), ia1, ia2);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        matrix_indirect<E, indirect_array<A> > operator () (const indirect_array<A> &ia1, const indirect_array<A> &ia2) {
            return matrix_indirect<E, indirect_array<A> > (operator () (), ia1, ia2);
        }

        BOOST_UBLAS_INLINE
        const_matrix_range_type project (const default_range &r1, const default_range &r2) const {
            return const_matrix_range_type (operator () (), r1, r2);
        }
        BOOST_UBLAS_INLINE
        matrix_range_type project (const default_range &r1, const default_range &r2) {
            return matrix_range_type (operator () (), r1, r2);
        }
        BOOST_UBLAS_INLINE
        const_matrix_slice_type project (const default_slice &s1, const default_slice &s2) const {
            return const_matrix_slice_type (operator () (), s1, s2);
        }
        BOOST_UBLAS_INLINE
        matrix_slice_type project (const default_slice &s1, const default_slice &s2) {
            return matrix_slice_type (operator () (), s1, s2);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        const matrix_indirect<const E, indirect_array<A> > project (const indirect_array<A> &ia1, const indirect_array<A> &ia2) const {
            return matrix_indirect<const E, indirect_array<A> > (operator () (), ia1, ia2);
        }
        template<class A>
        BOOST_UBLAS_INLINE
        matrix_indirect<E, indirect_array<A> > project (const indirect_array<A> &ia1, const indirect_array<A> &ia2) {
            return matrix_indirect<E, indirect_array<A> > (operator () (), ia1, ia2);
        }
#endif
    };

#ifdef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
    struct iterator1_tag {};
    struct iterator2_tag {};

    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_iterator_type begin (const I &it, iterator1_tag) {
        return it ().find2 (1, it.index1 (), 0);
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_iterator_type end (const I &it, iterator1_tag) {
        return it ().find2 (1, it.index1 (), it ().size2 ());
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_reverse_iterator_type rbegin (const I &it, iterator1_tag) {
        return typename I::dual_reverse_iterator_type (end (it, iterator1_tag ()));
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_reverse_iterator_type rend (const I &it, iterator1_tag) {
        return typename I::dual_reverse_iterator_type (begin (it, iterator1_tag ()));
    }

    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_iterator_type begin (const I &it, iterator2_tag) {
        return it ().find1 (1, 0, it.index2 ());
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_iterator_type end (const I &it, iterator2_tag) {
        return it ().find1 (1, it ().size1 (), it.index2 ());
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_reverse_iterator_type rbegin (const I &it, iterator2_tag) {
        return typename I::dual_reverse_iterator_type (end (it, iterator2_tag ()));
    }
    template<class I>
    BOOST_UBLAS_INLINE
    typename I::dual_reverse_iterator_type rend (const I &it, iterator2_tag) {
        return typename I::dual_reverse_iterator_type (begin (it, iterator2_tag ()));
    }
#endif

    /** \brief Base class for Matrix container models
     *
     * it does not model the Matrix concept but all derived types should.
     * The class defines a common base type and some common interface for all
     * statically derived Matrix classes
     * We implement the casts to the statically derived type.
     */
    template<class C>
    class matrix_container:
        public matrix_expression<C> {
    public:
        static const unsigned complexity = 0;
        typedef C container_type;
        typedef matrix_tag type_category;

        BOOST_UBLAS_INLINE
        const container_type &operator () () const {
            return *static_cast<const container_type *> (this);
        }
        BOOST_UBLAS_INLINE
        container_type &operator () () {
            return *static_cast<container_type *> (this);
        }

#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using matrix_expression<C>::operator ();
#endif
    };

}}}

#endif

/* expression_types.hpp
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
*/