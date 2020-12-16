/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_CONVERTER_HPP
#define BOOST_MULTI_INDEX_DETAIL_CONVERTER_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* converter offers means to access indices of a given multi_index_container
 * and for convertibilty between index iterators, so providing a
 * localized access point for get() and project() functions.
 */

template<typename MultiIndexContainer,typename Index>
struct converter
{
  static const Index& index(const MultiIndexContainer& x){return x;}
  static Index&       index(MultiIndexContainer& x){return x;}

  static typename Index::const_iterator const_iterator(
    const MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }

  static typename Index::iterator iterator(
    MultiIndexContainer& x,typename MultiIndexContainer::node_type* node)
  {
    return x.Index::make_iterator(node);
  }
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* converter.hpp
5WfCjvMC9KGVQGHHnjM38K08S2Vm/MiVHSyqS2Tlj9F8odN4K+UXIo99x88CrxKY9R55g5c7nuF78Rwve+4mhWN5sdGFeT/8PC+Lb+W+G3mecKNZ2YcfM+cdnxu41/GNNcNHmB06tmOB0DFZ9uLYY7CWuS8n3gfDzCplD/brtimK1LNyU699hdeDHbmpHeDYYkKYzq51JhMnVh5mZVTJ+Fzm4VoXvs7P3UPPtrw0sOpGdea8uWZVqmbuej72WV0nh5m8I5yilCMzdXmDYVNj+VIql4tE9lfZmSItNocS5E7D4420Ss/2ktwpBvPK0+oZaUWBFwZJ3adk7/AC75iZ1vPWjbZOgyiy4rpcnlxYy0lgznNNm4vXGnJpHAZulIR1Y0eYQ0PuPaacV7qOVTh6ovJnuNw967XlHU6C3EBl4wpTr0FTypujFPIWs/xe3m0UODXO3nJGDAtRq6+Rc3EoR0WDnOOjQzj1ghDvmhFOVtKk+PmByaHnGG8dgpvrzsY4cOgo5GXuIU4a3CjzD4ZysMz4tsIgh7+3+ck+xyeZwe/55ATixgeI28C+a1seREdsx3Zuy4OMIe8FAzzeHnj2NMDDNsG4Tu0azjHPl76DPFwRDLR/uptzzPb/PMOHt//dbwQcOgtwG+uzgzjUIeK7bmzikALZUykcP6cDeoYLBk79Q4s9DIOIMd43Kox8dUGStO3emyA+MIHT9jhj8nhVY12O33QoD6JCzjM4h45sTO8icsyFJe/Dx2+2HY/34W9sy+N22zN7B3lmf3rXEA7tTwduPoib/fbZyDHnYrIPH+QwfPUWBJ8bnIcvKpyvsM2ylLcc5NCyfJHhw8fGwX19Dp2PsA8S/DGlN9C3d92K4awfLCLGF7VmP/jOtjzeD47fejseH4+f1Dxc+fPxfr/bmDgf728dwHk/+zPF/Zmh38jV/Ywz9Bv5A86hRcEyu7dFDttUmPPyR4fy+Lx8+HbDOWb/fq3i8cWuWb5dt2ecoeV79lAO/x5erDi4Gjffr07vYOJcH3bexI01xh3uCDjohKDcZC1COO/hHFxH0LI87E6EQ7/vpK2+wjjm97bPe+Kdh/EG07zMefh9o+V/3gHCwe9Tf3zuvQvD4RvTfxeDYnw+R87kXZHD5kT6HTq/DaeOCuOauxvyzLmz/54BcujcSNZqd0eczWt0Thq/h+bgvNT/FjLMnEfImuGeyCPzQD8f5xA3xi+pF3Ev5LAxZ7bzN5BnjBWqtz2oOaSvkzguAQ66y6v08869kbNtP7+EnO37eec+yLlqP788lDeY5qn7Im/bfn4FOcP7ee9+FOf9/BJi2/fz3v2Rs20/v4ycq/fzUw9A3rb9/M/IGd7PTz0Q8W37+RXG4f28N4nYVfv5FeQN7+e9Q4hv288vI+fq/fzUlOZt38+vIIf381zfb17meuWkTB0nda/ZixhoSvV9ofdqe5hZuI7Dzw3vPooIrnnuSc4NNY7XZzod/WRM3x57kDfwftT46CAHNuw0vd4QjqR0VvX7enru5Dy2Flse41iX5xnr9/QJXr+hlwRFmFy3TYbWd5yn8R0tg9K37dxVflUse9bL55ingb4f4K+c4PpVxwr8JPDku8cPkh3CO5Zb0v0i9Hj0tsnf1P4Bky9ElHplGrmOkNc3imNwt1nryCGCyiXsonIJO61vkqAfVjyjXGY+HbLMKawiEBBBmPbL0NP6qD2UP+3lgV3YUSggKeXcRIrlWszWOmkqA0+r5FEUhqEvbliX93oX2t1uexEdW1LDE+Jz5MIxms+kjHw/zD0h5xiuFz5PeTNlkcrGyRxhaF8bT/O1znuZ2+DGlpP4oU0LpHzEFr5uFFYzq7pensg=
*/