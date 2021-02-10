/*=============================================================================
    Copyright (c) 2014 Christoph Weiss

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_HASH_23072014_1017)
#define FUSION_HASH_23072014_1017

#include <boost/functional/hash.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace hashing
    {
        struct hash_combine_fold
        {
            typedef std::size_t result_type;
            template<typename T>
            inline std::size_t operator()(std::size_t seed, T const& v)
            {
                boost::hash_combine(seed, v);
                return seed;
            }
        };

        template <typename Seq>
        inline typename
        boost::enable_if<traits::is_sequence<Seq>, std::size_t>::type
        hash_value(Seq const& seq)
        {
            return fold(seq, 0, hash_combine_fold());
        }
    }

    using hashing::hash_value;
}}

#endif

/* hash.hpp
hS0bKBBRN2Go19kfzaZb+zlyTMmwQA3VEi+fOsM1P4e4hFJssekacjoupTbirXjp4SRO07VI79R9lqoTAZSCvitdE6JQD2i/md1wS47AZhEhUkTfq92FP//0J9e6ATCQ76Kftd3hvnT1iB6/JQqJGRXKAPS8WBQf0E6c+9Gm0gREJjoeU+qP9gztAvAzmDXrJ7fasGaz1kpUUyOfOu92JQTTu4XL2pkAniACSwhGMrCNbjmq6ftYvbk5tVHhYVf/UWbvTKr0koii7XRCvsZ8D2x0YiGnwei8OtdjtfDzUqWBY5ja6FUWUkR8NjPYjGR3DhtihklQmD+1xNCfGyRHWkp6uW4Yx2epj8cJ1ZdKMHnbUBUX9NT3l02z43NBqR9NPWrdjtjfzjCe/Trsdj5hBHIwPDMSjmiqWdcapclV+/L9YHjVHjuiWqpUCTrZxwOSTKpIG27EAVgBeRAlwd83ciMP1NmBOZPgcxENfS6Bn2CTssWGLn6pvYEhfCpHBsP0lJmm8EMlk83hInSxW2BMF3h6/JZuE9kDUvxRJpGObVfNeN1cGYB09spiwBh/ww05mNo6x5WBuwnu2i2FD8IkgYecDU9nytRbmfTt615tpq47zzZjz5rtdPuNW8Ffq3BGqhkHVKfV94K8X/RR
*/