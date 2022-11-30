//
//  Copyright (c) 2003
//  Gunter Winkler, Joerg Walter
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_VECTOR_OF_VECTOR_
#define _BOOST_UBLAS_VECTOR_OF_VECTOR_

#include <boost/type_traits.hpp>

#include <boost/numeric/ublas/storage_sparse.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>

// Iterators based on ideas of Jeremy Siek

namespace boost { namespace numeric { namespace ublas {

    // uBLAS sparse vector based sparse matrix class
    // FIXME outer vector can be sparse type but it is completely filled
    template<class T, class L, class A>
    class generalized_vector_of_vector:
        public matrix_container<generalized_vector_of_vector<T, L, A> > {

        typedef T &true_reference;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef L layout_type;
        typedef generalized_vector_of_vector<T, L, A> self_type;
    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using matrix_container<self_type>::operator ();
#endif
        typedef typename A::size_type size_type;
        typedef typename A::difference_type difference_type;
        typedef T value_type;
        typedef const T &const_reference;
#ifndef BOOST_UBLAS_STRICT_VECTOR_SPARSE
        typedef T &reference;
#else
        typedef sparse_matrix_element<self_type> reference;
#endif
        typedef A array_type;
        typedef const matrix_reference<const self_type> const_closure_type;
        typedef matrix_reference<self_type> closure_type;
        typedef typename A::value_type vector_data_value_type;
        typedef vector_data_value_type vector_temporary_type;
        typedef self_type matrix_temporary_type;
        typedef sparse_tag storage_category;
        typedef typename L::orientation_category orientation_category;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector ():
            matrix_container<self_type> (),
            size1_ (0), size2_ (0), data_ (1) {
            const size_type sizeM = layout_type::size_M (size1_, size2_);
             // create size1+1 empty vector elements
            data_.insert_element (sizeM, vector_data_value_type ());
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
				generalized_vector_of_vector (size_type size1, size_type size2, size_type /*non_zeros = 0*/):
            matrix_container<self_type> (),
            size1_ (size1), size2_ (size2), data_ (layout_type::size_M (size1_, size2_) + 1) {
            const size_type sizeM = layout_type::size_M (size1_, size2_);
            const size_type sizem = layout_type::size_m (size1_, size2_);
            for (size_type i = 0; i < sizeM; ++ i) // create size1 vector elements
                data_.insert_element (i, vector_data_value_type ()) .resize (sizem, false);
            data_.insert_element (sizeM, vector_data_value_type ());
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector (const generalized_vector_of_vector &m):
            matrix_container<self_type> (),
            size1_ (m.size1_), size2_ (m.size2_), data_ (m.data_) {
            storage_invariants ();
        }
        template<class AE>
        BOOST_UBLAS_INLINE
				generalized_vector_of_vector (const matrix_expression<AE> &ae, size_type /*non_zeros = 0*/):
            matrix_container<self_type> (),
            size1_ (ae ().size1 ()), size2_ (ae ().size2 ()), data_ (layout_type::size_M (size1_, size2_) + 1) {
            const size_type sizeM = layout_type::size_M (size1_, size2_);
            const size_type sizem = layout_type::size_m (size1_, size2_);
            for (size_type i = 0; i < sizeM; ++ i) // create size1 vector elements
                data_.insert_element (i, vector_data_value_type ()) .resize (sizem, false);
            data_.insert_element (sizeM, vector_data_value_type ());
            storage_invariants ();
            matrix_assign<scalar_assign> (*this, ae);
        }

        // Accessors
        BOOST_UBLAS_INLINE
        size_type size1 () const {
            return size1_;
        }
        BOOST_UBLAS_INLINE
        size_type size2 () const {
            return size2_;
        }
        BOOST_UBLAS_INLINE
        size_type nnz_capacity () const {
            size_type non_zeros = 0;
            for (const_vectoriterator_type itv = data_.begin (); itv != data_.end (); ++ itv)
                non_zeros += (*itv).nnz_capacity ();
            return non_zeros;
        }
        BOOST_UBLAS_INLINE
        size_type nnz () const {
            size_type non_zeros = 0;
            for (const_vectoriterator_type itv = data_.begin (); itv != data_.end (); ++ itv)
                non_zeros += (*itv).nnz ();
            return non_zeros;
        }

        // Storage accessors
        BOOST_UBLAS_INLINE
        const array_type &data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        array_type &data () {
            return data_;
        }

        // Resizing
        BOOST_UBLAS_INLINE
        void resize (size_type size1, size_type size2, bool preserve = true) {
            const size_type oldM = layout_type::size_M (size1_, size2_);
            size1_ = size1;
            size2_ = size2;
            const size_type sizeM = layout_type::size_M (size1_, size2_);
            const size_type sizem = layout_type::size_m (size1_, size2_);
            data ().resize (sizeM + 1, preserve);
            if (preserve) {
                for (size_type i = 0; (i <= oldM) && (i < sizeM); ++ i)
                    ref (data () [i]).resize (sizem, preserve);
                for (size_type i = oldM+1; i < sizeM; ++ i) // create new vector elements
                    data_.insert_element (i, vector_data_value_type ()) .resize (sizem, false);
                if (sizeM > oldM) {
                    data_.insert_element (sizeM, vector_data_value_type ());
                } else {
                    ref (data () [sizeM]).resize (0, false);
                }
            } else {
                for (size_type i = 0; i < sizeM; ++ i) 
                    data_.insert_element (i, vector_data_value_type ()) .resize (sizem, false);
                data_.insert_element (sizeM, vector_data_value_type ());
            }
            storage_invariants ();
        }

        // Element support
        BOOST_UBLAS_INLINE
        pointer find_element (size_type i, size_type j) {
            return const_cast<pointer> (const_cast<const self_type&>(*this).find_element (i, j));
        }
        BOOST_UBLAS_INLINE
        const_pointer find_element (size_type i, size_type j) const {
            const size_type elementM = layout_type::index_M (i, j);
            const size_type elementm = layout_type::index_m (i, j);
            // optimise: check the storage_type and index directly if element always exists
            if (boost::is_convertible<typename array_type::storage_category, packed_tag>::value) {
                return & (data () [elementM] [elementm]);
            }
            else {
                const typename array_type::value_type *pv = data ().find_element (elementM);
                if (!pv)
                    return 0;
                return pv->find_element (elementm);
            }
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i, size_type j) const {
            const_pointer p = find_element (i, j);
            // optimise: check the storage_type and index directly if element always exists
            if (boost::is_convertible<typename array_type::storage_category, packed_tag>::value) {
                BOOST_UBLAS_CHECK (p, internal_logic () );
                return *p;
            }
            else {
                if (p)
                    return *p;
                else
                    return zero_;
            }
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i, size_type j) {
#ifndef BOOST_UBLAS_STRICT_MATRIX_SPARSE
            return at_element (i, j);
#else
            return reference (*this, i, j);
#endif
        }

        // Assignment
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector &operator = (const generalized_vector_of_vector &m) {
            if (this != &m) {
                size1_ = m.size1_;
                size2_ = m.size2_;
                data () = m.data ();
            }
            storage_invariants ();
            return *this;
        }
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector &assign_temporary (generalized_vector_of_vector &m) {
            swap (m);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector &operator = (const matrix_expression<AE> &ae) {
            self_type temporary (ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector &assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector& operator += (const matrix_expression<AE> &ae) {
            self_type temporary (*this + ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector &plus_assign (const matrix_expression<AE> &ae) { 
            matrix_assign<scalar_plus_assign> (*this, ae);
            return *this;
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector& operator -= (const matrix_expression<AE> &ae) {
            self_type temporary (*this - ae);
            return assign_temporary (temporary);
        }
        template<class AE>
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector &minus_assign (const matrix_expression<AE> &ae) {
            matrix_assign<scalar_minus_assign> (*this, ae);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector& operator *= (const AT &at) {
            matrix_assign_scalar<scalar_multiplies_assign> (*this, at);
            return *this;
        }
        template<class AT>
        BOOST_UBLAS_INLINE
        generalized_vector_of_vector& operator /= (const AT &at) {
            matrix_assign_scalar<scalar_divides_assign> (*this, at);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (generalized_vector_of_vector &m) {
            if (this != &m) {
                std::swap (size1_, m.size1_);
                std::swap (size2_, m.size2_);
                data ().swap (m.data ());
            }
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        friend void swap (generalized_vector_of_vector &m1, generalized_vector_of_vector &m2) {
            m1.swap (m2);
        }

        // Sorting
        void sort () {
            vectoriterator_type itv (data ().begin ());
            vectoriterator_type itv_end (data ().end ());
            while (itv != itv_end) {
                (*itv).sort ();
                ++ itv;
            }
        }

        // Element insertion and erasure
        BOOST_UBLAS_INLINE
        true_reference insert_element (size_type i, size_type j, const_reference t) {
            const size_type elementM = layout_type::index_M (i, j);
            const size_type elementm = layout_type::index_m (i, j);
            vector_data_value_type& vd (ref (data () [elementM]));
            storage_invariants ();
            return vd.insert_element (elementm, t);
        }
        BOOST_UBLAS_INLINE
        void append_element (size_type i, size_type j, const_reference t) {
            const size_type elementM = layout_type::index_M (i, j);
            const size_type elementm = layout_type::index_m (i, j);
            vector_data_value_type& vd (ref (data () [elementM]));
            storage_invariants ();
            return vd.append_element (elementm, t);
        }
        BOOST_UBLAS_INLINE
        void erase_element (size_type i, size_type j) {
            vectoriterator_type itv (data ().find (layout_type::index_M (i, j)));
            if (itv == data ().end ())
                return;
            (*itv).erase_element (layout_type::index_m (i, j));
            storage_invariants ();
        }
        BOOST_UBLAS_INLINE
        void clear () {
            const size_type sizeM = layout_type::size_M (size1_, size2_);
            // FIXME should clear data () if this is done via value_type/*zero*/() then it is not size preserving
            for (size_type i = 0; i < sizeM; ++ i)
                ref (data () [i]).clear ();
            storage_invariants ();
        }

        // Iterator types
    private:
        // Use vector iterator
        typedef typename A::const_iterator const_vectoriterator_type;
        typedef typename A::iterator vectoriterator_type;
        typedef typename A::value_type::const_iterator const_subiterator_type;
        typedef typename A::value_type::iterator subiterator_type;

        BOOST_UBLAS_INLINE
        true_reference at_element (size_type i, size_type j) {
            return ref (ref (data () [layout_type::index_M (i, j)]) [layout_type::index_m (i, j)]);
        }

    public:
        class const_iterator1;
        class iterator1;
        class const_iterator2;
        class iterator2;
        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base1<iterator1> reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;
        typedef reverse_iterator_base2<iterator2> reverse_iterator2;

        // Element lookup
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        const_iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) const {
            for (;;) {
                const_vectoriterator_type itv (data ().find (layout_type::index_M (i, j)));
                const_vectoriterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return const_iterator1 (*this, rank, i, j, itv_end, (*(-- itv)).end ());

                const_subiterator_type it ((*itv).find (layout_type::index_m (i, j)));
                const_subiterator_type it_end ((*itv).end ());
                if (rank == 0)
                    return const_iterator1 (*this, rank, i, j, itv, it);
                if (it != it_end && it.index () == layout_type::index_m (i, j))
                    return const_iterator1 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_i ()) {
                        if (it == it_end)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        i = it.index ();
                    } else {
                        if (i >= size1_)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        ++ i;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_i ()) {
                        if (it == (*itv).begin ())
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        --it;
                        i = it.index ();
                    } else {
                        if (i == 0)
                            return const_iterator1 (*this, rank, i, j, itv, it);
                        -- i;
                    }
                }
            }
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        iterator1 find1 (int rank, size_type i, size_type j, int direction = 1) {
            for (;;) {
                vectoriterator_type itv (data ().find (layout_type::index_M (i, j)));
                vectoriterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return iterator1 (*this, rank, i, j, itv_end, (*(-- itv)).end ());

                subiterator_type it ((*itv).find (layout_type::index_m (i, j)));
                subiterator_type it_end ((*itv).end ());
                if (rank == 0)
                    return iterator1 (*this, rank, i, j, itv, it);
                if (it != it_end && it.index () == layout_type::index_m (i, j))
                    return iterator1 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_i ()) {
                        if (it == it_end)
                            return iterator1 (*this, rank, i, j, itv, it);
                        i = it.index ();
                    } else {
                        if (i >= size1_)
                            return iterator1 (*this, rank, i, j, itv, it);
                        ++ i;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_i ()) {
                        if (it == (*itv).begin ())
                            return iterator1 (*this, rank, i, j, itv, it);
                        --it;
                        i = it.index ();
                    } else {
                        if (i == 0)
                            return iterator1 (*this, rank, i, j, itv, it);
                        -- i;
                    }
                }
            }
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        const_iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) const {
            for (;;) {
                const_vectoriterator_type itv (data ().find (layout_type::index_M (i, j)));
                const_vectoriterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return const_iterator2 (*this, rank, i, j, itv_end, (*(-- itv)).end ());

                const_subiterator_type it ((*itv).find (layout_type::index_m (i, j)));
                const_subiterator_type it_end ((*itv).end ());
                if (rank == 0)
                    return const_iterator2 (*this, rank, i, j, itv, it);
                if (it != it_end && it.index () == layout_type::index_m (i, j))
                    return const_iterator2 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_j ()) {
                        if (it == it_end)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        j = it.index ();
                    } else {
                        if (j >= size2_)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        ++ j;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_j ()) {
                        if (it == (*itv).begin ())
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        --it;
                        j = it.index ();
                    } else {
                        if (j == 0)
                            return const_iterator2 (*this, rank, i, j, itv, it);
                        -- j;
                    }
                }
            }
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        iterator2 find2 (int rank, size_type i, size_type j, int direction = 1) {
            for (;;) {
                vectoriterator_type itv (data ().find (layout_type::index_M (i, j)));
                vectoriterator_type itv_end (data ().end ());
                if (itv == itv_end)
                    return iterator2 (*this, rank, i, j, itv_end, (*(-- itv)).end ());

                subiterator_type it ((*itv).find (layout_type::index_m (i, j)));
                subiterator_type it_end ((*itv).end ());
                if (rank == 0)
                    return iterator2 (*this, rank, i, j, itv, it);
                if (it != it_end && it.index () == layout_type::index_m (i, j))
                    return iterator2 (*this, rank, i, j, itv, it);
                if (direction > 0) {
                    if (layout_type::fast_j ()) {
                        if (it == it_end)
                            return iterator2 (*this, rank, i, j, itv, it);
                        j = it.index ();
                    } else {
                        if (j >= size2_)
                            return iterator2 (*this, rank, i, j, itv, it);
                        ++ j;
                    }
                } else /* if (direction < 0)  */ {
                    if (layout_type::fast_j ()) {
                        if (it == (*itv).begin ())
                            return iterator2 (*this, rank, i, j, itv, it);
                        --it;
                        j = it.index ();
                    } else {
                        if (j == 0)
                            return iterator2 (*this, rank, i, j, itv, it);
                        -- j;
                    }
                }
            }
        }


        class const_iterator1:
            public container_const_reference<generalized_vector_of_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator1, value_type> {
        public:
            typedef typename generalized_vector_of_vector::difference_type difference_type;
            typedef typename generalized_vector_of_vector::value_type value_type;
            typedef typename generalized_vector_of_vector::const_reference reference;
            typedef const typename generalized_vector_of_vector::pointer pointer;

            typedef const_iterator2 dual_iterator_type;
            typedef const_reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator1 ():
                container_const_reference<self_type> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const self_type &m, int rank, size_type i, size_type j, const const_vectoriterator_type &itv, const const_subiterator_type &it):
                container_const_reference<self_type> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator1 (const iterator1 &it):
                container_const_reference<self_type> (it ()), rank_ (it.rank_), i_ (it.i_), j_ (it.j_), itv_ (it.itv_), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator1 &operator ++ () {
                if (rank_ == 1 && layout_type::fast_i ())
                    ++ it_;
                else {
                    const self_type &m = (*this) ();
                    i_ = index1 () + 1;
                    if (rank_ == 1 && ++ itv_ == m.end1 ().itv_) 
                        *this = m.find1 (rank_, i_, j_, 1);
                    else if (rank_ == 1) {
                        it_ = (*itv_).begin ();
                        if (it_ == (*itv_).end () || index2 () != j_)
                            *this = m.find1 (rank_, i_, j_, 1);
                    }
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator1 &operator -- () {
                if (rank_ == 1 && layout_type::fast_i ())
                    -- it_;
                else {
                    const self_type &m = (*this) ();
                    i_ = index1 () - 1;
                    if (rank_ == 1 && -- itv_ == m.end1 ().itv_)
                        *this = m.find1 (rank_, i_, j_, -1);
                    else if (rank_ == 1) {
                        it_ = (*itv_).begin ();
                        if (it_ == (*itv_).end () || index2 () != j_)
                            *this = m.find1 (rank_, i_, j_, -1);
                    } 
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                if (rank_ == 1) {
                    return *it_;
                } else {
                    return (*this) () (i_, j_);
                }
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 begin () const {
                const self_type &m = (*this) ();
                return m.find2 (1, index1 (), 0);
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 cbegin () const {
                return begin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 end () const {
                const self_type &m = (*this) ();
                return m.find2 (1, index1 (), m.size2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator2 cend () const {
                return end ();
            }

            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 rbegin () const {
                return const_reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 crbegin () const {
                return rbegin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 rend () const {
                return const_reverse_iterator2 (begin ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator2 crend () const {
                return rend ();
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().find1 (0, (*this) ().size1 (), j_), bad_index ());
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (layout_type::index_M (itv_.index (), it_.index ()) < (*this) ().size1 (), bad_index ());
                    return layout_type::index_M (itv_.index (), it_.index ());
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().find1 (0, (*this) ().size1 (), j_), bad_index ());
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (layout_type::index_m (itv_.index (), it_.index ()) < (*this) ().size2 (), bad_index ());
                    return layout_type::index_m (itv_.index (), it_.index ());
                } else {
                    return j_;
                }
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator1 &operator = (const const_iterator1 &it) {
                container_const_reference<self_type>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            const_vectoriterator_type itv_;
            const_subiterator_type it_;
        };

        BOOST_UBLAS_INLINE
        const_iterator1 begin1 () const {
            return find1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 cbegin1 () const {
            return begin1 ();
        }
        BOOST_UBLAS_INLINE
        const_iterator1 end1 () const {
            return find1 (0, size1_, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator1 cend1 () const {
            return end1 ();
        }

        class iterator1:
            public container_reference<generalized_vector_of_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator1, value_type> {
        public:
            typedef typename generalized_vector_of_vector::difference_type difference_type;
            typedef typename generalized_vector_of_vector::value_type value_type;
            typedef typename generalized_vector_of_vector::true_reference reference;
            typedef typename generalized_vector_of_vector::pointer pointer;

            typedef iterator2 dual_iterator_type;
            typedef reverse_iterator2 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator1 ():
                container_reference<self_type> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator1 (self_type &m, int rank, size_type i, size_type j, const vectoriterator_type &itv, const subiterator_type &it):
                container_reference<self_type> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator1 &operator ++ () {
                if (rank_ == 1 && layout_type::fast_i ())
                    ++ it_;
                else {
                    self_type &m = (*this) ();
                    i_ = index1 () + 1;
                    if (rank_ == 1 && ++ itv_ == m.end1 ().itv_)
                        *this = m.find1 (rank_, i_, j_, 1);
                    else if (rank_ == 1) {
                        it_ = (*itv_).begin ();
                        if (it_ == (*itv_).end () || index2 () != j_)
                            *this = m.find1 (rank_, i_, j_, 1);
                    }
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator1 &operator -- () {
                if (rank_ == 1 && layout_type::fast_i ())
                    -- it_;
                else {
                    self_type &m = (*this) ();
                    i_ = index1 () - 1;
                    if (rank_ == 1 && -- itv_ == m.end1 ().itv_)
                        *this = m.find1 (rank_, i_, j_, -1);
                    else if (rank_ == 1) {
                        it_ = (*itv_).begin ();
                        if (it_ == (*itv_).end () || index2 () != j_)
                            *this = m.find1 (rank_, i_, j_, -1);
                    }
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            true_reference operator * () const {
                BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                if (rank_ == 1) {
                    return *it_;
                } else {
                    return (*this) ().at_element (i_, j_);
                }
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator2 begin () const {
                self_type &m = (*this) ();
                return m.find2 (1, index1 (), 0);
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator2 end () const {
                self_type &m = (*this) ();
                return m.find2 (1, index1 (), m.size2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator2 rbegin () const {
                return reverse_iterator2 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator2 rend () const {
                return reverse_iterator2 (begin ());
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().find1 (0, (*this) ().size1 (), j_), bad_index ());
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (layout_type::index_M (itv_.index (), it_.index ()) < (*this) ().size1 (), bad_index ());
                    return layout_type::index_M (itv_.index (), it_.index ());
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().find1 (0, (*this) ().size1 (), j_), bad_index ());
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (layout_type::index_m (itv_.index (), it_.index ()) < (*this) ().size2 (), bad_index ());
                    return layout_type::index_m (itv_.index (), it_.index ());
                } else {
                    return j_;
                }
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator1 &operator = (const iterator1 &it) {
                container_reference<self_type>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator1 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            vectoriterator_type itv_;
            subiterator_type it_;
            
            friend class const_iterator1;
        };

        BOOST_UBLAS_INLINE
        iterator1 begin1 () {
            return find1 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator1 end1 () {
            return find1 (0, size1_, 0);
        }

        class const_iterator2:
            public container_const_reference<generalized_vector_of_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               const_iterator2, value_type> {
        public:
            typedef typename generalized_vector_of_vector::difference_type difference_type;
            typedef typename generalized_vector_of_vector::value_type value_type;
            typedef typename generalized_vector_of_vector::const_reference reference;
            typedef const typename generalized_vector_of_vector::pointer pointer;

            typedef const_iterator1 dual_iterator_type;
            typedef const_reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator2 ():
                container_const_reference<self_type> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const self_type &m, int rank, size_type i, size_type j, const const_vectoriterator_type &itv, const const_subiterator_type &it):
                container_const_reference<self_type> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}
            BOOST_UBLAS_INLINE
            const_iterator2 (const iterator2 &it):
                container_const_reference<self_type> (it ()), rank_ (it.rank_), i_ (it.i_), j_ (it.j_), itv_ (it.itv_), it_ (it.it_) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator2 &operator ++ () {
                if (rank_ == 1 && layout_type::fast_j ())
                    ++ it_;
                else {
                    const self_type &m = (*this) ();
                    j_ = index2 () + 1;
                    if (rank_ == 1 && ++ itv_ == m.end2 ().itv_) 
                        *this = m.find2 (rank_, i_, j_, 1);
                    else if (rank_ == 1) {
                        it_ = (*itv_).begin ();
                        if (it_ == (*itv_).end () || index1 () != i_)
                            *this = m.find2 (rank_, i_, j_, 1);
                    }
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator2 &operator -- () {
                if (rank_ == 1 && layout_type::fast_j ())
                    -- it_;
                else {
                    const self_type &m = (*this) ();
                    j_ = index2 () - 1;
                    if (rank_ == 1 && -- itv_ == m.end2 ().itv_)
                        *this = m.find2 (rank_, i_, j_, -1);
                    else if (rank_ == 1) {
                        it_ = (*itv_).begin ();
                        if (it_ == (*itv_).end () || index1 () != i_)
                            *this = m.find2 (rank_, i_, j_, -1);
                    }
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                if (rank_ == 1) {
                    return *it_;
                } else {
                    return (*this) () (i_, j_);
                }
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 begin () const {
                const self_type &m = (*this) ();
                return m.find1 (1, 0, index2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 cbegin () const {
                return begin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 end () const {
                const self_type &m = (*this) ();
                return m.find1 (1, m.size1 (), index2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_iterator1 cend () const {
                return end ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 rbegin () const {
                return const_reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 crbegin () const {
                return rbegin ();
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 rend () const {
                return const_reverse_iterator1 (begin ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            const_reverse_iterator1 crend () const {
                return rend ();
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().find2 (0, i_, (*this) ().size2 ()), bad_index ());
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (layout_type::index_M (itv_.index (), it_.index ()) < (*this) ().size1 (), bad_index ());
                    return layout_type::index_M (itv_.index (), it_.index ());
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().find2 (0, i_, (*this) ().size2 ()), bad_index ());
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (layout_type::index_m (itv_.index (), it_.index ()) < (*this) ().size2 (), bad_index ());
                    return layout_type::index_m (itv_.index (), it_.index ());
                } else {
                    return j_;
                }
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            const_iterator2 &operator = (const const_iterator2 &it) {
                container_const_reference<self_type>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            const_vectoriterator_type itv_;
            const_subiterator_type it_;
        };

        BOOST_UBLAS_INLINE
        const_iterator2 begin2 () const {
            return find2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 cbegin2 () const {
            return begin2 ();
        }
        BOOST_UBLAS_INLINE
        const_iterator2 end2 () const {
            return find2 (0, 0, size2_);
        }
        BOOST_UBLAS_INLINE
        const_iterator2 cend2 () const {
            return end2 ();
        }

        class iterator2:
            public container_reference<generalized_vector_of_vector>,
            public bidirectional_iterator_base<sparse_bidirectional_iterator_tag,
                                               iterator2, value_type> {
        public:
            typedef typename generalized_vector_of_vector::difference_type difference_type;
            typedef typename generalized_vector_of_vector::value_type value_type;
            typedef typename generalized_vector_of_vector::true_reference reference;
            typedef typename generalized_vector_of_vector::pointer pointer;

            typedef iterator1 dual_iterator_type;
            typedef reverse_iterator1 dual_reverse_iterator_type;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            iterator2 ():
                container_reference<self_type> (), rank_ (), i_ (), j_ (), itv_ (), it_ () {}
            BOOST_UBLAS_INLINE
            iterator2 (self_type &m, int rank, size_type i, size_type j, const vectoriterator_type &itv, const subiterator_type &it):
                container_reference<self_type> (m), rank_ (rank), i_ (i), j_ (j), itv_ (itv), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            iterator2 &operator ++ () {
                if (rank_ == 1 && layout_type::fast_j ())
                    ++ it_;
                else {
                    self_type &m = (*this) ();
                    j_ = index2 () + 1;
                    if (rank_ == 1 && ++ itv_ == m.end2 ().itv_)
                        *this = m.find2 (rank_, i_, j_, 1);
                    else if (rank_ == 1) {
                        it_ = (*itv_).begin ();
                        if (it_ == (*itv_).end () || index1 () != i_)
                            *this = m.find2 (rank_, i_, j_, 1);
                    }
                }
                return *this;
            }
            BOOST_UBLAS_INLINE
            iterator2 &operator -- () {
                if (rank_ == 1 && layout_type::fast_j ())
                    -- it_;
                else {
                    self_type &m = (*this) ();
                    j_ = index2 () - 1;
                    if (rank_ == 1 && -- itv_ == m.end2 ().itv_)
                        *this = m.find2 (rank_, i_, j_, -1);
                    else if (rank_ == 1) {
                        it_ = (*itv_).begin ();
                        if (it_ == (*itv_).end () || index1 () != i_)
                            *this = m.find2 (rank_, i_, j_, -1);
                    } 
                }
                return *this;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            true_reference operator * () const {
                BOOST_UBLAS_CHECK (index1 () < (*this) ().size1 (), bad_index ());
                BOOST_UBLAS_CHECK (index2 () < (*this) ().size2 (), bad_index ());
                if (rank_ == 1) {
                    return *it_;
                } else {
                    return (*this) ().at_element (i_, j_);
                }
            }

#ifndef BOOST_UBLAS_NO_NESTED_CLASS_RELATION
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator1 begin () const {
                self_type &m = (*this) ();
                return m.find1 (1, 0, index2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            iterator1 end () const {
                self_type &m = (*this) ();
                return m.find1 (1, m.size1 (), index2 ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator1 rbegin () const {
                return reverse_iterator1 (end ());
            }
            BOOST_UBLAS_INLINE
#ifdef BOOST_UBLAS_MSVC_NESTED_CLASS_RELATION
            typename self_type::
#endif
            reverse_iterator1 rend () const {
                return reverse_iterator1 (begin ());
            }
#endif

            // Indices
            BOOST_UBLAS_INLINE
            size_type index1 () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().find2 (0, i_, (*this) ().size2 ()), bad_index ());
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (layout_type::index_M (itv_.index (), it_.index ()) < (*this) ().size1 (), bad_index ());
                    return layout_type::index_M (itv_.index (), it_.index ());
                } else {
                    return i_;
                }
            }
            BOOST_UBLAS_INLINE
            size_type index2 () const {
                BOOST_UBLAS_CHECK (*this != (*this) ().find2 (0, i_, (*this) ().size2 ()), bad_index ());
                if (rank_ == 1) {
                    BOOST_UBLAS_CHECK (layout_type::index_m (itv_.index (), it_.index ()) < (*this) ().size2 (), bad_index ());
                    return layout_type::index_m (itv_.index (), it_.index ());
                } else {
                    return j_;
                }
            }

            // Assignment 
            BOOST_UBLAS_INLINE
            iterator2 &operator = (const iterator2 &it) {
                container_reference<self_type>::assign (&it ());
                rank_ = it.rank_;
                i_ = it.i_;
                j_ = it.j_;
                itv_ = it.itv_;
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const iterator2 &it) const {
                BOOST_UBLAS_CHECK (&(*this) () == &it (), external_logic ());
                // BOOST_UBLAS_CHECK (rank_ == it.rank_, internal_logic ());
                if (rank_ == 1 || it.rank_ == 1) {
                    return it_ == it.it_;
                } else {
                    return i_ == it.i_ && j_ == it.j_;
                }
            }

        private:
            int rank_;
            size_type i_;
            size_type j_;
            vectoriterator_type itv_;
            subiterator_type it_;

            friend class const_iterator2;
        };

        BOOST_UBLAS_INLINE
        iterator2 begin2 () {
            return find2 (0, 0, 0);
        }
        BOOST_UBLAS_INLINE
        iterator2 end2 () {
            return find2 (0, 0, size2_);
        }

        // Reverse iterators

        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rbegin1 () const {
            return const_reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 crbegin1 () const {
            return rbegin1 ();
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 rend1 () const {
            return const_reverse_iterator1 (begin1 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator1 crend1 () const {
            return rend1 ();
        }

        BOOST_UBLAS_INLINE
        reverse_iterator1 rbegin1 () {
            return reverse_iterator1 (end1 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator1 rend1 () {
            return reverse_iterator1 (begin1 ());
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rbegin2 () const {
            return const_reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 crbegin2 () const {
            return rbegin2 ();
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 rend2 () const {
            return const_reverse_iterator2 (begin2 ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator2 crend2 () const {
            return rend2 ();
        }

        BOOST_UBLAS_INLINE
        reverse_iterator2 rbegin2 () {
            return reverse_iterator2 (end2 ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator2 rend2 () {
            return reverse_iterator2 (begin2 ());
        }

         // Serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */){
        
            // we need to copy to a collection_size_type to get a portable
            // and efficient serialization
            serialization::collection_size_type s1 (size1_);
            serialization::collection_size_type s2 (size2_);
          
            // serialize the sizes
            ar & serialization::make_nvp("size1",s1)
               & serialization::make_nvp("size2",s2);

            // copy the values back if loading
            if (Archive::is_loading::value) {
                size1_ = s1;
                size2_ = s2;
            }

            ar & serialization::make_nvp("data", data_);

            storage_invariants();
        }

    private:
        void storage_invariants () const
        {
            BOOST_UBLAS_CHECK (layout_type::size_M (size1_, size2_) + 1 == data_.size (), internal_logic ());
            BOOST_UBLAS_CHECK (data ().begin () != data ().end (), internal_logic ());

        }
        size_type size1_;
        size_type size2_;
        array_type data_;
        static const value_type zero_;
    };

    template<class T, class L, class A>
    const typename generalized_vector_of_vector<T, L, A>::value_type generalized_vector_of_vector<T, L, A>::zero_ = value_type/*zero*/();

}}}

#endif

/* vector_of_vector.hpp
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
*/