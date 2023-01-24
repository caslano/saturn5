// Copyright David Abrahams 2009. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_BACKWARD_COMPATIBILITY_DWA200968_HPP
# define BOOST_CONCEPT_BACKWARD_COMPATIBILITY_DWA200968_HPP

namespace boost
{
  namespace concepts {}

# if defined(BOOST_HAS_CONCEPTS) && !defined(BOOST_CONCEPT_NO_BACKWARD_KEYWORD)
  namespace concept = concepts;
# endif 
} // namespace boost::concept

#endif // BOOST_CONCEPT_BACKWARD_COMPATIBILITY_DWA200968_HPP

/* backward_compatibility.hpp
N7m6m7SgPdz5R+Pih+lT/+5++xyqPExlmkqbPxaJhTrshP2hnN/8NSUGDdPUzWzWcBdZOYKRFfF+H4j9Vi1JgM0t/0CfUi2tT59VFmo+f48nyRym+k21xW9pEgHXkQiYjg8nJusPJZc1rmy6ovnmlhUkAu5Mbo7nYs0+0W/E8NKxeFnwS8bCZf1yhexRXO3T/51FN59bDTx47uoKt24r/Avrbb2JVv6YQv6PKPGW0afDx51p8Le7VzMOvJ0q91J5dLXRn7rOCX796QMVoG+orq/TVpNd5DJs7YQA+x/YJtXZbPeooco5VLacbXQ7Pt6Ap4WtEeyUkoeCcQH+O55mbaPbTBbbpzYYBc95Z5cbul+XvhFW1cklNdq6y17hnKvDVTp+sU601bcmilQ21Y8mnqvfkniz/vnEJfGukLVOrUZWh8RMNuXvnM025e9T5Tkqvzm7HOOz0zdW014TkA/ATrxijeuH7Qesn9JUlKx6nXGzCkJOmRfIAdIy6qOXXXQzOMr+f6OeXPb1b7gKbKdb60OqXe/y+L3GGcd8G73698b+QZVvUfnH0bJeN5BMphww5GkWF2CMOa5o9waj2D3mteWwfS/xnvOWfEFbWfuQcyT8UPTxWGu8SGVn7Ir4Y7E74s/FLolOO/fS0BrjpUv6JGf2POQjfBo5s5vO8a3FxXTz8XMQm9V9TnDxfaG6/rXA2ltFgtcE5JL5s1T0
*/