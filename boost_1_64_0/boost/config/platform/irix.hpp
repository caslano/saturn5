//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org for most recent version.

//  SGI Irix specific config options:

#define BOOST_PLATFORM "SGI Irix"

#define BOOST_NO_SWPRINTF 
//
// these are not auto detected by POSIX feature tests:
//
#define BOOST_HAS_GETTIMEOFDAY
#define BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE

#ifdef __GNUC__
   // GNU C on IRIX does not support threads (checked up to gcc 3.3)
#  define BOOST_DISABLE_THREADS
#endif

// boilerplate code:
#define BOOST_HAS_UNISTD_H
#include <boost/config/detail/posix_features.hpp>




/* irix.hpp
cIPWzZCN/a0Ftd0xkIo2nKwtOODI1agLZLgmWIHpgi20TaRvByIh66beL7WDWmq/Swa3FCghWPEZpSdo5m9ggWjebBQDWdAtKT+1vyZLkU3tW8kyZNP7T/x7tpBfe6it5keWQ+nI1PjI/G9LppaFLEgyOV3K7dzzSzU4ZqZsFB+V08D8f5dMij0oV0uAFME6wDA1BrIMNG/d1BjIMuV0agxkObKp5STzvyObXpZECLqjX2OdIV79zSWysDvUX5O98WRAC74HoPUQrN/kdzpqlo3WXLACGUPtmtly6FmbTH/WDocgtJZkXaAuXLaP7cN7LKFVEexmdPWrfI9DayXYzBOBwZr5/4PmhcmuPfpikmY2tJ0m3eLWep/h+/Q9BSKEdE18DoXxfROtraJb+415fuRxwQN1fSTntzk1nsvyUIERgnXcM/KYZhkP6T0sWW+vBTf5/v6I1gGSLU1rGMvp0BIF22ua/IT3s3qswAeCrf/2aj4ea/yT1kGQbS8wOoNjR9su2ESflb58jp7QeSerf3RaAsfuYqsqnbjCdf2Uxp9k1w9Fv8/nFi1YsGnrn83hcj7D76EEG5DUZalmqWh+ukltKcPAsgwsJ1drBD5/Kvx9XFeIFL6PqwuOP/Xz1w2SwBw3xKyZ7Tk9W5B1PPz7OM1y0FoItri1n02zQDBDrGDrCzx/pFkWWiPB5vfetF4zf5MZKgv29oHDGZoFoc0W7Prp4hwDKLh2W7CD72p9AUAmWllq890BYPX3eWz8/t1qhn2Uznn+rbfCrGxeZvBmk9fNpKA5aD+kngBQfe3ZaryWo6AZVlh0G5e58jKvE3hNtql/bP6C3yWXMMMtuqaDnGsZ6xWry2sW8KX9MjLnM8alDke/Yytr5u9Te+OfS349M49jQCsg2PM3P/yMY0ArK5ipbD5ec5nhcswBG9bs4vpECxDsl7iHa/S92HIvi085uSw7e+5pwvXiYn8u7DWc3+mjFRPsanSnLVzXaBbBZg+yTOd6QasgWOp7/vN5PQNaA8HiYtaO5LUVaM0EmzroD33fu/JmtS8g23X86lxeX4BmFmxu+R13uD7RxggWMjxe/7bM3wxRgg2tcG8hrz1AKy7Y4KFNO3J78ZdjaP0sWF//UkGul63/6BbB+RlYGFoR8dzen+/P7QWtpkm3Z2Uv8Xo+qITXn6Kbn+2kvl6jKn4/CmzSt3MOtAJCulVL53Ds8Dp+kyDkF7T1o1/5/FU3q88kZJertp/NdYbWULBjS8825HZWwwxdBStU9Lh+PaDVIevj/HNKG267mWjlBVs9rTx/35hjkM5WE+tMsONJjQZx7Gh9zLqV7dAiD7clW+7pstEsJt1uxTebzPnVU+uaTKrrMLSKgiWNnjuJ67OeHF90+7x9OHa0GmR9nfHmazVAM6hvBsycbZ9tuJ1jQPtNsHYnQ3jtXVYDM4wUbMrQhTu5nA3NUCKPbk3/yPOM21Irio9MakutqO2StQ7udIrjQxtg0u3usgnN+Zi4oG2Dl27D7eWncwydzHBF0e37Ld9043T4Ifd44ZjPpy+oo69dNkM50C1k1Kzf9bXL1O+SlQ4+VZnbIFotyq+f8/3tR+v2c369zOqaDLIP7gwBfW2vGfoKZiuwdTvXS18ztBZsw6dvxXKf3B/rGnQrVnw99/M2NC/daHxNZUELFuzK9DUrua9Duy3YlBO153LbHWCGNSDEN7TFCU4XTNcmWctf25fkcg40w1DBZo3644G+fldtE2RSm8hEswkWc9ibxiHOzPVyOvv04OjWtzn2wTQOIdvV6fIObp9oPopuNTomc/uEoWa4Idhr5l7HOL5wMywE3XzbBfCaUscwMxykc+S8uDY=
*/