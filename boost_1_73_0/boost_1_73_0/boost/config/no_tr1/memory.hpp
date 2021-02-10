//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// The aim of this header is just to include <memory> but to do
// so in a way that does not result in recursive inclusion of
// the Boost TR1 components if boost/tr1/tr1/memory is in the
// include search path.  We have to do this to avoid circular
// dependencies:
//

#ifndef BOOST_CONFIG_MEMORY
#  define BOOST_CONFIG_MEMORY

#  ifndef BOOST_TR1_NO_RECURSION
#     define BOOST_TR1_NO_RECURSION
#     define BOOST_CONFIG_NO_MEMORY_RECURSION
#  endif

#  include <memory>

#  ifdef BOOST_CONFIG_NO_MEMORY_RECURSION
#     undef BOOST_TR1_NO_RECURSION
#     undef BOOST_CONFIG_NO_MEMORY_RECURSION
#  endif

#endif

/* memory.hpp
+0PHBY7PgBrA3us+6cOzvO6hZ7ySDutMz5PkGXALnaT+G2jnRaKnuNJ6dv5DXt8JuioV9IZ9eHly+gZe6OF3Bz6mFSUMIkWqJRErB85ys/JHmd7eupK8d4AoSJl7EDAuqQTJC7VNBQGcM5qRSpIcUgk5kZmgS3ygFaiSQEEZgWE4mfvBnw5sS5qVXZw73oAsecNyKNMNAUEyQjdtmDoVCniBETB+TqXCmI2ivHIRnoAiYi27MDqJlEkO6SalLF0iXKqgVKqWbweDrBEMdzLIeSYH2Y4Kt1Tr/+1qjtms0zvgtQLFoZHEAW3vwJrntNAjUoSLdbNkVJbOPi0ErPIBFyAJY104dKVEtlsgEHVsOdoSasyeKj1IXkmNti35+sAQae0CFY2oEA5pQbucI/EONFVOhLE3ROxQOpYN5T84sn3uOfAKswLbi8CPbFimkkoHbvz4MpzFcONNp14QzyG8AC+Yd/Gu/OAjaoMiqgByWwsiMQsBdF0zSvID8J9a6ZYbX8JwNh37wUWYBN71aByGV7NJEvvXoySGV2C/fANeLYzQbbAZXWoJwG/u61P3BBf0U0JSeZesiKJVwfWJo7Akxo4uQYe0vgOweAHoZ+iu0jUBxvk/TQ2K4hwVv6aZ4JJkvMqliRfNg3AS+ZH1
*/