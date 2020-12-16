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
jkRn+fscvU34ARr5PPKqAa+B0r/CdOqAf0n+vgFyaMst/f4x8l2ReRukWiLMUTpZPsSjkeVjPIcRT7z0X2fF01X+vhpyiXMs+0Nb5LtQnbwf+avyfjBzodgNGir955h5xnjoSJ6nk9F054GnWDIJo6ziROk/1bwMt3JjkNLWtCO4aaCU05V0zYVyZMpkRlA+8kJJV2xeAYto3xoToRuY9gFEKgUt7VIdQTmMkWGXmILXOpko1DplSj+F/yjID7ah/GhvuG8jsEcD58ShkXQav8pO8n/ZLqP1MoWj28r7x0Ok/aqOhtmE8oUoSr4T+RB568i8Wd+BYrzmaxP8gYeB3YVs5Hma76B0EUQW9d/BbsQxR9I8j7Kk/YLzbG1mkL8qy1u6rDhHIyOsDZuxKI/1HQ6cIf23m93RJQ42OxiL4HRtVuXjL7+94tJFNvLDDFunjXVnG8uT/reacUZX2MaaDDsbg6Ezu72RDifKYxfKY4EMs8dsBx6/FESGLEowcsS5B2FUeXLrm5d0KyGL1tmotZdWbNl1mMpy7gv7aGPgroSr/YZY7/wO/xiLsNImTUcjHm25JdvyN1Y75f8KPhTKts62O7kJ2q6UZWUdu9rHQV0qbVfUS0fWSxjeiTISZddRKTvRfoc75deV+wni3zzKrxf3r9N+PdL/sVTSDde0WfJ061PBTtdmEdZzufbi/p7LtSOsrl1a8t3XSv+LXfSBrArHuCvr/NTuGrCvEXn2Sv79ODDVtNsz9v5MIG6UifdV01u9fMeGBzIORZ+8tVfr4D/ayw/r9+zt9/j1ZwX2ctf6PXXv98K93YN3yKtyPsR50ng3eVV/fAQCA4CBwEDqwz/mHH85BxrPux9HSKfqv7gAOBU4l/otCqnf4nJgAXAdsBBYASwCbgQWU/97CfBB4GLg08Al1ANfBnwfuAz4MfWofwNcAfwB+BvqHb+d+sY3U9/4FmA/4F3AccBtwOnUU14EvAe4CPgA8BrqKd/E37K8TPbtYsxjvns4dU9Rb3w09cYPBP4JOAX4GPCX1JefCfwLy+GvwCXUp38N9ehfRz36t1F//jbqz4eT+vNfov78j6g3/xj15ncw0ZaAIi3PUZ/6C8Bk4IvA8cB/AWcBDwEvA74m0sP3lwPfAF4BfBN4E/AtUR/At4G3M9z9wBrg74HviPoBvgvcDXwfuBf4AfCwCM9ym82+xymPPZ79nHNs6I1w/sA+tH/QD9hLNDHg+cCB1Gcfx/I8n3LbCczXwe/tZaaLbWSlxwwKPCOy0sdKg+qTlz5lOWl7GemG5aNPoNzCf4DsOdylP/hkof8fnjN0/p/QFOf/zjv7qUdxZ1+s+7mYjuD7Vc73CbH0cuwDjIDfwAb2AVL7q/sADd/tU+/FV9rwTFd5ilQZnvJ1zEdP8Ni0FwP05B2/KGs+ymx6eJcyqr/nd2OjNPNT/ZyTYd3v6+nmnAzrfpdy6CnepfRuLYu0uZVztmCs3Ovpx3l/TT9nOVvTfY/Kuaaf53dWa/p5Prev6ef53J5haaNPzttlWQ87xbJu7L3Vptbjp58/n379fvPleqEmd+3Gm16+4rtvH+05ozI7x/DJ/pxt2R/rfmL/2vVLtdv6ZRjv610IDKQePCddej10I0k3inSjlfuBUaTrRTr1fuBU0qXQDlsq7/tNs+j5nZLGnX4c6ceTbgKwH/UFlvp5JutUjnncph88v0NYn+4+zJF/0vr7bHT3+fT2nYLevl1oO/vhjsIF/OhbE/ge3+N7fM//ynOG1v/xTbn+L/9ArPPB1KH+z3q/q/Z9buagBOv9Ues9NOIo4SM/5HuH6j/jHL5PdbyPTxuUoOqds/xX0R8reumv7jU=
*/