/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004

#include <boost/config.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_set
    { 
        typedef is_set<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = is_std_set<Type>::value); 
    };

}} // namespace boost icl

#endif



/* is_set.hpp
aCg1OyZqxDlA2EwamrxJFk2daUJFSg3I4QRZCQiaM+D3aMw3cOttAhu+LNuTU6fUg4/ovyJwbj3v/zPDlFSEpTDpw/UAhh5ULKwXIltE0LdKg5GyITFS9dDBfTXsm/m8fSM+7L5qPvYBan9xhCAW/b/pO//u+PsLVdb/yHf6hX0VtngP9hoNXfP0rAKLe2xWtgtuvk2RBgg2ceZFPhkiuvXYZrtQ/PZUGAoB0Qg8ci5VBXCvJwilYkN3BdHH4sBGr/FNRK4Z7dPoG12F7jRnvqvInT8+q6h48EDJ+np8OhtxN2WBJ0pqySnE1RFTPhCuCDLC9Gde48m6BUhMrji0dCQ/eWPGHdVPlL+k+jH0BEjXMD7duA1CpQtNedEuhNY609Dxo+5KS2W3bPCe8a4pha5cd1ZerprfI/tR80s5IMusSESRbJOb6abCPY3tdN6JQ4uLZ+8mPteZ4zKqjkY2Ct6VW1gwVc1MPD9KxcT3oyFbIZ0VVXoo6AtA5V8NZxSyiUM5udL0Ix0xnOEFfCeqgkSnKDvmbNNv/sQx411TdQZRcZpP+g5OA8TlB5nO37UpeOYLFY8jJfQew7kL8wqo4MWJinh4tGQVTwraZcS/xpnAuHQ+7aLiudhUvDiXhXDlvogIavpDujkPMVxhwUR3IaWR/TFOFKPAqZrmnpl+b+y8kjj7pvkC+kTLJtxUf/r8SLIcXgIVOmEE3VtOIwjGI15oLpLqSA1N22hI4Yia2rMowBjZ6wugwZt4I2lWNVm/Nywnj8+yqZNBxiOZPozESU5b8frpq9i5TUuUNr5sUsYyHqExmLVSqNnyeTtKiIRj/RaNcJQKQ8MopCvUoLLxacopaVaSC0EJHzKiQkXp6juVGkKJ0iA6+4mwmivcYXPoZjQpVjyy0nxBhaaV6/rOEZ8QLMrdmKZoo8qTDkpa/YLdxSTd/FZtvUEuVxknGBsa7Ba/Rv0IrKF8bpxK4ghMPBD10JEyx2yBSnnCkJySOmDgoMFDhg5zjklLd42tfzyQklJEuXmOmEisfxyR1OoGjzmtU1Q6IIZZcKw9kU5VWkDcVyvcmPuAeYS7f05WjsvhqxCHu/KMaYGbDz7SuF/oK3tFGIEzNVdJc1/T42xIuqMRWQM3NNNyJsRyCBURxzRomVXj85xovVLg+P7k2DEwUP3wBTCyP5xqUA8dxQ+D+FS/qj80OZHUuO1D+qoZj3I6AF+JR1PDs5p2DTLNhwNVPySD6RYOOmbDcccNxzTVv9B912sGYkEpNURjTHp12Ssiql84Yy6sBlPDiRKnm0aMxSgOcWT/QV91fP98ZqLCV2H0H+jvSsVRZIW16qQp2VElpcqPpP8biM+9qn/uBelgiX4RTnz/tT4udTQqPWIsvFn6wzRn7XghWMr5/hJzkgNWKNHv9I13Z8gRD5PLNGK22AloNX1its/hNLF2Ea+v9lRGy2kZokbXF2afaF7SmSilH48TTsQsnR2JF4piraSTEuJOGvMojpxtPn5fV92DG48ot/isEK+MmWs69UgHIle+Hz9O8qfGy7yACIN9rfzg6EUyALgKT2Qm4tZ6xyI3dIuraxz15ZYjpl832+AJSOJU/Y6ULBGW1Oln+7xJjrC+JKAPm/SjXmEEwFBfb/EBjygQJa+6hKDkYtUB/CLHbhZQA8MZM381OI/bSJSC7o8KfwY+3U/a6YjJqMKSkBjUxD2P5Cj1yYVTMDbNMWDIkGFoOMZaijipU6z5SLChZihiiECmK6sx5rlAhIlGfOiB/aGAJyon3VdNFRTfC49tpWqnEXLQX1FZQc0LXFNN7+otSvKDygpwly/3/9zVxZM1yjfrvOsIdcXVpgbRaoJRD80=
*/