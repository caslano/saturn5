//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/int_float_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct int_float_mixture
  : convdetail::get_int_float_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                       ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                     >::type {} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* int_float_mixture.hpp
t1G1JPNd+czyDug+JBU1p7AlrG9htiBK+zvwRlQ01VP5MbxTph4diWVlFPMb2IaGIalDR5FvVRPVnx5BHmFw97FhAsuqWqZWDiMvV1lqU67wEk0sPoON18Cu8Mht5I6LjoYvklDmRNAILmjt0Gr0RKkoQWOiQQ96FjC1wqb+5MiPOq23TXDGLiyiUC2P4i2CebixwNndqdikEZu8h/XS31toIEdd6+UDkFK0eoL+ZfBvRb3rabS7w+WqetdqAwMgq205HWezTLMm9qNSB5V/NaFJxT+bQRiez2ZlDNv6wqeAGOEAs1AjmIFrEUcbzPs0rsQSpzLBBDvtwW9wB6xuBQyRj7lt9WLl3aZwRUzXO1LQVa2UlzoJKOjOvQwEvODCJnHDvcmJkuxaAQ0y4F+WFPTDHjS/jtlEgy7pYzOq+vcR7EdRcrkGBEFpXzbuCSaMHGOP4zJYrMQCSvtkPfo1W+9CNZPWDHWiHrlaLmij1h+M4AtZqG5Moxd20AveQnXuUHjkUBYNo44L1btHUrkJeWob/Vwwgo+oUJ0yEt/E2ZFSB6sVO3FTupagRyqzZOOxCXgMoEp0KYsMTlxNDmZ5Ooi3Xkmzvmxl09lKFp6F78DdFZq1OJU581pvogvvOs1aAFcO5frZdF7MteJtEI/HYlYB/z2hPjCoUs2aN5AmAlcPwFXUBwn0cHvAQDo2djvkuHTOemJ/mVbchruo
*/