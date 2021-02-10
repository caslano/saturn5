/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VALUE_AT_IMPL_27122005_1256)
#define BOOST_FUSION_VALUE_AT_IMPL_27122005_1256

namespace boost { namespace fusion {
    
    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct value_at_impl;

        template <>
        struct value_at_impl<boost_array_tag>
        {
            template <typename Sequence, typename N>
            struct apply 
            {
                typedef typename Sequence::value_type type;
            };
        };
    }
}}

#endif

/* value_at_impl.hpp
AtKD6nd71bvn2h45kYPpaYDP48ODRRytjo4Pnxwk+PvkaW+lxdV7OxJcF2i+TR/GXTdyyVndNbujfzy/FC5BwfsgjII3YRSmKy8oiv5a7gei7wXXF6ajcU/fSwz1a/K+ftXzt0/3cpaeL+f0PojOZ96SG9xM2kU9y+J3JErwsWlUi0YdD9vzOM3enIdRmoVzUva2uBSa92ijZDajIEpijN83y//k7WjveB/VuH3+HnnFoNsd3VEHvz6uHgTppe4O+f9F+8bkDVWSmT2+Vv4XUEsDBAoAAAAIAC1nSlLkOOAzTQQAAKAJAAA4AAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9UTFNBVVRIX1BBU1NXT1JELjNVVAUAAbZIJGCtVWFvo0YQ/c6vGNEPdSKCL5eT0rTpqZxDLjQEEOBLLVlCa1iO7WGW7i5xoqb/vbOAlTh3UXLSYdkLy8ybmbdvxvbShP0fdhm2hoMXr6z/ZnjhunWKBP+b5urbDll2D8MHHZe4viLUFB687rM9eJXXPUx6r2yMdarvs+wV4ZY6Sf0z1c7LTN/izuA5+s94eyfY50rBZLYHhycnv8ABvH1zeGLBGWkYrSFRtFlR8dmC06Lf+aMit7e2pO8toApI
*/