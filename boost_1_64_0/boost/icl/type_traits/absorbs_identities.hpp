/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ABSORBS_IDENTITIES_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_ABSORBS_IDENTITIES_HPP_JOFA_081004

namespace boost{ namespace icl
{
    template <class Type> struct absorbs_identities
    {
        typedef absorbs_identities<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* absorbs_identities.hpp
Ex+DbwUO0f9zLzP7aRexhPYr87VnAh4lpT5J8GFawIs+EkOzOnynSyUiyVkcTKn34NfAst+USHUUuLH2R3IspWYNChjYs3pdsmquq8Bp9V+jBXbdVg+xEiuPx8vsV1DLWRTgtNwJSq02wF43a1JGkfjlRf0TQV250qT9YlKOv/8XdG1t1rYCrldtpdbUVmA/PSQ5BVyNuBvqsUiHcsHT8vhRVfOllqH8YjGQr27siIasZ4ME4wacF9CGnMrV2+OyC7kFTjlAnI8TTSxi+5JJmQLjoZGLHgwHiYz2FuA6pboMUIFT1RAE3kXqyVg3qSdThTxwtJGI32X4x4htdj4lk5yRQYOzkmlw8sBUQkpJz+yXNjhLaYvpfdOyspX9TNwV860pZfCIzOxBVEZLgyJU7WtkrlnzHIlj0ZOqb49DFcSzq98Ot2pBjFWq7LTPyoMy0wbiWc6k9GMsVt2UjFwFHotYlqcVpizjqEJvbHTMnWWiosQuUco9ZJRHxM2eV+Qa8JMV742KMcWQbpLYNmtPYtnJvCw8S4xHjqxxBdx0t8vGoZQ8NnHvB6fEtxd8aE5yQKWrT7v2uG2y4/xkzzf6dtIRb5/BzvNMfz8gDWsFHVs3DK/nWMq9dLXHLhU7X450ZXT48oO3U85JtZ2h2rbKORtgG5S9m08GaO3574YDnkG8xbgIO1Qs/1ybB/NpZc93Hq85gJFqw3yzGNVPtNtxeQrURQ1sPnTHIqba7XA3UErkEB3SXXhOQS46Oo1QmYrCNRCdlA0laOWZaQMCOFaNX0UJ0V0F3PlIxhazL7BsPs/IJ540wsALYa7NrrHm13KXHEIl8FoNxMPm9tksygRYoFT+/bCfxXn91CycMQEavdMHBdCZ/VOy7tTkMVyq89C4cnoxsQEs/d+puzz8PoKf/+Uq7cMwMy6AZodbLeLX/0DeoJSsTDVnSHqgvE96ZpaakzIggKR+A5JTAuTZgfbJWSMGpmg87J/aJ4CTK50iyvF0iuyHFbhJxwRXYU4xuxGwYXTS7pXuNX1lz1qEJHXekrHZYhHdEA3LSkbNPewX4ST3n1abErNc6dZRyRu39p6yn62DlkpR01JJEo/T+S6vr8yX3Fx7gTdffS6SnHoPVPZxvS1jpvZTdtOGZpbxeg/pU7Y/qPfdZfs4V/x2LA/eXjghXYr5flqKsoc2x1i8vYFidkPjuIjfl6voFH8pOBTSTYZ2Wp+/M8IELuV4mdFbSDJcTFyaNzKUC4xgLrtJEopdBRhMcRXYlXtiSYFY8r8bYta+HaK+T+QO6efvyzf7hPFmr4CLsTlHFvrkqW70B1HSqUBliY2dyR5X1T97PBICrl0Dk4kQrXat7QXtCUlygRNoWl6Xs0xEssvdWkcn2od3a+1V/oglKHGetRu7qtYKIUr8OdLo/muEsWRphLF0ORtbfSLCaFyBcWCAVgIs5eCGokt8Wc9Y9bWu0D0qx+Yy5XSJ99dJdx4ZAw1RvdDXm+wYw+rV00+7cnOrZQc94Q7BJvQQ2uEItvfaJoiu3HZc3J6Iqlc+8vmn85Dq0KNnNTIpn4dNMnRWowz4eb1lyHo+h5v7GUc81Qwhyh5Z3xiNY5602n/co9eAXh9hPAIkbYgwVus+hx17NJaAYx8eQrTxV4y5Pos2tlHJqwRb46YI4+nNmIsowdxCib8MB6ZdzXkie0rx+3kJeSyE3sLn/bqjt2J/O3gA7fDzcS9sk87S6vrsGhvgMmXjkXZcgc0yVsjxuMYjkq4iYUyBwy1a5Xf3lEde84RiwerKa+sVcsyWsZ1IlVLTsoZHpfRO4fvKOLq3iNGyiO1LfJmXlpoWp7KJYzbSlstJtR+VltKbmE4=
*/