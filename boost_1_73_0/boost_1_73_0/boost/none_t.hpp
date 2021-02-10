// Copyright (C) 2003, Fernando Luis Cacciola Carballal.
// Copyright (C) 2014, 2015 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  fernando_cacciola@hotmail.com
//
#ifndef BOOST_NONE_T_17SEP2003_HPP
#define BOOST_NONE_T_17SEP2003_HPP

namespace boost {

#ifdef BOOST_OPTIONAL_USE_OLD_DEFINITION_OF_NONE

namespace detail { struct none_helper{}; }
typedef int detail::none_helper::*none_t ;

#elif defined BOOST_OPTIONAL_USE_SINGLETON_DEFINITION_OF_NONE

class none_t {};

#else

struct none_t
{
  struct init_tag{};
  explicit none_t(init_tag){} // to disable default constructor
};

#endif // old implementation workarounds

} // namespace boost

#endif // header guard

/* none_t.hpp
eTnO5KFAHEnT0bu6Dz0kP97jxBCatI35zIjL6TOwoMkuCbDa8PGEgVUavnOHefefTwYXMF/1Nzh9jPwHtRCDYpeCawfSBX2PrxRKWoACEd6HGXgDffFcuPRcutzxCDz98fkYhx4IzTe/cuF56jAcqlAJLj1JKmmS766lOkncG5jAdRUMuP4a0JOEAmmtfqGr0yG1UNOg4gEhFSRJuFxd0Wcp9pWDAGfaPZpub4ENwRocQSyyBWGMYpBs6FyQSCGPqrv46k5PLsrIgdTbpj0OnPfbxRBXK8JHcoyhc65xcWkffY7iB+z2KO5JVxcYgU4LrgDLVeCYlh82gQfik+JIFbOe9CSXi5j3I9TLV0HiFEzAvU+tYOjJAZH/rK7t9K40sH9K9xKLvqqPizbqKDeZpJOxzDNGH2lCAPoYtN+1z/g0ecO7C/k5Ik1PSjvl/qILI3PnJ9ljFyZG1tCZLz+Cc7mwZiO2WOLUzPnIxJg0DP83f/nmLzBtPh9fvCWkf32b1/9X6YuWjAe6VBWtUAWOfx9RGh5VyzN2Dg3nJg6Xf2mBGuZT4MODowCzXrBOIGLZTfAFKULDSiitkTBIhNBdzG3nfPxBednlV4TKqJh8F1CPv/h80QAnaEfKR+fTtY7BCLTlsoqVLaZo5IlB
*/