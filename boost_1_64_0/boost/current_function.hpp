#ifndef BOOST_CURRENT_FUNCTION_HPP_INCLUDED
#define BOOST_CURRENT_FUNCTION_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/current_function.hpp - BOOST_CURRENT_FUNCTION
//
//  Copyright 2002-2018 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  http://www.boost.org/libs/assert
//

namespace boost
{

namespace detail
{

inline void current_function_helper()
{

#if defined( BOOST_DISABLE_CURRENT_FUNCTION )

# define BOOST_CURRENT_FUNCTION "(unknown)"

#elif defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__) || defined(__clang__)

# define BOOST_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__DMC__) && (__DMC__ >= 0x810)

# define BOOST_CURRENT_FUNCTION __PRETTY_FUNCTION__

#elif defined(__FUNCSIG__)

# define BOOST_CURRENT_FUNCTION __FUNCSIG__

#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))

# define BOOST_CURRENT_FUNCTION __FUNCTION__

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

# define BOOST_CURRENT_FUNCTION __FUNC__

#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)

# define BOOST_CURRENT_FUNCTION __func__

#elif defined(__cplusplus) && (__cplusplus >= 201103)

# define BOOST_CURRENT_FUNCTION __func__

#else

# define BOOST_CURRENT_FUNCTION "(unknown)"

#endif

}

} // namespace detail

} // namespace boost

#endif // #ifndef BOOST_CURRENT_FUNCTION_HPP_INCLUDED

/* current_function.hpp
xFzEdU0klpztM/x9Ho9orIcEZU3ckk71noRY1cdF4ArWFzhKK2WZBR/ApbL/dXe3OEjTupscbtca9Zc3sjN7iccNRLvQ3SMpxiqFZR3Bt6bKyNpPCz+WgLDavtTm5FbZKpTG+ImH0dlzb2lnEHC5/R0vE3VGipmjt286cx2Rpml/0BDJOb2QstPYZUuiovio+p04jrU1BLLZbmHVIvwzzcjn7iHQRXLZIe2h/uMcPQ+Ml0iatLA7LGtfh7OAi2wgDygM7Ec+cMuZy4DWBqGwPg6+alrHOWs2PerSoFrgUEMQZwYr9KBZD8sjDF/kouvzj1HrvvlcoXwra+hDWsUgyn+R/zOoW0G1U7u3uriz1R1mmRORG4IODqrWdchIxd95IfI38Sh7urhgsSnGwzcqg05VRGmvAxwZhHe5ulFbtSEJWZRp38sZdphUszqNT15gEFLkinwFrhFZpXb5J00yfyW5qx1SCxhlrQs3ofha6IANwpy8ngP7PQ7FFycKb8BE4za5VMyl1wA9Mx4wdA9sb1TMpdyu8LrnyCulFQNVTNiQetKu6Df0I/P9rg==
*/