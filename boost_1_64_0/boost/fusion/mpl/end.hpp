/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_10022005_1619)
#define FUSION_END_10022005_1619

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/adapted/mpl/detail/end_impl.hpp>
#include <boost/fusion/iterator/mpl/fusion_iterator.hpp>

namespace boost { namespace mpl
{
    template <typename Tag>
    struct end_impl;

    template <>
    struct end_impl<fusion::fusion_sequence_tag>
    {
        template <typename Sequence>
        struct apply
        {
            typedef fusion_iterator<typename fusion::result_of::end<Sequence>::type> type;
        };
    };
}}

#endif

/* end.hpp
c/pXhXoaNsaCZ2idq4D3pJJZzbBfyOVf0EzoF7Zh70ckx/6Xep9AlVXcd9xSZRb6jhxfblNycd+xoMtQ+46i/5x/1SgujRN3UJ4Z57hsuX2Vnhdn0XSJhV0+OcrGxvrDWfhbL9nhNx6/Ps6bxtlsmoX9V13X1jeWvobOn8wXf79Hhyd92jryoRnr08r58Jxkrc9aVLr2WftKsz4rfMwHS26kT9pGv6P4kT5pO1sXacb40U4Rn2vT6fe+LLfNja7SY22nBTt8qWLjbUalU/tW0g63pU2v14VXwUzphSMYMi+kaTPOkDnzmPyKKOPNmeMbvGoER/Ehf8+MM96UweWfH+XQ3LN20OtGOVMNN874l47mPVrDOk+NWb9mz2e4XjPUZmaGizy1VqvRymzsHNYzI8xpBxEDP/51nvFL8kNK7o283uupknUdHfT/b4jp5bpMR/9NGePatwJ5Lf7NGUMOvU8Fxqu3GK28mk5ZEvTlIxhfKB2sAyiOJn4ML7YWWuSnc/k33ypYPwvh78pnGv1QZ2kRzNXPnzFk7MPPz3mmzen+zgU0c970IUCiDAefvaDkDk4dA4X2X7z9xRQzDYSZ3i0uoZjjh004ND+/pGToAWnLzF//Uoqhh5QBIc3nBcz0YZv/h2jGPy7kKc5/6Smam2NmGWl622UEQ11RhNm6bE4y1BUB4nBWAuaYZfqfuqxgqLsScaGvmbycZLwhR/L2dsXR/7DxFe56BcWcKFlm+427JUPnpC1TetCVJEPvjlum+UrNHJq1ddsdu7JkSpN3BcJzpFtfRTF3OTS7Z0zkH77+hw1365gNzP9Cca77N+nKfemqihH1Cyb/7mtIZo6bNzODu1xTMsenmOGzaH+/jmTusa9w4MTeSP32rpkPOVDwcd4h2wBkXpOE3qzVTvkOUvjYm1qXnSSvW77TMtxJinLWnFu9yyJcQJ1ZRkZ6DmcO3xXnZMRYl2O20aTtH9rcaZ2S38r9HHQqHR9OO2kg3VGd3qIR5bT1+Siz1CQG87P3gFn3BJ+3eV+mteitykZdd/1JFWn9gOf8xNEPH5h7FEK9c5ICrHqMz6EXwbUxroX3wOf7gkkLrYw+Adp6XbUsMcbPd4f2MDtbdt+SLE9NpNvkbawpG91ttrC+ZXRaqJJztqdk+tTs7PHJmfLs5MwUPWNFsfA6TpxJYxLl0R3BUYy8fgmGbmNM053tNF0UHdt38tQYo9/ZLUWZNHMom7Rfpu744Dna1Zxr0McA5X7c/PFMPzRVuhOll97uSh+6TK9VwI+PcutL5XqDdvDa+l56hPUOLMLrRxn9zgts4kaWzc64oR3eNMbQmgAxsI1YnP51HGcdsNObWc5XdAf9xokIQ26YvKSJt+NGsL5MPM51VorxK6f5rHtc988oiPfL4xyqDH1ljCN/PwsQ40SsXKi1qTcWY2HRBrVktqPM+pqcf+fuHmHcNxJpd37VFYbo67dj6XLPPKUL26fh7948xtWoU+K170Is3rasVz43X4qypl55nhjleb0AeyG3iHOiTtiHGRFmWJ7NwgiuSXMvavwynduxMPnqJLjcPTSXzic7jfQWLttv4TzNif6Fx9anBEy14VZzOU1xvdxutOiBVmE7YVy+bGE7gY7bKdSmZBl07xlw7ooRdShn02SzTYQc2+EKbCJgYrbVL1xeM2s1vHeEPm5PhPEdE/rpKEOZxMvDoj2OZl3HuY6+eiRHleD7dawZjmK5oP27OLzHn4xFfsOn2dtZ2PmRXNuEjTKL/ca/YYI5d5RpyzJrIq17o6wps8JIjssMY3CM5Y4BZduNc9GyxVvZo36jGzTbWZzP6qKCNedbjuDYAJDuUpyN1hvWFQM=
*/