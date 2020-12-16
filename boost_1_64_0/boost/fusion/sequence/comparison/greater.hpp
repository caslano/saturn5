/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_GREATER_05052005_0432)
#define FUSION_GREATER_05052005_0432

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/comparison/enable_comparison.hpp>

#if defined(FUSION_DIRECT_OPERATOR_USAGE)
#include <boost/fusion/sequence/comparison/detail/greater.hpp>
#else
#include <boost/fusion/sequence/comparison/less.hpp>
#endif

namespace boost { namespace fusion
{
    template <typename Seq1, typename Seq2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    greater(Seq1 const& a, Seq2 const& b)
    {
#if defined(FUSION_DIRECT_OPERATOR_USAGE)
        return detail::sequence_greater<Seq1 const, Seq2 const>::
            call(fusion::begin(a), fusion::begin(b));
#else
        return (b < a);
#endif
    }

    namespace operators
    {
        template <typename Seq1, typename Seq2>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        inline typename
            boost::enable_if<
                traits::enable_comparison<Seq1, Seq2>
              , bool
            >::type
        operator>(Seq1 const& a, Seq2 const& b)
        {
            return fusion::greater(a, b);
        }
    }
    using operators::operator>;
}}

#endif

/* greater.hpp
rtk4uSlM3N3cOSsYmmL2bm2KR4qZ5m9M7/jL3K66gE157PqJ0xD2XtZLtKcYrS/edEOvCxsAOxS+6sexmrO7y3zOdtIeuj7qOPUQ+bI/1Tv0hWX+Rt/uuEXY7gl+n9+cFpb37yWTvoCZmh9mkRs5cIIQ02s6LJ0iuJ3x102aY4HneUIwdMbbwzP98Rb5fpIt0RVeh58mXhDkMH7ZglniOVYHreHryzW/uC4chH34ZE2qYJH9yeqo2hJ4e/av8DdVN++Ffpo724crAQx1En9ko7vCfMUThI2DJ4ogEbVU6DS3VvgYh2FaBEXsOna4fqpHtclZqY1xL+m1u26iafkYqzpPrvD363ZSwGYPPqGN4f15f+zy/oDfXpb3ulFJOhVe/9q1ICb/qJWaX4VbdEQoPSEkrpWH/xa2P+bfTuN2caXuv5r4noeH1FKTKmRk1Cj261obP7PC12wv8uHMXoSMjvePtjOojUmQ5F0/Sbucdmdja3zW4vc657d0gk3hSiFpIWc187v/ybxO2KgVnTRxNd38Og8+mc9tDw1Nu7CfRJoEngqdz71jT+bjkvpZR4QPcBpSONTtGosn832il6VdL04yQdu8T/C6J7W6u2GGrc0PiN5IK63sRWk+PZnP316SFnBrjgStnW6a7zUfNGmP5e1eNyiiinJ1e4Pm7opq52dYXRH2Q/jYh167pLDTyVpjc6U2NlEUwiNN1sg0H7x/rtf6B27leQh/SouuTzEknAerufQUc/+J4MXZi4uK49HapOZnLHFpvuadJPXicu5IrUdbhA2RU4d8vZdMOmGClcOksl0NnxRYBxuzmk0bqyuEPVAaCw9RQVS2xR42OpfWn8LHoXDhqOjm5XyTGgKTmsaB5sxTeH/i1G93ok6X6LVGTRE7tAcxWrjxoIvghOKVtNPKsEa3Vvu2f6ZGFyaR1yuqrl1JlvthINKk0pxxyRfrKXV/c5BBznr+jdgHcI0arQpZBabedMppXq/zOiHrJW4vhoAjlUvYvB5JUpHB6/6n8nkAi8cQfWyQmaejngcHn8rmQQ6b0m7Syx2tyxK0tX3nqTWb6NT1e77fqxGhS0eDac2/9ySvL+hlRQ5XP5OUWkf2TbW2JZ4YaZ8xqQU/3SevfGptT3aDGKbXkkzsyc2yxsWn8jXvd10ING2TUGqLajENTDqgpyCKQ9c36KpB6J/ekmKH3mdqdWJfw7GTB4q2NCErr9o1uajWNym8beFoXjhMA0hD2KL5cpLRYV+DTxxkaU6HE75Gd9CkK0AW53A6zp3TgzVYZQrftFLPSkIfxc0w6RIHC7ATQzCt6LgPPY1fdLK2FuJMuP77zumxcANYPYy/m3w5TzG6LgziCtfL2kVJN9sCj9MxIomIK9vZ4TYrgtbFebOMHGEYei72mMKRtxhGRLL3ST7+Oc6mrBvEjhCShIxUOg/CfGcNVoXUtXrfuMToReiGsOPmsHlbkw47qPaFW2P8f0Trn/wUanVDjuy146IgX/Kt8fMh7mLOyjIkveqza7U+K5DkB0GPUtsXvb51af73P42vN0hdiHPRJh5GY4v6uOL/IKONHfhI9lI0HW63w9XK/xV9Jler4cZOsvTT+HyGF3bebUPQpwpF3RiHKR+zk0+r+f4HMBvG1mnSGQNunUu7T6vdD/0CAmPcZfRbIuSDsDTmNq0Xnsbv9XkMb/mgy3ieKncV7oVOfJCc8zQ+/pHrou89xke59/CGbCv6K7X+h/jpd7to0AjuBWcHGyDbnMzOWQNIMeifVtOVhAW8T3qhM8LOvI2wEeC+ut+J4D3jmTAWnw1IFnZof3l6bT9LvcLzo4J8wcXi3dk8Paz5Xh9jdK7TiWGnCRs=
*/