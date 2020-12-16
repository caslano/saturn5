//=======================================================================
// Copyright 2002 Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_SELECTORS_HPP
#define BOOST_GRAPH_SELECTORS_HPP

#include <boost/mpl/bool.hpp>

namespace boost
{

//===========================================================================
// Selectors for the Directed template parameter of adjacency_list
// and adjacency_matrix.

struct directedS
{
    enum
    {
        is_directed = true,
        is_bidir = false
    };
    typedef mpl::true_ is_directed_t;
    typedef mpl::false_ is_bidir_t;
};
struct undirectedS
{
    enum
    {
        is_directed = false,
        is_bidir = false
    };
    typedef mpl::false_ is_directed_t;
    typedef mpl::false_ is_bidir_t;
};
struct bidirectionalS
{
    enum
    {
        is_directed = true,
        is_bidir = true
    };
    typedef mpl::true_ is_directed_t;
    typedef mpl::true_ is_bidir_t;
};

} // namespace boost

#endif // BOOST_GRAPH_SELECTORS_HPP

/* graph_selectors.hpp
+5bKls01K2b8tcjzdwM9gjluX3V4Vr9aSyBSaYnv1TF1eqqHvrFaZpXEeKnyEYsnOnGrKqdO+FLMfbzY5gJOUoGRmWum63YfPUY4qM/e6yLWhRTQO89ybkMlMoZGp93jVZ/wpwRYVH5vfkPsK0URFNl2+Wh5zY2zlVIxK9rx0W+jv1dXqsh2sF1g3x1oqpf9EP32kuiZSXyTGL6XSUNnpjWdxS5zB40GKa6SF32edfkgVH9qsJn7weNKjbOPllvrRz/c/7KsxJrJZvis5F4uqylNDOejR9fj999Wzkn4V+tRV8WK0ZAMahSPsboUbGz+xka/r5B9iXfsQVC0uM3vnIaiDInYNla9Xp7IsjSLuNCHDhSxMOJwHa4+rjvF6VLreWabgZ4mdo/UXvXE4wWL+IVmTkubn5SpzXvSdEmeD5+zNQklTc4tM+M07VQLjVMm1n/3XrxSI7WpZyfc/ZEscernCndL0XGt6QTTQcL+vEmq4P4M7xrZH4Qf6I/n/ybw4evNF4WOnCPpx4XWSncFglUqrDxEq4ucWS9TbxAWO2uXf93NHpYPUhfmVOsgYx5Pi7/wdd8mWn1Ny5E/xVB5xWPjvYfdq/dTR2Ocd2mGEhP2OzOFruId6UwXHKD5aHOr5QIdtabAumiIUXYbX7Hm6rqf7csvRCy/dTB5fSveNOl44FvpbnGo2mex9+HFrJ2lL1zMXduT1ve23mzlye1myBA1fpel1dBcb9IWnrxyXs6GnZEo3v/FPRpC2bwtwj35uGZnn4/vBRtX42PoX0czs6PRPJy7g0kDZT3dvaFBzqy5RmRzrkfp5EVf8pNQn+WeeSkYlmck74X30UtgIH0VTb39wXFZIeMLTfeQxzfpMCGPnQihr5q6xoEfxwYbRc8U6WQdJ6TNWZ2NwI8pWXizqMZieLbfenT1XEtvaNkPAoP4gOlLrBftV0dzPW+OKFo2s/3Og5K7B2pWEkp7PGH+ooBFKM9gUPymQNjIWDLvkCq9Bfesc9fmzP5P+Z80LzaEd06+gnT8BBJeKZ3P4WDTdt9+piL19Po5AY8rKlTWwmmtJBSUVPy2cqECA6mGLHWVY2cpDfD9FDY7KoIYQzZZHda/uuL/5snAGWX97FMDt2NGeRrvPvz0yCPcyFZqrJ7VfmWlgVovvjGF3EeaaopaJrhHycTsp4jduIFV4v1nkaolKlnUVI4JzlXPzj7Is70ly662V+DjXULywyfe6aPBSlrQxUpI0uhJtzS+NpWrhKa4oYJt5OrYl8ChkYZdp/MWfJcLnkPjc8Qflu/qiQilqOJwxUp2pJ4+9fASDY2kjc1+1+qTbzr173wt5xWmmVI/hX3przzDy8pTdMnYP9ZUmbAvILgpi3GfLucVsWXGqasieqo4JR+VWXT2rx7nobR2Uc7dZWP28FUkoh9YfPohaoH76Uo1kbxDrOdvc4rKuzO2Yz1rNhfvLIzlJSs6dLKl/ZyYSHlGdMs1Y3KmJzm9KP9KDqdF/jOpLUPHjd+VSlJJap9ZXDnGid7Gb/hmc+TC+x9cePOF69o3C7ONb4y+tG+diLt9X/xh3cPme07KFEVLq1RdRPw6NmsnNh8PLFuq97ZGfvrNODkHs4BQKvnoCxl8QREvVqf7InjcFSQSNMKftZVfozUCP0S1fdk6JcE8EGdeKVybTHf93EpINl/0ZKYxfhMPGc8TQ8dqTtLzaWpbiU+rBH/LmyX3ofYDjzL1fIKWd9yl33leUH5bUXpmpDPZjcvwhHSkhNVIz3vhLcVLez+XXPfapz5oR34NbLvK1tISc2ZIa3bTS7hzfcXPN9QeMmyVNBQ88TY3bcZ75ExnUyjbTBdflaaO2I8euec=
*/