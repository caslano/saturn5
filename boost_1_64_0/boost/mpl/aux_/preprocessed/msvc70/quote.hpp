
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/quote.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {
template< bool > struct quote_impl
{
    template< typename T > struct result_
        : T
    {
    };
};

template<> struct quote_impl<false>
{
    template< typename T > struct result_
    {
        typedef T type;
    };
};

template<
      template< typename P1 > class F
    , typename Tag = void_
    >
struct quote1
{
    template< typename U1 > struct apply

        : quote_impl< aux::has_type< F<U1> >::value >
            ::template result_< F<U1> >

    {
    };
};

template<
      template< typename P1, typename P2 > class F
    , typename Tag = void_
    >
struct quote2
{
    template< typename U1, typename U2 > struct apply

        : quote_impl< aux::has_type< F< U1,U2 > >::value >
            ::template result_< F< U1,U2 > >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3 > class F
    , typename Tag = void_
    >
struct quote3
{
    template< typename U1, typename U2, typename U3 > struct apply

        : quote_impl< aux::has_type< F< U1,U2,U3 > >::value >
            ::template result_< F< U1,U2,U3 > >

    {
    };
};

template<
      template< typename P1, typename P2, typename P3, typename P4 > class F
    , typename Tag = void_
    >
struct quote4
{
    template<
          typename U1, typename U2, typename U3, typename U4
        >
    struct apply

        : quote_impl< aux::has_type< F< U1,U2,U3,U4 > >::value >
            ::template result_< F< U1,U2,U3,U4 > >

    {
    };
};

template<
      template<
          typename P1, typename P2, typename P3, typename P4
        , typename P5
        >
      class F
    , typename Tag = void_
    >
struct quote5
{
    template<
          typename U1, typename U2, typename U3, typename U4
        , typename U5
        >
    struct apply

        : quote_impl< aux::has_type< F< U1,U2,U3,U4,U5 > >::value >
            ::template result_< F< U1,U2,U3,U4,U5 > >

    {
    };
};

}}


/* quote.hpp
EYunkhfVM+kOLuRXVqykMY3PxtjymSqRtF0Y+g0eOitjpLE+ZfqUTK+R6V/N/t481XTaz2xaL9OOLsbpOTJdTqYXmU1vkOmzVY3Tu1NN1/+R6u+qfo1W+hHm/To9v9o9LLdL5L1940n3X7TcHmKt/cRae4i19ijr7WABhvaWDT9V7nHwxO47E1qeiQxP/aZ4/rVfWWtPMz4PKvu7HAcSiernQZ+Vfn+lsQo6oCs640p0wZ3oivX4bnN0wxboji2xF7ZCfxyGQTgcNyDtM49swznv+fdow7HWh8gj5q9py3ka/Yhma206WtCCFrSgBS1oQQtP+/5/UEhkVL7c/1+nuv+vk/v/dnL/vxBRec+Xk/Hav4unV18f5TI5N+94Uj+LGCrLrSPLrUUs5sj1gdlylbdz5GbZ6jHYxuq069x/8nXuYsN17srv66c+l9R++puzivcq/M39uU/nOtdVJ3Vb6nyi2fMt9tLfwAELoWPWc0FSd6VOJ5o9F1RBvlcZi2IVtMeqWBOdsBZWx4RcXu/+na91/1evczMCeRYmSLvW1YIWtKAFLWhBC1rQwqPDE77+DwjJp/H/Nqnu/XeS6/Q+cp3uRXR24X8nTPr/d/Ls4xMYHpD76/TqLMNfH224P13ZsCzGIJH72XVk+hl747S7TJdzMW1D8JKBgOZg5njhtZknMmfaxgb6BhjS1kK9Paz3S8iRTkdVfwQKOtBfHzF2os7Yj8CDxG0oSHopoPeVdavGrB+nM8xPnwHjvOf5o55596Lbyex502VedR+Gu5l9DliATj67IfPJe8/V7x+nX4NxOk3m8Y80lFfWehNYr7KgIinKerPHGZNxkQzzErPy9ID51ygrPq3uG5EznectpPOSOp2qvhJLVNtSmd5sNv2l2fQvMu1imB4u04Wpi8a/Fz9pOv8EptV9KeYwre4LsdPs77fMph8wra57pU6ZLv9tmb4rf081m74q0/Vl/tkpptNbU0yXfzDFdPlXZNpVpkdI2bcua5w+INMBVbLbuNILWGvTsN7G8r6hjeXwZ8urNbX33r3fKWB75MCKMdSRosrno6L936oafNV2XPMXd87t/3kY7wozfP7mD7uGeRzZvLDAnYc9yixO2Ew7YTHlc/smm9s2Cy/sn3b0wHebtu/fYa3t5a9rc8tr21pe28ry+uyMtbYyb0M5L0hpM632T6FvntnYvVf5GcfPZY4tJcddOR67mo1Bf1LamE7hs5iCNfA0NsYz2BrPojt+jD3xE/TCc5nvhyoox1A5trpK+1bme1c85NkaT3TGruiK3bA59sSO2AuJOi/VmPRh2BcnojdOxwH4Gg7ElTgIN+Ng6TMyFI/icExFH7yAvngd/fFHHIU1SHQo1sRwfBHHYDeMwt4YjUE4EefgS7gUJ+ManILbcCruwun8twdn4QGMwTP4Ct7AefgQF6AdZbQQy+Gr2BzjlPXiYgzBpTgbl+EruBzjMR534Ao8hCvxc1yFGbgGbW3YR7EYrseauAmb4GZ0xy3YDbfiANyGw3EHjsA3cTLuxFm4C+NwN67EPbgO9+EBfBuTcT+exnfxN3wPHWw5lmADTEJX/AD7YDKOwmOox48wMpfPYgWPtDP055mNMTnaNXO2aSZIW6bldsycbZidiKtY9l1PY/ulbVfL/XUGEq23YUr7pYW2yy3zrLdZerOuAGK8qr1S3zVnm+Ve0pdg1l4ZP8O0vXJLV+vPWaXy/YyRWlulFrSgBS381cGWOOpJXf8rN8ujhkbroxo1bqE0A+TDMwBbS/NzKdfa02U893r8nJTHythcaQdIUo9Lb1w9LQFKorLu2weblYEEq9fcL2S1DXDNLeO9h4yXsaQzp8M=
*/