/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SET_LIMITS_09162005_1103)
#define FUSION_SET_LIMITS_09162005_1103

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>

#if !defined(FUSION_MAX_SET_SIZE)
# define FUSION_MAX_SET_SIZE FUSION_MAX_VECTOR_SIZE
#else
# if FUSION_MAX_SET_SIZE < 3
#   undef FUSION_MAX_SET_SIZE
#   if (FUSION_MAX_VECTOR_SIZE > 10)
#       define FUSION_MAX_SET_SIZE 10
#   else
#       define FUSION_MAX_SET_SIZE FUSION_MAX_VECTOR_SIZE
#   endif
# endif
#endif

#define FUSION_MAX_SET_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_SET_SIZE))

#endif

/* limits.hpp
inSJZBY7xpvvtWYzDuPm8b0z/95JPQQx/BrDIvkeyb9zMI80R+LM7OTf+/AMamPOFDLMe4499kx3Rb5H4RxS/TCmRW1Mmp18D8Fz6M/fLXc749T43M20DAvDHMyTuDU5fC8Io8ykPL4X8P00+9DrpPqBxJAhhZPSSHmknaRC0hWSRzdi05CiSHNIG0hHSJdItboT64YUTkojLSNtIR0nXSK53eJu8SWFkmJIC2+piD9T8an4VHwqPhWfis9/pv9/YHRWujXtz+r//2xTi/ouc99Kxd+h/jI/5vLs1zbo0D5kcGA6D6GRf2K0EoUgI6Es76r3pJ/tKuZzJVl5j3pmovH9n1Wl//dJfhu2wsM4mfGtA+V5RV2+sQlkWqa+OI2HGvriGJ4Lri19ccJswzJt3/PlOWHH88db1O9xap++j5rKc5fOZ8jknbU5gWrfJkO/eum7I+Nly3Pk6nT+mrgIMixLnrF0fJ/JOM5nhimDvN/RWY4Q5/x076CV6dVhYc5hSnlt75jOG2z/Hf+ij/37Efn+gnx/YYj+75XD9H9fF6b+Xbdug6pKv1zl/ibOxZmMUzjCbN0qD4qXLVaC78gS30MssRL06zLPsC5XmqzLYN16M9Zr3Lji9Rqr/NOwPmMZT54/drGuIpzzZHp9nV2QOhsqzxuHktIpd8FtZnWWEJdWjn7/xjoKM7T/CGedyXLq64hyqvuLNRIDYLiUM4y0mGn9x5iV0/4u5oSU6f9WWakzXVmLPHV9BeR7nKwP12WPqm7PMELKPkzKHhPpuuzp09L+J8peVfq6D5ay9yfdT36FJZQ9a2pmmZ+HNZY9yFD2EGfZZX9SvKwjpKyXpaw/ynO7V5VyK8eCYLOy2uNgxCfznDgtJSs+k2PWlNgp2aX3AVb2Ca/20e8TYkz6gSRry2oeA0W/zBLDI8S4Hcty3ibLaZWD5lGSp9yr7EHeebeWsJxpibGZrJ8pKVnJ5em/ZnxmfYCUwSI/x6+SYSP8CnspZehRQhmIIFL+vBMSs7KNfW2yMrk+ryvPHClPf6mTYKkTf9d1IrVR3vI462Kw5J1Q0z7yk7KNrCWFKO2ut+u8J9HflxgR0xPLsD9V2tuSYLW9lWG757u639dv92ddbvcSh0XfPnXLWSTL2V7quDVpIGU4GFzyciYkTipXv4UaLtpcjMSIWCn5P0q6hXGtt7jOn1Vcrv6artZxVC2JT0FGrfAe7MO4ll6u886SdVyWPg3KOp7bW7+OI/TlMey77d9jDPv2ZMO+3Wqyjrsb90G6/VKKbv9/XZZ7ifTfWEiyUiaPYSbLTW1PT8wsV30b95lB6jmCNYOOKNLWdcugWy/Lbpbns2Wf35aUpbRJ8/JlRcdmU8okpVmUa19kVk4PZzl17fRabfsMeirP42F3nM64lnAXZcqYYm8nZeijq7ST2iMM/dtMypejL5/9vLUMxyNP3fEoLVl7bplrm596fqLGAlnqHM6xX2J4lXou6vw9MHg4yyPzV76vMnw/J9/JR1/PdfifPGPvjdFoVep5lFk9p8em8oMuiVWfWIY4H0o99xtdtmO8sb1ay1DP+v11juE8YGaZzgNyPJznxJ5yThxOWSL6mS2/rXx/+DwgzEVbd6sr7/+W7W8Z6XbGLXBdhnKfB4SZnAd4uDgPWFjXcB4gdXKlr8vylPs8wFgXoxznIJ7OPvmtsC5OZFyPAa7z5vgojZJqychM4BQ0OzGrbMeLZgPV9uk6Pp5hP1Bbfy3AcK1gZpnbr7bOr3sWPy7fRp7+ruu83MdlV3V+ReIgVJY6/5V0J+MeDHGdd9a/Ued7+petzsNM6rzIUOdFf6DOHdt+bn2JbyTbXRBpFHlaS1k=
*/