/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    mutable.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_MUTABLE_H
#define BOOST_HOF_GUARD_FUNCTION_MUTABLE_H

/// mutable
/// =======
/// 
/// Description
/// -----------
/// 
/// The `mutable` function adaptor allows using a non-const function object
/// inside of a const-function object. In Fit, all the function adaptors use
/// `const` call overloads, so if there is a function that has a non-const
/// call operator, it couldn't be used directly. So, `mutable_` allows the
/// function to be used inside of the call operator.
/// 
/// NOTE: This function should be used with caution since many functions are
/// copied, so relying on some internal shared state can be error-prone.
/// 
/// Synopsis
/// --------
/// 
///     template<class F>
///     mutable_adaptor<F> mutable_(F f)
/// 
/// Requirements
/// ------------
/// 
/// F must be:
/// 
/// * [MutableFunctionObject](MutableFunctionObject)
/// * MoveConstructible
/// 

#include <boost/hof/detail/result_of.hpp>
#include <boost/hof/detail/delegate.hpp>
#include <boost/hof/detail/move.hpp>
#include <boost/hof/detail/make.hpp>
#include <boost/hof/detail/static_const_var.hpp>

namespace boost { namespace hof {

template<class F>
struct mutable_adaptor
{
    mutable F f;

    BOOST_HOF_DELEGATE_CONSTRUCTOR(mutable_adaptor, F, f);

    BOOST_HOF_RETURNS_CLASS(mutable_adaptor);

    template<class... Ts>
    BOOST_HOF_SFINAE_RESULT(F, id_<Ts>...) 
    operator()(Ts&&... xs) const BOOST_HOF_SFINAE_RETURNS(BOOST_HOF_CONST_THIS->f(BOOST_HOF_FORWARD(Ts)(xs)...));
};

BOOST_HOF_DECLARE_STATIC_VAR(mutable_, detail::make<mutable_adaptor>);

}} // namespace boost::hof


#endif

/* mutable.hpp
tnUJ0d8BETl+PySoSZ/3j/XEH5zxNdTUInXUby1WPD5AEK3Vy1EY8/DPtZWWYtLm38KCB/mfhz0/yWpcYCctgpG3uiE9t+T7U/A10jllJ75w1wF/8yL7Ph8bynVOaQGuslWVOcF+tCqcZtyqHqPtbM+CW4sp8Be/jegoaXE2f8piIfL9lhdyFfXDucX5yr5VwONsuhDP8LxeFMRMs0Txw7llegadLTNRZTbnlhwrTh3zsdnFX+eWKmtJa3Cm/6KeFIRO3tAlB/8i9nwH+b2Hig394RGOL2OsoM2l1yGn/TZCN9Wyth4+118x8E8Cfls2h1XIA6hpb7C/VgnydnPNNnvJduc1m5ngVnZI6AERI7U9yKM9S+f3mkWz3aa9gZ8FoL2QgsBAOQk6RnoQL82jtQIy0vMtr7iDVUe5mH7ZqJxtKPe/bpG2CBpKlky3w64QYfBeiey3fa/vOi2jJAv3Y7bb4DQXKVd3RD75PHjB2oxzs3Bz45MvgtNwJ+ZctzU0OPLJl8HytRMyznVnwMPuJ7HgqLUTup3r7hYsIj06WYuSfF+moVv2X4xG0d1A4DmICxuv8U5xCS0FRY9Z2VPmlyU7h3S6qcdLWhbBRC3XsrxYa+JB41+vBjLU5KQMX+4Qq3/HyvJqxBV0iRnP81pKhalW/90qP1wEIJ/uU554GdpAdy1/gSShyzPhf/Nj3M874R16Heg9+ezAuEjMJra4iEtfKf1vqrOou3nehm2xq13iT9DqYCtRQajw5ZBfElUFo4L9PUKBfhbjhQAibGhQZ0VOJmzEK3Ib+niFlxc+ubZDtoNCbyp0gqwZDU/AGUDWezFdhuiuH1Z1VuRbKQjeeyKmn1G9y5KjVWr9aB8a34AuHYRHOurTgbrCgUBAvqldRx68z6wyfEiozW2ipaPC/e8QRZT7nPd9WH+W7O9Qt3aI2fPeHkvwQFAFkioKaC0rrNEP9YNTtNkurUOr4GPBSKu9vQcfC4bcxXuxRO/ZpS8I1/5VXwGWDkTyCU/oyQtUcuMAqoYkUzia6BRqIVsNlTMCprTS32O4lSP3729C1vUytcoKJ8Eqx6F/59K32AP1N+lZpXcMnIZp04LEqPKIb/EP/JG/8rHxeZzNCvIxMtyau8wX30CH7GAdtK6f4+Os+JNr/CmQiHDehOIc8tUnnNzYBbJUcCSp/aNuP8ug7oUsgrqDUjaNEuo8zmDlZYJ3v9/M3ldf/2EpbOhv8nzaFRaOc4q2mNnZkhHsToKP7molV6tQknmod2fLvOAJs3VoZ0sZbL+fOfjiKvesUG+VOjY8L3SKV0xi5Y5Nnk/NV0YTl3Uae9pO98z8ULYq9VS+vPnhOuhmY8lQz5UvWKwyCcPu8EE3E4MOzftrHXH22wpxdaMbMSn2qpPlIuTahSfO1f4XPRdt2YLHL+3XWbYQpiGRF8qonvZsSlYPNnpgr7SkT/biPsGHsZiucYEzXWdTObgOd3WNl/Xdx38U090b5aL7CrhhWpxNg5Gt1/6Vu5mdkcl7ITym1P/HPJhszWf/nxBHoaoq3kWdXgrdFN6Nljrq/mr0PjxY+LxILMQwQJeTLb+Y/VeDOWTyAQTegA9MD0kdexHeciZHR+b5ovXgLwCmoPgocfMXUvDIg8+luTg7v6Dk49B50EOVsHz89KOyS2rEb/RfKD1K/hE3/bZDb8kCmK8VwtAUX0WW8ACSoLV/0HrOOjK8BFWvocoqr3jwHV0H67zOhzZHVTMAGQOHY+9t46V5Im9jGgqqo8fxDJuCtILoGTVRq7hwHzOFicj8FDKTxYX0l1Lj87IYFbIwG8AkXPnFNiuxduheZiPl392LfP9Sq6QpyEd187XK+aQ=
*/