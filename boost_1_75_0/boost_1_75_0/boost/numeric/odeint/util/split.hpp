/*
 [auto_generated]
 boost/numeric/odeint/util/split.hpp

 [begin_description]
 Split abstraction for parallel backends.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky
 Copyright 2013 Pascal Germroth

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_UTIL_SPLIT_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_UTIL_SPLIT_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

/*
 * No default implementation of the split operation
 */
template< class Container1, class Container2 , class Enabler = void >
struct split_impl
{
    static void split( const Container1 &from , Container2 &to );
};

template< class Container1 , class Container2 >
void split( const Container1 &from , Container2 &to )
{
    split_impl< Container1 , Container2 >::split( from , to );
}


/*
 * No default implementation of the unsplit operation
 */
template< class Container1, class Container2 , class Enabler = void >
struct unsplit_impl
{
    static void unsplit( const Container1 &from , Container2 &to );
};

template< class Container1 , class Container2 >
void unsplit( const Container1 &from , Container2 &to )
{
    unsplit_impl< Container1 , Container2 >::unsplit( from , to );
}


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_UTIL_COPY_HPP_INCLUDED


/* split.hpp
JQjJbO/CsjwMJjTb3Ex50pGzrHpWGuCD61be1GCHh0JMAJ5FKa8ZgG3Xpdu9+0r8K7/in+rmaS7q/DytJZkrcv3IMJH98+CSvK5ogFThl/ThVEaayhuZ5As/HVuO/qf4a5IWw7BaUTPgjO+iB3s3kisvZXs0F5XQ7noLFbG7jvV5+HCrmNDUEf1jv0OL0vEGOQG1wUUA9Ikh6i6i2COC2X3Rym4NShUr7/DKVeRb8paNIfqH/hNeCju0QC3dPil9ZZR6bqZltz/Z7oHmqvOhXptPnkdtuta04x8Wy+Echuq3kqc1Cy9J0mPn7ZmAyaulThXLn4l+v/oVDS0Vo3bh/EjpL2dj7n1yLn5taKHG07U9hqqVDdukFXvYXUzXo3fHQLjvTkndU/qsSPVmdZf0k2AbsZsrsb8Lw39Hnbrzgv6pyCB8svdZ7m8ZeIfMWtM1KgQPmiOhpdyfX5I3EC7EqErKtIVFud92pGs23nxwMeFBtZdy9/kDNlSZ6zj5Lj/rALOHhRs5oKNrXeoTkZWAYcHSy4H7855dQX/SBF23F7U2Ep7hg/Slut8QLJrD3GgaTR6ltZndkeC/kFMep3fJcd7e8RQBvfbiNaTzQk/YLMA1ndV0nYD61zN3bywbBlyo4BsJCfOj26WuHXWIoS73ddZw518jqQETitfHDqIjTbVy4l4505VHOrOb+XWxKo+hw9uqZPh/Jmg2fPHk
*/