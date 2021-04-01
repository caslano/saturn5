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
XpxQmjvT877gphfUnUVN7M+dclnCELXqvUmEs+CGBVKOQbLZ4qJIrv4tSbbEExPvKzkTT0CmKN/FM1fV5QGxnlPfPwB06BwR5hCDQ8dQEztFpBclE7E2cMiybI1f9W90ug8cbP4LRqBXU2OALy/zJjCfXUFvzLW7YBXxXZYlqJ5oeJDGF5L9qbwdLKuo2F/S5O45iYlD10QPmEUCEzz4X2lwruw92D6nC6BLijPXWEF+yqMJT9wbsvISYYhJrDEeA+LWSpcVM9aHhiH5fzX4vIxlm7lPVzpW1f1bt7nQ2hJqYIv/4Da8SQMqHbUTHwHexZ0qzvgW1Q2MxIPXetG6wNR6APygH4ZW3khg5UmuaeXyfVOSaDuWNC7iUU3c4T8Rr+V06ylVA4A/1cyPDytOIn3R/Tsd7+BppS1IrqtT2jkgaR2DaHMERe+dJLMl5mcFCzcZ+6n5Grguv3XzDf5wyy6FOgyCpuseq6kBrMO1VHxYHTG9EcGbLgQl28KpvlRQAImqgpfLEwkVQ13PVp23IgHEiHtpU5pNINpxAvbDDyc96GmaxDfj60v4/A==
*/