#ifndef BOOST_POINTER_TO_OTHER_HPP_INCLUDED
#define BOOST_POINTER_TO_OTHER_HPP_INCLUDED

//
//  pointer_to_other.hpp
//
//  (C) Copyright Ion Gaztanaga 2005.
//  Copyright (c) 2005 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/smart_ptr/ for documentation.
//

namespace boost
{

// Defines the same pointer type (raw or smart) to another pointee type

template<class T, class U>
struct pointer_to_other;

template<class T, class U, 
         template<class> class Sp>
struct pointer_to_other< Sp<T>, U >
{
   typedef Sp<U> type;
};

template<class T, class T2, class U, 
         template<class, class> class Sp>
struct pointer_to_other< Sp<T, T2>, U >
{
   typedef Sp<U, T2> type;
};

template<class T, class T2, class T3, class U, 
         template<class, class, class> class Sp>
struct pointer_to_other< Sp<T, T2, T3>, U >
{
   typedef Sp<U, T2, T3> type;
};

template<class T, class U>
struct pointer_to_other< T*, U >
{
   typedef U* type;
};

} // namespace boost

#endif // #ifndef BOOST_POINTER_TO_OTHER_HPP_INCLUDED

/* pointer_to_other.hpp
hPz4kEwNWpAFnkleNgNTNQCFxYZUH6cRpVzpVeQ/RlOM3JvNmGg91PgxMOFk8BA08LUJjfXhMDTpGrxyUCdvvqtEYw/BR4dx8ea7g5DB7AQf33nRJr3DMGcTGbhIlOsZ1Kp9CR1THLOV/SS6p21uWDnx4oTVKUddN9ZmNijAHMsJkDF4B0pz6CULqo4Tw/jxBqHw+DNd3xVneBRKLRoCo1QAGIlTcQBhSwquMp8LybO00UYtaeKGTtpv0K5QQ5UyMtSH1n7555IfxKv1YxSDLmx7II8Wic/mtiDr8utXUC3QIfpLP9huvJDOzSvnn3wd7XqE2qRWxZqLxkk+LXTYhW2rcF1+lI7T+s2v8IH32ZPoR/VAaLTqXhSAk8H7+Wr5JJsuVMtbhjm1sYDsXJ5N+3DH8sIMLzP2fipn1rdA5C445X/y+TWnS/5p328w0Li3PPBMeWAmNhFl9tVYPyfX39egfLc8+17f19B4jBtAwChMTyAkyFiYl8gurfF0NJgo+eYzMxhV07FTURyeFteeJdv5cq2qRK66VXK02LEFJMXOaV6MbuTy19Sk9d/X1Cg74aurEx1brEsyV94EIO4A+HOH4X9mhlIbFxaZGDzmmzy1Yx2myXj2rgqP/vwpX3lX6+vg6rG8pCtzJOZ+
*/