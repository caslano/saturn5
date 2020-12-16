/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_IS_VIEW_IMPL_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_IS_VIEW_IMPL_01062013_1700

#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion 
{
    struct std_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_view_impl;

        template<>
        struct is_view_impl<std_array_tag>
        {
            template<typename T>
            struct apply : mpl::false_
            {};
        };
    }
}}

#endif

/* is_view_impl.hpp
0+fPF00czw2Ev+TD9Xn1ZR/uwZevKO9XQrhdam1D3Ksmx2O8LPNrPm4r+KbXyLaSe11y1WEafXAFLXFvhLiaIJF7kzluo1Ca7RzZJt9iDkxtelwPb/swaChVaqvvKLwNU856SdbnuwbOeWDa7zGO5rP2fYlBKXvEpJDxDyTeKo72DOt5zocmDnFkuT9inF2E2o8R03sdpfYTA4eUEftUY2q8/QyxDbJJe70E7IKDRdtyaXMZ/fh5iMds8Hz6hZ9TC9ArFYjt0fn0y2hNaTNRijLqsBxfRetGZH/4OsSjCViOb0Icnq22LroiAYr/rdIMV+DjaFDNbU/OG76TnFwTbrc2E69jl+fC7yVPRW83mw7MdTavD3PZftA8Z6vb/Y+KE6O6TJi4nzQHH0kpNsQJR7aBnyVHJRW5IW6Nxbg4QTWxFJjWWApv17SFVE9jC26dwhrys6i9AzZvXdb7UcbpqNH78cbtqNHzzPF8mrXSG2T8+xjHD/NqXjBBmFPtdELg8JuJ4qObcFJPwA4JLj/yE0Xyeh/PxJG8HgMnEXyvsSWbyzQp4yPDSy8Z3Fs9GXJyOzOlMzli5tZq0k6BuD/tKQmrR6U9FXJyCzVhUxPmObg9mrBpBJZZHTZX6jnQtIhB5aRSOawl8SlAx1P7c6YL8PydQ+SmD3H63DdDkKs526i9zkGu0ay36qV6hfmZgrz4RKG4kGX/z2zwNAIRPouBczkRn9XAsYzcRmcz8c3gDQBis7G+vsO4sxsa0QTUPmcTb8CrD2U8tn9Ok28Wt2a3IjdXgKsWt1Btfu4A16g3Vbucx+TgpYtbuSVZXKzfeZkvlkqObGPz+TCYaHA+80vcq9H8rNGET2Nug9wCQc5rj0huQZPz/PEW8nH+eAszV4IRf1hcs5VazQr7eBHisCrNfWWLKrzuOaINOHTeXEzi9VoNzqWY/hiFNbbFtgYfyWg1t0X94sRRllz3XQaGNoqxFv4HF5KevNbuDmq2borJ9mi72CzWWnqc6jF1DZiLQ4XIfJYwOWgBgZww/pKmZmuVAHJLMYdvt2Dvqb3KkhOfPLNr9Ro0+laxYjvNZr3JY8MypKFJCmPLGhiMYogtZ2By7r28ibkwP6xReVcI4yIZ5FYMcyI5TG8lxTXESd2tcXlWZnwEWw5pV1HYcNFzll5S9sdVNQ6Ny2lKPKHwktvYTOBUntUUXoFPHXIczjepuGpZppNSWA0m0XZLXhelNd6uVEjbq7CmU3HFGZn66eoSLwcrhcq0hua9zertSpnaKqaZkRz4jm/sYf5rEu7bQ7uWgYmZlBwn+ggXTVb2e+49lH+/5lWLknGzEZxdbKrxcEDzvj1ogwbubIMU4mtrHIdY26W2ldM4znZkfeU1LoZbbELbcB4Fg4NxUcVZR+PkSRuO2J51g5zofl69JuOup3mojHYLvhSouPU1J4o+vC2cH2R9bKA5T/pgQ8Y2c7bhYZm0GxHO3YG0Qwpr8bhE2o0Zr8BXNp0aYZtIrF7fos19yWasCmUzz2mbGrivEjEXsqsY0PCmbeSGAxxGY1+WglzZATPr6vqrHODROcw5Qa7RVtxIkDPmvaMGp8dg8sFmBme+W8E1cS/aB5uHNNoHW4Q47YOKjwv7oOrj/T6o+Ti/D+o+zu+Dho/z+2BLg6uX8XUpiDdNnEeSyQH3CBfuwrbV0sd2sj+Pcdsawx32sn1vZeCDayXzyzC+tcZ5vKFyb2PgYjBtFF01Xm+rOXkeR3w7jdN5jfvF9gY+wvcodjAxt6KuZ3fUuDr37KQx8ElVnD0Q31njPEhSGrsofBs1z95VYqJuGNvNxLoor90l1q4OO02sSfTHHj4ca1H18T0lh3U=
*/