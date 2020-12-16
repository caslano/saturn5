/*
 [auto_generated]
 boost/numeric/odeint/algebra/norm_result_type.hpp

 [begin_description]
 Calculates the type of the norm_inf operation for container types
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_NORM_RESULT_TYPE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_NORM_RESULT_TYPE_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/detail/extract_value_type.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< typename S , typename Enabler = void >
struct norm_result_type {
    typedef typename detail::extract_value_type< S >::type type;
};

} } }

#endif

/* norm_result_type.hpp
/uFe3H7x3tIfNP/tU7SbgNf25fbpil8J6yvt/dQ/yb7YX/YH2W/iq5H+Ev+Zgf92QNE2o/lL/Bmwf7sTi3YvyHcP5OtXv1K0jfSPpmP9t31c0X7Xp3nc5b/PKNoTpN9mFe1qsG874i9C/7ATirYQrh/O4ftX5kp/wPpb60Tpv153/YjK14r2HsnX1b/o/OLT5f9TfauvF203+v7iy0H8p3pG0Y4G+bb4k+ben5WcWbQY8lNrZxUtB+eLtc4u2npQP7wyr2iHU3xGfBr0j+q5RVs25V6/aZ5XtH+k3PWv7FvyfyD/OPqu/EM631N8+77F8fkVhzlfs3bh4vmt15H/YBcVOT9afB/9qLjWxy8t4v6uVlPxqz7Ju9r/57IvaH1DPCL9Lb4OjM/yVQP248D/wuH0j/gE0u8eHl0t+w7u3xa/Ru8/3rX+2yra1yA/sf4b+ScwPsPrWL4t/puU+sRA+w1TH2t+0Tan9ZPrFX+C8wOqNyj+RfEJD7cbpT9o/+ZNan/SvwMc7FPx8dS/f8+8Ib475T+K4/7Omzk+VhHfJwX65w+L4lfAbyna7XS+4a38fF3x5Xvc+VvJHYovDXDH+YX3FO1pyP+KHpR9JvlRrvnj4aJdmnHPL92ni7Z3nzv/odnR/ED+wXMcP6yI13vc69+NF4u2S497/mq9VLTVQf+GLxft2T63fqi/WeT8GXHMnxE/nfKz3pL9BDzx8PLb0r+UHyk+Ig3zw3tF2wr6d/K+vg/51+LfSrvrw1Y+4vfviNP7hf8pYn5ZLE7vbx9zfL0i/nLK7Z80pam/AuevRumS7Q39oy2O8T3xw2j/Rk/JrjVY/+4tWZ7qw/bp/tT/PLzp4S3xPWn/Ukby1P7itD+g5uEN8cvMbT/WsiWuTyf+Eu1PypVsBdJf4o/T/q6gZLvT+Qz9Jds47Rx/+lGyaSnIbyyV7Auk35Yp2SjgFfH94Hz/2oiSHU7jV5y+f/T5ks2n91+uhPnLNXHcn+GRb4pj/pBHPvHcvyu+CfnHy5fw/JlIfBatf4mfBPUx2iuW7C6o79AeWbIZUD83GVXC/a+1lUs2EXgiTusLtoo8nR73/sRktZKdLx669NNaJTub6leIZ+n+a5fsXoif2GiWL4s/qvY71bX+/qWSHQz+de3LpaX7y2w4vn7JtgXeEl+R+qf4CnD+fqXC/TsSx/1bHvl6hcdH08PbHt4Rp/yL6oYl24PaT/w4yk/YqGSrpKi+a8nmUv2fTdT+aah/s1nJTqD43+YluxL6Z22Lki2k+M+WJTsSrm9blWwE2VfimN/h4VUPj8Rp/SD2yNc9vCGO9otHvuXhbXG038R/DecztrZW+9P6uId3Pby8TQnXX6riJF/z8Lr45vT8Hvmu+BbAq2NKthPVHxOn/Jy2OMU/w21Ltgvwuvjq1D/EtyP7aruSvUv2TbVkV5B+2b5ke9HziW8FPBHH83/FMf6xA8+/oYdXxW+g+NSOJZsA+TXlcSW7GMZPx8NbO5fsG3D/2njm5V1KNg94W3x/er9dS/YsrQ/vVrIpsL873L1km0H/j8X/Rvpjj5KtS/6J+OdStD7H9kddfBzwjjjtj67sJf8Anq8pjvWBxceAfHnvksUQX2uKX0fja58S7l8J9y3ZjfD+5f1KWB+qKk7ylf1Zvia+PrWf+JnAowNk39D8Lr4S6U/x1Sm/W/yvVF9yIr9feKDH/vDwqodH4m/Q/rivMG8dVLIE1ifaB7P+63i4HcI8FCf/sSKO58+IF6l9xJch+0wc61eJ7wu8K74FxFeqh5bsiZTe03U+S61k30m5898bR0j/k/0hPoHe/0jNnyDfEKfzu+yokk0H3jiK9WfrKNbfiYc=
*/