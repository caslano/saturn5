/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MPL_ITERATOR_CATEGORY_07212005_0923)
#define FUSION_MPL_ITERATOR_CATEGORY_07212005_0923

namespace boost { namespace mpl 
{
    struct forward_iterator_tag;
    struct bidirectional_iterator_tag;
    struct random_access_iterator_tag;
}}

namespace boost { namespace fusion
{
    struct forward_traversal_tag;
    struct bidirectional_traversal_tag;
    struct random_access_traversal_tag;
}}

namespace boost { namespace fusion { namespace detail
{
    template <typename Category>
    struct mpl_iterator_category;
    
    template <>
    struct mpl_iterator_category<mpl::forward_iterator_tag>
    {
        typedef forward_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<mpl::bidirectional_iterator_tag>
    {
        typedef bidirectional_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<mpl::random_access_iterator_tag>
    {
        typedef random_access_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<forward_traversal_tag>
    {
        typedef forward_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<bidirectional_traversal_tag>
    {
        typedef bidirectional_traversal_tag type;
    };

    template <>
    struct mpl_iterator_category<random_access_traversal_tag>
    {
        typedef random_access_traversal_tag type;
    };
}}}

#endif

/* mpl_iterator_category.hpp
v9xiXmBZiiw7Rqr14sH5xWF3n4fqpUi0Njrh2JZzy411cGTQ23ta7K5QypVQBDl9eUNUxe7CWyiSVyzkFDQlZ/sPkf806pfMlRHOKXKZKQLchXu+Vj4uQ5TrkiU5SDRKzHFj0y/f6/olShUt85nU+Xx+cDxsZu1GSOHbCfdLdjmrpFkDGy9g4E75p3gvSsV5yp1ajtFSV4XZCVqU4TzQ4jLh3ATBtCYbE7RmzsKZcrdisA9poSwETU7Pa0LH7TMC4twhrCLOciGkimQxrEVboYB9gLCSRC2o0jz2e/yonRH7jo7X0hSYi4qcwz49NBe99sO6VrEoX2JiiWlHXjerAVnxnLwPdrsdX1bZeMHtcrcrF+uYm2vT9j5GBOYrmdKQTfV5vX98MlhFNu07hxgRLSaQEDk3zARyuE9ftDoqdHaYP+vszo3IhQpPLivByTzMq9slAja6fCrCamJilpxFNbydXNU8R7HGiju9f7qVd7fDqqCK1EUCdvZggoW48QjLCWdZ2aQ4DFawYsBjfPGz/i6CZZEZObR3XzxfvahP7LTe1mJ2fLKUelvI4KII9rBg89vVy3NunNbjnllWgcn7ufAehFNEKs6p8MvMztdfcnZcLWEnuy2sXy1214ScChOWrAPQH4F9HcRDQPIiMcplZVqlYo1mfyMP586uTcmqyJl0DcPe0Xw2DMcN12inhLCUxKx4slI22CGXFXxnwHf6z7HdoQ3cScMGW9GB7MEy08rV8eykltG64rDN3onwjnieqBVlhJ/eP7k6HspABSC784LKkERQaVTOpJq3zi+GRWKaKxHscY5a7F5KUSZjDanuh/cPz8/evPkYe+1mjF218re9l1Eouo4qN7/C9yhvq7I494E1riS1sjKoz7ZyeMq9OD87HrwjwScALOvBtgHVUbrCrHOUVL7B4RluEEZ/4lY+E+N0iFQ4svYRv7PTPDnDXWaLCaT4Iq20biBZBsGWD2C+jfHqUfsECdKKEFImm47amffOAgew9rXY3ayEzd6u2zQ8jiNbk+HnF3itpMPc5nEFWL2PTmwfntxi4qB+JgQfICvvnKZNl+CT9ws8nosoVupCyUETeXjarjOw6Wnxe85koUvKK87X1C5enzgebOpYWvlMpKdFs5QGwNIQlib4TIS5+uoWU0igUQQZc4NpnMlaex3MVZTj3NPQ4PLZSWe//PYWk4g2gWoR+QaTWwNfeCdrMbsxOZes5EBje5/eD2COorm2JSsAtByQQw/1kyJMKK2ichj0krNl6NxDrL+vdforzHvLQA8mC3u2uD/uL3Cf2XFKZYL2GTiXAZjml2x2794w+vE6+Ut8nylkpCp5DH1j9foA9GpcbfDXOzxPwfOk4qQAoMc2swXhORFCKU854PlsFV16v8lXDHc8CCuItlIPXtGg6yHeaWVucy2A/XuLTRWqjSqs6aaaC4P1uZ9bTCFJC1kYM4ABqv4+EtWTkay8TaIkrKM3TPg+3eFc0dZS1+EuAQfrX6fTEqVQlKsp7uUTnT7a6ZSHIrk2aCwtOwRYR+wTf4WxTGlpkg19X4KSGuwzEZYTIQW3OVGMBVrs34WwigSaqfbSQJ0P3sBnF4fDc0i8vNd9QyCsJJ6pnI1W0wkAzIBddLxZCF5M7icPGhbwDdHxpuBykFRNsSMvjCeEpcRzmjX37Zxp60thPCEcIz55OmwDE9zLu3WpwzHrUjJtt+KRD2OpGw9ZBuEtQzis2RH7xF9j/WSbBC+JTsDNKIax1GGlLD5KpTEW1xni9SMsI0HQKLiwgK2RB5oqA2dBOE6UH951Cp3iXj5p61GHLbp4a41GWKgtxr6ta6unWTIdJcI+ZPy+C2EVyTk=
*/