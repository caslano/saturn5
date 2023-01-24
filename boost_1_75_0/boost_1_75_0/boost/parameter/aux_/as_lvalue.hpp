// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_AS_LVALUE_HPP
#define BOOST_PARAMETER_AUX_AS_LVALUE_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    T const& as_lvalue(T const& value)
    {
        return value;
    }

    template <typename T>
    T& as_lvalue(T& value)
    {
        return value;
    }
}}} // namespace boost::parameter::aux

#endif  // include guard


/* as_lvalue.hpp
N9r/ITP1f8j80d3FwdoS6MHnYQ30dOX18vDDxyeCx7oTuGvxQ4Q29/Amq1W4VX7ejKvxjvBNaHJN4+NHPKc4aSum3N3VP8YqS0+l/Kvfpw2DLIbMw7lXvhPwL7n/aZc3/+vvSVTQ/t8yOP9b7gL8guL/LCt4egBdnBXsrC0dhf5NeBfXV0OeGzhkL1BLpSxG6XRLshBBVsP0d7Svk/B4kvrlwubljBLfDCer0fWS+4o+/xgZ9sbIjVBSm5bdxrotCWITaiFIaqJOzvLp2Ef6O2RYTe5WIYX4QykkQFlqRM3mmC2OPUU03hLWtdbVR8rCGJoSdKF2Ow693ViBe210rw1YQCNRDQ8HZl2+G+DGhvqMufqEaMLqiU/YZNK/+HdJ7hOiBwpNAE8edwbhckzS4i6Oe9J+AqUSZuHlSsKvaUjVo2z66aKkSL1xqcyrSB2tVvRioelHcpEJSuJjM8qUOgbfSvhFl3Tv9T4KVFua2o6nyAEc7Pf35EjmtMTqBDsdT+qE5CKMKsFmqb6GOdZL4smDnnBLvonPCWqmnwUwIRV4D2JCk50ythKB9O+dLqKALqcDuUnddL0mP/cSluiyMnHsQFNZBrVI7s/MjTdwIJjhGG8jttogeG4HqtS5EwsusxVMJpDrgK9s0XHVvx3Fg0H/yqnkgmwEcjW4WT98vX19VbF3XHbhnlKDirsoPYzfPOnN3gL1Pj4GkS4D
*/