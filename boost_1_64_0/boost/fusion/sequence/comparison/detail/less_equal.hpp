/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LESS_EQUAL_05052005_1141)
#define FUSION_LESS_EQUAL_05052005_1141

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/support/as_const.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Seq1, typename Seq2>
    struct sequence_less_equal
    {
        typedef typename result_of::end<Seq1>::type end1_type;
        typedef typename result_of::end<Seq2>::type end2_type;

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const&, I2 const&, mpl::true_)
        {
            return true;
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b, mpl::false_)
        {
            return extension::as_const(*a) <= extension::as_const(*b)
                && (!(extension::as_const(*b) <= extension::as_const(*a)) || 
                    call(fusion::next(a), fusion::next(b)));
        }

        template <typename I1, typename I2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static bool
        call(I1 const& a, I2 const& b)
        {
            typename result_of::equal_to<I1, end1_type>::type eq;
            return call(a, b, eq);
        }
    };
}}}

#endif

/* less_equal.hpp
3rKriumvk9whuym9Wt+rCp3rqOW7zfcARou1AvoVv0ulSFuosYVHdRwvS+a7fhLDlN6f3G0ZabdK2gr7nX9PpJ15MtJE3ZD2jX2MBjf6bUgFW/heyrXnI09htIJBVRvpY/uRrqqL9K8U9Ob19NBTgf4I6+lVHaetS8YYxzTnJpY2oAUWfMp5yhU+ZyJ9/WmEzhtH6mM8xumcouZ0QRuInxO7QD9N7Ni2gzL3mk3yu+H92j5iF+W0nDi3zNSYl2h5Z3GLynfswASbtbiUP42504j8A0R+YcIUBZnRU9AnMEfoZzarusDdpBulLmY/o/lE96nrhR/BTYhvx0YR5adqE3jomdTuAq7tPB8uIrIi0jyoTjJ4DWwWZRgq3yvA2iLyohbYzpx9h0zehfkmVOyUF6RgA2F6YH7CaopWY7KuC6RdvATaPfNC/qnMSsxFFTsZ+rEfZ26Rg08gB6SN2TOJjVngJnbiYqo6XfaHSR09z3fAXDgs2xGw1LYMsDQGH9xng5GN1pBYiuwHV2gdYhfMK1yXtSVi3452uJVynDyCq23oNU7n7Z3+3FJZEMvKrNuwfZvwWgYL4hYEWWIslLySk9pk3SF8puGEdgu+YFBecJ1sd9cWuAEwtU0eGCd9q5XbaZ61MrivXa4yoY5j41THKDXBudxNS+Npd3m+04W3k/M4ANG3bJzqmASpHWdhixlPUy5q1+wTPttopXkAtskwEub6c7RArT3PVHSNrSiKAqjgAvASTtou6+P0fjQLwaXNj8sqmm+H2RGZpL3jOPUdzFI/ytyMVY9yKPpdqujnxmkLBpNP7YuntdyEV1S+xIANcJYlrYCVxTglg2ITeF3lmcpsls/XTMt0iQqD8ULRF8dJrkTfsm0Hxvj8yVjX5xZtL9tMQTgYkoomButssD+iPHdpe4HHihOzlCptzsM5qN/ks0g5XmSZue2CiWe7uZzRZ1HbugB2/p4NXaCtl4N5M1QewEZg4mnHzoZ9dNkd6lmwUbr4iWLP3yuO67OF62yZvpBj5gHT/STDYMAhFYX7qgHYs9vM36Q8lEuz4wFlD1Fgmv01Dg3qdHwfF75UBQbeffVyMObtJ9W4u0ecVhKaoQ/nqblKLNIrz6DjN4/AqcN2DC0XY8k3KOR/g8gPY9OERwbTEBNulop++gz6rUB2nqVRutFvJeIwDBTyNO34nTWNHW8N6jjci2Hs+FocyZNwox5D8iRMDAKmuGvTcFJOgYHNbC3m+XhOY5h36Rh551VgmvtQd0ijazYW9wvMu2r1xXPzU0g85tDL4PXPWAPPXdxzSJvap5D5KI2TBC5NGXiVOaZofkHdMTJHuqkN00WaGqDMQrZ6kvDgPmgnuSMAvJeapULLMFV0+pV198JYZU3z0zDI7ZBxzPWChR4vqMf7Nu5FCB+MhQgYY9MB5eQ7r724gq+y6l5E5Z1kKYBtH6o114MPxMFtzEerYl+eua0kj+FVcXWhU8lHq+IyI4idjG24iDq9yrvznTMD6rtzHOQx8xg636nk2P8twcVwt+SlqcviK9O93LfHyH7VhnujOAQNlC+1+pjYE8N5fHhgdrZzvsvOUL3u8kAsvskt+t0TF0zfW4Hyniw+5TFqA35/jN6DJbAeJU7qb3QeEW068TQSg8e2vdDKq8+HxyuxqL80rH4vz8xdC9zLa/OaTT2N5iqw08iEEgLDhKhnyyvnV9Z6sLC/B3zZwWOIPL0PdIWM00RGbASRacYp9KaTK2v9Yi9cZLKCPaTWD7qvF2NAlRHBtsyN88iOW9Aj4fRQ+medg/14e4G/6AZzrNpOxhY49oOTFn8nzemin4NcnleRyrWt1E3z0GuWe/aBck+Kdns=
*/