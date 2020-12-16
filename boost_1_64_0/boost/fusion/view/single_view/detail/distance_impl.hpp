/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if !defined(BOOST_FUSION_SINGLE_VIEW_DISTANCE_IMPL_JUL_07_2011_1348PM)
#define BOOST_FUSION_SINGLE_VIEW_DISTANCE_IMPL_JUL_07_2011_1348PM

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/minus.hpp>

namespace boost { namespace fusion 
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<single_view_iterator_tag>
        {
            template<typename First, typename Last>
            struct apply
              : mpl::minus<typename Last::position, typename First::position>
            {
                typedef typename mpl::minus<typename Last::position,
                    typename First::position>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(First const& /*first*/, Last const& /*last*/)
                {
                    return type();
                }
            };
        };
    }

}}

#endif

/* distance_impl.hpp
tA2G0fh8MUUsNYQ5OkfPJ69bMU+00szk98pxPjQHsx3lX58UFkLLxqz5hWXy2Kozul9Bs3SxQXVm1acd2SfMrbPvbnrGUq/RsjKrN2zSQeoZWkFmqRkmbaZcdFYL3q4Xprmj7aK52Abqi87yTzXVEubV2cTJ52tSnjorPXFzHVojtOLMLuTLO4py6RptP7cc66K+6Cz74plvhfl11qZaQn+aT2crXpw5RPN1i7YJ2/bfp/nQ8jOT7zli7WgJJmlHlte8Tr3ujtdLZmlby9q+FubohecqkEbf4UdzoVVm9s58vgLVh6Yx2/q60DRhIbS5MWybaHRzCo3Zn85HaNHnoyBaXWa5+uztTn0ZEH0MqfnusZ1soA32stpnlu7Tn+bz4H0Vs/Nvn7ag+Qbb4A5I65ghoSGt0RAbjGe2OteIO9TroXg+YsbPR340OzN+PgqhJTHj5yPLMLW50BLJ+Llqc4wP7VBafVnNm2M6Vqg0Q1hohA0+BWlDcw3+XphrpA0uMtNeV5glzD3KBn2YLfnoh6+FRdAyMqN3lNBgtA06MGt1t/ASYR6dNX00dK+wMNoxZiWGrZhF9pkNnjI7MeDidmHaGLymjZVWsszgRGHeCTbox+JuTH1wRphlIh53meVZl7JOmAPtdZplQ/vhy5u7qYYvbLCZ2ewxt45SPyfZICbNsv/fbHtSqZ9oqdb3lgOtbe6hDyiXjTZ6Xp4Trcuce4eodrRR6aX9dXq4SxjswOOuWdqpk5OpZ76dNigF0h5dz1pMWAjtB2bLN15dIyy4ywYv0ywXmvePobWEwY82uMYsfbaJVIO2xwb9mS3f/ts/wgJoieml7Tz0n6nUz0O0LaFFb0tetObM6DiBFkH70izNcyvdv7R+h23wCYtb0nJjO8oFrR6zyNw1G2kdfsWeMetypY6H1hYtrzS2v+PcaHZmtL+j+dGSmNE+jRY2MO2/2DNmfH93o6ni/GiqXEIGcZYjanOhqXLxGcSFDOIsv9lgsOm95UaLn/0p9TN8lLYJtOhtIoL2JYt7u2xFmOy4DYqYpR05NCSW+hKKtvodl5K5TlPP0KJ75kVLYsbrC6IlMuP1wRk8r6TN9yHa109f9aVczttgEUjLte94ZlrbC5gLM56LDy2RGZ8vhFYmzfKgdS9/3kq9vojnxgzStkZ2Uy7Bm5gLiysxdvcMqv0W5sKM5xJAS2LG+xJBS2TG83TctsGGmPeWF+1ErcNequGeDYabpe3eBplozAdUH1p0fY6HuE9nlFbl8Tk79ewpzsfi7mZ4t1aY55l6zABacZO0oVUfhmm+FzYowOxx1SwHab6X1DO06J4F0RLJeF+2xMArmUs+85aY7ruf7RXmRPMzm9Dg8Aphltc2MJukXX57paQw9xt8NsPizjvjm9OYb20wmVn9tosLCIugFWCWeP7SjzTfO3zmz6y3Y1xhmg/tFsulUvU/NwsLmjTwsLiV+/pPEeYya5CbxaXPtpZqCMRoMILFDfh5wyGKi9VgFLMR2UdPpxoMzJdOgzbMynQtPk0YpNdgC7Oseep6hYXRmjILbU2aQLlk0KA5s05jNuam2tFWM+vZf8wdyiWjBnZpbHvBOAOLoCUxo/0PzfGBBonM+HbmMbAAmmq+MFpeZnT+Q4NM6jgHmipPD5oyF7S2aZYfrd/VGf2FaZk1SGbW9IUpRpgbrSazRhmXr6B+oh1jtnxRufVkWTQ4zezcgdKvhYWyalDIJG1/4477hTmza/CQ2S/uTJ9RDTk0GAjSUt/lm0txOTX4m1nrP2yvqC+5NLjLrEKVDVmF+XJrcIPZ3WVdytN8H2owmtm2Q1XqCXPl0aAMM/OkGeNoTLTszP6Y8Go=
*/