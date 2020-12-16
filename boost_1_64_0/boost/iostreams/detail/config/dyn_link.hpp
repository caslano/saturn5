// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Adapted from http://www.boost.org/more/separate_compilation.html, by
// John Maddock.

#ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_DYN_LINK_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CONFIG_DYN_LINK_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

//------------------Enable dynamic linking on windows-------------------------// 

#ifdef BOOST_HAS_DECLSPEC 
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#  ifdef BOOST_IOSTREAMS_SOURCE
#   define BOOST_IOSTREAMS_DECL __declspec(dllexport)
#  else
#   define BOOST_IOSTREAMS_DECL __declspec(dllimport)
#  endif  
# endif
//--------------Enable dynamic linking for non-windows---------------------//
#else // BOOST_HAS_DECLSPEC
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_IOSTREAMS_DYN_LINK)
#  ifdef BOOST_IOSTREAMS_SOURCE
#   define BOOST_IOSTREAMS_DECL BOOST_SYMBOL_EXPORT
#  else
#   define BOOST_IOSTREAMS_DECL BOOST_SYMBOL_IMPORT
#  endif
# endif
#endif 

#ifndef BOOST_IOSTREAMS_DECL
# define BOOST_IOSTREAMS_DECL
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CONFIG_DYN_LINK_HPP_INCLUDED

/* dyn_link.hpp
mp/fhdXwIvh3eDH8N7wE8tAi1wiug13g92BveBXsAy+DufByOBiugnlwNTxD5abBDfAsuBHO1Ouavro2mzXplvS92e0/wK2wD7wVDoC3wbFwG5wMf6D90NvhfHiH9kPvhsvhPfBy+CK8At4LfwbvhzvhA/B36v57uB3ugQ/Cf8KHtP18GKJnItcEPgIz4KMwBz4OW8MnYAf4FOwMfwx7wqdhH/gczIVVcCJ8Bs6CP4Vz1V6i9hXwWbhW7VepfZOGcyd8Hj4Jfw5fk/hpO2bWpaJLWp80xpBW8ntF+yE7NH1/CfvD1+FAuAsOhr+CI+FOOB2+AYvU/WN4wM1bvQ/rP+U+x2P2aT5+GUYPYCiJ9gimwAK1z1f7RzAV/g2mwU9gY/gZTIduumfCdrAZ7ASz4LEwGw6DefAM2AKeA1vCItgGng/bwXmwLVyk9mWwPbxE7ZepfR3sCDfBTvBGeDi8We2Pw87wSbX/RO1vqdyXsAtsFI7Ym8AuMAN2he1gd9gJ9oA9YC84BPaGY2F/WAhz4UJ4JFwMB8KNcAK8AU6Et8BJ8BE4GT4B8+DrcDD8CA6F++ExkLR1joVN4XEwF54Aj4cnwmlwGFwMR8FL4Bi4Ep4Mr4SnQDf/S6NrWeAa1TP0ysw1TEEuHX4HDoTT4BB4FhwNp8Nz4NlwJjwHXgzPhRWwAK6AM+AqWKD3HRZdmwGL9L4pmEF6X8YQct8JMBdOhEepfZbaNRxda2APJ0/DOVXDOU3DwU442DWcPPPOm7zTcLxny3GtIgQHwA4wF3aF0TMDB8Ie8CjYT69ruFQ+icPtgFwYdoRp8HDYDHbR+3SFvWE3DbeHGafo+1V9T+wfpwzW5z4WToTH6bzM8XA2PAGep/Ylar8cngivgSfB2+EweI/a71P7A3A4fAaOhL+Co+H7cAz8Mxyr6TrUvPfiGTWeyZjoN5TUiZKuV8OWcBPsADfDaPpVqv8+lvRbjZzLK2AyXAtbwCs1nHWwB/we7A3Xa7jXR9+R6Luepb4zIjtp+nWFrWE32BV21/FDDx039YQzYC84B/bR9DwCroN94Y2wH7wT9oePwwHwBZir811H6jzXQHj9VzxDUM8P/NacHXgozg3UMwO/NecFWs4KbDgnMMA5gXeOT5azArdzHuDLmH2YrFtSnL6YCZhCzEWY6zGPYXZhDmByKlOcXMxYTCFmJeYmzGOYHZh9mKytyGDGYgoxF2Guxzy0teHswYZfw6/h1/Br+DX8Gn4Nv4af842d/1c0P39pweKl7gmAX/v8v4VtHPO9CPNa8uuqz9IFc7S7vnazrHnMGz0xX9bdTxuce0z+8KnTomsfd+c4uM8udazfi6h/XYN4lcguta+p3Wz9Psu+hnaz5fssy3dcKmfWt5XV4ewr97la6HNl6vq1q+TaUpHJsHwXleX5LipMjE7UtJ2XFJ+2e/Bb6UtbPsPxp69+jzMzYfpWBkzfyjqkb2XA9K30pe+iOqRv5JuamV8rfaO6m6eLfrvrjbphJndkXrwmfWXNrkncgLq7w5MOs7ITp+0OXzqU1yEdbHrGvSQdvDo0NCX+GY9zI3CN7xm9ShRQh5xrgj2nypnnXFyH59T8tj+nWWtZf2v67GszE6/ps6/ZTLQWMvEaQF5Gcv2HN+zpdWt2xmevvP/ZnhZP/+TvideQ2tdgJlrjWX9rKuu6FtW+BrPua0Ltay3rvnb1UK+1dOeHO0fbEK27qzAhTE7NmZQVUbnKgHI7VK577XKUtdrlhjXMD3/l+eGfpyV9q+eI30pLapgn/grzxGm3pji9MBMwpbc2zOM2/Bp+Db/6+31T43969/Uy/l/SxjHnbaclGP9v3xQ//g869t8=
*/