// Copyright (C) 2007 Douglas Gregor 

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file contains a simplification of the "trigger" method for
// process groups. The simple trigger handles the common case where
// the handler associated with a trigger is a member function bound to
// a particular pointer.

#ifndef BOOST_PROPERTY_MAP_PARALLEL_SIMPLE_TRIGGER_HPP
#define BOOST_PROPERTY_MAP_PARALLEL_SIMPLE_TRIGGER_HPP

#include <boost/property_map/parallel/process_group.hpp>

namespace boost { namespace parallel {

namespace detail {

/**
 * INTERNAL ONLY
 *
 * The actual function object that bridges from the normal trigger
 * interface to the simplified interface. This is the equivalent of
 * bind(pmf, self, _1, _2, _3, _4), but without the compile-time
 * overhead of bind.
 */
template<typename Class, typename T, typename Result>
class simple_trigger_t 
{
public:
  simple_trigger_t(Class* self, 
                   Result (Class::*pmf)(int, int, const T&, 
                                        trigger_receive_context))
    : self(self), pmf(pmf) { }

  Result 
  operator()(int source, int tag, const T& data, 
             trigger_receive_context context) const
  {
    return (self->*pmf)(source, tag, data, context);
  }

private:
  Class* self;
  Result (Class::*pmf)(int, int, const T&, trigger_receive_context);
};

} // end namespace detail

/**
 * Simplified trigger interface that reduces the amount of code
 * required to connect a process group trigger to a handler that is
 * just a bound member function.
 *
 * INTERNAL ONLY
 */
template<typename ProcessGroup, typename Class, typename T>
inline void 
simple_trigger(ProcessGroup& pg, int tag, Class* self, 
               void (Class::*pmf)(int source, int tag, const T& data, 
                                  trigger_receive_context context), int)
{
  pg.template trigger<T>(tag, 
                         detail::simple_trigger_t<Class, T, void>(self, pmf));
}

/**
 * Simplified trigger interface that reduces the amount of code
 * required to connect a process group trigger with a reply to a
 * handler that is just a bound member function.
 *
 * INTERNAL ONLY
 */
template<typename ProcessGroup, typename Class, typename T, typename Result>
inline void 
simple_trigger(ProcessGroup& pg, int tag, Class* self, 
               Result (Class::*pmf)(int source, int tag, const T& data, 
                                    trigger_receive_context context), long)
{
  pg.template trigger_with_reply<T>
    (tag, detail::simple_trigger_t<Class, T, Result>(self, pmf));
}

/**
 * Simplified trigger interface that reduces the amount of code
 * required to connect a process group trigger to a handler that is
 * just a bound member function.
 */
template<typename ProcessGroup, typename Class, typename T, typename Result>
inline void 
simple_trigger(ProcessGroup& pg, int tag, Class* self, 
               Result (Class::*pmf)(int source, int tag, const T& data, 
                                    trigger_receive_context context))
{
        // We pass 0 (an int) to help VC++ disambiguate calls to simple_trigger 
        // with Result=void.
        simple_trigger(pg, tag, self, pmf, 0); 
}

} } // end namespace boost::parallel

namespace boost { namespace graph { namespace parallel { using boost::parallel::simple_trigger; } } }

#endif // BOOST_PROPERTY_MAP_PARALLEL_SIMPLE_TRIGGER_HPP

