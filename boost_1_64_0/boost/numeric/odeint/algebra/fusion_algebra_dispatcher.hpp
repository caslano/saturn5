/*
  [auto_generated]
  boost/numeric/odeint/algebra/fusion_algebra_dispatcher.hpp

  [begin_description]
  tba.
  [end_description]

  Copyright 2013 Karsten Ahnert
  Copyright 2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED

#include <boost/numeric/odeint/algebra/fusion_algebra.hpp>
#include <boost/numeric/odeint/algebra/algebra_dispatcher.hpp>

#include <boost/utility/enable_if.hpp>
#include <boost/fusion/include/is_sequence.hpp>



namespace boost {
namespace numeric {
namespace odeint {

// specialization for fusion sequences
template< class FusionSequence >
struct algebra_dispatcher_sfinae< FusionSequence ,
                           typename boost::enable_if<
                               typename boost::fusion::traits::is_sequence< FusionSequence >::type >::type >
{
    typedef fusion_algebra algebra_type;
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_DISPATCHER_HPP_DEFINED

/* fusion_algebra_dispatcher.hpp
Tj6P5y9HBeZtcRq/HfFNSb8U87Yj8Ib4qz2f1n+TZw3WT6svm8f64x1xrJ8gvkGP7uOqL7d83j5IiTvyd+ORebtLNxvrGn/r5nH/eiI+N+Wu/9haL2+7p8A+Xj9vc0C+UsnbMaB/uhvm8XzM+kZ5PJ+vJY7vJ74C2Sce+fLGeavT/cWpPlt1E31f8j/Ex1P/FV+F9OemzKseHosfb7B+sFke89tq4mQf1MU3p/MFxZ8C/6Czed7O0I8JDt4Yo/4P5wMm2+XtPqhvGu2YtxN63PUZWzvnbWNaXxen9b3aeLVfCuoD7Jq3fej7iGN9Hg9veHhTfFX6PuLbwPnUtQks3xCn/Iy2+AUG9Wd3Z/mW+DY97vmpvVfedoL4Wm2fvB2SgvW7/fJ2OZ0fJE7x7Wj/vO0C37clvsg+GeW4fu3AvGXEaw793z0ob3un3PW/m4fk7TzIj4gOzdsBS+sLDzN/HZ63W8A/iY/M2xehvmJTfCTF3zy8c6RHfx7J/S88Km8N8I86R7F+sEmsH0Jxit9UxfdPudd/u0fnMb5ix+RtbYrviW9B5xOIr0zrx+Irkv0qjvEjcVq/s8l5uzoF+yePy9skOh9HnPaPl4/P208ov1u8SPpffBT1nyn6/vR9xUcAr4nPoPwPccyfm5rH+G9V/BTSn+LfovadJv1G33caf/+uONZvnM7yZQ8PPbzi4VUPjzy85uGxOMXvwpj7RzVm+zHxyHc9vDyDecXDIw+PPbzh4S3x89Ow/2O2+jfV75+Tt9+Af9I5MW/fofXTk/L2Dlw/PFX+Efmf4hOBV76at3IK9s99TfMv1A/onrbo/iBfz9u5FP88nXnXw5tfz9vPyD88I2/zML9d+iet+ISDR/M0P4F/GJ3H+jf28IaHt8THUv7A+Xl7m+L338xbTP6beAV4+C1+vqr4YeAft8VXpPuLo//4beZVD4/F6fm64vR85UbeCnS+53fy9oeUuz5k43t5Ox3OZ63/gP2rrjjm//+QeVmc4l818bXIP/JcvylO6xt2geIHlL8kPsPc9XO64gP7nx3cLmT7OBSn56+IY/0pD294eNvDu+JYX+oi5pGH1z28JX7RAHPE3y9m/zERH9g77pBvXZK3g/QBOvo9erj479V5+6N4a5GPPQyv3JDn/SHiM6G+QPUmnr9q4stT+4knUF8wuVnfF/yn6i0e+06c/Ke6OPlPiTj5T3Yrz2+hONqv4uQ/ReLzwX+qt6W/yH5vs/8U3Z63H5B+uIP9p1B8FF1fnPynWJz8I7szb6dBfbymOOaPi5N/VLuL/aNwAftHNXH0D8TJP6p75Bse3vTwloe3PTzx8I6Hdz3c7mZe9vBQ/Czyn8TRfxI/HuTr97B808PbHt7xcLuXeejhVQ+veXjdw5se3ha/KO2uL2AP5G01Op9V/Pc90m0u/zDh+KE9zDwUR/tF/P70EvtomPXp1mN5O5nWLx/P4/kfHXE8X/gJ+cfm3h+SiM+F/L34ScWfwb+Onlm0/gLx/WfzthD2T9cXKr5M9c3+LP8Art8SPwV49BfF52l/oDj5x/Ff2T5siq9B+t/DrcP2W00c618/l9f+HZh/ntf6OazP1V/Q9Wl/5d/yeP5NQ/wosK+iv6t/kn4SP5T8539o/Q7qY9pLefsx+I+JONlHXfHNyT56We8H17dX8vYA2R+van2K8hfFcX+OOK5fiG+fcl+/8Xrenof2bXW1PgTxJXtT7QfxldpbebstDfUV383bJ5If69jfEv2b368mjud7ik+k/LUPuH1DD6+K4/4lD6+Lb0Xzj/h1sP4Yf6L1jR73+lmrp2B7Qv8MewsD328bR/30el/BIvJ/xcfB80eZgt4f7Fc=
*/