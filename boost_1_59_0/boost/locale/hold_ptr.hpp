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
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
*/