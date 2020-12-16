//
//  Copyright (c) 2009
//  Gunter Winkler
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//

#ifndef _BOOST_UBLAS_SPARSE_VIEW_
#define _BOOST_UBLAS_SPARSE_VIEW_

#include <boost/numeric/ublas/matrix_expression.hpp>
#include <boost/numeric/ublas/detail/matrix_assign.hpp>
#if BOOST_UBLAS_TYPE_CHECK
#include <boost/numeric/ublas/matrix.hpp>
#endif

#include <boost/next_prior.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/numeric/ublas/storage.hpp>

namespace boost { namespace numeric { namespace ublas {

    // view a chunk of memory as ublas array

    template < class T >
    class c_array_view
        : public storage_array< c_array_view<T> > {
    private:
        typedef c_array_view<T> self_type;
        typedef T * pointer;

    public:
        // TODO: think about a const pointer
        typedef const pointer array_type;

        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;

        typedef T value_type;
        typedef const T  &const_reference;
        typedef const T  *const_pointer;

        typedef const_pointer const_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        //
        // typedefs required by vector concept
        //

        typedef dense_tag  storage_category;
        typedef const vector_reference<const self_type>    const_closure_type;

        c_array_view(size_type size, array_type data) :
            size_(size), data_(data)
        {}

        ~c_array_view()
        {}

        //
        // immutable methods of container concept
        //

        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return data_ + size_;
        }

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }

    private:
        size_type  size_;
        array_type data_;
    };


