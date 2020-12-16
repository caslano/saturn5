#ifndef BOOST_METAPARSE_V1_NEXT_LINE_HPP
#define BOOST_METAPARSE_V1_NEXT_LINE_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/next_line.hpp>

#include <boost/mpl/tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Ch>
      struct next_line :
        next_line_impl<
          typename boost::mpl::tag<typename P::type>::type
        >::template apply<typename P::type, typename Ch::type>
      {};
    }
  }
}

#endif


/* next_line.hpp
mFy7LwNQvNQs3k+qiq2ugfkIjan7REhW+ypZtRidUrJ6L8pqdkTOSWaL8bXGmYN4+ym8n6v4lvcj3jyFdzbSexXX8eYj3gGI16P8ZxujOuZaPMF88bB09+5CboN3MI73RjZuHajkutj0QSXXD2D9DlJyOETp+8GIdwjT92G9h4i0t3p7iJinNSLXdaAvwX8D/XkRWwP7CqnRIsgSYXj204XR+mE7k9G0ccaqlbv7HEd+LzcB+J5iRPpfs3FNY1mEfNd1Yet/HYb1Xq5keoaS6eGIdwST6RLWfitV+3XBd5dqv1VIo1uVda0qqwfxer220G+K0dyYP2Pkh6OezWJ8rlF8HhWBn+JzLZa/jviEcwRkD45h9uBYRe/DEfgpeschvXik0nrLQBq2N9PuCpXXuhIkbPxWJbMBLCPB2udWpfPJiMwzhHnWszzNKs90LCcVsXk2YJ6Nbh56d2G22sP6R0i+uzCK+dKsrGOUHmSRvx+jPTsB8+RID0hu49SDOs+ncuthsdvwDEQxEviOlVqQCYCjft2mZHYi1iOJMtuM9djC6v4rppMnKx06JQI/pUOnIo3TlMxOVnpwOuKdwcranZX1UVXWWRH4qbI+hjTOZjQiqo7nYp770X5+HPOcp/hLKZ07H/E+GanqXGZpCyl4Z4lit7YyXhNh+nsd+/sm/Hsf4G0qi5W6EPJeBL+L4fepiLSTBfQaPo18f4aVs4+q66VY1ztRJp/FPJd5vkvge97BMVKB/lXlGBx7Z2pEztU/D992fZK3A5yPjdD4ADhu383q86nA3TbCAxzCg38F3lWkQ7jmQLahQD8Yh3TeSc41KKeLeUw04n9F6ea1EUrntC7Ds7fXI/4V9G3xaRwU9L4u04GeTP+mSp+r+Pl2xI4Pn2Xjw3dtG4h8N6h838N8l7N8Nwbku0nlu1nx06nSf6DSL1Hpt6GsL6nzl3WHwv2hopVR6T+OkO5fpnzWn7K0K1TanSxtpiPTfhGxZ7+zNg3wHPvmLOpd0ba7732iX0e43vjf37kLeQeaIlbwd0rm0Bdg31Puv98dof5UJL0Ta1/3RFgefPuI1iKD9B7W7KlvQZkU7ziTv9sHdfszttn9zB95L5ufPKjq8FBE8zfBeThSLm4g+N1Pdx1e0X2M0R0NWbp/iUjZjar+9XhEznnSJBeL73tXCdabSd4gN5IdyRfW8EW5/n77D2XfIB/I17/++CzyZ+rmsLeYnpO2HWhIPX0evwGO9o7WjIuu7hLfJ6C9pDad7GzHNn1J+lHQ9v4YWMo3yXkZ870i28aPCzJ4DXFfpzEL5Gf+lrJ5M2LLnalk8x/M/x6W/zy1FvwM2kynAWNKIrZ9ahrke+It5e6UGDMeAM5sNLC7Zepk+eARwlzWH9M+pcHP42TkEf51cXZqwPZl/M/GsftdDSRbSPP1p12IFrY/1d9+U/kGBnjwkzyGqXxIk/pV3yDX5ovKnjU0MJ0hnbO/WqkzjQ14xqCBtz3hg/zgX2lzmjHP7jYP6jblAf2kvLVSt9+NeffAvJRm7DvuP6g0lDndRanksVepPak9Jiq7sTflB3sqy90XeWqx5WobBPjSNs9ucKo8s1zdud05slwoM2Acg3LnUj3BJ5V7WImwxZmHsmmhN0xsmyLd6+G74Pj78wENEs/QmxmAtxDp79dA45+WF6QJeS0mfUXa0h4f1CBoQN15bL+lcbDSeYBjurVnS7ANPyR0EsdMh36NIZUXdLIV87Y16PGefMJJWN+l1Lcg3WePCRf61jLiGccZaSeWNxC+lSWvo99mH4F8rmjQ5zqCdb6L5Brc/wGnG2ke2eD3+YAvWg+C8nsR92m2jwj9DdcrSX8ca88=
*/