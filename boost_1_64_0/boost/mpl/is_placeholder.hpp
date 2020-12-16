
#ifndef BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED
#define BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/arg_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/yes_no.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T >
struct is_placeholder
    : bool_<false>
{
};

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct is_placeholder< arg<N> >
    : bool_<true>
{
};

#else

namespace aux {

aux::no_tag is_placeholder_helper(...);

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
aux::yes_tag is_placeholder_helper(aux::type_wrapper< arg<N> >*);

} // namespace aux

template< typename T >
struct is_placeholder
{
    static aux::type_wrapper<T>* get();
    BOOST_STATIC_CONSTANT(bool, value = 
          sizeof(aux::is_placeholder_helper(get())) == sizeof(aux::yes_tag)
        );
    
    typedef bool_<value> type;
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}}

#endif // BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED

/* is_placeholder.hpp
Lxpnqs13vZp7WCjqFSU2ME9Q4xSiRntjo/YunFPh3IVs4mUy1sv8nraFPJsdo8//Mo2VV5Jsq90oKmhh5fCFmfalv/aYRlks/sVb7P3QZik3X9taZr46zpNWogkIn/D8p8Yw55YT9i9J0Vaf+TxVQFc9BNH0wPh2sxgPkzhhMgDID1vYj5nG1H3pbNX3V1SaLkbveOj8C+OrFxiyEtXyRWaRX/Q+3Fhh7etseqZ9SJUHASwV6r0H3aPD16nGW89TBDhobn2bVjih63qVy+Wb1/pOlOEhurU1YPbE9CF6owoXst33QMQjBHF7g9/441wDjY+fyeoUty2w3qlxIoPmd6l86pFOan2vs/l61Xzr+3Jk9ivLNO08Y+xEhjidsJutz6Ea5UDunoAlB8rTDcHO5X7LH5dIjgbejU7/wHiYP/Z54uaziI/2wt7qUWySO4tvVnjPF8T+Eplak6KbvC7+9n7N316r5+NH/kNjcGm/m8FNuRjcSQ2cebVf/GnfIb7mLCWPirMzY2lNu1wjKpACK/nVP7WbftYKz6PvfZNFn7Ok95MchaqbVV/M+X8OHJSv5M7/bC+YJLpIY96lPpxgnytT1exXUyX9+T+uUiDLIhFHLKv50u3bJ8OvnmR5jSuRX3Vu8fzcm++V5huU2MAyDnne9FHVVSDO2/nzzjhw/pCdXxr+s19wYPif+7ai+Wx/Ud3B2//Xew/c/oteWjQ/cY7mhuwpeZo9Q6XtH6C4q+867RzZKmuqBQGr5fvSQHutvqblc12z7HVWlwfFn9+BgmlMrq+B6NFuy5pRS9Zc7LW2YgBbcTHd9QV0T7zytInYu71qEzbQ4xmVLs9By1ZBIverHw5YG/+QOE6O/wFeDeCpFoDXehwAHp97Qg9aYZX4OUtYr+j9AtcRVjHz8pdzhe0NFMEkHBpsFnzm1dgHrOPAnzPfcnD8ibz1wPjz/oYD53/5bCu/WHyWR5vd95fjyt4jg/+1UYgWn0473zr1vOg5Ho916jF1ZMXvKkaqrwLLx64W7BXOmQjsPNYAw/tti8V3R3IRpUfEZhYBpKXCKaggz2IuB0N7heVMqu3kxCZHEzfoJoa52DTaFctUNDEsTfyDzGWUBkCJHzsqnqcrDrFv2vMNqYpDUvFuVZGC2+LEFkfN43TNQalJf+GDquKgVFzH+TG1mGuKFMLL2LKr4mJMsqZ33NP2OrEdabx+HAnJgP19lJ4e+ANc6nxyqfV12k8wb6sIRCo+sNJMnaJOYDcBSnGNueevMNFInhGWnw2B9PmJQau4iBcXAu5dFJ7DhZYthG1e4gFdXoNgnmB18cvEkJ0HWdc0VHqkT13Fhs58kq9iH9MH+N3qKebXwZwkt6rjAIrp/95g8UuTgq+N/Q69PRF/G9PGlbWUwVc940vjmY434i4Caocb67fszioiFrpdLC9NHinUa02Gow9YR6sOEeUk4Nhs6v5sDfx42ifnAp6+oNGYh6AKojAmFOnTqTtYjuegXSO+tldQt3g87+e8odvlfbrp6AhbtQp9UJcNvT6KWWUgeR0uAVH4lefII+QU6GTrxy8hFrKDgvJvryso/8/IAcoPFJbfrsuX9v8BMdu9kvSNEAiTXGFqDD6OTOrfbccmvuPTW+ndredjK3Uu0wcB8fxhvc1fUYNE99FvDUXJaxewJapGNuW19DLVUvrVuIFun6uPDsllAUt+92nB3c+mLjjHoqlZpG/3eqxjyHKGj2GJk3lKF1XRYVnFvPOzT/j/6138YX0GNvmczPUT9rdx61uK35Lrs/g/4RGLpd5JfFVLNah0SMn1plj1321KnauqUmxw7CSxFmOOYOn6UXzpvFv+l1ZW+9LlZs0=
*/