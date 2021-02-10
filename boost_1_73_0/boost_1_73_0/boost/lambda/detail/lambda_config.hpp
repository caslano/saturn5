// Boost Lambda Library - lambda_config.hpp ------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// ---------------------------------------------------------------

#ifndef BOOST_LAMBDA_LAMBDA_CONFIG_HPP
#define BOOST_LAMBDA_LAMBDA_CONFIG_HPP

// add to boost/config.hpp
// for now


# if defined __GNUC__
#   if (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) 
#     define BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
#     define BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING
#   endif
# endif  // __GNUC__
 

#if defined __KCC

#define BOOST_NO_FDECL_TEMPLATES_AS_TEMPLATE_TEMPLATE_PARAMS

#endif  // __KCC

#endif








/* lambda_config.hpp
Y3BwVVQFAAG2SCRgtVRNb9swDD3noP9AYJekTdu0x34MCNKgKNAUQ5odtksgy3TCzZY8Sk5qDP3vI51sQbZr54vkR+rx8dHyxQncvddjAGAS6pZptU7QnwzgajS6hDNZrkZDmDI5eLIbWnk0mvsJuaIYKXigCCu2PmEOKYD1bfCouybKspZoDEXaWkYoAmsc6obrIFE5LK9K50JVNwkZYhsTVkPBOzbGnGJiyiQIlKBgxLIdQmyyb+iSpqS1Epdl2JJfKRejnnBJtMVrBc5gITm2SWupL3p8SJpUS5yycidLWZwA+KNB7zBCKLoGZNEelOZ3G0MhgMomlbsOW7DboimHgBsULzQdW7BMcrjgUEGOhSiNQBJN5wc9QawWbF/gYFLVxNRJzGRPkbEWraj2Sg0Sdoas8wxf65KcmOJKS5XwCQ5hP5V9oS+hASW16s9uQAdDc6hCTgXJxoWadk2rEYdORWAMDTtUOp1JRt5yq5bJkGoOG8qVdtezCLb8Xd5rUeRLgaJUFp8E2iCrrtiNtmOTdG3zuEc9kqFMshOy88iWfxR1bb3bRw8nF8Z8IO/KJke4jSkvKTtffzzCWMT8jeUUjqEZVoHbY+zh88vjJFSV9PtEHv/h2NcyF+94jbuO7qeTp/F8upyNH5/7
*/