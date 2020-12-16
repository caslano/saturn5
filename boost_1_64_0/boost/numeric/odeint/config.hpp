/*
 [auto_generated]
 boost/numeric/odeint/config.hpp

 [begin_description]
 Sets configurations for odeint and used libraries. Should be included before any other odeint library
 [end_description]

 Copyright 2011-2012 Mario Mulansky
 Copyright 2011-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_CONFIG_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_CONFIG_HPP_INCLUDED


//increase macro variable to allow rk78 scheme
#ifndef FUSION_MAX_VECTOR_SIZE
#define FUSION_MAX_VECTOR_SIZE 15
#endif


/*
 * the following definitions are only required if fusion vectors are used as state types
 * in the rk78 scheme
 * they should be defined by the user if required, see e.g. libs/numeric/examples/harmonic_oscillator_units.cpp
 */
#ifndef BOOST_FUSION_INVOKE_MAX_ARITY
#define BOOST_FUSION_INVOKE_MAX_ARITY 15
#endif

#ifndef BOOST_RESULT_OF_NUM_ARGS
#define BOOST_RESULT_OF_NUM_ARGS 15
#endif





#include <boost/config.hpp>

#if __cplusplus >= 201103L
#define BOOST_NUMERIC_ODEINT_CXX11 1
#endif




#endif // BOOST_NUMERIC_ODEINT_CONFIG_HPP_INCLUDED

/* config.hpp
etT4A/4gEi8bVb/56PZpAs8S/n0Xm3e36fi3iP5Z1FYLa36EfEra6jrKPlzMVpcQ6/fU4hh/lH9ucbr9asCp/ZMGc/8Wc/82c/9R4LNR+/dL0HgK+EyU/cXgTeBLEONndAm6/vEl6fonlqTrP7AkXT93Sbr8jSWZ/lmS6Z8lmf4BPkLJr6Vs9Yge3xHxm8vQ9Rtdhq5fYlm6fgPL0vVLLUvXz2XuX2fu32Du3wI+O+WfB35lEL8wfb/99RVtNbkd7X8ZXZmZP6sw82cVZv4weBN4LNjfmq/f/u7qNuIz8BkRn5FZi27/2lp0+9fXotu/CfzMwP6cq5/+WsdW61D7O+vS5UsCJ/3D69LlywBfjLBfGsC3J/DEeraamCof8F2o/aP1mPm5HjM/17fVpYR9Ngo8T+gvdwNbbUG0fwf4Rjaxv7Cxrd6n8k/Z6m3CP5XazFa7evWIiE/oAN+yW9d+/M3RftT4BU7539UWtpogiP9ZqJ99shXsi8D+m7mffN3GVufr+RdRvh1hnwEHhjz6tN+grTYjzifUcraafkLsn0fcv1Oy1XPgzxxx/2TZVrfGeuTbX/l72OoQwv6r70nbt00GbwMn43+AT42LgajzCfvbZHzhwP70+skFvp+W7xH2Zw3zV7d///w7B9nqasL+bh1sq4v0+InYvzvMVgehMCtG7Q8cZas9NRaxfj+aWV8An4FafwIn/WPAp6PsGwZvAe8Q/oHM8bY6ixjf7gm2ahH1z5xI17/G4A3gpH/zRLp+HeBLEP6DxEm2ahPrh+TJttocN5s5qn1Ot9UJBD9xBtZ/xPq0dpatFqfqB/wton07Z9P6cxT49JT9fQ6t/xLAJ6L0I8MfYPAUg2eArxdifeYv8Mmo/gc+KSW/GH78XBpPMngKeFZfR+hf4MeME61/ahBO6wTxAzP3W/9eZqvtqPF3ua3mtKLtn/oVttqJ4MevhPyj/FtX+v65rSPis92rYL8T9kfiWkY+Xsv4X66lx3ftWnp81Rm8cS09/psMvwV8M+p8Q5MZP8DJ/aMmI18Zfh345JT9z9y/zdy/w9xfXUfz49fR+ScZ/sB1dP4Zhu8y+dcZfoPJv8Xcv8Pcf5S5f/x6pv2uZ9rveqb9mPvXmPvXmfs3gU9HjT/m/h3gU1Hj7wZm/DF44gZGfjH81A10/V3m/nXm/g3m/i3g01Hjj7n/KPCpqPa7kWk/Bk8y+ABw8vwRw3dvpNunzvAbNzL+Q+BTUeOTKb+6iRmfwMn4LOBkfAJz/wxz/xpz/wZz/yZz/zZz/1Hm/upm+v6Jmxn/6M3M/L2Z8Y8y968z928w92/dzPifGDxxC+PfZPAagzcZvMPg8VtpfIDBXQZvMHibwdVtNJ5k8AyD1xm8xeCjDJ64nel/Bq8xeBP4TNT6jMHjd9D4AIO7DN5g8DaDqztpPMngGQavM3iLwUcZPHEXjacYvMbgTQbvMHj8bqb/Gdxl8AbwNQn/zEDLVrMQePNe7C9Q53vus9XaVPw+8AP0dVR8r63OJXD1gK3movIHvgGVP/A5CLwFfHEi/lk9yNgnDJ4ATsbXP8jYVwzeAb4psX+YeojR38DPI/gDD8M/SJS/+TCj/xg8/ggz/hncBT4HNf4ZvA18VUq+PWqrY6n4IuC7EPHZ7mO2Wok4X9bqwafu1z6PM+OLwZPAByn/zuO0/zH+hK0WouQn8Dkp+fkE478HfoqXT1T83JO2mjDwz0/fb/w9hflPtd/TTPmfZsoPPE6VH/iB1Pn/tq0cLV/7l189i/1vKj7tWWZ9x+A1Bq8zeIPBmwzeYvA2g3eeZeJPn6P7JwH8MxUdf5d6HvtDOv4vYny9iPhb6nzIi4z/gME=
*/