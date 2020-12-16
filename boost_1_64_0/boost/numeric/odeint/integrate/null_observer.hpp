/*
 [auto_generated]
 boost/numeric/odeint/integrate/null_observer.hpp

 [begin_description]
 null_observer
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_NULL_OBSERVER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_NULL_OBSERVER_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

struct null_observer
{
    template< class State , class Time >
    void operator()( const State& /* x */ , Time /* t */ ) const
    {

    }
};

} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_NULL_OBSERVER_HPP_INCLUDED

/* null_observer.hpp
4Eqa9db695Kq95vq9wRV19cVvELBZ1bFdWMvia8hb9Fz3vgu5XRHzI8ibiD7J3ciX/sId7HcWeas/N3GLnyfeNv12iLxfoA/rYf3EBf+sLzZrX7fon5/W/2+Xf3+nl6LIZ978Xcf/u7H34/w9wD+fqx5Y47/ieg3y8Tr9iDr9kPF6371+6d6DYk0HsLfw/h7JEeLeyCk9ZAq/wt9to7lf4G/x3JleU+nKitrucMFXCfrX5s2bDfj/ImquFxCOUO+7lsD8nTfMZBfTC5PGprXGZq/rYq3OZRPKBfII9bm3yFPty1s+y/M+frfs63nyPlypmV9R79TXFEq+5463pyVBfCH3Xd7XtaKWFZwrc39q+Kr90OvV+PvZv4WPKkv7ATTei5imnORTp9r0kMB00rWN/r8E8r6DV1fypFp3iXkHq2eQ8z6m10T/I9ag7PysmuVE6rVXME66vehC6tl/c/SsnPTJOCqfNTN3C0hre+ovriLv2U+knV+PR/tVh0/23xmYfxs81M42yxzdmFwdEX+PdtkcxNuF4SHUelwCiAXF3xKdUR3E2x+XjoNh7esbJRAMjGIic92Behk3xsorQ7LR2sC4Yd/iYurLjH096wWLjeNIYa+5nN7Hj5lHj7vVHweGCef2gI/n3d5+ExTfBYVjI/PZXn4vNvDZx/F5/px8rk3j9ze4+EzXfF5bJxyeyQPnwoPn/cqPs+Mk8/aPHz28/CZqfhsGiefTB4+szx89ld8to6Tz4l5+Mzx8KlUfM4cJ5+z8/Cp8vCpVnyuGCefM/PwqfHwqVV8Lhsnn2vz8Jnn4fN+xeeucfK5Kw+fAz18DlJ8Hhwnn1V5+Mz38Pmg4tMzTj5X5uHzIQ+fBYrPrePk05eHz0IPnwbF56Rx8tmSh0+jh89ixee0cfK5Kg+fJR4+TYrP7ePkc1MePod5+CxVfLaPk89jefg0e/gsV3yeHSef5/Pw+bCHT4vi8+Y4+RyQZz5t8/A5XPFZMs75dGkePkd4+Byp+HxknHyuz8NnlYfP0dq+jZPP9jx8jvHwOVbxeWScfD6XRw+O8/BpV3wuHqceXJ6HT6eHT9cO+KMP5eGz2sNnzQ74O8/l4dPt4bNuB8bP9Dx60OPh06v41I5TD6bm4dPv4TOg+MweJ59FefgMevikFZ+2cfLZlKd/hjx8Nio+p4yzf17Mw2eTh89mxScYZ3vK88jtBA+fjyo+VePkc1IePid6+Hxc+71j4OO/d5jEzoK7b5nqSfWm5GyoB86YdZ8A3wJ+N3+S380lO8l7Wt7zwozbkq37VlX3ojF8o6/UMWDM+SDhIfcT5A4V3thr71XvvMXvSsxjTJiTVX1KxvCtv68/Jg3j12GXJhRZIG/FnGLb2zHUjajHPPThWFhgbn+9tFr2Zj5XLeuSh3FdOF98nFOBW0idCdOnIV0k54pdXYtVXRdSFqdrWYxTP7gmw7WsPLEMx9V+3OGpjq9Pn4X0UBBftzq7Wr1jj9+6HudWK3ltHSG+olOVVAaX7rKNtMBcnc5jnQ6l7GdPzup8V+wcz/lOlkIjp69ujb+7dwDn2bszPZsb6sN7c1Fszwuqx3ZnaHqe9w8udOWjq9MLqX8Xaf1DWwfWe1pLsG2v126Mk0Yosy9RZqtYbxcz3txxnDs5rDvP6hwm+9+XON01ciR+cRDdCwjRD6YOXxrTYXQjSaoriBY4wptymw5MzkskndXpzp3PMUBp55fZzoPy04p0RCgJSN+NI52+EeR1OXB4XrJpEWFXOFlFWigyCuPNBzmZlcj9MZcuVTYRMnB3BrcpGZaNY3y4c0qkGwTtgfRrR+53Ee+WHcT4C19TvIrHKKNETC7rGQ8A6eg=
*/