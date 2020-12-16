//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2003-2005. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_EXCEPTION_HPP
#define BOOST_PTR_CONTAINER_EXCEPTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif

#include <exception>

namespace boost
{
    class bad_ptr_container_operation : public std::exception
    {
        const char* what_;
    public:
        bad_ptr_container_operation( const char* what ) : what_( what )
        { }
        
        virtual const char* what() const throw()
        {
            return what_;
        }
    };


    
    class bad_index : public bad_ptr_container_operation
    {
    public:
        bad_index( const char* what ) : bad_ptr_container_operation( what )
        { }
    };



    class bad_pointer : public bad_ptr_container_operation
    {
    public:
        bad_pointer() : bad_ptr_container_operation( "Null pointer not allowed in a pointer container!" )
        { }
        
        bad_pointer( const char* text ) : bad_ptr_container_operation( text )
        { }
    };
}

#endif

/* exception.hpp
9p0rSF89G39lqXMGk18slZvc6pi8wfmNgbCcAxsPS7XH8letz/PwzferK6nP86nczLbgEGwK4gTcYwXaDtTMCCxm3TsX4HGoL2RwuZDB5WJtjH+jMV5EcLmExngplSvc9Rg10GgZbEyrtb4v0+BzOfV9BRv7ajb2NYPtN2rWDk7ey68bbP3yvdFV1N7VrL2/svau1cZzHdU/j2BxPdW/gcopvGJjuEkbw82D8auN4RZq41bWxrWsjfVaG7cPxq/WxgZq4442cbW6IaJeuGnyh/0N8fXQEu21uIvaSo5VFqxZRH4Y0nc0RahqQn7fPVj5lgUWRRFfk2KV3TOYxSrrYP8XMxjcp8Hg/sH41WDwAMHgQW3NztZwaCOVe5jBe41W51Gqcxmt82NU53Gt3EVa209SuaeoXF6rtJEfaoxqlKElc1g8w8Z6lvp/l/HSk1mQ6qCVPOJNmxgNbGI08IIG+82D2XvSgy3Yv0hweJa+t/ZRY1Xfut/JFttexuqkiFf4uQSV422+xuyAz1LePLIDvqHVjYnkum9p58lPZOhloN9oZeQc9TJbme0DfatyX1N/fC7vsbZk2mZW5jJq64PB7C1D4m3sDUFFXxy/P07gO5Wn7wd729/0jiL6ZO84sr+Xp1kxL9em8bF0FZ8zPxGqS7+2Lf3rpDpdxD8YLFAHsCDYa77QX2n+MWiH7O063DqJr2lOzw+mdWV1gWt0J96CvV73W0aLWl1Wj8ao1f2BwV6m6bHTf2LrKdcF6Yn1eY7W85d4f2zNdTvbedTfDm3tV7L+ZRnZJu/fcJPPJ7VNccpbgXln4XLzsdD6t/J2ZSc3zY23rfmqd9HKOPmzdk0qQ+PSyuyhzYPG0+o89tTKU7yBVsvvrc2b19Hn3cNt85PnNNzp6eY8S7bj/A5TL4dyxDuSyvV275JfW48UF6s9qZexaz0rIRP6upNlUT938hz6W/NDOZuXD9TqDHIn85TBbsJDyovP43CKuZ6plRfM9vxPdr73HZUf4k7myzKd4/VQag9jV+3l9GLfmv+bTJutvZEx3J2cf7jW/gEsX+bp/Y9k+CXzJuD3DvzS2SGfj8KvUW4GD/5+Po/7T2PBL+MPncQYhm+bNV5+kMozUZZkLeMFB7uTxzyeysr2eSwa1E3Eg5notn657+Eh2tplUSyakT3t79f/rfNNxJoHiibHe8TtqzE8/n1lsXc0ndUnvn2JNzQ722k5lBY/s/fOSLaxV5TTd1d2r6Qbu38xk/IpDn5SDPzD3O3b68bX67t+ybSVS7BEuvpe1Jf8Yyk/s6/NC9197fcLeSx8D9rY+G+9yabfJ6fzgLyyxPsBKXG7aKFtE+mk+Y93TtgduY8EjkfGM/8nMvZT6EHmv1ZSVVxZhKCJVR5fRUHC1tmN8AHmkAI6I0j4shXIlKTzPxl2kPuylxTwc4y4Eco+xyA7JYstmuZgz+zhYINN1842e2rxFck/wlNcaJ/h9NLOhvbRzoZ6x78LihI22j4OfhZ9yW6tTiworR+ddVbmT2Nvs8njEg98T2x4DqC6ypiIZJk2MH4myuxngyz4eYs8OJQkv6bBcZu/BDON2R1Pm1ZWVUGwz4ynwRweby+L5i5BHa+bTXStwJYcH7N8Br1vt2/8LYuyGfZbbXZ8TZShswjLCigviCTOP4bF09n67sfibybHxrTOmQvyeHxMzAHV4+M9IJ6G8eR6yxIwHZFIn5Y4ux2ZSFOnVmUlRV77fMLOy2XZiq+Mjvt0tZOvSBtaPC7+AVr8deGyvvfsxb8hD0h/1++lFms6yGbmC8P9sUrdyXGMJ/fW/LpY/pqeO/dTocnyQVQ/nfIrefs9dvYbm4n8ecjvLeM=
*/