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
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
*/