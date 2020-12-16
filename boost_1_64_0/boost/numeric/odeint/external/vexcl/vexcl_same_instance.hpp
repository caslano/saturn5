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
2ZupnRTMS94ZEey9IJz1AV1H2oVeQJvAfIkLzR+mTArKOxn/+tzraf9TiZsrexv8/okPsOot1QJ3fiIcV+jee3Vx2Xc3PjJJfV8fvKxONsgUGkNmULYGVR6UNbRWn4kwfqE6PIjpZhHLNg1Zo9cCsycJBjJAR4JB2GHmkOcUw/Ngl7/gDyb+E8LTrFMk309qTB4f2Y1ir5ALP1PW+Ypeg78nG3ozwoF+QTf6PUTRPkoaMI52qOF7oE4LvkuCtLBxmasuM3Wz3OoR6VYIX6y5gp+W9zDQ9RpinllTjGP41PFBOFkUDr+xl5fne0SXM1y008YFC5oXxFY0LXa2mBud3a8+kuXRZ+i7y4P8FnKdsAU+rfOdn6gvdt5DWzeAX8aPzVrVLgp9n/U4vwNEZrNOR/C8BN8YYBlEzFh7f3f3VnegIzfapS2hXMe4PAN4E9+MOVbJUTBM3TQN+PZzvKsznuJ+uV9GHDXx6QyPlrdr3LfR45QcRZ5fcODlU4KEkXO0fylH952LZz8xhWLYF7eafrDNtIV2tu+E4JBGbHv9JPFR1mHsvBPhTtPuNpDfRmJn8TzVhqJA366qljcua9bVaGNdmVX9DyNdpu57VN3PZd33RtZ9lger3sRSj+uNHjex3G3sN/pY7hRxc3S5h2m/eu25qDiPf7EhtCFfnuNVW97C8bJIvelfVuT/pA8+i+sVxAX7V5O4Z5AHi3+Jp48K6uEQsy4/CfFnjBd8f0HQz38W8bKvE70v/7lJxpcI6biXQh2RpxcOgw/9RQTh+mIJ63tE4Gv2wXi+fFL4zm059CZ8+O4P2svxqr2cYdrIVxD+imkjZ2bHH6FVUfazFG2LaavnULfnmjzWIPw1M06dp/isMXy+gbCklXy2cKz6FvM5W80/vmryvADhC5luDdNdZPh+xfD9jqHbbwSXKPrSYt9ejG8H0CO/xw6zLV/uyjLofNf1KwsPXz4/eIEnIp78vjfQfHfgvt3Zz1XKfq42er4G4V3NGw3Xsn6uy+YbPS5dD3qBt66H39zAx429feuRV8bf1fdD81VfUQtWNC5d6iTNhiCnzn8h9zBuVPZxDf+eNuAY2ePGxx8CG4yPKW8W5dgekqO9N97VFUv19uHxeyeKjmAfKW2mkfL8iDJIfyJ+DvQd6x9Tf7eYuf/NCAfnpN0o6mSdvbc7W9uddFFBWW518q/rSwSjbbYMP9FlGML4LLYtMl0VMXe/PscGcJYZcezj2BdJGpTDyQ05Q3ncg3CkL8989U77vjfCJn9m+pv7KP/Var7wANNFjl9DqGOfxy9M3lcgfA3zvoP9yq9UX3eH6et+Tbl2RPB5yJThYWLv13VA7G9yyozznyrfK8wY9bjC6nCVCmtZ7jBlelrxvsak/S3lfDanXvAzY81zxD5vsL9D+PfEXsE8XzAy2f75JeKvdHjxk/Y91X/tNPOkV4xe/qjy8PmsM3XwZ0NvM+V5TejgLWN2G8vwuqK3HYBvHAcEdPzr6G+q+Qbi+E6FOc/GNd7RB0i5/o44Occn69p/IB6/0LzhbYZL1Dqb8y1gJU+fUdr6spgkeZSofNLmjvO7xMk7g9Lf6W+C/8mZX1lfu6BMJi9iLK8kee0CnPbZWxKiw7/FZKn3Si9c7yMlLb/fBfRKpi0EXd5Ri34rdQ9gtM+W1v0UT+KFjj1B4cl74rk8PywY0nP3IoqBcee4JstcepN6Y8vHXs67WK+UBtixxPp/H7ZfbrpCmKIOV4DPyBHhtw39pwUbnRfcfhzzC8aePUvdmJ6e35cI3ycibTRoS+OpdGNbWyKV8qmSrpS0I3GaN+FI+m3CHj+71Z0nJPxHIL1MfKXE48FIOZdTA/k=
*/