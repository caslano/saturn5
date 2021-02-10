//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_UDT_BUILTIN_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/udt_builtin_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct udt_builtin_mixture
  : convdetail::get_udt_builtin_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                         ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                       >::type {} ;

} } // namespace boost::numeric

#endif



/* udt_builtin_mixture.hpp
aWIxNTM4LmNVVAUAAbZIJGCtVG1P4kAQ/t5fMeFiQrVSz0+ncJcj6J1EXgxgPBKSTWkHu5e22+xuUXL632+2L6CIRy5xCd32mWfmeXam4B5+3LLgEPYuln8ZLdrzjBspfqOvd7MZe4LiQ1kz2veJuLBJeWI27E95gnqewkqVlrlnbJ/QzHgzF9dkzpi5JYTSTGZHpCvJ70MN9Y4Nn8/OvsAxnJ6cnjhw4SUcIxhrTOYo7x1oBTnyPfQeHxsKvzmAGryoUZaahFyBEgv94EkEuo+4j4nCADwFASpf8jk98AR0iLDgEUJneDPtDn468BByPzRFViIDFYosCiD0lggSfeTLokbqSQ1iQelUPOBKU8FMc5E0SBtBo4yVqWHkvUgJ8JYej7w5CXkaQq1Tde66fiYjcu8GwleuXx2/Eep4fZIpmYi9FYhUgxaQKXTAMB2IRcAXZqeGEJhm84ir0Nm4IakkcIUEhVFkalEeR1XYRhiX7XEMDVJyzLXZlEiUkXoIRfyKSH00VRaZTEiI+kCkQFCbHciSAGVOzk9eSZQ9zRv87mg2fgMQCZmBWnsM3XEN5p7iyoG77uRqeDuBu/Zo1B5MpjD8Ae3B1BS77g4uaPScxCTgYypRkbgEHqcRx6DU/LjlWp944kdZgFDT
*/