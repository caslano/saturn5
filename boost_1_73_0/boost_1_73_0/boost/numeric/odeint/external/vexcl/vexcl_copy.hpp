/*
 [auto_generated]
 boost/numeric/odeint/external/vexcl/vexcl_copy.hpp

 [begin_description]
 copy_impl specializations for vexcl
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_COPY_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_COPY_HPP_INCLUDED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/util/copy.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template< typename T1, typename T2 >
struct copy_impl< vex::vector<T1>, vex::vector<T2> >
{
    static void copy( const vex::vector<T1> &from , vex::vector<T2> &to )
    {
        to = from;
    }
};

template< typename T1, typename T2, size_t N >
struct copy_impl< vex::multivector<T1, N>, vex::multivector<T2, N> >
{
    static void copy( const vex::multivector<T1, N> &from , vex::multivector<T2, N> &to )
    {
        to = from;
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_COPY_HPP_INCLUDED

/* vexcl_copy.hpp
HVoxLXRA74+Xb2dnS3o/ns/HJ8tzmr2m8cm5dfbH8ckrtF4gmCJ+XSquEVyRyMtM8LiJ+f0+fe8HUURZFXPqGK7Rqo53TwQWZFZ8I0WhRYbE7kpznsd8Va1rFzFPRMFpOVksw7fjkzfh8vjdxBb9bIAyh4PBwPP6Dr+FrFTE0Us4AX9ROKe0WvNsY3mpeCmVqakN580zPft5+PTZU1pt3JylCpDL0mI279Epy0Chtj1nmlNeZUbAA3qZMMRCn9cYL7C0ynkB3l/CslTyekNXgB59An9smKLKV7Wrus0Rq+zMWSrc8dZJWbHu2BwzsbJDQL/0hoPevrXse1Ali6QfpUzR7tl82vU+eURHuKPdiA7p5Gw6HUFiNdFySAajRuEd7ea3NJI41EhdxZhrBaZcR1u7qihEsR55eNYG4xzamKEROaR+18nXmVyxLBSFML51Hr6Zzl6Op+F4Oq0VONOb+jiqBf1dN/+ltCFcbwCDSTHzxj3llQZM0tDKTucG66NYt6lY9luo1lgyhecWZg2ywxbAIPHEB2IuUabW+12n5ZJAlVgRfhQ4FGany/B0PvvrPKA7+iPvm+q4BGSx/g+dPyfzl7PFJKBhU79jSg1AflvC4jhEj+OM+zn2VX2USOWPRl365LLG0Fd4gwFv
*/