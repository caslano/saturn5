/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940)
#define BOOST_FUSION_CATEGORY_OF_IMPL_04202013_0940

namespace boost { namespace fusion
{
    struct std_tuple_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<std_tuple_tag>
        {
            template<typename T>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
QayrQvD0IPh3nXTHi67hYjYdBZMonoWD6di/HcBr6Jyew19NSbz+pQOdQqyo8XDmvT7zfsIF+hVzprax4ppajF9kk0KH4TWQE+eZ1+UJsaCGkq25pQSRmjWYdalFwsiDsQ8X42ASDkPHKzPnB1EmRZNyeENBWwLmbx3jP5G4foylS0/gVY7UKJAhxzhc5+vzn+SshleEkkD2/jBoLgfhxXQ4iYbB2JkwbAyz++xg4U6kjZ3F3QSuOFRSYFrlHeVKdCqbojghgomSIU+cZ8XIpCVhzUqV8dpznGU2PMbffd1bZhOcDa3M7gM3K/PbiEVVSy0TWTiHBfbMZFqUpdQmspGFtoXo5Y4bHm6QjiZCVxY4H71jMJP5pcXSWiLcOQZCh5T0Da9RA6WCj78etbh1zGAuylRuFE0IIsYsHqiKTyrm7BpPGFK5ZpiUyROvsqaJ3RWstaX8VZMkODsZlhqlZ6XJhjmPWCKR3HPtwTAzcVJZ/qjJQyutohRasGJPLPkxO4lUKmf33GhbhgJ5mPU4Gt26R21JUA2wL6riicgEpUpjvSX2HGx0qC6y0c/ytc3ay5TYZUEyoMDFowUCdLAuXGlEFkn4WhGp7VZwLuWmPBnxBzy6RvIOGzSmDVjb2WQM3RnGdCY1+hEVFoee
*/