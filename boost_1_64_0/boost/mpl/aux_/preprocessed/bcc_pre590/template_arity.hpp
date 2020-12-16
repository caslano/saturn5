
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "template_arity.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
        : mpl::int_< -1 >
    {
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
        : F::arity
    {
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

}}}


/* template_arity.hpp
+evTzhgDAukTpt8RysCuHizvEFOau+78RfOIn+SHI2q1xw+H8TrilBkXZA7xycPmuRXrdq7rifzDUfnlMOYY5nM09oXw3mRZJ1A6u33W+2Ip/3zyPxgls4z82r9zueISz0Ewrmeb4u51z9sc3nmbgsqY+Ke7CupszWXPgEYZpzzoLmPve1pskDK+7iFrGV/x0LEpY9/5aYV5HV351NxPczhPWbrqQH/Xa4HmdZ73wOPqA8V+v+//vg8Ue98ugfYHh7/fN9z90P9t+4MviDH+ffOW6IP7+h94NPOV25osa3pRwvHZHxxHSFkT0AcKY4zJt8ajgX2gDDTFK1B60UHSW1GJ3ARTvIQ1geX+yayfW26Q9MorkdvXFK+skvz2McXjm6TkBk6vxIjrjicfIUacNYq3m3inwL2wGfwK/gF+DS+E38AEuA/2g9/CRPgPmAe/g7fCCrgefg+3wn/Ct+AP8F34L7gTHoDfwoPwEPwR1jbW4WA9eAieBg+b6/XxwOV2pSleYiX1NcJc/0ovupL0DF1LFa+Rys141mxXvNe0f70MxsA3tY/9LXgWfFt+03fAwfBdmArfg1PgTngTfB8WwA/grfBDOBvugivgR3AD/BhuhJ/Ad2E5/A5+Cg/Cz+BPcDc8AvfAmuj9FYyCX8MG8Buzj59i+QIK0l8S3fGCtNsCd7wg/aC4kngqf+wH9E0HDlI8s/3A+Wq3F8CGsDU8D7aBF8F42AFeBHvBjmq/naDn3H7p8bjSN5/b30b12w7GGunAeNgBdjPSg71hJ5gCO8M02EU+jC6BM+GlcBHsCh+C3eAjMMFTD/q2ApsFqYcKU7zA9UB4SvGC1EOiJZ59PRRGaO0ffmXj179M9fAmjIY7YBf4DhwA34XXwPfgOLgTTofvw7/AD+D98EP4CNwFt8CP4IfwE1gOy+EX8FMo30dat6fMbXwflUiv9dJrg8a3Z2BbuFF6boLD4GY4Gj4Lr4elsAA+BxfD5+ED8AX4LNyice5F+BncChujxzYjffgq7Ai3S18HoUDlvVrleBJMk76rpe/Das+PwDbwUdgHroF94ePwcviE9CyGd8In4XK4Fq6C6zz9SOvt8FabfrRMcpfDeLgCDoL3w2vhSjgNPgBvhKvgzfBBb/vQejl1bNM+nlY/KtE4uQF2hc/AK+FGmAM3wUlws8bFUjgPPgdXwhfgKrhF/edFuAm+DF+HW+HbcJv7HI8TtPatNXFDL+O8iSztp+slvXpLrz6wmXxmdYT94EDYHybBAXAEHKjxO1Hj9uUat5PkK2uo9BwmPYfDF+VT6zX51PpCPrX+Ba+Gh+EoaDwHR2ucvgaeC5Nha5gGh8B0eC0cD7NgJsyG18JJMAveCCfCIpgDF8NcuArmwTUwHz4OJ8F1cDJ8Fl4PX4FT4HZ4A3wPToWfwRvhV7DAeN7AGfAkyvZmeCq8ReVfEaG1ddhC/bOZ6/nkd45KDLxH5V8Ez4f3arxdDDvBJRp3l8JecBmcAO+DM+ByOAeugAvg/XAJXAmXwVWwBD4I34B/hV/Bh+A3cDX8Fj6i5+qjeq6u0XP1MT1XH1c9PQkbw6dgU7jWfL7Heq+PtxRCIB9viYrXMEg8R4jxChWvHoG6t8TbbvYp6NYvSLxSt9wg8cpDjBexIbR4cRsC6/egKV6CO70g8VJCjFcQYrwVJv2KfeL1M5efO70g8cpDiIf9staYWHtSf2ptzFc0nn2n/lSh/vS9+tM/NR/9t/rTAdgBHoSj4E8af3/WuHZY49gvcCE8Au+FCC5YYwBuhDXg8zASvgxr6nldC34Ja8N9sC78Hp4IT0XXejAangTPhCfDc+ApsAs8FV4KT4M9YRS8HNY=
*/