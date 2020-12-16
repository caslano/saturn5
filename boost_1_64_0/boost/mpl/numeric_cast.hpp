
#ifndef BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED
#define BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt 21/sep/04: portability macro for the sake of MSVC 6.x-7.0;
// resolves conflicts with 'boost::numeric_cast' function template.
// use it in your own code _only_ if you care about compatibility with
// these outdated compilers!
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570) )
#   define BOOST_MPL_AUX_NUMERIC_CAST numeric_cast_
#else
#   define BOOST_MPL_AUX_NUMERIC_CAST numeric_cast
#endif

namespace boost { namespace mpl {

// no default implementation; the definition is needed to make MSVC happy

template< typename SourceTag, typename TargetTag > struct BOOST_MPL_AUX_NUMERIC_CAST
{
    template< typename N > struct apply;
};

}}

#endif // BOOST_MPL_NUMERIC_CAST_HPP_INCLUDED

/* numeric_cast.hpp
N8f29/BBtsPJhLvtvHxuv/OyNwNjIMxo4Knh/a9FA5y0aEA/eYGKH9vLCzUcn2TPysuz5LLMzxyrzz578SeLmioGNUzILfRHBtLrC0H64nS/05ij6X5UywJv/dhsrzw4vp1lkkHbz8u0vI2E8Eyv/UW3ajpDRzluHsyqghV2UsJIl0YkMJZBFWJezU2i8qSuSnn8siBA9ixV2/WqRC+dSqtU55lhIGJ1uDO0LnOmsosxZSOROnZ2JoynXwL9ZBKsuttvvUSTVnUAad/c8Lj5fGEVQLAzkjxuvsQ+6UIbou0mDbfa7uQrFb2jyxVpXeNykM5fEr6smi8fBQhWQ5Ivq/Z9BC0ydrbP2iQ9U2ge+8m4r1Svzz41PNqH2XeBeip8gvQLNeWzGXeohyb5raDTJhc9eQ4vKPHhyQxBoZcKnsB5OFM68Sqg3Oy6ZRAOISLMNYowKQutHfEZ2CckC1rxNG5FvDkurUvA2mwRC/12uSUM0Vvr1x0rz00np9W9tS7pGE0SgZo0VANpSQYwhXcmGUBUKB1JxD7sVLE55xwiEXJRgjw2uMSL1qECt583AS13DqcZh74TQdyb6A0R38Rkxcus6FXqBHh0TvCnSwg4JKBWmTLCKt69zHsy9ozmT5PiT5sScEzBKy/iXKhmpFVR61EZBOTSpPjTpgScUtApvo+tFf0fVysWvZg34/cU2P8Q90D8r374PsWJ5oPGX/8ZzAuGUNfw4u/KEBp+8FdvUfL2c7zvdz65jBPP9U2+7CQ/Uv2x1158xuleHef7Gl/J1G/l938/adJhsKdYEfbrO3cr6F/zwbxif71vG7xYL41ho8/LvzkPKXzMgnfzlAZosGzuOZTSPRcFGHIBQbzsx1JufuBugvnMTd70h4k2ZLCAbDaVd87NOTJk1STOuem7T8BYwxwn+AC6h+3LqVvQOGyn4/JaiU8q0wBsbJOXZXlIs/nMCRrONFMheTYt/igIRY5TT//xhig8nS4JCJ5NMF9ROXcC2iHyA0JufmNAuBwVmHyCemUTjNR4mBFsbuka4MgGruE6GvpdIGE5Xigpm6DeDMRbcOVS/n9XOVgeKrD/qQDygP3yZCBWE8M050JdVlMP/vO4jAwz3BhX4cYY5IH3TaC7eWsIkvywm4asAsmaMcgaehXICe5PAw/0gyOETI8/UKobEWUDxsYARI5cdDvB/Wnggf5wLq6NRL6oOFrEvsNmch/4SoYciNNffsK95qUnJxiWjeftXhIYNtka6sCUAYtrAGIemHKC+9PAA/3hzGUjsVBEb1iwl9cmj0mEBuOFyFKTLZw9DGXjDb8zFVux/dwbm4gFOglYxPPdRg8OlYby4CU8sdlkK8qXemajBe8TGDXffu7Edp6/07MLbFE2gYVoyIf3xo9UbMUYlo0WHKzYSuznTtwhT4wUsdVo92CXQSgLT9TVPSJsYb0xlI0WvEVg1Hz7uRObiIWi8ii9VkIv/Xhw6DmE5w6M+MMpIo8W7HpYifx+7sQWYqEIykhPyMhDL6GBeGryqodTRB4teKFiK7afO7GVT8FCGT0lLbD+vaFBuMnr2YdSRB4t+NOHlMjv507cwKE8KKOnvJXmsGSbQzl47P+Eh1JEHi14iGIrsZ87kTfbF0EZPcUbwEIslIsHGJdtShF5tOD0TUrk93MnruP3gKCM9NAVzfhobAsNxtjs2pQi8mjBvz6oRH4/d2JXHWxpEYcg1nlw+j+Uh4d/Qw+miDxa8HLFVmw/d2IDP2EDZaQnwsBCb2gAnih/6YEUkUcLPv2AEvn93Ilb6mBLi9ira/Bgd1hoIIblMx9IEXm04EiB7X8PpbMOtrSIt0Rt8eB2itAgDMv3bUw=
*/