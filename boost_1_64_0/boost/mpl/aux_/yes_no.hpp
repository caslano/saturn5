
#ifndef BOOST_MPL_AUX_YES_NO_HPP_INCLUDED
#define BOOST_MPL_AUX_YES_NO_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>


namespace boost { namespace mpl { namespace aux {

typedef char (&no_tag)[1];
typedef char (&yes_tag)[2];

template< bool C_ > struct yes_no_tag
{
    typedef no_tag type;
};

template<> struct yes_no_tag<true>
{
    typedef yes_tag type;
};


template< BOOST_MPL_AUX_NTTP_DECL(long, n) > struct weighted_tag
{
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    typedef char (&type)[n];
#else
    char buf[n];
    typedef weighted_tag type;
#endif
};

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
template<> struct weighted_tag<0>
{
    typedef char (&type)[1];
};
#endif

}}}

#endif // BOOST_MPL_AUX_YES_NO_HPP_INCLUDED

/* yes_no.hpp
QcILdjrOUBSylbJpnHY5+py6Ct25rZC21J/qrNiIUQ/GEeW782H87FxISY8Bt5XVsMhMGK7pbKTgHQm35vVSw6+vUcxxDGw9FPDB4kko3DYThT/ykUg3WYyOGAbOd6no+pmVlg8uAvX4PsLIiID98scgZY41zNhui9JL9sJosiqo7z4D0xQoXBSwh50FO7GS9R4sbmDe8xqfwO3+N2lr6BHM/TwEKi7b8KvlY0rdFoKfEwsq8j8Fbx5BWPnWBNKD1gF7bTwU6snSsyProUGvG8Wb3sCH8GC8umQpaie5wC1YjO439qB6syq0sG8nmtfYIFm8hTAWrkWZcRwYcJsXgnM66HN1GXgvH08aji8B/9Ni1LdtMUorL8BVpwfRomQc7UzaD1FWi4hb3nNwC6ijBz4tAJXCZzQ/MwHj8ttBaXgyKmqbAA4lYvPKXWizbgX2Ss4jMi7v4cUNZTqwMxMWlD7BwjUyyOfjBVaFQpinUAoLlDrw5bAtcHVkQLDOLnJ8twWGCI8jOJIB47nf04C5ElBZsIgOOslh8f4NtNhWHXnVBwnfwwy4anYVVIbtQcg2GlcLqQNsV6I7wkOwWO0N6RVeCiIPe/C0Rym+WvIVBcwiweTra6LhJI1saetxZfpDOJLzhbS2moEX1yN6peQOVqYzaNS7FNgotBXnHfTBoNIWMqdxBTTku2OnhCIWOS+hkRlTUVaph1a+vw2lnYpwbf55LGTk0j0sRhjYtZCKCEzE6Xcug+ugOKxpOIMXuHgw/2ILiRMYD1zad4jovWaQChKhd88q4uv7POS07zkYc0mmp99+gI98NrAvqwDbHaTphqs92JHTgjovp0GpzVFytMoCJOTukccpC3E7y06UjwwE43zEJdrlQNeuJQPuV6BSzZ8cebIWLFXLKbdcK7i8DKYPhw+DPE8q3oq8iLKdNSSuVRS/CAoQtSJl+I3f+I3f+I3f+I3f+I3f+I3f+I3f+I3f+I3f+I3f+I3f+I3/b0hIGDB/9g4Wdk5OtuLSEtISUpYGZo5uDs72BhZmzJ+M0T4XW2cJs/9sjL3Zz0MAAIAAQCQBeMgDjBcKwHi4CBjrpwJj7Rxg1KsDY5IoMLI3AUPbFBhzrYAxQxwYFUzegNnW4AUGfMNKXWAoM8fCD7i8ABh1zDJrKTB4VgDj6x5gXF0IDPFdwJBg6jFntrfKAmNoPjCShYDRIwaMRqGfdUyXAcYUkT9zG6SA4WAIDNWdf5W5xhwD/yb+jRg57XOw/SlI6msANjFHbNmiNVd9zVwT2z32jtbOVvu+90eRPxcAgLgUQcZFZtEp5GK8yedihBRxMT7lcDF0irkYniVcjLm5TK6Ui5HOLG+YZS6zL45ZPO9wMUqYxeEus2Y+AwDAPWadxxyby5TN5fqXPv5L34xM9lk4W/3im9oWFXEdE8c/dlk4OgEACC1xcnC0dl3B+a3tYvqnJhAAYADA6nRBxjj4MyYAwOIbgj/ZJsd8ZpsGf+FYAUD+F24CACh+477rvXtNkMHyrZ8LAFbfEPxJfjvz2X0G8z0ZB/Ajb87kp8ky36tfeAcmb2QMjJRf+CNM3vjpn+PJ+o2Xuv7nuWcxa/gFvn/HH9+amYzZm4EBBAAREQDgFFPO4SnXX/wJv/6zP8z+v+r4wZ8IAvAjf+2b3ZG/8LlM3vPpL+9B6p/X4v3fsbv8huDf2FjP5EJ+sFEr9ee1rP9lLaUmzWKIKP7s++pvHPlhHCurIGP3or+uZUjqz763/qK39dHMv4npAFMm7gf/JgAAZAgy0n/guABgApP70SbGH0vGH2P2V5umAQD/DxwDADpTmev4rZ8fABZm/Lwechl/itdPnBaTU9rxM2c=
*/