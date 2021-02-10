/*
 [auto_generated]
 boost/numeric/odeint/external/vexcl/vexcl_same_instance.hpp

 [begin_description]
 Check if two VexCL containers are the same instance.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_SAME_INSTANCE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_SAME_INSTANCE_HPP_INCLUDED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/util/same_instance.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template <typename T>
struct same_instance_impl< vex::vector<T> , vex::vector<T> >
{
    static bool same_instance( const vex::vector<T> &x1 , const vex::vector<T> &x2 )
    {
        return
            static_cast<const vex::vector<T>*>(&x1) ==
            static_cast<const vex::vector<T>*>(&x2);
    }
};

template <typename T, size_t N>
struct same_instance_impl< vex::multivector<T, N> , vex::multivector<T, N> >
{
    static bool same_instance( const vex::multivector<T, N> &x1 , const vex::multivector<T, N> &x2 )
    {
        return
            static_cast<const vex::multivector<T, N>*>(&x1) ==
            static_cast<const vex::multivector<T, N>*>(&x2);
    }
};

} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_SAME_INSTANCE_HPP_INCLUDED

/* vexcl_same_instance.hpp
fl3vGRMJL1MKLUM1pqrl4VKW0gzeBO/C+Px0MO7Hb1ZiR1kiDN/NT7xnVGDCvDULczpP6bScOSvdFTv0liB+aotvoS0h5+NLKAsuSYrlicECwWIUZE4bol0Ffyg19kCGGXCVB7pMEuQjK3mt3KQgrO0jvxXnWpYqoVgfiKpQ8oaluD69g1Cx5CMMygVCJ3Nb2kR81Ftoo+t5TGBFIgftJCcKtidRv+P94wGc4h1s29I+rJ+cXUwNHLvHMB6+ta/Oe/0QtvM01iqxz9Zgnto7LIgyMbE22Cs2tJiJTK5egDUeayx3g/ro5ok3lGBVuvtjGEz6fWshwepGMQd5WmbxHr5rRYPzCF6+eNl6TGK/khgPrcROJpWihLecU5a1tzibWhZiomb7HbAEAGSFwmCytjYIQPnQmmgyowdwhOhOsCQwpB0jd6qsnFyLVufQ6SlqsLlgHI7GcRhF8WQUXIT21RfrrWIK0WSyoKK97hhdqGllBTHZWOH4uFZ4EpQzAxnuS5htV1a4LtUB/JLCLxpR+d765o0vBbY6Eu3E2u65UyN/YDy0MmA9MDFzSTyojcI9xh4P/M/gj2EUvw7ODqG7jSFV+2xOCrSn7YOYabe3zskHdLOgTKW2KGumUGeG58GyMzT7tGwVLhPCq2Wn
*/