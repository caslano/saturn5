/*
  [auto_generated]
  boost/numeric/odeint/external/compute/compute_algebra_dispatcher.hpp

  [begin_description]
  algebra_dispatcher specialization for Boost.Compute
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <boost/compute/container/vector.hpp>

#include <boost/numeric/odeint/external/compute/compute_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

namespace boost {
namespace numeric {
namespace odeint {

// specialization for Boost.Compute vector
template< class T , class A >
struct algebra_dispatcher< boost::compute::vector< T , A > >
{
    typedef compute_algebra algebra_type;
};

} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_COMPUTE_COMPUTE_ALGEBRA_DISPATCHER_HPP_DEFINED

/* compute_algebra_dispatcher.hpp
uRw+dFs24zLeBVha3NDGthFm98ew4qoyi0qRS1TWngdtCcZQyRkDLNHFDJfoZmQLiX9m9SMs+JHFU+JmReUeiwrjAvwABgMIBhfpdo9jG7EKSZltdmyVgBdbgFCx/7Af7PwLBULuiwChUTpCbpjbyrpeHC9HHSG0Fdc/ItQgEFItiKUyqs1jqYTvgNQE94FV3UA4ESm6h6zlLMAdhsso0/EvJa4Dcykr9r8vsZhGWFL+7WZBYDgAo79UQrB7EOvZTcytmlOuowqeuAEbXJhbh7FxH68FluNTFsAwVALgwPDwW4QIUPBZTviU3oQk2zqCue1r26GE+ABWgA2hBegAVjjllkpiY4AG/HPRWk84WTA0SbnNjBOkc7CipZylcZZKvIz5Szleu8I4Wyn/ZrDikIUBI5OV4Fq32V/OKoGTeS2/OhrwKgH/ZPqXOzz/D3tfHt9UsT1+0za0QEsqEiibFilQrPIKdSkUNIEEbiGVClQqAlYLtSIKQiJlX0KRcI0WFcUFxe2JPp/iAi1FsaVCyyYFXFhcALcb4lIQoWXp/Z1zZu69SRdTv+/fX/mQM9udOTNz5syZM2dminralzBeJo0bspGqJO1Ra8P7i6rSvWFV/q53qCJALOaNRCjUv1CZgzhBtAL+SFyEzQoaO9lr7blb7aA2HtZBrHMes3lnG6ASRVhcRyw5Bnkq9gjWXaqDcVrbc+ESNq6tUqdw
*/