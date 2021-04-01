/*
  [auto_generated]
  boost/numeric/odeint/external/vexcl/vexcl_abs.hpp

  [begin_description]
  abs() specialization for vexcl
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>
#include <vexcl/operations.hpp>

namespace vex {

template <typename T, size_t N>
typename std::enable_if<
    std::is_integral<T>::value,
    typename boost::proto::result_of::make_expr<
        boost::proto::tag::function,
        abs_func,
        const vex::multivector<T, N>&
    >::type const
>::type
abs(const multivector<T, N> &arg) {
    return boost::proto::make_expr<boost::proto::tag::function>(
            abs_func(),
            boost::ref(arg)
            );
}

template <typename T, size_t N>
typename std::enable_if<
    !std::is_integral<T>::value,
    typename boost::proto::result_of::make_expr<
        boost::proto::tag::function,
        fabs_func,
        const vex::multivector<T, N>&
    >::type const
>::type
abs(const multivector<T, N> &arg) {
    return boost::proto::make_expr<boost::proto::tag::function>(
            fabs_func(),
            boost::ref(arg)
            );
}

} // namespace vex

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_ABS_HPP_DEFINED

/* vexcl_abs.hpp
YjOGW08Pz1QR7fEv/jlaaKiFjX0lLtBQ+BTxptCv1hd3go/Ha7i+UoAVv7Rp/qoZ6TyicMpgkxyO3Qyb5LKH2g4Juv9b9hliUEynOP+PXUmPnEDU+ke2z3F4bT0rklqNwZrONmKdMvEofQopWrcHikTNNWfEc3pSc0jdwk8+mPCmc7KrIOylaYoao8iQeLPTl0T6CWZ8j4mhkriLhzbKFAwNTyK15cQerZFZwlXGsLuz1Rqfm1vIAaHm0jfyxtnCNPRVaZ4Fe2Z6b3DbRILxp0FzarWdwghUr8HHzVSdqoudbM7GFf8w/rNfNokja5EzUvMYmtovVeAnV0KNRfGqz5yTQrmrMyWaE4B7u6a9NPnSRXS3RJBQAsUWhn7UOXwG7ucXhUoDxQHzqCkJUKhq/jaKhkM21Zr8208gucqSN1WF/qiA1AAUQLlCnq6KhcvbC7ZVHhQv73uogqR3dH6Xqx37QsclnPT/I7jbgsfA9tRt0aVR7FMyB8f0gcJjj1xqMIswI7mgZjV5n3UcLHzlXVlkkY9XXE++ZSzLBsFJipJy7IJJ6EnJAn1Hkg==
*/