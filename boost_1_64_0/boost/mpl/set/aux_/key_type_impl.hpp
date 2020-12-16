
#ifndef BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct key_type_impl< aux::set_tag >
{
    template< typename Set, typename T > struct apply
    {
        typedef T type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_KEY_TYPE_IMPL_HPP_INCLUDED

/* key_type_impl.hpp
yhq8D7uiwWrkaAUfgx/A7nIeDzahrqwv2QIb37Pd7ahbgHO0C/2vNPfT/dAlVdb/oa48i47ArtxrnITd1rL/H3LZktkPxvzyve0LiFfWUfwCGzK2/wFNC/I9WL7qZvd2ztsNxsLyLLWosVBPbq842C/cN0ob8xZjTSsYc77D58YqxuJa8Dhew5hfxpw7jAXl2sJtzFFa3v+FjdNc9x6Uk33UH4DPshanBTSQvUoeA9vI5VrDRqK8/wufZZ1ge2Oeccw6gTWV+T9jAbke6mEsIntZJEODLmy3jzG3rPnsZyxT1n0NBpPY/LArbBSYjNljkSNZvzsRvrzP+Z1szCXv209FHyrLffxtMNkH6F3EIXsMzoWmX3HfWHQll5zfZciHvAu6CnVln7b18DlNvv+LfMh8ySdg8u2ubYhN3rcKo72TrMs+1JWx/bAxr3zL4Dj8S+F4TxgLybrS09Dlfh7Hz6I9Wdv9I8q9xppeQt6mcGy/wz+d/6th+ZD3gAoZi97OrIixzFJ5iN1iLCL3R6WMOWSPgPLGvE/wWOwyFnie26tuLCjv09WGf/Kcrj7syhqqxmhP5kWbGnPJ/hv3G3NnsI2HEJtX1v/BhrAn4J+sU20D/+Q+rx3ilfeYO6JcG7YbD59lLqM76i6W/f/g816Z/zPml3NPX2MeOX4HIY59XHc4fFnLuryIunJvPwZ1x8j7v8ZChWX/P2NR+cbXG7BRnI/Vt5APP/s805hD1qvMgd3GrN9CaCU2ll7pk3wNvNKY7zuem1uH2GS/jBCYzBV8DO3lm7GfgX3hILbTWJy8D7EXusg+Nofgnzwr+hx9SJ7Hf4Vycj99Cu3JXPj3yHkPI9fO/0FTuW/8GTbGs3+X4fOdsv9fTYtNrkEKGvPJe0WFjXkusqZOY6FN3IduNRadxjkqZyx4QPb/M+ZYyT5XM+Zfx/3gdvgn35WuZyxOnhs0gl25N7gb7e3m9u6D3UTW70HUlTHiUWNO2de+FeJNZfaUMbc893vWWFhy+Tza68d9LQ46yzxNInyWd4dfgAayj38qfCnFsWUYc8k9xEDUlW9nDkO5w2z3r8Ycbo7jJeR8Hfs8HrGJBq+iruxl+zo0lWeQbyJv8s7eDOjSRfb/gy7yrHKBsUwX2wgijlGcyxXQZYF8/wOsNGv1IexKbJvh3x3s36fGIkVl/g+6fMjHwh7UlTXbB6F9XY7jGGIrJ/N/aE/WSX8DJvd+ZxBvGufynDF/kK8tfoL2S7k//4a6TvbFUcv8aynzf7UwNyff/zUWV1X2/zOWOUfW/xnzb+W6ZY2FXuL8VjIWlbUutxlzudi/WrAhezjXRTlZ99UQ/q3icnehXA1ur5mxsGja3Jjbw/eDj8C/jTL/h3LVuK95odVimf8zFvmZ+0sHYx7Rvgtik2fbCcZ8K9i/pCv+sX4piG0ss3TYkG+uDQA7JPN/8O8Nmf9DjmRtymhjjjUcxziwdfL9D9iozXWnII6jbGM6WHH5/i/q9ue6sxCbPO+ZX+tf90ldYiwwXL7/Ycwr38FaA51Lyfd/jTnlWx8fQRe5R9wKn6XcDuTjAl/z70Y/OMvsAPpkX27vKNg52f8Psck+cl9DA9mb9Lsr5XjMiRpzdGJ2EXGclPV/KPcF9/E/US6O/ct/u8WxjnN0ozG/fPOqmDHvDo6jhDGX7AVcBu0V4/GgojGHvKNTFXUrs92axuLke+B1jHlk/qWBsYB8a7oJyj3Hde8Fk29ce8DkmevD8LmafP8XTPZFfBK69OFybY19Ku/PPGfM97XM/xnLlDnzbohD1p73RLkhMv9nLNqeY0tDudWsc39jzveZDTEWiee6I+CfzLP+DeVkTdvLyMc=
*/