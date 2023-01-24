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
sHec/2eQnv0/muxC/wzSa7o6mgFt/81pN5L3FAc2lDdZLSXQrVxacLLVksg3vh6Np7tjPJUGM3p9tsxU2/ntcGiwXL1M9vDHiufhZP2TEuQDjPuHVhiLSSmOCujskwl8RVtTV840bzANBuJffawxF7kzeMO4ghobE3+tVKtzEdiNzbvR4n02liYUJ8QLnDgBIUSuwwA3wwk2tlLLcpgw+7LvL4BH37HS3uJQHj3Mab1NrlRBsiMli0wxXo4ZJmfLc6yLHsh+NZfAySVVw3qz8FGz6Gi0HsWOfCrKYP9Ky0rTMhzn/QOL1RlzpjjUchzs2xjfxjFqhUwsawmkvWqjdvbhhtVX51JmlZSBZyWJjqRvPi2LdA8wupIm8Ztd5Z/khD1R8wyeCvFu+fLmjqjt6SBWGr2bKppMz7Nrhnc0hKiCWfY9eTTvVbo1FGc21t2nakbu/ugwD7tOCeL/oin3dLpC0BYwsdIodmQEwKXTkgKt817lQR76D96RQJuimyvT6ZDtewewvZdIhIhuU1XThktQf8tUJ9hptoaV6z35n88zcNjuX3d9ewOsLD7k8lzdp3Wjc9uTz/JM63rMcIde340Xd9sIle+6P6BoNWonWA7RCbl27pLEAOSEx9+hL7qZus27ibuTCx1BVF+EvmB2Y+nh/EIDoxthNlOrlQ8ZhCD4vzqgOaAtoB09O34WQ20jXO2QSXPhjOaI5shy
*/