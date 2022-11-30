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

#ifndef BOOST_UBLAS_STORAGE_H
#define BOOST_UBLAS_STORAGE_H

#include <algorithm>
#ifdef BOOST_UBLAS_SHALLOW_ARRAY_ADAPTOR
#include <boost/shared_array.hpp>
#endif

#include <boost/core/allocator_access.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/numeric/ublas/exception.hpp>
#include <boost/numeric/ublas/traits.hpp>
#include <boost/numeric/ublas/detail/iterator.hpp>


namespace boost { namespace numeric { namespace ublas {


    // Base class for Storage Arrays - see the Barton Nackman trick
    template<class E>
    class storage_array:
        private nonassignable {
    };


    // Unbounded array - with allocator
    template<class T, class ALLOC>
    class unbounded_array:
        public storage_array<unbounded_array<T, ALLOC> > {

        typedef unbounded_array<T, ALLOC> self_type;
    public:
        typedef ALLOC allocator_type;
        typedef typename boost::allocator_size_type<ALLOC>::type size_type;
        typedef typename boost::allocator_difference_type<ALLOC>::type difference_type;
        typedef T value_type;
        typedef const T &const_reference;
        typedef T &reference;
        typedef const T *const_pointer;
        typedef T *pointer;
        typedef const_pointer const_iterator;
        typedef pointer iterator;

        // Construction and destruction
        explicit BOOST_UBLAS_INLINE
        unbounded_array (const ALLOC &a = ALLOC()):
            alloc_ (a), size_ (0) {
            data_ = 0;
        }
        explicit BOOST_UBLAS_INLINE
        unbounded_array (size_type size, const ALLOC &a = ALLOC()):
            alloc_(a), size_ (size) {
          if (size_) {
              data_ = alloc_.allocate (size_);
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
              if (! detail::has_trivial_constructor<T>::value) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                  for (pointer d = data_; d != data_ + size_; ++d)
                      boost::allocator_construct(alloc_, d);
              }
          }
          else
              data_ = 0;
        }
        // No value initialised, but still be default constructed
        BOOST_UBLAS_INLINE
        unbounded_array (size_type size, const value_type &init, const ALLOC &a = ALLOC()):
            alloc_ (a), size_ (size) {
            if (size_) {
                data_ = alloc_.allocate (size_);
                std::uninitialized_fill (begin(), end(), init);
            }
            else
                data_ = 0;
        }
        BOOST_UBLAS_INLINE
        unbounded_array (const unbounded_array &c):
            storage_array<unbounded_array<T, ALLOC> >(),
            alloc_ (c.alloc_), size_ (c.size_) {
            if (size_) {
                data_ = alloc_.allocate (size_);
                std::uninitialized_copy (c.begin(), c.end(), begin());
            }
            else
                data_ = 0;
        }
#ifdef BOOST_UBLAS_CPP_GE_2011
		BOOST_UBLAS_INLINE
		unbounded_array (unbounded_array &&c) :
			storage_array<unbounded_array<T, ALLOC> >(),
			alloc_ (std::move(c.alloc_)), size_ (c.size_), data_(c.data_)
		{
			c.size_ = 0;
			c.data_ = nullptr;
		}
#endif
        BOOST_UBLAS_INLINE
        ~unbounded_array () {
            if (size_) {
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                if (! detail::has_trivial_destructor<T>::value) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                    // std::_Destroy (begin(), end(), alloc_);
                    const iterator i_end = end();
                    for (iterator i = begin (); i != i_end; ++i) {
                        iterator_destroy (i); 
                    }
                }
                alloc_.deallocate (data_, size_);
            }
        }

        // Resizing
    private:
        BOOST_UBLAS_INLINE
        void resize_internal (const size_type size, const value_type init, const bool preserve) {
            if (size != size_) {
                pointer p_data = data_;
                if (size) {
                    data_ = alloc_.allocate (size);
                    if (preserve) {
                        pointer si = p_data;
                        pointer di = data_;
                        if (size < size_) {
                            for (; di != data_ + size; ++di) {
                                boost::allocator_construct(alloc_, di, *si);
                                ++si;
                            }
                        }
                        else {
                            for (; si != p_data + size_; ++si) {
                                boost::allocator_construct(alloc_, di, *si);
                                ++di;
                            }
                            for (; di != data_ + size; ++di) {
                                boost::allocator_construct(alloc_, di, init);
                            }
                        }
                    }
                    else {
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                        if (! detail::has_trivial_constructor<T>::value) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                            for (pointer di = data_; di != data_ + size; ++di)
                                boost::allocator_construct(alloc_, di);
                        }
                    }
                }

                if (size_) {
//Disabled warning C4127 because the conditional expression is constant
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4127)
#endif
                    if (! detail::has_trivial_destructor<T>::value) {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
                        for (pointer si = p_data; si != p_data + size_; ++si)
                            boost::allocator_destroy(alloc_, si);
                    }
                    alloc_.deallocate (p_data, size_);
                }

