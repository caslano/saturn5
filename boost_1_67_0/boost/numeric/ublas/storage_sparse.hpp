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

#ifndef _BOOST_UBLAS_STORAGE_SPARSE_
#define _BOOST_UBLAS_STORAGE_SPARSE_

#include <map>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/base_object.hpp>

#include <boost/numeric/ublas/storage.hpp>


namespace boost { namespace numeric { namespace ublas {

    namespace detail {

        template<class I, class T, class C>
        BOOST_UBLAS_INLINE
        I lower_bound (const I &begin, const I &end, const T &t, C compare) {
            // t <= *begin <=> ! (*begin < t)
            if (begin == end || ! compare (*begin, t))
                return begin;
            if (compare (*(end - 1), t))
                return end;
            return std::lower_bound (begin, end, t, compare);
        }
        template<class I, class T, class C>
        BOOST_UBLAS_INLINE
        I upper_bound (const I &begin, const I &end, const T &t, C compare) {
            if (begin == end || compare (t, *begin))
                return begin;
            // (*end - 1) <= t <=> ! (t < *end)
            if (! compare (t, *(end - 1)))
                return end;
            return std::upper_bound (begin, end, t, compare);
        }

        template<class P>
        struct less_pair {
            BOOST_UBLAS_INLINE
            bool operator () (const P &p1, const P &p2) {
                return p1.first < p2.first;
            }
        };
        template<class T>
        struct less_triple {
            BOOST_UBLAS_INLINE
            bool operator () (const T &t1, const T &t2) {
                return t1.first.first < t2.first.first ||
                       (t1.first.first == t2.first.first && t1.first.second < t2.first.second);
            }
        };

    }

#ifdef BOOST_UBLAS_STRICT_MAP_ARRAY
    template<class A>
    class sparse_storage_element:
       public container_reference<A> {
    public:
        typedef A array_type;
        typedef typename A::key_type index_type;
        typedef typename A::mapped_type data_value_type;
        // typedef const data_value_type &data_const_reference;
        typedef typename type_traits<data_value_type>::const_reference data_const_reference;
        typedef data_value_type &data_reference;
        typedef typename A::value_type value_type;
        typedef value_type *pointer;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        sparse_storage_element (array_type &a, pointer it):
            container_reference<array_type> (a), it_ (it), i_ (it->first), d_ (it->second), dirty_ (false) {}
        BOOST_UBLAS_INLINE
        sparse_storage_element (array_type &a, index_type i):
            container_reference<array_type> (a), it_ (), i_ (i), d_ (), dirty_ (false) {
            pointer it = (*this) ().find (i_);
            if (it == (*this) ().end ())
                it = (*this) ().insert ((*this) ().end (), value_type (i_, d_));
            d_ = it->second;
        }
        BOOST_UBLAS_INLINE
        ~sparse_storage_element () {
            if (dirty_) {
                if (! it_)
                    it_ = (*this) ().find (i_);
                BOOST_UBLAS_CHECK (it_ != (*this) ().end (), internal_logic ());
                it_->second = d_;
            }
        }

        // Element access - only if data_const_reference is defined
        BOOST_UBLAS_INLINE
        typename data_value_type::data_const_reference
        operator [] (index_type i) const {
            return d_ [i];
        }

        // Assignment
        BOOST_UBLAS_INLINE
        sparse_storage_element &operator = (const sparse_storage_element &p) {
            // Overide the implict copy assignment
            d_ = p.d_;
            dirty_ = true;
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_storage_element &operator = (const D &d) {
            d_ = d;
            dirty_ = true;
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_storage_element &operator += (const D &d) {
            d_ += d;
            dirty_ = true;
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_storage_element &operator -= (const D &d) {
            d_ -= d;
            dirty_ = true;
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_storage_element &operator *= (const D &d) {
            d_ *= d;
            dirty_ = true;
            return *this;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        sparse_storage_element &operator /= (const D &d) {
            d_ /= d;
            dirty_ = true;
            return *this;
        }

        // Comparison
        template<class D>
        BOOST_UBLAS_INLINE
        bool operator == (const D &d) const {
            return d_ == d;
        }
        template<class D>
        BOOST_UBLAS_INLINE
        bool operator != (const D &d) const {
            return d_ != d;
        }

        // Conversion
        BOOST_UBLAS_INLINE
        operator data_const_reference () const {
            return d_;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (sparse_storage_element p) {
            if (this != &p) {
                dirty_ = true;
                p.dirty_ = true;
                std::swap (d_, p.d_);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (sparse_storage_element p1, sparse_storage_element p2) {
            p1.swap (p2);
        }

    private:
        pointer it_;
        index_type i_;
        data_value_type d_;
        bool dirty_;
    };
#endif


    // Default map type is simply forwarded to std::map
    template<class I, class T, class ALLOC>
    class map_std : public std::map<I, T, std::less<I>, ALLOC> {
    public:
         // Serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */){
            ar & serialization::make_nvp("base", boost::serialization::base_object< std::map<I, T, std::less<I>, ALLOC> >(*this));
        }
    };

    


    // Map array
    //  Implementation requires pair<I, T> allocator definition (without const)
    template<class I, class T, class ALLOC>
    class map_array {
    public:
        typedef ALLOC allocator_type;
        typedef typename ALLOC::size_type size_type;
        typedef typename ALLOC::difference_type difference_type;
        typedef std::pair<I,T> value_type;
        typedef I key_type;
        typedef T mapped_type;
        typedef const value_type &const_reference;
        typedef value_type &reference;
        typedef const value_type *const_pointer;
        typedef value_type *pointer;
        // Iterators simply are pointers.
        typedef const_pointer const_iterator;
        typedef pointer iterator;

        typedef const T &data_const_reference;
#ifndef BOOST_UBLAS_STRICT_MAP_ARRAY
        typedef T &data_reference;
#else
        typedef sparse_storage_element<map_array> data_reference;
#endif

        // Construction and destruction
        BOOST_UBLAS_INLINE
        map_array (const ALLOC &a = ALLOC()):
            alloc_(a), capacity_ (0), size_ (0) {
                data_ = 0;
        }
        BOOST_UBLAS_INLINE
        map_array (const map_array &c):
            alloc_ (c.alloc_), capacity_ (c.size_), size_ (c.size_) {
            if (capacity_) {
                data_ = alloc_.allocate (capacity_);
                std::uninitialized_copy (data_, data_ + capacity_, c.data_);
                // capacity != size_ requires uninitialized_fill (size_ to capacity_)
            }
            else
                data_ = 0;
        }
        BOOST_UBLAS_INLINE
        ~map_array () {
            if (capacity_) {
                std::for_each (data_, data_ + capacity_, static_destroy);
                alloc_.deallocate (data_, capacity_);
            }
        }

    private:
        // Resizing - implicitly exposses uninitialized (but default constructed) mapped_type
        BOOST_UBLAS_INLINE
        void resize (size_type size) {
            BOOST_UBLAS_CHECK (size_ <= capacity_, internal_logic ());
            if (size > capacity_) {
                const size_type capacity = size << 1;
                BOOST_UBLAS_CHECK (capacity, internal_logic ());
                pointer data = alloc_.allocate (capacity);
                std::uninitialized_copy (data_, data_ + (std::min) (size, size_), data);
                std::uninitialized_fill (data + (std::min) (size, size_), data + capacity, value_type ());

                if (capacity_) {
                    std::for_each (data_, data_ + capacity_, static_destroy);
                    alloc_.deallocate (data_, capacity_);
                }
                capacity_ = capacity;
                data_ = data;
            }
            size_ = size;
            BOOST_UBLAS_CHECK (size_ <= capacity_, internal_logic ());
        }
    public:

        // Reserving
        BOOST_UBLAS_INLINE
        void reserve (size_type capacity) {
            BOOST_UBLAS_CHECK (size_ <= capacity_, internal_logic ());
            // Reduce capacity_ if size_ allows
            BOOST_UBLAS_CHECK (capacity >= size_, bad_size ());
            pointer data;
            if (capacity) {
                data = alloc_.allocate (capacity);
                std::uninitialized_copy (data_, data_ + size_, data);
                std::uninitialized_fill (data + size_, data + capacity, value_type ());
            }
            else
                data = 0;
                
            if (capacity_) {
                std::for_each (data_, data_ + capacity_, static_destroy);
                alloc_.deallocate (data_, capacity_);
            }
            capacity_ = capacity;
            data_ = data;
            BOOST_UBLAS_CHECK (size_ <= capacity_, internal_logic ());
        }

        // Random Access Container
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }
        BOOST_UBLAS_INLINE
        size_type capacity () const {
            return capacity_;
        }
        BOOST_UBLAS_INLINE
        size_type max_size () const {
            return 0; //TODO
        }
       
        BOOST_UBLAS_INLINE
        bool empty () const {
            return size_ == 0;
        }
            
        // Element access
        BOOST_UBLAS_INLINE
        data_reference operator [] (key_type i) {
#ifndef BOOST_UBLAS_STRICT_MAP_ARRAY
            pointer it = find (i);
            if (it == end ())
                it = insert (end (), value_type (i, mapped_type (0)));
            BOOST_UBLAS_CHECK (it != end (), internal_logic ());
            return it->second;
#else
            return data_reference (*this, i);
#endif
        }

        // Assignment
        BOOST_UBLAS_INLINE
        map_array &operator = (const map_array &a) {
            if (this != &a) {
                resize (a.size_);
                std::copy (a.data_, a.data_ + a.size_, data_);
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        map_array &assign_temporary (map_array &a) {
            swap (a);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (map_array &a) {
            if (this != &a) {
                std::swap (capacity_, a.capacity_);
                std::swap (data_, a.data_);
                std::swap (size_, a.size_);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (map_array &a1, map_array &a2) {
            a1.swap (a2);
        }

        // Element insertion and deletion
        
        // From Back Insertion Sequence concept
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        iterator push_back (iterator it, const value_type &p) {
            if (size () == 0 || (it = end () - 1)->first < p.first) {
                resize (size () + 1);
                *(it = end () - 1) = p;
                return it;
            }
            external_logic ().raise ();
            return it;
        }
        // Form Unique Associative Container concept
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        std::pair<iterator,bool> insert (const value_type &p) {
            iterator it = detail::lower_bound (begin (), end (), p, detail::less_pair<value_type> ());
            if (it != end () && it->first == p.first)
                return std::make_pair (it, false);
            difference_type n = it - begin ();
            resize (size () + 1);
            it = begin () + n;    // allow for invalidation
            std::copy_backward (it, end () - 1, end ());
            *it = p;
            return std::make_pair (it, true);
        }
        // Form Sorted Associative Container concept
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
				iterator insert (iterator /*hint*/, const value_type &p) {
            return insert (p).first;
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        void erase (iterator it) {
            BOOST_UBLAS_CHECK (begin () <= it && it < end (), bad_index ());
            std::copy (it + 1, end (), it);
            resize (size () - 1);
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        void erase (iterator it1, iterator it2) {
            if (it1 == it2) return /* nothing to erase */;
            BOOST_UBLAS_CHECK (begin () <= it1 && it1 < it2 && it2 <= end (), bad_index ());
            std::copy (it2, end (), it1);
            resize (size () - (it2 - it1));
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        void clear () {
            resize (0);
        }

        // Element lookup
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        const_iterator find (key_type i) const {
            const_iterator it (detail::lower_bound (begin (), end (), value_type (i, mapped_type (0)), detail::less_pair<value_type> ()));
            if (it == end () || it->first != i)
                it = end ();
            return it;
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        iterator find (key_type i) {
            iterator it (detail::lower_bound (begin (), end (), value_type (i, mapped_type (0)), detail::less_pair<value_type> ()));
            if (it == end () || it->first != i)
                it = end ();
            return it;
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        const_iterator lower_bound (key_type i) const {
            return detail::lower_bound (begin (), end (), value_type (i, mapped_type (0)), detail::less_pair<value_type> ());
        }
        // BOOST_UBLAS_INLINE This function seems to be big. So we do not let the compiler inline it.    
        iterator lower_bound (key_type i) {
            return detail::lower_bound (begin (), end (), value_type (i, mapped_type (0)), detail::less_pair<value_type> ());
        }

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return data_ + size_;
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

        BOOST_UBLAS_INLINE
        iterator begin () {
            return data_;
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return data_ + size_;
        }

        // Reverse iterators
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;

        BOOST_UBLAS_INLINE
        const_reverse_iterator rbegin () const {
            return const_reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator crbegin () const {
            return rbegin ();
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator rend () const {
            return const_reverse_iterator (begin ());
        }
        BOOST_UBLAS_INLINE
        const_reverse_iterator crend () const {
            return rend ();
        }

        BOOST_UBLAS_INLINE
        reverse_iterator rbegin () {
            return reverse_iterator (end ());
        }
        BOOST_UBLAS_INLINE
        reverse_iterator rend () {
            return reverse_iterator (begin ());
        }

        // Allocator
        allocator_type get_allocator () {
            return alloc_;
        }

         // Serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /* file_version */){
            serialization::collection_size_type s (size_);
            ar & serialization::make_nvp("size",s);
            if (Archive::is_loading::value) {
                resize(s);
            }
            ar & serialization::make_array(data_, s);
        }

    private:
        // Provide destroy as a non member function
        BOOST_UBLAS_INLINE
        static void static_destroy (reference p) {
            (&p) -> ~value_type ();
        }
        ALLOC alloc_;
        size_type capacity_;
        pointer data_;
        size_type size_;
    };


    namespace detail {
        template<class A, class T>
        struct map_traits {
            typedef typename A::mapped_type &reference;
        };
        template<class I, class T, class ALLOC>
        struct map_traits<map_array<I, T, ALLOC>, T > {
            typedef typename map_array<I, T, ALLOC>::data_reference reference;
        };

        // reserve helpers for map_array and generic maps
        // ISSUE should be in map_traits but want to use on all compilers

        template<class M>
        BOOST_UBLAS_INLINE
        void map_reserve (M &/* m */, typename M::size_type /* capacity */) {
        }
        template<class I, class T, class ALLOC>
        BOOST_UBLAS_INLINE
        void map_reserve (map_array<I, T, ALLOC> &m, typename map_array<I, T, ALLOC>::size_type capacity) {
            m.reserve (capacity);
        }

        template<class M>
        struct map_capacity_traits {
            typedef typename M::size_type type ;
            type operator() ( M const& m ) const {
               return m.size ();
            }
        } ;

        template<class I, class T, class ALLOC>
        struct map_capacity_traits< map_array<I, T, ALLOC> > {
            typedef typename map_array<I, T, ALLOC>::size_type type ;
            type operator() ( map_array<I, T, ALLOC> const& m ) const {
               return m.capacity ();
            }
        } ;

        template<class M>
        BOOST_UBLAS_INLINE
        typename map_capacity_traits<M>::type map_capacity (M const& m) {
            return map_capacity_traits<M>() ( m );
        }
    }

}}}

#endif

/* storage_sparse.hpp
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
*/