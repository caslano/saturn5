/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_09272006_0726)
#define BOOST_FUSION_CATEGORY_OF_IMPL_09272006_0726

namespace boost { namespace fusion 
{ 
    struct boost_tuple_tag;
    struct forward_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<boost_tuple_tag>
        {
            template<typename T>
            struct apply
            {
                typedef forward_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
cM5c3ksd/kgycHnVJT3JKdbxw1HkGB6Gr5B2rQGeP4+zY34QJhbwjjq+0CWORbyLzofrXuMcmWMsdsl+YuK+apfs+S/3Qd9rOWuvoCd4cKVLniJNzInBj0kDnoQnSa2uU+uSS0gNHoDjSTUegW+SSn1feISU4rKKHpI6rRNOeJe7pHPg0fe4Mzoed8nm9zkz3beOe0Wa8TS8eiPvq+MfumRwgvfCQ5tdMo+U6DjcSerxFHzzE75rrRlesoV7qOvDfVu5qzr+mUvOaOR9cQOmtnEndc3PqeUL7ioegdu+pC86/pVLrt/OWeg43EfMb3ivJN8LycajcMQOzkIdvruLd8QDe1zyKcnF0zD6LbXhCWjspR48AnNb6C0eg39+Tz14MuWSfvu5M3gQrvyB2nDjgEtWkBrdq5X7cpB3x/3wRpKv8+FhUqDzD7nkF9Kgcw67ZDtpwqWN3w1SrfNhxx/pic6B20mzzvmJ3x9SqXPgfFKh4z+75CVSgsfhwnbOWmuGRUe421obfDDNueO+oy5ZQ4rxFLzwOHX/T/89Lpcs/ZM+a50neG9yCg/DISc5d3XY7y/OHQ/B7cTOs2nY+xR9xsNwFcnDU6fp07/0Gfd1cMu1Z7glGzcy3LKAmHgC9u3klno8CIee6ZZCPAIHWN3SoM/a3LI0yy1j8KjTLV0NtxThAfgXKcCTLrdc53ZLmdYA/yC1+qzHLf8l1VonvNV0S52uAzt43VKCh2CClO2iD2e5Zc7ZbsnX+XBEF7eU6prwB3Xm+LqyJqnRfeFd57ilEo/BU93cUqz1Z7NXd7dU6F4wQSp5NgmtPRjHA7BfT7fk4GF4hLRof3xuaSWFulcvt3xDWnW8t1v2kVwdP9ctUdLOeBx27uOWZn1fmCYZzPGfRx9IH/XzcWKqX8C7kDzc6OuW9SQfT8OlF9JPrRPOuIieq8PZF9MrPAGbc9zSpHv1c8tP5JR6f7cMuoTzZU4ELvC7xY6n4IwBbjmmdcI3LuXsdBwuHEivdH3oy+WM8AB8nNTiUXj/ZfQZj8E2UofLIHo4mDuDB+H9Q+gbHod/kmbcGOqWtQXcH312BO87ippxGeOWm/9DzToOX72XXu2mBjg0RJ06Dn8eS2+1nvvd8tID9F9rhvlFvBfzQ/CLB+kn7n/ILStItq4Djz9Mz/HAOLccIDm4Md4t8yfQc1wmuiUcZi2dP5nnSug5HoePP865q8PXn6D/eAreNZVzxxPKp+kbHoPZz3AndS+4ixThUuqWF6dxXngaTo5wt3HfdLc8NdMtMTz6glvOmeWWKn0W7prjliQeeYU1o26J40EYI8t0X3jdAu6K1rbQLauruNO4LHLLhDfd0ogbS7jzZDcegq0kpeNL3TKFpHVfeNVbbjmBh2E7adM5NdwxIntYH+a97ZZMPASn1brFwIPvsgbpgvve43yJD0/BSJzfEX0W7l7jFj8efp85JB9PwgMf0GcdX+uWL0khnoa3rKPPOg5fWk8PdU04dgN9xqPQtZF+4gG4jpTqHHj3h/QWj8BTpAL31/O+pFKfhVd9xN3W2uDqj7nPuCS4a6RW32uzWx77lLuq62x1y6IvuNu6fpNbLtzJnccTzdT1DXdY14Q7SLPWDwf8j/uv68D9pBU3drnluT30F/d965bX9rIfLi1uOY+c0jrhLd9z/79lTor9iR1PwwH7udt4EL5OsvE4vPoH7jYehqtIDp6Ap1u5l3j0IOdwmPNTh93a6D8egCfa6T/u/8Ut3/5B/3HjpJv/7ir91zU7eOQ7UoRLR49cRIr1WfjVmR4p0fFMj8y1e6RU93V4pLvTI2V4BF5ztkcqdH5Xj8whlXgMHiDVutc5Hrmim0c=
*/