    /** \brief Present existing arrays as compressed array based
     *  sparse matrix.
     *  This class provides CRS / CCS storage layout.
     *
     *  see also http://www.netlib.org/utk/papers/templates/node90.html
     *
     *       \param L layout type, either row_major or column_major
     *       \param IB index base, use 0 for C indexing and 1 for
     *       FORTRAN indexing of the internal index arrays. This
     *       does not affect the operator()(int,int) where the first
     *       row/column has always index 0.
     *       \param IA index array type, e.g., int[]
     *       \param TA value array type, e.g., double[]
     */
    template<class L, std::size_t IB, class IA, class JA, class TA>
    class compressed_matrix_view:
        public matrix_expression<compressed_matrix_view<L, IB, IA, JA, TA> > {

    public:
        typedef typename vector_view_traits<TA>::value_type value_type;

    private:
        typedef value_type &true_reference;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef L layout_type;
        typedef compressed_matrix_view<L, IB, IA, JA, TA> self_type;

    public:
#ifdef BOOST_UBLAS_ENABLE_PROXY_SHORTCUTS
        using matrix_expression<self_type>::operator ();
#endif
        // ISSUE require type consistency check
        // is_convertable (IA::size_type, TA::size_type)
        typedef typename boost::remove_cv<typename vector_view_traits<JA>::value_type>::type index_type;
        // for compatibility, should be removed some day ...
        typedef index_type size_type;
        // size_type for the data arrays.
        typedef typename vector_view_traits<JA>::size_type array_size_type;
        typedef typename vector_view_traits<JA>::difference_type difference_type;
        typedef const value_type & const_reference;

        // do NOT define reference type, because class is read only
        // typedef value_type & reference;

        typedef IA rowptr_array_type;
        typedef JA index_array_type;
        typedef TA value_array_type;
        typedef const matrix_reference<const self_type> const_closure_type;
        typedef matrix_reference<self_type> closure_type;

        // FIXME: define a corresponding temporary type
        // typedef compressed_vector<T, IB, IA, TA> vector_temporary_type;

        // FIXME: define a corresponding temporary type
        // typedef self_type matrix_temporary_type;

        typedef sparse_tag storage_category;
        typedef typename L::orientation_category orientation_category;

        //
        // private types for internal use
        //

    private:
        typedef typename vector_view_traits<index_array_type>::const_iterator const_subiterator_type;

        //
        // Construction and destruction
        //
    private:
        /// private default constructor because data must be filled by caller
        BOOST_UBLAS_INLINE
        compressed_matrix_view () { }

    public:
        BOOST_UBLAS_INLINE
        compressed_matrix_view (index_type n_rows, index_type n_cols, array_size_type nnz
                                , const rowptr_array_type & iptr
                                , const index_array_type & jptr
                                , const value_array_type & values):
            matrix_expression<self_type> (),
            size1_ (n_rows), size2_ (n_cols), 
            nnz_ (nnz),
            index1_data_ (iptr), 
            index2_data_ (jptr), 
            value_data_ (values) {
            storage_invariants ();
        }

        BOOST_UBLAS_INLINE
        compressed_matrix_view(const compressed_matrix_view& o) :
            size1_(o.size1_), size2_(o.size2_),
            nnz_(o.nnz_),
            index1_data_(o.index1_data_),
            index2_data_(o.index2_data_),
            value_data_(o.value_data_)
        {}

        //
        // implement immutable iterator types
        //

        class const_iterator1 {};
        class const_iterator2 {};

        typedef reverse_iterator_base1<const_iterator1> const_reverse_iterator1;
        typedef reverse_iterator_base2<const_iterator2> const_reverse_iterator2;

        //
        // implement all read only methods for the matrix expression concept
        // 

        //! return the number of rows 
        index_type size1() const {
            return size1_;
        }

        //! return the number of columns
        index_type size2() const {
            return size2_;
        }

        //! return value at position (i,j)
        value_type operator()(index_type i, index_type j) const {
            const_pointer p = find_element(i,j);
            if (!p) {
                return zero_;
            } else {
                return *p;
            }
        }
        

    private:
        //
        // private helper functions
        //

        const_pointer find_element (index_type i, index_type j) const {
            index_type element1 (layout_type::index_M (i, j));
            index_type element2 (layout_type::index_m (i, j));

            const array_size_type itv      = zero_based( index1_data_[element1] );
            const array_size_type itv_next = zero_based( index1_data_[element1+1] );

            const_subiterator_type it_start = boost::next(vector_view_traits<index_array_type>::begin(index2_data_),itv);
            const_subiterator_type it_end = boost::next(vector_view_traits<index_array_type>::begin(index2_data_),itv_next);
            const_subiterator_type it = find_index_in_row(it_start, it_end, element2) ;
            
            if (it == it_end || *it != k_based (element2))
                return 0;
            return &value_data_ [it - vector_view_traits<index_array_type>::begin(index2_data_)];
        }

        const_subiterator_type find_index_in_row(const_subiterator_type it_start
                                                 , const_subiterator_type it_end
                                                 , index_type index) const {
            return std::lower_bound( it_start
                                     , it_end
                                     , k_based (index) );
        }


    private:
        void storage_invariants () const {
            BOOST_UBLAS_CHECK (index1_data_ [layout_type::size_M (size1_, size2_)] == k_based (nnz_), external_logic ());
        }
        
        index_type size1_;
        index_type size2_;

        array_size_type nnz_;

        const rowptr_array_type & index1_data_;
        const index_array_type & index2_data_;
        const value_array_type & value_data_;

        static const value_type zero_;

        BOOST_UBLAS_INLINE
        static index_type zero_based (index_type k_based_index) {
            return k_based_index - IB;
        }
        BOOST_UBLAS_INLINE
        static index_type k_based (index_type zero_based_index) {
            return zero_based_index + IB;
        }

        friend class iterator1;
        friend class iterator2;
        friend class const_iterator1;
        friend class const_iterator2;
    };

    template<class L, std::size_t IB, class IA, class JA, class TA  >
    const typename compressed_matrix_view<L,IB,IA,JA,TA>::value_type 
    compressed_matrix_view<L,IB,IA,JA,TA>::zero_ = value_type/*zero*/();


    template<class L, std::size_t IB, class IA, class JA, class TA  >
    compressed_matrix_view<L,IB,IA,JA,TA>
    make_compressed_matrix_view(typename vector_view_traits<JA>::value_type n_rows
                                , typename vector_view_traits<JA>::value_type n_cols
                                , typename vector_view_traits<JA>::size_type nnz
                                , const IA & ia
                                , const JA & ja
                                , const TA & ta) {

        return compressed_matrix_view<L,IB,IA,JA,TA>(n_rows, n_cols, nnz, ia, ja, ta);

    }

}}}

#endif

