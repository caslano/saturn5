/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_TOTAL_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_TOTAL_HPP_JOFA_081004

namespace boost{ namespace icl
{
    template <class Type> struct is_total
    { 
        typedef is_total<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_total.hpp
D+sTTvWMmjK4XvdTe7iST7TsUCiMd3elH5wxZrg60KHq5K9wvOyX8dKgQTXsEN+/Ky3NUVKJAVp8utm6lOgkv0Z4s33Jl/Fn57lrfZsPO1LUjvy+A4YO1I/E4jV10GAprZkhLRrPJoaLBqR0OhM8qinErPz4BCwM6w6aZ6U7c12OwmyMTOm8bMSrcbwuucSpCPWOcbbPM9OsR2e9/HCpxTmQp3pHmkVR1zmuBRMKSwlmmFq9gpj0CK6KtydVSGd89QYOicOHp5Mc2IFB3TmMNLjTCjXUXqU4aqLIU+4zUStSq1bmbvUen9dvLlA1QJ6D5VNa8JuH32b8yABas4bFRwfVjnBGLAjhM3KkI8Vxxhl0XqzvKCCKYiZYiASECH2kOEY5/BSFHy/J9KJpFDb5SOHifW+E/r2jp1cJqgrNxeXta9sfm2e+km9xhv2IT3pGfDtmTekn4qhPPCuWdPiXxDMlPTFuPI3wa9yAeMrjxSPiaNKAeP5VDzi4qETMzdnd8Hl0VbiioWsG1LQbGkYLz/RzGLVcXYm63cTGUv2GgZt7qmkrrwPcsq28KNxqPLzOjGGKsv4vPEghNkY61LLBOCMj0X6wH9s7VGxKCj+L8d0mgt6d0oEwzAP8rLvfbncQf8WzF2k387gQYWWbm62E/cLPM6zpWi7SJduGPLy0oyWtifglreho35tps18ncF3ipP8npL8F4AHAJMDVIv1ET6c04XcQ6VfLa+UTHe0/FJnpT5LSz7iB+PVa095iC3LDWKO8VgMuprLJSPyX2zg0z0qT5oZlDX5S3nhXOrnR2ZKxIJ3GM332y/s7bPiJ3fXjbVXXJj5vy7YkAz0T7a2LRbkJfl6RmWixtXowg/lM2P0EvanMY3BTvdqE3MmE22K7U3GrjzgKquxPGTTzFLhKd9eZv5hsFnkJSTy3L1O0XeHenyXc4vkC7j6Dzbx0gNtiazXLmvdW4xLtqzfaY/7TFf8dQCc442n4Ef72bQCEewbcFJccICrCJ41rGG8qe13G3CmdCkmlZbm45HIhOq10mLJyFeQ6s5U468d7QhLX/RzYbq+dp2Xta9n6fQd5l9vtQripjgKAraiO4pYN7wXwXpllf62efYPYuVNy0Vh27LPmoZWQp6r8LsxOtMjODpTu29vbW51ls18ht6Vr29u7djbzmjne4K9kwC7EN9mmTOwlZB0/MuOE4e8FfI9xXeLI9O5xZOLe8UbbfhQwGXBOdsP4zlzDUvYvhfzCsF3YwjJparnyMwK/q4/ST3FfybgOIk9yPrtIfRdjHRR/bqI92oExCKfWkyjf6ed0QD2ZNpmTqV5yiSeBE+keSGEF7jox5hoap49bjfgTqK8GzAT05pr1OQO/DfjNe7l2HxeGv9fGmenPjNPH5cepz1U5qE/yC7iR6tP1r7PjWyX0wWyxvcWJWelm/cMh92FgALH2qTNA/dqf0Hk70pwjHHaMNMxdOObMcfSBk61fyE8z6X1hntEvXCnJmKUCJ9uOXgGcbE+6FZVnHvWFRlgu4xUVHVAPku1k1JU8Tlubd+Q2xPuzxlow8kiKXsbaod8rys9Q4HFOnFKPcqsaMD0M+22ky9sg3VwRjlRR6m3DXQoXxNbPsYTDEhuHU/cp+8nvwz3FJdhiNvcuu4qKmdG07RHLd/lhuz1ch591l1N7sfY3jwoc1+d3+dbx/eKCRIv/VXCrcawDbsMoc94wdII1jm1KHPvh7jTAZm8q4T4mPz4zjjlKHIeJLot/t8GbcrwO4DKKzLxsVuIY6LaOXzLhvv6P5ninqfiGSW94f1CfJyvfaSx7FXiCZXzvez+xFJYf8ZX6qxkn+VPC5kUYC39CfUQO42M=
*/