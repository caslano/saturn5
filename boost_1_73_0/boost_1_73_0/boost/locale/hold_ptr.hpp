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
WvQDukHnRVo3KMCny/APmfH3Di7H3b3iXY4rco3Xg3I7YqdDlNE/TBZ37cfEmCHw5z2Oe4fDwx6w7A5zgBxgra5GBoOSH3Zx3b7HBNPWNXXN7ishmTARBBbdo09+eHJwj0Z7RYTu5s73oqRr34/U35QKW9NFVRbKBUwpq0oFuiZ7SB6DP6cbvI4OubPhvma92+Ndptv4hdDbHDH/aLbo6Sets0mTAEGyvRUnTqfpnDYxIXtPP9javh9gDh1/xn+ZoB3e5PFMaF+h+SVJTVH5TK1haw/TUJgk4xBaos0T1HcPX10Hv56dovc+G569HpxcXwwHLW5Z6x795+Nfg+fHV5eng5fX50h6h7tZ0R5d/Pt0eMa9ezA8OwuuxeGhsLhBrTHXRwGIbD6etLWP7pn6dKjfLSQJju41LIpqXqM+yMHj9v9v8jjb4KUaZcprbu4XdX3AVNDm2rE3wRCVlotu68FpnuaNIJtOg1JESZmVYdLd3kuz5bdRqwdQK0JVFWl/jwfqDJNxnIaJaITskVMLjEYTyV28WGLYWOZxWcqUPUrkqNm/DPNCHIdFLQnNutz/p3IpZBTTHIXShvkxLmkuhcUxvBIA2vKJXJRFn8cWIeoqWsZziaFCQEIEVXmLtc2xX59jrgjKPEyLKUbS
*/