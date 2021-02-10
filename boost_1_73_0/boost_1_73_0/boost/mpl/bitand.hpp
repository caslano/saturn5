
#ifndef BOOST_MPL_BITAND_HPP_INCLUDED
#define BOOST_MPL_BITAND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2009
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

// agurt, 23/jan/10: workaround a conflict with <iso646.h> header's 
// macros, see http://tinyurl.com/ycwdxco; 'defined(bitand)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'bitand' being an alternative token
#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitand)
#   pragma push_macro("bitand")
#   undef bitand
#   define bitand(x)
#endif
#endif
#endif

#define AUX778076_OP_NAME   bitand_
#define AUX778076_OP_PREFIX bitand
#define AUX778076_OP_TOKEN  &
#include <boost/mpl/aux_/arithmetic_op.hpp>

#if defined(_MSC_VER) && !defined(__clang__)
#ifndef __GCCXML__
#if defined(bitand)
#   pragma pop_macro("bitand")
#endif
#endif
#endif

#endif // BOOST_MPL_BITAND_HPP_INCLUDED

/* bitand.hpp
sZRxVOKAeWm+FvTZ4elFFEk5YJMwDPQBt35oLqPFfO6PauFQiNcT06es8hwzNlotZ4sgfAqWi5+/Jv5w7C+ZZ18ierZJwq7gEYsjFlaZJsi8Ag/ZicyxoDCxNKltt+1Cx3Fgcd9gDXr7ZvWSSEZ/OEH5UsaZKJGNI4kcwgo/g9OHuTiSh+uA2+XdPiff24eQmfwcVAOsUgv2Otohm0WkeBBJuk4xqaO4N3BX5SoPRelw1zlH8cNow6HZcZ1Oz0rir9ZNv/ul0+1/axJeg1KDjbcY794t638ookZPUj2oKxhlKeayHl+sBSrVQBiwrZQHfViGI559tnhSiGzAsvTZ7XV6ZDAyeHm0JxK+QyBIS0g3uSgwAWU22qfVfPp96o/ppW2eArFnv4/yhK4qNbdtucW2yJL2Xoi2SsdbqtvBYhnaSoTWZPEYTgPe0umUXrOsjuKtMZJVgcTbcxUXDfnVRVMzfmCRrk+gWgXRWmIBlFkPBbZRCc+IOTTLrZDU0KP2pQA6JlVsNgo+xgpnihBZRCn5X1wbLFBRrZHZlFTkHO4RD9YwS4/YYCsagzXcEG4OE+oR6LvZrhqPwiVFrIYSrEIwjfoXBMM4xgP5XNvXHyckgFLxZ4b5Rm45cbPB/NcDYaa741i06jLNK9Qb
*/