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
NcggAN8tmMq1wsUv8hqc6a1qhWNZDXK4VrhHIhd/EtcG3iNkYZaYolrPLn2onqzeQDJt+jQ8lG+ZpPfYTOtlbcKMflJXyiRubeKAB/YlHfCYLkr2An6646VPA093kGgJrXJrk6c7+mqnO1rj6Y6MguaOdrzMjnZsb9/s8V+iq2WlOsZnSprAeKUQcCQFP+FI+7YFIl3EkW7ZkZQlQsgjKW2aw7tp/Uao9VifPi3VJokB55taYsm6r/c/zLlllqyPtDjboINvocSyq5vPNuhsXdLJJraSW3ZK9ONezRahbhYStYknmzVrD1XEnc0XEWyPK9njNWYUX09HGR5++XJDo/xGqSzyKC2VKhcPfPmyJiN3X6vJlL6Fd1wMkCfjfObHLyuB5ruGl3X2sPTFy9r5Id9Ll7XlzdxN+tKo/4lazSb7nk36iY232OkNWuqtY26yx32F5UPrhP6b9LVBr036QrzzJl1T9zBLT8uzqcxNy7A7mZvWHhnMTTv1/Z8NvEAtnwZERrb8UGGAgE6Cd9xLVPFsVvF4XxTLhBYesZ3qGtk94/mxePkopAIPjN81ZDPxFfjZ/R9Psq0FWiVks5v6qOEczE3ca8oevYyixwLpKZ+taFEGbdHAaNWzWZJS7wyk1Wf7sxcblcJ3d0MV8do1IYsgtdN7f17UbCleY24ak8/+qa/kpD+J6iwqlb1crlPnfT9c1nbb+/yohydB
*/