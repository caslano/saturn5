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
8V7W9QfHObLxdUR2Edfxyy/Pbx1JHpOt/TRMXZqS9lPsOjZ8eR7raKMBpew4Q128cKSrfTXvy3PNtXOfP5yiPstYn66fuurzP1/8N7jBlvV56sr80WnqasM32FX0qlZ+0XFVd3S1BmlufQ1wM02gTq0NrNPH/xPZTLAAbB1wFUojQwwngGVf6bDnYZy/tdM472VdjvwuasvTONPPNs6oub7D+niZreYwQrvoua47fNa5dl6DYuos5UM2oCknu1qDyYfPF4fTGL3k8Eugvq0FjGJuPRChmDHwsxw+T/jh5N87SZNfyXDm9zOdaOZth86TZrp1mllEXVq/bqcuf/qCL7Mnlmb2OnSuvXaWsyOCS6fa6COV7CPHD3Tc0PiJjw/iJ/ae8/zo8A13NLyfYt/IYt+4/WDsRCR9JgUHz35GRWjGxDaiGdkMMb79PpZmVB7sQDOi8NNCwzB3Y28O+K7jXnznQGf8XAf8r4D6YMUh1TK58ZlHSGnbUrMqxj8CniyGJ/ApyqCs/n2V7imxjHtKWIo6pSPQ54VSs2JuzELVxR6UpUVnE+Y5tU5DfApSqvBuYU2w+sQDlKOjq3rUlDujndekLuhckxr5+JdOGQQZtUWSUkA3SvArlPrLZ9OLUuNuQLGAWQ3uOYXjyD5bGWo17jjwU2p7WTh3SGRP8+Hk9sSQAJhSxWn+Mc1npkLYIPtr1uLT/ANkmIhWmauv
*/