/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SINGLE_VIEW_SIZE_IMPL_JUL_07_2011_1348PM)
#define FUSION_SINGLE_VIEW_SIZE_IMPL_JUL_07_2011_1348PM

namespace boost { namespace fusion
{
    struct single_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct size_impl;

        template <>
        struct size_impl<single_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef mpl::int_<1> type;
            };
        };
    }
}}

#endif



/* size_impl.hpp
rmEAnBgmDH7CbYlZDv+6xsKcaHy+YUeuBmhMND5f02N95OdqP9uhDbMOP+3bSOv+C56Lmc1Yd/EY9RqtErPyeXbupr4ctkNPZhkGJn0uzI9WjRnfziJoyWS64/WveAxhxo8hLrQkMt01itJ2xoTQTpreW3nzzphNseXOCtN+w88wQdqBW49zCfPpbMSwhzHC4KgdZpulNS144bkwxwl8f5DF5RjiLygsgNaSWYWbOWtRLiex18yO5G9SWJgHzc6Mrt3Q/GhJzHjtYbREaewaDOcLqePcIfV8PoO4kIFZTqlzcaGNS7MKaC0G36N+RtDqmqT96p9+mXI5LbcXNLm9oAXQkpjxXCIG5jgj39WsiHb0xRDKM4DWj1nbKVp1Yc6zdijIjN45QfOgWZldafrZT7R+Opt8rmtN6idaVWbTLpW5Sut3Lnq+nl/vn0/9RKvALK71roI0H1oBZr17mqYJC6LZmfF1j6AlMuPr5zhvhwxp+0MltCcNxnegMS9Sr9Giew2XcD5mfD4HmirOg5bIjOcSMIiLoPUwvbfKaAWOJC6nuCv4DgFIi9/t3UPzXcVrdmb+3MXzUH1oVmY1rFkG0XxopZi9yPFFhOq7hu+sM9uWf4O069gXZrwvbrREZrx2P1peZnx/CKIlkenWIaw2Z1idi8fA/AZjhsPqGrQbeO3N+1m83wMaE21V2vpVQYvP3LQdrd8tvJ4AadZFfUrQOtzG93SY5R5y3ifMdQdrYMZr8KIlMuN5Bg3iImhJzHjtjj/UY3oMLICmGjOCpspFu4vbBDO+TTjRVHEeNNV8AQOLoKlqcNxTz+dGU8X50WYzu9ml3CJavz/t8BOzBT1KdCa7bwe/SVrmd0kLaL6HdrjN7MM+04vS2j6ywwWQlutM/W3CQql2uBgrrfmP2hhh4Sf4fjmLq1Tvy8NkT+3wLzPzeMddYZbndhjNrHXbG62o12jNWJ5bjtSPoRpe4vWuWVqnuOwdaR1ey2vhqmh0LYwGb+zgjZFWJKXgXzSmKUEZ5zEwr4H5DMyP9nMmacvmpGssTMueAIlAxq71MU80mzR2PY/zoe1mdmnslT2Up0U9ZtCiHjOCdtkk7eqy8w2EuXKpx/ShqcYMov1mlpY8at5xYc686jG9edVjBtCuMytUMVZen+VLgKnMug3f2ZbGzJ8AK5gtm9RrDtVXIAGuMqs+s8YfwjwFE2A8s+QsS2sJs8QlwAJmFeesv0W5oA3lNSxqWJXWNj4BLsRIy/1sRwlhjoQEKGuSlvhvpBvV/lECOEDajc4lJ9L6oQ1jljmQ4SStUaEEmMPGrJYyowBZkQT4hNmyqgVHUV+KJcC1DNJ6/XJmI+VZNgGqAZm8B0LzGljIwLRktXnQ8pnY9vJmUYTGLJcAyUAm77nQLClqcxmYz8BCaMNYLkvbXS5Na1QhAQ6bpdV+0CZEPauSAFVAWt2M38vjC9ojNub0XLM609pWS4D5zIq0fXiUrEYCbIqRVr/7jp5Uw8cJYGdxC7tezisM6ibARpbn2dHfxgtzN8A4IIu+P0JLZMbPYyGDOGiYAElkumswNFWcx8D8BhYymM/SSG0uNLbu7Jk/1m4QF0JT1t5Y3TOngXnR8jLj1zZ+NGXtaMram6jrc6Gp4nxoqvmCaKoaoKk6zoGmivOgVWD2YM22b2k+nR3JfZXiLM0S4F2aVUNLv8CdiepzJUCeWGkf/DRSo/laU55ouu0MLZEZzzNsEGdpg+vHjK+fAy2JTHf/hybmq647NwbQMjLj1xpBNBuZ7vyOVo0ZP7Y62+I2wYwf67xom0zvrQZa6sedn1Ff2idAfWbOsnVMNGZHPBeDtMH7Dg6kXNB2mKUFSvU=
*/