                if (!size)
                    data_ = 0;
                size_ = size;
            }
        }
    public:
        BOOST_UBLAS_INLINE
        void resize (size_type size) {
            resize_internal (size, value_type (), false);
        }
        BOOST_UBLAS_INLINE
        void resize (size_type size, value_type init) {
            resize_internal (size, init, true);
        }
                    
        // Random Access Container
        BOOST_UBLAS_INLINE
        size_type max_size () const {
            return boost::allocator_max_size(alloc_);
        }
        
        BOOST_UBLAS_INLINE
        bool empty () const {
            return size_ == 0;
        }
            
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }

        // Assignment
        BOOST_UBLAS_INLINE
        unbounded_array &operator = (const unbounded_array &a) {
            if (this != &a) {
                resize (a.size_);
                std::copy (a.data_, a.data_ + a.size_, data_);
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        unbounded_array &assign_temporary (unbounded_array &a) {
            swap (a);
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (unbounded_array &a) {
            if (this != &a) {
                std::swap (size_, a.size_);
                std::swap (data_, a.data_);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (unbounded_array &a1, unbounded_array &a2) {
            a1.swap (a2);
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

    private:
        friend class boost::serialization::access;

        // Serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /*version*/)
        { 
            serialization::collection_size_type s(size_);
            ar & serialization::make_nvp("size",s);
            if ( Archive::is_loading::value ) {
                resize(s);
            }
            ar & serialization::make_array(data_, s);
        }

    private:
        // Handle explict destroy on a (possibly indexed) iterator
        BOOST_UBLAS_INLINE
        static void iterator_destroy (iterator &i) {
            (void)(i);
            (&(*i)) -> ~value_type ();
        }
        ALLOC alloc_;
        size_type size_;
        pointer data_;
    };

    // Bounded array - with allocator for size_type and difference_type
    template<class T, std::size_t N, class ALLOC>
    class bounded_array:
        public storage_array<bounded_array<T, N, ALLOC> > {

        typedef bounded_array<T, N, ALLOC> self_type;
    public:
        // No allocator_type as ALLOC is not used for allocation
        typedef typename boost::allocator_size_type<ALLOC>::type size_type;
        typedef typename boost::allocator_difference_type<ALLOC>::type difference_type;
        typedef T value_type;
        typedef const T &const_reference;
        typedef T &reference;
        typedef const T *const_pointer;
        typedef T *pointer;
        typedef const_pointer const_iterator;
        typedef pointer iterator;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        bounded_array ():
            size_ (0) /*, data_ ()*/ {   // size 0 - use bounded_vector to default construct with size N
        }
        explicit BOOST_UBLAS_INLINE
        bounded_array (size_type size):
            size_ (size) /*, data_ ()*/ {
            BOOST_UBLAS_CHECK (size_ <= N, bad_size ());
            // data_ (an array) elements are already default constructed
        }
        BOOST_UBLAS_INLINE
        bounded_array (size_type size, const value_type &init):
            size_ (size) /*, data_ ()*/ {
            BOOST_UBLAS_CHECK (size_ <= N, bad_size ());
            // ISSUE elements should be value constructed here, but we must fill instead as already default constructed
            std::fill (begin(), end(), init) ;
        }
        BOOST_UBLAS_INLINE
        bounded_array (const bounded_array &c):
            size_ (c.size_)  {
            // ISSUE elements should be copy constructed here, but we must copy instead as already default constructed
            std::copy (c.begin(), c.end(), begin());
        }
        
        // Resizing
        BOOST_UBLAS_INLINE
        void resize (size_type size) {
            BOOST_UBLAS_CHECK (size <= N, bad_size ());
            size_ = size;
        }
        BOOST_UBLAS_INLINE
        void resize (size_type size, value_type init) {
            BOOST_UBLAS_CHECK (size <= N, bad_size ());
            if (size > size_)
                std::fill (data_ + size_, data_ + size, init);
            size_ = size;
        }

        // Random Access Container
        BOOST_UBLAS_INLINE
        size_type max_size () const {
            return N;
        }
        
        BOOST_UBLAS_INLINE
        bool empty () const {
            return size_ == 0;
        }
            
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }

        // Assignment
        BOOST_UBLAS_INLINE
        bounded_array &operator = (const bounded_array &a) {
            if (this != &a) {
                resize (a.size_);
                std::copy (a.data_, a.data_ + a.size_, data_);
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        bounded_array &assign_temporary (bounded_array &a) { 
            *this = a;
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (bounded_array &a) {
            if (this != &a) {
                std::swap (size_, a.size_);
                std::swap_ranges (data_, data_ + (std::max) (size_, a.size_), a.data_);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (bounded_array &a1, bounded_array &a2) {
            a1.swap (a2);
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

    private:
        // Serialization
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int /*version*/)
        {
            serialization::collection_size_type s(size_);
            ar & serialization::make_nvp("size", s);
            if ( Archive::is_loading::value ) {
                if (s > N) bad_size("too large size in bounded_array::load()\n").raise();
                resize(s);
            }
            ar & serialization::make_array(data_, s);
        }

    private:
        size_type size_;
// MSVC does not like arrays of size 0 in base classes.  Hence, this conditionally changes the size to 1
#ifdef _MSC_VER
        BOOST_UBLAS_BOUNDED_ARRAY_ALIGN value_type data_ [(N>0)?N:1];
#else
        BOOST_UBLAS_BOUNDED_ARRAY_ALIGN value_type data_ [N];
#endif
    };


    // Array adaptor with normal deep copy semantics of elements
    template<class T>
    class array_adaptor:
        public storage_array<array_adaptor<T> > {

        typedef array_adaptor<T> self_type;
    public:
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T &const_reference;
        typedef T &reference;
        typedef const T *const_pointer;
        typedef T *pointer;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        array_adaptor ():
            size_ (0), own_ (true), data_ (new value_type [0]) {
        }
        explicit BOOST_UBLAS_INLINE
        array_adaptor (size_type size):
            size_ (size), own_ (true), data_ (new value_type [size]) {
        }
        BOOST_UBLAS_INLINE
        array_adaptor (size_type size, const value_type &init):
            size_ (size), own_ (true), data_ (new value_type [size]) {
            std::fill (data_, data_ + size_, init);
        }
        BOOST_UBLAS_INLINE
        array_adaptor (size_type size, pointer data):
            size_ (size), own_ (false), data_ (data) {}

        template <size_t N>
        BOOST_UBLAS_INLINE array_adaptor (T (&data)[N]):
            size_ (N), own_ (false), data_ (data) {}
        BOOST_UBLAS_INLINE
        array_adaptor (const array_adaptor &a):
            storage_array<self_type> (),
            size_ (a.size_), own_ (true), data_ (new value_type [a.size_]) {
            *this = a;
        }
        BOOST_UBLAS_INLINE
        ~array_adaptor () {
            if (own_) {
                delete [] data_;
            }
        }

        // Resizing
    private:
        BOOST_UBLAS_INLINE
        void resize_internal (size_type size, value_type init, bool preserve = true) {
           if (size != size_) {
                pointer data = new value_type [size];
                if (preserve) {
                    std::copy (data_, data_ + (std::min) (size, size_), data);
                    std::fill (data + (std::min) (size, size_), data + size, init);
                }
                if (own_)
                    delete [] data_;
                size_ = size;
                own_ = true;
                data_ = data;
            }
        }
        BOOST_UBLAS_INLINE
        void resize_internal (size_type size, pointer data, value_type init, bool preserve = true) {
            if (data != data_) {
                if (preserve) {
                    std::copy (data_, data_ + (std::min) (size, size_), data);
                    std::fill (data + (std::min) (size, size_), data + size, init);
                }
                if (own_)
                    delete [] data_;
                own_ = false;
                data_ = data;
            }
            else {
                std::fill (data + (std::min) (size, size_), data + size, init);
            }
            size_ = size;
        }
    public:
        BOOST_UBLAS_INLINE
        void resize (size_type size) {
            resize_internal (size, value_type (), false);
        }
        BOOST_UBLAS_INLINE
        void resize (size_type size, value_type init) {
            resize_internal (size, init, true);
        }
        BOOST_UBLAS_INLINE
        void resize (size_type size, pointer data) {
            resize_internal (size, data, value_type (), false);
        }
        BOOST_UBLAS_INLINE
        void resize (size_type size, pointer data, value_type init) {
            resize_internal (size, data, init, true);
        }

        template <size_t N>
        BOOST_UBLAS_INLINE void resize (T (&data)[N]) {
            resize_internal (N, data, value_type (), false);
        }

        template <size_t N>
        BOOST_UBLAS_INLINE void resize (T (&data)[N], value_type init) {
            resize_internal (N, data, init, true);
        }

        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }

        // Assignment
        BOOST_UBLAS_INLINE
        array_adaptor &operator = (const array_adaptor &a) {
            if (this != &a) {
                resize (a.size_);
                std::copy (a.data_, a.data_ + a.size_, data_);
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        array_adaptor &assign_temporary (array_adaptor &a) {
            if (own_ && a.own_)
                swap (a);
            else
                *this = a;
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (array_adaptor &a) {
            if (this != &a) {
                std::swap (size_, a.size_);
                std::swap (own_, a.own_);
                std::swap (data_, a.data_);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (array_adaptor &a1, array_adaptor &a2) {
            a1.swap (a2);
        }

        // Iterators simply are pointers.

        typedef const_pointer const_iterator;

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

        typedef pointer iterator;

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

    private:
        size_type size_;
        bool own_;
        pointer data_;
    };

#ifdef BOOST_UBLAS_SHALLOW_ARRAY_ADAPTOR
    // Array adaptor with shallow (reference) copy semantics of elements.
    // shared_array is used to maintain reference counts.
    // This class breaks the normal copy semantics for a storage container and is very dangerous!
    template<class T>
    class shallow_array_adaptor:
        public storage_array<shallow_array_adaptor<T> > {

        typedef shallow_array_adaptor<T> self_type;

        template<class TT>
        struct leaker {
            typedef void result_type;
            typedef TT *argument_type;

            BOOST_UBLAS_INLINE
            result_type operator () (argument_type /* x */) {}
        };

    public:
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T &const_reference;
        typedef T &reference;
        typedef const T *const_pointer;
        typedef T *pointer;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        shallow_array_adaptor ():
            size_ (0), own_ (true), data_ (new value_type [0]) {
        }
        explicit BOOST_UBLAS_INLINE
        shallow_array_adaptor (size_type size):
            size_ (size), own_ (true), data_ (new value_type [size]) {
        }
        BOOST_UBLAS_INLINE
        shallow_array_adaptor (size_type size, const value_type &init):
            size_ (size), own_ (true), data_ (new value_type [size]) {
            std::fill (data_.get (), data_.get () + size_, init);
        }
        BOOST_UBLAS_INLINE
        shallow_array_adaptor (size_type size, pointer data):
            size_ (size), own_ (false), data_ (data, leaker<value_type> ()) {}
        template <size_t N>
        BOOST_UBLAS_INLINE
        shallow_array_adaptor (T (&data)[N]):
            size_ (N), own_ (false), data_ (data, leaker<value_type> ()) {}

        BOOST_UBLAS_INLINE
        shallow_array_adaptor (const shallow_array_adaptor &a):
            storage_array<self_type> (),
            size_ (a.size_), own_ (a.own_), data_ (a.data_) {}

        BOOST_UBLAS_INLINE
        ~shallow_array_adaptor () {
        }

        // Resizing
    private:
        BOOST_UBLAS_INLINE
        void resize_internal (size_type size, value_type init, bool preserve = true) {
            if (size != size_) {
                shared_array<value_type> data (new value_type [size]);
                if (preserve) {
                    std::copy (data_.get (), data_.get () + (std::min) (size, size_), data.get ());
                    std::fill (data.get () + (std::min) (size, size_), data.get () + size, init);
                }
                size_ = size;
                own_ = true;
                data_ = data;
            }
        }
        BOOST_UBLAS_INLINE
        void resize_internal (size_type size, pointer data, value_type init, bool preserve = true) {
            if (preserve) {
                std::copy (data_.get (), data_.get () + (std::min) (size, size_), data);
                std::fill (data + (std::min) (size, size_), data + size, init);
            }
            size_ = size;
            own_ = false;
            data_.reset(data, leaker<value_type> ());
        }
    public:
        BOOST_UBLAS_INLINE
        void resize (size_type size) {
            resize_internal (size, value_type (), false);
        }
        BOOST_UBLAS_INLINE
        void resize (size_type size, value_type init) {
            resize_internal (size, init, true);
        }
        BOOST_UBLAS_INLINE
        void resize (size_type size, pointer data) {
            resize_internal (size, data, value_type (), false);
        }
        BOOST_UBLAS_INLINE
        void resize (size_type size, pointer data, value_type init) {
            resize_internal (size, data, init, true);
        }
        template <size_t N>
        BOOST_UBLAS_INLINE
        void resize (T (&data)[N]) {
            resize_internal (N, data, value_type (), false);
        }
        template <size_t N>
        BOOST_UBLAS_INLINE
        void resize (T (&data)[N], value_type init) {
            resize_internal (N, data, init, true);
        }

        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }

        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }

        // Assignment
        BOOST_UBLAS_INLINE
        shallow_array_adaptor &operator = (const shallow_array_adaptor &a) {
            if (this != &a) {
                resize (a.size_);
                std::copy (a.data_.get (), a.data_.get () + a.size_, data_.get ());
            }
            return *this;
        }
        BOOST_UBLAS_INLINE
        shallow_array_adaptor &assign_temporary (shallow_array_adaptor &a) {
            if (own_ && a.own_)
                swap (a);
            else
                *this = a;
            return *this;
        }

        // Swapping
        BOOST_UBLAS_INLINE
        void swap (shallow_array_adaptor &a) {
            if (this != &a) {
                std::swap (size_, a.size_);
                std::swap (own_, a.own_);
                std::swap (data_, a.data_);
            }
        }
        BOOST_UBLAS_INLINE
        friend void swap (shallow_array_adaptor &a1, shallow_array_adaptor &a2) {
            a1.swap (a2);
        }

        // Iterators simply are pointers.

        typedef const_pointer const_iterator;

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return data_.get ();
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return data_.get () + size_;
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

        typedef pointer iterator;

        BOOST_UBLAS_INLINE
        iterator begin () {
            return data_.get ();
        }
        BOOST_UBLAS_INLINE
        iterator end () {
            return data_.get () + size_;
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

    private:
        size_type size_;
        bool own_;
        shared_array<value_type> data_;
    };

#endif


    // Range class
    template <class Z, class D>
    class basic_range {
        typedef basic_range<Z, D> self_type;
    public:
        typedef Z size_type;
        typedef D difference_type;
        typedef size_type value_type;
        typedef value_type const_reference;
        typedef const_reference reference;
        typedef const value_type *const_pointer;
        typedef value_type *pointer;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        basic_range ():
            start_ (0), size_ (0) {}
        BOOST_UBLAS_INLINE
        basic_range (size_type start, size_type stop):
            start_ (start), size_ (stop - start) {
            BOOST_UBLAS_CHECK (start_ <= stop, bad_index ());
        }

        BOOST_UBLAS_INLINE
        size_type start () const {
            return start_;
        }
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }

        // Random Access Container
        BOOST_UBLAS_INLINE
        size_type max_size () const {
            return size_;
        }
        
        BOOST_UBLAS_INLINE
        bool empty () const {
            return size_ == 0;
        }
            
        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return start_ + i;
        }

        // Composition
        BOOST_UBLAS_INLINE
        basic_range compose (const basic_range &r) const {
            return basic_range (start_ + r.start_, start_ + r.start_ + r.size_);
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const basic_range &r) const {
            return start_ == r.start_ && size_ == r.size_;
        }
        BOOST_UBLAS_INLINE
        bool operator != (const basic_range &r) const {
            return ! (*this == r);
        }

        // Iterator types
    private:
        // Use and index
        typedef size_type const_subiterator_type;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_const_iterator<self_type, std::random_access_iterator_tag> const_iterator;
#else
        class const_iterator:
            public container_const_reference<basic_range>,
            public random_access_iterator_base<std::random_access_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef typename basic_range::value_type value_type;
            typedef typename basic_range::difference_type difference_type;
            typedef typename basic_range::const_reference reference;
            typedef typename basic_range::const_pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<basic_range> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const basic_range &r, const const_subiterator_type &it):
                container_const_reference<basic_range> (r), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                BOOST_UBLAS_CHECK (it_ > 0, bad_index ());
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                BOOST_UBLAS_CHECK (n >= 0 || it_ >= size_type(-n), bad_index ());
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                BOOST_UBLAS_CHECK (n <= 0 || it_ >= size_type(n), bad_index ());
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK ((*this) ().start () <= it_, bad_index ());
                BOOST_UBLAS_CHECK (it_ < (*this) ().start () + (*this) ().size (), bad_index ());
                return it_;
            }

            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK ((*this) ().start () <= it_, bad_index ());
                BOOST_UBLAS_CHECK (it_ < (*this) ().start () + (*this) ().size (), bad_index ());
                return it_ - (*this) ().start ();
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                // Comeau recommends...
                this->assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) () == it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) () == it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_subiterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return const_iterator (*this, start_);
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return const_iterator (*this, start_ + size_);
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

        // Reverse iterator
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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
        basic_range preprocess (size_type size) const {
            if (this != &all_)
                return *this;
            return basic_range (0, size);
        }
        static
        BOOST_UBLAS_INLINE
        const basic_range &all () {
            return all_;
        }

    private:
        size_type start_;
        size_type size_;
        static const basic_range all_;
    };

    template <class Z, class D>
    const basic_range<Z,D> basic_range<Z,D>::all_  (0, size_type (-1));


    // Slice class
    template <class Z, class D>
    class basic_slice {
        typedef basic_slice<Z, D> self_type;
    public:
        typedef Z size_type;
        typedef D difference_type;
        typedef size_type value_type;
        typedef value_type const_reference;
        typedef const_reference reference;
        typedef const value_type *const_pointer;
        typedef value_type *pointer;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        basic_slice ():
            start_ (0), stride_ (0), size_ (0) {}
        BOOST_UBLAS_INLINE
        basic_slice (size_type start, difference_type stride, size_type size):
            start_ (start), stride_ (stride), size_ (size) {}

        BOOST_UBLAS_INLINE
        size_type start () const {
            return start_;
        }
        BOOST_UBLAS_INLINE
        difference_type stride () const {
            return stride_;
        }
        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }

        // Random Access Container
        BOOST_UBLAS_INLINE
        size_type max_size () const {
            return size_;
        }
        
        BOOST_UBLAS_INLINE
        bool empty () const {
            return size_ == 0;
        }
            
        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            BOOST_UBLAS_CHECK (stride_ >= 0 || start_ >= i * -stride_, bad_index ());
            return start_ + i * stride_;
        }

        // Composition
        BOOST_UBLAS_INLINE
        basic_slice compose (const basic_range<size_type, difference_type> &r) const {
            BOOST_UBLAS_CHECK (stride_ >=0 || start_ >= -stride_ * r.start(), bad_index ());
            return basic_slice (start_ + stride_ * r.start (), stride_, r.size ());
        }
        BOOST_UBLAS_INLINE
        basic_slice compose (const basic_slice &s) const {
            BOOST_UBLAS_CHECK (stride_ >=0 || start_ >= -stride_ * s.start_, bad_index ());
            return basic_slice (start_ + stride_ * s.start_, stride_ * s.stride_, s.size_);
        }

        // Comparison
        BOOST_UBLAS_INLINE
        bool operator == (const basic_slice &s) const {
            return start_ == s.start_ && stride_ == s.stride_ && size_ == s.size_; 
        }
        BOOST_UBLAS_INLINE
        bool operator != (const basic_slice &s) const {
            return ! (*this == s);
        }

        // Iterator types
    private:
        // Use and index
        typedef size_type const_subiterator_type;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_const_iterator<self_type, std::random_access_iterator_tag> const_iterator;
#else
        class const_iterator:
            public container_const_reference<basic_slice>,
            public random_access_iterator_base<std::random_access_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef typename basic_slice::value_type value_type;
            typedef typename basic_slice::difference_type difference_type;
            typedef typename basic_slice::const_reference reference;
            typedef typename basic_slice::const_pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<basic_slice> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const basic_slice &s, const const_subiterator_type &it):
                container_const_reference<basic_slice> (s), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                BOOST_UBLAS_CHECK (it_ > 0, bad_index ());
                --it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                BOOST_UBLAS_CHECK (n >= 0 || it_ >= size_type(-n), bad_index ());
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                BOOST_UBLAS_CHECK (n <= 0 || it_ >= size_type(n), bad_index ());
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                BOOST_UBLAS_CHECK (it_ < (*this) ().size (), bad_index ());
                return (*this) ().start () + it_* (*this) ().stride ();
            }

            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                BOOST_UBLAS_CHECK (it_ < (*this) ().size (), bad_index ());
                return it_;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                // Comeau recommends...
                this->assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) () == it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) () == it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_subiterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return const_iterator (*this, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return const_iterator (*this, size_);
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

        // Reverse iterator
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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
        basic_slice preprocess (size_type size) const {
            if (this != &all_)
                return *this;
            return basic_slice (0, 1, size);
        }
        static
        BOOST_UBLAS_INLINE
        const basic_slice &all () {
            return all_;
        }

    private:
        size_type start_;
        difference_type stride_;
        size_type size_;
        static const basic_slice all_;
    };

    template <class Z, class D>
    const basic_slice<Z,D> basic_slice<Z,D>::all_  (0, 1, size_type (-1));


    // Indirect array class
    template<class A>
    class indirect_array {
        typedef indirect_array<A> self_type;
    public:
        typedef A array_type;
        typedef const A const_array_type;
        typedef typename A::size_type size_type;
        typedef typename A::difference_type difference_type;
        typedef typename A::value_type value_type;
        typedef typename A::const_reference const_reference;
        typedef typename A::reference reference;
        typedef typename A::const_pointer const_pointer;
        typedef typename A::pointer pointer;

        // Construction and destruction
        BOOST_UBLAS_INLINE
        indirect_array ():
            size_ (), data_ () {}
        explicit BOOST_UBLAS_INLINE
        indirect_array (size_type size):
            size_ (size), data_ (size) {}
        BOOST_UBLAS_INLINE
        indirect_array (size_type size, const array_type &data):
            size_ (size), data_ (data) {}
        BOOST_UBLAS_INLINE
        indirect_array (pointer start, pointer stop):
            size_ (stop - start), data_ (stop - start) {
            std::copy (start, stop, data_.begin ());
        }

        BOOST_UBLAS_INLINE
        size_type size () const {
            return size_;
        }
        BOOST_UBLAS_INLINE
        const_array_type data () const {
            return data_;
        }
        BOOST_UBLAS_INLINE
        array_type data () {
            return data_;
        }

        // Random Access Container
        BOOST_UBLAS_INLINE
        size_type max_size () const {
            return size_;
        }
        
        BOOST_UBLAS_INLINE
        bool empty () const {
            return data_.size () == 0;
        }
            
        // Element access
        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            BOOST_UBLAS_CHECK (i < size_, bad_index ());
            return data_ [i];
        }

        BOOST_UBLAS_INLINE
        const_reference operator [] (size_type i) const {
            return (*this) (i);
        }
        BOOST_UBLAS_INLINE
        reference operator [] (size_type i) {
            return (*this) (i);
        }

        // Composition
        BOOST_UBLAS_INLINE
        indirect_array compose (const basic_range<size_type, difference_type> &r) const {
            BOOST_UBLAS_CHECK (r.start () + r.size () <= size_, bad_size ());
            array_type data (r.size ());
            for (size_type i = 0; i < r.size (); ++ i)
                data [i] = data_ [r.start () + i];
            return indirect_array (r.size (), data);
        }
        BOOST_UBLAS_INLINE
        indirect_array compose (const basic_slice<size_type, difference_type> &s) const {
            BOOST_UBLAS_CHECK (s.start () + s.stride () * (s.size () - (s.size () > 0)) <= size (), bad_size ());
            array_type data (s.size ());
            for (size_type i = 0; i < s.size (); ++ i)
                data [i] = data_ [s.start () + s.stride () * i];
            return indirect_array (s.size (), data);
        }
        BOOST_UBLAS_INLINE
        indirect_array compose (const indirect_array &ia) const {
            array_type data (ia.size_);
            for (size_type i = 0; i < ia.size_; ++ i) {
                BOOST_UBLAS_CHECK (ia.data_ [i] <= size_, bad_size ());
                data [i] = data_ [ia.data_ [i]];
            }
            return indirect_array (ia.size_, data);
        }

        // Comparison
        template<class OA>
        BOOST_UBLAS_INLINE
        bool operator == (const indirect_array<OA> &ia) const {
            if (size_ != ia.size_)
                return false;
            for (size_type i = 0; i < BOOST_UBLAS_SAME (size_, ia.size_); ++ i)
                if (data_ [i] != ia.data_ [i])
                    return false;
            return true;
        }
        template<class OA>
        BOOST_UBLAS_INLINE
        bool operator != (const indirect_array<OA> &ia) const {
            return ! (*this == ia);
        }

        // Iterator types
    private:
        // Use a index difference
        typedef difference_type const_subiterator_type;

    public:
#ifdef BOOST_UBLAS_USE_INDEXED_ITERATOR
        typedef indexed_const_iterator<indirect_array, std::random_access_iterator_tag> const_iterator;
#else
        class const_iterator:
            public container_const_reference<indirect_array>,
            public random_access_iterator_base<std::random_access_iterator_tag,
                                               const_iterator, value_type> {
        public:
            typedef typename indirect_array::value_type value_type;
            typedef typename indirect_array::difference_type difference_type;
            typedef typename indirect_array::const_reference reference;
            typedef typename indirect_array::const_pointer pointer;

            // Construction and destruction
            BOOST_UBLAS_INLINE
            const_iterator ():
                container_const_reference<indirect_array> (), it_ () {}
            BOOST_UBLAS_INLINE
            const_iterator (const indirect_array &ia, const const_subiterator_type &it):
                container_const_reference<indirect_array> (ia), it_ (it) {}

            // Arithmetic
            BOOST_UBLAS_INLINE
            const_iterator &operator ++ () {
                ++ it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -- () {
                -- it_;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator += (difference_type n) {
                it_ += n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            const_iterator &operator -= (difference_type n) {
                it_ -= n;
                return *this;
            }
            BOOST_UBLAS_INLINE
            difference_type operator - (const const_iterator &it) const {
                return it_ - it.it_;
            }

            // Dereference
            BOOST_UBLAS_INLINE
            const_reference operator * () const {
                return (*this) () (it_);
            }

            BOOST_UBLAS_INLINE
            const_reference operator [] (difference_type n) const {
                return *(*this + n);
            }

            // Index
            BOOST_UBLAS_INLINE
            size_type index () const {
                return it_;
            }

            // Assignment
            BOOST_UBLAS_INLINE
            const_iterator &operator = (const const_iterator &it) {
                // Comeau recommends...
                this->assign (&it ());
                it_ = it.it_;
                return *this;
            }

            // Comparison
            BOOST_UBLAS_INLINE
            bool operator == (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) () == it (), external_logic ());
                return it_ == it.it_;
            }
            BOOST_UBLAS_INLINE
            bool operator < (const const_iterator &it) const {
                BOOST_UBLAS_CHECK ((*this) () == it (), external_logic ());
                return it_ < it.it_;
            }

        private:
            const_subiterator_type it_;
        };
#endif

        BOOST_UBLAS_INLINE
        const_iterator begin () const {
            return const_iterator (*this, 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator end () const {
            return const_iterator (*this, size_);
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

        // Reverse iterator
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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
        indirect_array preprocess (size_type size) const {
            if (this != &all_)
                return *this;
            indirect_array ia (size);
            for (size_type i = 0; i < size; ++ i)
               ia (i) = i;
            return ia;
        }
        static
        BOOST_UBLAS_INLINE
        const indirect_array &all () {
            return all_;
        }

    private:
        size_type size_;
        array_type data_;
        static const indirect_array all_;
    };

    template<class A>
    const indirect_array<A> indirect_array<A>::all_;



    // Gunter Winkler contributed the classes index_pair, index_pair_array,
    // index_triple and index_triple_array to enable inplace sort of parallel arrays.

    template <class V>
    class index_pair :
        public container_reference<V> {

        typedef index_pair<V> self_type;
    public:
        typedef typename V::size_type size_type;

        BOOST_UBLAS_INLINE
        index_pair(V& v, size_type i) :
            container_reference<V>(v), i_(i),
            v1_(v.data1_[i]), v2_(v.data2_[i]),
            dirty_(false), is_copy_(false) {}
         BOOST_UBLAS_INLINE
        index_pair(const self_type& rhs) :
            container_reference<V>(rhs()), i_(0),
            v1_(rhs.v1_), v2_(rhs.v2_),
            dirty_(false), is_copy_(true) {}
         BOOST_UBLAS_INLINE
        ~index_pair() {
            if (dirty_ && (!is_copy_) ) {
                (*this)().data1_[i_] = v1_;
                (*this)().data2_[i_] = v2_;
            }
        }

        BOOST_UBLAS_INLINE
        self_type& operator=(const self_type& rhs) {
            v1_ = rhs.v1_;
            v2_ = rhs.v2_;
            dirty_ = true;
            return *this;
        }

        BOOST_UBLAS_INLINE
        void swap(self_type& rhs) {
            self_type tmp(rhs);
            rhs = *this;
            *this = tmp;
        }

        BOOST_UBLAS_INLINE
        friend void swap(self_type& lhs, self_type& rhs) {
            lhs.swap(rhs);
        }

        friend void swap(self_type lhs, self_type rhs) { // For gcc 4.8 and c++11
            lhs.swap(rhs);
        }


        BOOST_UBLAS_INLINE
        bool equal(const self_type& rhs) const {
            return (v1_ == rhs.v1_);
        }
        BOOST_UBLAS_INLINE
        bool less(const self_type& rhs) const {
            return (v1_ < rhs.v1_);
        }
        BOOST_UBLAS_INLINE
        friend bool operator == (const self_type& lhs, const self_type& rhs) {
            return lhs.equal(rhs);
        }
        BOOST_UBLAS_INLINE
        friend bool operator != (const self_type& lhs, const self_type& rhs) {
            return !lhs.equal(rhs);
        }
        BOOST_UBLAS_INLINE
        friend bool operator < (const self_type& lhs, const self_type& rhs) {
            return lhs.less(rhs);
        }
        BOOST_UBLAS_INLINE
        friend bool operator >= (const self_type& lhs, const self_type& rhs) {
            return !lhs.less(rhs);
        }
        BOOST_UBLAS_INLINE
        friend bool operator > (const self_type& lhs, const self_type& rhs) {
            return rhs.less(lhs);
        }
        BOOST_UBLAS_INLINE
        friend bool operator <= (const self_type& lhs, const self_type& rhs) {
            return !rhs.less(lhs);
        }

    private:
        size_type i_;
        typename V::value1_type v1_;
        typename V::value2_type v2_;
        bool dirty_;
        bool is_copy_;
     };

    template <class V1, class V2>
    class index_pair_array:
        private boost::noncopyable {

        typedef index_pair_array<V1, V2> self_type;
    public:
        typedef typename V1::value_type value1_type;
        typedef typename V2::value_type value2_type;

        typedef typename V1::size_type size_type;
        typedef typename V1::difference_type difference_type;
        typedef index_pair<self_type> value_type;
        // There is nothing that can be referenced directly. Always return a copy of the index_pair
        typedef value_type reference;
        typedef const value_type const_reference;

        BOOST_UBLAS_INLINE
        index_pair_array(size_type size, V1& data1, V2& data2) :
              size_(size),data1_(data1),data2_(data2) {}

        BOOST_UBLAS_INLINE
        size_type size() const {
            return size_;
        }

        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return value_type((*this), i);
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return value_type((*this), i);
        }

        typedef indexed_iterator<self_type, std::random_access_iterator_tag> iterator;
        typedef indexed_const_iterator<self_type, std::random_access_iterator_tag> const_iterator;

        BOOST_UBLAS_INLINE
        iterator begin() {
            return iterator( (*this), 0);
        }
        BOOST_UBLAS_INLINE
        iterator end() {
            return iterator( (*this), size());
        }

        BOOST_UBLAS_INLINE
        const_iterator begin() const {
            return const_iterator( (*this), 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator end() const {
            return const_iterator( (*this), size());
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

        // unnecessary function:
        BOOST_UBLAS_INLINE
        bool equal(size_type i1, size_type i2) const {
            return data1_[i1] == data1_[i2];
        }
        BOOST_UBLAS_INLINE
        bool less(size_type i1, size_type i2) const {
            return data1_[i1] < data1_[i2];
        }

        // gives a large speedup
        BOOST_UBLAS_INLINE
        friend void iter_swap(const iterator& lhs, const iterator& rhs) {
            const size_type i1 = lhs.index();
            const size_type i2 = rhs.index();
            std::swap(lhs().data1_[i1], rhs().data1_[i2]);
            std::swap(lhs().data2_[i1], rhs().data2_[i2]);
        }

    private:
        size_type size_;
        V1& data1_;
        V2& data2_;

        // friend class value_type;
        friend class index_pair<self_type>;
    };

    template <class M>
    class index_triple :
        public container_reference<M> {

        typedef index_triple<M> self_type;
    public:
        typedef typename M::size_type size_type;

        BOOST_UBLAS_INLINE
        index_triple(M& m, size_type i) :
            container_reference<M>(m), i_(i),
            v1_(m.data1_[i]), v2_(m.data2_[i]), v3_(m.data3_[i]),
            dirty_(false), is_copy_(false) {}
        BOOST_UBLAS_INLINE
        index_triple(const self_type& rhs) :
            container_reference<M>(rhs()), i_(0),
            v1_(rhs.v1_), v2_(rhs.v2_), v3_(rhs.v3_),
            dirty_(false), is_copy_(true) {}
        BOOST_UBLAS_INLINE
        ~index_triple() {
            if (dirty_ && (!is_copy_) ) {
                (*this)().data1_[i_] = v1_;
                (*this)().data2_[i_] = v2_;
                (*this)().data3_[i_] = v3_;
            }
        }

        BOOST_UBLAS_INLINE
        self_type& operator=(const self_type& rhs) {
            v1_ = rhs.v1_;
            v2_ = rhs.v2_;
            v3_ = rhs.v3_;
            dirty_ = true;
            return *this;
        }

        BOOST_UBLAS_INLINE
        void swap(self_type& rhs) {
            self_type tmp(rhs);
            rhs = *this;
            *this = tmp;
        }

        BOOST_UBLAS_INLINE
        friend void swap(self_type& lhs, self_type& rhs) {
            lhs.swap(rhs);
        }

        friend void swap(self_type lhs, self_type rhs) { // For gcc 4.8 and c++11
            lhs.swap(rhs);
        }

        BOOST_UBLAS_INLINE
        bool equal(const self_type& rhs) const {
            return ((v1_ == rhs.v1_) && (v2_ == rhs.v2_));
        }
        BOOST_UBLAS_INLINE
        bool less(const self_type& rhs) const {
            return ((v1_ < rhs.v1_) ||
                    (v1_ == rhs.v1_ && v2_ < rhs.v2_));
        }
        BOOST_UBLAS_INLINE
        friend bool operator == (const self_type& lhs, const self_type& rhs) {
            return lhs.equal(rhs);
        }
        BOOST_UBLAS_INLINE
        friend bool operator != (const self_type& lhs, const self_type& rhs) {
            return !lhs.equal(rhs);
        }
        BOOST_UBLAS_INLINE
        friend bool operator < (const self_type& lhs, const self_type& rhs) {
            return lhs.less(rhs);
        }
        BOOST_UBLAS_INLINE
        friend bool operator >= (const self_type& lhs, const self_type& rhs) {
            return !lhs.less(rhs);
        }
        BOOST_UBLAS_INLINE
        friend bool operator > (const self_type& lhs, const self_type& rhs) {
            return rhs.less(lhs);
        }
        BOOST_UBLAS_INLINE
        friend bool operator <= (const self_type& lhs, const self_type& rhs) {
            return !rhs.less(lhs);
        }

    private:
        size_type i_;
        typename M::value1_type v1_;
        typename M::value2_type v2_;
        typename M::value3_type v3_;
        bool dirty_;
        bool is_copy_;
    };

    template <class V1, class V2, class V3>
    class index_triple_array:
        private boost::noncopyable {

        typedef index_triple_array<V1, V2, V3> self_type;
    public:
        typedef typename V1::value_type value1_type;
        typedef typename V2::value_type value2_type;
        typedef typename V3::value_type value3_type;

        typedef typename V1::size_type size_type;
        typedef typename V1::difference_type difference_type;
        typedef index_triple<self_type> value_type;
        // There is nothing that can be referenced directly. Always return a copy of the index_triple
        typedef value_type reference;
        typedef const value_type const_reference;

        BOOST_UBLAS_INLINE
        index_triple_array(size_type size, V1& data1, V2& data2, V3& data3) :
              size_(size),data1_(data1),data2_(data2),data3_(data3) {}

        BOOST_UBLAS_INLINE
        size_type size() const {
            return size_;
        }

        BOOST_UBLAS_INLINE
        const_reference operator () (size_type i) const {
            return value_type((*this), i);
        }
        BOOST_UBLAS_INLINE
        reference operator () (size_type i) {
            return value_type((*this), i);
        }

        typedef indexed_iterator<self_type, std::random_access_iterator_tag> iterator;
        typedef indexed_const_iterator<self_type, std::random_access_iterator_tag> const_iterator;

        BOOST_UBLAS_INLINE
        iterator begin() {
            return iterator( (*this), 0);
        }
        BOOST_UBLAS_INLINE
        iterator end() {
            return iterator( (*this), size());
        }

        BOOST_UBLAS_INLINE
        const_iterator begin() const {
            return const_iterator( (*this), 0);
        }
        BOOST_UBLAS_INLINE
        const_iterator cbegin () const {
            return begin ();
        }
        BOOST_UBLAS_INLINE
        const_iterator end() const {
            return const_iterator( (*this), size());
        }
        BOOST_UBLAS_INLINE
        const_iterator cend () const {
            return end ();
        }

        // unnecessary function:
        BOOST_UBLAS_INLINE
        bool equal(size_type i1, size_type i2) const {
            return ((data1_[i1] == data1_[i2]) && (data2_[i1] == data2_[i2]));
        }
        BOOST_UBLAS_INLINE
        bool less(size_type i1, size_type i2) const {
            return ((data1_[i1] < data1_[i2]) ||
                    (data1_[i1] == data1_[i2] && data2_[i1] < data2_[i2]));
        }

        // gives a large speedup
        BOOST_UBLAS_INLINE
        friend void iter_swap(const iterator& lhs, const iterator& rhs) {
            const size_type i1 = lhs.index();
            const size_type i2 = rhs.index();
            std::swap(lhs().data1_[i1], rhs().data1_[i2]);
            std::swap(lhs().data2_[i1], rhs().data2_[i2]);
            std::swap(lhs().data3_[i1], rhs().data3_[i2]);
        }

    private:
        size_type size_;
        V1& data1_;
        V2& data2_;
        V3& data3_;

        // friend class value_type;
        friend class index_triple<self_type>;
    };

}}}

#endif

/* storage.hpp
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
*/