/* sparse_view.hpp
PXHjRfRtPIB0ZMcYXVAYVUNLo38b49oPJxxN0AsWdl1401MKM21xWLJoqdDAoEsQJ1oK6q65ZWrj3PtKOjwTJ6lVMMwp5clRuNh6ct2tKP80hUJl6c6iQBg63Huutp48Hwl0mJE2joTobe6YtbJl6wlbZ9K6MB2x5K2zdbY8JS5f/cOAEQmJIGLYG+qvGAvQUZ3WjvTqgnSkSRYdoaWu3caq/heNhIFpaJxnydGeDoSwu0SnjbSsa0+PsPYoh1dJfebR1KEnj+qQsFtH6O6Q1iWGw5RsSEGZ/5l0Dh1dOrvSDJs1Ckk351EhaOqvH+tIRyBvncAgfdDB8wHje8xMaBkiTAcWTRPtSQsX9NS6gHFnBx6r/KRBrbekk7wnE60NKq4+hpTrQwd/g0+4aXG1iawPisntTJcOaoUzEO2000yPnUQRRhixTpvscOnBbouJpeG5PuOKiROKvj7E4NKB6ZFyQ4eBQckaf3Ucq09UdnMOnCgpIYOjbioH6HvEng5PcPucqlsfzZ5C9QQHuAJt7rDZpdgOG7pFcdR1Mg6VTvWzWM9BS9u3Pn16x60LY6qJljJLV+GhLtd4Nez4UlBrbKxswkL8oxUsa8Sr8NZigIUTDUp4/lKbJ0qHmv258Pz7ZBbOUKnQbjxF3cJTf6QXhJ1YK//DdGjv1VEvmQkx+sSahTGPE9jy4hNtljyN73X4qB3VO4B2cQ9wwT6JG2dHzcRTDVFuQQxJF52WxHaIs/aaevhc0MLrYLhbc43X/XMYNia6IVPensTYGF3/TAwNSixZ1/knwtG7TL54d8cYbthnrG3/zZ5H9ziuZUkHXvU8tg7+4m4mj6aNxhnhWOpxQrA6jR1+Wr2Mje8zzXXvYmMo66hkhGF0b4IxD22cUfcqExp4G9NnWZRho4lMe6qt3YGlahSGofGcwBRThRidInW0UIYO3YpbOLtlsnGhnhJWZL4t7269NU6tkprTaVtHT16shYXi9AlCG+fuAWwdlEpOHWYvQDiz1LkxOk81zn6JJgxr1NOeqROm05smtoxVF0muYOGeBuW8bqHWYMnY4Y9ZtxwyZl0wE1LMH4N5K62PjsdARJv5QILRfQbqigdtHk9vifbzbhnKJ91pbj2eJ+7irqgQd2svBprfmy7Qvj9pKi4gX+Pj1f8zJaIIv5DGgVehd2yMPyfHV+3yPb2+6Wi4mf7RmfEJp0136EMYnBprTFdcW1B8PDpbCt7Hk+tHM7mZ9/vcoF7b47xxPm7pn8l/+dt6/ehGQ2qmUVNd4wV1jQsWzVvsz1vc6PcfNt4IGAp4nsn1cr9hdiNulVlS19gk3NQ0nO6FOR0JiQYpdBJI0qaceLOLtxe+0V7I07fcSz1gpHpihMXsR1XbiOPktILDX3qhXtvhX6/DwXbY1W5DIOKWMaPZp5w5SmLF69SHhfvB6JWwoNV2y4rm0Z02ZgD6TUczYk7Z3u/HOfWGvMvplNV574ivS5UtZ6qx3czi4gpH4XubDhmzUBWRTk6/zAQvQo8OlUPWLjkuObvwuNOq/zoh5IqrE66iQ232RJIRaSpdrfgqOYqDW1D4W9fYiPsSGhc1cPuSC5uWiN+5TfTbqH4VX8g1LFi0YIlP+MXn+yQ/X8qp37ny9/w6oadR2mulfrjTL9zp9wLFb6LfeQsWkTzs9As78edLPdw/Cq/6nSt/lb5GYSf/SI/8VeEh/2qhhxtqLxS/Sxedf+EixIcvzaiVpdZ4nlY1LwTN4zKguQgMv+NrDqgWzPmgRXNhBy0Fcd/n1oEgvKABMuA1LoZ9Nv8+EuzcbTnuFIBcwwWQaQKBt7QJesBbyt0X8/BAJ+xz5sPcADqfv+uaztFLjFQ=
*/