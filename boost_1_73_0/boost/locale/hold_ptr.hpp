//
//  Copyright (c) 2010 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_HOLD_PTR_H
#define BOOST_LOCALE_HOLD_PTR_H

namespace boost { 
namespace locale {
    ///
    /// \brief a smart pointer similar to std::auto_ptr but it is non-copyable and the
    /// underlying object has the same constness as the pointer itself (unlike an ordinary pointer).
    ///
    template<typename T>
    class hold_ptr {
        hold_ptr(hold_ptr const &other); // non copyable 
        hold_ptr const &operator=(hold_ptr const &other); // non assignable
    public:
        ///
        /// Create new empty pointer
        ///
        hold_ptr() : ptr_(0) {}
        ///
        /// Create a pointer that holds \a v, ownership is transferred to smart pointer
        ///
        explicit hold_ptr(T *v) : ptr_(v) {}

        ///
        /// Destroy smart pointer and the object it owns.
        ///
        ~hold_ptr() 
        {
            delete ptr_;
        }

        ///
        /// Get a const pointer to the object
        ///
        T const *get() const { return ptr_; }
        ///
        /// Get a mutable pointer to the object 
        ///
        T *get() { return ptr_; }

        /// 
        /// Get a const reference to the object
        ///
        T const &operator *() const { return *ptr_; }
        /// 
        /// Get a mutable reference to the object
        ///
        T &operator *() { return *ptr_; }
        ///
        /// Get a const pointer to the object
        ///
        T const *operator->() const { return ptr_; }
        ///
        /// Get a mutable pointer to the object 
        ///
        T *operator->() { return ptr_; }

        ///
        /// Transfer an ownership on the pointer to user
        ///
        T *release() { T *tmp=ptr_; ptr_=0; return tmp; }

        ///
        /// Set new value to pointer, previous object is destroyed, ownership on new object is transferred
        ///
        void reset(T *p=0)
        {
            if(ptr_) delete ptr_;
            ptr_=p;
        }
        /// Swap two pointers
        void swap(hold_ptr &other)
        {
            T *tmp=other.ptr_;
            other.ptr_=ptr_;
            ptr_=tmp;
        }
    private:
        T *ptr_;
    };

} // locale
} // boost

#endif
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* hold_ptr.hpp
qHs7u7p3Yld3VT/fGepKVfVz2WBXEHOE6H/5SffBeEZ6php6Po80kvazTJuAd46YaTJivFJ+DfvRRD69wocM/DgNf3E3+OIe3Sss56HrrM1oDmur6B+ZKW1g/+bHvJ7rtvW/CGUXRZV3ScdCodDhouw37C5zM9XIN1v+H1arHvHm9ZFj6mNttaJ5RfWbtme+gb9Ww19Vfcb6yzX1cYGGPY+wb3K+Rer0jiyzuojy/Nt76n2O
*/