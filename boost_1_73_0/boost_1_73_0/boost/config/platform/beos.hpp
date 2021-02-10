//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  BeOS specific config options:

#define BOOST_PLATFORM "BeOS"

#define BOOST_NO_CWCHAR
#define BOOST_NO_CWCTYPE
#define BOOST_HAS_UNISTD_H

#define BOOST_HAS_BETHREADS

#ifndef BOOST_DISABLE_THREADS
#  define BOOST_HAS_THREADS
#endif

// boilerplate code:
#include <boost/config/detail/posix_features.hpp>
 



/* beos.hpp
6f0Zdb3QyiqYRjHdbOh1UxIfEupcdFKx6g1eYX0RTCbBzSQYuVp3NhxOjBW53iNKachFvWpZ6gPE2Jz5YJDGcXDVkodWpp1sTs3S92hdn+yovNAfv3UYgxak9Tiw2u9lVVNn5P2eR72MmJFEfn3qYblY8J4Ne/Zf91KRlpjwpurC+Wo5OTM1cz+73sT95E286NZys6z9+p04h0fOsTkwG0fzmQ+f3cl8bM1Q0UyXTykgjqZ/Wunp6SybqhI19Uz7vWgPzv0rP7jx48D0ujbSIjbwvXA8BncSBjTIPs2epwx6JFwq97OydhvW/1BLAwQKAAAACAAtZ0pS6JANHPUDAAB1CAAAMQAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxJTkZPX09TX0VSUk5PLjNVVAUAAbZIJGCtVG1vm0gQ/s6vmON0kR1R3KQ99dqk1VGHXlBcsMBpzpIltIYl7Anvot0liXXpf7/ZBddNclLzoVh4YZlnnnl5Zv2VC4c/7XJ84w5+eOX2zvHCdQeaS/EPLfT/A/L8HvofAle4PoNqAnvUfT6GZ6HuYWRR+cB1ap7z/Bl0KxOk+ZsY8Co3j7jTIwf8VLRbya5rDaPpGI7evv0DXsDxy+OXHpwRzmgDmaZ8
*/