
#ifndef BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/preprocessor/seq/subseq.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>

#define BOOST_MPL_PP_RANGE_ITEM(z,n,_) (n)

#define BOOST_MPL_PP_RANGE(first, length) \
    BOOST_PP_SEQ_SUBSEQ( \
        BOOST_PP_REPEAT(BOOST_PP_ADD(first,length), BOOST_MPL_PP_RANGE_ITEM, _), \
        first, length \
    ) \
/**/

#endif // BOOST_MPL_AUX_PREPROCESSOR_RANGE_HPP_INCLUDED

/* range.hpp
u+I9DMA87I751y3KmLjwQq5brC/lboQe2Bg9sYmU2xMHYFMchc1wLDaX5QeRUmT5vUmhpHKkAFn+RhlDsgkr4masgi9jE9yKXrgdA3GHjDExjyM5l1LhL3HN18McZ/LfMMbkBvtFs5ztTmpJCiSFkmaQUkkZy+1jTOyTfbJP9sk+2Sf7ZJ/sk336f5keTv//JG1J9P+70K91y5dYDAEUWj4s1nSdeC1e/0p5/UL+6yFxUVF6LV0iDfi3aS60pa9Y/1uIXO5KbFHyVFTl4Y5phmhdTDSrzV9GlUL/PUTpeslfhrMxT1R0vN5gqji3A4zUJhrHKRxX3b/AVcYHzCY5STz9ji//W2rur+rZvX+3riERXPhanLEKUwiERoQzr+obsr7/Pf9s7J8cYlwXMWoP07xe5jf6FrzePFn67U+jE76F35Infan1fQykytRXKW/wA/oOU1OM64uJi9MZ5x9fYeP+a1pDoX1d6ut89WFRWst1vtJXFxlpvucc85b7+7mpt5P03cm9DNT32mO5D+4nVsqQKfNRHFCRaB5/UZ8dxt339Jbn9lmew1eV+Szz/HhtxER9wWvYfQq5vv47tnnoc+ZtHq23bO0H9xNbj4+wbE/L+l0K3pMxRBem12sjZZuqtpn6HhcXpS87nvI6YSzeU/o3f1vOqDC9wXhLDgpcpOPj3RfMx8MfK39d1bXf3BXBEB8dFqPcQjJaTye7bBtXq2PiaiH9u7Lc/P0b01DZv3yH2DhO/sXencDXcO0BHL8kCILQkNhjqX1JIkiUin0nCGKNbCRkk9wglkrta+21L7W0qLWUVHm0pVRpPUurRaVtKLXFVqG8vt/c+7/J3EkuN+r1bXc+zudrJnfmnDnnzH7mzGbts2ypV82M5S/1TNKvqSNDZR23Z8wTGEN1Nr47Th6fy2O8v71tYea747ukfQN1zlBG6m3YUZ5Dd+THhbAtPqSc3JbIc2gKKSY4KDjStA2Hhj+3XwKljNKWmG/DvZeayixnfTuot1dnzfaq7TMyzYo2BIbt18OYXynklQPr34q/F1yqetc+m/xqbmpHJg0EFkl+zcdH5NfBpRbziwOK8l9rvhOap2jwMvN8a7n8xfJNnS/qthWlVPXNeLyTAxGDNs9KqfJMe2xU8s+JvGtLguowXsiYTikHy/nnn9+4whPl+Jakk/xbbjn/SHdcos66vkmbrFDlF+Nnlmfk5wvn331L9UrywY+F+rFeNRnPb4hf6psmH9R9gaTL7dUy0g7QBX8nH2IN8+cyzwRZd7fntAUcuzJzXYsxvsuYlqDBQRHszqyrP6Zjp/oYpd2HFVNtI6FhkfogLKEu96CRMpk6JH1VxPJ/9vjxnLixViNi4mSfFUC+zSxgbOt0S5V3qZq8M/32IL9ty/Q6yrpiCVX7rfiIUXRExOkhCVXPc7+AcR0nqeZJkXnIB0lNZj8ar0sZRUplqyTt2MqjYd+4WspIW1HlZEO+KfXMejrmHfPt3H1N9tt5LFouJ+mriR0k/33uPtLUT4my3GEyj+aYZvG8RvabUv9lGVL/n5C/4SRwGuPLlPXCYqpyiaUQwXhsk2nDmCZ5btZvjHehzHa6doRPCE+VNmiG/Mk1IkIfTY9T1p/XKOkcgdl/90nG5bjrbBqXY6op/+S4m23/Vm6MZx7vbX2i5KS91n97nygPDO2vHif2+GZGce8uie4L7qW4BdR8uX2ixOrk2g+SpM+Lghgqld1P2i90w1ewO5ZCf3THXuiDAeiLvbEP9sEg7I+jMBjHZPa1wXWoXMfJ9Z0SrzK/o1yfDpZ4I9AZh2BpHIoVMRKrYxS2Yd4Y7ITDMAzjMBrjcRQm4DwcjkswEbfjKNw=
*/