/* simple_trigger.hpp
0n8uf0mRz5M4jkv4Gxnv5LtqX5Yy+h209wf5bt/1Oukv1iD7HRS5CnP4buRF8n3KCikTOH8duVJO5zhGj+NvZv1Bvr/wI777cJrUe7/Md+Odov2VU/8ZtPPr9OfX+O60j4eJHPSH27nSjmGrfA76w0XeT8v36g/5rrZs2uvjop/Oyne7LeT4qIwjc/nbIe+S+uOUP/KbfJfrZNpvAe1pFv3nUb6LfC1/o+UhzsMH+fmb0k4K7XYN41T/ZL6rq4JyHue7Ri8xjvB4dwV/Y227HG97KFz6reO4LVZE/+/S7rm/hvpR2sNvdNL+E4wPSfJ94b5wmZenaMcP0s9f5Tuivsbxf4G/ATSkiLwc5/7VUm73KVL/1TDGT2mv9tuMQ9T/QiR/e+Pb1O/tUqoGtneQcjPOb2UZ/I7IkfAtKbdES7umBPpZmyLz/wnGoT+x3+dp37sYBzleO56SdnR7+S7uCTz//I3vLvyolP1PKiKnm+90PUW7dPGdWRMNcnwKz2+LpTygcLwvymf3i/S7zfxtk508H72N8Wgh39F4iPHmRxyXR8P5Wzyyf3CY+qfS71/m/mlSnn5Y9isc5DvdllAfxofl79PJfp/mePRRv68ooodD9g/m0i84fjN0cnw0/dbWyXhh1vOdhLTv7bKfjnY2m/bckSztRBbw3Y9/4Pl9OvWfZZB23s135H6BfjCsk3Yfo74nOb5s/9RCvqOwUMrD16Sc5mB8fUAn8txguw8pMj51PA++Qb95u17kvcrflHyb9JdUJ6X7J/RPG/2gmfFfx3cEBhWeRzh+jcxjNrGdTurL89QEluf/TP/6GN/R+4hB2vXTHpKlzNwaLu0k0i94nO2W9Jcwie9GPasX+TiPi74aLvVvUaSskvrd6dKu6ZVwKZv5jlkb7SSJ75j8DeN/L8d9E+XJCJf+3yFlx2TafwbHaTrt8ln5rPI8u6eF5/9Pc9yaOR4/Zx7wKb4TfrFO5Pga491rfPf+eeY7a+Wzdx3Pt0EtflJvN9/hp+f8fYHvTrXRnxgfLh1h/zr+pkCllLt+KeXhKfRj2v8lp17kpp/O2Ea7/BPHN1bad4TJ9/1pjMen+S79b/G3z37Gd0luoX90MJ6zfRvPN/tcOpHPKfW7v8LjviKfk5hXukv4W2aPhUn972jn36Ddxct+jiGRT7dLJ3ouZdx7K/33gE7qPyvlpWkcL/rrpPfwNziZVx4Yp/0GK/PzHL3U1/O8lSmlu5J2Qr91fD9M5Nog+y/aQvtgvmPL4nzv4/hT31N/4XiFSRmdJ/W7S5kPFoYz3jJ/HgyT8hnGx0j6z3yOL+0h6YuM6y8yX1nNd1e/rPAdnoxf9K+EHOYH9KOEo9Qrn++A/RbHN4njEcf8aD/tMIx5toV2y3av25kfrdSJfNHS3iIf/e07jLt/Y37+UdrTJMbdd0ipvp32/BWOn4v+RT0jdzBfol0Xfkf2Szoq7aYc0Eu7Xvppebi09wTrp9CePXopFzCOFjKfXiel6Yu0y8Vcx1HvhHcy/2GeDzMT+SvoV23S/qK3M7/5DePPTb5LvIR6JdFvpjCfrNTJ51opTS6+k/5X2rqAds78/gS/7/fSHls4D0NcHyyl3U7jfOUwH2zg+VNPf/wl410vj1M4XhNEDnWPlBdawqX9wxwfLW9fzfMP/dHwcfb7COPXlznO6ZTvd1x/Mc5u8Um55xLt6SLtfBPtpVVKx4f5rnKV7XyG66S6cJF/N9c/b6G/naO90F9TWCYVUn8f88UMxvW5zG/DuI6dy/XLb3mem813nv5OjpvwEfpXJ+f1JeZz86QMPqRI/0lcV3J9cvsL2m9WMF58UvpdGK2I/B9n/F/GdUIa1yU=
*/