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
        typedef typename boost::allocator_size_type<ALLOC>::type size_type;
        typedef typename boost::allocator_difference_type<ALLOC>::type difference_type;
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