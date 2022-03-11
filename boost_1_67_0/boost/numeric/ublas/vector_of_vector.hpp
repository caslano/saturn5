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