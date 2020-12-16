/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_ASSOCIATED_VALUE_HPP_JOFA_100829
#define BOOST_ICL_DETAIL_ASSOCIATED_VALUE_HPP_JOFA_100829

#include <boost/icl/detail/design_config.hpp>
#include <boost/icl/type_traits/is_combinable.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>

namespace boost{namespace icl
{

template<class Type, class CoType> 
typename enable_if< mpl::and_< is_key_compare_equal<Type,CoType>
                             , mpl::and_<is_map<Type>, is_map<CoType> > >, 
                    bool>::type
co_equal(typename Type::const_iterator left_, typename CoType::const_iterator right_, 
         const Type* = 0, const CoType* = 0)
{
    return co_value<Type>(left_) == co_value<CoType>(right_);
}

template<class Type, class CoType> 
typename enable_if< mpl::and_< is_key_compare_equal<Type,CoType>
                             , mpl::not_<mpl::and_<is_map<Type>, is_map<CoType> > > >,
                  bool>::type
co_equal(typename Type::const_iterator, typename CoType::const_iterator,
         const Type* = 0, const CoType* = 0)
{
    return true;
}


}} // namespace icl boost

#endif


/* associated_value.hpp
Ge/mYX6+JS7bPMbbD5t5YogO+ptf8n1u62jjvt3c6+EI7HNbitrCZtrb/x7bRVopbVMpfjZGwXbsdHJZN4F8V36DEX+Exx0OTFH7NHV9+EU6OZ/xrsuG2/jG0PfCPCwea4jp7ntpblMKnB7JsK+3fMk5sxAC80in5LIp5nUIil0mM/V0QV+t+y330W3BTDkZlu6wGdNVovmzX4uxbF0gj4gtIpt9YZTHiylJ7A9+jCrEz9BumGvMoc5pe2mUaTg1b/1Itz03o8TkLev8eI9u7L3M1FL1SfVAHDOqt8P7WQfhtGwJRkwTx/dbr3C39DrO6i3Cxe3Tkd89BOWKZ5hpYgZaQvez3c+acW7zM975wYus5g/jcS+VMCi6i11a54rlgXPYin2SlB7twE+0W2FzhRW5ae6gLf6/2SeXJBqX78veaf7E1zZTmvFDjKIdL7D7znK4NT+G/9y1H3bLXzCpoasEvSwVRHnb0syjCjzOQqCLyyWw9toynHVYzUP2h1PH6+uQKA+nM1u+8M8adWQR/ByGTqo0Y34VEwnaQMbXXLmIqAGCSs6z0BoturZzBCtLt6KJyW6016gZtTpHWcjAUDK9UEsz/+jS28YHPNQwFHpzO+jcCi0MM+ikx08ewUl5ClZ8eQ4362VMuSGCJjR+4rUNG0lkgRsLOJWMPgFHCtF4TEGW0xDy9hEGZ+vh8jZnhBdkYMipfjKSdIfIjouIU/nN3EO/UklnHnN/+gSKy3ox8VsrPEQFPITL0O8ULzpwQRYJHt3cf8xMir4diXdFe/BHaiazubwUc9YshdPbN9SNSET3SCP/6GecOnSV/NXTmObxcRSxbClTV85HwvtpZHculpLsXtHB2zkwXttN744Y0wC/wFMKzcnQWBnD9+uSFCf+RluCDOoP0Jz+DehyV8bPMB/Ude1HUKgVKm678m6ls/g2u5/LP56CdOcWqp5+h0r+NrGzWqfJQHskN1d0xIRzyjyHxPFHNI+tXLwP44ssSHG2QC9dW8G0t6ynAjU9/nOlByY31OPTWTOSbiikkbXeyJdrZ3sDtkNzvqGgLzoZ32aN4MXdVxAVuQIqCg10WNGARiZ/Rr1QDi261Upktp+LyLdg8rktrGR+D6bMkSOrkpOkHZxGwgOlyNScypWkaij+aBE5i7rg2tEg8lY7SGMFd8HeKBbXP56lYUJepBwrTZo3F5HnqevcXCgbQjGrYPSpCiEmL9i4OB18MVKhogRdUs/UZGF7F5JzeCM6/wjys7xUOq/3id5uGc/mvZOna8/r6INbD9XUPKHMjJ/0L/EW5aqK49K9RzzTRvCmbbpPU4bnIKhiH5kIuP1mN10mPiMDbLg1l343Cs1twlCTLsO5EbVcb3Es1jZuZ05Ps8Bz9rCE/kQyv/GYmw05QPfN9GmdtQGt1/bkvQo6sO46yXtD99ICtRKusbcN4clRtLN7Og7JMVDaUzpyfxyP1/TE8e9dMNFfAa31LnQ81x7OQ1NR310GrxkK/NrceYgNdGBKdw6R6/126BeLkJBUPpvXXoFtsyqZkulBKpCU5nEdubg8x5115AbDZFY6rdx2V6DJJ/PT7qvoZ4Qsqb+OwkvxY6Q0rgiSDdPYCcdLODYpDW9uBuCT30bcb7lPT5uryHr2I1KZdI6kso1JSTGahy38g7sH6rG5UBhTVv/H34p70sN/WryM7aJAe04fI6fi078KpjFiBt6N74Hne0XY3SqBg0YpDm78wGdOekK91kvowXkxejJNmbYai2H9gBU1yhfQ8+oiKhsfC2tvCza/ZSn46DdknbWCnHP+8s371dH6KJs9Xu1AJQnRtOjgQ3IzikZgpCqFjx5KoV9MKPCsJV8=
*/