
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).
//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_FUNCTION_HPP_INCLUDED
#define BOOST_FT_IS_FUNCTION_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_function
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::function_tag> 
        >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_function,(T,Tag))
    };
  }
} 

#endif


/* is_function.hpp
au4zKTvLFlMbI6BiqMc/qndg7rE/fM4DEdyf3kY3deJxbHUFmRoOodN2VrzxoB8KVF35Q+0VtFl9LHWN+0Veo0X4qcpfdEeOcVOXLvTk9tCiMS6Ud+sG7o5lCLA/iq23XUgJIbg+/wdEo6PZepsnpLZOFrri8+HfcAsbhM6T2I80jCxcSKkvnrL4yQ/o+YZa1nuvGrIJarxStA3vTqyiVDMVnIxJZTqqHGOWn2R8/D2BrjvJpVSWk9wmLz4zZxIGvJ244ruL2BsXi8JBedo7U4lbNO3AhzGnqHTRMfos1Y7Pr09i8MkTdmmPCzquTqPSSn0apyTDz2lr40rAULTU2BIbX0qX337Fb3dRjvgSqC+dTozE6HfqJY7uaEit88bRT7NgmXOQ+8iE0fUvX6lXeCP1XD7EG8yMqM6wh99zN6F1bwIxaZwInTujR+brzVAbrMoXnPiC5uPSmCf6BAUrFrDTfCLCbpbi9IpN+CAbD7T44/mgI/+vNwYrZs5kylFdpLm+iR//lUWvzJLJK2AbBZosZsG5wvSu7ya/eCcQIxO+wEt5PLGYC3Rx2jRS2RHJY+/VwGZNOXYWGeDWhrcsWrmcVhNo2CkPesYCEGRcRRU/9NmxkwuRdTiKtojoUrlQEZU5+iAndg67+XU17qzI4zuX7kXK0gze33QG73w3cNvaNqzn5dxwdThWXOnjHWfy6ca+qzwkcRykFCXp+NE2PB3I5d7N/jhr+ICiPFYJ8vXL/NvPPviluQj86Fg6pq/HV3sF4WRdH1t90oXkN1fwzHWS1Bzzkh+R1SWd9sW8TOo6wjTN+dyJcvT0RCRNHvYTJw/asuoFQ8jWKpprPztB++ti2fovD9Dy5Q20jlTRv75xrDzzPRRe+nL31S8o7v40vshmJz4r7+Fn2R7cMJXFz2Mr6N+wNgzXGEebDz+A33QNEn/qgUanRNr1uIGUv/+m3/e/8D6JKYi3DaV139ToyObJ3C72OwodiliT6FP4acXxR2YX8PveXvo29zjp2T7FkbOpqFeowEzRXZgwxpKtqtwOkbBxNGHXUnoY9Y4tcNHD8Mmc/+Z/KObiS/JwlqaHR5/gzJZinBsmTyYqEzHlmhjJdoYjsMCB6R3SpnEz7fm58Ddk8fkL3YhXwt0kWT7XRYjE6qRZ8TMjcnFvZaPLdpP7IncuJ+AEarYbKKB8MlnrrCSZURPxYNsmtqLXChF+K6G76BcFv7eiCcOmkI26MbtaJmBbaRokWzUSqit7uESIPo2W1YeyQTmUhyoxOf+LFJIhDYlIb/zZksbdcvfSiSorLD7STqMnlfNV80dQTLg3v6KUC91kE8qbF0+jbY2pJGOQ7s1VZueKj6NccDZHtVzHnmlOXCh4JRZUuFNbvAbZnNVGb9UM+lrVgd7nJ5ETtAVRD81IstSCxq5rxI6ZV1luMKMPK//wTqEqWhZYRtapdshp/cYtt4WjWKWAuxR3UafbZ1Y26Rbungym0VXm2CqziuuNM6Qs4QC22ZqTre1z8t7iQ/ZVh8np2DzsGzsZLyOW06q6GezToBmS9hVQyNscKDeMpJl3DkF0uBGiqqrxWAp8UtA/CipsYI/9rKBw1wlJI6vJZ1Q2n71JDTrOR5lm5TBytJBhTgkHMFzcCtO2umNN6HgqWpuJFyNjWNmfqRBtMcOd8zOowlQONtYmsDD4CNMbnbCsOcH2PPyCafL1XFHhJL62HmJbjb1QsvYPzb9wkFbpvIamvjal+tzn5kddSDPJiNpX36eCU0mo+a2OCb8FXKpuI90VseKhIR9xk79jGif9cbteE0MdpKhOeS4VBe2hjvMZUCv4QyPWmXAVg/Oo2+BF8tHL0TFqNKk=
*/