///////////////////////////////////////////////////////////////////////////////
// accumulator_concept.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_CONCEPT_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATOR_CONCEPT_HPP_EAN_28_10_2005

#include <boost/concept_check.hpp>

namespace boost { namespace accumulators
{

template<typename Stat>
struct accumulator_concept
{
    void constraints()
    {
        // TODO: define the stat concept
    }

    Stat stat;
};

}} // namespace boost::accumulators

#endif

/* accumulator_concept.hpp
HRttifKv/bux/hb7tVwPHfVNpLxZkS28eB2NRO3nx4rqunT0IpX1n7KUID+mUk9kUkDX0RSTcN+To9WzvTNuPuI7YvTX7+IeYPIdIYVZZ68UaLRyXI0fypFdd/IiBtmBc1Y6kkUVGoGpDhy01R8h1jXoc3BEgohwUcR0EeFS5QrDiqLppyy5QcoxLhGmExvdZAvyRwiRvtNvhEChvhzhPEdAVEx6oqL00Ohj9H5viKWK+MLQ6O5ZtD2VQb/j0+C7GlSkji86SQmNitcbhfXKHfjYS2k3ie/rKV2qWLlWi6BRctAtE5/DkELDHbY52ps0L4JNZd2In80lCv8iFjs2oVithHJt+sSlHOSiiU4d964+mYspOsls5h2imdsHGs38vT7rYVCpcREL+gTXa5CMHl3F79+IIVryPgpFXySgA9geB63VKkEP6tj9MEg4xD9PXvRUTBXbP/3NON8U3NtHnm8SNwTBSDyVZaPbSIDOpISJFmqfQfBiwqVTNqqfuExC+KCsmd8il+f2ROwFCuTDGHyCqv9jsXTLVKLKIyN6IjHw4xrZWopssTMoI1leCb04aW5XiJ6sQAxZIxpmjdyjbwPPPIHq3nsFaS2XvIKHzluxn/niGlKi5+q2mSLVYyxERWl8swSiFfHUURy+5U068MC+O5HyDdJrZjDN3IBKqawhe2/7Ba2RX3OlhZeq/fcWqiZAftuuyAp9QYjixGVcDWdQA/P1sEh/Mu6j4wBad59PJAnPu2g0EtSCnVPkigAkYIZ6NIO20fdTE79cJuhqIPO3AoEKrQ8CzyrdKSpPX90HBgqn6qr4Hs//jCJj3/p+6PpDE9OqF9VSo457VnD+Wt70LE1cO7gxa+ZuoiTn7G+ACZCV+NCZpnynQm//GRTdx9DBpWZBCAj+JXTqk0mXb2Fh6yllM/tAR3rtV5W+z+x8YMrXVOlrIG+l7xj8QVE5/WjpOgZRTmiiI5U+mwj3JeKWOKwOeacStj8uwyhuJhnZOB4Bx/lDOQ8j/XToSN9Aog1i55Tzhn7q7U2RWWDghyBdYOp0qDfOYN/DUDKcCh+Inh86QQGPq1rRGyjkj/0/VINFlbaPUND7KKSS9AD6h0WioC8tlP2PKOgT9j2Ogt6jAlCQw8oFPePXiipR0F+U/rv8waLXbB+ipOdR0mtc0jxZ0hOc/y8JzpKH2PcMSprDtxP4nkcpCzAXvoZSXlJtVcj/kbf/10DPa3BrFCoxZw2XNpRLKx4VmPqSvSg3MHWBpQiGiFeuURbZxZUSpH/4fiJPp2dkBfthJtYYUsSh6ZxG9JlfEx0FGq1lGoVaGC+z1MK9DVeHLjViDnOFcVQ+J7V12U/L+dRKFqQTeIsNYZ0Wx0Y+4PeZXrRvWcvFU53+5STG64UaEgxZWXROYAp22kUZPAUEmhOKHCpNVegbLbF/2GoTnErQyfwh1h/mDj1jK/gbmDNCDogPb+9+hVhl5I1PRTfc3yralz5tK9ZfRftQP2GS3Dyburax6VgTi3rr/nnRBSCOj2LdDMZ7ciqkRUU99W4vRdl2ovNdwzKshSfzrjc0AjKah0sRmIP1/o/XUQWbOOFShJVsK7yW9pKFg8dH3x9k+SSG7Zx/ipmeZk76/uKvTJabyP+Lm9j/dsPPIIeCJ4lNOb7CdUSRKmxDMaFotZRu9GM8Xf9KH/+iITAo9BnEvp7YL88sRABSP236RxdjHgfcLnC7xMZl0MKVzpIVJfKrFGxsUdeN+l6I3JdcJ3mNuwWvsffnxGs8Bl7jUT2FzF2GTE4tdNBuoPYh+hqbji9AVI4vYn0WvSqtQLH5ZUtOyYZMidXOVegPPCRFYcsEyYxNb3j6zf/sz3M=
*/